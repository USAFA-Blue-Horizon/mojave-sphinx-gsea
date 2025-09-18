#include "system.hpp"

const char* System::e_state_to_string(E_State state) {
    switch(state) {
        case E_State::DISARMED:         return "DISARMED";
        case E_State::ARMED:            return "ARMED";
        case E_State::LOADING:          return "LOADING";
        case E_State::LOADED:           return "LOADED";
        case E_State::FLOW:             return "FLOW";
        case E_State::FIRE:             return "FIRE";
        case E_State::CO2_PURGE:        return "CO2_PURGE";
        
        #ifdef MANUAL_COMMAND_OVERRIDE_MODE_DANGEROUS
        case E_State::MANUAL_OVERRIDE:  return "MANUAL_OVERRIDE";
        #endif

        default:                    return "UNKNOWN_STATE";
    }
}

void System::execute_cmd(E_CMD cmd) {
    USB_DEBUG_PRINTLN(
        std::string(
            std::string("Executing command: ") +
            e_cmd_to_string(cmd)
        ).c_str()
    );

    switch(cmd) {
        case E_CMD::PING: {
            watchdogg_reset();
            break;
        }
        case E_CMD::DISARM: {
            CloseAllValves();
            break;
        }
        case E_CMD::ARM: {
            // Arming merely changes states :(
            break;
        }
        case E_CMD::LOAD: {
            StartLoading();
            break;
        }
        case E_CMD::STOP_LOADING: {
            StopLoading();
            break;
        }
        case E_CMD::FIRE: {
            Fire();
            break;
        }
        case E_CMD::FLOW: {
            Flow();
            break;
        }
        case E_CMD::CO2_PURGE: {
            StartCO2Purge();
            break;
        }
        case E_CMD::TARE_LOADCELL: {
            m_loadcell.Tare();
            break;
        }

        #ifdef MANUAL_COMMAND_OVERRIDE_MODE_DANGEROUS
        case E_CMD::GSE_NOX_OPEN: {
            m_valve_gse_nitrous.Open();
            break;
        }
        case E_CMD::GSE_NOX_CLOSE: {
            m_valve_gse_nitrous.Close();
            break;
        }
        case E_CMD::GSE_CO2_OPEN: {
            m_valve_gse_co2.Open();
            break;
        }
        case E_CMD::GSE_CO2_CLOSE: {
            m_valve_gse_co2.Close();
            break;
        }
        case E_CMD::ROCKET_NOX_OPEN: {
            m_valve_rocket_nitrous.Open();
            break;
        }
        case E_CMD::ROCKET_NOX_CLOSE: {
            m_valve_rocket_nitrous.Close();
            break;
        }
        case E_CMD::ROCKET_FUEL_OPEN: {
            m_valve_rocket_fuel.Open();
            break;
        }
        case E_CMD::ROCKET_FUEL_CLOSE: {
            m_valve_rocket_fuel.Close();
            break;
        }
        #endif

        case E_CMD::NONE: {
            break;
        }
        default: {
            USB_DEBUG_PRINTLN("Cannot execute unknown command");
            break;
        }
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
    m_state = new_state;
}

void System::Initialize() {
    m_valve_gse_nitrous.Setup();
    m_valve_gse_co2.Setup();
    m_valve_rocket_nitrous.Setup();
    m_valve_rocket_fuel.Setup();
    m_igniter.Setup();
    m_loadcell.Setup();
    m_pt.Setup();
    m_radio.Setup();
}

void System::RunStateManager(E_CMD cmd) {
    #ifdef MANUAL_COMMAND_OVERRIDE_MODE_DANGEROUS
    if (cmd != E_CMD::NONE) {
        execute_cmd(cmd);
    }
    return;
    #endif

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
        case System::E_State::FIRE: {
            run_fire(cmd);
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
            " because the current state is " +
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
        case E_CMD::TARE_LOADCELL: {
            execute_cmd(cmd);
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
            set_state(E_State::FIRE);
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

void System::run_fire(E_CMD cmd) {
    if (m_igniter_littime == -1) {
        m_igniter_littime = millis();
    }

    if (millis() - m_igniter_littime >= IGNITER_RUNTIME) {
        m_igniter.Standby();
        m_igniter_littime = -1;
        set_state(E_State::FLOW);
    }

    switch (cmd) {
        case E_CMD::NONE: {
            break;
        }
        default: {
            debug_unauth_cmd(cmd);
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

void System::TransmitTelemetry() {
    static uint8_t data_buffer[MAX_TLM_LENGTH] = { 0 };

    // memset(data_buffer, 0, MAX_TLM_LENGTH);
    // std::stringstream tlm_string;
    // tlm_string
    //     << millis() << ","
    //     << e_state_to_string(GetState()) << ","
    //     << SABV::e_sabv_state_to_string(m_valve_gse_nitrous.GetCommandedState()) << ","
    //     << SABV::e_sabv_state_to_string(m_valve_gse_co2.GetCommandedState()) << ","
    //     << SABV::e_sabv_state_to_string(m_valve_rocket_nitrous.GetCommandedState()) << ","
    //     << SABV::e_sabv_state_to_string(m_valve_rocket_fuel.GetCommandedState()) << ","
    //     << Igniter::e_igniterstate_to_string(m_igniter.GetCurrentOutputState()) << ","
    //     << Igniter::e_igniterstate_to_string(m_igniter.GetCommandedState()) << ","
    //     << m_igniter.GetContinuity() << ","
    //     << m_loadcell.GetLoad() << ","
    //     << m_pt.Measure();
    
    // const char* as_chr = tlm_string.str().c_str();

std::stringstream tlm_string;
tlm_string
    << millis() << ","
    << e_state_to_string(GetState()) << ","
    << SABV::e_sabv_state_to_string(m_valve_gse_nitrous.GetCommandedState()) << ","
    << SABV::e_sabv_state_to_string(m_valve_gse_co2.GetCommandedState()) << ","
    << SABV::e_sabv_state_to_string(m_valve_rocket_nitrous.GetCommandedState()) << ","
    << SABV::e_sabv_state_to_string(m_valve_rocket_fuel.GetCommandedState()) << ","
    << Igniter::e_igniterstate_to_string(m_igniter.GetCurrentOutputState()) << ","
    << Igniter::e_igniterstate_to_string(m_igniter.GetCommandedState()) << ","
    << m_igniter.GetContinuity() << ","
    << m_loadcell.GetLoad() << ","
    << m_pt.Measure();

std::string tlm_std = tlm_string.str();   // keep the std::string alive
const char* as_chr = tlm_std.c_str();
size_t len = tlm_std.size();
uint8_t* data = (uint8_t*)as_chr;

USB_DEBUG_PRINTLN(as_chr);

uint8_t checksum = 0;
for (size_t i = 0; i < len; i++) {
    checksum ^= data[i];
}

    int n_to_copy;
    if (len > MAX_TLM_LENGTH - 1) {
        USB_DEBUG_PRINT("TLM string too long; length = ");
        USB_DEBUG_PRINT(std::to_string(len).c_str());
        USB_DEBUG_PRINTLN(" bytes; max = ");
        USB_DEBUG_PRINT(std::to_string(MAX_TLM_LENGTH).c_str());
        USB_DEBUG_PRINTLN(" bytes");
        n_to_copy = MAX_TLM_LENGTH - 1;
    }
    else {
        n_to_copy = len;
    }

    memcpy(data_buffer, data, n_to_copy);
    data_buffer[n_to_copy] = checksum;

    m_radio.TX(data_buffer, n_to_copy + 1);
}