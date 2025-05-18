#ifndef SABV_HPP
#define SABV_HPP

#include <Arduino.h>
#include <Servo.h>

class SABV {
  public:
    SABV(int pin, int open_angle, int closed_angle);
    SABV(const SABV&) = delete;
    SABV(SABV&&) = delete;

    void Setup();
    void Close();
    void Open();

  private:
    int angle_to_useconds(double angle);
    void set(int useconds);

    Servo m_servo;

    int m_pin;
    int m_open_useconds;
    int m_closed_useconds;
};

#endif