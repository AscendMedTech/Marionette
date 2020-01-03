#include <Arduino.h>
#include "Stepper.h"
//#include "Catheter.h"

#ifndef ledPin
  #define ledPin(pin) (pin) //13
#endif

using StepperMotor::Stepper;
//using Catheter::FourPull;

float distancePerRotation = 0.9738929;

char ledPinChar = PC13;

char xAxisDir = PB12;
char xAxisStep = PB13;
char yAxisDir = PB14;
char yAxisStep = PB15;

Stepper xAxisStepper(xAxisDir, xAxisStep);
Stepper yAxisStepper(yAxisDir, yAxisStep);

//FourPull fourPull1(xAxisDir,xAxisStep, yAxisDir, yAxisStep);

//Get the length of string that you want to reel in inches from the serial
//Format is x,y decimals are accepted
String getInputString(){
  String input = "";
  if (Serial.available() > 0){
    input = Serial.readString();
  }
  return input;
}

float getStepsX(String input){
  int index = input.indexOf(",");
  String xDistance = input.substring(0, index);
  float xDistanceFloat = xDistance.toFloat();
  Serial.println("x distance inputted:");
  Serial.println(xDistanceFloat);

  float rotationsX = xDistanceFloat / distancePerRotation;

  float stepsX = rotationsX * 3200;

  Serial.println("x steps calculated:");
  Serial.println(stepsX);
  return stepsX;
}

float getStepsY(String input){
  int index = input.indexOf(",");
  String yDistance = input.substring(index + 1, input.length()-1);
  float yDistanceFloat = yDistance.toFloat();
  Serial.println("y distance inputted:");
  Serial.println(yDistanceFloat);

  float rotationsY = yDistanceFloat / distancePerRotation;

  float stepsY = rotationsY * 3200;

  Serial.println("y steps calculated:");
  Serial.println(stepsY);
  return stepsY;
}

void setup() {
  pinMode(ledPin(PC13),OUTPUT);
  Serial.begin(9600);
  Serial.println("setup");
}

void loop() {
  if (Serial.available() > 0){
    String inputString = getInputString();
    xAxisStepper.step(getStepsX(inputString));
    yAxisStepper.step(getStepsY(inputString));
    //fourPull1.move(getStepsX(inputString),getStepsY(inputString));
  }
}
