#include <SABV.hpp>

SABV::SABV(int pin, int open_angle, int closed_angle) {
    m_pin = pin;
    m_open_useconds = angle_to_useconds(open_angle);
    m_closed_useconds = angle_to_useconds(closed_angle);
}

void SABV::Setup() {
    m_servo.attach(m_pin);
    Close();
}

void SABV::set(int useconds) {
    if (useconds > 2500) {
        useconds = 2500;
    }
    else if (useconds < 500) {
        useconds = 500;
    }
    m_servo.writeMicroseconds(useconds);
}

void SABV::Close() {
    set(m_closed_useconds);
}

void SABV::Open() {
    set(m_open_useconds);
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