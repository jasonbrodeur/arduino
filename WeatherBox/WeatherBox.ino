
/*
Insert general comments here:

* Wiring Setup:
Sun cycle (8 leds: 7 yellow, 1 blue) - wired in digital pins 2-9. 
Sunrise in pin position 2, followed sequentially by rest of sun cycle. Night light is in pin 9

* Servo in digital 10
*Piezo in digital 12
* Stay In in digital A4
* Go Outside in digital A5

* Weather Indicators:
Sun in digital 13
Sun/Cloud in A0
Cloudy in A1
Raindrops in 11 (through A4?, or just a big one?
Fog in A2

*/
#define NOTE_C3  131
#define NOTE_C4  262
#define NOTE_C5  523
#define NOTE_C6  1047

//#include <pitches.h>
#include <Servo.h>
#include <math.h>
Servo myservo;  // create servo object to control a servo

// Music
int melody[] = {NOTE_C4, 0, NOTE_C4, 0, NOTE_C5,0};
//int melody[] = {0, 0, 0, 0, 0,0};

int noteDurations[] = {2, 2, 2, 2, 1,4};


//Lat / Long information (converted to radians)
double lati  = 48.4222*0.0174532925; //latitude in radians
double longi = 123.3657*0.0174532925; //longitude in radians
double doy = 162; // June 10 is the 161st day of the year
double tz = -7; // Time offset to UTC (PDT is -7 from UTC)

const double pi = 3.141592653589;
int sunpin;
int val;

// **************************** Set up some pretend data: ***************
// 1 = Sunny; 2=Sun+Cloud; 3=Cloud; 4=Rain; 5=Foggy
//int weather = 1;
//int temp = 0; // temperature (in C)
// Sun angle information
//double time_input = 2300;
//int time;
int time_ctr;
//double temp_array[24]={4,5,18,7,18,10,18,14,17,18,21,22,24,22,21,18,16,14,12,11,9,7,6,6};
//int wx_array[24]={1,2,1,4,1,3,1,1,1,2,3,4,4,3,2,1,1,2,3,4,4,3,2,1};
// demo stuff:
double temp_array[8]={0,6,12,17,23,20,16,12};
int wx_array[8]={1,2,3,4,1,4,1,2};

char wx_types[5]={'Sunny','Sun+Cloud','Cloudy','Rainy','Foggy'};
// ****************************************** SETUP ******
void setup() {
  // put your setup code here, to run once:

// set upp the servo:
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object
  // Set up serial 
  Serial.begin(9600);
    pinMode(2, OUTPUT);pinMode(3,OUTPUT);pinMode(4, OUTPUT);pinMode(5,OUTPUT);
    pinMode(6, OUTPUT);pinMode(7,OUTPUT);pinMode(8, OUTPUT);pinMode(9,OUTPUT);
       pinMode(11, OUTPUT);pinMode(12,OUTPUT);pinMode(13, OUTPUT);
  pinMode(A0, OUTPUT);pinMode(A1,OUTPUT);pinMode(A3,OUTPUT);
    pinMode(A4, OUTPUT);pinMode(A5,OUTPUT);
}
// ************************************************

// ****************************************** Main Loop ******

