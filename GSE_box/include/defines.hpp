#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <Arduino.h>

// Flags
#define DEBUGGING_ENABLED

// Macro for logging only when when debugging
#ifdef DEBUGGING_ENABLED
#define USB_DEBUG_PRINTLN(message) Serial.println(message)
#else
#define USB_DEBUG_PRINTLN(messge)
#endif

#ifdef DEBUGGING_ENABLED
#define USB_DEBUG_PRINT(message) Serial.print(message)
#else
#define USB_DEBUG_PRINT(messge)
#endif

// Settings
constexpr int USB_SERIAL_SPEED = 115200;
constexpr uint32_t WATCHDOGG_TIMEOUT = 300 * 1000;
// #define MANUAL_COMMAND_OVERRIDE_MODE_DANGEROUS

// Igniter
constexpr int P_IGNITER_CONTROL         = 41;
constexpr int P_IGNITER_CONTINUITY      = A4;
constexpr int IGNITER_RUNTIME           = 4000;

// Loadcell
constexpr int P_LOADCELL_DT             = 38;
constexpr int P_LOADCELL_SCK            = 39;
constexpr float LOADCELL_SCALING        = 6209.96;

// Pressure Transducer
constexpr int P_PRESSURE_TRANSDUCER     = A13;

// XBee
#define XBeeSerial Serial8
constexpr int XBEE_SERIAL_SPEED = 115200;
constexpr int XBEE_SERIAL_TIMOUT = 50;
#define RX_MESSAGE_LENGTH 26
constexpr const char* CMD_PING          = "PING----------------------";
constexpr const char* CMD_DISARM        = "DISARM--------------------";
constexpr const char* CMD_ARM           = "ARM-----------------------";
constexpr const char* CMD_LOAD          = "LOAD----------------------";
constexpr const char* CMD_STOP_LOADING  = "STOP_LOADING--------------";
constexpr const char* CMD_FIRE          = "FIRE----------------------";
constexpr const char* CMD_FLOW          = "FLOW----------------------";
constexpr const char* CMD_CO2_PURGE     = "CO2_PURGE-----------------";
constexpr const char* CMD_TARE_LOADCELL = "TARE_LOADCELL-------------";

#ifdef MANUAL_COMMAND_OVERRIDE_MODE_DANGEROUS
constexpr const char* CMD_GSE_NOX_OPEN      = "GSE_NOX_OPEN!!!!!!!!!!!!!!";
constexpr const char* CMD_GSE_NOX_CLOSE     = "GSE_NOX_CLOSE!!!!!!!!!!!!!";
constexpr const char* CMD_GSE_CO2_OPEN      = "GSE_CO2_OPEN!!!!!!!!!!!!!!";
constexpr const char* CMD_GSE_CO2_CLOSE     = "GSE_CO2_CLOSE!!!!!!!!!!!!!";
constexpr const char* CMD_ROCKET_NOX_OPEN   = "ROCKET_NOX_OPEN!!!!!!!!!!!";
constexpr const char* CMD_ROCKET_NOX_CLOSE  = "ROCKET_NOX_CLOSE!!!!!!!!!!";
constexpr const char* CMD_ROCKET_FUEL_OPEN  = "ROCKET_FUEL_OPEN!!!!!!!!!!";
constexpr const char* CMD_ROCKET_FUEL_CLOSE = "ROCKET_FUEL_CLOSE!!!!!!!!!";
#endif

// Servos
// Rocket nitrous
constexpr int P_SERVO_ROCKET_NITROUS            = 1;
constexpr int SERVO_ANGLE_OPEN_ROCKET_NITROUS   = 102;
constexpr int SERVO_ANGLE_CLOSED_ROCKET_NITROUS = 27;

// Rocket fuel
constexpr int P_SERVO_ROCKET_FUEL               = 3;
constexpr int SERVO_ANGLE_OPEN_ROCKET_FUEL      = 99;
constexpr int SERVO_ANGLE_CLOSED_ROCKET_FUEL    = 20;

// GSE nitrous
constexpr int P_SERVO_GSE_NITROUS               = 5;
constexpr int SERVO_ANGLE_OPEN_GSE_NITROUS      = 107;
constexpr int SERVO_ANGLE_CLOSED_GSE_NITROUS    = 23;

// GSE CO2
constexpr int P_SERVO_GSE_CO2                   = 7;
constexpr int SERVO_ANGLE_OPEN_GSE_CO2          = 95;
constexpr int SERVO_ANGLE_CLOSED_GSE_CO2        = 17;

// Telemetry
constexpr int MAX_TLM_LENGTH = 128;
constexpr int TLM_TIMER_WAIT = 500; // ms

#endif