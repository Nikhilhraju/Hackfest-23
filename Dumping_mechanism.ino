#include <Servo.h>

const int servo1Pin = D1;    
const int servo2Pin = D2;    


Servo servo1;
Servo servo2;

void setup()
 {
  
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
}

void loop() 
{
servo1.write(90);
servo2.write(90);
delay(5000);

servo1.write(0);
servo2.write(0);
delay(5000);


}