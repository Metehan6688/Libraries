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
void qtrSet(QTRsensorNew *qtr, uint8_t pins[], uint8_t count);    // Initialization
void qtrCalibrate(QTRsensorNew *qtr);                             // Learn line/surface contrast
void qtrRead(QTRsensorNew *qtr);                                  // Get normalized 0-1000 values
void qtrReadDigital(QTRsensorNew *qtr);                           // Get binary 0/1 values in qtr.p[i]
uint16_t qtrPos(QTRsensorNew *qtr);                               // Calculate line center position
cpp
```
## Helper Functions
```cpp
void qtrSetRef(QTRsensorNew *qtr, uint16_t ref) { qtr->refValue = ref; }         // Set referance value
void qtrSetLineBlack(QTRsensorNew *qtr, bool black) { qtr->lineBlack = black; }  // Set line state (black/white)
```


## Quick Start Example
```cpp
#include <QTRsensorNew.h>

QTRsensorNew qtr;
uint8_t pins[] = {A0, A1, A2, A3, A4, A5, A6, A7};

void setup() {
  qtrSet(&qtr, pins, 8);
  
  // Calibration: Sweep the sensor over the line for 4 seconds
  for (int i = 0; i < 400; i++) {
    qtrCalibrate(&qtr);
    delay(10);
  }
}

void loop() {
  // Get high-precision position for PID
  uint16_t position = qtrPos(&qtr); 
  
  // Get digital state for intersections
  qtrReadDigital(&qtr); 
  if (qtr.p[0] == 1 && qtr.p[7] == 1) {
    // T-junction detected!
  }
}
```


## Library Logic
1. Normalization:
The library converts raw 10-bit analog values (0-1023) into a standardized 0-1000 range. This ensures your PID constants remain the same even if ambient lighting or surface reflectivity changes.

2. Digital Representation `(p[i])`
By calling qtrReadDigital(), the library populates an internal array qtr.p[i] with binary values based on a configurable refValue. This is extremely useful for logic-heavy tasks like detecting 90-degree turns or cross-lines.

## License
This project is licensed under the MIT License. You are free to use, modify, and distribute it for personal or commercial projects.



## Author:
- GitHub: Metehan6688

