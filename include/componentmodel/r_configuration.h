//
// Created by parallels on 9/7/16.
//

#ifndef RIAPS_FW_R_CONFIGURATION_H
#define RIAPS_FW_R_CONFIGURATION_H

#include <componentmodel/r_parameter.h>

#include <string>
#include <vector>

using namespace riaps::componentmodel;

/**
 * Baseclass for component and group ports. Contains portName - messageType mapping.
 */
struct PortConfigBase {
    std::string port_name;
    std::string message_type;
};

/**
 * Port-message type mapping for groups
 */
struct GroupPortConfig : public PortConfigBase{
};

/**
 * Port-message type mapping for groups
 * Component port can be local.
 */
struct ComponentPortConfig : public PortConfigBase {
    /**
     * True if the port is bound to the localhost.
     */
    bool        is_local;

    /**
     * The first frame of each message is timestamped.
     */
    bool        is_timed;

    ComponentPortConfig(){
        is_local=false;
        is_timed=false;
    }
};


struct ComponentPortClt : public ComponentPortConfig {};
struct ComponentPortPub : public ComponentPortConfig {};

struct ComponentPortReq : public ComponentPortConfig {
    /**
     * Request message type
     */
    std::string req_type;

    /**
     * Response message type
     */
    std::string rep_type;
};

struct ComponentPortRep : public ComponentPortConfig{
    /**
     * Request message type
     */
    std::string req_type;

    /**
     * Response message type
     */
    std::string rep_type;
};
struct ComponentPortSrv : public ComponentPortConfig{};
struct ComponentPortSub : public ComponentPortConfig{
};
struct ComponentPortTim : public ComponentPortConfig {
    ulong period;

    ComponentPortTim() {
        period = 0;
    }
};
struct ComponentPortIns : public ComponentPortConfig{

};

struct ComponentPortQry : public ComponentPortConfig {
    std::string qry_type;
    std::string ans_type;
};

struct ComponentPortAns : public ComponentPortConfig{
    std::string qry_type;
    std::string ans_type;
};

/**
 * Container fol all ports.
 */
struct ComponentPorts {
    std::vector<ComponentPortClt> clts; // Client
    std::vector<ComponentPortSrv> srvs; // Server
    std::vector<ComponentPortPub> pubs; // Publisher
    std::vector<ComponentPortSub> subs; // Subscribe
    std::vector<ComponentPortReq> reqs; // Request
    std::vector<ComponentPortRep> reps; // Response
    std::vector<ComponentPortTim> tims; // Timer
    std::vector<ComponentPortIns> inss; // Inside
    std::vector<ComponentPortQry> qrys; // Query
    std::vector<ComponentPortAns> anss; // Answer
};

/**
 * List of ports for group types
 * Only pub/sub
 */
typedef struct ComponentPortPub GroupPortPub;
typedef struct ComponentPortSub GroupPortSub;
struct groupt_ports {
    std::vector<GroupPortPub> pubs;
    std::vector<GroupPortSub> subs;
};

/**
 * Grouptype configuration
 */
//struct GroupTypeConf {
//    std::string   group_type_id;
//    bool          has_leader;
//};

class GroupConf {
public:
    GroupConf() = default;
    GroupConf(const std::string& tname, const std::string& tkind, const std::string& tmessage, const bool ttimed) :
        name_(tname), kind_(tkind), message_(tmessage), timed_(ttimed) {};

    const std::string& name() const { return name_; }
    const std::string& kind() const { return kind_; }
    const std::string& message() const { return message_; }
    const bool timed() const { return timed_; }
    bool has_leader() const {
        return kind_ != "default";
    };

private:
    std::string name_;
    std::string kind_;
    std::string message_;
    bool timed_;
};

struct ComponentConf {
    std::string               component_name;
    std::string               component_type;
    ComponentPorts            component_ports;
    Parameters                component_parameters;
    bool                      is_device;
};

#endif //RIAPS_FW_R_CONFIGURATION_H
