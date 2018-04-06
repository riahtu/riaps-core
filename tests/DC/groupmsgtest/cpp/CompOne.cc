#include <CompOne.h>

namespace groupmsgtest {
   namespace components {
      
      CompOne::CompOne(_component_conf &config, riaps::Actor &actor) :
      CompOneBase(config, actor), m_joinedToA(false) {
          _logger->set_pattern("[%n] %v");
      }
      
      void CompOne::OnClock(riaps::ports::PortBase *port) {
         if (!m_joinedToA){
             _logger->info("Component joins to {}:{}", groupIdA.groupTypeId, groupIdA.groupName);
            auto joined = JoinGroup(groupIdA);
            if (joined){
                m_joinedToA = true;
            }
            _logger->error_if(!joined, "Couldn't join to group {}:{}", groupIdA.groupTypeId, groupIdA.groupName);
         } else {
             capnp::MallocMessageBuilder builder;
             auto grpMsg = builder.initRoot<MessageType>();
             auto msgContent = fmt::format("{}", GetComponentName());
             grpMsg.setMsg(msgContent);
             _logger->error_if(!SendGroupMessage(groupIdA, builder), "{} couldn't send groupmessage", GetComponentName());
         }
      }
    
      
      void CompOne::OnGroupMessage(const riaps::groups::GroupId& groupId, capnp::FlatArrayMessageReader& capnpreader, riaps::ports::PortBase* port){
          logGroupMessage(_logger, __FUNCTION__, groupId, capnpreader.getRoot<MessageType>().getMsg());
      }
      
      CompOne::~CompOne() {
         
      }
   }
}

riaps::ComponentBase *create_component(_component_conf &config, riaps::Actor &actor) {
   auto result = new groupmsgtest::components::CompOne(config, actor);
   return result;
}

void destroy_component(riaps::ComponentBase *comp) {
   delete comp;
}
