#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Event.h>
#include <Timer.h> //計算時間函數

#define PIN_SCE   7
#define PIN_RESET 6
#define PIN_DC    5
#define PIN_SDIN  4
#define PIN_SCLK  3
#define buttonSelect 13
#define buttonAccept 12

Timer hungry_time;
Timer mood_time;
Timer eating_time;
byte count = 0; //UI選項選擇依據
byte xChicken = 42; //小雞x座標
byte xpac_man = 1; //小精靈之x座標
byte xpoo = 1; //poo之x座標
byte below_Screen = 0; //下畫面顯示(0-4)
byte mood_num = 8; //心情值
bool hungry = 1; //飢餓參數
bool hungry_Before = 1; 
bool clean = 1;//衛生參數 
bool clean_Before = 1;
bool mood_type = 1;
bool chickenFlag = 0;
bool select_Now = 0;
bool select_Before = 0;
bool accept_YesNow = 0;
bool accept_YesBefore = 0;
bool cookieFlag = 1;
bool acceptCtrl=1; 
bool mood_Flag=1;


Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_SCLK, PIN_SDIN, PIN_DC, PIN_SCE, PIN_RESET);

//小雞 Bitmap
static const unsigned char PROGMEM Chicken[] ={
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
static const unsigned char PROGMEM ChickenReverse[] ={
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
  B00000000, B00000000, B00000000, B00000000,
  B00000000, B00001111, B11111111, B00000000,
  B00000000, B11000000, B00000000, B11000000,
  B00000001, B00000000, B00000000, B01100000,
  B00000110, B00111000, B00000111, B10000000,
  B00011000, B00111000, B00110000, B00000000,
  B00110000, B00000000, B01100000, B00000000,
  B00110000, B00000000, B11000000, B00000000,
  B00110000, B00000000, B01110000, B00000000,
  B00110000, B00000000, B00001100, B00000000,
  B00011000, B00000000, B00000001, B11111000,
  B00000110, B00000000, B00000000, B00011000,
  B00000001, B00000000, B00000000, B01100000,
  B00000000, B11000000, B00000001, B11000000,
  B00000000, B00001111, B11111111, B00000000,
  B00000000, B00000000, B00000000, B00000000
  };
static const unsigned char PROGMEM poo[] = { 
  B00000000, B00000000, B00000000,  
  B00000000, B00000000, B00000000, 
  B11111111, B00000000, B00000000, 
  B00001011, B01000001, B10000010, 
  B00001111, B00100010, B01000100, 
  B00000000, B00010100, B00101000, 
  B11111111, B00001010, B01010000, 
  B00001011, B00010000, B00001000, 
  B00001111, B00100000, B00000100, 
  B00000000, B01000000, B00000010, 
  B11111111, B11111111, B11111111, 
  B00001011, B00000000, B00000000, 
  B00001111, B00000000, B00000000
  };
  static const unsigned char PROGMEM hungryChicken[] = { 
    B00000000, B00000000, B00000000, 
    B00000000, B00000000, B00000000, 
    B01111111, B11111111, B11000000, 
    B01000000, B00000000, B01000000, 
    B01000000, B00000000, B01000000, 
    B01000000, B00000101, B01000000, 
    B01000000, B00000010, B01000000, 
    B01000000, B00000101, B01100000, 
    B01000000, B00000000, B01010000, 
    B01000000, B00000000, B01100000, 
    B01000000, B00000000, B01001010, 
    B01000000, B00000000, B01010101, 
    B01000000, B00000000, B01000000, 
    B01111111, B11111111, B11000000, 
    B00000100, B00010000, B00000000, 
    B00000011, B10001110, B00000000
  };

  static const unsigned char PROGMEM deadChickenUp[] = { 
    B00000000, B00000000, B00000000, 
    B00000000, B00000000, B00000000, 
    B00000011, B11111111, B10000000, 
    B00000010, B00000000, B10000000, 
    B00000010, B01000100, B10000000, 
    B00000010, B11101110, B10000000, 
    B00011010, B01000100, B10110000, 
    B00100110, B00010000, B10001000, 
    B00010010, B00111000, B10010000, 
    B00001110, B00000000, B11100000, 
    B00000001, B01101101, B00000000, 
    B00000000, B10010010, B00000000, 
    B00000000, B00000000, B00000000, 
    B00000000, B00000000, B00000000
  };
  static const unsigned char PROGMEM deadChickenDown[] = { 
    B00000000, B00000000, B00000000, 
    B00000000, B00000000, B00000000, 
    B00000011, B11111111, B10000000, 
    B00000010, B00000000, B10000000, 
    B00000010, B01000100, B10000000, 
    B00000010, B11101110, B10000000, 
    B00000010, B01000100, B10000000, 
    B00001110, B00010000, B11100000, 
    B00010110, B00111000, B11010000, 
    B00101010, B00000000, B10101000, 
    B00010001, B01101101, B00010000, 
    B00000000, B10010010, B00000000, 
    B00000000, B00000000, B00000000, 
    B00000000, B00000000, B00000000
  };
  static const unsigned char PROGMEM singlePoo[] = { 
    B00000000, B00000000, B00000000, 
    B00000000, B00000000, B00000000,
    B00000000, B00010000, B00000000,
    B00000000, B00101000, B00000000,
    B00000000, B01000100, B00000000,
    B00010000, B10000010, B00010000,
    B00001001, B00000001, B00100000,
    B00000110, B00000000, B11000000,
    B00000100, B01101100, B01000000,
    B00001001, B00000001, B00100000,
    B00010000, B11111110, B00010000,
    B00100000, B00000000, B00001000,
    B01111111, B11111111, B11111100,
    B00000000, B00000000, B00000000
  };
static const unsigned char PROGMEM angry_Chicken[] ={ 
    B00000010, B00010000, B10000111, 
    B11000101, B00101001, B01011010, 
    B01011000, B11000110, B00100101, 
    B00100000, B00000000, B00000010, 
    B01011111, B11111111, B11110100, 
    B10101000, B00111000, B00010001,  
    B01001001, B00111000, B10010010, 
    B00101000, B10111001, B00010100, 
    B00011000, B00011000, B00011000, 
    B00001000, B00111100, B00010000, 
    B00001000, B00000000, B00010000, 
    B00001000, B00111000, B00010000, 
    B00001000, B00111000, B00010000,  
    B00001111, B11111111, B11110000, 
    B00000001, B00000000, B10000000, 
    B00000001, B00000000, B10000000 
};
static const unsigned char PROGMEM angry_hungry_Chicken[] ={ 
    B00000010, B00010000, B10000111, 
    B11000101, B00101001, B01011010, 
    B01011000, B11000110, B00100101, 
    B00100000, B00000000, B00000010, 
    B01011111, B11111111, B11110100, 
    B10101000, B00111000, B00010001,  
    B01001011, B10111001, B11010010, 
    B00101000, B00111001, B00010100, 
    B00011000, B00011000, B00011000, 
    B00001000, B00111100, B00010000, 
    B00001000, B00000000, B00010000, 
    B00001000, B00111000, B00010000, 
    B00001000, B00111000, B00010000,  
    B00001111, B11111111, B11110000, 
    B00000001, B00000000, B10000000, 
    B00000001, B00000000, B10000000 
};
void setup() {

  Serial.begin(9600);
  pinMode(buttonSelect,INPUT);
  pinMode(buttonAccept,INPUT);
  display.begin();
  //display.setContrast(60);
  hungry_time.after(10000,hungry_hungry);//計時10秒後開始餓
  display.display();
  delay(2000);

  display.clearDisplay();

  display.display();

}

void loop() {
  Serial.println(mood_num);
  if(mood_num!=0){
    mood_time.update();
    eating_time.update();
    hungry_time.update();

    selection();
    UI();
    uiChoice();//選擇(v)大便/吃飯/愛心
    mood();
    hungry_clean_record();

    ScreenDisplay();
  }
  else {
    deadChicken();
  }
  delay(100);
  display.display();
}

void ScreenDisplay(){
  switch(below_Screen){
      case 0 :
      if(hungry && clean){ 
         if(mood_num<=4)
            angry_Chicken_Display();
         else
            chickenMove();
      }
      else if(hungry && !clean){
         if(mood_num<=4)
            angry_Chicken_with_poo();
         else
            chickenMove_with_poo();
      }
      else if(!hungry && clean){
         if(mood_num<=4)
            angry_chicken_hungry();
         else
            chicken_hungry_hungry();
      }
      else if(!hungry && !clean){
         if(mood_num<=4)
            angry_chicken_hungry_dirty();
         else
            chicken_hungry_dirty();
      }
        break;
      case 1 :
        pooCome();
        break;
      case 2 :
        feedFood();
        break;
      case 3 :
        fill(mood_num);
        break;
    }  
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
void uiChoice(){
  accept_YesNow = digitalRead(buttonAccept);
  if(accept_YesNow == 1 && accept_YesBefore == 0 && acceptCtrl == 1){
    if(count == 0){//雞移動
      below_Screen = 0;
    }
    if(count == 1){//大便
      below_Screen = 1;
    }
    if(count == 2){//吃飯
      below_Screen = 2;
    }
    if(count == 3){//心情
      below_Screen = 3;
    }    
  }
  accept_YesNow = accept_YesBefore;
}
void feedFood(){

  kClear(0, 16, 84, 48, 0);
  if(cookieFlag == 1){
    //餅乾
    display.drawCircle(52, 32, 5, BLACK);//x,y,color
    display.drawPixel(52, 32, BLACK);
    display.drawPixel(50, 30, BLACK);
    display.drawPixel(50, 34, BLACK);
    display.drawPixel(54, 30, BLACK);
    display.drawPixel(54, 34, BLACK);
  }

    if(xpac_man > 38)
      cookieFlag = 0;//餅乾大於38時消失
    else
      cookieFlag = 1;//餅乾出現
  
    kClear(xpac_man-1, 20, xpac_man + 25, 44, WHITE);//小精靈出現前的覆蓋
  
    display.drawBitmap(xpac_man, 26, pac_man, 32, 16, BLACK);//小精靈
  
    xpac_man++;//小精靈移動
  
    if(xpac_man == 83){//小精靈動作結束
      xpac_man = 1;//回到原始位置
      acceptCtrl = 1;//又可以accept
      below_Screen = 0;//回到小雞移動
      hungry_time.after(10000, hungry_hungry);//完食計時10秒後開始餓
      eating_time.after(15000, get_poo);//完食計時15秒後開始大便
      hungry = 1;//完食 飽
    }
    else
      acceptCtrl = 0;//控制accept不能被啟動
}  

void selection(){
  
  select_Now = digitalRead(buttonSelect);
  
  /*
  以兩個變數去判斷是否按下按鈕 當Now = 1,Before = 1則進入選項內，其餘狀況則不做任何反應|| 
  需要此功能是因為Button按下後會回傳一個boolean型態，會是永久1或0
  */
  if(select_Now == 1 && select_Before == 0){
    count++;
    if(count == 4)
      count = 0;
  }
  select_Before = select_Now;
}

void pooCome(){ //大便沖水
  
  kClear(0, 16, 84, 48, 0);
  kClear(xpoo - 1, 20, xpoo + 25, 40, WHITE);
  display.drawBitmap(xpoo, 26, poo, 24, 13, BLACK);
  xpoo++;
  
  if(xpoo == 83){//poo動作結束
    xpoo = 1;//回到原始位置
    acceptCtrl = 1;//又可以accept
    below_Screen = 0;//回到小雞移動
    clean = 1;
  }
  else
    acceptCtrl = 0;//控制accept不能被啟動
}

void mood(){
  if(hungry_clean_change_key()){
    if(hungry && clean && !mood_Flag) {
      mood_time.every(10000, moodIncrease); //整潔、不餓的情況下，持續10秒後心情值+1
      mood_Flag=1;
    }
    else if( (!hungry || !clean) && mood_Flag ){
      mood_time.every(10000, moodDecrease); //反之
      mood_Flag=0;
    }
  }
}

void moodIncrease(){
  if(mood_num <= 8 )
    mood_num++;
}
void moodDecrease(){
  if(0 <= mood_num)
    mood_num--;
}
bool hungry_clean_change_key(){
  if( (hungry_Before == 0 && hungry == 1) || (hungry_Before == 1 && hungry == 0)||
      (clean_Before == 0 && clean == 1) || (clean_Before == 1 && clean == 0) )
    return 1;
  else
    return 0;
}
void hungry_clean_record(){ //記錄飢餓
  hungry_Before = hungry ;
  clean_Before = clean;
}

void hungry_hungry(){ //使變餓
  hungry = 0;
}

void chicken_hungry_hungry(){ //餓肚子雞顯示
  kClear(0, 16, 84, 48, 0);
  display.drawBitmap(30, 26, hungryChicken, 24, 16, BLACK);
}

void deadChicken(){ //死去的雞
  delay(100);
  kClear(0, 16, 84, 48, 0);
  display.drawBitmap(30, 26, deadChickenUp, 24, 14, BLACK);
  display.display();
  kClear(0, 16, 84, 48, 0);
  display.drawBitmap(30, 26, deadChickenDown, 24, 14, BLACK);
}

void rectangle(){ //圓餅圖骨架
  kClear(0, 16, 84, 48, 0); 
  display.drawRect(23, 28, 50, 9, 1);
}

void chickenMove_with_poo(){ //髒的雞
  
  display.drawBitmap(56, 30, singlePoo, 24, 14, BLACK);

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
  if(xChicken == 1)
    chickenFlag = 1;
  else if(xChicken == 59)
    chickenFlag = 0;
}

void chicken_hungry_dirty(){ //又餓又髒的雞
  kClear(0, 16, 84, 48, 0);
  display.drawBitmap(30, 26, hungryChicken, 24, 16, BLACK);
  display.drawBitmap(56, 30, singlePoo, 24, 14, BLACK);
}
void get_poo(){ //使大便
  clean = 0;
}
void angry_Chicken_Display(){ //生氣的雞
   kClear(0, 16, 84, 48, 0);
   display.drawBitmap(30, 26, angry_Chicken, 24, 16, BLACK);
}
void angry_Chicken_with_poo(){ //生氣又髒的雞
  kClear(0, 16, 84, 48, 0);
  display.drawBitmap(56, 30, singlePoo, 24, 14, BLACK);
  display.drawBitmap(30, 26, angry_Chicken, 24, 16, BLACK);
}
void angry_chicken_hungry(){ //生氣又餓的雞
  kClear(0, 16, 84, 48, 0);
  display.drawBitmap(30, 26, angry_hungry_Chicken, 24, 16, BLACK);
}
void angry_chicken_hungry_dirty(){ //生氣又餓又髒的雞
  kClear(0, 16, 84, 48, 0);
  display.drawBitmap(30, 26, angry_hungry_Chicken, 24, 16, BLACK);
  display.drawBitmap(56, 30, singlePoo, 24, 14, BLACK);
}

void fill(byte num){
    rectangle();
    display.drawLine(12, 30, 8, 26, BLACK); //af
    display.drawLine(8, 26, 4, 30, BLACK); //fe
    display.drawLine(4, 30, 12, 38, BLACK); //ed
    display.drawLine(12, 38, 20, 30, BLACK); //dc
    display.drawLine(20, 30, 16, 26, BLACK); //cb
    display.drawLine(16, 26, 12, 30, BLACK); //ba
  switch(num){
    case 8:
      display.fillRect(67, 30, 5, 5, 1);
      display.fillRect(61, 30, 5, 5, 1);
      display.fillRect(55, 30, 5, 5, 1);
      display.fillRect(49, 30, 5, 5, 1);
      display.fillRect(43, 30, 5, 5, 1);
      display.fillRect(37, 30, 5, 5, 1);
      display.fillRect(31, 30, 5, 5, 1);
      display.fillRect(25, 30, 5, 5, 1);
      break;
    case 7:
      display.fillRect(61, 30, 5, 5, 1);
      display.fillRect(55, 30, 5, 5, 1);
      display.fillRect(49, 30, 5, 5, 1);
      display.fillRect(43, 30, 5, 5, 1);
      display.fillRect(37, 30, 5, 5, 1);
      display.fillRect(31, 30, 5, 5, 1);
      display.fillRect(25, 30, 5, 5, 1);
      break;
    case 6:
      display.fillRect(55, 30, 5, 5, 1);
      display.fillRect(49, 30, 5, 5, 1);
      display.fillRect(43, 30, 5, 5, 1);
      display.fillRect(37, 30, 5, 5, 1);
      display.fillRect(31, 30, 5, 5, 1);
      display.fillRect(25, 30, 5, 5, 1);
      break;
    case 5:
      display.fillRect(49, 30, 5, 5, 1);
      display.fillRect(43, 30, 5, 5, 1);
      display.fillRect(37, 30, 5, 5, 1);
      display.fillRect(31, 30, 5, 5, 1);
      display.fillRect(25, 30, 5, 5, 1);
      break;
    case 4:
      display.fillRect(43, 30, 5, 5, 1);
      display.fillRect(37, 30, 5, 5, 1);
      display.fillRect(31, 30, 5, 5, 1);
      display.fillRect(25, 30, 5, 5, 1);
      break;
    case 3:
      display.fillRect(37, 30, 5, 5, 1);
      display.fillRect(31, 30, 5, 5, 1);
      display.fillRect(25, 30, 5, 5, 1);
      break;
    case 2:
      display.fillRect(31, 30, 5, 5, 1);
      display.fillRect(25, 30, 5, 5, 1);
      break;
    case 1:
      display.fillRect(25, 30, 5, 5, 1);
      break;
  }
}
