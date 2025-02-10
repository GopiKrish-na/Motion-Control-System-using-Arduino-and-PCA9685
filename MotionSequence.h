#ifndef MOTION_SEQUENCE_H
#define MOTION_SEQUENCE_H

#include "ServoInit.h"

//Motion Sequence parameters
#define TRANSITION_STEPS 50
#define MAX_FRAMES_PER_SEQUENCE 10
#define NUM_SEQUENCES 3  

// Structure to hold a single motion sequence
struct MotionSequence {
    const char* name;
    int numFrames;
    const int (*frames)[NUM_SERVOS];
    const float* transitionTimes;
    float loopTransitionTime;  //parameter for loop transition
};


// Function declarations
void smoothTransition(Adafruit_PWMServoDriver &pwm, int currentAngles[], const int targetAngles[], float transitionTime);
void executeMotionSequence(Adafruit_PWMServoDriver &pwm, int sequenceIndex);

// Declare sequences
extern const MotionSequence SEQUENCES[NUM_SEQUENCES];

#endif