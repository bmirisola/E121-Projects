#include <WemosInit.h>
#include <Servo.h>

const int sampleRate = 10;
long duration_C;
const double inchesDivisor = 148;
boolean drivenForwardsLong = false;
boolean turned = false;
int turns = 0;

Servo motor1;
Servo motor2;

const int timeForSpin = 600;

#define motor1pin D4 
#define motor2pin D2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //center arduino
  pinMode(D3,OUTPUT); 
  pinMode(D5,INPUT);

  //left sensor
  pinMode(D1,OUTPUT);//trigger
  pinMode(D8,INPUT); //echo

  //right sensor
  pinMode(D7,OUTPUT); //trigger
  pinMode(D6,INPUT); //echo

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

void turn(){
  delay(1500);
  motor1.write(70);
  motor2.write(70);
  Serial.println("Spinning");
  delay(timeForSpin);
  stop();
  drivenForwardsLong  = false;
  turns++;
}

void stop (){
motor1.write(90);
motor2.write(90);
}


double centerCalculateDistance(){
 //delay(sampleRate);
 duration_C = ultrasonicPing(D3,D5);
 return duration_C/inchesDivisor;   
}

double leftCalculateDistance(){
 delay(sampleRate);
 duration_C = ultrasonicPing(D1,D8);
 return duration_C/inchesDivisor; 
}

double rightCalculateDistance(){
 delay(sampleRate);
 duration_C = ultrasonicPing(D7,D6);
 return duration_C/inchesDivisor; 
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(centerCalculateDistance());
    //Serial.println(rightCalculateDistance());
    Serial.println(leftCalculateDistance());
  if (turns >= 4 && centerCalculateDistance() < 10){
    stop();
  }
  
   if(!drivenForwardsLong){
    if(centerCalculateDistance()< 5)
    {
      drivenForwardsLong = true;
    }
  }

  else if(drivenForwardsLong){
          turn();
  }

  else{
    spin(50);
  }
//    motor1.write(0);
//    motor2.write(0);
  Serial.println(centerCalculateDistance());
  Serial.println("hi:");
}
