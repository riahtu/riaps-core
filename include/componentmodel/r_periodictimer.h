//
// Created by istvan on 5/2/17.
//

#ifndef RIAPS_CORE_R_PERIODIC_TIMER_H
#define RIAPS_CORE_R_PERIODIC_TIMER_H

#include <componentmodel/r_portbase.h>

#include <czmq.h>

#include <string>



namespace riaps {


    namespace ports {

        void ptimeractor(zsock_t* pipe, void* args);

        class PeriodicTimer : public PortBase {
        public:
            PeriodicTimer(std::string &timerresponsechannel, const _component_port_tim_j& config);

            ~PeriodicTimer();

            virtual const zsock_t* GetSocket() const;

            int GetInterval();

            void stop();

            //void start(int interval, std::function<void(void)> func);
            void start();

            bool is_running() const noexcept;

            virtual PeriodicTimer* AsTimerPort()  ;
            std::string& GetTimerResponseChannel();

        protected:
            std::string _timerresponsechannel;
            zactor_t* _periodicTimerActor;
            ulong _interval;
        };
    }
}

#endif //RIAPS_CORE_R_PERIODIC_TIMER_H