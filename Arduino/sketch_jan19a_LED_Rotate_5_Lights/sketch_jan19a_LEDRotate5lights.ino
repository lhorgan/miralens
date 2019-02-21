const int circuitInput;
void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);
}

void loop() {
  int s = 250;
  // put your main code here, to run repeatedly:
  digitalWrite(7, HIGH);
  delayMicroseconds(s);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  delayMicroseconds(s);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delayMicroseconds(s);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  delayMicroseconds(s);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delayMicroseconds(s);
  digitalWrite(11, LOW);
}
