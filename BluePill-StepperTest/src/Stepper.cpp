#include "Stepper.h"
#include <Arduino.h>

using namespace StepperMotor;

#define DIRECTION_PIN(pin) (pin)
#define STEP_PIN(pin) (pin)
#define LED_PIN PC13

Stepper::Stepper(){}

Stepper::Stepper(char dirPin, char stpPin){
    dirPinChar = dirPin;
    stpPinChar = stpPin;
    pinMode(DIRECTION_PIN(dirPinChar), OUTPUT);
    pinMode(STEP_PIN(stpPin), OUTPUT);
    pinMode(LED_PIN, OUTPUT);
}

void Stepper::step(float steps){
  digitalWrite(STEP_PIN(stpPinChar), LOW);
  bool isPositive = true;
  if (steps >= 0.0){
    digitalWrite(DIRECTION_PIN(dirPinChar), LOW);
    isPositive = true;
  }
  else if(steps < 0.0){
    digitalWrite(DIRECTION_PIN(dirPinChar), HIGH);
    isPositive = false;
  }
  for(int i = 1; i <= abs(steps); i ++){
    digitalWrite(STEP_PIN(stpPinChar), HIGH);
    digitalWrite(LED_PIN, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP_PIN(stpPinChar), LOW);
    digitalWrite(LED_PIN, LOW);
    delayMicroseconds(1000);
    if(isPositive){
      stepsPassed++;
    }
    else if(!isPositive){
      stepsPassed--;
    }
  }
}

int Stepper::getStepsPassed(){
    return stepsPassed;
}

void Stepper::resetStepsPassed(){
    stepsPassed = 0;
}
