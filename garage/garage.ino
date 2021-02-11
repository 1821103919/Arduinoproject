/*车库程序*/
#include <Servo.h>
#define Triq 5
#define Echo 4
#define Triqb 2
#define Echob 3
float distance;
float distanceb;
Servo myservo;
int i=0;

void setup()
{
  pinMode(Triq, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(Triqb, OUTPUT);
  pinMode(Echob, INPUT);
  
  Serial.begin(9600);
  myservo.attach(9);
}

void loop()
{
  digitalWrite(Triq, LOW);
  delayMicroseconds(2);
  digitalWrite(Triq, HIGH);
  delayMicroseconds(10);
  digitalWrite(Triqb, LOW);
  delayMicroseconds(2);
  digitalWrite(Triqb, HIGH);
  delayMicroseconds(10);
  
  distance=pulseIn(Echo, HIGH);
  distance=distance * 0.018;
  distanceb=pulseIn(Echob, HIGH);
  distanceb=distanceb * 0.018;

  if(distance<20||distanceb<20)
   {
    myservo.write(180);
    delay(4000);
    int i=0;
   }
  else
  {
    myservo.write(90);
    for(i=0;i<1;i++)
    delay(200);
  }
}
