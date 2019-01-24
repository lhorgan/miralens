/*
 * This code is for a prototype board that will rotate through 10 basic LED lights
 * 
 */
/////////////////////
// Pin Definitions //
/////////////////////
const int selectPins[3] = {2, 3, 4}; // S0~2, S1~3, S2~4
const int zOutput = 5; // Connect common (Z) to 5 (PWM-capable)

const int selectLEDs[2] = {7,8}; 
const int disable = 6; 
const int us = 250; // need 1/4000 HZ or .25 ms
void setup() 
{
  // Set up the select pins 2, 3, 4 as outputs
  for (int i=0; i<3; i++)
  {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], LOW);
  }

  pinMode(zOutput, OUTPUT); // Set up Z as an output - digital pin 5
  pinMode(disable, OUTPUT); // Digital pin 6 as diable
  digitalWrite(disable, LOW);
  
  pinMode(selectLEDs[0], OUTPUT);
  digitalWrite(selectLEDs[0], LOW);
  pinMode(selectLEDs[1], OUTPUT);
  digitalWrite(selectLEDs[1], LOW);
}

void loop() 
{
  // Cycle from pins Y0 to Y7 first
  for (int pin=0; pin<=7; pin++)
  {
    // Set the S0, S1, and S2 pins to select our active
    // output (Y0-Y7):
    selectMuxPin(pin);
    analogWrite(zOutput, 255);
    delayMicroseconds(us);
    analogWrite(zOutput, 0);
    
  }

  digitalWrite(disable, HIGH);
  
  digitalWrite(selectLEDs[0], HIGH);
  delayMicroseconds(us);
  digitalWrite(selectLEDs[0], LOW);

  digitalWrite(selectLEDs[1], HIGH);
  delayMicroseconds(us);
  digitalWrite(selectLEDs[1], LOW);
  
  digitalWrite(disable, LOW);
}

// The selectMuxPin function sets the S0, S1, and S2 pins
// accordingly, given a pin from 0-7.
void selectMuxPin(byte pin)
{
  if (pin > 7) return; // Exit if pin is out of scope
  for (int i=0; i<3; i++)
  {
    if (pin & (1<<i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}
