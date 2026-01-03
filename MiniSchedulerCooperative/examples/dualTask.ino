#include <MiniSchedulerCooperative.h>

MiniSchedulerCooperative sched;

void blinkLED() {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void printTick() {
    Serial.println("tick");
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);

    schedulerInit(&sched);
    schedulerAddTask(&sched, blinkLED, 500);   // 500ms
    schedulerAddTask(&sched, printTick, 1000); // 1000ms
}

void loop() {
    schedulerUpdate(&sched);
    // loop is still available
}