
#include <Wire.h>
  int offset = 32000; // Offset for the sensor
  float scale = 140.0; // Scale factor for Air and N2 is 140.0, O2 is 142.8

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  int a = 0;
  int b = 0;
  int c = 0;

 /*Wire.requestFrom(0x40, 3); //
  a = Wire.read(); // first received byte stored here
  b = Wire.read(); // second received byte stored here
  c = Wire.read(); // third received byte stored here
  Wire.endTransmission();
  delay(5);
 
  Wire.requestFrom(0x40, 3); //
  a = Wire.read(); // first received byte stored here
  b = Wire.read(); // second received byte stored here
  c = Wire.read(); // third received byte stored here
  Wire.endTransmission();
  delay(5);*/
}

uint8_t crc8(const uint8_t data, uint8_t crc) 
{
  crc ^= data;

  for ( uint8_t i = 8; i; --i ) 
  {
    crc = ( crc & 0x80 )
      ? (crc << 1) ^ 0x31
      : (crc << 1);
  }
  return crc;
}

void loop() 
{
  delay(500);
  Wire.beginTransmission(byte(0x40)); // transmit to device #064 (0x40)
  Wire.write(byte(0x10));      //
  Wire.write(byte(0x00));      //
  Wire.endTransmission();
  Wire.requestFrom(0x40, 3); // read 3 bytes from device with address 0x40
  while (Wire.available()) 
 { // slave may send less than requested
  uint16_t a = Wire.read(); // first received byte stored here. The variable "uint16_t" can hold 2 bytes, this will be relevant later
  uint8_t b = Wire.read(); // second received byte stored here
  uint8_t crc = Wire.read(); // crc value stored here
  uint8_t mycrc = 0xFF; // initialize crc variable
  mycrc = crc8(a, mycrc); // let first byte through CRC calculation
  mycrc = crc8(b, mycrc); // and the second byte too
  if (mycrc != crc) { // check if the calculated and the received CRC byte matches
  Serial.println("Error: wrong CRC");
  }
  Serial.println('p');
  Serial.println(a);
  Serial.println(b);
  Serial.println(crc);
  Serial.println('h');
  a = (a << 8) | b; // combine the two received bytes to a 16bit integer value
  // a >>= 2; // remove the two least significant bits
  int Flow = (a - offset) / scale;
  //Serial.println(a); // print the raw data from the sensor to the serial interface
  Serial.println(Flow); // print the calculated flow to the serial interface
   }
}
