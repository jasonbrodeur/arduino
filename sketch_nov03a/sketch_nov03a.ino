/*
Adafruit Arduino - Lesson 3. RGB LED
*/

int redPin = 11;
int greenPin = 10;
int bluePin = 9;
int redPin2 = 6;
int greenPin2 = 5;
int bluePin2 = 4;

//uncomment this line if using a Common Anode LED
//#define COMMON_ANODE

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
  pinMode(redPin2, OUTPUT);
  pinMode(greenPin2, OUTPUT);
  pinMode(bluePin2, OUTPUT);  
}

void loop()
{
  setColor1(255, 0, 0);  // red
  delay(1000);
  setColor1(0, 255, 0);  // green
  delay(1000);
  setColor1(0, 0, 255);  // blue
  delay(1000);
  setColor1(255, 255, 0);  // yellow
  delay(1000);  
  setColor1(80, 0, 80);  // purple
  delay(1000);
  setColor1(0, 255, 255);  // aqua
  delay(1000);
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

