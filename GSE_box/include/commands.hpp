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
    TARE_LOADCELL,

    #ifdef MANUAL_COMMAND_OVERRIDE_MODE_DANGEROUS
    GSE_NOX_OPEN,
    GSE_NOX_CLOSE,
    GSE_CO2_OPEN,
    GSE_CO2_CLOSE,
    ROCKET_NOX_OPEN,
    ROCKET_NOX_CLOSE,
    ROCKET_FUEL_OPEN,
    ROCKET_FUEL_CLOSE,
    #endif

    NONE
} E_CMD;

const char* e_cmd_to_string(E_CMD);

E_CMD parse_command(uint8_t*);

#endif