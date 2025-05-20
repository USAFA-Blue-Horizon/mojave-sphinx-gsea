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

        inline Igniter(int output_pin, int continuity_pin) {
            m_p_output = output_pin;
            m_p_continuity = continuity_pin;
        }

        inline void Setup() {
            pinMode(m_p_output, OUTPUT);
            digitalWrite(m_p_output, LOW);
            pinMode(m_p_continuity, INPUT);
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

        inline E_IgniterState GetCurrentOutputState() {
            return digitalRead(m_p_output) ? E_IgniterState::IGNITE : E_IgniterState::STANDBY;
        }

        inline int GetContinuity() {
            return analogRead(m_p_continuity);
        }

    private:
        inline void write(uint8_t high_or_low) {
            digitalWrite(m_p_output, high_or_low);
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
        int m_p_output;
        int m_p_continuity;
};

#endif