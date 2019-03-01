#include <HID.h>
#include <Servo.h> //Use the Servo librarey for generating PWM
Servo ESC; //name the servo object, here ESC
int rots; // rotations recorded
const int hallPin = 2; // hallPin to Arduino pin 2
int hallState = 0; // sensor's state
int prevState; // sensor's previous state
/*
 * Since sensor records one rotation multiple times due
 * to the size of the magnet, we use previous state to 
 * determine if the input reading is from a new rotation
 */
void setup()
{
  Serial.begin(9600);
  ESC.attach(9); //Generate PWM in pin 9 of Arduino
  ESC.write(90); //set servo speed to 90 -> ~118 rotations per second
  pinMode(hallPin, INPUT); // set hallPin (2) to receive input
  rots = 0; // rotations recorded
  prevState = LOW; // no rotations previously detected
}

void loop()
{
  hallState = digitalRead(hallPin); // read from the sensor
  // add to rotation count if a new rotation
  if(hallState == LOW && prevState == HIGH) {
    rots++;
  }
  prevState = hallState;
  int t = millis();
  if(t % 1000 == 0) {
    Serial.print("Rotations per second: \n");
    Serial.print(rots);
    Serial.print("\n");
    rots = 0;
  }
}
