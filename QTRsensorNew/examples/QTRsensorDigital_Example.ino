/**
 * @file    QTRsensorDigital_Example.ino
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

#include "QTRsensorNew.h"

/* --- Global Configuration --- */
QTRsensorNew qtr; // Create the sensor object instance

// Define the sensor array pins. Adjust based on your hardware layout.
const uint8_t SensorPins[] = {A0, A1, A2, A3, A4, A5, A6, A7};
const uint8_t SensorCount = 8;

void setup() {
    // Initialize Serial Communication for debugging
    Serial.begin(9600);
    
    // Built-in LED serves as a status indicator during calibration
    pinMode(LED_BUILTIN, OUTPUT); //Only for arduino

    /* --- INITIALIZATION --- */
    // Initialize pins and reset internal min/max arrays
    // Note: (uint8_t*) cast is used to prevent compiler warnings for const arrays
    qtrSet(&qtr, (uint8_t*)SensorPins, SensorCount);

    // Set the digital threshold (Reference Value)
    // Range: 0 (White) to 1000 (Black). Default is 500.
    qtrSetRef(&qtr, 500); 

    // Define line polarity: true for Black line, false for White line
    qtrSetLineBlack(&qtr, true);

    /* --- CALIBRATION PHASE --- */
    Serial.println("Calibration Starting... Move the robot over the line!");
    digitalWrite(LED_BUILTIN, HIGH); // LED ON: Calibration in progress //Only for arduino

    /**
     * Run calibration loop for ~4 seconds (400 iterations * 10ms delay).
     * During this phase, you MUST slide the sensor array across the line
     * so every sensor sees both the darkest (line) and brightest (surface) points.
     */
    for (int i = 0; i < 400; i++) {
        qtrCalibrate(&qtr); 
        delay(10); 
    }

    digitalWrite(LED_BUILTIN, LOW); // LED OFF: Calibration finished
    Serial.println("Calibration Completed Successfully.");
    
    // Print the learned calibration boundaries for diagnostics
    Serial.println("--- Calibration Results (Raw Values) ---");
    for(int i = 0; i < SensorCount; i++) {
        Serial.print("Sensor ["); Serial.print(i); Serial.print("] -> ");
        Serial.print("Min: "); Serial.print(qtr.minValues[i]);
        Serial.print(" | Max: "); Serial.println(qtr.maxValues[i]);
    }
    delay(2000); // Small pause for user to read data
}

void loop() {
    /* --- DATA ACQUISITION --- */
    
    // Option 1: Digital Reading (Populates the qtr.p[i] array with 0 or 1)
    // Ideal for corner detection (90 degrees), intersections, and logic gates.
    qtrReadDigital(&qtr);

    // Option 2: Precision Positioning (Weighted average for PID control)
    // Returns 0 to (SensorCount-1)*1000. For 8 sensors, center is 3500.
    uint16_t linePosition = qtrPos(&qtr);

    /* --- DEBUG OUTPUT --- */
    
    // Print digital sensor states (e.g., "00111100")
    Serial.print("Digital Array: ");
    for(int i = 0; i < qtr.sensorCount; i++) {
        Serial.print(qtr.p[i]); 
    }
    
    // Print normalized line position
    Serial.print(" | Position: ");
    Serial.println(linePosition);


    delay(20); // Small delay to prevent serial buffer overflow
}
