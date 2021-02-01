#include <AFMotor.h>                      //L293四驱  加5路寻迹
#include <SoftwareSerial.h>                //蓝牙库

AF_DCMotor motorA(1,MOTOR12_64KHZ);   //L293四驱 四个电机运行频率
AF_DCMotor motorB(2,MOTOR12_64KHZ);
AF_DCMotor motorC(3,MOTOR34_64KHZ);
AF_DCMotor motorD(4,MOTOR34_64KHZ);
int cheSpeed;                          //小车的速度

int trac1 = 14;                           //从车头方向的最左边开始排序接红外寻迹模块
int trac2 = 15;
int trac3 = 16;
int trac4 = 17;
int trac5 = 18;
int val1;         //寻迹模块储存值
int val2;
int val3;
int val4;
int val5;
int servopin = 10;    //定义舵机接口数字接口10 也就是舵机的橙色信号线。

int bl;             //定义运行指针
int bll;
unsigned int L; //左距离存储
unsigned int R; //右距离存储
unsigned int S; //中距离存储

int trig=2; //发射信号
int echo=13; //接收信号
int speker=9; //有源喇叭接口

void setup() {
  digitalWrite(speker,HIGH);//有源喇叭拉高禁音
  Serial.begin(9600);
  pinMode(trac1, INPUT);  //寻迹模块引脚初始化
  pinMode(trac2, INPUT);
  pinMode(trac3, INPUT);
  pinMode(trac4, INPUT);
  pinMode(trac5, INPUT);
  pinMode(trig,OUTPUT); //超声波设置引脚模式
  pinMode(echo,INPUT);
  pinMode(speker,OUTPUT); //设置有源喇叭接口引脚模式
cheSpeed=80;  //小车的速度80
pinMode(servopin,OUTPUT);//设定舵机接口为输出接口
zw();//定义舵机中位
delay(500); //开机延时
bl=1;//定义运行指针值
bll=1;//定义运行指针记忆值 
              }

void loop() {
  
if(Serial.available()>0){   // 蓝牙串口有数据
              chuspeed();  // 给小车速度赋值
              lytest();    // 运行蓝牙解码判断         
              }   

if(bl==2){                     
                chuspeed(); // 给小车速度赋值
                xunji();// 运行寻迹

                }   

if(bl==3){                  
                  chuspeed();// 给小车速度赋值
                  motorun();  // 小车前进不停

                  }
if(bl==4){                  
                 chuspeed();// 给小车速度赋值
                  bz();  // 小车避障
                  }

if(bl==5){                    
                  motostop();
               digitalWrite(speker,LOW);// 喇叭响
               delay(150);
               digitalWrite(speker,HIGH);
                  if(bll==2){bl=2;}// 喇叭响完以后继续之前程序指针
                  else if(bll==3){bl=3;}
                  else if(bll==4){bl=4;}
                  else {
                        bll=1;
                        bl=1;}
                  }  



else{ motostop();}  

}


void servopulse(int angle)//定义一个脉冲函数   舵机函数
{
  int pulsewidth=(angle*11)+500;  //将角度转化为500-2480的脉宽值
  digitalWrite(servopin,HIGH);    //将舵机接口电平至高
  delayMicroseconds(pulsewidth);  //延时脉宽值的微秒数
  digitalWrite(servopin,LOW);     //将舵机接口电平至低
  delayMicroseconds(20000-pulsewidth);
}

void chuspeed(void){                  // 定义小车初始速度
motorA.setSpeed(cheSpeed);   
motorB.setSpeed(cheSpeed);
motorC.setSpeed(cheSpeed);   
motorD.setSpeed(cheSpeed);   
                 }

void motostop(void){              // 定义小车停止  
              motorA.run(RELEASE);
              motorB.run(RELEASE);
              motorC.run(RELEASE);
              motorD.run(RELEASE);
              }

void motorun(void){              // 定义小车前进  
              motorA.run(FORWARD);
              motorB.run(FORWARD);
              motorC.run(FORWARD);
              motorD.run(FORWARD);}

void motodown(void){              // 定义小车后退
              motorA.run(BACKWARD);
              motorB.run(BACKWARD);
              motorC.run(BACKWARD);
              motorD.run(BACKWARD);}

void motoleft(void){              // 定义小车原地左拐
              motorA.run(BACKWARD);
              motorB.run(FORWARD);
              motorC.run(BACKWARD);
              motorD.run(FORWARD);}

void motoright(void){              // 定义小车原地右拐
              motorA.run(FORWARD);
              motorB.run(BACKWARD);
              motorC.run(FORWARD);
              motorD.run(BACKWARD);}

void motorle(void){              // 定义小车左拐
              motorA.run(RELEASE);
              motorB.run(FORWARD);
              motorC.run(RELEASE);
              motorD.run(FORWARD);}

void motorri(void){              // 定义小车右拐
              motorB.run(RELEASE);
              motorA.run(FORWARD);
              motorD.run(RELEASE);
              motorC.run(FORWARD);}              

