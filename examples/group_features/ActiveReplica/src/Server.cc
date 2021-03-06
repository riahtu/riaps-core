//
// Created by istvan on 11/11/16.
//

#include "Server.h"

namespace activereplica {
    namespace components {

        Server::Server(_component_conf &config, riaps::Actor &actor) :
                ServerBase(config, actor) {
            SetDebugLevel(_logger, spdlog::level::level_enum::debug);
            _hasJoined = false;
            _lastValue = nullptr;
        }

        void Server::OnReady(const messages::SensorReady::Reader &message,
                                     riaps::ports::PortBase *port) {

            riaps::groups::GroupId gid;
            gid.groupTypeId = GROUPTYPE_BACKUPGROUP;
            gid.groupName = "Group1";


            if (!_hasJoined){
                _hasJoined = true;
                if (this->JoinToGroup(gid)){
                    _logger->debug("Joined to group {}::{}", gid.groupTypeId, gid.groupName);
                }


            }

            //_logger->info("Group.Members.Count() == {}", GetGroupMemberCount(gid));

            capnp::MallocMessageBuilder builderSensorQuery;
            messages::SensorQuery::Builder queryMsg = builderSensorQuery.initRoot<messages::SensorQuery>();

            queryMsg.setMsg("sensor_query");
            std::string requestId;
            auto result = SendQuery(builderSensorQuery, queryMsg, requestId);
            _logger->error_if(!result, "SendQuery failed");
            _logger->info_if(result, "Query sent, requestId: {}", requestId);
//            if (result) {
//                messages::SensorValue::Reader sensorValue;
//                if (RecvQuery(sensorValue)) {
//                    _lastValue.reset(new double(sensorValue.getValue()));
//                }
//            }
        }

        void Server::OnQuery(std::shared_ptr<riaps::RiapsMessage<messages::SensorValue::Reader, messages::SensorValue>>& message,
                             riaps::ports::PortBase *port,
                             std::shared_ptr<riaps::MessageParams> params) {
            _logger->info("OnQuery()");
        }

        void Server::OnGroupMessage(const riaps::groups::GroupId &groupId,
                                            capnp::FlatArrayMessageReader &capnpreader, riaps::ports::PortBase *port) {
            if (groupId.groupTypeId == GROUPTYPE_BACKUPGROUP && groupId.groupName == "Group1") {
                if (port->GetPortName() == GROUPPORT_BACKUPGROUP_QUERY_IN){

                    // If no value from the sensor, don't send reply
                    if (_lastValue == nullptr) return;

                    auto msgRequest = capnpreader.getRoot<activereplica::messages::QueryRequest>();

                    capnp::MallocMessageBuilder builder;
                    auto msgEstimate = builder.initRoot<messages::Estimate>();
                    msgEstimate.setId(msgRequest.getId());
                    msgEstimate.setValue(*_lastValue);

                    riaps::groups::GroupId gid;
                    gid.groupTypeId = GROUPTYPE_BACKUPGROUP;
                    gid.groupName = "Group1";

                    bool rc =SendGroupMessage(gid, builder, GROUPPORT_BACKUPGROUP_RESPONSE_OUT);
                    _logger->info_if(rc, "Message sent Id:{} Value:{}", msgEstimate.getId(), msgEstimate.getValue());
                    _logger->warn_if(!rc, "Couldn't send message");
                }
            }
        }

        Server::~Server() {

        }
    }
}

riaps::ComponentBase *create_component(_component_conf &config, riaps::Actor &actor) {
    auto result = new activereplica::components::Server(config, actor);
    return result;
}

void destroy_component(riaps::ComponentBase *comp) {
    delete comp;
}