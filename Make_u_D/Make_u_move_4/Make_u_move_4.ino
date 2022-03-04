#include <AFMotor.h>

#include <SoftwareSerial.h>

 
AF_DCMotor motor_L(4);              // 모터드라이버 L293D  3: M3에 연결,  4: M4에 연결

AF_DCMotor motor_R(3); 

#define BT_RXD A5

#define BT_TXD A4

SoftwareSerial bluetooth(BT_RXD, BT_TXD);       // RX: A5, TX: A4

 

int i;

 

//초음파센서 출력핀(trig)과 입력핀(echo), 변수, 함수 선언//

int TrigPin = A0;

int EchoPin = A1;

long duration, distance;

 

void Distance_Measurement();

 

void setup(){

  Serial.begin(9600);              // PC와의 시리얼 통신속도

  bluetooth.begin(9600);            // 스마트폰 블루투스 통신속도

  Serial.println("Eduino Smart Car Start!");

 

  pinMode(EchoPin, INPUT);   // EchoPin 입력

  pinMode(TrigPin, OUTPUT);  // TrigPin 출력

 

  motor_L.setSpeed(250);              // 왼쪽 모터의 속도   

  motor_L.run(FORWARD);

  motor_R.setSpeed(250);              // 오른쪽 모터의 속도   

  motor_R.run(FORWARD);

}

 

void loop(){

  Distance_Measurement();

  motor_L.run(FORWARD);

  motor_R.run(FORWARD);

  motor_L.setSpeed(230);

  motor_R.setSpeed(230);

  bluetooth.println(distance);

  if(distance<85)

  {

    motor_L.run(RELEASE);

  }

    

  else if(distance>100&&distance<2000)

  {

    motor_R.run(RELEASE);

  }

}

 

////////거리감지///////////

void Distance_Measurement()

{

  digitalWrite(TrigPin, LOW);

  delay(2);

  digitalWrite(TrigPin, HIGH);  // trigPin에서 초음파 발생(echoPin도 HIGH)

  delayMicroseconds(10);

  digitalWrite(TrigPin, LOW);

  duration = pulseIn(EchoPin, HIGH);    // echoPin 이 HIGH를 유지한 시간을 저장 한다.

  distance = ((float)(340 * duration) / 1000) / 2;

  delay(5);

}
