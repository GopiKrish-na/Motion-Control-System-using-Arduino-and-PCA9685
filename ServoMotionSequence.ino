#include "ServoInit.h"
#include "MotionSequence.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(PWM_ADDR);

void setup() {
    Serial.begin(115200);
    Serial.println("Initializing PCA9685....");
    
    initializeServos(pwm);
    delay(1000);
}

void loop() {
    executeMotionSequence(pwm, 0);  // Start with sequence 0 (square motion)
    // delay(100);
}