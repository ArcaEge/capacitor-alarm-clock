#include "display.hpp"

#ifndef BUILD_TEST_ESP8266
extern U8G2_SSD1315_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, SSD_RESET, SCL, SDA);
#else
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, SSD_RESET, SCL, SDA);
#endif

muif_t muif_list[] = {
    MUIF_U8G2_FONT_STYLE(0, u8g2_font_helvR08_tr),  // Regular
    MUIF_U8G2_FONT_STYLE(1, u8g2_font_helvB08_tr),  // Bold
    MUIF_RO("HR", _display_mui_hrule),
    MUIF_U8G2_LABEL(),
    MUIF_RO("GP", mui_u8g2_goto_data),
    MUIF_BUTTON("GC", mui_u8g2_goto_form_w1_pi),
    MUIF_BUTTON("SS", _display_mui_button_save_exit),   // Save schedule, go back
    MUIF_VARIABLE("CS", &state.alarm.skipNext, mui_u8g2_u8_chkbox_wm_pi),
    MUIF_VARIABLE("CB", &state.persistent.schedule.enabled, mui_u8g2_u8_chkbox_wm_pi),
    MUIF_U8G2_U8_MIN_MAX("NS", &state.persistent.nextSlot, 1, 3, mui_u8g2_u8_min_max_wm_mud_pi),
    MUIF_U8G2_U8_MIN_MAX("NH", &state.persistent.schedule.time.hours, 0, 23, mui_u8g2_u8_min_max_wm_mud_pi),
    MUIF_U8G2_U8_MIN_MAX("NM", &state.persistent.schedule.time.minutes, 0, 59, mui_u8g2_u8_min_max_wm_mud_pi),

    MUIF_VARIABLE("W0", &state.persistent.schedule.weekSchedule[0], mui_u8g2_u8_chkbox_wm_pi),
    MUIF_VARIABLE("W1", &state.persistent.schedule.weekSchedule[1], mui_u8g2_u8_chkbox_wm_pi),
    MUIF_VARIABLE("W2", &state.persistent.schedule.weekSchedule[2], mui_u8g2_u8_chkbox_wm_pi),
    MUIF_VARIABLE("W3", &state.persistent.schedule.weekSchedule[3], mui_u8g2_u8_chkbox_wm_pi),
    MUIF_VARIABLE("W4", &state.persistent.schedule.weekSchedule[4], mui_u8g2_u8_chkbox_wm_pi),
    MUIF_VARIABLE("W5", &state.persistent.schedule.weekSchedule[5], mui_u8g2_u8_chkbox_wm_pi),
    MUIF_VARIABLE("W6", &state.persistent.schedule.weekSchedule[6], mui_u8g2_u8_chkbox_wm_pi),

    MUIF_RO("EX", _display_mui_exit)
};

fds_t fds_data[] =
MUI_FORM(1)
    MUI_STYLE(1)
    MUI_LABEL(5, 10, "Schedule")
    MUI_XY("HR", 0,13)

    MUI_STYLE(0)
    MUI_DATA("GP",
        MUI_5  "Skip|"
        MUI_7  "Next slot|"
        MUI_10 "State|"
        MUI_20 "Time|"
        MUI_30 "Days of week|"
        MUI_99 "Exit|")
    MUI_XYA("GC", 5, 25, 0)
    MUI_XYA("GC", 5, 37, 1)
    MUI_XYA("GC", 5, 49, 2)
    MUI_XYA("GC", 5, 61, 3)

MUI_FORM(5)
    MUI_STYLE(1)
    MUI_LABEL(5, 10, "Skip")
    MUI_XY("HR", 0, 13)

    MUI_STYLE(0)
    MUI_LABEL(5, 30, "Skip next")
    MUI_XY("CS", 60, 30)
    MUI_XYAT("SS", 64, 59, 1, " OK ")

MUI_FORM(7)
    MUI_STYLE(1)
    MUI_LABEL(5, 10, "Next capacitor slot")
    MUI_XY("HR", 0, 13)

    MUI_STYLE(0)
    MUI_LABEL(5, 30, "Next slot")
    MUI_XY("NS", 60, 30)
    MUI_XYAT("SS", 64, 59, 1, " OK ")

