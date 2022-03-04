#include <SoftwareSerial.h>
#include <AFMotor.h>

 

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);
}

void loop() {
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
}
