#include <SoftwareSerial.h>
#define ledPin 15

//SoftwareSerial mySlave(10,14);
int state = 0;
void setup() {
  Serial.begin(38400);
  while (!Serial){
    
  }
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(38400); // Default communication rate of the Bluetooth module
}
void loop() {
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial.read();// Reads the data from the serial port
 
 if (state == '0') {
  digitalWrite(ledPin, LOW); // Turn LED OFF
  Serial.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
  state = 0;
 }
 else if (state == '1') {
  digitalWrite(ledPin, HIGH);
  Serial.println("LED: ON");
  state = 0;
}
  }
    }
