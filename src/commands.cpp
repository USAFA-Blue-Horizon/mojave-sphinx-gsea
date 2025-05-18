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