#include "includes.hpp"
#include "state.hpp"

#ifndef BUILD_TEST_ESP8266
// Building for PCB
#define BTN_L 6
#define BTN_R 7
#else
// Building for test ESP8266
#define BTN_L 2
#define BTN_R 0
#endif

void inputs_init();
void inputs_loop(State& state);