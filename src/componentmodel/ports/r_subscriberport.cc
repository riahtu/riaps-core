#include <componentmodel/ports/r_subscriberport.h>
#include <framework/rfw_network_interfaces.h>

using namespace std;

namespace riaps{
    namespace ports {
        SubscriberPort::SubscriberPort(const component_port_sub &config, const ComponentBase *parentComponent)
                : SubscriberPortBase((component_port_config*)&config, parentComponent) {

        }

        void SubscriberPort::Init() {
            component_port_sub* current_config = (component_port_sub*)GetConfig();
            const string host = (current_config->is_local) ? "127.0.0.1" : riaps::framework::Network::GetIPAddress();

            auto results =
                    subscribeToService(parent_component()->actor()->application_name(),
                                       parent_component()->component_config().component_name,
                                       parent_component()->actor()->actor_name(),
                                         host,
                                         riaps::discovery::Kind::SUB,
                                         (current_config->is_local?riaps::discovery::Scope::LOCAL:riaps::discovery::Scope::GLOBAL),
                                       current_config->port_name, // Subscriber name
                                       current_config->message_type);
            for (auto& result : results) {
                string endpoint = "tcp://" + result.host_name + ":" + to_string(result.port);
                ConnectToPublihser(endpoint);
            }
        }

        SubscriberPort* SubscriberPort::AsSubscribePort() {
            return this;
        }

        SubscriberPort::~SubscriberPort() {

        }
    }

}