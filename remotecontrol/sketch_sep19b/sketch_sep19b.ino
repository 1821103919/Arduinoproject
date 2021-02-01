//显示图片程序
 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
 
static const unsigned char PROGMEM logo[] =
{ 
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,
    0x00,0x00,0x01,0xFF,0x83,0xC0,0x00,0x00,0x00,0x02,0x00,0x18,0x00,0x00,0x00,0x00,
    0x00,0x00,0x07,0x00,0xFC,0x40,0x00,0x00,0x00,0x03,0x00,0x18,0x00,0x00,0x00,0x00,
    0x00,0x00,0x0C,0x07,0x10,0x20,0x00,0x00,0x00,0x01,0xC0,0x00,0x01,0x80,0x00,0x00,
    0x00,0x00,0x08,0x7C,0xC0,0x30,0x00,0x00,0x00,0x00,0xC0,0x00,0x03,0x80,0x00,0x00,
    0x00,0x00,0x09,0xC0,0x60,0x10,0x00,0x00,0x00,0x00,0x00,0x78,0x07,0x00,0x00,0x00,
    0x00,0x7C,0x07,0x00,0x20,0x10,0x00,0x00,0x00,0x00,0x00,0xFE,0x0E,0x00,0x00,0x00,
    0x00,0xC7,0x9C,0x00,0x30,0x10,0x00,0x00,0x00,0x00,0x03,0xFF,0x00,0x00,0x00,0x00,
    0x01,0x80,0x70,0x00,0x10,0x10,0x00,0x00,0x00,0x00,0x07,0xFF,0x80,0x00,0x00,0x00,
    0x01,0x80,0x00,0x00,0x30,0x10,0x00,0x00,0x00,0x00,0x0F,0xFF,0xC0,0x00,0x00,0x00,
    0x00,0x80,0x00,0x00,0x60,0x1C,0x00,0x00,0x00,0x00,0x0F,0xFF,0xE0,0x00,0x00,0x00,
    0x00,0x80,0x00,0x01,0xC0,0x04,0x00,0x00,0x00,0x00,0x1F,0xFF,0xE2,0x00,0x00,0x00,
    0x00,0x80,0x00,0x07,0xFF,0xF8,0x00,0x00,0x00,0x00,0x1F,0xFF,0xE1,0xF0,0x00,0x00,
    0x00,0xC0,0x00,0x3E,0x00,0x00,0x00,0x00,0x00,0x1F,0xC7,0xFF,0xE1,0xF0,0x00,0x00,
    0x00,0x7F,0xFF,0xE0,0x0C,0x00,0x00,0x00,0x00,0x0F,0xC7,0xFF,0xE0,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x3E,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xE0,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x61,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0xE0,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x01,0x80,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x07,0x00,0x38,0x00,0x00,0x3E,0x00,0x00,0x00,0x02,0x00,0x00,0x00,
    0x00,0x00,0x00,0x0C,0x00,0x0C,0x00,0x00,0x23,0x00,0x04,0x00,0x07,0x00,0x00,0x00,
    0x00,0x00,0x00,0x18,0x00,0x04,0x00,0x00,0x41,0x00,0x0C,0x06,0x07,0x80,0x00,0x00,
    0x00,0x00,0x00,0x30,0x00,0x02,0x00,0x00,0xC0,0x80,0x1C,0x07,0x01,0xC0,0x00,0x00,
    0x00,0x00,0x00,0x60,0x00,0x03,0x00,0x01,0x80,0x60,0x78,0x07,0x00,0x60,0x00,0x00,
    0x00,0x00,0x00,0xCF,0x80,0x01,0x00,0x03,0x00,0x30,0x00,0x07,0x00,0x00,0x00,0x00,
    0x00,0x00,0x03,0xF8,0x7F,0xFF,0x80,0x06,0x00,0x18,0x00,0x07,0x00,0x00,0x00,0x00,
    0x00,0x00,0x07,0x80,0x00,0x00,0x40,0x0C,0x00,0x0C,0x00,0x06,0x00,0x00,0x00,0x00,
    0x00,0x00,0x1F,0xFF,0xFF,0xFF,0x20,0x18,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x70,0x00,0x00,0x00,0x30,0x30,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0xC0,0x00,0x00,0x00,0x18,0x43,0xFE,0x01,0xC0,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFE,0x40,0x03,0xFF,0x60,0x00,0x00,0x00,0x00,0x00,
    0x00,0x03,0x00,0x00,0x00,0x00,0x02,0x40,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,
    0x00,0x06,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,0x00,
    0x00,0x0F,0xFF,0xE0,0x00,0x00,0x00,0xC1,0xFF,0xFF,0xC6,0x00,0x00,0x00,0x00,0x00,
    0x00,0x1A,0x00,0x1F,0xFF,0xFF,0xC0,0x60,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x00,
    0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x30,0x3F,0xFF,0xE0,0xC0,0x00,0x00,0x00,0x00,
    0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,
    0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x0C,0x00,0x0F,0xFE,0x18,0x00,0x00,0x00,0x00,
    0x03,0x3F,0xFF,0xFF,0xFF,0xFF,0x80,0x06,0x7F,0xF8,0x00,0x06,0x00,0x00,0x00,0x00,
    0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,
    0x0C,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0x80,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,
    0x18,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x80,0x00,0x0F,0xFF,0x30,0x00,0x00,0x00,
    0x10,0x00,0x00,0x00,0x00,0x3F,0xFC,0x00,0xC1,0xFF,0xF0,0x00,0x08,0x00,0x00,0x00,
    0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x07,0x00,0x00,0x00,
    0x10,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x01,0x00,0x00,0x00,
    0x00,0x7F,0xFE,0x00,0x00,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
  
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
 
void setup()   {                
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.clearDisplay();
}
 
void loop() {
  display.drawBitmap(0, 0, logo, 128, 64, 1);  //在坐标X0，Y0的位置开始显示图片
                                               //128是取模软件显示的宽度
                                               //64是取模软件显示的高度
  display.display();                           //把缓存的都显示
  delay(1);
  
  display.clearDisplay();     //清除屏幕
}
 