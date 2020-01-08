#include <Arduino.h>
#include "Stepper.h"
#include "Catheter.h"

#define POSITIVE_X_BUTTON PB11
#define NEGATIVE_X_BUTTON PB10
#define POSITIVE_Y_BUTTON PB1
#define NEGATIVE_Y_BUTTON PB0

using StepperMotor::Stepper;
using Catheter::FourPull;

float distancePerRotation = 0.9738929;

char xAxisDir = PB12;
char xAxisStep = PB13;
char yAxisDir = PB14;
char yAxisStep = PB15;

Stepper xAxisStepper(xAxisDir, xAxisStep);
Stepper yAxisStepper(yAxisDir, yAxisStep);

FourPull fourPull1(xAxisStepper, yAxisStepper);

//Get the length of string that you want to reel in inches from the serial
//Format is x,y decimals are accepted
String getInputString(){
  String input = "";
  while (Serial.available() > 0){
    input = Serial.readString();
    //input.replace("\n", "");
    //input.replace("\r","");
  }
  return input;
}

void requestInputString(){
  Serial.println("send");
}

float getXSplit(String input){
  int index = input.indexOf(",");
  String xDistance = input.substring(0, index);
  float xDistancefloat = xDistance.toFloat();
  return xDistancefloat;
}

float getYSplit(String input){
  int index = input.indexOf(",");
  String yDistance = input.substring(index + 1, input.length()-1);
  float yDistancefloat = yDistance.toFloat();
  return yDistancefloat;
}

float getStepsX(String input){
  int index = input.indexOf(",");
  String xDistance = input.substring(0, index);
  float xDistanceFloat = xDistance.toFloat();
  Serial.println("x distance inputted:");
  Serial.println(xDistanceFloat);

  float rotationsX = xDistanceFloat / distancePerRotation;

  float stepsX = rotationsX * 1600;

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

  float stepsY = rotationsY * 1600;

  Serial.println("y steps calculated:");
  Serial.println(stepsY);
  return stepsY;
}

void setup() {
  Serial.begin(9600);
  //Serial.println("setup catheter");
  pinMode(POSITIVE_X_BUTTON, INPUT);
  pinMode(NEGATIVE_X_BUTTON, INPUT);
  pinMode(POSITIVE_Y_BUTTON, INPUT);
  pinMode(NEGATIVE_Y_BUTTON, INPUT);
  requestInputString();
}

void loop() {
  
  int x = 0;
  int y = 0;
  if (digitalRead(POSITIVE_X_BUTTON)){
    x = x + 10;
  }
  if (digitalRead(NEGATIVE_X_BUTTON)){
    x = x - 10;
  }
  if  (digitalRead(POSITIVE_Y_BUTTON)){
    y = y + 10;
  }
  if (digitalRead(NEGATIVE_Y_BUTTON)){
    y = y - 10;
  }
  fourPull1.move(x,y);

  if (Serial.available() > 0){
    String inputString = getInputString();
    Serial.println(inputString);
    //xAxisStepper.step(getStepsX(inputString));
    //yAxisStepper.step(getStepsY(inputString));
    fourPull1.move(getStepsX(inputString),getStepsY(inputString));
    //fourPull1.move(getXSplit(inputString),getYSplit(inputString));
    //requestInputString();
  }
  String stepDataPrefix = "xy,";
  stepDataPrefix += fourPull1.xStepper.getStepsPassed();
  String stepDataSuffix = ",";
  stepDataSuffix += fourPull1.yStepper.getStepsPassed();
  String stepData = "";
  stepData += stepDataPrefix + stepDataSuffix;
  Serial.println(stepData);
}
