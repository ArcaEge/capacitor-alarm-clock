#pragma once
#include "includes.hpp"
#include <MUIU8g2.hpp>

enum alarmState { ALARM_PENDING,
                  ALARM_TRIGGERING };

struct State {
    struct {
        bool connected = false;
        bool previouslyConnected = false;
        IPAddress ip;
    } wifi;

    struct {
        bool available = false;
        tm info;
    } time;

    struct {
        int last100ms = 0;
        bool elapsed100ms = false;
    } timing;

    Preferences prefs;
    MUIU8G2 mui;

    struct {
        bool enabled = true;
        struct {
            int hours = 0;
            int minutes = 0;
        } time;
        bool weekSchedule[7] = {false};
    } schedule;

    struct {
        // 0 to 2, index of the next slot to go off (to avoid triggering already exploded slot)
        int nextSlot = 0;
    } alarm;

    struct {
        struct {
            bool prev = false;
            bool next = false;
            bool select = false;
        } events;
        struct {
            bool bothPressed = false;

            // States of left + right buttons from the last loop
            bool leftLast = false;
            bool rightLast = false;
        } raw;
    } input;
};

extern State state;