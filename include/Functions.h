#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>

void initPumps();

void initLed();

void water();

void pumpOn(uint8_t pumpPin);

void pumpOff(uint8_t pumpPin);

#endif