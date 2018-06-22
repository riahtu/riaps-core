//
// Auto-generated by edu.vanderbilt.riaps.generator.ComponenetGenerator.xtend
//
#include "include/STimerBase.h"

namespace statictimer {
    namespace components {

        STimerBase::STimerBase(_component_conf &config, riaps::Actor &actor) : ComponentBase(config, actor) {

        }

        void STimerBase::DispatchMessage(capnp::FlatArrayMessageReader* capnpreader, riaps::ports::PortBase *port,std::shared_ptr<riaps::MessageParams> params) {
            auto portName = port->GetPortName();
            if (portName == PORT_TIMER_CLOCK) {
                OnClock(port);
            }

            if (portName == PORT_SUB_PING) {
                Msg::Reader Ping =
                        capnpreader->getRoot<Msg>();
                OnPing(Ping, port);
            }

        }

        void STimerBase::DispatchInsideMessage(zmsg_t* zmsg, riaps::ports::PortBase* port) {
            //empty the header
        }


        STimerBase::~STimerBase() {

        }
    }
}