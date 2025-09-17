#ifndef WATCHDOGG_HPP
#define WATCHDOGG_HPP

#include <Arduino.h>
#include "defines.hpp"

void watchdogg_reset();
bool watchdogg_dead();

#endif