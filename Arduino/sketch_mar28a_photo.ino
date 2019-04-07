/**************************************************************************
 * Name: sketch_mar28a_photo.ino
 * Author(s): Quan Do, Luck Horgan, Matin Raayai Ardakani
 * Arduino code for detecting presence of a frame in miralens. 
 ***************************************************************************/
//Const values:
const long BAUD = 115200; //Baud rate for serial communication
const long SAMPLE_FREQ = 60; //Frequency of sampling and detecting frames in Hz.
const int SENSOR_PIN = A3; //Pin number of the phototransistor on the Arduino board.
const int FRAME_ON_VAL = 15; //The raw sensor value of the white frame on the monitor.
const int FRAME_OFF_VAL = 0; //The raw sensor value of the black frame on the monitor.
//Calculated and Global variables:
const long INTERVAL_PT = 1000000 / SAMPLE_FREQ;
const int FRAME_CUTTOFF_VAL = (FRAME_ON_VAL - FRAME_OFF_VAL) / 2;
unsigned long prevMicrosPT = 0;

void setup() {
  Serial.begin(BAUD);
}

void loop() {
  unsigned long currentMicrosPT = micros();
  if(currentMicrosPT - prevMicrosPT >= INTERVAL_PT) {
    int curSenVal = analogRead(SENSOR_PIN);
    int output = (curSenVal > FRAME_CUTTOFF_VAL);
    Serial.println(output); //TODO: Direct this to a pin instead of serial port.
    prevMicrosPT = currentMicrosPT;
  }
}
