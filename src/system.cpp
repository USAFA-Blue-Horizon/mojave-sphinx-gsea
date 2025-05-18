#include "system.hpp"

const char* System::e_state_to_string(E_State state) {
    switch(state) {
        case E_State::DISARMED:     return "DISARMED";
        case E_State::ARMED:        return "ARMED";
        case E_State::LOADING:      return "LOADING";
        case E_State::LOADED:       return "LOADED";
        case E_State::FLOW:         return "FLOW";
        case E_State::CO2_PURGE:    return "CO2_PURGE";
        default:                    return "UNKNOWN_STATE";
    }
}

void System::set_state(E_State new_state) {
    USB_DEBUG_PRINTLN(
        std::string(
            std::string("Transitioning states from ") +
            e_state_to_string(System::GetInstance().GetState()) +
            " to " +
            e_state_to_string(new_state)
        ).c_str()
    );
}

void System::Initialize() {
    m_valve_gse_nitrous.Setup();
    m_valve_gse_co2.Setup();
    m_valve_rocket_nitrous.Setup();
    m_valve_rocket_fuel.Setup();
    m_igniter.Setup();
    m_radio.Setup();
}

void System::RunStateManager(E_CMD cmd) {
    switch (System::GetInstance().GetState()) {
        case System::E_State::DISARMED: {
            run_disarmed(cmd);
            break;
        }
        case System::E_State::ARMED: {
            run_armed(cmd);
            break;
        }
        case System::E_State::LOADING: {
            run_loading(cmd);
            break;
        }
        case System::E_State::LOADED: {
            run_loaded(cmd);
            break;
        }
        case System::E_State::FLOW: {
            run_flow(cmd);
            break;
        }
        case System::E_State::CO2_PURGE: {
            run_co2_purge(cmd);
            break;
        }
        default: {
            break;
        }
    }
}

void System::debug_unauth_cmd(E_CMD cmd) {
    USB_DEBUG_PRINTLN(
        std::string(
            std::string("Cannot run command") +
            e_cmd_to_string(cmd) +
            "because the current state is " +
            System::e_state_to_string(GetState())
        ).c_str()
    );
}

void System::run_disarmed(E_CMD cmd) {
    switch(cmd) {
        case E_CMD::ARM: {
            execute_cmd(cmd);
            set_state(E_State::ARMED);
            break;
        }
        case E_CMD::NONE: {
            break;
        }
        default: {
            debug_unauth_cmd(cmd);
            break;
        }
    }
}

void System::run_armed(E_CMD cmd) {
    switch(cmd) {
        case E_CMD::DISARM: {
            execute_cmd(cmd);
            set_state(E_State::DISARMED);
            break;
        }
        case E_CMD::LOAD: {
            execute_cmd(cmd);
            set_state(E_State::LOADING);
            break;
        }
        case E_CMD::FLOW: {
            execute_cmd(cmd);
            set_state(E_State::FLOW);
            break;
        }
        case E_CMD::NONE: {
            break;
        }
        default: {
            debug_unauth_cmd(cmd);
            break;
        }
    }
}

void System::run_loading(E_CMD cmd) {
    switch(cmd) {
        case E_CMD::STOP_LOADING: {
            execute_cmd(cmd);
            set_state(E_State::LOADED);
            break;
        }
        case E_CMD::NONE: {
            break;
        }
        default: {
            debug_unauth_cmd(cmd);
            break;
        }
    }
}

void System::run_loaded(E_CMD cmd) {
    switch(cmd) {
        case E_CMD::FIRE: {
            execute_cmd(cmd);
            set_state(E_State::FLOW);
            break;
        }
        case E_CMD::FLOW: {
            execute_cmd(cmd);
            set_state(E_State::FLOW);
            break;
        }
        case E_CMD::NONE: {
            break;
        }
        default: {
            debug_unauth_cmd(cmd);
            break;
        }
    }
}

void System::run_flow(E_CMD cmd) {
    switch(cmd) {
        case E_CMD::CO2_PURGE: {
            execute_cmd(cmd);
            set_state(E_State::CO2_PURGE);
            break;
        }
        case E_CMD::DISARM: {
            execute_cmd(cmd);
            set_state(E_State::DISARMED);
            break;
        }
        case E_CMD::NONE: {
            break;
        }
        default: {
            debug_unauth_cmd(cmd);
            break;
        }
    }
}

void System::run_co2_purge(E_CMD cmd) {
    switch(cmd) {
        case E_CMD::DISARM: {
            execute_cmd(cmd);
            set_state(E_State::DISARMED);
            break;
        }
        case E_CMD::NONE: {
            break;
        }
        default: {
            debug_unauth_cmd(cmd);
            break;
        }
    }
}