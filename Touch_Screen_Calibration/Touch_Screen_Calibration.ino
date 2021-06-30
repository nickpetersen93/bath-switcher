#include <Adafruit_GFX.h>    
#include <SPI.h>
#include <Wire.h>      
#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>

extern uint8_t LOGO[];



// The STMPE610 uses hardware SPI on the shield, and #8
#define STMPE_CS 8
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

// The display also uses hardware SPI, plus #9 & #10
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


void setup() {
  
  Serial.begin(9600);
  tft.begin();

  if (!ts.begin()) {
    Serial.println("Couldn't start touchscreen controller");
    while (1);
  }
  
  Serial.println("Touchscreen started");

  //Welcome Screen
  WelcomeScreen();
  delay(1000);
  
 
}


void loop() {

//Screen is 240x320 pixels
//draw a red rectangle in each corner
tft.fillRect(0, 0, 10, 10 ,0xF800);
tft.fillRect(230, 310, 10, 10 ,0xF800);
tft.fillRect(230, 0, 10, 10 ,0xF800);
tft.fillRect(0, 310, 10, 10 ,0xF800);

  tft.setFont(&FreeSans12pt7b);
  tft.setTextColor(0xF800);
  tft.setCursor(25, 78);
  tft.print("Tap each corner &");
  tft.setCursor(30, 100);
  tft.print("record the values");
  tft.setCursor(25, 122);
  tft.print("from Serial Monitor");


  if (ts.touched()) {
      TS_Point p = ts.getPoint();
      
      while (!ts.bufferEmpty() && p.y>10) {  p = ts.getPoint(); }

      // serial monitor will show when and where touched
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);  
    
    
//      Serial.print("("); Serial.print(p.x);
//      Serial.print(", "); Serial.print(p.y);
//      Serial.println(")");
  }
}
      
void WelcomeScreen() {
  tft.setRotation(0);
  tft.fillScreen(ILI9341_BLACK);
  drawBitmap(10,130,LOGO,220,68,ILI9341_WHITE);
}




void drawBitmap(int16_t x, int16_t y,const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {
  int16_t i, j, byteWidth = (w + 7) / 8;
  uint8_t byte;
  for(j=0; j<h; j++) {
    for(i=0; i<w; i++) {
      if(i & 7) byte <<= 1;
      else      byte   = pgm_read_byte(bitmap + j * byteWidth + i / 8);
      if(byte & 0x80) tft.drawPixel(x+i, y+j, color);
    }
  }
}
