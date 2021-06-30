

void Color_Scheme_Menu(){


tft.setCursor(8,20);
tft.setFont(&FreeSans12pt7b);
tft.setTextSize(1);
tft.fillScreen(BLACK);
tft.setTextColor(WHITE);
tft.print("Select Color Scheme!");

ColorBlock("Classic", 32, MAROON, NAVY, RED, BLUE, RED, BLUE, RED, BLUE, PINK, YELLOW, WHITE);
ColorBlock("Rainbow", 64, RED, RED, ORANGE, ORANGE, YELLOW, YELLOW, GREEN, GREEN, BLUE, PURPLE, BLACK);
ColorBlock("Rainbow EXTREME", 96, RED, ORANGE, YELLOW, GREENYELLOW, GREEN, CYAN, BLUE, PURPLE, MAGENTA, PINK, BLACK);
ColorBlock("Monochrome", 128, BLACK, BLACK, DARKGREY, DARKGREY, DARKGREY, DARKGREY, DARKGREY, DARKGREY, LIGHTGREY, DARKGREY, WHITE);
ColorBlock("Monochrome 2", 160, WHITE, WHITE, LIGHTGREY, LIGHTGREY, LIGHTGREY, LIGHTGREY, LIGHTGREY, LIGHTGREY, DARKGREY, LIGHTGREY, BLACK);
ColorBlock("Pastel", 192, PASTELRED, PASTELBLUE, PASTELPINK, PASTELCYAN, PASTELPINK, PASTELCYAN, PASTELPINK, PASTELCYAN, PASTELGREEN, PASTELYELLOW, BLACK);
ColorBlock("Vandy Fam", 224, BLACK, BLACK, GOLD, GOLD, GOLD, GOLD, GOLD, GOLD, BLACK, GOLD, WHITE);
ColorBlock("'Murica", 256, NAVY, RED, WHITE, WHITE, RED, RED, WHITE, WHITE, RED, WHITE, BLACK); 
ColorBlock("Sunset", 288, NAVY, NAVY, PURPLE, PURPLE, INDIGO, INDIGO, SALMON, SALMON, ORANGE, YELLOW, WHITE);
}


