#include "includes.hpp"
#include "state.hpp"

#ifndef BUILD_TEST_ESP8266
// Building for PCB
extern WebServer server;
#else
// Building for test ESP8266
extern ESP8266WebServer server;
#endif

void server_init(State& state);
void server_handle();
