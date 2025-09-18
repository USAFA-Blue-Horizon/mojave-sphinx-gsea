// // #include "radio.hpp"

// // bool Radio::AttemptRX() {
// //     if (m_serial->available() > 0) {
// //         int n_rx = m_serial->readBytes(m_rx_buffer, RX_MESSAGE_LENGTH);
// //         if (n_rx != RX_MESSAGE_LENGTH) {
// //             USB_DEBUG_PRINT("Did not receive a full RX message! RXed: ");
// //             USB_DEBUG_PRINT(std::to_string(n_rx).c_str());
// //             USB_DEBUG_PRINT(" bytes");
// //             // USB_DEBUG_PRINT("; message = ");
// //             // for (int i = 0; i < n_rx; i++) {
// //             //     USB_DEBUG_PRINT(m_rx_buffer[i]);
// //             //     USB_DEBUG_PRINT(" ");
// //             // }
// //             USB_DEBUG_PRINTLN("");
// //             return false;
// //         }
// //         return true;
// //     }
// //     return false;
// // }
// // #include <Arduino.h>
// // #include <RH_RF95.h>
// extern data_buffer
// #include <Arduino.h>
// #include <RH_RF95.h>

// // Pin mapping for Teensy + RFM95
// #define RFM95_CS   10   // Chip Select
// #define RFM95_RST  22   // Reset
// #define RFM95_INT   1   // DIO0 (interrupt pin)

// #define RF95_FREQ  915.0   // MHz (set this same on both boards)

// // Create LoRa driver
// RH_RF95 rf95(RFM95_CS, RFM95_INT);

// // Example buffer to send
// // char data_buffer[] = "Telemetry:1234";

// void setup() {
//   Serial.begin(9600);  // For USB serial comms
//   delay(100);

//   // Reset LoRa
//   pinMode(RFM95_RST, OUTPUT);
//   digitalWrite(RFM95_RST, HIGH);
//   delay(10);
//   digitalWrite(RFM95_RST, LOW);
//   delay(10);
//   digitalWrite(RFM95_RST, HIGH);
//   delay(10);

//   if (!rf95.init()) {
//     Serial.println("LoRa init failed!");
//     while (1);
//   }

//   if (!rf95.setFrequency(RF95_FREQ)) {
//     Serial.println("setFrequency failed!");
//     while (1);
//   }

//   // Configure radio
//   rf95.setTxPower(23, false);   // max power
//   rf95.setSpreadingFactor(9);   // SF7..12
//   rf95.setSignalBandwidth(500000); // Hz
//   rf95.setCodingRate4(5);

//   Serial.println("LoRa init OK. Ready!");
// }

// void loop() {
//   // --------------------
//   // 1. SEND DATA
//   // --------------------
//   Serial.print("Sending: ");
//   Serial.println(data_buffer);

//   rf95.send((uint8_t *)data_buffer, strlen(data_buffer));
//   rf95.waitPacketSent();

//   // --------------------
//   // 2. RECEIVE COMMANDS
//   // --------------------
//   if (rf95.available()) {
//     uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
//     uint8_t len = sizeof(buf);

//     if (rf95.recv(buf, &len)) {
//       buf[len] = '\0'; // null terminate
//       Serial.print("Received command: ");
//       Serial.println((char*)buf);

//       // Example: interpret simple commands
//       if (strcmp((char*)buf, "LED_ON") == 0) {
//         digitalWrite(13, HIGH);   // turn on LED
//       } else if (strcmp((char*)buf, "LED_OFF") == 0) {
//         digitalWrite(13, LOW);    // turn off LED
//       }
//     } else {
//       Serial.println("Receive failed");
//     }
//   }

//   delay(1000); // wait 1s between sends
// }


#include "../radio.hpp"

Radio::Radio() : rf95(RFM95_CS, RFM95_INT), rx_len(0) {}

void Radio::Setup() {
    pinMode(RFM95_RST, OUTPUT);

    // Reset pulse
    digitalWrite(RFM95_RST, HIGH);
    delay(10);
    digitalWrite(RFM95_RST, LOW);
    delay(10);
    digitalWrite(RFM95_RST, HIGH);
    delay(10);

    if (!rf95.init()) {
        Serial.println("LoRa init failed!");
        while (1);
    }

    if (!rf95.setFrequency(RF95_FREQ)) {
        Serial.println("LoRa setFrequency failed!");
        while (1);
    }

    rf95.setTxPower(23, false);
    rf95.setSpreadingFactor(9);
    rf95.setSignalBandwidth(500000);
    rf95.setCodingRate4(5);

    Serial.println("LoRa radio initialized");
}

void Radio::TX(uint8_t* data, size_t len) {
    rf95.send(data, len);
    rf95.waitPacketSent();
}

bool Radio::AttemptRX() {
    if (rf95.available()) {
        rx_len = sizeof(rx_buffer);
        if (rf95.recv(rx_buffer, &rx_len)) {
            return true;
        }
    }
    return false;
}

uint8_t* Radio::GetData() {
    return rx_buffer;
}
