#include <PID_v1.h>
#define PIN_INPUT 0
#define PIN_OUTPUT 3
#include <HID.h>
#include <Servo.h> //Use the Servo librarey for generating PWM
Servo ESC; //name the servo object, here ESC
const int hallPin = 2; // hallPin to Arduino pin 2
int hallState = 0; // sensor's state
int prevState; // sensor's previous state
int totalHz = 0;
int totalRots = 0;

float prevElapsed = 0;
int rotTime = 0;

float desired_speed = 15.0;
int base_val = 1200;
void setup()
{
  Serial.begin(9600);

  ESC.attach(9); //Generate PWM in pin 9 of Arduino
  pinMode(hallPin, INPUT); // set hallPin (2) to receive input
  delay(500);  
  ESC.writeMicroseconds(1000);
  delay(500);  
  ESC.writeMicroseconds(1000);
  //set servo speed to 90 -> ~118 rotations per second
}

void loop()
{
  ESC.writeMicroseconds(base_val); //70 - 90 miliseconds is safe
  hallState = digitalRead(hallPin); // read from the sensor
  // add to rotation count if a new rotation
  if(hallState == LOW && prevState == HIGH) {
  //  rots++;
    float elapsed = millis();
    float rotTime = elapsed - prevElapsed;
    prevElapsed = elapsed;
    totalRots++;
    totalHz += float(1000.0/rotTime);   
  }
  prevState = hallState;
  int t = millis();
  if(t % 1000 == 0) { //every 1 second
    if (totalRots != 0){
          Serial.println("Hz (rots/sec):");
          Serial.println(float(totalHz/float(totalRots)));
          Serial.println("Duration");
          Serial.println(base_val);
          //SPEED CONTROL, SUBTRACTING AND INCREASING BASE_VAL TO HIT 15Hz
          if ((float(desired_speed) - float(totalHz/float(totalRots))) >= 2){
            base_val = base_val + 10;
          }
            else if ((float(desired_speed) - float(totalHz/float(totalRots))) < -2){
             base_val = base_val - 10;
          }
            else if ((float(desired_speed) - float(totalHz/float(totalRots))) >= 1){
             base_val = base_val + 5;
          }
            else if ((float(desired_speed) - float(totalHz/float(totalRots))) < -1){
             base_val = base_val - 5;
          }
             else if ((float(desired_speed) - float(totalHz/float(totalRots))) >= 0.5){
             base_val = base_val + 2;
          }
            else if ((float(desired_speed) - float(totalHz/float(totalRots))) < -0.5){
             base_val = base_val - 2;
          }
            else if ((float(desired_speed) - float(totalHz/float(totalRots))) >= 0.2){
             base_val = base_val + 1;
          }
            else if ((float(desired_speed) - float(totalHz/float(totalRots))) < -0.2){
             base_val = base_val - 1;
          }
          //END SPEED CONTROL
    }
    totalHz = 0;
    totalRots = 0;
  }
}


