#include <Arduino.h>
#include "Catheter.h"

using namespace Catheter;

StepperMotor::Stepper xStepper;
StepperMotor::Stepper yStepper;

/*FourPull::FourPull(char xdir, char xstp, char ydir, char ystp){
    xDir = xdir;
    xStp = xstp;
    yDir = ydir;
    yStp = ystp;
}*/

FourPull::FourPull(StepperMotor::Stepper x, StepperMotor::Stepper y){
    xStepper = x;
    yStepper = y;
}

void FourPull::move(int stepsX, int stepsY){
    float ratio;
    if(stepsX > stepsY){
        ratio = stepsX/stepsY;
        for (int i = 0; i < stepsY; i++){
            xStepper.step(ratio);
            yStepper.step(1);
        }
    }
    else if (stepsX < stepsY){
        ratio = stepsY/stepsX;
        for (int i = 0; i < stepsX; i++){
            yStepper.step(ratio);
            xStepper.step(1);
        }
    }
    else if (stepsX == stepsY){
        ratio = 1;
        for (int i = 0; i < stepsX; i++){
            xStepper.step(1);
            yStepper.step(1);
        }
    }
}
