//Wemos libraries
#include <WemosInit.h>
#include <Servo.h>

#define motor1pin D4 
#define motor2pin D2

Servo motor1;
Servo motor2;

long duration_C;

const int THRESHOLD = 5;

const int speed1 = 80;

const int timeForSpin = 600;

const int sampleRate = 10;
const double inchesDivisor = 148;

boolean drivenForwards = false;
boolean turned = false;
boolean finished = false;

void setup(){
  Serial.begin(115200); // Set baud rate to serial monitor
  
  pinMode(D3,OUTPUT); //sets trigger pin of ultrasonic to port D3
  pinMode(D5,INPUT); //sets echo pin of ultrasonic to port D5

  //Initializes left and right motors to their respective pins
  motor1.attach(motor1pin);
  motor2.attach(motor2pin);
  
  delay(3000); //Delay 3 seconds to allow for time to open Serial Monitor after program upload
}

/* @function    spin   
 * @discussion          Function to move the motors forwards and backwards. 
 *                      Code automatically reverses delivered voltage to leftmotor
 *                      because motors are mirror imaged.
 * @param       speed   the speed the motors should be set to. 
 *                      Closer to zero means forwards. 180 represents backwards. 90 = stop
 */
void spin(int speed){

motor1.write(speed);
if(speed < 90){
  motor2.write(180 - speed +5);
  Serial.println(180 - speed);
  }

else if(speed > 90){
  motor2.write(170+speed);
    Serial.println(180 + speed);
  }

}

/* @function    stop   
 * @discussion  Function to stop all motors. Motors set to 90 speed.
 */
void stop (){
motor1.write(90);
motor2.write(90);
}

/* @function    calculateDistance   
 * @discussion  Function to calculate distance object is to front of ultrasonic sensor.
 *              Iterates once every samplerate value in milliseconds
 *              Obtains ultrasnic echo duration and returns this value divided by inchesDivisor factor
 *              to return distance as a float in inches
 */
double calculateDistance(){
 delay(sampleRate);
 duration_C = ultrasonicPing(D3,D5);
 double distance_inches = duration_C/inchesDivisor;
 return distance_inches;  
}

/* @function    stop   
 * @discussion  Function to drive robot to certain distance threshold from wall
 *              drives forwards at speed until threshold constant is returned by calculateDistance.
 *              Once distance is achieved, robot stops and drivenForwards class variable is set to true.
 */
void driveToWall(){
  if(calculateDistance() >= THRESHOLD){
    spin(speed1);
 }

 else if (calculateDistance() < 4){
  stop();
  drivenForwards = true;
   //Serial.println("Finished Baby!!!!!!");
 }

}

/* @function    turn   
 * @discussion          Function to turn the robot left for a predetermined 
 *                      and claibrated amount of time. Robot moves at 70 speed.
 *                      Then stops and sets turned class variable to true.
 * @param timeForSpin   Duration in milliseconds for turning of robot. 
 */
void turn(){
  delay(1500);
  motor1.write(70);
  motor2.write(70);
  Serial.println("Spinning");
  delay(timeForSpin);
  stop();
  turned = true;
  
}

void loop() 
{
  
   Serial.println(calculateDistance());
   /*
    * First checks if finished boolean is true
    * If condition is met the rest of the if chain is not checked
    * and robot stops moving
    */
   if(finished){
    stop();
    Serial.println("Done");
  }

  /*
   * Checks if drivenForwards variable is false
   * If it is robot runs driveToWall method
   * else robot moves onto Turn method call check
   */
  else if(drivenForwards != true && !finished){
      driveToWall();
      Serial.println("forwards");
  }
  
  /*
   * Checks if drivenForwards variable is true and turned variable is false.
   * If condition is met robot runs turn method
   * else robot moves onto second driveToWall method call check
   */
  else if(drivenForwards && !finished && turned != true){
      turn();
      Serial.println("Turning");
  }
  /*
   * Checks if turned variable is true.
   * If condition is met robot runs driveToWall Method
   * Distance is also checked and if it <=2 the finish class
   * variable is set to true
   */
  else if(turned && !finished){
     driveToWall();
     if(calculateDistance() <=2){
           finished = true; 
     }
     Serial.println("Reverse");
  }
}
