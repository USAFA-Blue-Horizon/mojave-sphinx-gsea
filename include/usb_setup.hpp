#ifndef USB_SERIAL_HPP
#define USB_SERIAL_HPP

#include "defines.hpp"

inline void usb_setup() {
    #ifdef DEBUGGING_ENABLED
    Serial.begin(USB_SERIAL_SPEED);
    // TODO: BAD
    while (!Serial);
    #endif

    USB_DEBUG_PRINTLN("I'm all Sphinxed up!");
}

#endif