/*
Adafruit Arduino - Lesson 3. RGB LED
*/

int redPin = 11;
int greenPin = 10;
int bluePin = 9;
int redPin2 = 6;
int greenPin2 = 5;
int bluePin2 = 3;
int potPin = A0;
int pot_in;
//uncomment this line if using a Common Anode LED
//#define COMMON_ANODE

void setup()
{
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
  pinMode(redPin2, OUTPUT);
  pinMode(greenPin2, OUTPUT);
  pinMode(bluePin2, OUTPUT);  
}

void loop()
{
  pot_in = analogRead(potPin);
  Serial.println(pot_in);
  if (pot_in<200){
  setColor1(random(0,255), random(0,255), random(0,255));  // red
  setColor2(random(0,255), random(0,255), random(0,255));  // red
  delay(50);
  }
  
  else if (pot_in >= 200 && pot_in <400){
  setColor1(random(0,255), random(0,255), random(0,255));  // red
  setColor2(random(0,255), random(0,255), random(0,255));  // red
  delay(random(50,2000));
  }
  
  else if (pot_in >= 400 && pot_in <600){
  setColor1(255, 0, 0);setColor2(255, 0, 0);  // red
  delay(1000);
  setColor1(0, 255, 0);setColor2(0,255, 0);  // green
  delay(1000);
  setColor1(0, 0, 255);setColor2(0, 0, 255);  // blue
  delay(1000);
  setColor1(255, 255, 0);setColor2(255, 255, 0);  // yellow
  delay(1000);  
  setColor1(80, 0, 80); setColor2(80, 0, 80);  // purple
  delay(1000);
  setColor1(0, 255, 255);setColor2(0, 255, 255);  // aqua
  delay(1000);  
  }
  
  else if (pot_in >= 600 && pot_in <800){
    Serial.println("new loop");
    for (float i=0.01;i<3.1415;i=i+0.01){
  setColor1(255*((sin(i)/2)),0,0);
  setColor2(255*(0.5+(cos(i)/2)),0,0);
  Serial.print("sin(i) = "); Serial.print(sin(i));
  Serial.print("cos(i) = ");
  Serial.println(cos(i));
  delay(50);  
  }
  }
  
  else if (pot_in >= 800){
  // fade between reds and yellos
 for(int fadevalue = 5; fadevalue<=255; fadevalue = fadevalue + 5){ 
  setColor1(fadevalue,0,0);
  setColor2(fadevalue,0,0);
  delay(50);
 }
 for(int fadevalue = 255; fadevalue>=0; fadevalue = fadevalue - 5){ 
  setColor1(fadevalue,0,0);
  setColor2(fadevalue,0,0);
  delay(50);
 }
 for(int fadevalue = 5; fadevalue<=255; fadevalue = fadevalue + 5){ 
  setColor1(fadevalue,fadevalue/2,0);
  setColor2(fadevalue,fadevalue/2,0);
  delay(50);
 }
  for(int fadevalue = 255; fadevalue>=0; fadevalue = fadevalue - 5){ 
  setColor1(fadevalue,fadevalue/2,0);
  setColor2(fadevalue,fadevalue/2,0);
  delay(50);
 }
 
}
}

void setColor1(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

void setColor2(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin2, red);
  analogWrite(greenPin2, green);
  analogWrite(bluePin2, blue);  
}

