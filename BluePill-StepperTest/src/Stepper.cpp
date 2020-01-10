#include "Stepper.h"
#include <Arduino.h>

using namespace StepperMotor;

#define DIRECTION_PIN(pin) (pin)
#define STEP_PIN(pin) (pin)
#define LED_PIN PC13

//Default constructor
Stepper::Stepper()
{
}

//Constuctor with pin arguments
Stepper::Stepper(char dirPin, char stpPin)
{
  dirPinChar = dirPin;
  stpPinChar = stpPin;
  pinMode(DIRECTION_PIN(dirPinChar), OUTPUT);
  pinMode(STEP_PIN(stpPin), OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

//Move stepper motor steps number of steps
void Stepper::step(float steps)
{
  digitalWrite(STEP_PIN(stpPinChar), LOW);
  bool isPositive = true;
  if (steps >= 0.0)
  {
    digitalWrite(DIRECTION_PIN(dirPinChar), LOW);
    isPositive = true;
  }
  else if (steps < 0.0)
  {
    digitalWrite(DIRECTION_PIN(dirPinChar), HIGH);
    isPositive = false;
  }
  for (int i = 1; i <= abs(steps); i++)
  {
    digitalWrite(STEP_PIN(stpPinChar), HIGH);
    digitalWrite(LED_PIN, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP_PIN(stpPinChar), LOW);
    digitalWrite(LED_PIN, LOW);
    delayMicroseconds(1000);
    if (isPositive)
    {
      stepsPassed++;
    }
    else if (!isPositive)
    {
      stepsPassed--;
    }
  }
}

//Returns the number of steps stepper motor has moved.
//Takes direction into account
int Stepper::getStepsPassed()
{
  return stepsPassed;
}

//Resets the counter for number of steps passed.
void Stepper::resetStepsPassed()
{
  stepsPassed = 0;
}
