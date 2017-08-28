#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <SoftwareSerial.h>

SoftwareSerial mySlave(10,9); //rx,tx

// For the Adafruit shield, these are the default.
#define TFT_DC 6
#define TFT_CS 7
#define TFT_CLK 15
#define TFT_MOSI 16
#define TFT_MISO 14
#define TFT_RST 8


float inValue = 0;    // string to hold input
float weightInput =0;
int weightLimit = 50;

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

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
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft.width()  / 12,
                cy = tft.height() / 3;

  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  tft.fillRect(cx, cy, 40*level, 60, color1);
  return 0;
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
  pinMode(5, OUTPUT);

  // send an intro:
  Serial.println();
  Serial.println("Setting Weight Limit...");
  Serial.println(weightLimit);
  Serial.println();
 
  

}

void loop() {
int warning = 0;

  if (weightLimit <= 19) {
    warning = (weightLimit / 5);
    Serial.println(warning);
  }
  else if (weightLimit > 19) {
    warning = (weightLimit / 10);
    Serial.println(warning);
  }
Serial.println(tft.width());
Serial.println(tft.height());
while(true){
  delay(441);
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
	  int state = 0;
	  if ((weightLimit) <= weightInput)
		state=10;
	  else if (weightLimit <= (weightInput + warning))
		state=9;
	  else if ((weightInput <= weightLimit) && (weightInput > weightLimit * 0.875))
		state=8;
	  else if ((weightInput <= weightLimit * 0.875) && (weightInput > weightLimit * 0.75))
		state=7;
	  else if ((weightInput <= weightLimit * 0.75) && (weightInput > weightLimit * 0.625))
		state=6;
	  else if ((weightInput <= weightLimit * 0.625) && (weightInput > weightLimit * 0.5))
		state=5;
	  else if ((weightInput <= weightLimit * 0.5) && (weightInput > weightLimit * 0.375))
		state=4;
	  else if ((weightInput <= weightLimit * 0.375) && (weightInput > weightLimit * 0.25))
		state=3;
	  else if ((weightInput <= weightLimit * 0.25) && (weightInput > weightLimit * 0.125))
		state=2;
	  else if ((weightInput <= weightLimit * 0.125) && (weightInput > 0))
		state=1;

	  
	  if (state==10){
			tone(5, 440);
			txtCritical();
	  }
    else if (state==9){
			tone(5, 220);
			txtWarning();
    }
		else {
	    lvlBars(ILI9341_WHITE,state);
	  }
	}
}
}
