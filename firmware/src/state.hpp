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
};

extern State state;