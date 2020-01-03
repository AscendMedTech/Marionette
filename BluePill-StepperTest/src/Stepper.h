namespace StepperMotor{
    class Stepper{
        private:
            char dirPinChar;
            char stpPinChar;

        public:
            Stepper(char,char);
            void step(float);
            int getStepsPassed();
            void resetStepsPassed();
    };
}