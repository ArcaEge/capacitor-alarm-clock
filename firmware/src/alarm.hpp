#include "includes.hpp"
#include "state.hpp"

#define ALARM_PIN_ON_TIME 25000

void alarm_init();
void alarm_loop(State& state);

uint8_t _alarm_get_pin(uint8_t slot);