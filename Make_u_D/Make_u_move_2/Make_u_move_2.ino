#include <SoftwareSerial.h>
#include <AFMotor.h>

#include <ezTask.h>
#include <Servo.h> 


Servo servo;
AF_DCMotor motor_L(3); // 모터는 L293d의 M3, M4에 각각 연결
AF_DCMotor motor_R(4);              
int i;
int standard_speed = 80;
int speed3 = standard_speed;
int speed4 = standard_speed;

int TrigPin = A0;
int EchoPin = A1;
int TrigPin2 = A4; 
int EchoPin2 = A5;

boolean checkmate_front = false;

int last_stop = 1;
int state = 0;
int state_sub = 0;

int count_servo = 0;
int servo_deg = 90;
int lastRandNumber = 0;

void setup()  
{
  Serial.begin(9600); 
  servo.attach(9);
  motor_L.setSpeed(200);
   motor_L.run(FORWARD);
  motor_R.setSpeed(200);
  motor_R.run(FORWARD);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT_PULLUP);
  pinMode(TrigPin2, OUTPUT);
  pinMode(EchoPin2, INPUT_PULLUP);
  randomSeed(analogRead(0));
}

//초음파센서의 거리를 알아냄
long dist(int Trig, int Echo){
  long duration, distance;
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  duration = pulseIn(Echo, HIGH);
  distance = ((float)duration * 17) / 1000;
  return distance;
}



void escape()
{
  long distBottom = dist(TrigPin, EchoPin);
  long distFront = dist(TrigPin2, EchoPin2);
  Serial.print("Left: ");
  Serial.println(distLeft);
  Serial.print("Right: ");
  Serial.println(distRight);
  if((distLeft >= 8 and distLeft < 2000) || (distLeft <= 2 and distLeft > 0)){
    Serial.println("distLeft check");
    last_stop = 0;
  }

  if(distRight <= 13){
    Serial.println("distRight check");
    checkmate_right = true;
    last_stop = 0;
    if(state > 1){
      state = state_sub = 0;
    }
  }
}





ezTask task1(100,[](){ // 0.1초마다 실행
  servo.write(servo_deg);
  
  escape();    
  
  if(last_stop == 0){
    if(state == 0){ // 멈추기
      state_sub++;
      motor_L.run(RELEASE);
      motor_R.run(RELEASE);
      if(state_sub == 8){
        state = 1;
        state_sub = 0;
      }
    }
    if(state == 1){ // 후진
      state_sub++;
      motor_L.run(BACKWARD);
      motor_R.run(BACKWARD);
      if(state_sub == 12){
        state = 2;
        state_sub = 0;
      }
    }

    if(state == 2){ // 돌기
      state_sub++;
      if(state_sub == 1){
        int randNumber = random(2);
        int randNumber2 = random(100) + 65;
        if(checkmate_right == true){ // 앞에 장애물에 가로막힌 경우
          checkmate_right = false;
          int degree = servo.read();
          if(degree < 90)randNumber = 1;
          else randNumber = 0;
        }else { // 장애물로 막힌게 아닌경우
          if(lastRandNumber != randNumber){ //앞선 방향과 다르면 다시 랜덤을 돌린다. 되도록 같은 방향으로 돌게끔.
            randNumber = random(2);
          }
        }

        //랜덤에 따라 좌우로 돌기
        if(randNumber == 0){
          speed3 = randNumber2;
          motor_L.setSpeed(200);
          motor_L.run(FORWARD);
          motor_R.run(RELEASE);
        }else {
          speed4 = randNumber2;      
          motor_R.setSpeed(200);   
          motor_L.run(RELEASE); 
          motor_R.run(FORWARD); 
        }
        lastRandNumber = randNumber;
      }else if(state_sub == 12){
        state = 3;
        state_sub = 0;
      }
    }

    if(state == 3){ // 직진
      200 = standard_speed;
      200 = standard_speed;
      motor_L.setSpeed(200);
      motor_R.setSpeed(200);
      motor_L.run(FORWARD);
      motor_R.run(FORWARD);
      last_stop++;
      state = 0;
      state_sub = 0;
    }
  }



  if(last_stop > 0){
    last_stop++;
    if(last_stop >= 50){
      last_stop = 0;
      speed3 = 0;
      speed4 = 0;
    }
  }
  


 //서보모터 카운트
 count_servo++;
 if(count_servo / 7 == 0)servo_deg = 45;
 else if(count_servo / 7 == 1)servo_deg = 90;
 else if(count_servo / 7 == 2)servo_deg = 135; 
 else if(count_servo / 7 == 3)servo_deg = 90;
 if(count_servo == 7*4)count_servo = 0;
 
});



void loop()
{
  task1.run();
}