void loop() {
  for(time_ctr = 0; time_ctr <8; time_ctr++){ //  for(time_ctr = 0; time_ctr <24; time_ctr++){
    int time_input = time_ctr*300;
    int temp = temp_array[time_ctr];
    int wx = wx_array[time_ctr];
    
 // Play music at change
 for (int thisNote = 0; thisNote < 7; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(12, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(12);
  }
    
    
 double time = time_input;// - (tz*100); // time of day (in UTC)
 //Serial.print("time_tmp = "); Serial.println(time);
//if(time_tmp < 0){time = 2400+time_tmp;}
//else if(time_tmp >=2400){time = time_tmp - 2400;}
//else{time = time_tmp;}

double time2 = time/100;
int hr = floor(time2);
int minute = time - (hr*100);
int minofday = hr*60 + minute;
Serial.print("Time = "); Serial.println(time);
Serial.print("Temperature = "); Serial.println(temp);
Serial.print("Wx = "); Serial.println(wx);
//Serial.print("Hr = "); Serial.println(hr); 
//Serial.print("Minute = "); Serial.println(minute); 
//Serial.print("Minute Of Day = "); Serial.println(minofday);

// call the function suntimes to figure out which led to light up
int sunpin = suntimes(lati, longi, doy, tz, time, minofday);
for (int tmp_pin = 2; tmp_pin <10; tmp_pin++){digitalWrite(tmp_pin,LOW);}
digitalWrite(sunpin,HIGH); // light the proper pin

// function here that parses weather information and lights the appropriate pin
 digitalWrite(13,LOW);digitalWrite(A0,LOW); digitalWrite(A1,LOW); digitalWrite(A2,LOW); analogWrite(11,0);//digitalWrite(A4,LOW); digitalWrite(A5,LOW);
 switch (wx) {
    case 1: // Sunny
      digitalWrite(13,HIGH);
      Serial.println("Sunny");break;
    case 2: // Sun + Cloud
      digitalWrite(A0,HIGH);
      Serial.println("Sun and Cloud");break;
    case 3: // Cloudy
      digitalWrite(A1,HIGH);
      Serial.println("Cloudy");break;
    case 4: // Rain
      digitalWrite(A1,HIGH);
      //analogWrite(11,255);
      for (int bright = 0;  bright <52; bright = bright+1){analogWrite(11,bright*5); delay(50);}
      for (int bright = 51; bright >-1;   bright = bright-1){analogWrite(11,bright*5); delay(50);}
     
    //for (int bright = 255; bright >0; bright = bright+5){analogWrite(A2,bright); delay(50);}
     // for (int bright = 0; bright <256; bright = bright+5){analogWrite(A2,bright); delay(50);}
      //for (int bright = 255; bright >0; bright = bright+5){analogWrite(A2,bright); delay(50);}
      //analogWrite(A2,HIGH);
      Serial.println("Rain");break;
      // put in the raindrops
    case 5: //foggy
      digitalWrite(A2,HIGH);
      Serial.println("Foggy");break;
      // if nothing else matches, do the default
      // default is optional
  }
  
// Controls the temperature output:
val = map(temp, -20, 37, 159, 0);     // scale it to use it with the servo (value between 0 and 180) 
  myservo.write(val);                  // sets the servo position according to the scaled value 

// Check the weather and actuate the GO OUTSIDE / STAY in based on certain conditions
if(time > 0 & time < 1700 & temp>17 & temp < 28 & wx >=1 & wx <=2){
 for (int i = 1;  i <5; i = i+1){
   analogWrite(A5,255); 
 int noteDuration = 1000 / 1;
    tone(12, NOTE_C6, noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
  analogWrite(A5,0);
 delay(200);
 noTone(12);

 }

}


delay(4000);  
} // Ends the temporary time loop;
}
// ************************************************

// ****************************************** Sun Position Function ******
// function here that takes the time (from the weather update??) and then calculates where the current time lies between SR, SN and SS
// Can we abstract everything to this function, so that it just outputs which pin to light up?
//http://pveducation.org/pvcdrom/properties-of-sunlight/solar-time#TC 
int suntimes(double lat_in, double long_in, double doy_in, double tz_in, double time_in, double minofday){
  // fractional year (gamma)
  double beta = 0.9863013698*(doy_in-81); 
   //    Serial.print("beta = "); Serial.println(beta); 
double decl =  asin( sin(23.45*0.0174532925) * sin(beta*0.0174532925)); // in radians
  // Serial.print("decl = "); Serial.println(decl); 
 
    double gamma = ((2*pi) / 365) * (doy_in - 1 + (((-1*tz_in)-12)/24));
  //double gamma = asin( sin(23.45*0.0174532925) * sin( 0.0174532925*(360/365)*(doy_in-81) ) );
  //Serial.print("Gamma = "); Serial.println(gamma); 

  // equation of time (in minutes)
  double eqtime = 229.18*(0.000075+ 0.001868*cos(gamma) - 0.032077*sin(gamma) - 0.014615*cos(2*gamma) - 0.040849*sin(2*gamma));
   // Serial.print("eqtime = "); Serial.println(eqtime); 

  // Solar declination angle (in radians)
  //double decl = 0.006918 - 0.399912*cos(gamma) + 0.070257*sin(gamma) - 0.006758*cos(2*gamma) + 0.000907*sin(2*gamma) - 0.002697*cos(3*gamma) + 0.00148*sin(3*gamma);
    //Serial.print("decl = "); Serial.println(decl); 

   // hour angle for the day (in degrees) 
   double a = cos(90.833*0.0174532925);
   double b = cos(lat_in)*cos(decl);
   double c = a/b;
  
   double ha_rise_set = acos(c - (tan(lat_in)*tan(decl)));
  //  double ha_rise_set = acos( ( ((cos(90.833*0.0174532925))/ (cos(lat_in)*cos(decl)))  - tan(lat_in)*tan(decl) )*0.0174532925 );
  
   //  Serial.print("ha_rise_set = "); Serial.println(ha_rise_set); 
 
  // sunrise/sunset (in minutes from 0000 UTC)
  double sunrise_minsUTC = 720 + 4*( (long_in*57.2957795-ha_rise_set*57.2957795) ) - eqtime;
  double sunset_minsUTC  = 720 + 4*( (long_in*57.2957795+ha_rise_set*57.2957795) ) - eqtime;
  double snoon_minsUTC   = 720 + 4*(long_in*57.2957795) - eqtime;
  double sunmins = sunset_minsUTC - sunrise_minsUTC;
// Convert to mins from Local time:
  double sunrise_mins_local = sunrise_minsUTC + tz_in*60;  
    double sunset_mins_local = sunset_minsUTC + tz_in*60;  
     // double sunrise_mins_local = sunrise_minsUTC + tz_in*60;  
  //Serial.println("Suntimes:");
  //Serial.print("sunrise_mins_local: ");Serial.println(sunrise_mins_local);
  //Serial.print("sunset_mins_local: ");Serial.println(sunset_mins_local);
  
  //Serial.println(sunset_mins_local);
//  Serial.println(snoon_minsUTC);
 // Serial.print("Sunmins: "); Serial.println(sunmins);
  
  // What we want to do here is divide sunmins into six equal segments.
  double seg_length = sunmins/6;
  //Serial.print("seg_length: "); Serial.println(seg_length);
    
  //If structure to figure out which pin to light for the sun position;  
  if(minofday > sunrise_mins_local & minofday < sunrise_mins_local + seg_length/2){sunpin=1;}
  else if(minofday > sunrise_mins_local+ seg_length/2 & minofday < sunrise_mins_local + 3*seg_length/2){sunpin=2;}
  else if(minofday > sunrise_mins_local+ 3*seg_length/2 & minofday < sunrise_mins_local + 5*seg_length/2){sunpin=3;}
  else if(minofday > sunrise_mins_local+ 5*seg_length/2 & minofday < sunrise_mins_local + 7*seg_length/2){sunpin=4;}
  else if(minofday > sunrise_mins_local+ 7*seg_length/2 & minofday < sunrise_mins_local + 9*seg_length/2){sunpin=5;}
  else if(minofday > sunrise_mins_local+ 9*seg_length/2 & minofday < sunrise_mins_local + 11*seg_length/2){sunpin=6;}
else{sunpin = 8;}
 // Serial.print("minofday: "); Serial.println(minofday);
  sunpin = sunpin + 1;
  Serial.print("sunpin: "); Serial.println(sunpin);
  return sunpin;
}

// ************************************************

