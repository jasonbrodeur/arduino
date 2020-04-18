// set pin numbers:
int led1Pin = 4; // the number of the LED1 pin
int led2Pin = 5; // the number of the LED2 pin
int daddy = 1;
//#include "pitches.h"

void setup() {
  // initialize the LED pin as an output:
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
}

void loop() {
  if (daddy < 10){
      tone(6, 2000, 500);}
      else {
        tone(6, 500, 500);}

    digitalWrite(led1Pin, HIGH); // turn the LED1 on
  digitalWrite(led2Pin, LOW); // turn the LED2 off
  delay(50); // wait for a second
  digitalWrite(led1Pin, LOW); // turn the LED1 off
  digitalWrite(led2Pin, HIGH); // turn the LED2 on
  delay(50); // wait for a second
  daddy++;
  if (daddy > 20){
      daddy = 1;
     }
}
