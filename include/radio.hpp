#ifndef RADIO_HPP
#define RADIO_HPP

#include <Arduino.h>
#include "defines.hpp"
#include <string>

class Radio {
    public:
        Radio(HardwareSerial* serial, int baudrate) {
            m_serial = serial;
            m_baudrate = baudrate;
        }

        void Setup() {
            m_serial->begin(m_baudrate);
            m_serial->setTimeout(XBEE_SERIAL_TIMOUT);
            // TODO: this is super dangerous!
            while (!m_serial);
        }

        void TX(uint8_t* data, int length) {
            m_serial->write(data, length);
        }

        bool AttemptRX();

        uint8_t* GetData() {
            return m_rx_buffer;
        }
        
    private:
        uint8_t* m_rx;
        int m_baudrate;
        HardwareSerial* m_serial;
        uint8_t m_rx_buffer[RX_MESSAGE_LENGTH + 1];
};

#endif