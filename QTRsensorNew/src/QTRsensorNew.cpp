#include "QTRsensorNew.h"

// Set start values for sensor
// This function initializes the sensor structure. It sets sensor pins and sensor count as INPUT
void qtrSet(QTRsensorNew *qtr, uint8_t pins[], uint8_t sensorCount) {
    if (sensorCount > QTR_MAX_SENSORS) sensorCount = QTR_MAX_SENSORS;
    qtr->sensorCount = sensorCount; // 0-32 sensor count is available
    for (uint8_t i = 0; i < sensorCount; i++) {
        qtr->pins[i] = pins[i];
        pinMode(pins[i], INPUT);
        qtr->minValues[i] = 1023;
        qtr->maxValues[i] = 0;
        /*It sets minValues to 1023 and maxValues to 0.
        This "extreme values" approach ensures that the very first reading
         during calibration will immediately update these limits.*/
        qtr->p[i] = 0; //p as sensor in digital mode. p0, p1, p2, p...
    }
    qtr->lineBlack = true;//default
    qtr->refValue = 500; // This can change but 500 default
    qtr->useNonBlocking = false; //disabled for this version
    qtr->interval = 0; //disabled for this version coming soon...
    qtr->lastRead = 0;
    qtr->lastPosition = 0;
}

//Performs a single-sample calibration. It should be called multiple times (e.g., in a loop of 400 iterations) while moving the robot over the line.
void qtrCalibrate(QTRsensorNew *qtr) {
    for (uint8_t i = 0; i < qtr->sensorCount; i++) {
        uint16_t val = analogRead(qtr->pins[i]);
        if (val > qtr->maxValues[i]) qtr->maxValues[i] = val; //It compares the current raw reading with the stored min and max values.
        if (val < qtr->minValues[i]) qtr->minValues[i] = val; //If the current reading is outside the known range, it updates the borders.
    }
}

//Reads raw analog data and converts it into a "Normalized" format (0 to 1000).
void qtrRead(QTRsensorNew *qtr) {
    // Non Block Control //coming soon...
    if (qtr->useNonBlocking && (millis() - qtr->lastRead < qtr->interval)) return;
    qtr->lastRead = millis();

    for (uint8_t i = 0; i < qtr->sensorCount; i++) {
        uint16_t val = analogRead(qtr->pins[i]);
        uint16_t den = qtr->maxValues[i] - qtr->minValues[i];
        int32_t norm = 0;

        if (den > 0) {
            norm = ((int32_t)val - qtr->minValues[i]) * 1000 / den;
        }
        //This is formula. It uses the: (Raw - Min) * 1000 / (Max - Min).

        if (norm < 0) norm = 0;
        if (norm > 1000) norm = 1000;

        // If line is white this is reversing the form
        if (!qtr->lineBlack) norm = 1000 - norm;

        //make new normal
        qtr->normalized[i] = (uint16_t)norm;
    }
}

// Converts analog signals into binary (0 or 1) based on a ref value (default 500)
void qtrReadDigital(QTRsensorNew *qtr) {
    qtrRead(qtr); // Firsty take analog values
    for (uint8_t i = 0; i < qtr->sensorCount; i++) {
        qtr->p[i] = (qtr->normalized[i] > qtr->refValue) ? 1 : 0; //Transform it
    }
    // Border sensor touch variables for auto calibration (for the motor controlling codes)
    qtr->leftSensorTouch = qtr->p[0];
    qtr->rightSensorTouch = qtr->p[qtr->sensorCount - 1];
}

// Calculates the exact center of the line relative to the sensor array. For 8A the midpoint is 3500
//Because max value is 7000 and min is 0 for 8A.
//Uses a "Weighted Average" algorithm: Sum(Value * Index * 1000) / Sum(Values).
uint16_t qtrPos(QTRsensorNew *qtr) {
    qtrRead(qtr);
    uint32_t avg = 0;
    uint32_t sum = 0;
    bool onLine = false;

    for (uint8_t i = 0; i < qtr->sensorCount; i++) {
        uint16_t val = qtr->normalized[i];
        if (val > 200) onLine = true;
        if (val > 50) {
            avg += (uint32_t)val * (i * 1000);
            sum += (uint32_t)val;
        }
    }

    // This part is panic mode: Memory Feature: If the robot completely loses the line
    //the function remembers the lastPosition and returns either 0 or the maximum value to tell the PID controller which way to turn back.
    if (!onLine) {
        if (qtr->lastPosition < (qtr->sensorCount - 1) * 500) return 0;
        else return (qtr->sensorCount - 1) * 1000;
    }

    qtr->lastPosition = (uint16_t)(avg / sum); // This is formula
    return qtr->lastPosition;
}

// Helper Functions
void qtrSetRef(QTRsensorNew *qtr, uint16_t ref) { qtr->refValue = ref; } //Adjusts the threshold (Default value: 500).
void qtrSetLineBlack(QTRsensorNew *qtr, bool black) { qtr->lineBlack = black; } //Sets the line type (white or black) that is auto-convert function
