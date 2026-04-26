#include <U8g2lib.h>
#include <MUIU8g2.hpp>

#include "state.hpp"

#ifndef BUILD_TEST_ESP8266
// Building for final PCB
#define SDA 4
#define SCL 5
#define SSD_RESET 2
#else
// Building for test ESP8266
#define SDA 4
#define SCL 5
#define SSD_RESET U8X8_PIN_NONE
#endif

void display_init(State& state);
void display_loop(State& state);

void _display_draw_time(State& state);

uint8_t _display_mui_hrule(mui_t *ui, uint8_t msg);
uint8_t _display_mui_exit(mui_t* ui, uint8_t msg);
uint8_t _display_mui_button_save_exit(mui_t *ui, uint8_t msg);
