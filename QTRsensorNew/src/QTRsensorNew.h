#ifndef QTRSENSORNEW_H
#define QTRSENSORNEW_H

#include <Arduino.h>

#define QTR_MAX_SENSORS 32 //Now this library can use max 32 sensor in same time
                                                   //You can use what do you want even 2 sensor is working
                                                   //I prefer 8A for line follower robots.

typedef struct { //this is core structure for containing sensor states, variables, calibration data
    uint8_t pins[QTR_MAX_SENSORS];               // User will enter the pin no's
    uint8_t sensorCount;                                   // Initilazing pins
    uint16_t minValues[QTR_MAX_SENSORS];   // Minimum values (White) found during calibration
    uint16_t maxValues[QTR_MAX_SENSORS];  // Maximum values (Black) found during calibration
    uint16_t normalized[QTR_MAX_SENSORS]; // Calibrated readings mapped to 0-1000 range

    uint8_t p[QTR_MAX_SENSORS]; // for limiting user

    uint16_t refValue;                  //< Threshold for digital conversion (0-1000)
    bool lineBlack;                     //< True: Black line on White surface | False: Convert
    uint16_t lastPosition;              //< Stores the last known line position (0 to (N-1)*1000)

    //coming soon
    bool useNonBlocking;
    uint32_t interval;
    uint32_t lastRead;

    //auto calibration helpers
    bool leftSensorTouch;
    bool rightSensorTouch;
} QTRsensorNew;


// ==========================================
// FUNCTION PROTOTYPES
// ==========================================

void qtrSet(QTRsensorNew *qtr, uint8_t pins[], uint8_t count);
/*
Initializes the sensor pins and resets calibration ranges.
qtr Pointer to the QTRsensorNew struct.
pins Array of analog pin numbers.
count Number of sensors being used.
*/


void qtrCalibrate(QTRsensorNew *qtr);
/*
Updates the min/max calibration range by reading current values.
Should be called inside a loop while moving the robot over the line.
*/


void qtrRead(QTRsensorNew *qtr);
/*
Reads raw data and scales it to 0-1000 range based on calibration.
Respects non-blocking interval if enabled(not now).
*/


void qtrReadDigital(QTRsensorNew *qtr);
/*
Converts normalized values to binary (0/1) stored in the 'p' array.
Also updates leftSensorTouch and rightSensorTouch flags.
*/


uint16_t qtrPos(QTRsensorNew *qtr);
/*
Calculates the weighted average position of the line.
Value from 0 to (SensorCount-1)*1000.
Center is (Count-1)*500.
*/


void qtrSetRef(QTRsensorNew *qtr, uint16_t ref);
/*
Set threshold value (default 500)
*/


void qtrSetLineBlack(QTRsensorNew *qtr, bool black);
/*
Set line colour(Black or White line)
*/



#endif