void lytest(){                     // 定义蓝牙串口解码判断
         int cmd = Serial.read();//读取蓝牙模块发送到串口的数据         

          if(cmd==49){   // 手机蓝牙输出1，对应ascii数是49
           Serial.println("FORWARD"); //输出状态
              motostop();  
              delay(100);
              motorun();
              delay(400);
                     }

          if(cmd==50){  // 手机蓝牙输出2，对应ascii数是50，后面以此类推即加48
          Serial.println("BACKWARD"); //输出状态
              motostop();              
              delay(100);
              motodown();
              delay(400);
                       }

               if(cmd==51){   
                 Serial.println("STOP"); //输出状态
              motostop();
              bl=1;
              bll=1;            
              delay(100);              
                         }

                if(cmd==52){   
              Serial.println("left"); //输出状态
              motostop();               
              delay(100);
              motoleft();
              delay(400);            
                       }
                  if(cmd==53){   
              Serial.println("Right"); //输出状态
              motostop();            
              delay(100);
              motoright();
              delay(400);            
                  }
                 if(cmd==54){
                 cheSpeed+=5;
                 if(cheSpeed>255){cheSpeed=255; } //不超过255最高值
                 Serial.print("cheSpeed=");
                 Serial.println(cheSpeed);
                         }
                   if(cmd==55){
              cheSpeed-=5;
               if(cheSpeed<0){cheSpeed=0;}//不低于0
              Serial.print("cheSpeed=");
              Serial.println(cheSpeed);
                               }

                   if(cmd==56){ //指针寻迹
                   bl=2;
                   bll=2;
                   Serial.println("xunji"); }                       

                  if(cmd==57){  //指针一直进      
                  bl=3;
                  bll=3;
                  Serial.println("go line");  }                     

                 if(cmd==97){//按健a，对应ASCII码是97 指针避障
                 bl=4;
                 bll=4;
                 Serial.println("bizhang");}            

                 if(cmd==98){ //按健b，对应ASCII码是98  指针喇叭
                      bl=5;

                    Serial.println("tonee"); }
}   

void xunji(){         //寻迹主函数     
val1 = digitalRead(trac1);
val2 = digitalRead(trac2); //寻迹模块返回值
val3 = digitalRead(trac3);
val4 = digitalRead(trac4);
val5 = digitalRead(trac5);

if(val1==1 && val2==1 && val3==0  && val4==1 && val5==1  )  //11011中间黑线,即0为黑线
{
motostop();
motorun();
delay(20);
}

else if(val1==1 && val2==0 && val3==0  && val4==0 && val5==1  )  //10001中间三黑线，十字路
{
motostop();
motorun();
delay(20);
}

else if(val1==0 && val2==0 && val3==0  && val4==0 && val5==0  )  //00000都检测到黑线
{
Serial.println("stop");
motostop();
delay(50);
}

else if(val1==1 && val2==1 && val3==1  && val4==1 && val5==1  )  //11111都无检测到黑线
{
Serial.println("go...");
motostop();
motorun();
delay(20);
}

else if(val1==1 && val2==0 && val3==0  && val4==1 && val5==1  )  //10011
{  
motostop();
delay(20);
Serial.println("go left");
motoleft();
delay(50);
}

else if(val1==0 && val2==1 && val3==0  && val4==1 && val5==1  )  //01011
{
motostop();
delay(20);
Serial.println("go left");
motoleft();
delay(100);
}

else if(val1==1 && val2==0 && val3==1  && val4==1 && val5==1  )  //10111
{
motostop();
delay(20);
Serial.println("go left");
motoleft();
delay(50);
}

else if(val1==0 && val2==0 && val3==1  && val4==1 && val5==1  )  //00111
{
motostop();
delay(20);
Serial.println("go left");
motoleft();
delay(100);
}

else if(val1==0 && val2==0 && val3==0  && val4==1 && val5==1  )  //00011
{
motostop();
delay(20);
Serial.println("go left");
motoleft();
delay(400);
}


else if(val1==0 && val2==1 && val3==1  && val4==1 && val5==1  )  //01111
{
motostop();
delay(20);
Serial.println("go left");
motoleft();
delay(150);
}

else if(val1==1 && val2==1 && val3==0  && val4==0 && val5==1  )  //11001
{
motostop();
delay(20);
Serial.println("go right");
motoright();
delay(50);
}

else if(val1==1 && val2==1 && val3==0  && val4==1 && val5==0  )  //11010
{
motostop();
delay(20);
Serial.println("go right");
motoright();
delay(50);
}

else if(val1==1 && val2==1 && val3==1  && val4==0 && val5==1  )  //11101
{
motostop();
delay(20);
Serial.println("go right");
motoright();
delay(50);
}

else if(val1==1 && val2==1 && val3==1  && val4==0 && val5==0  )  //11100
{
motostop();
delay(20);
Serial.println("go right");
motoright();
delay(100);
}

else if(val1==1 && val2==1 && val3==0  && val4==0 && val5==0  )  //11000
{
motostop();
delay(20);
Serial.println("go right");
motoright();
delay(400);
}

else if(val1==1 && val2==1 && val3==1  && val4==1 && val5==0  )  //11110
{
motostop();
delay(20);
Serial.println("go right");
//motorri();
motoright();
delay(150);
}

else if(val1==1 && val2==0 && val3==1  && val4==0 && val5==1  )  //10101
{
motostop();
delay(20);
Serial.println("go right");
motoright();
delay(20);
}

else{
   motostop();
   // Serial.println("else go");
   motostop();
   delay(20);
  }

  }

