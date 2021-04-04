//###############################################################
//Code Developer : Ankit Nath
//Sensor tested : AS21 Pressure Sensor Module with buzzer
//Datasheet : https://5.imimg.com/data5/JE/QU/CL/SELLER-6903772/as21-pcb-mounted-pressure-sensor.pdf
//Date : 19/08/2020
//#################################################################


void setup() 
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("Initialising the sensor ...");
}
 
// the loop routine runs over and over again forever:
void loop() 
{
  // read the input on analog pin 0:
  float rd = analogRead(A0);
  Serial.print("analog read : ");
  Serial.print(rd);
  Serial.println("    ");
  delay(500);        
}
