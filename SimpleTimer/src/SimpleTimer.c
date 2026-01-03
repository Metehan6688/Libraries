#include "SimpleTimer.h"
#include <Arduino.h>

void timerInit(SimpleTimer *t, uint32_t interval_ms) {
    if (!t) return;
    t->last = millis();
    t->interval = interval_ms;
}

int timerExpired(SimpleTimer *t) {
    if (!t) return 0;

    uint32_t now = millis();
    if ((uint32_t)(now - t->last) >= t->interval) {
        t->last = now;
        return 1;
    }
    return 0;
}
