# MiniScheduler

A lightweight cooperative scheduler for Arduino.
Allows you to run multiple functions at independent intervals without blocking the loop.

## Features

- Multiple tasks managed in a single scheduler
- Non-blocking: no `delay()` calls
- Millis-based, overflow-safe
- Simple and lightweight, perfect for learning cooperative multitasking

## Installation

1. In Arduino IDE: **Sketch → Include Library → Add .ZIP Library**
2. Or copy the `MiniScheduler/` folder into your Arduino libraries directory.

## Usage
1. **In Arduino IDE(before setup):** firstly write **#include <MiniSchedulerCooperative.h>**
2. **Create an instance of the scheduler:** **MiniSchedulerCooperative sched;** This object will hold and manage all tasks.
3. **Create your functions:** **void ledBlink()**, etc.
4. **In Setup:** Initialize the scheduler, **schedulerInit(&sched);**
5. **&shed** is address of the instance
6. **schedulerAddTask(&sched, ledBlink, 500);**  in there: **&shed** is address, **ledBlink** is your function(this can be change), 500(ms) is your interval value(you can change it)
7. **In Loop:** **schedulerUpdate(&sched);** to check all tasks
   
-This library allows you to schedule multiple functions to run at independent intervals. The scheduler continuously checks each task, and when its time is up, the assigned function is executed automatically, keeping the main loop free for other operations.

## Author
- GitHub: Metehan6688
