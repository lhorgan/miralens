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
long long homeThresh = 1800;
long long stopTime = 0;
bool monitorStopped = false;
long long restartAt = -1;

long long restartSecondsAfterHome = 1000000;
long long stopMonitorFor = 1000000;

long long timeBetweenAdjustments = 100;
bool homeTriggered = false; // TODO

long long lastAdjusted = 0;
bool speedAcceptable = true;

bool isMonitorHome = false;

void loop() {
  demoOne();
  int currHallState = digitalRead(hallPin);
  //Serial.println(hallState);
  long long currTime = micros();

  bool currMonitorHome = monitorHome();
  bool monitorHomeTriggered = false;
  if(currMonitorHome != isMonitorHome) {
    if(currMonitorHome) {
      monitorHomeTriggered = true;
    }
  }
  isMonitorHome = currMonitorHome;
  
  if(currHallState != hallState) {
    hallState = currHallState;
    if(hallState == 0) {
      homeTriggered = true;
      logRotationTime(micros());
      double rotationInterval = getRotationInterval();
      double rps = 1000000 / rotationInterval;
      if(rps < 14.9) {
        speedAcceptable = false;
        if(currTime - lastAdjusted > 10000) {
          lastAdjusted = currTime;
          setPWMPulse(pwmPulse + 1);
        }
        // implement time between adjustments
      }
      else if(rps > 15.1) {
        speedAcceptable = false;
        if(currTime - lastAdjusted > 10000) {
          lastAdjusted = currTime;
          setPWMPulse(pwmPulse - 1);
        }
      }
      else { // motor at acceptable speed
        //Serial.println("acceptable");
        speedAcceptable = true;
      }
      Serial.println(rps);
    }
  }

  // home stuff
  if(homeTriggered) { // todo, write this
    if(motorMeasurement == -1) {
      motorMeasurement = currTime;
    }
    
    if(stopTime >= 0 && monitorStopped && currTime - stopTime >= stopMonitorFor) {
      //Serial.print("restarting the monitor at ");
      //Serial.println((int)(restartAt / 10000));
      restartAt = currTime + restartSecondsAfterHome;
      stopTime = -1;
    }
  }

  if(monitorHomeTriggered) {
    monitorStopped = false;
    if(monitorMeasurement == -1) {
      //Serial.println("measuring monitor pulse");
      monitorMeasurement = currTime;
    }
  }
  // end home stuff
  
  if(speedAcceptable) {
    //Serial.println("well, speed is good");
    // measure time between home and monitor home time
    if(motorMeasurement > -1 && monitorMeasurement > -1) {
      int grk = diff(motorMeasurement, monitorMeasurement);
      Serial.println(grk);
      if(diff(motorMeasurement, monitorMeasurement) > homeThresh) {
        if(!monitorStopped) {
          //Serial.println("stop"); // tell the monitor to stop
          monitorStopped = true;
          stopTime = micros();
        }
      }
      else {
        //Serial.println("we seem to be synced!");
      }
      motorMeasurement = -1;
      monitorMeasurement = -1;
    }
    else {
      //Serial.println((int)(motorMeasurement / 10000));
      //Serial.println((int)(monitorMeasurement / 10000));
      //Serial.println(monitorMeasurement > -5 && motorMeasurement > -5);
      //Serial.println(monitorMeasurement > 0);
      //Serial.println("\n");
    }

    ///// other potential place for home stuff
    
    if(restartAt >= 0 && currTime >= restartAt) {
      restartAt = -1;
      //monitorStopped = false;
      //Serial.println("start");
    }
    else {
      //Serial.println((int)(restartAt / 10000));
      //Serial.println((int)(restartAt / 10000));
      //Serial.println((int)(currTime - restartAt));
      //Serial.println();
    }
  }
}

long long lastTimeTrue = 0;
bool monitorHome() { 
  long long currTime = micros();
  if(monitorStopped) {
    if(currTime - stopTime >= stopMonitorFor) {
      //monitorStopped = false;
      return true; 
    }
    return false;
  }
  
  if(currTime - lastTimeTrue >= 66666) {
    lastTimeTrue = currTime;
    return true;
  }
  return false;
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
