#include "display.hpp"

#ifndef BUILD_TEST_ESP8266
extern U8G2_SSD1315_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, SSD_RESET, SCL, SDA);
#else
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, SSD_RESET, SCL, SDA);
#endif

void display_init() {
    u8g2.initDisplay();

    u8g2.firstPage();

    do {
        u8g2.setFont(u8g2_font_ncenB14_tr);
        u8g2.drawStr(0, 20, "Fetching time");
    } while (u8g2.nextPage());
}

void display_loop() {
    u8g2.firstPage();

    do {
        u8g2.setFont(u8g2_font_ncenB14_tr);
        u8g2.drawStr(0, 20, "Fetched time");
    } while (u8g2.nextPage());
}