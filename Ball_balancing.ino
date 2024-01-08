#include <Servo.h>
Servo servo;
const int echoPin1 = 8; 
const int pingPin1 = 9; 
const int echoPin2 = 6; 
const int pingPin2 = 7; 

#define kp 35
#define ki 0.015
#define kd 420

#define setpoint 20

double priError = 0;
double toError = 0;

void setup() {
  servo.attach(5);
  pinMode(4, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  PID();
  delay(50);
}

void PID() {
   
   float duration1, inches1, cm1;
   pinMode(pingPin1, OUTPUT);
   digitalWrite(pingPin1, LOW);
   delayMicroseconds(4);
   digitalWrite(pingPin1, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin1, LOW);
   pinMode(echoPin1, INPUT);
   duration1 = pulseIn(echoPin1, HIGH);
   inches1 = microsecondsToInches(duration1);
   cm1 = microsecondsToCentimeters(duration1);

   float duration2, inches2, cm2;
   pinMode(pingPin2, OUTPUT);
   digitalWrite(pingPin2, LOW);
   delayMicroseconds(4);
   digitalWrite(pingPin2, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin2, LOW);
   pinMode(echoPin2, INPUT);
   duration2 = pulseIn(echoPin2, HIGH);
   inches2 = microsecondsToInches(duration2);
   cm2 = microsecondsToCentimeters(duration2);

float error;

  if(cm1<=cm2)
  {
    error=cm1-setpoint;
  }
  else
  {
    error=40-setpoint-cm2;
  }


  
  if(error>=-1.5&&error<=1.5)
  {
    servo.write(98);
    digitalWrite(4, LOW);
    Serial.println(error/5);
    return;
  }
  Serial.println(error);
  if(error>16.0)
  {
    servo.write(8);
    return;
  }
  if(error<-16.0)
  {
    servo.write(180);
    return;
  }
  
float Pvalue = error * kp;
float Ivalue = toError * ki;
float Dvalue = (error - priError) * kd;

float PIDvalue = Pvalue + Ivalue + Dvalue;
  
priError = error;
toError += error;
int Fvalue = (int)PIDvalue;
int range = 20*(kp+5);
    
  if (Fvalue < (-1*range))
  {
     Fvalue = 180;
  }
  else if (Fvalue > range) 
  {
     Fvalue = 8;
  }
  else
  {
    Fvalue = map(Fvalue, (-1*range), range, 180, 8);
    servo.write(Fvalue);
  }
digitalWrite(4, HIGH); 
    
}


float microsecondsToInches(float microseconds) {
   return microseconds / 74 / 2;
}

float microsecondsToCentimeters(float microseconds) {
   return microseconds / 29 / 2;
}
}
