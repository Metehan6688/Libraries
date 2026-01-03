#include "MiniSchedulerCooperative.h"
#include <Arduino.h>

void schedulerInit(MiniSchedulerCooperative *sched) {
    sched->taskCount = 0;
    for (int i = 0; i < MAX_TASKS; i++) {
        sched->tasks[i].active = 0;
        sched->tasks[i].func = 0;
        sched->tasks[i].interval = 0;
        sched->tasks[i].lastRun = 0;
    }
}

int schedulerAddTask(MiniSchedulerCooperative *sched, TaskFunc func, uint32_t interval) {
    if (sched->taskCount >= MAX_TASKS) return -1; // full
    int i = sched->taskCount++;
    sched->tasks[i].func = func;
    sched->tasks[i].interval = interval;
    sched->tasks[i].lastRun = millis();
    sched->tasks[i].active = 1;
    return 0;
}

void schedulerUpdate(MiniSchedulerCooperative *sched) {
    uint32_t now = millis();
    for (int i = 0; i < sched->taskCount; i++) {
        Task *t = &sched->tasks[i];
        if (t->active && (uint32_t)(now - t->lastRun) >= t->interval) {
            t->lastRun = now;
            t->func();
        }
    }
}
