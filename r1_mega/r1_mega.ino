#include <AccelStepper.h>
#include <Wire.h>
#include <Servo.h>

///// Define input pins for channels /////

#define step_neg 24
#define step_posi 26
#define grip_rel 28
#define dcv_rel 30

#define CH1 2
#define CH2 3
#define CH3 4
#define CH4 5
#define CH5 6
#define CH6 7
// #define CH7 8
// #define CH8 12

#define DIR1 25
#define PWM1 9
#define DIR2 27
#define PWM2 10
#define DIR3 29
#define PWM3 11
#define DIR4 31
#define PWM4 13

Servo myservo1;
Servo myservo2;

unsigned long startTime;              // Variable to store the start time
const unsigned long duration = 5000;  // Duration in milliseconds (1 minute)

// Global variables for storing channel values
int ch1Value;
int ch2Value;
int ch3Value;
int ch4Value;
int ch5Value;
int ch6Value;


int pulse1;
int pulse2;
int pulse3;
int pulse4;
int pulse5;
int pulse6;


#define step_dir1 34  //  Working
#define step_dir3 38  //  working

#define step_step1 35  //  Working
#define step_step3 39  // WOrking


#define SERVOMIN 150
#define SERVOMAX 600

///// Define instances of AccelStepper /////
AccelStepper stepper1 = AccelStepper(1, step_dir1, step_step1);
AccelStepper stepper2 = AccelStepper(1, step_dir3, step_step3);

// Adafruit_PWMServoDriver myServo = Adafruit_PWMServoDriver();

void setup() {

  Serial.begin(115200);
  // Set input pins
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);


  pinMode(DIR1, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(DIR3, OUTPUT);
  pinMode(PWM3, OUTPUT);
  pinMode(DIR4, OUTPUT);
  pinMode(PWM4, OUTPUT);

  pinMode(step_neg, OUTPUT);
  pinMode(step_posi, OUTPUT);
  pinMode(grip_rel, OUTPUT);
  pinMode(dcv_rel, OUTPUT);

  stepper1.setMaxSpeed(1500);
  stepper1.setAcceleration(1800);
  stepper2.setMaxSpeed(1500);
  stepper2.setAcceleration(1800);

  myservo1.attach(23);
  myservo2.attach(26);

  // myServo.begin();
  // myServo.setPWMFreq(60);

  startTime = millis();
}

void loop() {
  readChannelsatOnce();
  remote_control();
  Serial.print("ch3Value");
  Serial.println(ch3Value);
  Serial.print("ch5Value");
  Serial.println(ch5Value);
  Serial.print("ch6Value");
  Serial.println(ch6Value);
  if (ch6Value > 100){
    Mode2();
    }
}

int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  int val = map(ch, 1000, 2000, minLimit, maxLimit);
  if (val > 255){
    val = 255;
  }
  else if (val < -255){
    val = -255;
  }
  return val;
}

void readChannelsatOnce(){
ch1Value = readChannel(CH1, -255, 255, 0);
ch2Value = readChannel(CH2, -255, 255, 0);
ch3Value = readChannel(CH3, -255, 255, 0);
ch4Value = readChannel(CH4, -255, 255, 0);
ch5Value = readChannel(CH5, -255, 255, 0);
ch6Value = readChannel(CH6, -255, 255, 0);
}

void remote_control() {
  readChannelsatOnce();  ///// Drive function /////
  if (ch2Value > 80 && -80 < ch1Value < 80) {
    run();
    Fdir();
  } else if (ch2Value < -80 && -80 < ch1Value < 80) {
    run();
    Bdir();
  } else if (ch1Value > 80 && -80 < ch2Value < 80) {
    run();
    Rdir();
  } else if (ch1Value < -80 && -80 < ch2Value < 80) {
    run();
    Ldir();
  } else if (-80 < ch1Value < 80 && -80 < ch2Value < 80) {
    stop();
  }
}

void rotate(){
  if (ch2Value > 120 &&  ch1Value > 120){
  run();
  CWR();
  }
  else if (ch2Value < -120 &&  ch1Value <  -120){
  run();
  ACWR();
  }
}



void Mode1(){
}

void Mode2(){
  stepper();
  servo();
}