MUI_FORM(10)
    MUI_STYLE(1)
    MUI_LABEL(5, 10, "State")
    MUI_XY("HR", 0, 13)

    MUI_STYLE(0)
    MUI_LABEL(5, 30, "Enabled")
    MUI_XY("CB", 60, 30)
    MUI_XYAT("SS", 64, 59, 1, " OK ")

MUI_FORM(20)
    MUI_STYLE(1)
    MUI_LABEL(5, 10, "Time")
    MUI_XY("HR", 0, 13)

    MUI_STYLE(0)
    MUI_XY("NH", 50, 35)
    MUI_STYLE(1)
    MUI_LABEL(64, 35, ":")
    MUI_STYLE(0)
    MUI_XY("NM", 68, 35)
    MUI_XYAT("SS", 64, 59, 1, " OK ")

MUI_FORM(30)
    MUI_STYLE(1)
    MUI_LABEL(5, 10, "Days of week")
    MUI_XY("HR", 0, 13)

    MUI_STYLE(0)

    MUI_XY("W0", 1, 25)
    MUI_LABEL(11, 25, "Mon")
    MUI_XY("W1", 44, 25)
    MUI_LABEL(54, 25, "Tue")
    MUI_XY("W2", 85, 25)
    MUI_LABEL(95, 25, "Wed")
    MUI_XY("W3", 1, 35)
    MUI_LABEL(11, 35, "Tue")
    MUI_XY("W4", 44, 35)
    MUI_LABEL(54, 35, "Fri")
    MUI_XY("W5", 85, 35)
    MUI_LABEL(95, 35, "Sat")
    MUI_XY("W6", 1, 45)
    MUI_LABEL(11, 45, "Sun")

    MUI_XYAT("SS", 64, 59, 1, " OK ")

MUI_FORM(99)
    MUI_AUX("EX")
;

void display_init(State& state) {
    u8g2.begin();
    state.mui.begin(u8g2, fds_data, muif_list, sizeof(muif_list) / sizeof(muif_t));
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
        if (state.input.events.select || state.input.events.next || state.input.events.prev) {
            state.input.events.select = false;
            state.input.events.next = false;
            state.input.events.prev = false;
            state.mui.gotoForm(1, 0);
        }

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

uint8_t _display_mui_hrule(mui_t* ui, uint8_t msg) {
    u8g2_t* u8g2 = mui_get_U8g2(ui);
    switch (msg) {
        case MUIF_MSG_DRAW:
            u8g2_DrawHLine(u8g2, 0, mui_get_y(ui), u8g2_GetDisplayWidth(u8g2));
            break;
    }
    return 0;
}

uint8_t _display_mui_exit(mui_t* ui, uint8_t msg) {
    if (msg == MUIF_MSG_FORM_START) {
        mui_SaveForm(ui);
        mui_LeaveForm(ui);
        
        return 1;
    }
    return 0;
}

uint8_t _display_mui_button_save_exit(mui_t *ui, uint8_t msg) {
  switch(msg) {
    case MUIF_MSG_DRAW:
      mui_u8g2_draw_button_utf(ui, U8G2_BTN_HCENTER |mui_u8g2_get_fi_flags(ui), 0, 1, 1, ui->text);
      break;
    case MUIF_MSG_FORM_START:
      break;
    case MUIF_MSG_FORM_END:
      break;
    case MUIF_MSG_CURSOR_ENTER:
      break;
    case MUIF_MSG_CURSOR_SELECT:
    case MUIF_MSG_VALUE_INCREMENT:
    case MUIF_MSG_VALUE_DECREMENT:
      // Save
      state.prefs.putBytes("persistent", &state.persistent, sizeof(state.persistent));
      mui_SaveForm(ui);
      return mui_GotoFormAutoCursorPosition(ui, ui->arg);
    case MUIF_MSG_CURSOR_LEAVE:
      break;
    case MUIF_MSG_TOUCH_DOWN:
      break;
    case MUIF_MSG_TOUCH_UP:
      break;    
  }
  return 0;
}