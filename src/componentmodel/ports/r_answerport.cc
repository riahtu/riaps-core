#include <framework/rfw_network_interfaces.h>
#include <componentmodel/ports/r_answerport.h>

using namespace std;

namespace riaps{
    namespace ports{

        // TODO: Do not thrwo exception from the constructor
        AnswerPort::AnswerPort(const component_port_ans &config, const ComponentBase *parent_component) :
            PortBase(PortTypes::Answer, (component_port_config*)&config, parent_component),
            SenderPort(this)
        {
            port_socket_ = zsock_new(ZMQ_ROUTER);
            host_ = riaps::framework::Network::GetIPAddress();


            if (host_ == "") {
                throw std::runtime_error("Response cannot be initiated. Cannot find  available network interface.");
            }

            string end_point = fmt::format("tcp://{}:!", host_);
            port_ = zsock_bind(port_socket_, "%s", end_point.c_str());


            if (port_ == -1) {
                throw std::runtime_error("Couldn't bind response port.");
            }

            logger_->info("Answerport is created on: {}:{}", host_, port_);


            if (!registerService(parent_component->actor()->application_name(),
                                 parent_component->actor()->actor_name(),
                                  config.message_type,
                                  host_,
                                  port_,
                                  riaps::discovery::Kind::ANS,
                                  (config.is_local?riaps::discovery::Scope::LOCAL:riaps::discovery::Scope::GLOBAL),
                                  {})) {
                throw std::runtime_error("Answerport couldn't be registered.");
            }
        }

        const component_port_ans* AnswerPort::GetConfig() const{
            return (component_port_ans*)GetPortBaseConfig();
        }

        bool AnswerPort::SendAnswer(capnp::MallocMessageBuilder& builder, std::shared_ptr<MessageParams> params) {
            zmsg_t* msg = zmsg_new();

            // Message to query port, first frame must be the SocketId
            zmsg_pushstr(msg, params->GetOriginId().c_str());

            // Original requestId (added in qry-ans)
            zmsg_addstr(msg, params->GetRequestId().c_str());

            zframe_t* userFrame;
            userFrame << builder;

            zmsg_add(msg, userFrame);

            // Has timestamp
            int64_t ztimeStamp;
            if (params->HasTimestamp()) {
                ztimeStamp = zclock_time();
                zmsg_addmem(msg, &ztimeStamp, sizeof(ztimeStamp));
            } else {
                zmsg_addmem(msg, nullptr, 0);
            }
            return Send(&msg);
        }

        AnswerPort* AnswerPort::AsAnswerPort() {
            return this;
        }

        AnswerPort::~AnswerPort() noexcept {

        }

    }
}

