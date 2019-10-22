#include <WemosInit.h>
#include <Servo.h>

#define motor1pin D4 
#define motor2pin D2

Servo motor1;
Servo motor2;

long duration_C;

const int THRESHOLD1 = 20;
const int THRESHOLD2 = 10;
const int THRESHOLD3 = 6;
const int THRESHOLD4 = 5;

const int speed1 = 80;
const int speed2 = 80;
const int speed3 = 80;
const int speed4 = 80;

const int timeForSpin = 600;

const int sampleRate = 10;
const double inchesDivisor = 148;

boolean drivenForwards = false;
boolean turned = false;
boolean finished = false;


void setup()
{
  Serial.begin(115200);
  pinMode(D3,OUTPUT); 
  pinMode(D5,INPUT);
  motor1.attach(motor1pin);
  motor2.attach(motor2pin);
  delay(3000);

  
}

void spin(int speed)

{

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

void stop (){
motor1.write(90);
motor2.write(90);
}

double calculateDistance(){
 delay(sampleRate);
 duration_C = ultrasonicPing(D3,D5);
 double distance_inches = duration_C/inchesDivisor;
 return distance_inches;  
}

void driveToWall(){
  if(calculateDistance() >= THRESHOLD1){
    spin(speed1);
    //drivenForwards = false;
 }

 else if(calculateDistance() >= THRESHOLD2 && calculateDistance() < THRESHOLD1){
  spin(speed2);
  //drivenForwards = false;
 }

 else if(calculateDistance() >= THRESHOLD3 && calculateDistance() < THRESHOLD2){
  spin(speed3);
  //drivenForwards = false;
 }

 else if(calculateDistance() >= THRESHOLD4 && calculateDistance() < THRESHOLD3){
  spin(speed4);
  //drivenForwards = false;
 }

 else if (calculateDistance() < 4){
  stop();
  drivenForwards = true;
   //Serial.println("Finished Baby!!!!!!");
 }

  
}

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
   if(finished){
    stop();
    Serial.println("Done");
  }
  
  else if(drivenForwards != true && !finished){
      driveToWall();
      Serial.println("forwards");
  }
  
  else if(drivenForwards && !finished && turned != true){
      turn();
      Serial.println("Turning");
  }

  else if(turned && !finished){
     driveToWall();
     if(calculateDistance() <=2){
           finished = true; 
     }
     Serial.println("Reverse");
  }
  
}
