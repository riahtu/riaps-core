//
// Created by istvan on 11/11/16.
//

#include "LocalEstimator.h"

namespace distributedestimator {
    namespace components {


        LocalEstimator::LocalEstimator(_component_conf &config, riaps::Actor &actor) :
                LocalEstimatorBase(config, actor) {
            //PrintParameters();
        }

        void LocalEstimator::OnReady(const messages::SensorReady::Reader &message,
                                     riaps::ports::PortBase *port) {

            //PrintMessageOnPort(port, message.getMsg().cStr());

            _logger->info("LocalEstimator::OnReady(): {} {}", message.getMsg().cStr(), ::getpid());

            capnp::MallocMessageBuilder builderSensorQuery;

            messages::SensorQuery::Builder queryMsg = builderSensorQuery.initRoot<messages::SensorQuery>();

            queryMsg.setMsg("sensor_query");
            auto result = SendQuery(builderSensorQuery, queryMsg);
            if (result) {
                messages::SensorValue::Reader sensorValue;
                if (RecvQuery(sensorValue)) {
                    if (GetPortByName(PORT_REQ_QUERY)->GetPortBaseConfig()->isTimed) {
                        auto recvPort = GetPortByName(PORT_REQ_QUERY)->AsRecvPort();
                        if (recvPort!=nullptr){
                            _logger->info("LocalEstimator::OnQuery(): {};  sentTimestamp: {}.{}, recvTimestamp: {}.{}",
                                          sensorValue.getMsg().cStr(),
                                          recvPort->GetLastSendTimestamp().tv_sec ,
                                          recvPort->GetLastSendTimestamp().tv_nsec,
                                          recvPort->GetLastRecvTimestamp().tv_sec ,
                                          recvPort->GetLastRecvTimestamp().tv_nsec
                            );
                        }
                    } else {
                        _logger->info("LocalEstimator::OnQuery(): {}", sensorValue.getMsg().cStr());
                    }

                    capnp::MallocMessageBuilder builderEstimate;
                    auto estimateMsg = builderEstimate.initRoot<messages::Estimate>();
                    estimateMsg.setMsg("local_est(" + std::to_string(::getpid()) + ")");
                    SendEstimate(builderEstimate, estimateMsg);
                }
            }
        }



        LocalEstimator::~LocalEstimator() {

        }
    }
}

riaps::ComponentBase *create_component(_component_conf &config, riaps::Actor &actor) {
    auto result = new distributedestimator::components::LocalEstimator(config, actor);
    return result;
}

void destroy_component(riaps::ComponentBase *comp) {
    delete comp;
}