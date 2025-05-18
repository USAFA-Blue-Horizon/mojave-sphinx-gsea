#include "commands.hpp"

E_CMD parse_command(uint8_t* alleged_cmd) {
    // Make sure that last byte is a zero before doing string comparison
    alleged_cmd[RX_MESSAGE_LENGTH] = 0;
    const char* alleged_cmd_string = (const char*)alleged_cmd;
    
    if (strcmp(alleged_cmd_string, CMD_PING) == 0) {
        return E_CMD::PING;
    }
    else if (strcmp(alleged_cmd_string, CMD_DISARM) == 0) {
        return E_CMD::DISARM;
    }
    else if (strcmp(alleged_cmd_string, CMD_ARM) == 0) {
        return E_CMD::ARM;
    }
    else if (strcmp(alleged_cmd_string, CMD_LOAD) == 0) {
        return E_CMD::LOAD;
    }
    else if (strcmp(alleged_cmd_string, CMD_STOP_LOADING) == 0) {
        return E_CMD::STOP_LOADING;
    }
    else if (strcmp(alleged_cmd_string, CMD_FIRE) == 0) {
        return E_CMD::FIRE;
    }
    else if (strcmp(alleged_cmd_string, CMD_FLOW) == 0) {
        return E_CMD::FLOW;
    }
    else if (strcmp(alleged_cmd_string, CMD_CO2_PURGE) == 0) {
        return E_CMD::CO2_PURGE;
    }
    else {
        return E_CMD::NONE;
    }
}

const char* e_cmd_to_string(E_CMD cmd) {
    switch(cmd) {
        case E_CMD::PING:           return "PING";
        case E_CMD::DISARM:         return "DISARM";
        case E_CMD::ARM:            return "ARM";
        case E_CMD::LOAD:           return "LOAD";
        case E_CMD::STOP_LOADING:   return "STOP_LOADING";
        case E_CMD::FIRE:           return "FIRE";
        case E_CMD::FLOW:           return "FLOW";
        case E_CMD::CO2_PURGE:      return "CO2_PURGE";
        case E_CMD::NONE:           return "NONE";
        default:                    return "UNKNOWN_CMD";
    }
}