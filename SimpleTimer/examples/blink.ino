#include <SimpleTimer.h>

SimpleTimer ledTimer;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  timerInit(&ledTimer, 500);
}

void loop() {
  if (timerExpired(&ledTimer)) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}
