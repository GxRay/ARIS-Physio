#include <SoftwareSerial.h>

SoftwareSerial myMaster(8,7); //(Rx, Tx)

void setup() {
  Serial.begin(38400);
  while (!Serial){
    
  }
  myMaster.begin(38400); // Default communication rate of the Bluetooth module
}
void loop() { // run over and over
  if (myMaster.available()) {
    Serial.write(myMaster.read());
  }
   if (Serial.available()) {
    myMaster.write(Serial.read());
  }
  
}
