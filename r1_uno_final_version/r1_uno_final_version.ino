#include <Servo.h>

#define CH2 A0
#define CH5 A1
#define CH6 A2
#define CH7 A3
#define CH8 A4


#define la_rel1 2
#define la_rel2 3
#define grip_rel 4
#define dcv_rel 5

#define stepPin1 6
#define dirPin1 7

#define stepPin2 8
#define dirPin2 9

#define stepPin3 10
#define dirPin3 11

Servo myservo1;
Servo myservo2;

int ch2Value, ch5Value, ch6Value, ch7Value, ch8Value;

void setup() {

  Serial.begin(115200);
  pinMode(CH2, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);
  pinMode(CH7, INPUT);
  pinMode(CH8, INPUT);

  pinMode(la_rel1, OUTPUT);
  pinMode(la_rel2, OUTPUT);
  pinMode(grip_rel, OUTPUT);
  pinMode(dcv_rel, OUTPUT);

  pinMode(stepPin1,OUTPUT); 
  pinMode(dirPin1,OUTPUT);
  pinMode(stepPin2,OUTPUT); 
  pinMode(dirPin2,OUTPUT);
  pinMode(stepPin3,OUTPUT); 
  pinMode(dirPin3,OUTPUT);

  myservo1.attach(12);
  myservo2.attach(13);

  stepper_setup();
}

int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  int val = map(ch, 1000, 2000, minLimit, maxLimit);
  if (val > 255) val = 255;
  else if (val < -255) val = -255;
  return val;
}

void readChannelsatOnce() {
  ch2Value = readChannel(CH2, -255, 255, 0);
  ch5Value = readChannel(CH5, -255, 255, 0);
  ch6Value = readChannel(CH6, -255, 255, 0);
  ch7Value = readChannel(CH7, -255, 255, 0);
  ch8Value = readChannel(CH8, -255, 255, 0);
}

void stepper_setup() {
  digitalWrite(dirPin1, 1);
  // digitalWrite(step_dir4, 0);
  for (int x = 0; x < 500; x++) {
    digitalWrite(stepPin1, LOW);
    // digitalWrite(step_step4, LOW);
    delayMicroseconds(700);
    digitalWrite(stepPin1, HIGH);
    // digitalWrite(step_step4, HIGH);
    delayMicroseconds(700);
  }
}

void shoot() {
  if (ch7Value > 150) {
    digitalWrite(dcv_rel, HIGH);
  } else if (ch7Value < -200) {
    digitalWrite(dcv_rel, LOW);
  }
}

void Actuate() {
  if (ch5Value < 150 && ch5Value > -150) {
    digitalWrite(la_rel1, HIGH);
    digitalWrite(la_rel2, HIGH);  // Default state
  } else if (ch5Value > 150) {
    digitalWrite(la_rel1, LOW);
    digitalWrite(la_rel2, HIGH);  // PLZ aage move hoja
  } else if (ch5Value < -150) {
    digitalWrite(la_rel1, HIGH);
    digitalWrite(la_rel2, LOW);  // plz peeche move hojo T_T
  }
}

void claw() {
  if (ch6Value < -100) {
    digitalWrite(grip_rel, LOW);
  } else if (ch6Value > -20 && ch6Value < 20) {
    digitalWrite(grip_rel, HIGH);
    myservo1.write(0);
    myservo2.write(0);
    delay(200);
  } else if (ch6Value > 100) {
    myservo1.write(180);
    myservo2.write(180);
    delay(200);
  }
}

void stepper() {
  readChannelsatOnce();
  if (ch2Value > 150) {
    digitalWrite(dirPin2, 0);
    digitalWrite(dirPin3, 0);
    for (int x = 0; x < 800; x++) {
      Serial.println("actually Chal");
      digitalWrite(stepPin3, LOW);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(700);
      digitalWrite(stepPin3, HIGH);
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(700);
    }
  } else if (ch2Value < -150) {
    digitalWrite(dirPin2, 1);
    digitalWrite(dirPin3, 1);
    for (int x = 0; x < 800; x++) {
      Serial.println("Chal");
      digitalWrite(stepPin3, LOW);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(800);
      digitalWrite(stepPin3, HIGH);
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(800);
    }

  } 

}

void loop() {

  readChannelsatOnce();
  // Serial.println(ch2Value);
  stepper();
  claw();
  shoot();
  Actuate();
}
