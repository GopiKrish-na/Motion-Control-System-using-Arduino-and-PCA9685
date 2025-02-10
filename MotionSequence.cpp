#include "MotionSequence.h"
#include "ServoDirection.h"

// Define frame arrays for each sequence
const int SQUARE_FRAMES[][NUM_SERVOS] = {
   // {0, 0},    //frame 0
    {45, -45},   //frame 1
    {22.5, -22.5},  //frame 2
    {0, 0},   //frame 3
    {-22.5, 22.5}, //frame 4
    {-45, 45},  //frame 5
    //{0, 0}     //frame 6
};

const int WAVE_FRAMES[][NUM_SERVOS] = {
    {30, -30},    
    {30, -30},  
    {30, -30},    
    {30, -30},
    {30, -30}     
};

const int CIRCLE_FRAMES[][NUM_SERVOS] = {
    {45, 0},   
    {45, 45},  
    {0, 45},   
    {-45, 45}, 
    {-45, 0},  
    {-45, -45},
    {0, -45},  
    {45, -45}  
};

// transition times for each sequence
const float SQUARE_TIMES[] = {1.4, 0.3, 0.3, 0.3, 0.3};
const float WAVE_TIMES[] = {0.5, 0.5, 0.5, 0.5, 0.5};
const float CIRCLE_TIMES[] = {0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8};

// sequences array
const MotionSequence SEQUENCES[NUM_SEQUENCES] = {
    {
        "square",
        5,
        SQUARE_FRAMES,
        SQUARE_TIMES
    },
    {
        "wave",
        5,
        WAVE_FRAMES,
        WAVE_TIMES
    },
    {
        "circle",
        8,
        CIRCLE_FRAMES,
        CIRCLE_TIMES
    }
};

// void smoothTransition(Adafruit_PWMServoDriver &pwm, int currentAngles[], const int targetAngles[], float transitionTime) {
//     // step size
//     int delayTime = (transitionTime*1000)/TRANSITION_STEPS;
//     for (int step = 1; step <= TRANSITION_STEPS; step++) {
//         for (int i = 0; i < NUM_SERVOS; i++) {
//             // Calculate intermediate angle
//             int intermediateAngle = currentAngles[i] + (targetAngles[i] - currentAngles[i]) * step / TRANSITION_STEPS;
            
//             // multiplier before converting to PWM
//             int directedAngle = applyDirection(i, intermediateAngle);
            
//             //setting pwm using channel mapping 
//             pwm.setPWM(SERVO_PINS[i], 0, angleToPulse(directedAngle));
//         }
//         delay(delayTime);
//     }
// }

// void executeMotionSequence(Adafruit_PWMServoDriver &pwm, int sequenceIndex) {
//     if (sequenceIndex >= NUM_SEQUENCES) {
//         return;
//     }
    
//     static int currentAngles[NUM_SERVOS];  // Make static to preserve between calls
//     static bool firstRun = true;  // Flag for first execution
    
//     // Only initialize angles on first run
//     if (firstRun) {
//         for (int i = 0; i < NUM_SERVOS; i++) {
//             currentAngles[i] = INITIAL_POSITIONS[i];
//         }
//         firstRun = false;
//     }
    
//     const MotionSequence& sequence = SEQUENCES[sequenceIndex];
    
//     // Execute the selected sequence
//     for (int frame = 0; frame < sequence.numFrames; frame++) {
//         smoothTransition(pwm, currentAngles, sequence.frames[frame], sequence.transitionTimes[frame]);
//         // Update current angles to current frame
//         for (int i = 0; i < NUM_SERVOS; i++) {
//             currentAngles[i] = sequence.frames[frame][i];
//         }
//     }
// }
void smoothTransition(Adafruit_PWMServoDriver &pwm, int currentAngles[], const int targetAngles[], float transitionTime) {
    int delayTime = (transitionTime*1000)/TRANSITION_STEPS;
    for (int step = 1; step <= TRANSITION_STEPS; step++) {
        for (int i = 0; i < NUM_SERVOS; i++) {
            
            int intermediateAngle = currentAngles[i] + 
                (targetAngles[i] - currentAngles[i]) * step / TRANSITION_STEPS;
            
            int directedAngle = applyDirection(i, intermediateAngle);
            pwm.setPWM(SERVO_PINS[i], 0, angleToPulse(directedAngle));
        }
        delay(delayTime);
    }
}

void executeMotionSequence(Adafruit_PWMServoDriver &pwm, int sequenceIndex) {
    if (sequenceIndex >= NUM_SEQUENCES) {
        return;
    }
    
    static int currentAngles[NUM_SERVOS];
    static bool firstRun = true;
    
    if (firstRun) {
        for (int i = 0; i < NUM_SERVOS; i++) {
            currentAngles[i] = INITIAL_POSITIONS[i];  
        }
        firstRun = false;
    }
    
    const MotionSequence& sequence = SEQUENCES[sequenceIndex];
    
    for (int frame = 0; frame < sequence.numFrames; frame++) {
        smoothTransition(pwm, currentAngles, sequence.frames[frame], sequence.transitionTimes[frame]);
        
        for (int i = 0; i < NUM_SERVOS; i++) {
            currentAngles[i] = sequence.frames[frame][i];
        }
    }
}

//to add additional transition time from last to 1st frame transition time > last frame--->first frame

// void executeMotionSequence(Adafruit_PWMServoDriver &pwm, int sequenceIndex) {
//     if (sequenceIndex >= NUM_SEQUENCES) {
//         return;
//     }
    
//     static int currentAngles[NUM_SERVOS];
//     static bool firstRun = true;
    
//     if (firstRun) {
//         for (int i = 0; i < NUM_SERVOS; i++) {
//             currentAngles[i] = INITIAL_POSITIONS[i];
//         }
//         firstRun = false;
//     }
    
//     const MotionSequence& sequence = SEQUENCES[sequenceIndex];
    
//     // Execute sequence
//     for (int frame = 0; frame < sequence.numFrames; frame++) {
//         smoothTransition(pwm, currentAngles, sequence.frames[frame], sequence.transitionTimes[frame]);
//         for (int i = 0; i < NUM_SERVOS; i++) {
//             currentAngles[i] = sequence.frames[frame][i] + INITIAL_POSITIONS[i];
//         }
//     }
    
//     // Add transition back to first frame using the last transition time
//     smoothTransition(pwm, currentAngles, sequence.frames[0], sequence.transitionTimes[sequence.numFrames]);
//     for (int i = 0; i < NUM_SERVOS; i++) {
//         currentAngles[i] = sequence.frames[0][i] + INITIAL_POSITIONS[i];
//     }
// }