#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h> // It provides ESP8266 specific Wi-Fi routines that we are calling to connect to the network.
#include <BlynkSimpleEsp8266.h> // It handles all the connection routines and data exchange between hardware, Blynk Cloud, and app.
char auth[] = "1c777027bb32498c92ffbaca882f5688"; // Device Authentication Token to get the hardware online and connect it to Blynk Cloud
const int sensorPin = 00; // connect D0 of Moisture Sensor to D3 of NodeMCU Kit, which connects to GPIO 00 of ESP8266.
int sensorState = 0; // measures 
int lastState = 0;
int c;
double analogValue = 0.0;
const int redPin = 4; //connect R of RGB LED to D2 of NodeMCU Kit, which connects to GPIO 04 of ESP8266.
const int greenPin = 12; //connect G of RGB LED to D6 of NodeMCU Kit, which connects to GPIO 12 of ESP8266
const int bluePin = 14; //connect B of RGB LED to D5 of NodeMCU Kit, which connects to GPIO 14 of ESP8266
void setup()
{
Serial.begin(9600); //Baud Rate 9600
Blynk.begin(auth, "INTEX", "77777777"); // "INTEX" and "77777777" are the Service Set IDentifier and Password of the Access Point respectively.
pinMode(sensorPin, INPUT);
}
void loop()
{
analogWrite(redPin, 280);
analogWrite(greenPin, 300);
analogWrite(bluePin, 300); 
Blynk.run();
analogValue = analogRead(A0); // measuring the analog value from Moisture Sensor
if (analogValue < 300.75 )
{
analogWrite(redPin, 0);
analogWrite(greenPin, 0);
analogWrite(bluePin, 1000);
Blynk.notify("stop watering your plants");
}
sensorState = digitalRead(sensorPin);
Serial.println(sensorState);
if (sensorState == 1 && lastState == 0) 
{
Serial.println("needs water, sending notification");
Blynk.notify("Water your plants");
lastState = 1;
delay(1000);
}
if (sensorState == 1 && lastState == 1)
{
Serial.println("plants have not been watered yet");
delay(1000);
c++;
if (c==30)
{
Blynk.notify("plants have not been watered yet");
Serial.println(", sending notification");
c=0;
}
}
else 
{
Serial.println("does not need water");
lastState = 0;
delay(1000);
}
delay(100);
}
