/*
 Fade

 This example shows how to fade an LED on pin 9
 using the analogWrite() function.

 The analogWrite() function uses PWM, so if
 you want to change the pin you're using, be
 sure to use another PWM capable pin. On most
 Arduino, the PWM pins are identified with 
 a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

 This example code is in the public domain.
 */
//attached to pins 3,5,6,9,10,11
const float pi = 3.1415926;
float x = 0;
int leds[] = {3,5,6,9,10,11};           // the PWM pin the LED is attached to
int brightness = 0;    // how bright the LED is
//int fadeAmount = 5;    // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
   // Serial.begin(9600);
  // declare pin 9 to be an output:
for (int led_pin = 0; led_pin<6; led_pin++){
  pinMode(leds[led_pin], OUTPUT);
}
}

// the loop routine runs over and over again forever:
void loop() {
for (float ctr = 0; ctr < 10000*pi; ctr++){
x = ctr/500;
analogWrite(leds[0],255*abs(sin(x)));
analogWrite(leds[1],255*abs(sin(2*x)));
analogWrite(leds[2],255*abs(sin(3*x)));
analogWrite(leds[3],255*abs(sin(4*x)));
analogWrite(leds[4],255*abs(sin(5*x)));
analogWrite(leds[5],255*abs(sin(6*x)));
delay(50);

/*
Serial.print(ctr);
Serial.print(" ");
Serial.print(x);
Serial.print(" ");
Serial.print(255*abs(sin(x)));
Serial.print(" ");
Serial.print(255*abs(sin(2.5*x)));
Serial.print(" ");
Serial.println(255*abs(sin(3.3*x)));
*/

}
  // wait for 30 milliseconds to see the dimming effect
}
