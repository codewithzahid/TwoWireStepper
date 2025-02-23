#include "TwoWireStepper.h"

#define STEP_PIN 3
#define DIR_PIN 2
#define STOP_BUTTON_PIN 5  // Connect button between this pin and GND
#define START_BUTTON_PIN 6

TwoWireStepper stepper(STEP_PIN, DIR_PIN);

void setup() {
  pinMode(STOP_BUTTON_PIN, INPUT_PULLUP);   // Enable internal pullup resistor
  pinMode(START_BUTTON_PIN, INPUT_PULLUP);  // Enable internal pullup resistor

  stepper.setStepperSpeed(800);         // 800 steps per second
  stepper.setStepperAcceleration(100);  // 100 steps/second²
  stepper.setStepperDeceleration(200);  // 200 steps/second² for stopping
}

void loop() {
  // Check if button is pressed (LOW because of INPUT_PULLUP)
  if (digitalRead(STOP_BUTTON_PIN) == LOW) {
    stepper.stopStepper();  // Trigger deceleration
  }
  if (digitalRead(START_BUTTON_PIN) == LOW) {
    stepper.setStepperDirection(1);
    stepper.startStepper(800);  // Trigger deceleration
  }
  stepper.runStepper();
}