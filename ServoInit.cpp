#include "ServoInit.h"
#include "ServoDirection.h"

const int SERVO_PINS[NUM_SERVOS] = {14, 15};
const int INITIAL_POSITIONS[NUM_SERVOS] = {0, 0};

int angleToPulse(int angle) {
  return map(angle, -90, 90, SERVO_MIN, SERVO_MAX);
}

void initializeServos(Adafruit_PWMServoDriver &pwm) {
  pwm.begin();
  pwm.setPWMFreq(PWM_FREQ);

  delay(500);
  for (int i = 0; i < NUM_SERVOS; i++) {
    // Apply direction multiplier to initial position
    int directedAngle = applyDirection(i, INITIAL_POSITIONS[i]);
    pwm.setPWM(SERVO_PINS[i], 0, angleToPulse(directedAngle));
  }
}