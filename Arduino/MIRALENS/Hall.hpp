#pragma once
#define DEFAULT_HALL_PIN 2
#include <HID.h>

class HallSensor {
  private:
    const int pin;
    int prevState;
    float totalHz = 0;
    int totalRots = 0;
    float prevRotTimeStamp = 0;

  public:
    HallSensor(int pin_num=DEFAULT_HALL_PIN);
    virtual ~HallSensor() {};
    void setup();
    void listenAndReportState();
    float frequencyUntilNow();
};
