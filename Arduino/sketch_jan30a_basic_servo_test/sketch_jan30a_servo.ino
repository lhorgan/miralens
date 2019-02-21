#include <HID.h>

#include <Servo.h> //Use the Servo librarey for generating PWM
Servo ESC; //name the servo object, here ESC

void setup()
{
  ESC.attach(9); //Generate PWM in pin 9 of Arduino
  ESC.write(90);
}

void loop()
{
  //ESC.write(200); //based on the value of throttle generate PWM signal
}
