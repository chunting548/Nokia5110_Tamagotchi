#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define color 0x0000
#define PIN_SCE   7
#define PIN_RESET 6
#define PIN_DC    5
#define PIN_SDIN  4
#define PIN_SCLK  3

Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_SCLK, PIN_SDIN, PIN_DC, PIN_SCE, PIN_RESET);

void setup(){
  Serial.begin(9600);

  display.begin();
  display.setContrast(50);

  display.display(); // show splashscreen
  delay(2000);
  display.clearDisplay();

  display.drawLine(0, 15, 84, 15, BLACK);
  display.drawLine(28, 0, 28, 15, BLACK);
  display.drawLine(56, 0, 56, 15, BLACK);
  display.display();

}
void loop(){

}
