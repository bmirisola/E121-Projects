#include <WemosInit.h>
#include <Servo.h>

#define leftMotorPin D2 
#define rightMotorPin D4

Servo leftMotor;
Servo rightMotor;

int counter = 0;

void setup() {
  leftMotor.attach(leftMotorPin);
  rightMotor.attach(rightMotorPin);
  
  Serial.begin(115200);  // Set baud rate to serial monitor
  delay(2000);//Delay 5 seconds to allow for time to open Serial Monitor after program upload
  // put your setup code here, to run once:

  drive(30);
  delay(200);
  turnRight(300);
  drive(15);
  delay(1800);
  turnLeft(200);
  drive(15);
  delay(1200);
  stop();
  delay(1000);
  drive(170);
  delay(900);
  stop();
  delay(1000);
  drive(75);
  delay(300);
  stop();
  delay(500);
  turnLeft(250);
  drive(15);
  delay(1400);
  stop();
  turnRight(275);
  drive(15);
  delay(800);
  stop();
  delay(500);
  drive(170);
  delay(1000);
  stop();
  delay(500);
  turnLeft(300);
  drive(20);
  delay(200);
  stop();
  
  
//drive(165);
  
}

void drive(int speed){

  rightMotor.write(speed);
  if(speed < 90){
    leftMotor.write(180 - speed);
    Serial.println(180 - speed);
  }

  else if(speed > 90){
    leftMotor.write(180-speed);
    Serial.println(180 - speed);
  }

}

void turnLeft(int timeForSpin){
  stop();
  delay(750);
  leftMotor.write(60);
  rightMotor.write(60);
  Serial.println("Spinning Left");
  delay(timeForSpin);
  stop();
  delay(500);
}

void turnRight(int timeForSpin){
  stop();
  delay(750);
  leftMotor.write(120);
  rightMotor.write(120);
  Serial.println("Spinning Right");
  delay(timeForSpin);
  stop();
  delay(500);
}

void stop (){
leftMotor.write(90);
rightMotor.write(90);
Serial.println("Stop");
}

void loop() {
  // put your main code here, to run repeatedly:
  //rightMotor.write(0);

}
