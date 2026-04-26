#pragma once
#include "includes.hpp"
#include <MUIU8g2.hpp>

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

    Preferences prefs;
    MUIU8G2 mui;

    struct {
        struct {
            bool enabled = true;
            struct {
                uint8_t hours = 0;
                uint8_t minutes = 0;
            } time;
            bool weekSchedule[7] = {false};
        } schedule;

        uint8_t nextSlot = 1;
    } persistent;

    struct {
        bool skipNext = false;
        
        unsigned long stopTriggerAt = 0;
        unsigned long lastSkipAt = 0;

        uint8_t currentSlot = 0;
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