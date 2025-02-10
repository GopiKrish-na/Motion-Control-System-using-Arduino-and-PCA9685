#ifndef SERVO_INIT_H
#define SERVO_INIT_H
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// PWM config
#define PWM_ADDR 0x40
#define PWM_FREQ 50

// servo pwm limits to map to angles
#define SERVO_MIN 150
#define SERVO_MAX 520
// servo pins
// #define SERVO_1 14
// #define SERVO_2 15

//servo count
#define NUM_SERVOS 2

extern const int SERVO_PINS[NUM_SERVOS];

// initial servo positions (in degrees)
extern const int INITIAL_POSITIONS[NUM_SERVOS];
// initialize servos / function declaration
void initializeServos(Adafruit_PWMServoDriver &pwm);
int angleToPulse(int angle);

#endif