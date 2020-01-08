#ifndef CATHETER_H
#define CATHETER_H

#include "Stepper.h"

namespace Catheter{
    class FourPull{
        private:
            //char xDir, xStp, yDir, yStp;
            
        public:
            char xDir, xStp,yDir, yStp;
            StepperMotor::Stepper xStepper;
            StepperMotor::Stepper yStepper;
            //FourPull(char, char, char, char);
            FourPull(StepperMotor::Stepper, StepperMotor::Stepper);
            void move(float,float);
    };
}

#endif
