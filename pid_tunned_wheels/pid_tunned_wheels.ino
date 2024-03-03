#define DIR1 8
#define PWM1 9

#define DIR2 7
#define PWM2 6

#define encoder1PinA 2
#define encoder1PinB 3

#define encoder2PinA 18
#define encoder2PinB 19

volatile long encoder1Count = 0;
volatile long encoder2Count = 0;

long previousTime = 0;
float ePrevious = 0;
float eIntegral = 0;

void setup() {
  Serial.begin(115200);

  pinMode(DIR1, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(encoder1PinA, INPUT);
  pinMode(encoder2PinA, INPUT);
  pinMode(encoder1PinB, INPUT);
  pinMode(encoder2PinB, INPUT);

  attachInterrupt(digitalPinToInterrupt(encoder1PinA), handleEncoder1A, RISING);
  attachInterrupt(digitalPinToInterrupt(encoder2PinA), handleEncoder2A, RISING);
  attachInterrupt(digitalPinToInterrupt(encoder1PinB), handleEncoder1B, RISING);
  attachInterrupt(digitalPinToInterrupt(encoder2PinB), handleEncoder2B, RISING);

  previousTime = micros(); // Initialize previousTime
}

void loop() {
  int target = encoder1Count;

  float kp = 0.5; // Example PID parameters, tune these
  float kd = 0.1;
  float ki = 0.08;
  float u = pidController(target, kp, kd, ki);

  moveMotor(DIR1, PWM1, 200); // Move motor 1
  moveMotor(DIR2, PWM2, 200+u);   // Control motor 2 speed

  Serial.print(encoder1Count);
  Serial.print(" | ");
  Serial.print(encoder2Count);
  Serial.println();
}

void handleEncoder1A() {
  if (digitalRead(encoder1PinA) == digitalRead(encoder1PinB)) {
    encoder1Count++;
  } else {
    encoder1Count--;
  }
}

void handleEncoder1B() {
  if (digitalRead(encoder1PinA) == digitalRead(encoder1PinB)) {
    encoder1Count--;
  } else {
    encoder1Count++;
  }
}

void handleEncoder2A() {
  if (digitalRead(encoder2PinA) == digitalRead(encoder2PinB)) {
    encoder2Count++;
  } else {
    encoder2Count--;
  }
}

void handleEncoder2B() {
  if (digitalRead(encoder2PinA) == digitalRead(encoder2PinB)) {
    encoder2Count--;
  } else {
    encoder2Count++;
  }
}

void moveMotor(int dirPin, int pwmPin, float speed) {
  if (speed > 255) {
    speed = 255;
  }

  int direction = 0;
  digitalWrite(dirPin, direction);
  analogWrite(pwmPin, speed);
}

float pidController(int target, float kp, float kd, float ki) {
  long currentTime = micros();
  float deltaT = ((float)(currentTime - previousTime)) / 1.0e6;

  int e = encoder1Count - target; // Use encoder1Count for PID control
  float eDerivative = (e - ePrevious) / deltaT;
  eIntegral = eIntegral + e * deltaT;

  float u = (kp * e) + (kd * eDerivative) + (ki * eIntegral);

  // Adjust motor 2 speed based on the difference in encoder counts between motor 1 and motor 2
float maxSpeedDifference = 0; // Max speed difference between motors
float encoderDifference = encoder2Count - encoder1Count;
if (abs(encoderDifference) > maxSpeedDifference) {
  // If the difference exceeds the maximum allowed difference, adjust u
  if (encoderDifference > 0) {
    u -= abs(encoderDifference - maxSpeedDifference) * 0.1; // Decrease u
  } 
  else {
    u += abs(maxSpeedDifference - encoderDifference) * 0.1; // Increase u
  }
}

  previousTime = currentTime;
  ePrevious = e;

  return u;
}
