#include "display.hpp"

#ifndef BUILD_TEST_ESP8266
extern U8G2_SSD1315_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, SSD_RESET, SCL, SDA);
#else
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, SSD_RESET, SCL, SDA);
#endif

void display_init() {
    u8g2.begin();
}

void display_loop(State& state) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_siji_t_6x10);

    if (!state.wifi.connected) {
        u8g2.drawGlyph(116, 10, 0xe217);
    } else {
        u8g2.drawGlyph(116, 10, 0xe21a);
    }
    
    _display_draw_time(state);

    u8g2.sendBuffer();
}

void _display_draw_time(State& state) {
    char timebuf[9];

    if (state.time.available) {
        sprintf(timebuf, "%02d:%02d:%02d", state.time.info.tm_hour, state.time.info.tm_min, state.time.info.tm_sec);
    } else {
        sprintf(timebuf, "--:--:--");
    }

    u8g2.setFont(u8g2_font_spleen16x32_me);
    u8g2.drawStr(0, 42, timebuf);
}