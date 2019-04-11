#include "BackLight.hpp"
int pins[20] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 38, 39, 40, 41, 42, 43, 44, 45};
BackLight bl = BackLight(pins);
const unsigned long interval = 100;

void setup() { 
  bl.setup();
}

void loop() {
    for (int i = 0; i < 22; i++) {
        bl.nextLed();
        delay(interval);
    }
    bl.reset();
    delay(interval);
}
