//int pins[20] = {2,3,4,5,6,7,8,9,10,11,12,13,38,39,40,41,42,43,44,45};
int pins[20] = {13,12,11,10,9,8,7,6,5,4,3,2,38,39,40,41,42,43,44,45};

unsigned long previousmicros = 0;        // will store last time LED was updated
// constants won't change
//833 for 1200Hz
//208 for 1/4800
unsigned long intervals[20]; 
int ledStates[20];

void setup() { 
  for(int ctr = 0; ctr < 20; ctr++) {
    pinMode(pins[ctr], OUTPUT);
    digitalWrite(pins[ctr], LOW);
    ledStates[ctr] = LOW;  
    intervals[ctr] = 833;
  }
}

void loop() {
 for(int ctr = 0; ctr < 20; ctr++) {
    unsigned long currentmicros = micros();
    if (currentmicros - previousmicros >= 833) {
      // save the last time you blinked the LED
      previousmicros = currentmicros;
      blinkLED(pins[ctr], ledStates[ctr], intervals[ctr]);
    }
  }
}

void blinkLED (int onPin, int ledState, unsigned long interval){    
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      interval = 833; //208for 4800Hz
      ledState = HIGH;
    } 
    else {
      interval = 15833; //3950 for 4800Hz
      ledState = LOW;
    }
    // set the LED with the ledState of the variable:
    digitalWrite(onPin, ledState);
}

