#include <SoftwareSerial.h> // Inclui a biblioteca Software Serial

SoftwareSerial HC12(8,7); // 8 RX vai ligado no Tx do modulo HC 12, 7 TX vai
//ligado no RX do módulo

#define yellow 2

char comando = 0;

void setup()
{
 pinMode(yellow,OUTPUT);
 Serial.begin(9600);
 HC12.begin(9600);
 Serial.println("Receptor");
// digitalWrite(blue,1);
 delay(300);
 
}

void loop()
{
 while(HC12.available()>0)
 {
 comando = HC12.read();
 Serial.println(comando);
   switch(comando)
   {
   case '1' : digitalWrite(yellow,!digitalRead(yellow));
   break;
   
   }
 }
}
