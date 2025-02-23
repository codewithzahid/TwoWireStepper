
// TwoWireStepper.cpp
#include "TwoWireStepper.h"

TwoWireStepper::TwoWireStepper(int8_t stepPin, int8_t dirPin) {
  _stepPin = stepPin;
  _dirPin = dirPin;
  pinMode(_stepPin, OUTPUT);
  pinMode(_dirPin, OUTPUT);

  // Default parameters
  _targetSpeed = 100;  // target speed in steps per second
  _currentSpeed = 0;   // starting speed in steps per second
  _acceleration = 50;  // steps per second^2
  _deceleration = 50;  // steps per second^2
  _lastStepTime = 0;
  _lastSpeedUpdateTime = 0;
  _direction = true;
  _stopping = false;
}

void TwoWireStepper::setStepperSpeed(float speed) {
  _targetSpeed = abs(speed);  // Ensure positive speed
}

void TwoWireStepper::setStepperAcceleration(float acceleration) {
  _acceleration = abs(acceleration);  // Ensure positive acceleration
}

void TwoWireStepper::setStepperDeceleration(float deceleration) {
  _deceleration = abs(deceleration);  // Ensure positive deceleration
}

void TwoWireStepper::setStepperDirection(bool direction) {
  _direction = direction;
  digitalWrite(_dirPin, _direction);
}

void TwoWireStepper::stopStepper() {
  _stopping = true;
  _targetSpeed = 0;  // Set target speed to 0 for deceleration
}

void TwoWireStepper::startStepper(float speed) {
  _stopping = false;
  _targetSpeed = speed;  // Set target speed to 0 for deceleration
}

bool TwoWireStepper::isStopped() {
  return _currentSpeed == 0;
}

void TwoWireStepper::enableStepper() {
  digitalWrite(_dirPin, _direction);
}

void TwoWireStepper::disableStepper() {
  digitalWrite(_stepPin, LOW);
}

void TwoWireStepper::stepControl() {
  digitalWrite(_stepPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(_stepPin, LOW);
}

void TwoWireStepper::runStepper() {
  unsigned long currentTime = micros();
  unsigned long elapsedTime = currentTime - _lastSpeedUpdateTime;

  // Update speed every millisecond
  if (elapsedTime >= 1000) {                        // 1000 microseconds = 1 millisecond
    float timeInSeconds = elapsedTime / 1000000.0;  // Convert to seconds

    if (_stopping) {
      // Decelerate to stop
      _currentSpeed -= _deceleration * timeInSeconds;
      if (_currentSpeed <= 0) {
        _currentSpeed = 0;
        _stopping = false;  // Reset stopping flag
      }
    } else if (_currentSpeed < _targetSpeed) {
      // Accelerate
      _currentSpeed += _acceleration * timeInSeconds;
      if (_currentSpeed > _targetSpeed) {
        _currentSpeed = _targetSpeed;
      }
    }

    _lastSpeedUpdateTime = currentTime;
  }

  // Only step if we have a non-zero speed
  if (_currentSpeed > 0) {
    // Calculate step interval in microseconds
    unsigned long stepInterval = static_cast<unsigned long>(1000000.0 / _currentSpeed);

    // Check if it's time for the next step
    if (currentTime - _lastStepTime >= stepInterval) {
      stepControl();
      _lastStepTime = currentTime;
    }
  }
}