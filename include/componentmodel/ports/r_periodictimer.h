#ifndef RIAPS_CORE_R_PERIODIC_TIMER_H
#define RIAPS_CORE_R_PERIODIC_TIMER_H

#include <componentmodel/ports/r_portbase.h>
#include <componentmodel/ports/r_recvport.h>
#include <czmq.h>
#include <string>



namespace riaps {


    namespace ports {

        void ptimeractor(zsock_t* pipe, void* args);

        class PeriodicTimer : public PortBase, RecvPort {
        public:
            PeriodicTimer(const component_port_tim& config, const ComponentBase* parentComponent);

            void Init();


            virtual const zsock_t* GetSocket() const;

            int interval();
            void Stop();
            void Start();

            bool is_running() const noexcept;

            virtual PeriodicTimer* AsTimerPort() override;
            std::string TimerChannel();

            virtual ~PeriodicTimer();
        protected:
            std::string timer_channel_;
            zactor_t*   timer_actor_;
            ulong       interval_;
        };
    }
}

#endif //RIAPS_CORE_R_PERIODIC_TIMER_H