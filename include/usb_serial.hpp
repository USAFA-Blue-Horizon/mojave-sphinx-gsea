#ifndef USB_SERIAL_HPP
#define USB_SERIAL_HPP

#include "defines.hpp"

void usb_serial_setup() {
    #ifdef DEBUGGING_ENABLED
    Serial.begin(USB_SERIAL_SPEED);
    #endif

    USB_DEBUG_PRINTLN("I'm all Sphinxed up!");
}

#endif