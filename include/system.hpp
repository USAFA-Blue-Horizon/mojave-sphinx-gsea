#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "defines.hpp"
#include "SABV.hpp"
#include "igniter.hpp"
#include "radio.hpp"
#include "commands.hpp"
#include <string>

class System {
    public:
        typedef enum {
            DISARMED,
            ARMED,
            LOADING,
            LOADED,
            FLOW,
            CO2_PURGE
        } E_State;

        static const char* e_state_to_string(E_State);

        System(const System&) = delete;
        System(System&&) = delete;
        System& operator= (const System&) = delete;
        System& operator= (System&&) = delete;

        static System& GetInstance() {
            static System instance;
            return instance;
        }

        E_State GetState() {
            return m_state;
        }

        Radio* GetRadio() {
            return &m_radio;
        }

        void Initialize();

        void RunStateManager(E_CMD cmd);

        void CloseAllValves() {
            m_valve_gse_nitrous.Close();
            m_valve_gse_co2.Close();
            m_valve_rocket_nitrous.Close();
            m_valve_rocket_fuel.Close();
        }

        void StartLoading() {
            m_valve_gse_nitrous.Open();
        }

        void StopLoading() {
            m_valve_gse_nitrous.Close();
        }

        void Fire() {
            m_igniter.Ignite();
            m_valve_rocket_nitrous.Open();
            m_valve_rocket_fuel.Open();
        }

        void Ignite() {
            m_igniter.Ignite();
        }

        void Flow() {
            m_valve_rocket_nitrous.Open();
            m_valve_rocket_fuel.Open();
        }

        void StartCO2Purge() {
            m_valve_gse_co2.Open();
        }

        void StopCO2Purge() {
            m_valve_gse_co2.Close();
        }

    private:
        ~System() = default;
        System() :
        m_valve_gse_nitrous(
            P_SERVO_GSE_NITROUS,
            SERVO_ANGLE_OPEN_GSE_NITROUS,
            SERVO_ANGLE_CLOSED_GSE_NITROUS
        ),
        m_valve_gse_co2(
            P_SERVO_GSE_CO2,
            SERVO_ANGLE_OPEN_GSE_CO2,
            SERVO_ANGLE_CLOSED_GSE_CO2
        ),
        m_valve_rocket_nitrous(
            P_SERVO_ROCKET_NITROUS,
            SERVO_ANGLE_OPEN_ROCKET_NITROUS,
            SERVO_ANGLE_CLOSED_ROCKET_NITROUS
        ),
        m_valve_rocket_fuel(
            P_SERVO_ROCKET_FUEL,
            SERVO_ANGLE_OPEN_ROCKET_FUEL,
            SERVO_ANGLE_CLOSED_ROCKET_FUEL
        ),
        m_igniter(P_IGNITER),
        m_radio(&XBeeSerial, XBEE_SERIAL_SPEED),
        m_state(E_State::DISARMED) {};

        SABV m_valve_gse_nitrous;
        SABV m_valve_gse_co2;
        SABV m_valve_rocket_nitrous;
        SABV m_valve_rocket_fuel;
        Igniter m_igniter;
        Radio m_radio;
        E_State m_state;

        void set_state(E_State new_state);

        void run_disarmed(E_CMD cmd);
        void run_armed(E_CMD cmd);
        void run_loading(E_CMD cmd);
        void run_loaded(E_CMD cmd);
        void run_flow(E_CMD cmd);
        void run_co2_purge(E_CMD cmd);

        void debug_unauth_cmd(E_CMD cmd);
};

#endif