#include <PID_v1.h>
#define PIN_INPUT 0
#define PIN_OUTPUT 3
#include <HID.h>
#include <Servo.h> //Use the Servo librarey for generating PWM
Servo ESC; //name the servo object, here ESC
const int hallPin = 2; // hallPin to Arduino pin 2
int hallState = 0; // sensor's state
int prevState; // sensor's previous state
int totalHz = 0;
int totalRots = 0;
int desired_speed = 0;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;
int val = 0;
//Specify the links and initial tuning parameters
double aggKp=4, aggKi=0.2, aggKd=1;
double consKp=0, consKi=0.0, consKd=16;
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);
float prevElapsed = 0;
int rotTime = 0;

void setup()
{
  ESC.attach(9); //Generate PWM in pin 9 of Arduino
  ESC.writeMicroseconds(1000);
  delay(5000);
  ESC.writeMicroseconds(1200);
  delay(100);
  ESC.writeMicroseconds(900);
  
  Serial.begin(9600);
  //set servo speed to 90 -> ~118 rotations per second
  pinMode(hallPin, INPUT); // set hallPin (2) to receive input
  prevState = LOW; // no rotations previously detected
  
  //initialize the variables we're linked to
  Output = 1200;
  Setpoint = 12;
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  //speed control
  ESC.writeMicroseconds(Output); //70 - 90 miliseconds is safe
  //1260 is the value to go with, it's the lowest 
  //delay(100);
  
  //Speed measuring
  hallState = digitalRead(hallPin); // read from the sensor
  // add to rotation count if a new rotation
  if(hallState == LOW && prevState == HIGH) {
  //  rots++;
    float elapsed = millis();
    float rotTime = elapsed - prevElapsed;
    prevElapsed = elapsed;
    totalRots++;
    totalHz += float(1000.0/rotTime);
    
  }
  prevState = hallState;
  int t = millis();
  if(t % 1000 == 0) {
    if (totalRots != 0){

      Input = double(totalHz/float(totalRots));
      //Setpoint = 12;
      double gap = abs(Setpoint-Input); //distance away from setpoint
      if (gap < 5.0)
      {  //we're close to setpoint, use conservative tuning parameters
          myPID.SetTunings(consKp, consKi, consKd);
      }
      else
      {
         //we're far from setpoint, use aggressive tuning parameters
         myPID.SetTunings(aggKp, aggKi, aggKd);
      }
      myPID.Compute();
      Serial.println("Input in Hz (rots/sec):");
      Serial.println(Input);
      Serial.println("Output in ms:");
      Serial.println(Output);
    }
    
    totalHz = 0;
    totalRots = 0;

  }
}
