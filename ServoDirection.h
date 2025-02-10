#ifndef SERVO_DIRECTION_H
#define SERVO_DIRECTION_H
#include "ServoInit.h"

//Direction multiplier for each servo
extern const int SERVO_DIRECTION[NUM_SERVOS];

//Function to apply the multiplier
int applyDirection(int servoIndex, int angle);

#endif