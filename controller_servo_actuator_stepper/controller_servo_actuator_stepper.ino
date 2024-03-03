#define CH5 51
#include <AccelStepper.h>
#define dirPin 3
#define stepPin 2
#define motorInterfaceType 1
#include <Servo.h>
Servo servo;  // create servo object to control a servo
int pos = 0;

int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Integers to represent values from sticks and pots
int ch5Value;
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup() {
  Serial.begin(115200);
  stepper.setMaxSpeed(1700);
  stepper.setAcceleration(2200);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT); //actuator bottom relay output
  servo.attach(7);  
  servo.write(0);  
}

void loop() {

  ch5Value = readChannel(CH5, 255, -255, 0);
  
  if (ch5Value >= -5 && ch5Value <= 10){               // NO = 2
    stepper.moveTo(-300);
    stepper.runToPosition();
    digitalWrite(9,LOW);
    digitalWrite(8,HIGH); 
    Serial.println(" Switch 2 value \t");
    Serial.print(ch5Value); // attaches the servo on pin 9 to the servo objectư
//--------------------- extend--------------------------------------------------
  } else if (ch5Value <= -200) {                        // No = 3
    stepper.moveTo(6000);
    stepper.runToPosition();
    digitalWrite(9,HIGH);
    digitalWrite(8,LOW); 
    Serial.println(" Switch 3 value \t");
    Serial.print(ch5Value);                            
//----------------------Retract-------------------------------------------------
  } else {                 
    stepper.moveTo(-300);
    stepper.runToPosition();                            // NO = 1
    digitalWrite(9,LOW);
    digitalWrite(8,HIGH);  
    Serial.println(" Switch 1 value \t");
    Serial.print(ch5Value); // attaches the servo on pin 9 to the servo objectư
    servo.write(50);   
//----------------------Stop-----------------------------------------------------
 }
}