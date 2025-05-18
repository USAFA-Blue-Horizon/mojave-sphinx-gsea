#include <Arduino.h>
#include <Servo.h>
#include "defines.hpp"
#include "system.hpp"
#include "usb_serial.hpp"
#include "commands.hpp"
#include "watchdogg.hpp"

void setup() {
  usb_serial_setup();
  USB_DEBUG_PRINTLN("Setup complete");
}

void loop() {
  // If we're armed, we need constant comms with the operator.
  // If the watchdog has died, then we need to flow and disarm
  // TODO: what if we're in the middle of a burn??
  if (System::GetInstance().GetState() != System::E_State::DISARMED) {
    if (watchdogg_dead()) {
      // execute_cmd(E_CMD::STOP_LOADING);
      // execute_cmd(E_CMD::FLOW);
    }
  }

  E_CMD parsed_cmd = E_CMD::NONE;
  if (System::GetInstance().GetRadio()->AttemptRX()) {
    parsed_cmd = parse_command(System::GetInstance().GetRadio()->GetData());
  }

  System::GetInstance().RunStateManager(parsed_cmd);
}