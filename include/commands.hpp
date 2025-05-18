#ifndef commands_HPP
#define commands_HPP

#include <Arduino.h>
#include "defines.hpp"
#include "system.hpp"
#include "watchdogg.hpp"

typedef enum {
    PING,
    DISARM,
    ARM,
    LOAD,
    STOP_LOADING,
    FIRE,
    FLOW,
    CO2_PURGE,
    NONE
} E_CMD;

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

E_CMD parse_command(uint8_t* alleged_cmd);

void execute_cmd(E_CMD cmd) {
    USB_DEBUG_PRINT(
        std::string(
            std::string("Executing command: ") +
            e_cmd_to_string(cmd)
        ).c_str()
    );

    switch(cmd) {
        case E_CMD::PING: {
            watchdogg_reset();
            break;
        }
        case E_CMD::DISARM: {
            System::GetInstance().CloseAllValves();
            break;
        }
        case E_CMD::ARM: {
            // Arming merely changes states :(
            break;
        }
        case E_CMD::LOAD: {
            System::GetInstance().StartLoading();
            break;
        }
        case E_CMD::STOP_LOADING: {
            System::GetInstance().StopLoading();
            break;
        }
        case E_CMD::FIRE: {
            System::GetInstance().Fire();
            break;
        }
        case E_CMD::FLOW: {
            System::GetInstance().Flow();
            break;
        }
        case E_CMD::CO2_PURGE: {
            System::GetInstance().StartCO2Purge();
            break;
        }
        case E_CMD::NONE: {
            break;
        }
        default: {
            USB_DEBUG_PRINTLN("Cannot execute unknown command");
            break;
        }
    }
}

#endif