/*
 * Simple plant watering solution
 *
 * Amount of connected pumps: 3
 * Pump type: AD20P-1230C
 * Pump specs:
 *  - 12VDC
 *  - Hmax 300cm
 *  - Qmax 240L/H(66ml/s)
 *  - Qreal 180L/H(50ml/s)
 */

#include <Arduino.h>
#include <SimpleTimer.h>

#include "Functions.h"

#define PUMP1PIN 2
#define PUMP2PIN 3
// Uncomment to enable 3rd pump
// #define PUMP3PIN 4
#define LEDPIN   LED_BUILTIN

SimpleTimer timer;

/* pump1 - est water amount: 500ml - time in seconds */
uint8_t pump1WaterDuration = 10;
/* pump2 - est water amount: 500ml - time in seconds */
uint8_t pump2WaterDuration = 10;
/* pump3 - est water amount: 350ml - time in seconds */
// Uncomment to enable 3rd pump
// uint8_t pump3WaterDuration = 7;

/* water each 5 days - value in seconds */
// TODO: revert back valid values
// uint32_t waterInterval = 5L * 24L * 60L * 60L;
uint32_t waterInterval = 30 * 60;

/* delay between pumps - value in seconds */
uint8_t interPumpDelay =  5;

/***************************************************/

/*********/
/* SETUP */
/*********/
void setup() {

  // init Serial for logging and say Hi
  Serial.begin(115200);
  Serial.println("Arduino is up. Hey there!");

  initPumps();
  initLed();

  Serial.println("Watering interval is " + String(waterInterval) + "s");

  timer.setInterval(waterInterval * 1000, water);

}

/********/
/* LOOP */
/********/
void loop() {

  timer.run();

}

/***************************************************/

/*************/
/* FUNCTIONS */
/*************/
void initPumps() {
  pinMode(PUMP1PIN, OUTPUT);
  digitalWrite(PUMP1PIN, LOW);
  pinMode(PUMP2PIN, OUTPUT);
  digitalWrite(PUMP2PIN, LOW);
  // Uncomment to enable 3rd pump
  // pinMode(PUMP3PIN, OUTPUT);
  // digitalWrite(PUMP3PIN, LOW);
}

void initLed() {
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);
}

void water() {
  uint8_t prevDuration;

  // TODO: use loop here

  pumpOn(PUMP1PIN);
  timer.setTimeout(pump1WaterDuration * 1000, []{ pumpOff(PUMP1PIN); });
  prevDuration = pump1WaterDuration;

  timer.setTimeout((prevDuration + interPumpDelay) * 1000, []{ pumpOn(PUMP2PIN); });
  prevDuration = prevDuration + interPumpDelay;
  timer.setTimeout((prevDuration + pump2WaterDuration) * 1000, []{ pumpOff(PUMP2PIN); });
  prevDuration = prevDuration + pump2WaterDuration;

  // Uncomment to enable 3rd pump
  // timer.setTimeout((prevDuration + interPumpDelay) * 1000, []{ pumpOn(PUMP3PIN); });
  // prevDuration = prevDuration + interPumpDelay;
  // timer.setTimeout((prevDuration + pump3WaterDuration) * 1000, []{ pumpOff(PUMP3PIN); });
}

void pumpOn(uint8_t pumpPin) {
  String log;

  digitalWrite(LEDPIN, HIGH);
  digitalWrite(pumpPin, HIGH);
  log = "Pump " + String(pumpPin - 1) + " is on";
  Serial.println(log);
}

void pumpOff(uint8_t pumpPin) {
  String log;

  digitalWrite(pumpPin, LOW);
  log = "Pump " + String(pumpPin - 1) + " is off";
  Serial.println(log);
  digitalWrite(LEDPIN, LOW);
}
