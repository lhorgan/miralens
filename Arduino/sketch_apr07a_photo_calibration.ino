/**************************************************************************
 * Name: sketch_apr07a_photo_calibration.ino
 * Author(s): Quan Do, Luck Horgan, Matin Raayai Ardakani
 * Arduino code for measuring the raw values coming from the phototransistor
 * when put in front of a black screen (FRAME_OFF_VAL) and a white screen
 * (FRAME_OFF_VAL).
 ***************************************************************************/
//Const values:
const long BAUD = 115200; //Baud rate for serial communication
const long SAMPLE_FREQ = 60; //Frequency of sampling and detecting frames in Hz.
const int SENSOR_PIN = A3; //Pin number of the phototransistor on the Arduino board.
//Calculated and Global variables:
const long INTERVAL_PT = 1000000 / SAMPLE_FREQ;
unsigned long prevMicrosPT = 0;

void setup() {
  Serial.begin(BAUD);
}

void loop() {
  unsigned long currentMicrosPT = micros();
  if(currentMicrosPT - prevMicrosPT >= INTERVAL_PT) {
    Serial.println(analogRead(SENSOR_PIN));
    prevMicrosPT = currentMicrosPT;
  }
}