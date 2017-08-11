#include <SoftwareSerial.h>
#define ledPin 15
float inValue = 0;    // string to hold input
float weightInput =0;
int weightLimit = 20;
SoftwareSerial mySlave(10,14);
int state = 0;
void setup() {
  Serial.begin(38400);
  while (!Serial){
    
  }
  //pinMode(16, OUTPUT);
  //pinMode(14, OUTPUT);
  //pinMode(5, OUTPUT);
  //pinMode(4, OUTPUT);
  //pinMode(3, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 // pinMode(10, OUTPUT);
  //pinMode(9, OUTPUT);
  //pinMode(8, OUTPUT);
  //pinMode(6, OUTPUT);

  // send an intro:
  Serial.println();
  Serial.println("Measuring Weight...");
  Serial.println();
  
  mySlave.begin(38400);
}

void loop() {
  
 if(mySlave.available() > 0){ // Checks whether data is comming from the serial port
    state = mySlave.read();
 }
    
  while (Serial.available() > 0) {
      //string inString = Serial.readString();
      float inValue = Serial.parseFloat();
      //if (isDigit(inChar)) {
        // convert the incoming byte to a char
        // and add it to the string:
        //inString += (char)inChar;}
      // if you get a newline, print the string,
      // then the string's value:
      //if (inValue == '.') {
        Serial.print("New Weight:");
        Serial.println(inValue);
        weightInput = (inValue);
        if (weightInput < 0) {
          weightInput = 0;
        }
        //weightInput = abs(weightInput);
        Serial.println(weightLimit);
        //Serial.print("String: ");
        //Serial.println(inString);
        // clear the string for new input:
      //}  
   
    
    
    int state = 0;
    if ((weightLimit) <= weightInput)
    state=1;
    if ((weightLimit) > weightInput)
    state=2;
    
    switch (state) {
    case 1:
      //digitalWrite(10, HIGH);
      //digitalWrite(9, HIGH);
      digitalWrite(ledPin, HIGH);
      Serial.println("LED: ON");
      mySlave.println("LED: ON");
     // tone(6, 440);
     // lcd.setCursor(0, 0);
      //lcd.print("!!!!CRITICAL!!!!");
      //lcd.setCursor(0, 1);
      //lcd.print("!!!!CRITICAL!!!!");
      break;
     case 2:
    digitalWrite(ledPin, LOW);
    Serial.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
    mySlave.println("LED: OFF");
     break;
    

    }
    }
  }


