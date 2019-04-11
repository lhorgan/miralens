#include "BackLight.hpp"

//constant variables:
const int PINS[20] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 38, 39, 40, 41, 42, 43, 44, 45};
const BackLight BL = BackLight(pins);
const int PHOTO_PIN = A2;
const unsigned long INTERVAL = 833;
//global variables:
unsigned long prevMicrosPT = 0;


void setup() {
    BL.setup();
}

void loop() {
    unsigned long curMicrosPT = micros();
    if (analogRead(pin)) {
        BL.reset();
        prevMicrosPT = micros();
    }
    else if (curMicrosPT > prevMicrosPT >= INTERVAL) {
        BL.nextLed();
        prevMicrosPT = curMicrosPT;
    }
}