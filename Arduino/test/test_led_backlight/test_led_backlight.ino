#include "BackLight.hpp"
int pins[20] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 38, 39, 40, 41, 42, 43, 44, 45};
BackLight bl = BackLight(pins);
const unsigned long interval = 1000;
unsigned long previousmicros = 0;        // will store last time LED was updated

void setup() { 
  bl.setup();
}

void loop() {
 for(int ctr = 0; ctr < 20; ctr++) {
    unsigned long currentmicros = micros();
    if (currentmicros - previousmicros >= interval) {
      bl.next_led();
      previousmicros = currentmicros;
    }
  }
}
