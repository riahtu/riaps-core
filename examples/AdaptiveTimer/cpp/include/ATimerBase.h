//
// Auto-generated by edu.vanderbilt.riaps.generator.ComponenetGenerator.xtend
//

#ifndef RIAPS_CORE_ATIMER_H
#define RIAPS_CORE_ATIMER_H

#include "componentmodel/r_componentbase.h"

// Name of the ports from the model file
#define PORT_TIMER_CLOCK "clock"

namespace adaptivetimer {
   namespace components {
      
      class ATimerBase : public riaps::ComponentBase {
         
         public:
         ATimerBase(_component_conf &config, riaps::Actor &actor);
         
         virtual void OnClock(riaps::ports::PortBase *port)=0;
         
         virtual ~ATimerBase();
         protected:
         virtual void DispatchMessage(capnp::FlatArrayMessageReader* capnpreader, riaps::ports::PortBase *port,std::shared_ptr<riaps::MessageParams> params=nullptr );
         virtual void DispatchInsideMessage(zmsg_t* zmsg, riaps::ports::PortBase* port);
      };
   }
}
#endif //RIAPS_CORE_ATIMER_H
