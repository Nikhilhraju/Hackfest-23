#include <Servo.h>
#include <Astra.h>

#define TRIGGER_PIN1 2
#define ECHO_PIN1 3
#define TRIGGER_PIN2 4
#define ECHO_PIN2 5
#define TRIGGER_PIN3 6
#define ECHO_PIN3 7

Servo servo1;
Servo servo2;
Servo servo3;

SoftwareSerial astraSerial(8, 9);  

Astra astra(astraSerial);
const int ROWS = 5;   
const int COLS = 5;      


int grid[ROWS][COLS] = {
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0}
};


int startX = 0;
int startY = 0;
int goalX = 4;
int goalY = 4;


void setup() {
  pinMode(TRIGGER_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(TRIGGER_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);
  pinMode(TRIGGER_PIN3, OUTPUT);
  pinMode(ECHO_PIN3, INPUT);

  astraSerial.begin(115200);
  astra.init();

  servo1.attach(10);
  servo2.attach(11);
  servo3.attach(12);

  motor1.setSpeed(255);
  motor2.setSpeed(255);
}

void loop() {
  int distance1 = getUltrasonicDistance(TRIGGER_PIN1, ECHO_PIN1);
  int distance2 = getUltrasonicDistance(TRIGGER_PIN2, ECHO_PIN2);
  int distance3 = getUltrasonicDistance(TRIGGER_PIN3, ECHO_PIN3);

  if (astra.update()) {
    if (astra.isPathAvailable()) {
      
      int leftSpeed = astra.getLeftSpeed();
      int rightSpeed = astra.getRightSpeed();
      motor1.run(leftSpeed > 0 ? FORWARD : BACKWARD);
      motor2.run(rightSpeed > 0 ? FORWARD : BACKWARD);
      motor1.setSpeed(abs(leftSpeed));
      motor2.setSpeed(abs(rightSpeed));

      
      controlServos(distance1, distance2, distance3);
    } else {
      
      motor1.run(RELEASE);
      motor2.run(RELEASE);
    }
  }
}

int getUltrasonicDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}

void controlServos(int distance1, int distance2, int distance3) {
  
  if (distance1 < 10) {
    servo1.write(90); 
    delay(500);
    servo1.write(0);   
    delay(500);
  }

  else if (distance2 < 10) {
    servo2.write(90);  
    delay(500);
    servo2.write(0);   
    delay(500);
  }

  if (distance3 < 10) {
    servo3.write(90);  
    delay(500);
    servo3.write(0);   
    delay(500);
  }
}