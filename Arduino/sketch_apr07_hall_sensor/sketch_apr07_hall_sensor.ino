#include "Hall.hpp"
HallSensor hs = HallSensor(2);
void setup()
{
  Serial.begin(115200);
  hs.setup();
}

void loop()
{
  hs.listenAndReportState();
  int t = millis();
  if(t % 1000 == 0) {
      Serial.println("Hz (rots/sec):");
      Serial.println(hs.frequencyUntilNow());
  }
}
