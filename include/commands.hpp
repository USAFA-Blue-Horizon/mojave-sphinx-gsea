#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <Arduino.h>
#include "defines.hpp"
#include "watchdogg.hpp"
#include <string>

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

const char* e_cmd_to_string(E_CMD);

E_CMD parse_command(uint8_t*);

#endif