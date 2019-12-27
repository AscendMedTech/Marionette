//#include <Stepper.h>
//Stepper stepX = Stepper(3200, 2, 3); //0.1125 degrees per step
//Stepper stepY = Stepper(3200, 4, 5);

float distancePerRotation = 0.393196481;
uint16_t message = 0;
String message1 = "";
float intMessage = 0;

class StepperMotor{
  public:
    int DIRECTION_PIN;
    int STEP_PIN;
    StepperMotor(int, int);
    void step(int);
};

StepperMotor::StepperMotor(int dirPin, int stpPin){
  DIRECTION_PIN = dirPin;
  STEP_PIN = stpPin;
  pinMode(DIRECTION_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
}

void StepperMotor::step(int steps){
  digitalWrite(STEP_PIN, LOW);
  //digitalWrite(DIRECTION_PIN, LOW);
  if (steps >= 0){
    digitalWrite(DIRECTION_PIN, LOW);
  }
  else if(steps < 0){
    digitalWrite(DIRECTION_PIN, HIGH);
  }
  for(int i = 1; i <= abs(steps); i ++){
    digitalWrite(STEP_PIN, HIGH);
    delay(1);
    digitalWrite(STEP_PIN, LOW);
  }
}

StepperMotor motor = StepperMotor(2,3);
StepperMotor motor2 = StepperMotor(4,5);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Setting Up");

  //stepX.setSpeed(60);
  //stepY.setSpeed(60);
}

void loop() {
  // put your main code here, to run repeatedly:
  getSerial();

}

void getSerial(){
  message1 = "";
  if(Serial.available() > 0){
    //message = Serial.read() << 8;
    message1 = Serial.readString();
    intMessage = message1.toFloat();
    Serial.println(intMessage);
    //Serial.print("Message Recieved");
    //Serial.println(intMessage);
    float rotations = intMessage / distancePerRotation;
    float steps = rotations * 3200;
    motor.step(steps);
    motor2.step(steps);
     
    //step(3200);  
  }
}
