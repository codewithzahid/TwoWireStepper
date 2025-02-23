// TwoWireStepper.h
#ifndef TWOWIRESTEPPER_H
#define TWOWIRESTEPPER_H

#include <Arduino.h>

class TwoWireStepper {
 private:
  int8_t _stepPin, _dirPin;
  bool _direction;
  float _targetSpeed;   // target speed
  float _currentSpeed;  // current speed
  float _acceleration;
  float _deceleration;
  unsigned long _lastStepTime;
  unsigned long _lastSpeedUpdateTime;
  bool _stopping;
  void stepControl();

 public:
  TwoWireStepper(int8_t stepPin, int8_t dirPin);
  void setStepperSpeed(float speed);
  void setStepperAcceleration(float acceleration);
  void setStepperDeceleration(float deceleration);
  void setStepperDirection(bool direction);
  void enableStepper();
  void disableStepper();
  void runStepper();
  void stopStepper();
  bool isStopped();
  void startStepper(float speed);
};

#endif