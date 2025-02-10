#include "ServoDirection.h"

const int SERVO_DIRECTION[NUM_SERVOS] = {1, -1};

int applyDirection(int servoIndex, int angle) {
  return angle * SERVO_DIRECTION[servoIndex];
}