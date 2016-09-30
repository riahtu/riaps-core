//
// Created by istvan on 9/30/16.
//

#ifndef RIAPS_FW_COMP_SUB_H
#define RIAPS_FW_COMP_SUB_H

#include "messages.h"
#include "componentmodel/r_componentbase.h"

#include <czmq.h>

#include <random>
#include <string>
#include <vector>

class component_sub : public riaps::ComponentBase {

public:

    component_sub(component_conf& config);

    virtual void OnMessageArrived(std::string messagetype, zmsg_t* msg_body);

    virtual void OnTimerFired(std::string timerid);

    void init();

    virtual ~component_sub();

};


#endif //RIAPS_FW_COMP_SUB_H
