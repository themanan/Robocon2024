// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

// Motor C connections
int enC = 13;
int in5 = 11;
int in6 = 10;
// Motor D connections
int enD = 12;
int in7 = 6;
int in8 = 2;

//Set Motor speeds
int A = 255;
int B = 255;
int C = 255;
int D = 255;

void setup() {
	// Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);

  pinMode(enC, OUTPUT);
	pinMode(enD, OUTPUT);
	pinMode(in5, OUTPUT);
	pinMode(in6, OUTPUT);
	pinMode(in7, OUTPUT);
	pinMode(in8, OUTPUT);
	
	// Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
	digitalWrite(in6, LOW);
	digitalWrite(in7, LOW);
	digitalWrite(in8, LOW);
}

void loop(){
  move_backward();
  delay(5000);
  
}

void set_speed(){
  analogWrite(enA, A);
	analogWrite(enB, B);
  analogWrite(enC, C);
	analogWrite(enD, D);
}
void move_forward(){
  set_speed();
  digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);

  digitalWrite(in5, HIGH);
	digitalWrite(in6, LOW);
	digitalWrite(in7, HIGH);
	digitalWrite(in8, LOW);
}

void move_backward(){
  set_speed();
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
	digitalWrite(in6, HIGH);
	digitalWrite(in7, HIGH);
	digitalWrite(in8, LOW);
}


void move_left(){
  set_speed();
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
  digitalWrite(in5, HIGH);
	digitalWrite(in6, LOW);
	digitalWrite(in7, LOW);
	digitalWrite(in8, HIGH);
}

void move_right(){
  set_speed();
  digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
  digitalWrite(in5, HIGH);
	digitalWrite(in6, LOW);
	digitalWrite(in7, LOW);
	digitalWrite(in8, HIGH);
}

void move_forward_left(){
  set_speed();
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
  digitalWrite(in5, HIGH);
	digitalWrite(in6, LOW);
	digitalWrite(in7, HIGH);
	digitalWrite(in8, LOW);
}

void move_forward_right(){
  set_speed();
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
  digitalWrite(in5, HIGH);
	digitalWrite(in6, LOW);
	digitalWrite(in7, HIGH);
	digitalWrite(in8, LOW);
}

void move_backward_left(){
  set_speed();
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
  digitalWrite(in5, HIGH);
	digitalWrite(in6, LOW);
	digitalWrite(in7, HIGH);
	digitalWrite(in8, LOW);
}

void move_backward_right(){
  set_speed();
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
  digitalWrite(in5, HIGH);
	digitalWrite(in6, LOW);
	digitalWrite(in7, HIGH);
	digitalWrite(in8, LOW);
}

void stop_motor(){
 digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
	digitalWrite(in6, LOW);
	digitalWrite(in7, LOW);
	digitalWrite(in8, LOW); 
}


// PREVIOUS CODE OR REFERENCE CODE
// void loop() {
// 	directionControl();
	// delay(1000);
	// speedControl();
	// delay(1000);
//}

// This function lets you control spinning direction of motors
// void directionControl() {
	// Set motors to maximum speed
	// For PWM maximum possible values are 0 to 255
	// analogWrite(enA, 255);
	// analogWrite(enB, 255);
  // analogWrite(enC, 255);
	// analogWrite(enD, 255);
	// Turn on motor A & B
	// digitalWrite(in1, HIGH);
	// digitalWrite(in2, LOW);
	// digitalWrite(in3, HIGH);
	// digitalWrite(in4, LOW);
  // digitalWrite(in5, HIGH);
	// digitalWrite(in6, LOW);
	// digitalWrite(in7, HIGH);
	// digitalWrite(in8, LOW);
	// delay(2000);
	
	// Now change motor directions
	// digitalWrite(in1, LOW);
	// digitalWrite(in2, HIGH);
	// digitalWrite(in3, LOW);
	// digitalWrite(in4, HIGH);
  // digitalWrite(in5, LOW);
	// digitalWrite(in6, HIGH);
	// digitalWrite(in7, LOW);
	// digitalWrite(in8, HIGH);
	// delay(2000);
	
	// Turn off motors
	// digitalWrite(in1, LOW);
	// digitalWrite(in2, LOW);
	// digitalWrite(in3, LOW);
	// digitalWrite(in4, LOW);
  // digitalWrite(in5, LOW);
	// digitalWrite(in6, LOW);
	// digitalWrite(in7, LOW);
	// digitalWrite(in8, LOW);
//}

// This function lets you control speed of the motors
// void speedControl() {
// 	// Turn on motors
// 	digitalWrite(in1, LOW);
// 	digitalWrite(in2, HIGH);
// 	digitalWrite(in3, LOW);
// 	digitalWrite(in4, HIGH);
	
// 	// Accelerate from zero to maximum speed
// 	for (int i = 0; i < 256; i++) {
// 		analogWrite(enA, i);
// 		analogWrite(enB, i);
// 		delay(20);
// 	}
	
// 	// Decelerate from maximum speed to zero
// 	for (int i = 255; i >= 0; --i) {
// 		analogWrite(enA, i);
// 		analogWrite(enB, i);
// 		delay(20);
// 	}
	
// 	// Now turn off motors
// 	digitalWrite(in1, LOW);
// 	digitalWrite(in2, LOW);
// 	digitalWrite(in3, LOW);
// 	digitalWrite(in4, LOW);
//}