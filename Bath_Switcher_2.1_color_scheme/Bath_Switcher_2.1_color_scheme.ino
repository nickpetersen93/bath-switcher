#include <Adafruit_GFX.h>    
#include <SPI.h>
#include <Wire.h>      
#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>
#include <Servo.h> 
#include <math.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>

extern uint8_t LOGO[];

int servoPin = 44;
int servotwoPin = 45;
int servothreePin = 46;
Servo servo;
Servo servotwo;
Servo servothree;

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 288
#define TS_MINY 195
#define TS_MAXX 3756
#define TS_MAXY 3711

// The STMPE610 uses hardware SPI on the shield, and #8
#define STMPE_CS 8
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

// The display also uses hardware SPI, plus #9 & #10
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

unsigned long TTB_drug1 = 63000;   //time to bath from drug 1 in milliseconds
unsigned long TTB_drug2 = 64000;   //time to bath from drug 2 in milliseconds
unsigned long TTB_drug3 = 65000;   //time to bath from drug 3 in milliseconds
unsigned long TTB_aCSF = 66000;    //time to bath from drug aCSF in milliseconds
unsigned long prime_delay = 20000; //time in milliseconds to prime each tube with "PRIME ALL" function

unsigned long min5 = 300000; // do not change
unsigned long min10 = 600000; // do not change


unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
const long interval = 1000;


//uncomment below to debug (shorter wait times)
/*unsigned long TTB_drug1 = 1000;   //time to bath from drug 1 in milliseconds
unsigned long TTB_drug2 = 1020;
unsigned long TTB_drug3 = 1155;//time to bath from drug 1+2 in milliseconds
unsigned long TTB_aCSF = 1035;   //time to bath from drug aCSF in milliseconds
unsigned long min5 = 3000;
unsigned long min10 = 6000;
unsigned long prime_delay = 25000;
*/
unsigned long time_now = 0;
unsigned long start_time = 0;
int minutes = 00;
int seconds = 00;

int SelectColor = 1;


uint16_t color1 = 0;
uint16_t color2 = 0;
uint16_t color3 = 0;
uint16_t color4 = 0;
uint16_t color5 = 0;
uint16_t color6 = 0;
uint16_t color7 = 0;
uint16_t color8 = 0;
uint16_t color9 = 0;
uint16_t color10 = 0;
uint16_t textcolor1 = 0;
uint16_t textcolor2 = 0;
uint16_t textcolor3 = 0;
uint16_t textcolor4 = 0;
uint16_t textcolor5 = 0;
uint16_t textcolor6 = 0;
uint16_t textcolor7 = 0;
uint16_t textcolor8 = 0;
uint16_t textcolor9 = 0;
uint16_t textcolor10 = 0;




#define RED 0xF800         ///< 255,   0,   0
#define PASTELRED 0xFEBA
#define MAROON 0x7800      ///< 123,   0,   0
#define ORANGE 0xFD20      ///< 255, 165,   0
#define YELLOW 0xFFE0      ///< 255, 255,   0
#define GOLD 0xFE89
#define PASTELYELLOW 0xFFF9
#define GREENYELLOW 0xAFE5 ///< 173, 255,  41
#define GREEN 0x07E0       ///<   0, 255,   0
#define PASTELGREEN 0xCFFB
#define DARKGREEN 0x03E0   ///<   0, 125,   0
#define OLIVE 0x7BE0       ///< 123, 125,   0
#define BLUE 0x001F        ///<   0,   0, 255
#define PASTELBLUE 0xB69F
#define NAVY 0x000F        ///<   0,   0, 123
#define CYAN 0x07FF        ///<   0, 255, 255
#define PASTELCYAN 0xD7FF
#define DARKCYAN 0x03EF    ///<   0, 125, 123
#define PASTELPINK 0xF67B
#define PURPLE 0x780F      ///< 123,   0, 123
#define MAGENTA 0xF81F     ///< 255,   0, 255
#define PINK 0xFC18        ///< 255, 130, 198
#define LIGHTGREY 0xC618   ///< 198, 195, 198
#define DARKGREY 0x7BEF    ///< 123, 125, 123
#define BLACK 0x0000       ///<   0,   0,   0
#define WHITE 0xFFFF       ///< 255, 255, 255
#define SALMON 0xFAC9
#define INDIGO 0xCAD9
#define DarkGold  0x8080
#define LightGold 0xFEDB
#define DarkTeal 0x02BA
#define LightTeal 0xCF9F
#define DarkPlum 0x60AF
#define LightPlum 0xF65F


