
//functions used throughout code

void Button(int x, int y, int sizeX, int sizeY, int rad, uint16_t color){
  tft.fillRoundRect(x, y, sizeX, sizeY, rad, color);
  tft.drawRoundRect(x, y, sizeX, sizeY, rad, ILI9341_BLACK);
}

void WelcomeScreen() {
  tft.setRotation(0);
  tft.fillScreen(ILI9341_BLACK);
  drawBitmap(10,130,LOGO,220,68,ILI9341_WHITE);
}

void HomeScreen() {
  tft.setRotation(0);
  tft.setFont(&FreeSans9pt7b);
  tft.setTextSize(0);
  tft.fillScreen(ILI9341_BLACK);
  
  Button(0, 0, 120, 40, 4, color1);
  Button(0, 40, 120, 60, 4, color3);
  Button(0, 100, 120, 60, 4, color5);
  Button(0, 160, 120, 60, 4, color7);
  tft.setCursor(8, 25);
  tft.setTextColor(textcolor1);
  tft.print("5 min Blocks");
  tft.setTextColor(textcolor3);
  tft.setFont(&FreeSans12pt7b);
  tft.setCursor(20, 78);
  tft.print("1 Drug");
  tft.setCursor(18, 137);
  tft.setTextColor(textcolor5);
  tft.print("2 Drugs");
  tft.setCursor(18, 198);
  tft.setTextColor(textcolor7);
  tft.print("3 Drugs");
 
  Button(120, 0, 120, 40, 4, color2);
  Button(120, 40, 120, 60, 4, color4);
  Button(120, 100, 120, 60, 4, color6);
  Button(120, 160, 120, 60, 4, color8);
  tft.setFont(&FreeSans9pt7b);
  tft.setCursor(122, 25);
  tft.setTextColor(textcolor2);
  tft.print("10 min Blocks");
  tft.setFont(&FreeSans12pt7b);
  tft.setTextColor(textcolor4);
  tft.setCursor(140, 78);
  tft.print("1 Drug");
  tft.setCursor(138, 137);
  tft.setTextColor(textcolor6);
  tft.print("2 Drugs");
  tft.setCursor(138, 198);
  tft.setTextColor(textcolor8);
  tft.print("3 Drugs");
 
  tft.setFont(&FreeSans9pt7b);
  Button (0, 220, 240, 40, 4, color9);
  tft.setCursor(80, 245);
  tft.setTextColor(textcolor9);
  tft.print("PRIME ALL");

  Button (0, 260, 60, 60, 4, color10);
  Button (60, 260, 60, 60, 4, color10);
  Button (120, 260, 60, 60, 4, color10);
  Button (180, 260, 60, 60, 4, color10);
  tft.setCursor(7,295);
  tft.setTextColor(textcolor10);
  tft.print("aCSF");
  tft.setCursor(63,295);
  tft.print("Drug 1");
  tft.setCursor(123,295);
  tft.print("Drug 2");
  tft.setCursor(183,295);
  tft.print("Drug 3");
  
}

void DrugButtons() {
  Button (0, 260, 60, 60, 4, color10);
  Button (60, 260, 60, 60, 4, color10);
  Button (120, 260, 60, 60, 4, color10);
  Button (180, 260, 60, 60, 4, color10);
  tft.setCursor(7,295);
  tft.setTextColor(textcolor10);
  tft.print("aCSF");
  tft.setCursor(63,295);
  tft.print("Drug 1");
  tft.setCursor(123,295);
  tft.print("Drug 2");
  tft.setCursor(183,295);
  tft.print("Drug 3");
}

void aCSF() {
  servo.attach(servoPin);
  servotwo.attach(servotwoPin);
  servothree.attach(servothreePin);
  servo.write(30);
  servotwo.write(30);
  servothree.write(20);
  delay(250);
  servo.detach();
  servotwo.detach();
  servothree.detach();
}

void Drug1() {
  servo.attach(servoPin);
  servotwo.attach(servotwoPin);
  servothree.attach(servothreePin);
  servo.write(120);
  servotwo.write(30);
  servothree.write(20);
  delay(250);
  servo.detach();
  servotwo.detach();
  servothree.detach();
}

void Drug2() {
  servo.attach(servoPin);
  servotwo.attach(servotwoPin);
  servothree.attach(servothreePin);
  servo.write(30);
  servotwo.write(120);
  servothree.write(20);
  delay(250);
  servo.detach();
  servotwo.detach();
  servothree.detach();
}

void Drug3() {
  servo.attach(servoPin);
  servotwo.attach(servotwoPin);
  servothree.attach(servothreePin);
  servo.write(30);
  servotwo.write(30);
  servothree.write(110);
  delay(250);
  servo.detach();
  servotwo.detach();
  servothree.detach();
}

void NickTime(unsigned long text_color, unsigned long bg_color) {
 
  currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    tft.fillRect(73,291,90,25,bg_color);

          tft.setTextColor(text_color);
          tft.setCursor(78,315);
          tft.setTextSize(1);
          seconds = ((millis()-start_time)/1000);
                if (seconds >= 60) {
                  minutes = minutes + 1;
                  start_time = millis();
                  seconds = 0;
                }
                 if (minutes <= 9) {
                  tft.print(0);
                }
            
          tft.print(minutes);
          tft.print(":");
          
                if (seconds <= 9) {
                  tft.print(0);
                }
            
          tft.print(seconds);
    
  }
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


void ColorBlock(String title, int y, uint16_t color_1, uint16_t color_2, uint16_t color_3, uint16_t color_4, uint16_t color_5, uint16_t color_6, 
                uint16_t color_7, uint16_t color_8, uint16_t color_9, uint16_t color_10, uint16_t text_color) {

    tft.fillRect(0, y, 24, 32, color_1);
    tft.fillRect(24, y, 24, 32, color_2);
    tft.fillRect(48, y, 24, 32, color_3);
    tft.fillRect(72, y, 24, 32, color_4);
    tft.fillRect(96, y, 24, 32, color_5);
    tft.fillRect(120, y, 24, 32, color_6);
    tft.fillRect(144, y, 24, 32, color_7);
    tft.fillRect(168, y, 24, 32, color_8);
    tft.fillRect(192, y, 24, 32, color_9);
    tft.fillRect(216, y, 24, 32, color_10);

    tft.drawRect(0, y, 240, 32, ILI9341_BLACK);
    tft.setCursor(5,y+24);
    tft.setTextColor(text_color);
    tft.print(title);
}
