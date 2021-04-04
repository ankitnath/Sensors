#include<SoftwareSerial.h>

SoftwareSerial HC12(10,11);

void setup() 
{
  Serial.begin(9600);
  HC12.begin(9600);
    
}

void loop() 
{ 
//  while(HC12.available())
//  {
//    Serial.println("Hello World");
//    Serial.write(HC12.read());
//  }
//
//  while (Serial.available())
//  {
//    HC12.write(Serial.read());
//    delay(2000);
//  }

Serial.println("Hello World");
delay(1000);
}
