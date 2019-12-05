//Wemos libraries
#include <WemosInit.h>
#include <Servo.h>

#define leftMotorPin D2 
#define rightMotorPin D4

Servo leftMotor;
Servo rightMotor;

int counter = 0;

void setup() {
  //Initializes left and right motors to their respective pins
  leftMotor.attach(leftMotorPin);
  rightMotor.attach(rightMotorPin);
  
  Serial.begin(115200);  // Set baud rate to serial monitor
  delay(2000);//Delay 2 seconds to allow for time to open Serial Monitor after program upload

  drive(15); //drive forwards at 15 speed
  delay(850); //Drive forwards for 850 milliseconds
  turnRight(300); //Call the turn right method for 300 milliseconds
  drive(15); //drive forwards at 15 speed
  delay(1800); //Drive forwards for 1800 milliseconds
  turnLeft(300); //Call the turn left method for 300 milliseconds
  drive(15); //drive forwards at 15 speed
  delay(400); ////Drive forwards for 400 milliseconds
  stop(); //stop all motors. Set speed equal to Zero
  delay(900); //Wait 900 milliseconds before starting to move again
  drive(170); //drive backwards at 170 speed
  delay(1000); //Drive backwards for 1000 milliseconds
  stop(); //stop all motors. Set speed equal to Zero
  delay(1000); //Wait 1000 milliseconds before starting to move again
  drive(15); //drive forwards at 15 speed
  delay(800); //Drive forwards for 800 milliseconds
  stop(); //stop all motors. Set speed equal to Zero
  delay(500); //Wait 500 milliseconds before starting to move again
  turnLeft(250); //Call the turn right method for 250 milliseconds
  drive(15); //drive forwards at 15 speed
  delay(1500); //Drive forwards for 1500 milliseconds
  stop(); //stop all motors. Set speed equal to Zero
  turnRight(275); //Call the turn right method for 275 milliseconds
  drive(15); //drive forwards at 15 speed
  delay(800); //Drive forwards for 800 milliseconds
  stop(); //stop all motors. Set speed equal to Zero
  delay(500); //Wait 500 milliseconds before starting to move again
  drive(170); //drive backwards at 170 speed
  delay(1000); //Drive forwards for 1000 milliseconds
  stop(); //stop all motors. Set speed equal to Zero
  delay(500); //Wait 500 milliseconds before starting to move again
  turnLeft(300); //Call the turn left method for 300 milliseconds
  drive(20); //drive forwards at 20 speed
  delay(200); //Drive forwards for 200 milliseconds
  stop(); //stop all motors. Set speed equal to Zero
  
}
/* @function    drive   
 * @discussion          Function to move the motors forwards and backwards. 
 *                      Code automatically reverses delivered voltage to leftmotor
 *                      because motors are mirror imaged.
 * @param       speed   the speed the motors should be set to. 
 *                      Closer to zero means forwards. 180 represents backwards. 90 = stop
 */
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

/* @function    turnLeft   
 * @discussion          Function to turn the robot left. Robot moves at 60 speed
 *                      Then stops for 500 milliseconds
 * @param timeForSpin   Duration in milliseconds for turning of robot. 
 */
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

/* @function    turnRight   
 * @discussion          Function to turn the robot right. Robot moves at 120 speed
 *                      Then stops for 500 milliseconds
 * @param timeForSpin   Duration in milliseconds for turning of robot. 
 */
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

/* @function    stop   
 * @discussion          Function to stop all motors. Motors set to 90 speed.
 */
void stop (){
leftMotor.write(90);
rightMotor.write(90);
Serial.println("Stop");
}

void loop() {
  // put your main code here, to run repeatedly:

}
