#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "1c777027bb32498c92ffbaca882f5688";
const int sensorPin = 00;
int sensorState = 0;
int lastState = 0;
int c;
double analogValue = 0.0;
const int redPin = 4;
const int greenPin = 12;
const int bluePin = 14; 
void setup()
{
Serial.begin(9600);
Blynk.begin(auth, "INTEX", "77777777");
pinMode(sensorPin, INPUT);
}
void loop()
{
analogWrite(redPin, 280);
analogWrite(greenPin, 300);
analogWrite(bluePin, 300); 
Blynk.run();
analogValue = analogRead(A0); 
if (analogValue < 300.75 )
{
analogWrite(redPin, 0);
analogWrite(greenPin, 0);
analogWrite(bluePin, 1000);
Blynk.notify("stop watering your plants");
}
sensorState = digitalRead(sensorPin);
Serial.println(sensorState);
if (sensorState == 1 && lastState == 0) {
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
