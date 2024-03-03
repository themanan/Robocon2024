#define CH1 53
#define CH2 52

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

// Integers to represent values from sticks and pots
int ch1Value;
int ch2Value;
  
// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
 
void setup(){
  // Set up serial monitor
  Serial.begin(115200);
  
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

  // Set all pins as inputs
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
}
 
 
void loop() {
  
  // Get values for each channel
  ch1Value = readChannel(CH1, -255, 255, 0);
  ch2Value = readChannel(CH2, -255, 255, 0);
  if (ch2Value>10 and ch1Value<ch2Value){  
    move_forward();
    Serial.println("MOVING F");
  }
  else if (ch2Value<-10 and ch1Value<abs(ch2Value)){
    move_backward();
    Serial.println("MOVING B");
  }
  else if (ch1Value>10 and ch2Value<ch1Value){
    move_right();
    Serial.println("MOVING R");
  }
  else if (ch1Value<-10 and ch2Value>(ch1Value)){
    move_left();
    Serial.println("MOVING L");
  }
  else{
    stop_motor();
  }
  Serial.println(" | Ch1: ");
  Serial.println(ch1Value);
  Serial.println(" | Ch2: ");
  Serial.println(ch2Value);
  // delay(500);
}

// void loop(){
//   if (ch1Value>0){
//     move_forward();
//   }
//   if (ch1Value<0){
//     move_backward();
//   }
//   if (ch2Value<0){
//     move_leftward();
//   }
//   if (ch2Value>0){
//     move_rightward();
//   }
  
//   delay(5000);
//   move_backward();
//   delay(5000);
// }

  
void move_forward(){
  analogWrite(enA, 255);
	analogWrite(enB, 255);
  analogWrite(enC, 255);
	analogWrite(enD, 255);

  digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);

  digitalWrite(in5, HIGH);
	digitalWrite(in6, LOW);
	digitalWrite(in7, HIGH);
	digitalWrite(in8, LOW);
}


void move_backward(){
  analogWrite(enA, 255);
	analogWrite(enB, 255);
  analogWrite(enC, 255);
	analogWrite(enD, 255);

  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);

  digitalWrite(in5, LOW);
	digitalWrite(in6, HIGH);
	digitalWrite(in7, LOW);
	digitalWrite(in8, HIGH);

}

void move_left(){
  analogWrite(enA, 255);
	analogWrite(enB, 255);
  analogWrite(enC, 255);
	analogWrite(enD, 255);

  digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
  digitalWrite(in5, HIGH);
	digitalWrite(in6, LOW);
	digitalWrite(in7, LOW);
	digitalWrite(in8, HIGH);
}

void move_right(){
  analogWrite(enA, 255);
	analogWrite(enB, 255);
  analogWrite(enC, 255);
	analogWrite(enD, 255);

  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
	digitalWrite(in6, HIGH);
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