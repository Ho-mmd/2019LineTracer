/* 이 소스는 에듀이노(Eduino)에 의해서 번역, 수정, 작성되었고 소유권 또한 에듀이노의 것입니다. 
 *  소유권자의 허락을 받지 않고 무단으로 수정, 삭제하여 배포할 시 법적인 처벌을 받을 수도 있습니다. 
 *  
 *  에듀이노 교육용 2휠 라인트레이서 기본예제 
 *  
 */

#include <SoftwareSerial.h>
#include <AFMotor.h>
AF_DCMotor motor_L(2);              // 모터드라이버 L293D 
AF_DCMotor motor_R(1);            // tx pin, rx pin
int i;
    
void setup() {
  Serial.begin(9600);              // PC와의 시리얼 통신속도
  Serial.println("Eduino Smart Car Start!");
  // turn on motor
  i = 200;
  motor_L.setSpeed(i);              // 왼쪽 모터의 속도   
  motor_L.run(RELEASE);
  motor_R.setSpeed(i                                                                                                                                                                                                                                                                                                                                                                                                               );              // 오른쪽 모터의 속도   
  motor_R.run(RELEASE);
}

void loop() {
  int val = digitalRead(A0);
  int val1 = digitalRead(A2);    
  int val2 = digitalRead(A5);
  i = 200;
  
  if (val == 0 && val2 == 0) {                   // 직진
    motor_L.setSpeed(i);
    motor_R.setSpeed(i); 
    motor_L.run(FORWARD); 
    motor_R.run(FORWARD);
}
     
  else if (val == 0 && val2 == 1 || val1 == 0) {              // 우회전
    while(i <= 100){
      i--;}
    motor_L.setSpeed(i); 
    motor_L.run(FORWARD); 
    motor_R.run(RELEASE);
 }
      
 else if (val == 1 && val2 == 0 || val1 == 0) {              // 좌회전
   while(i <= 100){
          i--;}
    motor_L.setSpeed(i); 
    motor_L.run(RELEASE); 
    motor_R.run(FORWARD);
 } 
     
 else if (val == 0 && val1 == 0 && val2 == 0) {              // 정지
    motor_L.run(RELEASE); 
    motor_R.run(RELEASE);
      }           
} 
