/*
  Blink without Delay

  Turns on and off a light emitting diode (LED) connected to a digital pin,
  without using the delay() function. This means that other code can run at the
  same time without being interrupted by the LED code.

  The circuit:
  - Use the onboard LED.
  - Note: Most Arduinos have an on-board LED you can control. On the UNO, MEGA
    and ZERO it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN
    is set to the correct LED pin independent of which board is used.
    If you want to know what pin the on-board LED is connected to on your
    Arduino model, check the Technical Specs of your board at:
    https://www.arduino.cc/en/Main/Products

  created 2005
  by David A. Mellis
  modified 8 Feb 2010
  by Paul Stoffregen
  modified 11 Nov 2013
  by Scott Fitzgerald
  modified 9 Jan 2017
  by Arturo Guadalupi

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
*/

// constants won't change. Used here to set a pin number:
const int ledPin =  7;// the number of the LED pin

// Variables will change:
int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMicros = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 200;           // interval at which to blink (milliseconds)

unsigned long prevMicrosPT = 0;
const long intervalPT = 16;
//unsigned long currentMicrosPT = micros();
bool on = false;
unsigned int ticks = 0;
unsigned int intervalsPerSec = 1000000 / intervalPT;
unsigned int intervalsElapsed = 0;

unsigned long int prevTimerMillis = 0;

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Serial.println(intervalsPerSec);
}

void loop() {
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMicros = micros();
  
  if (currentMicros - previousMicros >= interval) {
    // save the last time you blinked the LED
    previousMicros = currentMicros;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }

  unsigned long currentMicrosPT = micros();
  if(currentMicrosPT - prevMicrosPT >= intervalPT) {
    prevMicrosPT = currentMicrosPT;
    int sensorValue = analogRead(A13);
    
    if(sensorValue > 500) {
      on = true;
    }
    else if(on == true) {
      on = false;
      ticks += 1;
    }

    intervalsElapsed += 1;
    // print out the value you read:
    //Serial.println(sensorValue);
  }

  unsigned long currTimerMillis = millis();
  //if(intervalsElapsed >= intervalsPerSec) {
  if(currTimerMillis - prevTimerMillis >= 1000) {
    //Serial.println(intervalsElapsed);
    Serial.println(ticks);
    intervalsElapsed = 0;
    ticks = 0;
    prevTimerMillis = currTimerMillis;
  }
}
