#include <NewPing.h>
#include <AFMotor.h>
#include <SoftwareSerial.h>

AF_DCMotor motor_L(4);              // 모터드라이버 L293D  3: M3에 연결,  4: M4에 연결
AF_DCMotor motor_R(3); 
#define BT_RXD A5
#define BT_TXD A4
SoftwareSerial bluetooth(BT_RXD, BT_TXD);       // RX: A5, TX: A4

int i;

//초음파센서 출력핀(trig)과 입력핀(echo), 변수, 함수 선언//
#define TRIGGER_CH1_PIN  0 //첫번째 Trigger pin
#define ECHO_CH1_PIN     1 //첫번째 Echo pin

#define TRIGGER_CH2_PIN  4 //두번째 Trigger pin
#define ECHO_CH2_PIN     5 //두번째 Echo Pin

#define MAX_DISTANCE 200   //최대 측정 거리 설정
long duration, distance;

void Obstacle_Check();
void Distance_Measurement();
void Forward();
void Backward();
void Right();
void Left();
void Stop();

void setup(){
  Serial.begin(9600);              // PC와의 시리얼 통신속도
  bluetooth.begin(9600);            // 스마트폰 블루투스 통신속도
  Serial.println("Eduino Smart Car Start!");

  pinMode(ECHO_CH1_PIN, INPUT);   // EchoPin 입력
  pinMode(TRIGGER_CH1_PIN, OUTPUT);  // TrigPin 출력
  pinMode(ECHO_CH2_PIN, INPUT);   // EchoPin 입력
  pinMode(TRIGGER_CH2_PIN, OUTPUT);  // TrigPin 출력

  motor_L.setSpeed(200);              // 왼쪽 모터의 속도   
  motor_L.run(FORWARD);
  motor_R.setSpeed(200);              // 오른쪽 모터의 속도   
  motor_R.run(FORWARD);
}

void loop(){
  Distance_Measurement();
  motor_L.run(FORWARD);
  motor_R.run(FORWARD);
  motor_L.setSpeed(200);
  motor_R.setSpeed(200);
  bluetooth.println(distance);  
  if(distance<150)
  {
    int j=0;
    if(distance<85)
    {
      while(j<100)
      {
        motor_R.setSpeed(200);
        motor_L.run(RELEASE);
        j++;
      }
    }
    else if(distance>105)
    {
      while(j<100)
      {
        motor_L.setSpeed(200);
        motor_R.run(RELEASE);
        j++;
      }
    }
  }
}

///////////장애물 확인 및 회피 방향 결정///////////
void Obstacle_Check()
{      
  Distance_Measurement();
  
  Serial.println(distance);     
   while(1){
   if(distance<80){    
     Left();
     Forward();
     Distance_Measurement();
   }
   else if(distance>110)
   {   
     Right();
     Forward();
     Distance_Measurement();
    }
    Distance_Measurement();
    Serial.println(distance);
    Forward();
   }
}


////////거리감지///////////
  //첫번째 거리 읽기
  Serial.print("Ch1: ");
  Serial.print(sonar_ch1.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println();

  //두번째 거리 읽기
  Serial.print("Ch2: ");
  Serial.print(sonar_ch2.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println();
  
}
}


///////////방향 제어 함수////////////
void Forward(){    
    motor_L.run(FORWARD);  motor_R.run(FORWARD);
    for (i=0; i<200; i=i+20) { 
      motor_L.setSpeed(i);  motor_R.setSpeed(i);  
      delay(2);
    }
    for (i=200; i<0; i=i-20) {
      motor_L.setSpeed(i);  motor_R.setSpeed(i);  
      delay(2);
    }
}

void Backward(){
    motor_L.run(BACKWARD);  motor_R.run(BACKWARD);
    for (i=0; i<200; i=i+20) {
      motor_L.setSpeed(i);  motor_R.setSpeed(i);  
      delay(2);
    }
    for (i=200; i<0; i=i-20) {
      motor_L.setSpeed(i);  motor_R.setSpeed(i);  
      delay(2);
    }
}

void Right(){      
    motor_L.run(FORWARD); motor_R.run(BACKWARD);
    for (i=0; i<180; i=i+20) {
        motor_L.setSpeed(i);  motor_R.setSpeed(i);
        delay(2);
    }
    for (i=180; i<0; i=i-20) {
      motor_L.setSpeed(i);  motor_R.setSpeed(i);  
      delay(2);
    }
}

void Left(){
    motor_R.run(FORWARD); motor_L.run(BACKWARD);
    for (i=0; i<180; i=i+20) {
        motor_L.setSpeed(i);  motor_R.setSpeed(i);
        delay(2);
    }
    for (i=180; i<0; i=i-20) {
      motor_L.setSpeed(i);  motor_R.setSpeed(i);  
      delay(2);
    }
}

void Stop(){
   motor_L.run(RELEASE);       motor_R.run(RELEASE);
   for (i=200; i>=0; i=i-20) {
          motor_L.setSpeed(i);  motor_R.setSpeed(i);  
          delay(2);
   }
}
