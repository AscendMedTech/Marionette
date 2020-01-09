#include <Arduino.h>
#include "Catheter.h"

using namespace Catheter;

FourPull::FourPull() {}

FourPull::FourPull(StepperMotor::Stepper x, StepperMotor::Stepper y)
{
    xStepper = x;
    yStepper = y;
}

void FourPull::move(float stepsX, float stepsY)
{
    float ratio;
    int xDirection = 1;
    int yDirection = 1;

    if (stepsX < 0)
    {
        xDirection = -1;
    }
    if (stepsY < 0)
    {
        yDirection = -1;
    }

    if (stepsX == 0 || stepsY == 0)
    {
        xStepper.step(stepsX);
        yStepper.step(stepsY);
    }
    else if (abs(stepsX) > abs(stepsY))
    {
        ratio = stepsX / stepsY;
        for (int i = 0; i < abs(stepsY); i++)
        {
            xStepper.step(ratio * xDirection);
            yStepper.step(1 * yDirection);
        }
    }
    else if (abs(stepsX) < abs(stepsY))
    {
        ratio = stepsY / stepsX;
        for (int i = 0; i < abs(stepsX); i++)
        {
            yStepper.step(ratio * yDirection);
            xStepper.step(1 * xDirection);
        }
    }
    else if (abs(stepsX) == abs(stepsY))
    {
        ratio = 1;
        for (int i = 0; i < abs(stepsX); i++)
        {
            xStepper.step(1 * xDirection);
            yStepper.step(1 * yDirection);
        }
    }
}
