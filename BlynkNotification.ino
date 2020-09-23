#define BLYNK_PRINT Serial // Defines the object that is used for printing
#include <ESP8266WiFi.h> // It provides ESP8266 specific Wi-Fi routines that we are calling to connect to the network
#include <BlynkSimpleEsp8266.h> // It handles all the connection routines and data exchange between hardware, Blynk Cloud, and Blynk app
char auth[] = "1c777027bb32498c92ffbaca882f5688"; // Device Authentication Token to get the hardware online and connect it to Blynk Cloud
const int sensorPin = 00; // connect digital output pin D0 of Moisture Sensor to pin D3 of NodeMCU development board, which connects to GPIO 00 of ESP8266 microcontroller
int sensorState = 0;
int lastState = 0;
int c;
const int redPin = 4; //connect pin R of RGB LED to D2 of NodeMCU development board, which connects to GPIO 04 of ESP8266 microcontroller
const int greenPin = 12; //connect pin G of RGB LED to D6 of NodeMCU development board, which connects to GPIO 12 of ESP8266 microcontroller
const int bluePin = 14; //connect pin B of RGB LED to D5 of NodeMCU development board, which connects to GPIO 14 of ESP8266 microcontroller
void setup()
{
Serial.begin(9600); //Baud Rate 9600
Blynk.begin(auth, "INTEX", "77777777"); // "INTEX" and "77777777" are the Service Set IDentifier and Password of the Access Point respectively
pinMode(sensorPin, INPUT); // declaring D3 of NodeMCU development board as INPUT pin
}
void loop()
{
analogWrite(redPin, 280);
analogWrite(greenPin, 300);
analogWrite(bluePin, 300); 
Blynk.run();
sensorState = digitalRead(sensorPin);
if (sensorState == 1 && lastState == 0) 
  {
  Blynk.notify("Water your plants"); //Initial notification to water the plants
  lastState = 1;
  delay(100);
  }
if (sensorState == 1 && lastState == 1)
  {
  delay(1000);
  c++;
    if (c==600)
    {
    Blynk.notify("plants have not been watered yet"); //Second notification after 10 mins from the initial notification, if plants haven't been watered yet 
    c=0;
    }
  }
else 
  {
  lastState = 0;
  delay(100);
  }
delay(10);
}
