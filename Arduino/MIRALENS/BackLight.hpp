#pragma once
#include "Arduino.h"
#define GRID_SIZE 20

class BackLight {
    private:
        int *ledPins;
        int curHighPin;

    public:
        BackLight(int *ledPinNum);
        void setup();
        void reset();
        void nextLed();
};

