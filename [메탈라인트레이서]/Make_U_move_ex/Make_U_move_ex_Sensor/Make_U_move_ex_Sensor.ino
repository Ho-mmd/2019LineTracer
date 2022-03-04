int sensor = A0;
int sensor1 = A5;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int val = digitalRead(sensor);
  Serial.println(val);
  delay(100);

  int val1 = digitalRead(sensor1);
  Serial.println(val1);
  delay(100);
}
