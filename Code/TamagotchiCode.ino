#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define PIN_SCE   7
#define PIN_RESET 6
#define PIN_DC    5
#define PIN_SDIN  4
#define PIN_SCLK  3

byte count = 0;

Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_SCLK, PIN_SDIN, PIN_DC, PIN_SCE, PIN_RESET);

//小雞 Bitmap
static const unsigned char PROGMEM Chicken[] =
{
  B00000000, B10001000, B10000000,
  B00000000, B01001001, B00000000,
  B00000000, B00101010, B00000000,
  B00001111, B11111111, B11110000,
  B00010000, B00000000, B00001000,
  B00010000, B00000000, B00001000,
  B00110111, B00000000, B00001000,
  B01010111, B00000000, B00001000,
  B10010111, B00000000, B00001000,
  B01010000, B00000000, B00001000,
  B00110000, B00000000, B00001000,
  B00010000, B00000000, B00001000,
  B00010000, B00000000, B00001000,
  B00010000, B00000000, B00000111,
  B00010000, B00000000, B00000001,
  B00010000, B00000000, B00000001,
  B00010000, B00000000, B00000001,
  B00010000, B00000000, B00000001,
  B00010000, B00000000, B00000001,
  B00010000, B00000000, B00000001,
  B00010000, B00000000, B00000110,
  B00001111, B11111111, B11111000,
  B00000011, B00000000, B00110000,
  B00000011, B00000000, B00110000,
  B00000011, B00000000, B00110000
};

void setup() {

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

  //小雞
  display.drawBitmap(20, 20, Chicken, 24, 24, BLACK);

  display.display();

}

void kClear(byte x1, byte y1, byte x2, byte y2, bool color) { //x1,y1等於起始座標 x2,y2等於終點座標 color為顏色 0=白 1=黑
  if (color == 0)
    for (byte j = y1; j < y2; j++)
      for (byte i = x1; i < x2; i++)
        display.drawPixel(j, i, WHITE);
  else if (color == 1)
    for (byte j = y1; j < y2; j++)
      for (byte i = x1; i < x2; i++)
        display.drawPixel(j, i, BLACK);
}

void loop() {
  if (count == 0) { //未選擇

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

  }
  if (count == 1) { //選三角形

    //三角形，大便(反白)
    kClear(0, 0, 27 , 14, 1);
    display.drawTriangle(14, 3 , 7, 12, 21, 12, WHITE);

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


  }
  if (count == 2) { //選餅乾

    //三角形，大便
    display.drawTriangle(14, 3 , 7, 12, 21, 12, BLACK);

    //圓圈+點，吃飯(餅乾)(反白)
    kClear(29, 0, 55 , 14, 1);
    display.drawCircle(42, 7, 5, WHITE);
    display.drawPixel(42, 7, WHITE);
    display.drawPixel(40, 5, WHITE);
    display.drawPixel(40, 9, WHITE);
    display.drawPixel(44, 5, WHITE);
    display.drawPixel(44, 9, WHITE);

    //愛心
    display.drawLine(70, 5, 66, 1, BLACK); //af
    display.drawLine(66, 1, 62, 5, BLACK); //fe
    display.drawLine(62, 5, 70, 13, BLACK); //ed
    display.drawLine(70, 13, 78, 5, BLACK); //dc
    display.drawLine(78, 5, 74, 1, BLACK); //cb
    display.drawLine(74, 1, 70, 5, BLACK); //ba


  }
  if (count == 3) { //選愛心

    //三角形，大便
    display.drawTriangle(14, 3 , 7, 12, 21, 12, BLACK);

    //圓圈+點，吃飯(餅乾)
    display.drawCircle(42, 7, 5, BLACK);
    display.drawPixel(42, 7, BLACK);
    display.drawPixel(40, 5, BLACK);
    display.drawPixel(40, 9, BLACK);
    display.drawPixel(44, 5, BLACK);
    display.drawPixel(44, 9, BLACK);

    //愛心(反白)
    kClear(57, 0, 84 , 14, 1);
    display.drawLine(70, 5, 66, 1, WHITE); //af
    display.drawLine(66, 1, 62, 5, WHITE); //fe
    display.drawLine(62, 5, 70, 13, WHITE); //ed
    display.drawLine(70, 13, 78, 5, WHITE); //dc
    display.drawLine(78, 5, 74, 1, WHITE); //cb
    display.drawLine(74, 1, 70, 5, WHITE); //ba

  }
}
