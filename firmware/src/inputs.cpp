#include "inputs.hpp"

void inputs_init() {
    pinMode(BTN_L, INPUT);
    pinMode(BTN_R, INPUT);
}

void inputs_loop(State& state) {
    // Inverted logic as using pullup
    bool left = !digitalRead(BTN_L);
    bool right = !digitalRead(BTN_R);

    if (left && right && !state.input.raw.bothPressed) {
        // Trigger select event
        state.input.events.select = true;
        state.input.raw.bothPressed = true;
    } else if (!left && !right && state.input.raw.bothPressed) {
        // Both released
        state.input.raw.bothPressed = false;
    } else {
        if (state.input.raw.leftLast && !left && !state.input.raw.bothPressed) {
            // Left released
            state.input.events.prev = true;
        }
        if (state.input.raw.rightLast && !right && !state.input.raw.bothPressed) {
            // Right released
            state.input.events.next = true;
        }
    }

    state.input.raw.leftLast = left;
    state.input.raw.rightLast = right;
}