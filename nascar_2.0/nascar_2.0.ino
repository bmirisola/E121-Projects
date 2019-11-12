#include <WemosInit.h>
#include <Servo.h>

#define leftMotorPin D2 
#define rightMotorPin D4

Servo leftMotor;
Servo rightMotor;

int counter = 0;

const int timeForSpin = 300;

void setup() {

  leftMotor.attach(leftMotorPin);
  rightMotor.attach(rightMotorPin);
  
  Serial.begin(115200);  // Set baud rate to serial monitor
  delay(2000);//Delay 5 seconds to allow for time to open Serial Monitor after program upload
  // put your setup code here, to run once:

  spin(10);
  delay(1100);
  stop();
  turn();
  spin(10);
  delay(750);
  stop();
  turn();
  spin(10);
  delay(2000);
  stop();
  turn();
  spin(10);
  delay(750);
  stop();
  turn();
  spin(10);
  delay(500);
  stop();

}

void spin(int speed){

  rightMotor.write(speed);
  if(speed < 90){
    leftMotor.write(180 - speed);
    Serial.println(180 - speed);
  }

  else if(speed > 90){
    leftMotor.write(170+speed);
    Serial.println(180 + speed);
  }

}

void turn(){
  delay(750);
  leftMotor.write(60);
  rightMotor.write(60);
  Serial.println("Spinning");
  delay(timeForSpin);
  stop();
  delay(500);
}

void stop (){
leftMotor.write(90);
rightMotor.write(90);
}


void loop() {
  // put your main code here, to run repeatedly:
  //rightMotor.write(0);

}
