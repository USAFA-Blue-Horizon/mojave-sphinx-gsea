// #ifndef RADIO_HPP
// #define RADIO_HPP

// #include <Arduino.h>
// #include "defines.hpp"
// #include <string>

// class Radio {
//     public:
//         Radio(HardwareSerial* serial, int baudrate) {
//             m_serial = serial;
//             m_baudrate = baudrate;
//         }

//         void Setup() {
//             m_serial->begin(m_baudrate);
//             m_serial->setTimeout(XBEE_SERIAL_TIMOUT);
//         }

//         void TX(uint8_t* data, int length) {
//             m_serial->write(data, length);
//         }

//         bool AttemptRX();

//         uint8_t* GetData() {
//             return m_rx_buffer;
//         }
        
//     private:
//         uint8_t* m_rx;
//         int m_baudrate;
//         HardwareSerial* m_serial;
//         uint8_t m_rx_buffer[RX_MESSAGE_LENGTH + 1];
// };

// #endif

#pragma once

#include <Arduino.h>
#include <RH_RF95.h>

// LoRa pin configuration (adjust for your Teensy wiring)
#define RFM95_CS   10
#define RFM95_RST  22
#define RFM95_INT  1
#define RF95_FREQ  915.0

class Radio {
public:
    Radio();
    void Setup();                                     // initialize LoRa
    void TX(uint8_t* data, size_t len);               // send telemetry
    bool AttemptRX();                                 // check if data received
    uint8_t* GetData();                               // pointer to received data

private:
    RH_RF95 rf95;
    static const uint16_t BUFFER_LEN = RH_RF95_MAX_MESSAGE_LEN;
    uint8_t rx_buffer[BUFFER_LEN];   // stores last received packet
    uint8_t rx_len;
};
