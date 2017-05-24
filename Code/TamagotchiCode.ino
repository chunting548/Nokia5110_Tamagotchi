#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define PIN_SCE   7
#define PIN_RESET 6
#define PIN_DC    5
#define PIN_SDIN  4
#define PIN_SCLK  3

Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_SCLK, PIN_SDIN, PIN_DC, PIN_SCE, PIN_RESET);

void setup(){
  
  Serial.begin(9600);

  display.begin();
  //display.setContrast(60);

  display.display();
  delay(2000);
  
  display.clearDisplay();

  //三個格子：
  display.drawLine(0, 15, 84, 15, BLACK);
  display.drawLine(28, 0, 28, 15, BLACK);
  display.drawLine(56, 0, 56, 15, BLACK);
  
  //三角形，大便
  display.drawTriangle(14, 3 , 7, 12, 21, 12, BLACK);
  
  //圓圈+點，吃飯(餅乾)
  display.drawCircle(42, 7, 5, BLACK);
  display.drawPixel(42, 7, BLACK);
  display.drawPixel(40, 5, BLACK);
  display.drawPixel(40, 9, BLACK);
  display.drawPixel(44, 5, BLACK);
  display.drawPixel(44, 9, BLACK);
  
  //愛心
  display.drawLine(70, 5, 66, 1, BLACK); //af
  display.drawLine(66, 1, 62, 5, BLACK); //fe
  display.drawLine(62, 5, 70, 13, BLACK); //ed
  display.drawLine(70, 13, 78, 5, BLACK); //dc
  display.drawLine(78, 5, 74, 1, BLACK); //cb
  display.drawLine(74, 1, 70, 5, BLACK); //ba
 
  display.display();

}

void loop(){

}
