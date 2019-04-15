// Motor A
int enA = 9;
int in1 = 8;
int in2 = 7;

const int hallPin = 13;
int hallState = 1;

const int rotationNum = 5;
long long rotationTimes[rotationNum] = {-1, -1, -1, -1, -1};

int pwmPulse = 100;

const int numLEDs = 20;

void setup() {
  Serial.begin(9600);
  Serial.println("SETTING UP");
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(hallPin, INPUT); // set hallPin (2) to receive input

  /*for(int i = 2; i <= 13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  for(int i = 38; i <= 45; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }*/
}

void setPWMPulse(int pulse) {
  if(pulse > 255) {
    pwmPulse = 255;
  }
  else if(pulse < 100) {
    pwmPulse = 100;
  }
  else {
    pwmPulse = pulse;
  }
}

long long motorMeasurement = -1;
long long monitorMeasurement = -1;
long long homeThresh = 1851;
long lont stopTime = 0;
long long stopMonitorFor = 10000000;
bool monitorStopped = false;
long long restartAt = -1;
long long restartSecondsAfterHome = 100;
long long timeBetweenAdjustments = 100;

void loop() {
  demoOne();
  int currHallState = digitalRead(hallPin);
  //Serial.println(hallState);

  
  
  if(currHallState != hallState) {
    hallState = currHallState;
    if(hallState == 0) {
      logRotationTime(micros());
      double rotationInterval = getRotationInterval();
      double rps = 1000000 / rotationInterval;
      if(rps < 14.9) {
        setPWMPulse(pwmPulse + 1);
        // implement time between adjustments
      }
      else if(rps > 15.1) {
        setPWMPulse(pwmPulse - 1);
      }
      else { // motor at acceptable speed
        // measure time between home and monitor home time
        if(motorMeasurement > -1 && monitorMeasurement > -1) {
          if(diff(motorMeasurement, monitorMeasurement) > homeThresh) {
            if(!monitorStopped) {
              Serial.println("stop"); // tell the monitor to stop
              monitorStopped = true;
              stopTime = micros();
            }
          }
        }

        if(homeTriggered) { // todo, write this
          if(monitorStopped && currTime - stopTime >= stopMonitorFor) {
            restartAt = currTime + restartSecondsAfterHome;
          }
        }
        if(restartSecondsAfterHome >= 0 && currTime >= restartSecondsAfterHome) {
          restartSecondsAfterHome = -1;
          Serial.println("start");
        }
      }
      Serial.println(rps);
    }
  }
}

long long diff(long long m1, long long m2) {
  if(m1 < m2) {
    return m2 - m1;
  }
  return m1 - m2;
}

void demoOne() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, pwmPulse);
}


double getRotationInterval() {
  double avgRotationInterval = 0;
  if(rotationTimes[0] < 0) {
    return -1;
  }
  
  for(unsigned int i = 1; i < rotationNum; i++) {
    if(rotationTimes[i] < 0) {
      return -1.0;
    }
    else {
      avgRotationInterval += rotationTimes[i] - rotationTimes[i - 1];
    }
  }
  
  avgRotationInterval /= rotationNum;
  return avgRotationInterval;
}

 // save a rotation time measurement so we can factor it into our average
void logRotationTime(long long rotationTime) {
  for(int i = 0; i < rotationNum - 1; i++) {
    rotationTimes[i] = rotationTimes[i + 1];
  }
  rotationTimes[rotationNum - 1] = rotationTime;
}
