// Arduino Relay Control Code
#define relay0 2
#define relay1 3
#define relay2 4
#define relay3 5
#define relay4 6
#define relay5 7
#define relay6 8
#define relay7 9
#define interval 1000

void setup() {

  pinMode(relay0, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);

}
void loop(){

   digitalWrite(relay0, HIGH);
   delay(interval);
   digitalWrite(relay0, LOW);
   delay(interval);

   digitalWrite(relay1, HIGH);
   delay(interval);
   digitalWrite(relay1, LOW);
   delay(interval);

   digitalWrite(relay2, HIGH);
   delay(interval);
   digitalWrite(relay2, LOW);
   delay(interval);

   digitalWrite(relay3, HIGH);
   delay(interval);
   digitalWrite(relay3, LOW);
   delay(interval);

   digitalWrite(relay4, HIGH);
   delay(interval);
   digitalWrite(relay4, LOW);
   delay(interval);

   digitalWrite(relay5, HIGH);
   delay(interval);
   digitalWrite(relay5, LOW);
   delay(interval);

   digitalWrite(relay6, HIGH);
   delay(interval);
   digitalWrite(relay6, LOW);
   delay(interval);

   digitalWrite(relay7, HIGH);
   delay(interval);
   digitalWrite(relay7, LOW);
   delay(interval);
}