void setup() {
  
  Serial.begin(9600);
  tft.begin();

  if (!ts.begin()) {
    Serial.println("Couldn't start touchscreen controller");
    while (1);
  }
  
  Serial.println("Touchscreen started");

  // set servos to default position 
  aCSF();

  //Welcome Screen
  WelcomeScreen();
  delay(5000);

 

  //Color scheme selection screen
  Color_Scheme_Menu();
  
  //Home Screen
  //HomeScreen();
  




}


void loop() {


  
  if (ts.touched()) {
      TS_Point p = ts.getPoint();
      
      while (!ts.bufferEmpty() && p.y>10) {  p = ts.getPoint(); }

      // serial monitor will show when and where touched
      Serial.print("X = "); Serial.print(p.x);
      Serial.print("\tY = "); Serial.print(p.y);
      Serial.print("\tPressure = "); Serial.println(p.z);  
    
     
      // Scale from ~0->4000 to tft.width using the calibration #'s
      p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
      p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
    
    
      Serial.print("("); Serial.print(p.x);
      Serial.print(", "); Serial.print(p.y);
      Serial.println(")");

        if (SelectColor == 1){
          Color_Scheme_Select();
        }

    boolean buttonEnabled = true;
    minutes = 00;

// PRIME ALL BUTTON
    if(p.x>0 && p.x<240 && p.y>220 && p.y<260 && p.z>50 && buttonEnabled){
        tft.drawRoundRect(0, 220, 240, 40, 4, ILI9341_GREEN);
        buttonEnabled = false;
        start_time = millis();
        time_now = millis();
        Drug1();
        tft.fillScreen(color9);
        tft.setFont(&FreeSans18pt7b);
        tft.setTextColor(textcolor9);
        tft.setTextSize(1);
     
        while(millis() < time_now + prime_delay) {
              tft.setCursor(60,40);
              tft.print("Priming\n       Drug 1...");
              NickTime(textcolor9, color9);
              
            }
            
        time_now = millis();
        Drug2();
           
        while(millis() < time_now + prime_delay) {
              tft.setCursor(60,40);
              tft.print("Priming\n       Drug 1...\n       Drug 2...");
              NickTime(textcolor9, color9);
            }

        time_now = millis();
        Drug3();

        while(millis() < time_now + prime_delay) {
              tft.setCursor(60,40);
              tft.print("Priming\n       Drug 1...\n       Drug 2...\n       Drug 3...");
              NickTime(textcolor9, color9);
            }

        time_now = millis();
        aCSF();

        while(millis() < time_now + prime_delay) {
              tft.setCursor(60,40);
              tft.print("Priming\n       Drug 1...\n       Drug 2...\n       Drug 3...\n        aCSF...");
              NickTime(textcolor9, color9);
            }

        tft.fillScreen(color9);
        tft.setCursor(60,40);
        tft.print("Priming\n        Done!");
        delay(2000);
        HomeScreen();
        TS_Point p = ts.getPoint();
        
   } //END PRIME ALL BUTTON

//5 MIN BLOCK - aCSF>Drug 1>aCSF
    if(p.x>0 && p.x<120 && p.y>40 && p.y<100 && buttonEnabled){
        tft.drawRoundRect(0, 40, 120, 60, 4, ILI9341_GREEN);
        buttonEnabled = false;
        start_time = millis();
        time_now = millis();
        aCSF();
        tft.fillScreen(color3);
        tft.setFont(&FreeSans18pt7b);
        tft.setTextColor(textcolor3);
        tft.setTextSize(1);   
         
        while(millis() < time_now + min5 - TTB_drug1) {
              tft.setCursor(60,40);
              tft.print("5 - 5 - 5\n       aCSF...");
              NickTime(textcolor3, color3);
            }
            
        time_now = millis();
        Drug1();
           
        while(millis() < time_now + min5 + TTB_drug1 - TTB_aCSF) {
              tft.setCursor(60,40);
              tft.print("5 - 5 - 5\n       aCSF...\n       Drug 1...");
              NickTime(textcolor3, color3);
            }

        time_now = millis();
        aCSF();

        while(millis() < time_now + min5 + TTB_aCSF) {
              tft.setCursor(60,40);
              tft.print("5 - 5 - 5\n       aCSF...\n       Drug 1...\n       aCSF...");
              NickTime(textcolor3, color3);
            }

        tft.fillScreen(color3);
        tft.setCursor(60,40);
        tft.print("5 - 5 - 5\n        Done!");
        delay(2000);
        HomeScreen();
        TS_Point p = ts.getPoint();
        
   } //END 5 MIN BLOCK - aCSF>Drug 1>aCSF

//5 MIN BLOCK - aCSF>Drug 1>Drug 2>aCSF
    if(p.x>0 && p.x<120 && p.y>100 && p.y<160 && buttonEnabled){
        tft.drawRoundRect(0, 100, 120, 60, 4, ILI9341_GREEN);
        buttonEnabled = false;
        start_time = millis();
        time_now = millis();
        aCSF();
        tft.fillScreen(color5);
        tft.setFont(&FreeSans18pt7b);
        tft.setTextColor(textcolor5);
        tft.setTextSize(1);
        
        while(millis() < time_now + min5 - TTB_drug1) {
              tft.setCursor(35,40);
              tft.print("5 - 5 - 5 - 5\n       aCSF...");
              NickTime(textcolor5, color5);
            }
            
        time_now = millis();
        Drug1();
        
           
        while(millis() < time_now + min5 + TTB_drug1 - TTB_drug2) {
              tft.setCursor(35,40);
              tft.print("5 - 5 - 5 - 5\n       aCSF...\n       Drug 1...");
              NickTime(textcolor5, color5);
            }

        time_now = millis();
        Drug2();
   

        while(millis() < time_now + min5 + TTB_drug2 - TTB_aCSF) {
              tft.setCursor(35,40);
              tft.print("5 - 5 - 5 - 5\n       aCSF...\n       Drug 1...\n       Drug 2...");
              NickTime(textcolor5, color5);
            }
            
        time_now = millis();
        aCSF();
        
        while(millis() < time_now + min5 + TTB_aCSF) {
              tft.setCursor(35,40);
              tft.print("5 - 5 - 5 - 5\n       aCSF...\n       Drug 1...\n       Drug 2...\n       aCSF...");
              NickTime(textcolor5, color5);
            }

        tft.fillScreen(color5);
        tft.setCursor(35,40);
        tft.print("5 - 5 - 5 - 5\n        Done!");
        delay(2000);
        HomeScreen();
        TS_Point p = ts.getPoint();
        
   } //END 5 MIN BLOCK - aCSF>Drug 1>Drug 2>aCSF
 
//5 MIN BLOCK - aCSF>Drug 1>Drug 2>Drug 3>aCSF
    if(p.x>0 && p.x<120 && p.y>160 && p.y<220 && buttonEnabled){
        tft.drawRoundRect(0, 160, 120, 60, 4, ILI9341_GREEN);
        buttonEnabled = false;
        start_time = millis();
        time_now = millis();
        aCSF();
        tft.fillScreen(color7);
        tft.setFont(&FreeSans18pt7b);
        tft.setTextColor(textcolor7);
        tft.setTextSize(1);
        
        while(millis() < time_now + min5 - TTB_drug1) {
              tft.setCursor(10,40);
              tft.print("5 - 5 - 5 - 5 - 5\n       aCSF...");
              NickTime(textcolor7, color7);
            }
            
        time_now = millis();
        Drug1();
        
           
        while(millis() < time_now + min5 + TTB_drug1 - TTB_drug2) {
              tft.setCursor(10,40);
              tft.print("5 - 5 - 5 - 5 - 5\n       aCSF...\n       Drug 1...");
              NickTime(textcolor7, color7);
            }

        time_now = millis();
        Drug2();
   

        while(millis() < time_now + min5 + TTB_drug2 - TTB_drug3) {
              tft.setCursor(10,40);
              tft.print("5 - 5 - 5 - 5 - 5\n       aCSF...\n       Drug 1...\n       Drug 2...");
              NickTime(textcolor7, color7);
            }
            
        time_now = millis();
        Drug3();

        while(millis() < time_now + min5 + TTB_drug3 - TTB_aCSF) {
              tft.setCursor(10,40);
              tft.print("5 - 5 - 5 - 5 - 5\n       aCSF...\n       Drug 1...\n       Drug 2...\n       Drug 3...");
              NickTime(textcolor7, color7);
            }
            
        time_now = millis();
        aCSF();
        
        while(millis() < time_now + min5 + TTB_aCSF) {
              tft.setCursor(10,40);
              tft.print("5 - 5 - 5 - 5 - 5\n       aCSF...\n       Drug 1...\n       Drug 2...\n       Drug 3...\n       aCSF...");
              NickTime(textcolor7, color7);
            }

        tft.fillScreen(LightGold);
        tft.setCursor(10,40);
        tft.print("5 - 5 - 5 - 5 - 5\n        Done!");
        delay(2000);
        HomeScreen();
        TS_Point p = ts.getPoint();
        
   } //END 5 MIN BLOCK - aCSF>Drug 1>Drug 2> Drug 3>aCSF

//10 MIN BLOCK - aCSF>Drug 1>aCSF
    if(p.x>120 && p.x<240 && p.y>40 && p.y<100 && buttonEnabled){
        tft.drawRoundRect(120, 40, 120, 60, 4, ILI9341_GREEN);
        buttonEnabled = false;
        start_time = millis();
        time_now = millis();
        aCSF();
        tft.fillScreen(color4);
        tft.setFont(&FreeSans18pt7b);
        tft.setTextColor(textcolor4);
        tft.setTextSize(1);
     
        while(millis() < time_now + min10 - TTB_drug1) {
              tft.setCursor(30,40);
              tft.print("10 - 10 - 10\n       aCSF...");
              NickTime(textcolor4, color4);
            }
            
        time_now = millis();
        Drug1();
           
        while(millis() < time_now + min10 + TTB_drug1 - TTB_aCSF) {
              tft.setCursor(30,40);
              tft.print("10 - 10 - 10\n       aCSF...\n       Drug 1...");
              NickTime(textcolor4, color4);
            }

        time_now = millis();
        aCSF();

        while(millis() < time_now + min10 + TTB_aCSF) {
              tft.setCursor(30,40);
              tft.print("10 - 10 - 10\n       aCSF...\n       Drug 1...\n       aCSF...");
              NickTime(textcolor4, color4);
            }

        tft.fillScreen(color4);
        tft.setCursor(30,40);
        tft.print("10 - 10 - 10\n        Done!");
        delay(2000);
        HomeScreen();
        TS_Point p = ts.getPoint();
        
   } //END 10 MIN BLOCK - aCSF>Drug 1>aCSF

//10 MIN BLOCK - aCSF>Drug 1>Drug 2>aCSF
    if(p.x>120 && p.x<240 && p.y>100 && p.y<150 && buttonEnabled){
        tft.drawRoundRect(120, 100, 120, 60, 4, ILI9341_GREEN);
        buttonEnabled = false;
        start_time = millis();
        time_now = millis();
        aCSF();
        tft.fillScreen(color6);
        tft.setFont(&FreeSans18pt7b);
        tft.setTextColor(textcolor6);
        tft.setTextSize(0);
        
        while(millis() < time_now + min10 - TTB_drug1) {
              tft.setCursor(20,40);
              tft.print("10-10-10-10\n       aCSF...");
              NickTime(textcolor6, color6);
            }
            
        time_now = millis();
        Drug1();
        
        while(millis() < time_now + min10 + TTB_drug1 - TTB_drug2) {
              tft.setCursor(20,40);
              tft.print("10-10-10-10\n       aCSF...\n       Drug 1...");
              NickTime(textcolor6, color6);
            }

        time_now = millis();
        Drug2();

        while(millis() < time_now + min10 + TTB_drug2 - TTB_aCSF) {
              tft.setCursor(20,40);
              tft.print("10-10-10-10\n       aCSF...\n       Drug 1...\n       Drug 2...");
              NickTime(textcolor6, color6);
            }
            
        time_now = millis();
        aCSF();
        
        while(millis() < time_now + min10 + TTB_aCSF) {
              tft.setCursor(20,40);
              tft.print("10-10-10-10\n       aCSF...\n       Drug 1...\n       Drug 2...\n       aCSF...");
              NickTime(textcolor6, color6);
            }

        tft.fillScreen(color6);
        tft.setCursor(20,40);
        tft.print("10-10-10-10\n        Done!");
        delay(2000);
        HomeScreen();
        TS_Point p = ts.getPoint();
        
   } //END 10 MIN BLOCK - aCSF>Drug 1>Drug 2>aCSF
 
//10 MIN BLOCK - aCSF>Drug 1>Drug 2>Drug 3>aCSF
    if(p.x>120 && p.x<240 && p.y>160 && p.y<220 && buttonEnabled){
        tft.drawRoundRect(120, 160, 120, 60, 4, ILI9341_GREEN);
        buttonEnabled = false;
        start_time = millis();
        time_now = millis();
        aCSF();
        tft.fillScreen(color8);
        tft.setFont(&FreeSans18pt7b);
        tft.setTextColor(textcolor8);
        tft.setTextSize(0);
     
        while(millis() < time_now + min10 - TTB_drug1) {
              tft.setCursor(0,40);
              tft.print("10-10-10-10-10\n       aCSF...");
              NickTime(textcolor8, color8);
            }
            
        time_now = millis();
        Drug1();
        
           
        while(millis() < time_now + min10 + TTB_drug1 - TTB_drug2) {
              tft.setCursor(0,40);
              tft.print("10-10-10-10-10\n       aCSF...\n       Drug 1...");
              NickTime(textcolor8, color8);
            }

        time_now = millis();
        Drug2();
   

        while(millis() < time_now + min10 + TTB_drug2 - TTB_drug3) {
              tft.setCursor(0,40);
              tft.print("10-10-10-10-10\n       aCSF...\n       Drug 1...\n       Drug 2...");
              NickTime(textcolor8, color8);
            }
            
        time_now = millis();
        Drug3();

        while(millis() < time_now + min10 + TTB_drug3 - TTB_aCSF) {
              tft.setCursor(0,40);
              tft.print("10-10-10-10-10\n       aCSF...\n       Drug 1...\n       Drug 2...\n       Drug 3...");
              NickTime(textcolor8, color8);
            }
            
        time_now = millis();
        aCSF();
        
        while(millis() < time_now + min10 + TTB_aCSF) {
              tft.setCursor(0,40);
              tft.print("10-10-10-10-10\n       aCSF...\n       Drug 1...\n       Drug 2...\n       Drug 3...\n       aCSF...");
              NickTime(textcolor8, color8);
            }

        tft.fillScreen(color8);
        tft.setCursor(0,40);
        tft.print("10-10-10-10-10\n        Done!");
        delay(2000);
        HomeScreen();
        TS_Point p = ts.getPoint();
        
   } //END 10 MIN BLOCK - aCSF>Drug 1>Drug 2> Drug 3>aCSF

//aCSF Button
    if(p.x>0 && p.x<60 && p.y>260 && p.y<320 && buttonEnabled){
        tft.drawRoundRect(0, 260, 60, 60, 4, ILI9341_GREEN);
        buttonEnabled = false;

        aCSF();
        
        DrugButtons();
        tft.drawRoundRect(0, 260, 60, 60, 4, ILI9341_GREEN);
        tft.setCursor(7,295);
        tft.setTextColor(ILI9341_BLUE);
        tft.print("aCSF");
        TS_Point p = ts.getPoint();
        
   } //END aCSF Button

//Drug 1 Button
    if(p.x>60 && p.x<120 && p.y>260 && p.y<320 && buttonEnabled){
        tft.drawRoundRect(60, 260, 60, 60, 4, ILI9341_GREEN);
        buttonEnabled = false;

        Drug1();
        
        DrugButtons();
        tft.drawRoundRect(60, 260, 60, 60, 4, ILI9341_GREEN);
        tft.setCursor(63,295);
        tft.setTextColor(ILI9341_BLUE);
        tft.print("Drug 1");
        TS_Point p = ts.getPoint();
        
   } //END Drug 1 Button


//Drug 2 Button
    if(p.x>120 && p.x<180 && p.y>260 && p.y<320 && buttonEnabled){
        tft.drawRoundRect(120, 260, 60, 60, 4, ILI9341_GREEN);
        buttonEnabled = false;

        Drug2();

        DrugButtons();
        tft.drawRoundRect(120, 260, 60, 60, 4, ILI9341_GREEN);
        tft.setCursor(123,295);
        tft.setTextColor(ILI9341_BLUE);
        tft.print("Drug 2");
        TS_Point p = ts.getPoint();
        
   } //END Drug 2 Button

   
//Drug 3 Button
    if(p.x>180 && p.x<240 && p.y>260 && p.y<320 && buttonEnabled){
        tft.drawRoundRect(180, 260, 60, 60, 4, ILI9341_GREEN);
        buttonEnabled = false;

        Drug3();

        DrugButtons();
        tft.drawRoundRect(180, 260, 60, 60, 4, ILI9341_GREEN);
        tft.setCursor(183,295);
        tft.setTextColor(ILI9341_BLUE);
        tft.print("Drug 3");
        TS_Point p = ts.getPoint();
        
   } //END Drug 3 Button

}
} //ends loop section
