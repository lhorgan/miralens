#include <PID_v1.h>
#include <HID.h>
#include <Servo.h> //Use the Servo librarey for generating PWM

const int PT_SENSOR_PIN = A3; //photosensor pin
const long SAMPLE_FREQ = 60; //Frequency of sampling and detecting frames in Hz.
const int FRAME_ON_VAL = 100; //The raw sensor value of the white frame on the monitor.
const int FRAME_OFF_VAL = 20; //The raw sensor value of the black frame on the monitor.
//Calculated and Global variables:
const long INTERVAL_PT = 1000000 / SAMPLE_FREQ;
const int FRAME_CUTTOFF_VAL = (FRAME_ON_VAL - FRAME_OFF_VAL) / 2;
bool prevFrameStatus = false;


//int pins[20] = {2,3,4,5,6,7,8,9,10,11,12,13,38,39,40,41,42,43,44,45};
int pins[20] = {13,12,11,10,9,8,7,6,5,4,3,2,38,39,40,41,42,43,44,45};

unsigned long previousmicros = 0;        // will store last time LED was updated
// constants won't change
//833 for 1200Hz
//208 for 1/4800
unsigned long intervals[20]; 
int ledStates[20];

void setup() {
  Serial.begin(115200);
  for(int ctr = 0; ctr < 20; ctr++) {
    pinMode(pins[ctr], OUTPUT);
    digitalWrite(pins[ctr], LOW);
    ledStates[ctr] = LOW;  
    intervals[ctr] = 833;
  }
}

void loop() {
 for(int ctr = 0; ctr < 20; ctr++) {
    bool currentFrameStatus = getFrameStatus();
    if (currentFrameStatus != prevFrameStatus) {
      prevFrameStatus = currentFrameStatus;
      break;
    }
    unsigned long currentmicros = micros();
    if (currentmicros - previousmicros >= 833) {
      // save the last time you blinked the LED
      previousmicros = currentmicros;
      blinkLED(pins[ctr], ledStates[ctr], intervals[ctr]);
    }
    
  }
}

void blinkLED (int onPin, int ledState, unsigned long interval){    
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      interval = 833; //208for 4800Hz
      ledState = HIGH;
    } 
    else {
      interval = 15833; //3950 for 4800Hz
      ledState = LOW;
    }
    // set the LED with the ledState of the variable:
    digitalWrite(onPin, ledState);
}

/**
 * return frame status as a boolean.
 */
bool getFrameStatus(){
    return (analogRead(PT_SENSOR_PIN) > FRAME_CUTTOFF_VAL);   
}
