#ifndef SIMPLE_TIMER_H
#define SIMPLE_TIMER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t last;
    uint32_t interval;
} SimpleTimer;

void timerInit(SimpleTimer *t, uint32_t interval_ms);
int timerExpired(SimpleTimer *t);

#ifdef __cplusplus
}
#endif

#endif