void stepper() {
  ///// Stepper up and down /////
  if (ch3Value > 100) {
    digitalWrite(step_dir1, 0);
    digitalWrite(step_dir3, 0);
    for (int x = 0; x < 300; x++) {
      digitalWrite(step_step1, LOW);
      digitalWrite(step_step3, LOW);
      delayMicroseconds(700);
      digitalWrite(step_step1, HIGH);
      digitalWrite(step_step3, HIGH);
      delayMicroseconds(700);
    }
  } else if (ch3Value < -100) {
    digitalWrite(step_dir1, 1);
    digitalWrite(step_dir3, 1);
    for (int x = 0; x < 300; x++) {
      digitalWrite(step_step1, HIGH);
      digitalWrite(step_step3, HIGH);
      delayMicroseconds(700);
      digitalWrite(step_step1, LOW);
      digitalWrite(step_step3, LOW);
      delayMicroseconds(700);
    }
  }
}

void servo() {
  ///// Seedling Grab /////
  if (ch5Value < -100) {
    myservo1.write(0);
    myservo2.write(0);
    delay(500);
    myservo1.write(90);
    delay(500);
  } else if (ch5Value > 100) {
    myservo1.write(180);
    myservo2.write(180);
    delay(500);
    myservo1.write(90);
    delay(500);
  } else {
    myservo1.write(90);
    myservo2.write(90);
    delay(500);
  }
}

void Grip() {
  ///// Ball Grab /////
  if (ch6Value > 100) {
    Serial.println("GRIPPING");
    digitalWrite(grip_rel, HIGH);  // Gripper Actuate
  } else {
    Serial.println("UNGRIPPING");
    digitalWrite(grip_rel, LOW);  // Gripper Close
  }
}

void sol_shoot(){
  if (ch5Value < -100){
    Serial.println("OPEN");
    digitalWrite(grip_rel, HIGH);
    digitalWrite(dcv_rel, HIGH);  // Gripper Actuate
  } else if (-20 > ch5Value < 20) {
    Serial.println("CLOSE");
    digitalWrite(grip_rel, LOW);  // Gripper Close
    digitalWrite(dcv_rel, HIGH);
  } else if (ch5Value > 100) {
    Serial.println("SHOOT");
    digitalWrite(dcv_rel, LOW);
  }
}

void Actuate() {
  ///// Shooting angle adjust /////
  if (ch3Value < 100 && ch3Value > -100) {
    Serial.println("stop");
    digitalWrite(step_neg, HIGH);
    digitalWrite(step_posi, HIGH);  // Default state
  } else if (ch3Value > 100) {
    Serial.println("retract");
    digitalWrite(step_neg, LOW);
    digitalWrite(step_posi, HIGH);  // PLZ aage move hoja
  } else {
    Serial.println("extend");
    digitalWrite(step_neg, HIGH);
    digitalWrite(step_posi, LOW);  // plz peeche move hojo T_T
  }
}

void Shoot() {
  ///// Piston shooter /////
  if (ch5Value > 100) {
    Serial.println("shoot");
    digitalWrite(dcv_rel, LOW);  // Shoot
  } else {
    Serial.println("dont");
    digitalWrite(dcv_rel, HIGH);  // Default state
  }
}

///// Quality of life Function /////

void Fdir() {
  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, LOW);
  digitalWrite(DIR3, HIGH);
  digitalWrite(DIR4, LOW);
}

void Bdir() {
  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, HIGH);
  digitalWrite(DIR3, LOW);
  digitalWrite(DIR4, HIGH);
}

void Rdir() {
  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, HIGH);
  digitalWrite(DIR3, HIGH);
  digitalWrite(DIR4, HIGH);
}

void Ldir() {
  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, LOW);
  digitalWrite(DIR3, LOW);
  digitalWrite(DIR4, LOW);
}

void CWR() {
  digitalWrite(DIR1, LOW);
  digitalWrite(DIR2, LOW);
  digitalWrite(DIR3, LOW);
  digitalWrite(DIR4, HIGH);
}

void ACWR() {
  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, HIGH);
  digitalWrite(DIR3, HIGH);
  digitalWrite(DIR4, LOW);
}

void run(){
  digitalWrite(PWM1, HIGH);
  digitalWrite(PWM2, HIGH);
  digitalWrite(PWM3, HIGH);
  digitalWrite(PWM4, HIGH);
}

void stop() {
  digitalWrite(PWM1, LOW);
  digitalWrite(PWM2, LOW);
  digitalWrite(PWM3, LOW);
  digitalWrite(PWM4, LOW);
}