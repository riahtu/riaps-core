#include "discoveryd/r_riaps_actor.h"

#define REGULAR_MAINTAIN_PERIOD 3000 //msec

#define DHT_ROUTER_CHANNEL "ipc:///tmp/dhtrouterchannel"

void
riaps_actor (zsock_t *pipe, void *args)
{

    /////
    // Experiment, use OpenDHT
    ////
    dht::DhtRunner dht_node;

    // Launch a dht node on a new thread, using a
    // generated RSA key pair, and listen on port 4222.
    dht_node.run(RIAPS_DHT_NODE_PORT, dht::crypto::generateIdentity(), true);

    auto mtx = std::make_shared<std::mutex>();
    auto cv = std::make_shared<std::condition_variable>();
    auto ready = std::make_shared<bool>(false);

    auto wait = [=] {
        *ready = true;
        std::unique_lock<std::mutex> lk(*mtx);
        cv->wait(lk);
        *ready = false;
    };
    auto done_cb = [=](bool success) {
        //if (success) {
        //    std::cout << "success!" << std::endl;
        //} else {
        //    std::cout << "failed..." << std::endl;
        //}
        std::unique_lock<std::mutex> lk(*mtx);
        cv->wait(lk, [=]{ return *ready; });
        cv->notify_one();
    };



    std::srand(std::time(0));

    init_command_mappings();


    zsock_t* dht_router_socket = zsock_new_pull(DHT_ROUTER_CHANNEL);
    assert(dht_router_socket);

    // Response socket for incoming messages from RIAPS Components
    zsock_t * riaps_socket = zsock_new_rep (DISCOVERY_SERVICE_IPC);
    //zsock_t * riaps_socket = zsock_new_router ("ipc://riapsdiscoveryservice");
    assert(riaps_socket);

    //zactor_t* async_service_poller = zactor_new(service_poller_actor, NULL);
    //assert(async_service_poller);

    zpoller_t* poller = zpoller_new(pipe, riaps_socket, dht_router_socket, NULL);
    assert(poller);




    bool terminated = false;
    zsock_signal (pipe, 0);

    // Store the last checkins of the registered services
    // If there was no checkin in SERVICE_TIMEOUT ms then, remove the service from consul
    std::map<std::string, int64_t> service_checkins;

    // Pair sockets for Actor communication
    std::map<std::string, actor_details> clients;

    // Client subscriptions to messageTypes
    std::map<std::string, std::set<std::string>> clientSubscriptions;


    //char hostname[256];
    //int hostnameresult = gethostname(hostname, 256);

    //if (hostnameresult == -1) {
    //    std::cout << "hostname cannot be resolved" << std::endl;
    //    return;
    //}

    //disc_registernode(hostname);

    while (!terminated){
        void *which = zpoller_wait(poller, REGULAR_MAINTAIN_PERIOD);

        // Handling messages from the caller (e.g.: $TERM$)
        if (which == pipe) {
            zmsg_t* msg = zmsg_recv(which);
            if (!msg){
                std::cout << "No msg => interrupted" << std::endl;
                break;
            }

            char* command = zmsg_popstr(msg);

            if (streq(command, "$TERM")){
                std::cout << "R_ACTOR $TERM arrived" << std::endl;

                //disc_deregisternode(std::string(hostname));

                terminated = true;
            }
            else if (streq(command, "JOIN")) {
                std::cout << "JOIN arrived" << std::endl;
                bool has_more_msg = true;

                while (has_more_msg){
                    char* newhost = zmsg_popstr(msg);
                    if (newhost){
                        std::cout << "Connect to: " << newhost;
                        std::string str_newhost(newhost);
                        dht_jointocluster(str_newhost, RIAPS_DHT_NODE_PORT, dht_node);
                        zstr_free(&newhost);
                    } else{
                        has_more_msg = false;
                    }
                }
            }

            if (command){
                zstr_free(&command);
            }
            zmsg_destroy(&msg);
        }
        else if (which == dht_router_socket){
            // Process the updated nodes
            zmsg_t* msg_response = zmsg_recv(dht_router_socket);

            zframe_t* capnp_msgbody = zmsg_pop(msg_response);
            size_t    size = zframe_size(capnp_msgbody);
            byte*     data = zframe_data(capnp_msgbody);

            auto capnp_data = kj::arrayPtr(reinterpret_cast<const capnp::word*>(data), size / sizeof(capnp::word));

            capnp::FlatArrayMessageReader reader(capnp_data);
            auto msg_providerupdate = reader.getRoot<ProviderUpdatePush>();

            std::string provider_key = std::string (msg_providerupdate.getProviderpath().cStr());

            auto msg_newproviders = msg_providerupdate.getNewvalues();

            for (int i =0; i<msg_newproviders.size(); i++){
                std::cout << "New provider: " << msg_newproviders[i].cStr() <<std::endl;
            }


            // Look for services who may interested in the new provider
            if (clientSubscriptions.find(provider_key)!=clientSubscriptions.end()){
                for (auto& new_provider : clientSubscriptions[provider_key]){

                }
            }


            zframe_destroy(&capnp_msgbody);
            zmsg_destroy(&msg_response);
        }

        // Handling messages from the RIAPS FW
        // Discovery service commands
        else if(which == riaps_socket){
            zmsg_t* msg = zmsg_recv(which);
            
            if (!msg){
                std::cout << "No msg => interrupted" << std::endl;
                break;
            }

            zframe_t* capnp_msgbody = zmsg_pop(msg);
            size_t    size = zframe_size(capnp_msgbody);
            byte*     data = zframe_data(capnp_msgbody);

            auto capnp_data = kj::arrayPtr(reinterpret_cast<const capnp::word*>(data), size / sizeof(capnp::word));

            capnp::FlatArrayMessageReader reader(capnp_data);
            auto msg_discoreq= reader.getRoot<DiscoReq>();

            //zsys_info("Message arrived: %s (%s)", "DiscoReq", msg_discoreq.which());

            // Register actor
            if (msg_discoreq.isActorReg()) {
                auto msg_actorreq = msg_discoreq.getActorReg();
                std::string actorname    = std::string(msg_actorreq.getActorName());
                std::string appname      = std::string(msg_actorreq.getAppName());

                std::string clientKeyBase = "/" + appname + '/' + actorname + "/";

                // If the actor already registered
                if (clients.find(clientKeyBase)!=clients.end()) {
                    std::cout << "Cannot register actor. This actor already registered (" << clientKeyBase << ")" << std::endl;

                    capnp::MallocMessageBuilder message;
                    auto drepmsg = message.initRoot<DiscoRep>();
                    auto arepmsg = drepmsg.initActorReg();

                    arepmsg.setPort(0);
                    arepmsg.setStatus(Status::ERR);

                    auto serializedMessage = capnp::messageToFlatArray(message);

                    zmsg_t* msg = zmsg_new();
                    zmsg_pushmem(msg, serializedMessage.asBytes().begin(), serializedMessage.asBytes().size());

                    zmsg_send(&msg, riaps_socket);

                } else{
                    // Open a new PAIR socket for actor communication
                    zsock_t * actor_socket = zsock_new (ZMQ_PAIR);
                    auto port = zsock_bind(actor_socket, "tcp://*:!");

                    clients[clientKeyBase] = actor_details{};
                    clients[clientKeyBase].socket     = actor_socket;
                    clients[clientKeyBase].port = port;

                    // Create and send the Response
                    capnp::MallocMessageBuilder message;
                    auto drepmsg = message.initRoot<DiscoRep>();
                    auto arepmsg = drepmsg.initActorReg();

                    arepmsg.setPort(port);
                    arepmsg.setStatus(Status::OK);

                    auto serializedMessage = capnp::messageToFlatArray(message);

                    zmsg_t* msg = zmsg_new();
                    zmsg_pushmem(msg, serializedMessage.asBytes().begin(), serializedMessage.asBytes().size());

                    zmsg_send(&msg, riaps_socket);

                    // TODO: replace with MacAddress
                    auto uuid = gethostid();
                    auto uuid_str = std::to_string(uuid);
                    //zuuid_destroy(&uuid);

                    std::string clientKeyLocal = clientKeyBase + uuid_str;
                    clients[clientKeyLocal] = _actor_details{};
                    clients[clientKeyLocal].port = port;

                    std::string clientKeyGlobal = clientKeyBase + uuid_str;
                    clients[clientKeyGlobal] = _actor_details{};
                    clients[clientKeyGlobal].port = port;
                }
            } else if (msg_discoreq.isServiceReg()){
                auto msg_servicereg_req = msg_discoreq.getServiceReg();
                auto msg_path           = msg_servicereg_req.getPath();
                auto msg_sock           = msg_servicereg_req.getSocket();

                auto kv_pair = buildInsertKeyValuePair(msg_path.getAppName(),
                                                       msg_path.getMsgType(),
                                                       msg_path.getKind(),
                                                       msg_path.getScope(),
                                                       msg_sock.getHost(),
                                                       msg_sock.getPort());

                // Insert KV-pair

                /// Consul part (main line now)
                //disc_registerkey(kv_pair.first, kv_pair.second);

                std::cout << "Register: " + kv_pair.first << std::endl;

                /////
                // Experiment OpenDht
                ////


                // Convert the value to bytes
                std::vector<uint8_t> opendht_data(kv_pair.second.begin(), kv_pair.second.end());
                auto keyhash = dht::InfoHash::get(kv_pair.first);
                //dht_node.put(keyhash, dht::Value(opendht_data), [=](bool success){
                    // Done Callback
                //    done_cb(success);
                //});

                //dht::Value opendht_data_value = dht::Value(opendht_data);
                //opendht_data_value.user_type = kv_pair.first;

                dht_node.put(keyhash, dht::Value(opendht_data));

                std::cout << "keyhash: "<< keyhash << std::endl;

                // Add listener to the added key
                auto token = dht_node.listen(keyhash,
                         [kv_pair](const std::vector<std::shared_ptr<dht::Value>>& values) {

                             zsock_t* notify_ractor_socket = zsock_new_push(DHT_ROUTER_CHANNEL);

                             capnp::MallocMessageBuilder message;
                             auto msg_provider_push       = message.initRoot<ProviderUpdatePush>();
                             msg_provider_push.setProviderpath(kv_pair.first);

                             std::vector<std::string> update_results;
                             for (const auto& value :values ){
                                 std::string result = std::string(value->data.begin(), value->data.end());
                                 update_results.push_back(result);
                             }

                             auto number_of_providers = update_results.size();
                             ::capnp::List< ::capnp::Text>::Builder msg_providers = msg_provider_push.initNewvalues(number_of_providers);

                             int provider_index = 0;
                             for (std::string provider : update_results){
                                 ::capnp::Text::Builder b((char*)provider.c_str());
                                 msg_providers.set(provider_index++, b.asString());
                             }

                             auto serializedMessage = capnp::messageToFlatArray(message);

                             zmsg_t* msg = zmsg_new();
                             zmsg_pushmem(msg, serializedMessage.asBytes().begin(), serializedMessage.asBytes().size());

                             zmsg_send(&msg, notify_ractor_socket);

                             //for (const auto& v : values) {
                             //    std::cout << "Found value: " << *v << std::endl;
                             //    std::cout << "In Key: " << kv_pair.first << std::endl;
                             //    std::cout << "Let's look if anybody is interested in..." << std::endl;


                                 /*zmsg_t* q_interested = zmsg_new();
                                 zmsg_addstr(q_interested, "Szevasz");

                                 zmsg_send(&q_interested, notify_ractor_socket);

                                 zmsg_t* r_interested = zmsg_recv(notify_ractor_socket);
                                 char*t = zmsg_popstr(r_interested);
                                  */


                              //   std::cout << std::endl;
                             //}

                             sleep(1);
                             zsock_destroy(&notify_ractor_socket);
                             sleep(1);

                             return true; // keep listening
                         }
                );

                /////
                //  End experiment
                /////

                //Send response
                capnp::MallocMessageBuilder message;
                auto msg_discorep       = message.initRoot<DiscoRep>();
                auto msg_servicereg_rep = msg_discorep.initServiceReg();

                msg_servicereg_rep.setStatus(Status::OK);

                auto serializedMessage = capnp::messageToFlatArray(message);

                zmsg_t* msg = zmsg_new();
                zmsg_pushmem(msg, serializedMessage.asBytes().begin(), serializedMessage.asBytes().size());

                zmsg_send(&msg, riaps_socket);

            } else if(msg_discoreq.isServiceLookup()){
                auto msg_servicelookup = msg_discoreq.getServiceLookup();

                auto client = msg_servicelookup.getClient();
                auto path   = msg_servicelookup.getPath();

                // Key   -> /appname/msgType/kind
                // Value -> /appname/clientactorname/clienthost/clientinstancename/clientportname
                // The "value" is interested in "key"
                auto lookupkey =
                           buildLookupKey(path.getAppName()        ,
                                          path.getMsgType()        ,
                                          path.getKind()           ,
                                          path.getScope()          ,
                                          client.getActorHost()    ,
                                          client.getActorName()    ,
                                          client.getInstanceName() ,
                                          client.getPortName()     );




                /// Consul part (main line now)
                //std::string consul_lookup_result = disc_getvalue_by_key(key.first);


                /////
                // Experiment OpenDht
                ////

                // Convert the value to bytes
                //std::vector<uint8_t> opendht_data(kv_pair.second.begin(), kv_pair.second.end());

                // For dht async request - response

                std::cout << "Get: " + lookupkey.first << std::endl;

                std::vector<std::string> dht_lookup_results;
                dht_node.get(lookupkey.first, [&](const std::vector<std::shared_ptr<dht::Value>>& values){
                    // Done Callback
                    for (const auto& value :values ){
                        std::string result = std::string(value->data.begin(), value->data.end());
                        dht_lookup_results.push_back(result);
                    }
                    return true;
                }, [=](bool success){
                    // Done Callback
                    std::cout << "Get callback done! " << success <<std::endl;
                    done_cb(success);
                });

                wait();

                std::cout << "Get results: ";

                for (auto r : dht_lookup_results){
                    std::cout << r << ", ";
                }

                std::endl(std::cout);

                //zclock_sleep(5000);

                /////
                //  End experiment
                /////

                //Send response
                capnp::MallocMessageBuilder message;
                auto msg_discorep       = message.initRoot<DiscoRep>();
                auto msg_service_lookup_rep = msg_discorep.initServiceLookup();

                msg_service_lookup_rep.setStatus(Status::OK);

                auto number_of_clients =dht_lookup_results.size();
                auto sockets = msg_service_lookup_rep.initSockets(number_of_clients);

                for (int i = 0; i<number_of_clients; i++){
                    auto dht_result = dht_lookup_results[i];
                    auto pos = dht_result.find_first_of(':');
                    if (pos==std::string::npos) continue;

                    auto host = std::string(dht_result.begin(), dht_result.begin()+pos);
                    auto port = std::string(dht_result.begin()+pos+1, dht_result.end());

                    sockets[i].setHost(host);
                    sockets[i].setPort(std::stoi(port));

                    std::cout << "Added: " << host << " " << std::stoi(port) << std::endl;
                }

               // msg_service_lookup_rep.setSockets()

                //msg_servicereg_rep.setStatus(Status::OK);

                auto serializedMessage = capnp::messageToFlatArray(message);

                zmsg_t* msg = zmsg_new();
                zmsg_pushmem(msg, serializedMessage.asBytes().begin(), serializedMessage.asBytes().size());

                zmsg_send(&msg, riaps_socket);

                // Subscribe, if new provider arrives

                // -- Register with OpenDHT --
                // This client is interested in this kind of messages. Register it.
                //std::string client_subscribe_key = lookupkey.first + "_clients";
                //std::vector<uint8_t> opendht_client_subscribe_data(client_subscribe_key.begin(), client_subscribe_key.end());
                //auto keyhash = dht::InfoHash::get(client_subscribe_key);
                //dht_node.put(keyhash, dht::Value(opendht_client_subscribe_data));


                // Now using just the discovery service to register the interested clients
                if (clientSubscriptions.find(lookupkey.first) == clientSubscriptions.end()){
                    // Nobody subscribed to this messagetype
                    clientSubscriptions[lookupkey.first] = std::set<std::string>();
                }

                clientSubscriptions[lookupkey.first].insert(lookupkey.second);

            }




            //capnp::initMessageBuilderFromFlatArrayCopy(reader.getRoot(), message);

            //capnp::MallocMessageBuilder message;
            //capnp::initMessageBuilderFromFlatArrayCopy(kjptr, message);
            /*
            char* command = zmsg_popstr(msg);
            
            if (command){

                if (streq(command, CMD_DISC_GETSERVICE_BY_NAME_POLL_ASYNC)) {
                    //zframe_t* flat_msgbody = zmsg_pop(msg);
                    //byte* framedata = zframe_data(flat_msgbody);
                    //auto m = Getmsg_getservice_poll_request(framedata);

                    //auto s = m->service_name()->str();
                    //auto r = m->reply_id()->str();


                    //int i =5;
                }

                    // TODO: only handle_command should be called, without ifs
                if (streq(command, CMD_DISC_REGISTER_SERVICE)) {
                    bool handle_result = handle_command(command, msg, riaps_socket, async_service_poller);
                    assert(handle_result);
                }
                else if (streq(command, CMD_DISC_DEREGISTER_SERVICE)){
                    bool handle_result = handle_command(command, msg, riaps_socket, async_service_poller);
                    assert(handle_result);
                }
                else if (streq(command, CMD_DISC_GET_SERVICES)) {
                    bool handle_result = handle_command(command, msg, riaps_socket, async_service_poller);
                    assert(handle_result);
                }
                else if (streq(command, CMD_DISC_GETSERVICE_BY_NAME)) {
                    bool handle_result = handle_command(command, msg, riaps_socket, async_service_poller);
                    assert(handle_result);
                }
                else if (streq(command, CMD_DISC_GETSERVICE_BY_NAME_ASYNC)){
                    bool handle_result = handle_command(command, msg, riaps_socket, async_service_poller);
                    assert(handle_result);
                }
                else if(streq(command, CMD_DISC_REGISTER_NODE)){
                    bool handle_result = handle_command(command, msg, riaps_socket, async_service_poller);
                    assert(handle_result);
                }


                else if (streq(command, CMD_DISC_REGISTER_ACTOR)){
                    char* actorname = zmsg_popstr(msg);
                    if (actorname){
                        disc_registeractor(hostname, actorname);
                        free(actorname);
                        zstr_send(riaps_socket, "OK");
                    }
                }
                else if(streq(command, CMD_DISC_DEREGISTER_ACTOR)){
                    char* actorname = zmsg_popstr(msg);
                    if (actorname){
                        disc_deregisteractor(hostname, actorname);

                        free(actorname);

                        zstr_send(riaps_socket, "OK");
                    }
                }
                else if(streq(command, CMD_DISC_PING)){

                    std::cout << "Ping arrived" << std::endl;

                    char* service_name = zmsg_popstr(msg);
                    if (service_name){

                        //std::cout << "   " << service_name << std::endl;
                        int64_t time = zclock_mono();
                        service_checkins[service_name] = time;

                        // remove outdated services from the cache and from the discovery service
                        auto outdateds = maintain_servicecache(service_checkins);

                        for (auto outdated : outdateds){
                            std::cout << outdated << ";" ;
                        }

                        std::cout << std::endl;

                        free(service_name);
                        //zstr_send("OK", riaps_socket);
                        zstr_send(riaps_socket, "OK");
                    }
                }
                else {

                }

                free(command);
            }*/
        }
        else {
            //std::cout << "Regular maintain, cannot stop: " << terminated <<std::endl;

            //zmsg_t* msg = zmsg_recv(which);
            //if (msg){
            //    std::cout << "HEYY MSG!" << std::endl;
            //    break;
            //}

            //auto outdateds = maintain_servicecache(service_checkins);

            //for (auto outdated : outdateds){
            //    std::cout << outdated << ";" ;
            //}

            //std::cout << std::endl;
        }
    }

    for (auto it_client = clients.begin(); it_client!=clients.end(); it_client++){
        if (it_client->second.socket!=NULL) {
            zsock_destroy(&it_client->second.socket);
            it_client->second.socket=NULL;
        }
    }


    zpoller_destroy(&poller);
    //zactor_destroy(&async_service_poller);
    zsock_destroy(&riaps_socket);
    zsock_destroy(&dht_router_socket);

    sleep(1);
}

