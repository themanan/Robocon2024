#define CH1 52
#define CH2 53
#include <math.h>
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
int A;
int B;

void setup() {
  // Set all the motor control pins to outputs
  Serial.begin(9600);
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
   // Set up serial monitor
  Serial.begin(115200);
  
  // Set all pins as inputs
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
}
void diagonalone(int dir,int speed){
  if (dir==1)
  {
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    digitalWrite(in7,LOW);
    digitalWrite(in8,HIGH);
    analogWrite(enB,speed);
    analogWrite(enD,speed);
  }
  else
  {
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    digitalWrite(in7,HIGH);
    digitalWrite(in8,LOW);
    analogWrite(enB,speed);
    analogWrite(enD,speed);
  }
}
void diagonaltwo(int dir,int speed){
  if (dir==1)
  {
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in5,LOW);
    digitalWrite(in6,HIGH);
    analogWrite(enA,speed);
    analogWrite(enC,speed);
  }
  else
  {
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in5,HIGH);
    digitalWrite(in6,LOW);
    analogWrite(enA,speed);
    analogWrite(enC,speed);
  }
}
void traverse(int speed1, int speed2)
{ // Get values for each channel
  //Serial.println(" | Ch1: ");
  //Serial.println(ch1Value);
  //Serial.println(" | Ch2: ");
  //Serial.println(ch2Value);
  //delay(500);
  
  //Quarter 1
  if (ch1Value>0 && ch2Value>0)
  {
    if(ch1Value>ch2Value)
    {
      diagonalone(1,ch1Value);
      diagonaltwo(1,ch2Value);
      Serial.println("0 to 45");
    }
    else if(ch1Value<ch2Value)
    {
      diagonalone(1,ch2Value);
      diagonaltwo(0,ch1Value);
      Serial.println("90 to 45");
    }
  }
  //Quarter 2
  if (ch1Value>0 && ch2Value<0)
  {
    if(ch1Value>abs(ch2Value))
    {
      diagonalone(0,ch1Value);
      diagonaltwo(1,abs(ch2Value));
      Serial.println("0 to 315");
    }
    else if(ch1Value<abs(ch2Value))
    {
      diagonalone(0,abs(ch2Value));
      diagonaltwo(0,ch1Value);
      Serial.println("315 to 270");
    }
  }
  //Quarter 3
  if (ch1Value<0 && ch2Value<0)
  {
    if(abs(ch1Value)>abs(ch2Value))
    {
      diagonalone(0,abs(ch1Value));
      diagonaltwo(0,abs(ch2Value));
      Serial.println("225 to 180");
    }
    else if(abs(ch1Value)<abs(ch2Value))
    {
      diagonalone(0,abs(ch2Value));
      diagonaltwo(1,abs(ch1Value));
      Serial.println("225 to 270");
    }
  }
  //Quarter 4
  if (ch1Value<0 && ch2Value>0)
  {
    if(abs(ch1Value)>ch2Value)
    {
      diagonalone(1,abs(ch1Value));
      diagonaltwo(0,ch2Value);
      Serial.println("180 to 135");
    }
    else if(abs(ch1Value)<ch2Value)
    {
      diagonalone(1,ch2Value);
      diagonaltwo(1,abs(ch1Value));
      Serial.println("90 to 135");
    } 
  }

}

void loop() 
{
  ch1Value = readChannel(CH1, -255, 255, 0);
  ch2Value = readChannel(CH2, -255, 255, 0);
  if(ch1Value<10 && ch1Value>-10 && (ch2Value>10 || ch2Value<-10))
  {
    ch1Value=0;
    traverse(ch1Value,ch2Value);
    Serial.println("ch1 NULL");
    delay(100);
  }
  else if(ch2Value<10 && ch2Value>-10 && (ch1Value>10 || ch1Value<-10))
  {
    ch2Value=0;
    traverse(ch1Value,ch2Value);
    Serial.println("ch2 NULL");
    delay(100);
  }
  else if (ch1Value<10 && ch1Value>-10 && ch2Value<10 && ch2Value>-10)
  {
    ch1Value=0;
    ch2Value=0;
    Serial.println("ch1 & ch2 NULL");
    delay(100);
  }
  else
  {
    traverse(ch1Value,ch2Value);
    delay(100);
  }
}

