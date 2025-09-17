#ifndef LOADCELL_HPP
#define LOADCELL_HPP

#include "HX711.h"

class Loadcell {
    public:
        Loadcell(const int dout, const int sck, const float scaling) :
            m_p_dout(dout), m_p_sck(sck), m_scaling(scaling) {}

        void Setup() {
            m_sensor.begin(m_p_dout, m_p_sck);
            m_sensor.set_scale(m_scaling);
        }

        void Tare() {
            m_sensor.tare();
        }

        float GetLoad() {
            if (m_sensor.wait_ready_timeout(100)) {
                return m_sensor.get_units();
            }
            else {
                return -10.26;
            }
        }

    private:
        int m_p_dout;
        int m_p_sck;
        float m_scaling;
        HX711 m_sensor;
};

#endif