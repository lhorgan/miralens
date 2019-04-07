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

int val = 0;
float prevElapsed = 0;
int rotTime = 0;


/////////////////////////////////////////////////////////////////////////////////
const int PT_SENSOR_PIN = A3; //photosensor pin
const long SAMPLE_FREQ = 60; //Frequency of sampling and detecting frames in Hz.
const int FRAME_ON_VAL = 15; //The raw sensor value of the white frame on the monitor.
const int FRAME_OFF_VAL = 0; //The raw sensor value of the black frame on the monitor.
//Calculated and Global variables:
const long INTERVAL_PT = 1000000 / SAMPLE_FREQ;
bool prevFrameVal = false; //prev frame value

void setup()
{
  ESC.attach(9); //Generate PWM in pin 9 of Arduino
  ESC.writeMicroseconds(1000);
  delay(2000);
  ESC.writeMicroseconds(1200);
  delay(100);
  ESC.writeMicroseconds(900);
  Serial.begin(9600);
  //set servo speed to 90 -> ~118 rotations per second
   pinMode(hallPin, INPUT); // set hallPin (2) to receive input
 //  rots = 0; // rotations recorded
   prevState = LOW; // no rotations previously detected
  
  //initialize the variables we're linked to
 /* Input = analogRead(PIN_INPUT);
  Setpoint = 5000;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);*/
}

void loop()
{
  //speed control
 //if(Serial.available()) {
 //   val = Serial.parseInt();
 // }
  ESC.writeMicroseconds(1180); //70 - 90 miliseconds is safe
  
  ESC.writeMicroseconds(0); //70 - 90 miliseconds is safe

  //1260 is the value to go with, it's the lowest 
  //Speed measuring
  /*hallState = digitalRead(hallPin); // read from the sensor
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
          Serial.println("Hz (rots/sec):");
      Serial.println(float(totalHz/float(totalRots)));
    }
    totalHz = 0;
    totalRots = 0;
  }
  */
}

bool didFrameChange(){
  return (getFrameStatus() != prevFrameValue);
}

/**
 * return frame status as a boolean.
 */
bool getFrameStatus(){
    return (analogRead(PT_SENSOR_PIN) > FRAME_CUTTOFF_VAL);   
}



