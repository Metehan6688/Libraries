# SimpleTimer

A minimal, delay-free, millis-based software timer library for Arduino.
Designed for learning event-driven, cooperative-style timing and building small non-blocking applications.

## Features

- Simple, lightweight, no delay() usage
- Works with multiple timers independently
- Overflow-safe timing using `millis()`
- Perfect for learning kernel-like timing concepts

## Installation

1. In Arduino IDE: **Sketch → Include Library → Add .ZIP Library**
2. Or copy the `SimpleTimer/` folder into your Arduino libraries directory.

## Usage
1. **In Arduino IDE(before setup):** firstly write **#include <SimpleTimer.h>**
2. **Create timers:** **SimpleTimer ledTimer;** this code created timer of the led
3. **In Setup:** Initialize timer with an int type interval: **timerInit(&ledTimer, 500);**
4. **&ledTimer:** **"&"** is address of variable **ledTimer**
5. 500 is interval value, this is 500ms
6. **In Loop:** **timerExpired(&ledTimer);** checks if interval value have passed since the last trigger
7. You can use **timerExpired()** function in **if()** in loop
- With this library, you can create multiple timers and run each with an independent interval. The loop runs continuously, and when a timer’s interval expires, the corresponding action is triggered.

## Author
- GitHub: Metehan6688
