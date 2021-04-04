#include <SFE_BMP180.h>
#include <Wire.h>
#include "i2c.h"
#include "i2c_BMP280.h"
BMP280 bmp280;
SFE_BMP180 bmp180;

void setup()
{
    Serial.begin(9600);
    //initializing bmp180
    bool success = bmp180.begin();
    if (success) 
    {
    Serial.println("BMP180 init success");
    }
    //initializing bmp280
    Serial.print("Probe BMP280: ");
    if (bmp280.initialize()) Serial.println("Sensor found");
    else
    {
        Serial.println("Sensor missing");
        while (1) {}
    }

    // onetime-measure:
    bmp280.setEnabled(0);
    bmp280.triggerMeasurement();
}

void loop()
{
  char status;
  double T, P;
  bool success = false;
  bmp280.awaitMeasurement();

    float temperature;
    bmp280.getTemperature(temperature);

    float pascal,cm2;
    bmp280.getPressure(pascal);
    cm2 = pascal * 0.010197162129779282;
    

    static float meters, metersold;
    bmp280.getAltitude(meters);
    metersold = (metersold * 10 + meters)/11;

    bmp280.triggerMeasurement();

  status = bmp180.startTemperature();

  if (status != 0) 
  {
    delay(1000);
    status = bmp180.getTemperature(T);

    if (status != 0) 
    {
      status = bmp180.startPressure(1);

      if (status != 0) 
      {
        delay(status);
        status = bmp180.getPressure(P, T);

        if (status != 0) 
        {
          Serial.print("Pressure by BMP180: ");
          float cm1 = (P * 100 * 0.010197162129779282);
          Serial.print(cm1);
          Serial.print(" cmH2O");
          Serial.print(" ");
          Serial.print(" Pressure by BMP280: ");
          Serial.print(cm2);
          //Serial.print(" ");
          Serial.print(" cmH20");
          Serial.print("\n\n ");
          Serial.print("Differential Pressure B/W BMP280 & BMP180 : ");
          float cm = cm1 - cm2;
          Serial.print(cm);
          Serial.print(" cmH20");
          
          Serial.print("\n");
          
          Serial.print("Temperature by BMP180: ");
          Serial.print(T);
          Serial.print(" ");
          Serial.print(" C");
          Serial.print(" ");
          Serial.print("Temperature by BMP280: ");
          Serial.print(temperature);
          Serial.println(" C");

          Serial.print("\n\n");
          delay(1000);
          
          
        }
      }
    }
  }
    
}

/**<

Program size:
A1.0.5:
A1.5.7: 9680b
A1.6.3: 9664b / 561b

 */
