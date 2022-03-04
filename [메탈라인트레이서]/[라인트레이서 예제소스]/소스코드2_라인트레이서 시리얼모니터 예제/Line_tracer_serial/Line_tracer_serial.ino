int sensor = A0;        // 라인트레이서 센서를 9번 핀에 연결
int sensor1 = A2;
int sensor2 = A5;

void setup(){
  Serial.begin(9600); 
}

void loop(){
  int val = digitalRead(sensor);  // 센서 값을 읽어와서
  int val1 = digitalRead(sensor1);
  int val2 = digitalRead(sensor2);
  Serial.println(val);
  Serial.println(val1);
  Serial.println(val2);
  delay(100);
}
