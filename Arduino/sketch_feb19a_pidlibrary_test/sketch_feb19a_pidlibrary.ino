#include <PID_v1.h>
#define PIN_INPUT 0
#define PIN_OUTPUT 3
#include <HID.h>
#include <PID_v1.h>
#include <Servo.h> //Use the Servo librarey for generating PWM
Servo ESC; //name the servo object, here ESC
int rots; // rotations recorded
const int hallPin = 2; // hallPin to Arduino pin 2
int hallState = 0; // sensor's state
int prevState; // sensor's previous state

//Define Variables we'll be connecting to
double Setpoint, Input, Output;
int val = 0;
//Specify the links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup()
{
  ESC.attach(9); //Generate PWM in pin 9 of Arduino
  ESC.writeMicroseconds(1000);
  delay(5000);
  ESC.writeMicroseconds(2000);
  delay(100);
  ESC.writeMicroseconds(900);
  Serial.begin(9600);

  /* for(int angle = 0; angle < 70; angle += 10)    // command to move from 0 degrees to 180 degrees 
  {                                  
    ESC.write(angle);                 //command to rotate the servo to the specified angle
    delay(15);                       
  } */
  /*int i = 0;
  while(i <= 20) {
    ESC.write(i);
    i++;
    // delay(1000);
  } */
   //set servo speed to 90 -> ~118 rotations per second
  pinMode(hallPin, INPUT); // set hallPin (2) to receive input
  rots = 0; // rotations recorded
  prevState = LOW; // no rotations previously detected
  
  //initialize the variables we're linked to
 /* Input = analogRead(PIN_INPUT);
  Setpoint = 50;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);*/
}

void loop()
{

  
  if(Serial.available()) {
    val = Serial.parseInt();
  }
  ESC.writeMicroseconds(val);
  hallState = digitalRead(hallPin); // read from the sensor
  // add to rotation count if a new rotation
  if(hallState == LOW && prevState == HIGH) {
    rots++;
  }
  prevState = hallState;
  int t = millis();
  if(t % 1000 == 0) {
    // Input = rots;
    Serial.print("Rotations per second: \n");
    Serial.print(rots);
    Serial.print("\n");
    rots = 0;
  }
  //myPID.Compute();
  //ESC.write(Output);
}
