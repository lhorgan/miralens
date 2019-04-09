#include "BackLight.hpp"

BackLight::BackLight(int *led_pin_num) {
    led_pins = led_pin_num;
    curr_high_pin = -1;
}

void BackLight::setup() {
    for(int i = 0; i < GRID_SIZE; i++) {
        pinMode(led_pins[i], OUTPUT);
        digitalWrite(led_pins[i], LOW);
    }
}

void BackLight::reset() {
    if (curr_high_pin != -1) {
        digitalWrite(curr_high_pin, LOW);
        curr_high_pin = -1;
    }  
}

void BackLight::next_led() {
    if (curr_high_pin != -1)
        digitalWrite(curr_high_pin, LOW);
    if (curr_high_pin != GRID_SIZE - 1)
        curr_high_pin++;
    else 
        curr_high_pin = 0;
    digitalWrite(curr_high_pin, HIGH);
}
