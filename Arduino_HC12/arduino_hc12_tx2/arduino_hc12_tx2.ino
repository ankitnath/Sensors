        
#include <SoftwareSerial.h> // Inclui a biblioteca Software Serial
SoftwareSerial HC12(8,7); // 8 RX vai ligado no Tx do modulo HC 12, 7 TX vai
//ligado no RX do módulo
#define B0 2

void setup()
{
 pinMode(B0,INPUT);
// pinMode(B1,INPUT);
 Serial.begin(9600);
 HC12.begin(9600);
}
void loop() 
{
  int button_state = digitalRead(B0);
  if(button_state == HIGH)
  {
   Serial.println("B0 pressed ");
   Serial.print('1');
   HC12.print('1');
   while(digitalRead(B0)==0);
  }
  else
  {
   Serial.println("B0 not pressed ");
   Serial.print('0');
   HC12.print('0');
 //  while(digitalRead(B0)==0);
  }
  
//   if(!digitalRead(B0))
//   {
//    
//   Serial.println("B0 pressionado ");
//   Serial.print('1');
//   HC12.print('1');
//   while(digitalRead(B0)==0);
   
//   }
}
