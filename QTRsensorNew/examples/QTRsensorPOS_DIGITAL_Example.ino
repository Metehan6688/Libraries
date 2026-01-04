/**
 * @file    QTRsensorPOS_DIGITAL_Example.ino
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

// Sensor object and configuration
QTRsensorNew qtr;
const uint8_t SensorCount = 8;
uint8_t pins[SensorCount] = { A0, A1, A2, A3, A4, A5, A6, A7 };

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  // 1. Initialize sensor pins and internal memory
  qtrSet(&qtr, pins, SensorCount);

  // 2. Set the threshold for digital conversion (0-1000 range)
  // Higher value means more sensitivity to black.
  qtrSetRef(&qtr, 500);

  // 3. Set line polarity: true = Black line, false = White line
  qtrSetLineBlack(&qtr, true);

  /* --- CALIBRATION PHASE --- */
  Serial.println("Calibration Phase: Moving across the line...");
  digitalWrite(LED_BUILTIN, HIGH); 

  // Calibrate for ~2 seconds (400 samples * 5ms)
  // Sweep the sensors across the line during this period
  for (uint16_t i = 0; i < 400; i++) {
    qtrCalibrate(&qtr);
    delay(5);
  }

  digitalWrite(LED_BUILTIN, LOW); 
  Serial.println("Calibration Done!");
  
  // Optional: Print calibration results for hardware check
  for(uint8_t i=0; i<SensorCount; i++) {
    Serial.print("Sensor "); Serial.print(i);
    Serial.print(" -> Min: "); Serial.print(qtr.minValues[i]);
    Serial.print(" | Max: "); Serial.println(qtr.maxValues[i]);
  }
  delay(2000);
}

void loop() {
  // A. Get precise line position (0 to 7000 for 8 sensors)
  // This internally calls qtrRead()
  uint16_t position = qtrPos(&qtr);

  // B. Update digital array (p[i]) for intersection/turn logic
  qtrReadDigital(&qtr);

  /* --- DATA OUTPUT / DEBUG --- */

  // 1. Display Digital Array (visual feedback)
  Serial.print("Digital: [");
  for (uint8_t i = 0; i < qtr.sensorCount; i++) {
    Serial.print(qtr.p[i]); 
  }
  Serial.print("]");

  // 2. Display Normalized Position
  Serial.print(" | Pos: ");
  Serial.print(position);
  Serial.println("");

  // Your PID control logic or Turn logic would go here:
  // int error = position - 3500;
  // applySteering(error);
}