//
// Created by istvan on 11/11/16.
//


#include <Client.h>

namespace activereplica {
    namespace components {

        Client::Client(_component_conf &config, riaps::Actor &actor)
                : ClientBase(config, actor), _hasJoined(false) {

            SetDebugLevel(_logger, spdlog::level::level_enum::debug);

            _pending = 0;
            _idIndex = 1;
        }

        void Client::OnEstimate(messages::Estimate::Reader &message,
                                         riaps::ports::PortBase *port) {
        }

        void Client::OnWakeup(riaps::ports::PortBase *port) {

            riaps::groups::GroupId gid;
            gid.groupTypeId = GROUPTYPE_BACKUPGROUP;
            gid.groupName = "Group1";

            if (!_hasJoined) {
                _hasJoined = true;
                bool rc = this->JoinToGroup(gid);
                _logger->debug_if(rc, "Successfully joined to group {}:{}", gid.groupTypeId, gid.groupName);

            } else {
                capnp::MallocMessageBuilder builder;

                auto msgEstimate = builder.initRoot<activereplica::messages::QueryRequest>();

                // Set the query id, which is the idIndex bit.
                msgEstimate.setId(_idIndex.to_ulong());

                //add the id to the pending requests
                _pending |= _idIndex;

                // shift the _idIndex
                _idIndex <<= 1;
                if (_idIndex == 0) _idIndex =1;

                bool rc = SendGroupMessage(gid, builder, GROUPPORT_BACKUPGROUP_QUERY_OUT);
                _logger->warn_if(!rc, "Sending groupmessage failed");
                if (rc){
                    _logger->info("Request [{}] sent", msgEstimate.getId());
                }
            }

        }

        void Client::OnGroupMessage(const riaps::groups::GroupId  &groupId,
                                    capnp::FlatArrayMessageReader &capnpreader,
                                    riaps::ports::PortBase        *port) {
            if (groupId.groupTypeId == GROUPTYPE_BACKUPGROUP && groupId.groupName == "Group1") {
                if (port->GetPortName() == GROUPPORT_BACKUPGROUP_RESPONSE_IN) {

                    auto msgEstimate = capnpreader.getRoot<activereplica::messages::Estimate>();
                    std::bitset<QUERYID_LENGTH> messageId(msgEstimate.getId());

                    // Check if the message already arrived earlier
                    // (_pending&messageId)!=0 -> New message arrived, process the new message
                    if ((_pending&messageId).any()){
                        // delete the pending flag
                        _pending ^=messageId;
                        _logger->info("Response: {}", msgEstimate.getValue());
                    }
                }
            }
        }

        Client::~Client() {

        }
    }
}

riaps::ComponentBase *create_component(_component_conf &config, riaps::Actor &actor) {
    auto result = new activereplica::components::Client(config, actor);
    return result;
}

void destroy_component(riaps::ComponentBase *comp) {
    delete comp;
}