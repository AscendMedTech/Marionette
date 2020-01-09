#ifndef CATHETER_H
#define CATHETER_H

#include "Stepper.h"

namespace Catheter
{
class FourPull
{
private:

public:
    char xDir, xStp, yDir, yStp;
    StepperMotor::Stepper xStepper;
    StepperMotor::Stepper yStepper;
    FourPull();
    FourPull(StepperMotor::Stepper, StepperMotor::Stepper);
    void move(float, float);
};
} // namespace Catheter

#endif
