#include <Arduino.h>
#include <Servo.h>
#include "defines.hpp"
#include "system.hpp"
#include "usb_setup.hpp"
#include "commands.hpp"
#include "watchdogg.hpp"


uint32_t tlm_timer;

void setup() {
  usb_setup();
  System::GetInstance().Initialize();
  tlm_timer = millis();
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

  uint32_t now = millis();
  if (now - tlm_timer > TLM_TIMER_WAIT) {
    System::GetInstance().TransmitTelemetry();
    tlm_timer = now;
  }
}