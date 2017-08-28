#include <SoftwareSerial.h>
#define ledPin 15
#define ledGREEN 5

SoftwareSerial mySlave(10, 14); //rx,tx
//int state = 0;
void setup() {
  //Serial.begin(38400); // Default communication rate of the Bluetooth module
  mySlave.begin(38400);
  pinMode(ledPin, OUTPUT);
  pinMode(ledGREEN,OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(ledGREEN, HIGH);
  
}
void loop() {
  delay(441);
 if(mySlave.available() > 0){ // Checks whether data is comming from the serial port
    float state = mySlave.parseFloat();// Reads the data from the serial port
    Serial.println(state);
    
  if (state < 1) {
    digitalWrite(ledPin, LOW); // Turn LED OFF
    //Serial.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
  }
 
  else if (state >= 1) {
    digitalWrite(ledPin, HIGH);
    //Serial.println("LED: ON");
  }
 }
}
