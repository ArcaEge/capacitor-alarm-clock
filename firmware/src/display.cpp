#include "display.hpp"

#ifndef BUILD_TEST_ESP8266
extern U8G2_SSD1315_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, SSD_RESET, SCL, SDA);
#else
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, SSD_RESET, SCL, SDA);
#endif

muif_t muif_list[] = {  
  MUIF_U8G2_FONT_STYLE(0, u8g2_font_helvR08_tr),  /* define style 0 */
  MUIF_U8G2_LABEL(),                                                    /* allow MUI_LABEL command */
  MUIF_BUTTON("BN", mui_u8g2_btn_exit_wm_fi),        /* define exit button */
  MUIF_BUTTON("B2", mui_u8g2_btn_exit_wm_fi)        /* define exit button */
};


fds_t fds_data[] =                              /* Don't use comma between the commands! */
MUI_FORM(1)                                     /* This will start the definition of form 1 */
MUI_STYLE(0)                                    /* select the font defined with style 0 */
MUI_LABEL(5, 15, "Hello U8g2")          /* place text at postion x=5, y=15 */
MUI_XYT("BN",64, 30, " Select Me ")     /* place a button at pos x=64, y=30 */
MUI_XYT("B2",64, 50, "aasd asd ")     /* place a button at pos x=64, y=30 */
;

void display_init(State& state) {
    u8g2.begin();
    state.mui.begin(u8g2, fds_data, muif_list, sizeof(muif_list)/sizeof(muif_t));
    state.mui.gotoForm(/* form_id= */ 1, /* initial_cursor_position= */ 0);
}

void display_loop(State& state) {
    u8g2.clearBuffer();

    if (state.mui.isFormActive()) {
        if (state.input.events.select) {
            state.mui.sendSelect();
            state.input.events.select = false;
        }
        if (state.input.events.next) {
            state.mui.nextField();
            state.input.events.next = false;
        }
        if (state.input.events.prev) {
            state.mui.prevField();
            state.input.events.prev = false;
        }

        state.mui.draw();
    } else {
        u8g2.setFont(u8g2_font_siji_t_6x10);
    
        if (!state.wifi.connected) {
            u8g2.drawGlyph(116, 10, 0xe217);
        } else {
            u8g2.drawGlyph(116, 10, 0xe21a);
        }
        
        _display_draw_time(state);
    }

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