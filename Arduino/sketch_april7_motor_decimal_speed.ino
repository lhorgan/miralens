#include <PID_v1.h>
#define PIN_INPUT 0
#define PIN_OUTPUT 3
#include <HID.h>
#include <Servo.h> //Use the Servo librarey for generating PWM


int hallState = 0; // sensor's state

int totalHz = 0;
int totalRots = 0;

int val = 0;
float prevElapsed = 0;
int rotTime = 0;


/////////////////////////////////////////////////////////////////////////////////
const int PT_SENSOR_PIN = A3; //photosensor pin
const int PT_MOTOR_PIN = 9;
const int hallPin = 2; // hallPin to Arduino pin 2
const long SAMPLE_FREQ = 60; //Frequency of sampling and detecting frames in Hz.
const int FRAME_ON_VAL = 20; //The raw sensor value of the white frame on the monitor.
const int FRAME_OFF_VAL = 0; //The raw sensor value of the black frame on the monitor.
//Calculated and Global variables:
const long INTERVAL_PT = 1000000 / SAMPLE_FREQ;
const int FRAME_CUTTOFF_VAL = (FRAME_ON_VAL - FRAME_OFF_VAL) / 2;
bool prevFrameVal = false; //prev frame value
Servo ESC; //name the servo object, here ESC
int prevHallState; // Hall sensor's previous state
unsigned long prevMicrosPT = 0;

void setup()
{
  ESC.attach(PT_MOTOR_PIN); //Generate PWM in pin 9 of Arduino
  pinMode(hallPin, INPUT); // set hallPin (2) to receive input
  prevHallState = LOW; // no rotations previously detected
  prevFrameVal = getFrameStatus();
  delay(1000);
  ESC.writeMicroseconds(1000);
}

void loop()
{
  unsigned long currentMicrosPT = micros();
  if(currentMicrosPT - prevMicrosPT >= INTERVAL_PT) {
//    ESC.writeMicroseconds(didFrameChange()? 1000 : 0); //70 - 90 miliseconds is safe
    ESC.writeMicroseconds(getFrameStatus() ? 1200 : 900); //70 - 90 miliseconds is safe
    prevFrameVal = getFrameStatus();
    prevMicrosPT = currentMicrosPT;
  }
}


/**
 * Compares the prevFrameValue with current Frame. Returns true if they are not the same and false otherwise.
 */
bool didFrameChange(){
  return (getFrameStatus() != prevFrameVal);
}

/**
 * return frame status as a boolean.
 */
bool getFrameStatus(){
    return (analogRead(PT_SENSOR_PIN) > FRAME_CUTTOFF_VAL);   
}



