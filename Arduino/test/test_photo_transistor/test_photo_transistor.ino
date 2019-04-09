#include "Photo.hpp"
const long BAUD = 115200; //Baud rate for serial communication
PhotoTransistor pht = PhotoTransistor();
//Calculated and Global variables:
const long INTERVAL_PT = 1000;
unsigned long prevMicrosPT = 0;

void setup() {
  Serial.begin(BAUD);
}

void loop() {
  unsigned long currentMicrosPT = micros();
  if(currentMicrosPT - prevMicrosPT >= INTERVAL_PT) {
    Serial.println(int(pht.frameState()));
  }
}
