#include <SABV.hpp>
#include <cmath>

SABV::SABV(int pin, int open_angle, int closed_angle) : m_commanded_state(E_SABV_State::CLOSED) {
    m_pin = pin;
    m_open_useconds = angle_to_useconds(open_angle);
    m_closed_useconds = angle_to_useconds(closed_angle);
}

void SABV::Setup() {
    m_servo.attach(m_pin);
    Close();
}

void SABV::set(E_SABV_State state) {
    if (state == E_SABV_State::CLOSED) {
        write(m_closed_useconds);
    }
    else {
        write(m_open_useconds);
    }
    m_commanded_state = state;
}

void SABV::write(int useconds) {
    if (useconds > 2500) {
        useconds = 2500;
    }
    else if (useconds < 500) {
        useconds = 500;
    }
    m_servo.writeMicroseconds(useconds);
}

void SABV::Close() {
    set(E_SABV_State::CLOSED);
}

void SABV::Open() {
    set(E_SABV_State::OPEN);
}

int SABV::angle_to_useconds(double angle) {
    int useconds = round((2500-500) * (angle / 300.0) + 500);
    if (useconds > 2500) {
        useconds = 2500;
    }
    else if (useconds < 500) {
        useconds = 500;
    }

    return useconds;
}

SABV::E_SABV_State SABV::GetCommandedState() {
    return m_commanded_state;
}