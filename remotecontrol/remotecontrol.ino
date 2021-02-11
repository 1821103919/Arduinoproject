/*遥控器程序*/
#define X analogRead(0)
#define Y analogRead(1)
#define A digitalRead(2)
#define B digitalRead(3)
#define C digitalRead(4)
#define D digitalRead(5)
#define E digitalRead(6)
#define F digitalRead(7)
#define K digitalRead(8)
#define DELAY 250
#define STOP 300

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if(Y>511)              //前后操作
  {
    Serial.println("1");
    delay(STOP);
  }
  else if(Y<491)
  {
    Serial.println("2");
    delay(STOP);
  }

  if(X>524)              //左右操作
  {
    Serial.println("5");
    delay(STOP);
  }
  else if(X<504)
  {
    Serial.println("4");
    delay(STOP);
  }
  
  if (A == LOW)          //加速操作
  {
    Serial.println("6");
    delay(DELAY);
  }

  if (B == LOW)          //避障
  {
    Serial.println("a");
    delay(DELAY);
  }

  if (C == LOW)         //减速操作
  {
    Serial.println("7");
    delay(DELAY);
  }

  if (D == LOW)         //寻迹
  {
    Serial.println("8");
    delay(DELAY);
  }

  if (E == LOW)         //一直前进
  {
    Serial.println("9");
    delay(DELAY);
  }

  if (F == LOW)         //喇叭
  {
    Serial.println("b");
    delay(DELAY);
  }

  if (K == LOW)         //停止
  {
    Serial.println("3");
  }
}
