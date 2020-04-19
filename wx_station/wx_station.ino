#include <dht.h>

dht DHT; // create dht object
int dhtPin = 2; // the number of the DHT11 sensor pin

void setup() {
Serial.begin(9600); // Initialize the serial port and set the baud rate to 9600
delay(500); // Delay to let the system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor  
}

void loop() {
// read DHT11 and judge the state according to the return value
int chk = DHT.read11(dhtPin);
switch (chk)
{
case DHTLIB_OK: // When read data successfully, print temperature and humidity data
Serial.print("Humidity: ");
Serial.print(DHT.humidity);
Serial.print("%, Temperature: ");
Serial.print(DHT.temperature);
Serial.println("C");
break;
case DHTLIB_ERROR_CHECKSUM: // Checksum error
Serial.println("Checksum error");
break;
case DHTLIB_ERROR_TIMEOUT: // Time out error
Serial.println("Time out error");
break;
default: // Unknown error
Serial.println("Unknown error");
break;
}
delay(5000);
}
