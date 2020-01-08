#ifndef STEPPER_H
#define STEPPER_H
namespace StepperMotor{
    class Stepper{
        private:
            char dirPinChar;
            char stpPinChar;
            int stepsPassed;

        public:
            Stepper();
            Stepper(char,char);
            void step(float);
            int getStepsPassed();
            void resetStepsPassed();
    };
}
#endif
