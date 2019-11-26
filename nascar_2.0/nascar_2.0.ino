//Wemos libraries
#include <WemosInit.h>
#include <Servo.h>

#define leftMotorPin D2 
#define rightMotorPin D4

Servo leftMotor;
Servo rightMotor;

int counter = 0;

const int timeForSpin = 300;

void setup() {
  //Initializes left and right motors to their respective pins
  leftMotor.attach(leftMotorPin);
  rightMotor.attach(rightMotorPin);
  
  Serial.begin(115200);  // Set baud rate to serial monitor
  delay(2000); //Delay 2 seconds to allow for time to open Serial Monitor after program upload

  spin(10); //drive forwards at 10 speed
  delay(1100); //Drive forwards for 1100 milliseconds
  stop(); //Stop moving robot. Set motor speed to 90
  turn(); //Turn left
  spin(10); //drive forwards at 10 speed
  delay(750); //Drive forwards for 750 milliseconds
  stop(); //Stop moving robot. Set motor speed to 90
  turn(); //Turn left
  spin(10); //drive forwards at 10 speed
  delay(2000); //Drive forwards for 2000 milliseconds
  stop(); //Stop moving robot. Set motor speed to 90
  turn(); //Turn left
  spin(10); //drive forwards at 10 speed
  delay(750); //Drive forwards for 750 milliseconds
  stop(); //Stop moving robot. Set motor speed to 90
  turn(); //Turn left
  spin(10); //drive forwards at 10 speed
  delay(500); //Drive forwards for 500 milliseconds
  stop(); //Stop moving robot. Set motor speed to 90

}

/* @function    spin   
 * @discussion          Function to move the motors forwards and backwards. 
 *                      Code automatically reverses delivered voltage to leftmotor
 *                      because motors are mirror imaged.
 * @param       speed   the speed the motors should be set to. 
 *                      Closer to zero means forwards. 180 represents backwards. 90 = stop
 */
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

/* @function    turn   
 * @discussion          Function to turn the robot left for a predetermined 
 *                      and claibrated amount of time. Robot moves at 60 speed.
 *                      Then stops for 500 milliseconds.
 * @param timeForSpin   Duration in milliseconds for turning of robot. 
 */
void turn(){
  delay(750);
  leftMotor.write(60);
  rightMotor.write(60);
  Serial.println("Spinning");
  delay(timeForSpin);
  stop(); 
  delay(500);
}

/* @function    stop   
 * @discussion  Function to stop all motors. Motors set to 90 speed.
 */
void stop (){
leftMotor.write(90);
rightMotor.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
}
