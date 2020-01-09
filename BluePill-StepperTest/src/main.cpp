#include <Arduino.h>
#include "Stepper.h"
#include "Catheter.h"
#include "Serial.h"

#define POSITIVE_X_BUTTON PB11
#define NEGATIVE_X_BUTTON PB10
#define POSITIVE_Y_BUTTON PB1
#define NEGATIVE_Y_BUTTON PB0

using AscendSerial::CatheterSerial;
using Catheter::FourPull;
using StepperMotor::Stepper;

float distancePerRotation = 0.9738929;

char xAxisDir = PB12;
char xAxisStep = PB13;
char yAxisDir = PB14;
char yAxisStep = PB15;

Stepper xAxisStepper(xAxisDir, xAxisStep);
Stepper yAxisStepper(yAxisDir, yAxisStep);

FourPull fourPull1(xAxisStepper, yAxisStepper);

CatheterSerial fourPull1Serial(fourPull1);

float getXSplit(String input)
{
	int index = input.indexOf(",");
	String xDistance = input.substring(0, index);
	float xDistancefloat = xDistance.toFloat();
	return xDistancefloat;
}

float getYSplit(String input)
{
	int index = input.indexOf(",");
	String yDistance = input.substring(index + 1, input.length() - 1);
	float yDistancefloat = yDistance.toFloat();
	return yDistancefloat;
}

float getStepsX(String input)
{
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

float getStepsY(String input)
{
	int index = input.indexOf(",");
	String yDistance = input.substring(index + 1, input.length() - 1);
	float yDistanceFloat = yDistance.toFloat();
	Serial.println("y distance inputted:");
	Serial.println(yDistanceFloat);

	float rotationsY = yDistanceFloat / distancePerRotation;

	float stepsY = rotationsY * 1600;

	Serial.println("y steps calculated:");
	Serial.println(stepsY);
	return stepsY;
}

void setup()
{
	Serial.begin(9600);
	//Serial.println("setup catheter");
	pinMode(POSITIVE_X_BUTTON, INPUT);
	pinMode(NEGATIVE_X_BUTTON, INPUT);
	pinMode(POSITIVE_Y_BUTTON, INPUT);
	pinMode(NEGATIVE_Y_BUTTON, INPUT);
	fourPull1Serial.requestInputString();
}

void loop()
{

	int x = 0;
	int y = 0;
	if (digitalRead(POSITIVE_X_BUTTON))
	{
		x = x + 10;
	}
	if (digitalRead(NEGATIVE_X_BUTTON))
	{
		x = x - 10;
	}
	if (digitalRead(POSITIVE_Y_BUTTON))
	{
		y = y + 10;
	}
	if (digitalRead(NEGATIVE_Y_BUTTON))
	{
		y = y - 10;
	}
	fourPull1.move(x, y);

	if (Serial.available() > 0)
	{
		String inputString = fourPull1Serial.getInputString();
		Serial.println(inputString);
		fourPull1.move(getStepsX(inputString), getStepsY(inputString));
	}

	fourPull1Serial.sendStepsPassed();
}
