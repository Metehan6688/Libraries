#include <SimpleTimer.h>

SimpleTimer ledTimer;
SimpleTimer serialTimer;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  timerInit(&ledTimer, 500);
  timerInit(&serialTimer, 2000);
}

void loop() {
  if (timerExpired(&ledTimer)) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }

  if (timerExpired(&serialTimer)) {
    Serial.println("tick");
  }
}
