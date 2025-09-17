#ifndef SABV_HPP
#define SABV_HPP

#include <Arduino.h>
#include <Servo.h>

class SABV {
  public:
    typedef enum {
      CLOSED,
      OPEN
    } E_SABV_State;

    static inline const char* e_sabv_state_to_string(E_SABV_State state) {
      if (state == E_SABV_State::CLOSED) return "CLOSED";
      else return "OPEN";
    }

    SABV(int pin, int open_angle, int closed_angle);
    SABV(const SABV&) = delete;
    SABV(SABV&&) = delete;

    void Setup();
    void Close();
    void Open();

    E_SABV_State GetCommandedState();

  private:
    int angle_to_useconds(double);
    void write(int);
    void set(E_SABV_State);

    Servo m_servo;

    int m_pin;
    int m_open_useconds;
    int m_closed_useconds;

    E_SABV_State m_commanded_state;
};

#endif