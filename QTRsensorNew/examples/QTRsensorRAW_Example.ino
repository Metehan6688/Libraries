/**
 * @file    QTRsensorRAW_Example.ino
 * @author  Metehan Semerci
 * @brief   Advanced Line Following Example using QTRsensorNew Library
 * @version 1.0
 * @date    2024-05-20
 * * @section LICENSE
 * MIT License
 * * Copyright (c) 2024 Metehan Semerci
 * * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @see     https://github.com/Metehan6688/QTRsensorNew
 */
#include <QTRsensorNew.h>

QTRsensorNew qtr;
const uint8_t SensorCount = 8;
uint8_t pins[SensorCount] = { A0, A1, A2, A3, A4, A5, A6, A7 };

void setup() {
  // We use a higher baud rate for faster data streaming
  Serial.begin(115200);
  
  // Basic initialization - no calibration needed for raw test
  qtrSet(&qtr, pins, SensorCount);

  Serial.println("--- QTRsensorNew RAW DATA TEST ---");
  Serial.println("Reading raw 10-bit values (0 to 1023)");
  delay(2000);
}

void loop() {
  /**
   * IMPORTANT: In this test, we don't use qtrRead() because qtrRead()
   * uses calibration data. We will use analogRead() directly from the pins.
   */
  
  Serial.print("RAW_DATA: ");

  for (uint8_t i = 0; i < qtr.sensorCount; i++) {
    // Read the physical voltage on the pin directly
    uint16_t rawValue = analogRead(qtr.pins[i]);

    // Visual formatting for Serial Monitor
    Serial.print(i);
    Serial.print(":");
    Serial.print(rawValue);
    
    if (i < qtr.sensorCount - 1) {
      Serial.print(" | "); // Separator between sensors
    }
  }

  Serial.println(); // New line for next sample
  
  delay(100); // 10Hz sampling rate is enough for human reading
}