void range(){ //定义中间测距函数
digitalWrite(trig,LOW); //测距
delayMicroseconds(2); //延时2微秒
digitalWrite(trig,HIGH);
delayMicroseconds(20);
digitalWrite(trig,LOW);
int distance = pulseIn(echo,HIGH); //读取高电平时间
distance = distance/58; //按照公式计算
S = distance; //把值赋给S
}

void rangel(){ //定义左边测距函数
digitalWrite(trig,LOW); //测距
delayMicroseconds(2); //延时2微秒
digitalWrite(trig,HIGH);
delayMicroseconds(20);
digitalWrite(trig,LOW);
int distance = pulseIn(echo,HIGH); //读取高电平时间
distance = distance/58; //按照公式计算
L = distance; //把值赋给L
}

void ranger(){ //定义右边测距函数
digitalWrite(trig,LOW); //测距
delayMicroseconds(2); //延时2微秒
digitalWrite(trig,HIGH);
delayMicroseconds(20);
digitalWrite(trig,LOW);
int distance = pulseIn(echo,HIGH); //读取高电平时间
distance = distance/58; //按照公式计算
R = distance; //把值赋给R
}

void turn(){      //左右探测距离函数
  motostop();
  delay(500);
    lw();     //舵机转到150度既左边（角度与安装方式有关）
   delay(800);     //留时间给舵机转向
   rangel();//左边测距值为L

   zw();    //测距完成，舵机回到中位
   delay(800);   //留时间给舵机转向
   range();//中间测距值为S

     rw(); //舵机转动到30度，测右边距离
    delay(800);//留时间给舵机转向
    ranger();   //右边测距值为R

    zw(); //回中位
     delay(800);//留时间给舵机转向
     }  

void zw(){   //舵机中
   for(int i=0;i<50;i++)  //发送50个脉冲
        {
          servopulse(90);   //引用脉冲函数  舵机位置中
         }   
   }

void lw(){  //舵机150度角
   for(int i=0;i<50;i++)  //发送50个脉冲
        {
          servopulse(150);   //引用脉冲函数 舵机150度角
         }   
   }

void rw(){   //舵机30度角
   for(int i=0;i<50;i++)  //发送50个脉冲
        {
          servopulse(30);   //引用脉冲函数 舵机30度角
         }   
  }

void bz(){//避障主程序
     motostop();              
     delay(20);
   range();     //先对中间测距值为S
  if (S>60){   // 如果S大于60cm
     motostop();              
     delay(20);
     Serial.println("run"); //输出状态
     motorun();//前进
     delay(80);   
    }

  else if(S<30){  // 如果S小于30cm
              Serial.println("BACKWARD"); //输出状态
              motostop();              
              delay(200);
              motodown();//后退
              delay(200);
    }

  else{   // 即S小于60cm,大于30cm     
     Serial.println("turn"); //输出状态
    turn();                      //调出左右探测距离函数，判断左右距离值
    Serial.print("L="); //输出状态
   Serial.print(L); //输出状态
    Serial.print("--"); //输出状态
    Serial.print("R="); //输出状态
   Serial.print(R); //输出状态
   Serial.println(); //输出状态

             if((L>R) && (L>S)){//左边比前方和右方距离大
              Serial.println("GO LEFT"); //输出状态
              motostop();               
              delay(100);
              motoleft();//左转
              delay(300);      
                    }
             else if ((R>L) && (R>S)){//右边比前方和左方距离大
              Serial.println("GO RIGHT"); //输出状态
              motostop();               
              delay(100);
              motoright();//右转
              delay(300);
               }

              else if ((L>R) && (L<S)){   //左边比右方距离大，但是小于前方
              Serial.println("GO RIGHT"); //输出状态
              motostop();               
              delay(100);
              motoleft();   //从左边大转弯，相当于从左边调头
              delay(600);
               }

              else if ((R>L) && (R<S)){   //右边比左方距离大，但是小于前方
              Serial.println("GO RIGHT"); //输出状态
              motostop();               
              delay(100);
              motoright();//从右边大转弯，相当于从右边调头
              delay(600);
               }


             else{ motodown();
              delay(100);    }      
    }
   }
