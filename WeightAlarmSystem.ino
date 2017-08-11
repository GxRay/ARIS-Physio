#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
String inString = "";    // string to hold input
int weightInput = 0;
int weightLimit = 20;
byte fillbox[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

byte emptybox[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};


void setup() {
  
  // Open serial communications and wait for port to open:
  
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // send an intro:
  Serial.println();
  Serial.println("Measuring Weight...");
  Serial.println();

  lcd.createChar(0, fillbox);
  lcd.createChar(1, emptybox);
  lcd.begin(16, 2);

  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(6, OUTPUT);

}

void loop() {
  
  // Read serial input:
  int warning = 0;

  if (weightLimit <= 19) {
    warning = (weightLimit / 5);
    Serial.println(warning);
  }
  else if (weightLimit > 19) {
    warning = (weightLimit / 10);
    Serial.println(warning);
  }

  while (true) {
    
    while (Serial.available() > 0) {
      int inChar = Serial.read();
      if (isDigit(inChar)) {
        // convert the incoming byte to a char
        // and add it to the string:
        inString += (char)inChar;
      }
      // if you get a newline, print the string,
      // then the string's value:
      if (inChar == '\n') {
        Serial.print("New Weight:");
        Serial.println(inString.toInt());
        weightInput = (inString.toInt());
        weightInput = abs(weightInput);
        //Serial.println(weightLimit);
        //Serial.print("String: ");
        //Serial.println(inString);
        // clear the string for new input:
        inString = "";
      }
	  
	  int state = 0;
	  if ((weightLimit) <= weightInput)
		state=1;
	  else if (weightLimit <= (weightInput + warning))
		state=2;
	  else if ((weightInput <= weightLimit) && (weightInput > weightLimit * 0.875))
		state=3;
	  else if ((weightInput <= weightLimit * 0.875) && (weightInput > weightLimit * 0.75))
		state=4;
	  else if ((weightInput <= weightLimit * 0.75) && (weightInput > weightLimit * 0.625))
		state=5;
	  else if ((weightInput <= weightLimit * 0.625) && (weightInput > weightLimit * 0.5))
		state=6;
	  else if ((weightInput <= weightLimit * 0.5) && (weightInput > weightLimit * 0.375))
		state=7;
	  else if ((weightInput <= weightLimit * 0.375) && (weightInput > weightLimit * 0.25))
		state=8;
	  else if ((weightInput <= weightLimit * 0.25) && (weightInput > weightLimit * 0.125))
		state=9;
	  else if ((weightInput <= weightLimit * 0.125) && (weightInput > 0))
		state=10;
	
	
	  
	  
	  switch (state) {
		case 1:
			digitalWrite(10, HIGH);
			digitalWrite(9, HIGH);
			digitalWrite(8, HIGH);
			tone(6, 440);
			lcd.setCursor(0, 0);
			lcd.print("!!!!CRITICAL!!!!");
			lcd.setCursor(0, 1);
			lcd.print("!!!!CRITICAL!!!!");
			break;
		case 2:
			digitalWrite(10, HIGH);
			digitalWrite(9, HIGH);
			digitalWrite(8, LOW);
			tone(6, 220);
			lcd.setCursor(0, 0);
			lcd.print("   !WARNING!    ");
			lcd.setCursor(0, 1);
			lcd.print("   !WARNING!    ");
			break;
		case 3:
			digitalWrite(10, HIGH);
			digitalWrite(9, LOW);
			digitalWrite(8, LOW);
			noTone(6);
			for (int c = 0; c < 16; c++) {
				lcd.setCursor(c, 0);
				lcd.write(byte(0));
				lcd.setCursor(c, 1);
				lcd.write(byte(0));
			}
			break;
		case 4:
			digitalWrite(10, HIGH);
			digitalWrite(9, LOW);
			digitalWrite(8, LOW);
			noTone(6);
			for (int c = 0; c < 14; c++) {
				lcd.setCursor(c, 0);
				lcd.write(byte(0));
				lcd.setCursor(c, 1);
				lcd.write(byte(0));
			}
			for (int c = 14; c < 16; c++){
				lcd.setCursor(c, 0);
				lcd.write(byte(1));
				lcd.setCursor(c, 1);
				lcd.write(byte(1));
			}
			break;
		case 5:
			digitalWrite(10, HIGH);
			digitalWrite(9, LOW);
			digitalWrite(8, LOW);
			noTone(6);
			for (int c = 0; c < 12; c++) {
				lcd.setCursor(c, 0);
				lcd.write(byte(0));
				lcd.setCursor(c, 1);
				lcd.write(byte(0));
			}
			for (int c = 12; c < 16; c++){
				lcd.setCursor(c, 0);
				lcd.write(byte(1));
				lcd.setCursor(c, 1);
				lcd.write(byte(1));
			}
			break;
		case 6:
			digitalWrite(10, HIGH);
			digitalWrite(9, LOW);
			digitalWrite(8, LOW);
			noTone(6);
			for (int c = 0; c < 10; c++) {
				lcd.setCursor(c, 0);
				lcd.write(byte(0));
				lcd.setCursor(c, 1);
				lcd.write(byte(0));
			}
			for (int c = 10; c < 16; c++){
				lcd.setCursor(c, 0);
				lcd.write(byte(1));
				lcd.setCursor(c, 1);
				lcd.write(byte(1));
			}
			break;
		case 7:
			digitalWrite(10, HIGH);
			digitalWrite(9, LOW);
			digitalWrite(8, LOW);
			noTone(6);
			for (int c = 0; c < 8; c++) {
				lcd.setCursor(c, 0);
				lcd.write(byte(0));
				lcd.setCursor(c, 1);
				lcd.write(byte(0));
			}
			for (int c = 8; c < 16; c++){
				lcd.setCursor(c, 0);
				lcd.write(byte(1));
				lcd.setCursor(c, 1);
				lcd.write(byte(1));
			}
			break;
		case 8:
			digitalWrite(10, HIGH);
			digitalWrite(9, LOW);
			digitalWrite(8, LOW);
			noTone(6);
			for (int c = 0; c < 6; c++) {
				lcd.setCursor(c, 0);
				lcd.write(byte(0));
				lcd.setCursor(c, 1);
				lcd.write(byte(0));
			}
			for (int c = 6; c < 16; c++){
				lcd.setCursor(c, 0);
				lcd.write(byte(1));
				lcd.setCursor(c, 1);
				lcd.write(byte(1));
			}
			break;
		case 9:
			digitalWrite(10, HIGH);
			digitalWrite(9, LOW);
			digitalWrite(8, LOW);
			noTone(6);
			for (int c = 0; c < 4; c++) {
				lcd.setCursor(c, 0);
				lcd.write(byte(0));
				lcd.setCursor(c, 1);
				lcd.write(byte(0));
			}
			for (int c = 4; c < 16; c++){
				lcd.setCursor(c, 0);
				lcd.write(byte(1));
				lcd.setCursor(c, 1);
				lcd.write(byte(1));
			}
			break;
		case 10:
			digitalWrite(10, HIGH);
			digitalWrite(9, LOW);
			digitalWrite(8, LOW);
			noTone(6);
			for (int c = 0; c < 2; c++) {
				lcd.setCursor(c, 0);
				lcd.write(byte(0));
				lcd.setCursor(c, 1);
				lcd.write(byte(0));
			}
			for (int c = 2; c < 16; c++){
				lcd.setCursor(c, 0);
				lcd.write(byte(1));
				lcd.setCursor(c, 1);
				lcd.write(byte(1));
			}
			break;
		default:
			digitalWrite(10, HIGH);
			digitalWrite(9, LOW);
			digitalWrite(8, LOW);
			noTone(6);
			for (int c = 0; c < 16; c++) {
				lcd.setCursor(c, 0);
				lcd.write(byte(1));
				lcd.setCursor(c, 1);
				lcd.write(byte(1));
			}
			break;
	  
	  }
	}
}
}
