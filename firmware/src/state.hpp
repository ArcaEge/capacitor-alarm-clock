#pragma once
#include "includes.hpp"

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

    struct {
        struct {
            int hours = 0;
            int minutes = 0;
        } time;
        bool weekSchedule[7] = {false};
    } schedule;
};

extern State state;