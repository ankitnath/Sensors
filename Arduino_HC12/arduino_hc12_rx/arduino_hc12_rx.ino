#include<SoftwareSerial.h>

SoftwareSerial HC12(10,11);
int LED = 13;

void setup() 
{
    Serial.begin(9600);
    HC12.begin(9600);
    pinMode(LED, OUTPUT);
}

void loop() 
{
//    while(HC12.available())
//    {
//      int val = HC12.read();
//      Serial.println(HC12.read());
//      analogWrite(LED,val);
//    }

while(HC12.available())
 {
    if(Serial.available() > 0)
    {
        String input = Serial.readString();
        if(input == "Hello World")
        {
            digitalWrite(LED, HIGH);
            delay(500);
            digitalWrite(LED, LOW);
            Serial.println("Received");
        }
    }
 }
}