void Color_Scheme_Select() {
//  COLOR SCHEME BUTTONS BUTTON 
    
     TS_Point p = ts.getPoint();
      //Scale from ~0->4000 to tft.width using the calibration #'s
      p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
      p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
    


//classic
    if(p.x>0 && p.x<240 && p.y>32 && p.y<64 && p.z>50 && SelectColor==1){
      
        color1 = MAROON;
        color2 = NAVY;
        color3 = RED;
        color4 = BLUE;
        color5 = RED;
        color6 = BLUE;
        color7 = RED;
        color8 = BLUE;
        color9 = PINK;
        color10 = YELLOW;

        textcolor1 = WHITE;
        textcolor2 = WHITE;
        textcolor3 = BLACK;
        textcolor4 = BLACK;
        textcolor5 = BLACK;
        textcolor6 = BLACK;
        textcolor7 = BLACK;
        textcolor8 = BLACK;
        textcolor9 = BLACK;
        textcolor10 = BLACK;
        tft.fillCircle(p.x,p.y,12,GREEN);
        delay(1000);
        HomeScreen();
        SelectColor = 0;
        TS_Point p = ts.getPoint();
        
      } 

      //rainbow
    if(p.x>0 && p.x<240 && p.y>64 && p.y<96 && p.z>50 && SelectColor==1){

        color1 = RED;
        color2 = RED;
        color3 = ORANGE;
        color4 = ORANGE;
        color5 = YELLOW;
        color6 = YELLOW;
        color7 = GREEN;
        color8 = GREEN;
        color9 = BLUE;
        color10 = PURPLE;  

        textcolor1 = BLACK;
        textcolor2 = BLACK;
        textcolor3 = BLACK;
        textcolor4 = BLACK;
        textcolor5 = BLACK;
        textcolor6 = BLACK;
        textcolor7 = BLACK;
        textcolor8 = BLACK;
        textcolor9 = BLACK;
        textcolor10 = WHITE;
        tft.fillCircle(p.x,p.y,12,GREEN);
        delay(1000);
        HomeScreen();
        SelectColor = 0;
        TS_Point p = ts.getPoint();
      } 

      //rainbow extreme
    if(p.x>0 && p.x<240 && p.y>96 && p.y<128 && p.z>50 && SelectColor==1){

        color1 = RED;
        color2 = ORANGE;
        color3 = YELLOW;
        color4 = GREENYELLOW;
        color5 = GREEN;
        color6 = CYAN;
        color7 = BLUE;
        color8 = PURPLE;
        color9 = MAGENTA;
        color10 = PINK;

        textcolor1 = BLACK;
        textcolor2 = BLACK;
        textcolor3 = BLACK;
        textcolor4 = BLACK;
        textcolor5 = BLACK;
        textcolor6 = BLACK;
        textcolor7 = BLACK;
        textcolor8 = BLACK;
        textcolor9 = BLACK;
        textcolor10 = BLACK;
        tft.fillCircle(p.x,p.y,12,GREEN);
        delay(1000);
        HomeScreen();
        SelectColor = 0;
        TS_Point p = ts.getPoint();
      }       

      //monochrome 1
    if(p.x>0 && p.x<240 && p.y>128 && p.y<160 && p.z>50 && SelectColor==1){

        color1 = BLACK;
        color2 = BLACK;
        color3 = DARKGREY;
        color4 = DARKGREY;
        color5 = DARKGREY;
        color6 = DARKGREY;
        color7 = DARKGREY;
        color8 = DARKGREY;
        color9 = LIGHTGREY;
        color10 = DARKGREY;

        textcolor1 = WHITE;
        textcolor2 = WHITE;
        textcolor3 = WHITE;
        textcolor4 = WHITE;
        textcolor5 = WHITE;
        textcolor6 = WHITE;
        textcolor7 = WHITE;
        textcolor8 = WHITE;
        textcolor9 = BLACK;
        textcolor10 = WHITE;
        tft.fillCircle(p.x,p.y,12,GREEN);
        delay(1000);

        HomeScreen();
        SelectColor = 0;
        TS_Point p = ts.getPoint();
      } 

      //monochrome 2
    if(p.x>0 && p.x<240 && p.y>160 && p.y<192 && p.z>50 && SelectColor==1){

        color1 = WHITE;
        color2 = WHITE;
        color3 = LIGHTGREY;
        color4 = LIGHTGREY;
        color5 = LIGHTGREY;
        color6 = LIGHTGREY;
        color7 = LIGHTGREY;
        color8 = LIGHTGREY;
        color9 = DARKGREY;
        color10 = LIGHTGREY;

        textcolor1 = BLACK;
        textcolor2 = BLACK;
        textcolor3 = BLACK;
        textcolor4 = BLACK;
        textcolor5 = BLACK;
        textcolor6 = BLACK;
        textcolor7 = BLACK;
        textcolor8 = BLACK;
        textcolor9 = WHITE;
        textcolor10 = BLACK;

        tft.fillCircle(p.x,p.y,12,GREEN);
        delay(1000);
        HomeScreen();
        SelectColor = 0;
        TS_Point p = ts.getPoint();
      } 
     
      //pastels
    if(p.x>0 && p.x<240 && p.y>192 && p.y<224 && p.z>50 && SelectColor==1){

        color1 = PASTELRED;
        color2 = PASTELBLUE;
        color3 = PASTELPINK;
        color4 = PASTELCYAN;
        color5 = PASTELPINK;
        color6 = PASTELCYAN;
        color7 = PASTELPINK;
        color8 = PASTELCYAN;
        color9 = PASTELGREEN;
        color10 = PASTELYELLOW;

        textcolor1 = BLACK;
        textcolor2 = BLACK;
        textcolor3 = BLACK;
        textcolor4 = BLACK;
        textcolor5 = BLACK;
        textcolor6 = BLACK;
        textcolor7 = BLACK;
        textcolor8 = BLACK;
        textcolor9 = BLACK;
        textcolor10 = BLACK;
        tft.fillCircle(p.x,p.y,12,GREEN);
        delay(1000);

        HomeScreen();
        SelectColor = 0;
        TS_Point p = ts.getPoint();
      }

      //vandy fam
    if(p.x>0 && p.x<240 && p.y>224 && p.y<256 && p.z>50 && SelectColor==1){
        
        color1 = BLACK;
        color2 = BLACK;
        color3 = GOLD;
        color4 = GOLD;
        color5 = GOLD;
        color6 = GOLD;
        color7 = GOLD;
        color8 = GOLD;
        color9 = BLACK;
        color10 = GOLD;

        textcolor1 = WHITE;
        textcolor2 = WHITE;
        textcolor3 = BLACK;
        textcolor4 = BLACK;
        textcolor5 = BLACK;
        textcolor6 = BLACK;
        textcolor7 = BLACK;
        textcolor8 = BLACK;
        textcolor9 = WHITE;
        textcolor10 = BLACK;
        tft.fillCircle(p.x,p.y,12,GREEN);
        delay(1000);
        HomeScreen();
        SelectColor = 0;
        TS_Point p = ts.getPoint();
      } 

      //murica
    if(p.x>0 && p.x<240 && p.y>256 && p.y<288 && p.z>50 && SelectColor==1){
     
        color1 = NAVY;
        color2 = RED;
        color3 = WHITE;
        color4 = WHITE;
        color5 = RED;
        color6 = RED;
        color7 = WHITE;
        color8 = WHITE;
        color9 = RED;
        color10 = WHITE;

        textcolor1 = WHITE;
        textcolor2 = BLACK;
        textcolor3 = BLACK;
        textcolor4 = BLACK;
        textcolor5 = BLACK;
        textcolor6 = BLACK;
        textcolor7 = BLACK;
        textcolor8 = BLACK;
        textcolor9 = BLACK;
        textcolor10 = BLACK;
        tft.fillCircle(p.x,p.y,12,GREEN);
        delay(1000);
        HomeScreen();
        SelectColor = 0;
        TS_Point p = ts.getPoint();
      } 


     //sunset
    if(p.x>0 && p.x<240 && p.y>288 && p.y<320 && p.z>50 && SelectColor==1){

        color1 = NAVY;
        color2 = NAVY;
        color3 = PURPLE;
        color4 = PURPLE;
        color5 = INDIGO;
        color6 = INDIGO;
        color7 = SALMON;
        color8 = SALMON;
        color9 = ORANGE;
        color10 = YELLOW;

        textcolor1 = WHITE;
        textcolor2 = WHITE;
        textcolor3 = WHITE;
        textcolor4 = WHITE;
        textcolor5 = WHITE;
        textcolor6 = WHITE;
        textcolor7 = WHITE;
        textcolor8 = WHITE;
        textcolor9 = BLACK;
        textcolor10 = BLACK;
        tft.fillCircle(p.x,p.y,12,GREEN);
        delay(1000);
        HomeScreen();
        SelectColor = 0;
        TS_Point p = ts.getPoint();
      } 
       
  }
