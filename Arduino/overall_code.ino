bool motorHome = false;
bool frameWhite = true;
const int ledCount = 20;
const int ledPins[ledCount]= {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 38, 39, 40, 41, 42, 43, 44, 45};
const int photoPin = 5; // TODO

const int refreshNum = 5;
long long refreshTimes[refreshNum] = {-1, -1, -1, -1, -1};
double avgRefreshInterval = -1;

unsigned int currLEDIndex = 0;
unsigned int ledOnTime = 0; // how long an LED should be on for
long long prevLEDOnTime = 0; // time when the previous LED was flashed on

void setup() {
  
}

void loop() {
  // TODO, control the motor's speed
  
  long long currTime = micros(); // get the current itme
  
  bool frameWhiteCurrent = isFrameWhite(); // is the current frame white?
  if(frameWhiteCurrent != frameWhite) { // whatever it is, it isn't what it was before
    // and that means we have a new frame
    frameWhite = frameWhiteCurrent;
    logRefreshTime(currTime);
    resetBacklight();
    avgRefreshInterval = getRefreshInterval();
    ledOnTime = avgRefreshInterval / ledCount;
  }

  // cycle through to the next LED
  if(currTime - prevLEDOnTime >= ledOnTime) {
    // turn currLEDIndex LED off TODO
    currLEDIndex++;
    // turn currLEDIndex LED on TODO
  }

  if(avgRefreshInterval > 0) {
    bool motorHomeCurrent = isMotorHome();
    if(motorHomeCurrent != motorHome) { // motor home status has changed
      if(motorHomeCurrent) {
        Serial.println("The motor is home.");
        restartImageSequence();
      }
      else {
        Serial.println("The motor is no longer home.");
      }
      motorHome = motorHomeCurrent;
    }
  }
}

// returns average refresh interval or -1 if not yet calculated
double getRefreshInterval() {
  double avgRefreshInterval = 0;
  if(refreshTimes[0] < 0) {
    return -1;
  }
  
  for(unsigned int i = 1; i < refreshNum; i++) {
    if(refreshTimes[i] < 0) {
      return -1.0;
    }
    else {
      avgRefreshInterval += refreshTimes[i] - refreshTimes[i - 1];
    }
  }

  avgRefreshInterval /= refreshNum;
  return avgRefreshInterval;
}

// save a refresh time measurement so we can factor it into our average
void logRefreshTime(long long refreshTime) {
  for(int i = 0; i < refreshNum - 1; i++) {
    refreshTimes[i] = refreshTimes[i + 1];
  }
  refreshTimes[refreshNum] = refreshTime;
}

bool isFrameWhite() {
  // TODO get this code from Matin
  return true;
}

bool isMotorHome() {
  // TODO get this code from Matin
  return true;
}

void resetBacklight() {
  // TODO, turn the first LED back on
}

void restartImageSequence() {
  // TODO
}
