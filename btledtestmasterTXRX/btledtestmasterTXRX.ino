#include <SoftwareSerial.h>

//SoftwareSerial myMaster(8,7); //(Rx, Tx)

void setup() {
  Serial.begin(38400); // Default communication rate of the Bluetooth module
  while (!Serial){
    
  }
}
void loop() { // run over and over
 // if (Serial.available()) {
    Serial.println("1");
    Serial.println("LED: ON");
 delay (1000);
 Serial.println("0");
 Serial.println("LED: OFF");
 delay(1000);
    
  }
   //if (Serial.available()) {
    //Serial.write(Serial.read());
  //}
  
//}
