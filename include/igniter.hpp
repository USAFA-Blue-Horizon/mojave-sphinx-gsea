#ifndef IGNITER_HPP
#define IGNITER_HPP

#include <Arduino.h>
#include "igniter.hpp"

class Igniter {
    public:
        Igniter(int pin) {
            m_pin = pin;
        }

        void Setup() {
            digitalWrite(m_pin, LOW);
        }

        void Ignite() {
            digitalWrite(m_pin, HIGH);
        }

        void Safe() {
            digitalWrite(m_pin, LOW);
        }

    private:
        int m_pin;
};

#endif