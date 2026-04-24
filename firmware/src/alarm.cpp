#include "alarm.hpp"

#ifndef BUILD_TEST_ESP8266
// Building for PCB
#define RELAY_1 14
#define RELAY_2 12
#define RELAY_3 13
#else
// Building for test ESP8266
#define RELAY_1 14
#define RELAY_2 12
#define RELAY_3 13
#endif

void alarm_init() {
    pinMode(RELAY_1, OUTPUT);
    pinMode(RELAY_2, OUTPUT);
    pinMode(RELAY_3, OUTPUT);
}

void alarm_loop(State& state) {
    
}