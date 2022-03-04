//초음파 센서 세팅
const int soundPin = 0;
 const int trigPin = 11;
 const int echoPin = 12;
 long distance;
 long duration;

 // 모터A의 핀배열
#define ENA 3 // motor A 속도조절용, 아두이노 3번핀과 모터드라이버 Enable 1,2 핀 연결
#define EN1 2 // motor A  모터와 모터드라이버 OUTPUT 1번 핀 연결
#define EN2 4 // motor A  모터와 모터드라이버 OUTPUT 2번 핀 연결

// 모터B의 핀배열 초기화
#define ENB 5  // motor A 속도조절용, 아두이노 3번핀과 모터드라이버 Enable 3,4 핀 연결
#define EN3 7  // motor B  모터와 모터드라이버 OUTPUT 3번 핀 연결
#define EN4 6  // motor B  모터와 모터드라이버 OUTPUT 4번 핀 연결

int carSpeed = 200; // RC카의 속도
int carSpeed_smooth = 50; //부드러운 회전시 RC카의 속도

void setup() {

   // 초음파 센서 입출력 핀 설정
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
   pinMode(echoPin, INPUT); // Sets the echoPin as an Input

   // 모터 활성화핀 출력모드로 초기화
  pinMode(ENA, OUTPUT);
   pinMode(ENB, OUTPUT);

   // 모터A의 두 핀을 출력 모드로 초기화
  pinMode(EN1, OUTPUT);
   pinMode(EN2, OUTPUT);

   // 모터B의 두 핀을 출력 모드로 초기화
  pinMode(EN3, OUTPUT);
   pinMode(EN4, OUTPUT);
 }

 void loop(){
 ultra();
   if (distance > 10 && distance < 30) {
       moving_forward();
   }
     else if(distance < 10) {
       moving_backward();
     }
     else {
        stop_moving();
     }
     // 일정시간 지연
  delay(100);
 }

 void moving_forward(){
   // 모터A를 정방향으로 회전
  digitalWrite(EN1, HIGH);
   digitalWrite(EN2, LOW);
   analogWrite(ENA, carSpeed);

   // 모터B를 정방향으로 회전
  digitalWrite(EN3, HIGH);
   digitalWrite(EN4, LOW);
   analogWrite(ENB, carSpeed);
 }

 void moving_backward(){
   // 모터A를 역방향으로 회전
  digitalWrite(EN1, LOW);
   digitalWrite(EN2, HIGH);
   analogWrite(ENA, carSpeed);

   // 모터B를 역방향으로 회전
  digitalWrite(EN3, LOW);
   digitalWrite(EN4, HIGH);
   analogWrite(ENB, carSpeed);
 }

 void moving_left(){
   // 모터A를 정방향으로 회전
  digitalWrite(EN1, LOW);
   digitalWrite(EN2, HIGH);
   analogWrite(ENA, carSpeed);

   // 모터B를 역방향으로 회전
  digitalWrite(EN3, HIGH);
   digitalWrite(EN4, LOW);
   analogWrite(ENB, carSpeed);
 }

 void moving_right(){
   // 모터A를 역방향으로 회전
  digitalWrite(EN1, HIGH);
   digitalWrite(EN2, LOW);
   analogWrite(ENA, carSpeed);

   // 모터B를 정방향으로 회전
  digitalWrite(EN3, LOW);
   digitalWrite(EN4, HIGH);
   analogWrite(ENB, carSpeed);
 }

 void stop_moving(){
   // 모터A와 모터B를 비활성화
  analogWrite(ENA, LOW);
   analogWrite(ENB, LOW);
 }

 void moving_smooth_left(){
   // 모터A를 정방향으로 회전
  digitalWrite(EN1, HIGH);
   digitalWrite(EN2, LOW);
   analogWrite(ENA, carSpeed_smooth);

   // 모터B를 역방향으로 회전
  digitalWrite(EN3, HIGH);
   digitalWrite(EN4, LOW);
   analogWrite(ENB, carSpeed);
 }

 void moving_smooth_right(){
   // 모터A를 역방향으로 회전
  digitalWrite(EN1, HIGH);
   digitalWrite(EN2, LOW);
   analogWrite(ENA, carSpeed);

   // 모터B를 정방향으로 회전
  digitalWrite(EN3, HIGH);
   digitalWrite(EN4, LOW);
   analogWrite(ENB, carSpeed_smooth);
 }

 void ultra(){
 // Clears the trigPin
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);

 // Sets the trigPin on HIGH state for 10 micro seconds
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);

 // Reads the echoPin, returns the sound wave travel time in microseconds
 duration = pulseIn(echoPin, HIGH);

 // Calculating the distance
 distance= duration*0.034/2;
 }
