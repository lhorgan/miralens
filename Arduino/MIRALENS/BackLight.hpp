#pragma once
#include "Arduino.h"
#define GRID_SIZE 20

class BackLight {
    private:
        int *led_pins;
        int curr_high_pin;

    public:
        BackLight(int *led_pin_num);
        void setup();
        void reset();
        void next_led();
};

