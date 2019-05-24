//Significant bug when moving limit over 100 and trying to go back down, overflow
//value doesn't disappear

#include "SPI.h"
#include "Adafruit_GFX.h" 
#include "Adafruit_ILI9341.h" //320x240 LCD
#include <SoftwareSerial.h>
#include "TouchScreen.h"

SoftwareSerial mySlave(9,10); //rx,tx

// For the Adafruit shield, these are the default.
#define TFT_DC 6
#define TFT_CS 7
#define TFT_CLK 15
#define TFT_MOSI 16
#define TFT_MISO 14
#define TFT_RST 8

// These are the four touchscreen analog pins
#define YP A0  // must be an analog pin, use "An" notation!
#define XM A1  // must be an analog pin, use "An" notation!
#define YM 5   // can be a digital pin
#define XP 6   // can be a digital pin

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

 float inValue = 0;    // string to hold input
  float weightInput = 40;
  int weightLimit = 50;
  int warning = 0;

int txtWarning() {
  tft.fillScreen(ILI9341_YELLOW);
  //unsigned long start = micros();
  tft.setRotation(3);
  tft.setCursor(30, (tft.width()/2)-50);
  tft.setTextColor(ILI9341_BLACK);  tft.setTextSize(6);
  tft.println("WARNING!");
  delay(200);
  return 0;
}

int txtCritical() {
  tft.fillScreen(ILI9341_RED);
  tft.setRotation(3);
  tft.setCursor(20, (tft.width()/2)-50);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(6);
  tft.println("CRITICAL");
  delay(200);
  return 0;
}

int lvlBars(uint16_t color1, int level){
  tft.setRotation(3);
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft.width()  / 20,
                cy = tft.height() / 3;

  for (i=1;i<=level;i++){
  tft.fillRect(cx+(36*(i-1)), cy-10, 35, 70, color1);
  }
  for (i=level+1;i<=8;i++){
  tft.fillRect(cx+(36*(i-1)), cy-10, 35, 70, ILI9341_BLACK);
  }
  return 0;
}

unsigned long triangleButtons() {
 tft.setRotation(3);
  unsigned long start, t = 0;
  int           i, cx = tft.width()- (tft.width() / 6),
                   cy = tft.height()-90;

  tft.fillTriangle(cx, cy-1, cx-30, cy+40, cx+30, cy+40,
      tft.color565(0, 187, 255));
  tft.fillTriangle(cx, cy+89, cx-30, cy+50, cx+30, cy+50,
      tft.color565(0, 187, 255));

}

unsigned long settingsButton(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = 50, h = 23, r2 = radius*3;
tft.setRotation(0);
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}
int currentTxt(float inputValue){

  tft.setRotation(3);
  tft.setCursor(20, 20);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);  tft.setTextSize(2);
  tft.print("Current Weight: ");
  tft.setCursor(225, 20);
  tft.println(inputValue);
}

int limitTxt(float weightLimit){

  tft.setRotation(3);
  tft.setCursor(20, 170);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);  tft.setTextSize(2);
  tft.print("Current Limit: ");
  tft.setCursor(160, 200);
  tft.println(weightLimit);
}

int updateState(){

if ((weightLimit) <= weightInput)
    return(10);
    else if (weightLimit <= (weightInput + warning))
    return(9);
    else if ((weightInput <= weightLimit) && (weightInput > weightLimit * 0.875))
    return(8);
    else if ((weightInput <= weightLimit * 0.875) && (weightInput > weightLimit * 0.75))
    return(7);
    else if ((weightInput <= weightLimit * 0.75) && (weightInput > weightLimit * 0.625))
    return(6);
    else if ((weightInput <= weightLimit * 0.625) && (weightInput > weightLimit * 0.5))
    return(5);
    else if ((weightInput <= weightLimit * 0.5) && (weightInput > weightLimit * 0.375))
    return(4);
    else if ((weightInput <= weightLimit * 0.375) && (weightInput > weightLimit * 0.25))
    return(3);
    else if ((weightInput <= weightLimit * 0.25) && (weightInput > weightLimit * 0.125))
    return(2);
    else if ((weightInput <= weightLimit * 0.125) && (weightInput > 0))
    return(1);
}

void setup() {
  
  //Serial.begin(38400);
  mySlave.begin(38400);

  //Serial.println("ILI9341 Test!"); 
 
  tft.begin();

/*  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 
  // Open serial communications and wait for port to open:
  
  */
  pinMode(4, OUTPUT);
  tft.fillScreen(ILI9341_BLACK);
}



void loop() {

  settingsButton(15,ILI9341_RED);
  triangleButtons();

// Retrieve a point  
  TSPoint p = ts.getPoint();

// we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
 if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {

  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.height());
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.width());
  
  if ((p.y >= 23) && (p.y <= 83)){
    if ((p.x <= 190) && (p.x >= 150)){
      weightLimit++;
    }
    if ((p.x >= 200)){
      weightLimit--;
    }
  }

  if ((p.y < 23)){
    if ((p.x <= 190)){
       mySlave.println("x");
       delay(50);
       mySlave.println("1");
       if ((p.y < 23)){
          if ((p.x <= 190)){
            mySlave.println("x");
          }
       }
    }
  }
 }
  
  
if (mySlave.available() > 0) {
      float inValue = mySlave.parseFloat();
        Serial.print("New Weight:");
        Serial.println(inValue);
        weightInput = (inValue);
        if (weightInput < 0) {
          weightInput = 0;
        }
        Serial.print("Input Weight:");
        Serial.println(weightInput);
 }


currentTxt(weightInput);
limitTxt(weightLimit);

  if (weightLimit <= 19) {
    warning = (weightLimit / 5);
    Serial.println(warning);
  }
  else if (weightLimit > 19) {
    warning = (weightLimit / 10);
    Serial.println(warning);
  }

int state = 0;
state= updateState();  
	  
	  if (state==10){
			tone(4, 440);
			txtCritical();
      tft.fillScreen(ILI9341_BLACK);
	  }
    else if (state==9){
			tone(4, 220);
			txtWarning();
      tft.fillScreen(ILI9341_BLACK);
    }
		else {
	    lvlBars(ILI9341_WHITE, state);
	  }
}

