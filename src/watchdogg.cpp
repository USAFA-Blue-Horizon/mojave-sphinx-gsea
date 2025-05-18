#include "watchdogg.hpp"

uint32_t last_reset = 0;
bool started = false;

void watchdogg_reset() {
    if (!started) {
        started = true;
    }
    last_reset = millis();
}

bool watchdogg_dead() {
    return millis() - last_reset >= WATCHDOGG_TIMEOUT;
}