#include "Serial.h"
#include "Stepper.h"

using namespace AscendSerial;
using StepperMotor::Stepper;

CatheterSerial::CatheterSerial() {}

CatheterSerial::CatheterSerial(FourPull catheter)
{
    activeCatheter = catheter;
}

void CatheterSerial::requestInputString()
{
	Serial.println("send");
}

//Get the length of string that you want to reel in inches from the serial
//Format is x,y decimals are accepted
String CatheterSerial::getInputString()
{
    String input = "";
    while (Serial.available() > 0)
    {
        input = Serial.readString();
    }
    return input;
}

void CatheterSerial::sendStepsPassed()
{
    String stepDataPrefix = "xy,";
    stepDataPrefix += activeCatheter.xStepper.getStepsPassed();
    String stepDataSuffix = ",";
    stepDataSuffix += activeCatheter.yStepper.getStepsPassed();
    String stepData = "";
    stepData += stepDataPrefix + stepDataSuffix;
    Serial.println(stepData);
}
