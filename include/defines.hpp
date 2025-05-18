#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <Arduino.h>

// Flags
#define DEBUGGING_ENABLED

// Macro for logging only when when debugging
#ifdef DEBUGGING_ENABLED
#define USB_DEBUG_PRINTLN(message) Serial.println(message);
#else
#define USB_DEBUG_PRINTLN(messge)
#endif

#ifdef DEBUGGING_ENABLED
#define USB_DEBUG_PRINT(message) Serial.print(message);
#else
#define USB_DEBUG_PRINT(messge)
#endif

// Settings
constexpr int USB_SERIAL_SPEED = 115200;
constexpr uint32_t WATCHDOGG_TIMEOUT = 300 * 1000;

// Igniter
constexpr int P_IGNITER                 = 99;

// Loadcell
constexpr int P_LOADCELL_DT             = 99;
constexpr int P_LOADCELL_SCK            = 99;

// Pressure Transducer
constexpr int P_PRESSURE_TRANSDUCER     = A0;

// XBee
#define XBeeSerial Serial2
constexpr int XBEE_SERIAL_SPEED = 115200;
#define RX_MESSAGE_LENGTH 64
constexpr const char* CMD_PING          = "PING----------------------";
constexpr const char* CMD_DISARM        = "DISARM--------------------";
constexpr const char* CMD_ARM           = "ARM-----------------------";
constexpr const char* CMD_LOAD          = "LOAD----------------------";
constexpr const char* CMD_STOP_LOADING  = "STOP_LOADING--------------";
constexpr const char* CMD_FIRE          = "FIRE----------------------";
constexpr const char* CMD_IGNITE        = "IGNITE--------------------";
constexpr const char* CMD_FLOW          = "FLOW----------------------";
constexpr const char* CMD_CO2_PURGE     = "CO2_PURGE-----------------";

// Servos
// Rocket nitrous
constexpr int P_SERVO_ROCKET_NITROUS    = 99;
constexpr int SERVO_ANGLE_OPEN_ROCKET_NITROUS   = 45;
constexpr int SERVO_ANGLE_CLOSED_ROCKET_NITROUS = 10;

// Rocket fuel
constexpr int P_SERVO_ROCKET_FUEL       = 99;
constexpr int SERVO_ANGLE_OPEN_ROCKET_FUEL      = 45;
constexpr int SERVO_ANGLE_CLOSED_ROCKET_FUEL    = 10;

// GSE nitrous
constexpr int P_SERVO_GSE_NITROUS       = 99;
constexpr int SERVO_ANGLE_OPEN_GSE_NITROUS      = 45;
constexpr int SERVO_ANGLE_CLOSED_GSE_NITROUS    = 10;

// GSE CO2
constexpr int P_SERVO_GSE_CO2                   = 99;
constexpr int SERVO_ANGLE_OPEN_GSE_CO2          = 45;
constexpr int SERVO_ANGLE_CLOSED_GSE_CO2        = 10;

#endif