#include <HX711.h>

//constants
const int out = 5 ;
const int clck = 4;
const int pushButton = 2;

//variables will change
volatile int buttonState = 0; //variable for reading the pushbutton status

HX711 scale(out, clck);
float CalibrationFactor = -110215;
//109200
//-110415


void setup()
{
  Serial.begin(9600);
  pinMode(pushButton,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pushButton), pin_ISR, FALLING);
  Serial.println("Press Button for tare");
  scale.set_scale();
  scale.tare();
  long zero_factor = scale.read_average();
  Serial.print("Zero factor: ");
  Serial.println(zero_factor);
}

void loop()
{
  scale.set_scale(CalibrationFactor);
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 3);
  Serial.println(" Kilogram");
  Serial.print("Calibration Factor is: ");
  Serial.println(CalibrationFactor);
  Serial.println("--------------------------------------------");
  delay(500);

}

void pin_ISR()
{
  
  buttonState = digitalRead(pushButton);
  
  if (buttonState == 1)
  {
    Serial.println("HIGH");
    scale.tare();
  }


}
//-------------------- --------------------//
