#ifndef IGNITER_HPP
#define IGNITER_HPP

#include <Arduino.h>
#include "igniter.hpp"

class Igniter {
    public:
        typedef enum {
            STANDBY,
            IGNITE
        } E_IgniterState;

        static inline const char* e_igniterstate_to_string(E_IgniterState state) {
            if (state == E_IgniterState::STANDBY) return "STANDBY";
            else return "IGNITE";
        }

        inline Igniter(int pin) {
            m_pin = pin;
        }

        inline void Setup() {
            digitalWrite(m_pin, LOW);
        }

        inline void Ignite() {
            set(E_IgniterState::IGNITE);
        }

        inline void Standby() {
            set(E_IgniterState::STANDBY);
        }

        inline E_IgniterState GetCommandedState() {
            return m_commanded_state;
        }

        inline E_IgniterState GetCurrentState() {
            return digitalRead(m_pin) ? E_IgniterState::IGNITE : E_IgniterState::STANDBY;
        }

    private:
        inline void write(uint8_t high_or_low) {
            digitalWrite(m_pin, high_or_low);
        }

        inline void set(E_IgniterState state) {
            if (state == E_IgniterState::STANDBY) {
                write(LOW);
            }
            else {
                write(HIGH);
            }
            m_commanded_state = state;
        }

        E_IgniterState m_commanded_state;
        int m_pin;
};

#endif