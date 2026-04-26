#include "alarm.hpp"

#ifndef BUILD_TEST_ESP8266
// Building for PCB
#define RELAY_1 3
#define RELAY_2 1
#define RELAY_3 10
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
    unsigned long now = millis();

    if (state.alarm.stopTriggerAt != 0) {
        // Currently going off
        if (now > state.alarm.stopTriggerAt) {
            uint8_t pin = _alarm_get_pin(state.alarm.currentSlot);

            digitalWrite(pin, LOW);

            state.alarm.stopTriggerAt = 0;
            state.alarm.currentSlot = 0;
        }
    } else if (state.persistent.schedule.enabled) {
        bool timeMatches = state.persistent.schedule.time.hours == state.time.info.tm_hour && state.persistent.schedule.time.minutes == state.time.info.tm_min && state.time.info.tm_sec == 0;
        bool dayOfWeekMatches = state.persistent.schedule.weekSchedule[(state.time.info.tm_wday + 6) % 7];

        if (state.time.available && timeMatches && dayOfWeekMatches) {
            // Is time to go off
            if (state.alarm.skipNext) {
                // Use skip
                state.alarm.skipNext = false;
                state.alarm.lastSkipAt = now;
                Serial.println("skipped");
            } else if (now - state.alarm.lastSkipAt > 5000) {
                // >5s since skip and skipNext is false
                // go boom
                Serial.println("going kaboom");

                state.alarm.stopTriggerAt = now + ALARM_PIN_ON_TIME;

                state.alarm.currentSlot = state.persistent.nextSlot;
                uint8_t pin = _alarm_get_pin(state.alarm.currentSlot);

                digitalWrite(pin, HIGH);

                // (((state.persistent.nextSlot - 1) + 1) % 3) + 1
                state.persistent.nextSlot = (state.persistent.nextSlot % 3) + 1;
                state.prefs.putBytes("persistent", &state.persistent, sizeof(state.persistent));
            }
        }
    }
}

uint8_t _alarm_get_pin(uint8_t slot) {
    switch (slot) {
        case 1:
            return RELAY_1;
        case 2:
            return RELAY_2;
        case 3:
            return RELAY_3;
        default:
            return 0;
    }
}