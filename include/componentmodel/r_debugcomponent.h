//
// Created by istvan on 11/25/16.
//

#ifndef RIAPS_FW_R_DEBUGCOMPONENT_H
#define RIAPS_FW_R_DEBUGCOMPONENT_H

#include "r_componentbase.h"

// This component prints the arrived messages to the consol.
// Ports definitions come from the json file.
class DebugComponent : public riaps::ComponentBase {
public:
    DebugComponent(_component_conf_j& config, riaps::Actor& actor);

    virtual void OnMessageArrived(std::string messagetype, zmsg_t* msg_body, zsock_t* socket);

    virtual void OnTimerFired(std::string timerid);

    virtual ~DebugComponent();
};

#endif //RIAPS_FW_R_DEBUGCOMPONENT_H
