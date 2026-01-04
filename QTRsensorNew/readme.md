# QTRsensorNew

A high-performance, lightweight, and non-blocking sensor library for QTR-style analog reflectance sensors on Arduino. This library is designed for speed and reliability in competitive line-following robotics, avoiding dynamic memory allocation (realloc/malloc) for maximum stability.

## Features

- **Running Calibration**: Adaptive min/max calibration algorithm.
- **Weighted Average Positioning**: High-precision line position calculation (0 to N*1000).
- **Hybrid Reading**: Both Analog (0-1000) and Digital (0/1) outputs available.
- **Line Polarity Control**: Easily switch between Black and White line modes.
- **Non-Blocking Logic**: Built-in interval management to keep your PID loop timing consistent.
- **Memory Efficient**: Uses static memory allocation, perfect for Arduino Uno, Nano, and Pro Mini.



## Installation

1. Download the repository as a `.ZIP` file.
2. In the Arduino IDE: **Sketch → Include Library → Add .ZIP Library...**
3. Alternatively, manually copy the `QTRsensorNew` folder into your `Documents/Arduino/libraries/` directory.

## Core Functions

```cpp
void qtrSet(QTRsensorNew *qtr, uint8_t pins[], uint8_t count);      // Initialization
void qtrCalibrate(QTRsensorNew *qtr);                             // Learn line/surface contrast
void qtrRead(QTRsensorNew *qtr);                                  // Get normalized 0-1000 values
void qtrReadDigital(QTRsensorNew *qtr);                           // Get binary 0/1 values in qtr.p[i]
uint16_t qtrPos(QTRsensorNew *qtr);                               // Calculate line center position

## Library Logic
