#include "TwoWireStepper.h"

#define STEP_PIN 3
#define DIR_PIN 2

TwoWireStepper stepper(STEP_PIN, DIR_PIN);

void setup() {
  stepper.setStepperSpeed(800);        // 200 steps per second
  stepper.setStepperAcceleration(100);  // 50 steps/second²
  //stepper.setStepperDeceleration(40);  // 40 steps/second²  
}

void loop() {
    stepper.runStepper();
}
