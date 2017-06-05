#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define PIN_SCE   7
#define PIN_RESET 6
#define PIN_DC    5
#define PIN_SDIN  4
#define PIN_SCLK  3
#define buttonSelect 13
#define buttonAccept 12

byte count = 0;
byte xChicken = 42;
byte xpac_man = 0;
byte below_Screen = 0;
bool chickenFlag = 0;
bool select_Now = 0;
bool select_Before = 0;
bool accept_YesNow = 0;
bool accept_YesBefor = 0;
bool cookieFlag = 1;


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
static const unsigned char PROGMEM ChickenReverse[] =
{
  B00000001 ,B00010001 ,B00000000,
  B00000000 ,B10010010 ,B00000000,
  B00000000 ,B01010100 ,B00000000,
  B00001111 ,B11111111 ,B11110000,
  B00010000 ,B00000000 ,B00001000,
  B00010000 ,B00000000 ,B00001000,
  B00010000 ,B00000000 ,B11101100,
  B00010000 ,B00000000 ,B11101010,
  B00010000 ,B00000000 ,B11101001,
  B00010000 ,B00000000 ,B00001010,
  B00010000 ,B00000000 ,B00001100,
  B00010000 ,B00000000 ,B00001000,
  B00010000 ,B00000000 ,B00001000,
  B11100000 ,B00000000 ,B00001000,
  B10000000 ,B00000000 ,B00001000,
  B10000000 ,B00000000 ,B00001000,
  B10000000 ,B00000000 ,B00001000,
  B10000000 ,B00000000 ,B00001000,
  B10000000 ,B00000000 ,B00001000,
  B10000000 ,B00000000 ,B00001000,
  B01100000 ,B00000000 ,B00001000,
  B00011111 ,B11111111 ,B11110000,
  B00001100 ,B00000000 ,B11000000,
  B00001100 ,B00000000 ,B11000000,
  B00001100 ,B00000000 ,B11000000
};
static const unsigned char PROGMEM pac_man[] = { //精靈
    B00000000, B00000000, B00000000,
    B00000111, B01111111, B11100000, 
    B00110000, B00000000, B00011000, 
    B11000000, B11000000, B00000110,
    B11000000, B11000000, B00110000, 
    B11000000, B00000000, B11000000,
    B11000000, B00000011, B00000000,
    B11000000, B00000000, B11000000,
    B11000000, B00000000, B00110000, 
    B00110000, B00000000, B00011000,
    B00000110, B00000000, B00110000,
    B00000001, B11111111, B10000000,
    B00000000, B00000000, B00000000
  };
void setup() {

  Serial.begin(9600);
  pinMode(buttonSelect,INPUT);
  pinMode(buttonAccept,INPUT);
  display.begin();
  //display.setContrast(60);

  display.display();
  delay(2000);

  display.clearDisplay();

  display.display();

}



void loop() {
  select_Now=digitalRead(buttonSelect);  //以兩個變數去判斷是否按下按鈕 當Now=1,Before=1則進入選項內，其餘狀況則不做任何反映    ||   需要此功能是因為Button按下後會回傳一個bool型態，會是永久1或0
  if(select_Now==1 && select_Before==0){
    count++;
    if(count==4)
      count=0;
  }
  select_Before=select_Now;
  
  UI();
  uiChoise();//選擇(v)大便/吃飯/愛心
  
  switch(below_Screen){
    case 0 : 
      chickenMove();//雞放UI後雞才不會不見
      break;
    case 1 :
      break;
    case 2 :
      feedFood();
      break;
    case 3 :
      break;
  }  
    delay(100);
  display.display();

}

void chickenMove(){
  kClear(xChicken-1, 20, xChicken + 25, 44, WHITE);
  //小雞
  
  if (chickenFlag){ //倒走
    display.drawBitmap(xChicken, 20, ChickenReverse, 24, 24, BLACK);
    xChicken++;
  }
  else{             //正走
    display.drawBitmap(xChicken, 20, Chicken, 24, 24, BLACK);
    xChicken--;
  }
  if(xChicken==1)
    chickenFlag=1;
  else if(xChicken==59)
    chickenFlag=0;
}

void UI(){
  
  if (count == 0) { //未選擇
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

  }
  else if (count == 1) { //選三角形
    display.clearDisplay();
    display.drawLine(0, 15, 84, 15, BLACK);
    display.drawLine(28, 0, 28, 15, BLACK);
    display.drawLine(56, 0, 56, 15, BLACK);
    //三角形，大便(反白)
    kClear(0, 0, 28 , 15, 1);
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
  else if (count == 2) { //選餅乾
    display.clearDisplay();
    display.drawLine(0, 15, 84, 15, BLACK);
    display.drawLine(28, 0, 28, 15, BLACK);
    display.drawLine(56, 0, 56, 15, BLACK);
    //三角形，大便
    display.drawTriangle(14, 3 , 7, 12, 21, 12, BLACK);

    //圓圈+點，吃飯(餅乾)(反白)
    kClear(28, 0, 56 , 15, 1);
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
  else if (count == 3) { //選愛心
    display.clearDisplay();
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

void kClear(byte x1, byte y1, byte x2, byte y2, bool color) { //x1,y1等於起始座標 x2,y2等於終點座標 color為顏色 0=白 1=黑
  if (color == 0)
    for (byte j = y1; j < y2; j++)
      for (byte i = x1; i < x2; i++)
        display.drawPixel(i, j, WHITE);
  else if (color == 1)
    for (byte j = y1; j < y2; j++)
      for (byte i = x1; i < x2; i++)
        display.drawPixel(i, j, BLACK);
}
void uiChoise(){
  accept_YesNow=digitalRead(buttonAccept);
  if(accept_YesNow == 1 && accept_YesBefor == 0){
    if(count == 1){//大便
      below_Screen=1;
    }
    if(count == 2){//吃飯
      below_Screen=2;
    }
    if(count == 3){//心情
      below_Screen=3;
    }
    accept_YesNow=accept_YesBefor;
  }
}
void  feedFood(){
  kClear(0,16,84,48,0);
  if(cookieFlag==1){
    //餅乾
    display.drawCircle(52, 32, 5, BLACK);
    display.drawPixel(52, 32, BLACK);//x,y,colour
    display.drawPixel(50, 30, BLACK);
    display.drawPixel(50, 34, BLACK);
    display.drawPixel(54, 30, BLACK);
    display.drawPixel(54, 34, BLACK);
  }
    if(xpac_man=52)
      cookieFlag=0;
    kClear(xpac_man-1, 20, xpac_man + 25, 44, WHITE);
    display.drawBitmap(xpac_man, 20, pac_man, 24, 24, BLACK);
    xpac_man++;
    if(xpac_man==84)
      below_Screen=0;
}
