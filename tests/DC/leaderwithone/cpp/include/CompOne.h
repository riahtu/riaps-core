//
// Auto-generated by edu.vanderbilt.riaps.generator.ComponenetGenerator.xtend
//
#ifndef RIAPS_FW_COMPONE_H
#define RIAPS_FW_COMPONE_H

#include "CompOneBase.h"
#include "common.h"
#include "MessageType.capnp.h"

namespace leaderwithone {
   namespace components {
      
      class CompOne : public CompOneBase {
         
         public:
         
         CompOne(_component_conf &config, riaps::Actor &actor);
         
         virtual void OnClock(riaps::ports::PortBase *port);
         
         void OnGroupMessage(const riaps::groups::GroupId& groupId, capnp::FlatArrayMessageReader& capnpreader, riaps::ports::PortBase* port);
         
         virtual ~CompOne();
         private:
         bool m_joinedToA;
         
         
      };
   }
}

extern "C" riaps::ComponentBase* create_component(_component_conf&, riaps::Actor& actor);
extern "C" void destroy_component(riaps::ComponentBase*);


#endif //RIAPS_FW_COMPONE_H
