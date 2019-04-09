#include "Hall.hpp"

HallSensor::HallSensor(int pin_num=DEFAULT_HALL_PIN) {
  pin = pin_num;
  prevState = LOW;
};

void HallSensor::setup() {
  pinMode(pin, INPUT);
};

int HallSensor::listenAndReportState() {
  int curState = digitalRead(hallPin); // read from the sensor
  // add to rotation count if a new rotation
  if(curState == LOW && prevState == HIGH) {
    float elapsed = millis();
    float rotTime = elapsed - prevRotTimeStamp;
    prevRotTimeStamp = elapsed;
    totalRots++;
    totalHz += 1000.0 / rotTime;
  }
  prevState = curState;
};

float HallSensor::frequencyUntilNow() {
  float output = totalHz / totalRots;
  totalHz = 0;
  totalRots = 0;
  return output;
};
