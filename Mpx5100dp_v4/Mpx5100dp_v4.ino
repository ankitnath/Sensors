
#include <Servo.h>
Servo esc_signal;

float rawADC;
float potValue;

void setup()
{
   
    Serial.begin(9600);
   esc_signal.attach(9);  //Specify here the pin number on which the signal pin of ESC is connected.
  esc_signal.write(30);   //ESC arm command. ESCs won't start unless input speed is less during initialization.
  delay(3000);            //ESC initialization delay.
  Serial.println("Initialising the sensor ...");
}

void loop()
{
    

  potValue = analogRead(A8);   // reads the value of the potentiometer (value between 0 and 1023)
  potValue = map(potValue, 0, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)
  Serial.println(potValue);
  esc_signal.write(potValue); 
    int rawADC = analogRead(A2);
    float voltage = rawADC / 1024.0 * 5.0;    // 5.0 is always good, the sensor is ratiometric
    // correct offset, divide by voltage range, multiply with pressure range.
   float kpa = (((voltage - 0.15) / 4.55) * 100.0);
   float kpav1 = (kpa * 100)/60;
    Serial.print("Air Pressure : ");
    Serial.print(kpa);
    Serial.print("kPA");

    //converting kPa to slm

  float d = kpav1 * 2; //Multiply dynamic pressure value by 2
  float pa = d * 1000; //convert to Pascal
  float H20_density = pa / 1.24; //Dividing the pascal value by fluid density(water in this case = 1000kg/m3) in kg/m3
  float H20_den = sqrt(H20_density); //fluid's velocity in meters/sec
  float rad_pipe = 0.0015; //m (radius of blowing pipe of mpx5100)
  float rad_sq = rad_pipe * rad_pipe; //taking square of the radius of pipe
  float rad_pi = rad_sq * 3.1416; //multiplying by pi
  float flow1 = rad_pi * H20_den; //m3/sec
  float flow2 = flow1 * 1000; //flow in litre/sec
  float flow3 = flow2 * 1000; //flow in ml/sec
 
  float flow3 = flow2 * 60; //litre/minute
  Serial.print("  ");
  Serial.print("Flow rate in litre/min : ");
  Serial.println(flow3);
  Serial.println();
  delay(1000);        // delay in between reads for stability
    
}
