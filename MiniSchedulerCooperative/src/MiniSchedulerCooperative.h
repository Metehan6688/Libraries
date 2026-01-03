#ifndef MINISCHEDULERCOOPERATIVE_H
#define MINISCHEDULERCOOPERATIVE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_TASKS 8

typedef void (*TaskFunc)(void);

typedef struct {
    TaskFunc func;
    uint32_t interval;
    uint32_t lastRun;
    uint8_t active;
} Task;

typedef struct {
    Task tasks[MAX_TASKS];
    uint8_t taskCount;
} MiniSchedulerCooperative;

void schedulerInit(MiniSchedulerCooperative *sched);
int schedulerAddTask(MiniSchedulerCooperative *sched, TaskFunc func, uint32_t interval);
void schedulerUpdate(MiniSchedulerCooperative *sched);

#ifdef __cplusplus
}
#endif

#endif

