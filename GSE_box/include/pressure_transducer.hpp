#ifndef PRESSURE_TRANSDUCER_HPP
#define PRESSURE_TRANSDUCER_HPP

#include <Arduino.h>

class PressureTransducer {
    public:
        PressureTransducer(int pin) : m_pin(pin) {}

        void Setup() {
            pinMode(m_pin, INPUT);
        }

        // V = IR
        // I = V/R
        // V = analogRead() / 1023 * 3.3
        // R = 150 ohms
        // I = analogRead() / 1023 * 3.3 / 150.0
        // I is from 0.004 to 0.020 mA
        // subtract 0.004 from I then divide by (0.020 - 0.004) to get the 0-100% of sensor output
        // I = ((analogRead() / 1023 * 3.3 / 150.0) - 0.004) / 0.016
        // multiply that by the max output of the sensor (1500 psi) to get the psi output
        // I = (((analogRead() / 1023 * 3.3 / 150.0) - 0.004) / 0.016) * 1500
        double Measure() {
            return (((analogRead(m_pin) / 1023.0 * 3.3 / 150.0) - 0.004) / 0.016) * 1500.0;
        }

    private:
        int m_pin;
};

#endif