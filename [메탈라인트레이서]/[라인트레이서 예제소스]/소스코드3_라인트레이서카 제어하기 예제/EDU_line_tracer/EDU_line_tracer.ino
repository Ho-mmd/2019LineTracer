#include <AFMotor.h>
#include <SoftwareSerial.h>

SoftwareSerial hc06(4,3); //Tx, Rx

void setup() {
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  //hc06.begin(9600);//
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);
}

AF_DCMotor motor_L(1);              // 모터드라이버 L293D 
AF_DCMotor motor_R(2);              // tx pin, rx pin

void loop() {
  /*if(hc06.available()){
    Serial.write(hc06.read()); //블루투스 내용을 시리얼에 쓰기
    int data =hc06.write(Serial.read());*/


  /*  hc06.write(Serial.read()); //시리얼 모니터 내용을 블루투스에 쓰기
  }*/
  
  int val = digitalRead(A0);        // 우측 적외선
  int val2 = digitalRead(A2);       //좌측 적외선

  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  delayMicroseconds(2);
  digitalWrite(13, HIGH);
  delayMicroseconds(10);
  digitalWrite(13, LOW);
  
  unsigned long duration = pulseIn(12, HIGH);
  float distance = ((float)(340 * duration) / 10000) / 2;

  Serial.print(distance);
  Serial.println("cm");

 
  if(distance < 10.00){
    motor_L.run(RELEASE); 
    motor_R.run(RELEASE);
  }

  else{
  if (val == 0 && val2 == 0) {                   // 직진
    motor_L.setSpeed(100);
    motor_R.setSpeed(100); 
    motor_L.run(FORWARD); 
    motor_R.run(FORWARD);
  }
  
     
  else if (val == 1 && val2 == 0) {              // 우회전
    motor_L.setSpeed(90); 
    motor_R.setSpeed(110); 
    motor_L.run(FORWARD); 
    motor_R.run(BACKWARD);
 }
      
 else if (val == 0 && val2 == 1) {              // 좌회전
     motor_L.setSpeed(120); 
     motor_R.setSpeed(100);
     motor_L.run(BACKWARD); 
     motor_R.run(FORWARD);
 } 
 
}}
