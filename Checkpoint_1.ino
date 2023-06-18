#include <Servo.h>

const int trigPin = D1;   
const int echoPin = D2;    
const int servoPin = D3;   

Servo servo;  

void setup() {
 
  Serial.begin(9600);

  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.attach(servoPin);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  
  if (distance <= 20) {
    servo.write(90);
    delay(1000);
  } 
  else {
    servo.write(0);
  }

  delay(500);  