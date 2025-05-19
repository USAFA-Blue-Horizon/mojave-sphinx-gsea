#include "radio.hpp"

bool Radio::AttemptRX() {
    if (m_serial->available() > 0) {
        int n_rx = m_serial->readBytes(m_rx_buffer, RX_MESSAGE_LENGTH);
        if (n_rx != RX_MESSAGE_LENGTH) {
            USB_DEBUG_PRINT("Did not receive a full RX message! RXed: ");
            USB_DEBUG_PRINT(std::to_string(n_rx).c_str());
            USB_DEBUG_PRINTLN(" bytes");
            return false;
        }
        return true;
    }
    return false;
}