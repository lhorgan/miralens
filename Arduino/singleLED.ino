const int circuitInput;
 int arr[20] = {13,12,11,10,9,8,7,6,5,4,3,2,40,41,42,43,44,50,51,52};
int val = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
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
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);  
  pinMode(40, OUTPUT);
  digitalWrite(40, LOW);
  pinMode(41, OUTPUT);
  digitalWrite(41, LOW);  
  pinMode(42, OUTPUT);
  digitalWrite(42, LOW);
  pinMode(43, OUTPUT);
  digitalWrite(43, LOW);  
  pinMode(44, OUTPUT);
  digitalWrite(44, LOW); 
  pinMode(43, OUTPUT);
  digitalWrite(43, LOW); 
  pinMode(43, OUTPUT);
  digitalWrite(43, LOW); 
  pinMode(50, OUTPUT);
  digitalWrite(50, LOW); 
  pinMode(51, OUTPUT);
  digitalWrite(51, LOW); 
  pinMode(52, OUTPUT);
  digitalWrite(52, LOW); 

    Serial.begin(9600);

  }

void loop() {
  if(Serial.available()) {
    val = Serial.parseInt();
  }
  for (int i = 0; i < 20; i++){
    digitalWrite(arr[i], LOW);
  }
  digitalWrite(val, HIGH);
  delay(1000);
  //digitalWrite(13, LOW);
 /* digitalWrite(12, HIGH);
  delay(s);
  digitalWrite(12, LOW); 
  digitalWrite(11, HIGH);
  delay(s);
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  delay(s);
  digitalWrite(10, LOW);
  digitalWrite(9, HIGH);
  delay(s);
  digitalWrite(9, LOW);
  digitalWrite(8, HIGH);
  delay(s);
  digitalWrite(8, LOW);
  digitalWrite(7, HIGH);
  delay(s);
  digitalWrite(7, LOW);
  digitalWrite(5, HIGH);
  delay(s);
  digitalWrite(5, LOW);
  digitalWrite(2, HIGH);
  delay(s);
  digitalWrite(2, LOW);
  digitalWrite(50, HIGH);
  delay(s);
  digitalWrite(50, LOW);
   digitalWrite(40, HIGH);
  delay(s);
  digitalWrite(40, LOW);
   digitalWrite(44, HIGH);
  delay(s);
  digitalWrite(44, LOW);*/
}
