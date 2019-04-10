#include "BackLight.hpp"

BackLight::BackLight(int *ledPinNum) {
    ledPins = ledPinNum;
    curHighPin = -1;
}

void BackLight::setup() {
    for(int i = 0; i < GRID_SIZE; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
    }
}

void BackLight::reset() {
    if (curHighPin != -1) {
        digitalWrite(ledPins[curHighPin], LOW);
        curHighPin = -1;
    }  
}

void BackLight::nextLed() {
    if (curHighPin != -1)
        digitalWrite(ledPins[curHighPin], LOW);
    if (curHighPin != GRID_SIZE - 1)
        curHighPin++;
    else 
        curHighPin = 0;
    digitalWrite(ledPins[curHighPin], HIGH);
}
