#include <SoftwareSerial.h>

//#define DAC1 25

const int FSR_PIN1 = A0; // Pin connected to FSR/resistor divider
const int FSR_PIN2 = A1;
const int FSR_PIN3 = A7;

//Multiplexer Pins


SoftwareSerial mySlave(9, 10); //rx,tx



int r0 = 0;
int r1 = 0;
int r2 = 0;

int count = 0; //which y pin is selected

// Measure the voltage at 5V and resistance of your 3.3k resistor, and enter
// their value's below:
const float VCC = 5; // Measured voltage of Ardunio 5V line


void setup()
{
  Serial.begin(38400);
  mySlave.begin(38400);

  pinMode(FSR_PIN1, INPUT);
  pinMode(FSR_PIN2, INPUT);
  pinMode(FSR_PIN3, INPUT);


}

void loop()
{
  // Print the header:
  Serial.println();
  Serial.println("A0\tA1\tA7\tY3\tY4\tY5\tY6\tY7");
  Serial.println("---\t---\t---\t---\t---\t---\t---\t---");
  int lines = 0;

  //      int dacValue = 20; //Set DAC generate 1V = 77, 225 = 3.3V, 20 = 0.3 V
  //      dacWrite(DAC1, dacValue);
  do {
    //    for (byte pin = 0; pin <= 7; pin++)
    //    {
    //selectMuxPin(pin);
    //    int fsrADC1 = analogRead(FSR_PIN1);
    //    Serial.print(fsrADC1);
        Serial.print("\t");
    //    mySlave.print(fsrADC1);
        mySlave.print("\t");

    int fsrADC2 = analogRead(FSR_PIN2);
    Serial.print(fsrADC2);
    Serial.print("\t");
    mySlave.print(fsrADC2);
    mySlave.print("\t");

//    int fsrADC3 = analogRead(FSR_PIN3);
//    Serial.print(fsrADC3);
    Serial.print("\t");
//    mySlave.print(fsrADC3);
    mySlave.print("\t");

    // If the FSR has no pressure, the resistance will be
    // near infinite. So the voltage should be near 0.



    //      if (fsrADC != 0) // If the analog reading is non-zero
    //      {
    //        // Use ADC reading to calculate voltage:
    //        int fsrV = map(fsrADC, 0, 1023, 0, 5000);
    //
    //        //Serial.print(String(String(fsrV) + " mV") + "\t");
    //        //mySlave.print(String(String(fsrV) + " mV") + "\t");
    //
    //        //    // Guesstimate force based on slopes in figure 3 of
    //        //    // FSR datasheet:
    //        //    float force;
    //        //    float fsrG = 1.0 / fsrR; // Calculate conductance
    //        //    // Break parabolic curve down into two linear slopes:
    //        //    if (fsrR <= 600)
    //        //      force = (fsrG - 0.00075) / 0.00000032639;
    //        //    else
    //        //      force =  fsrG / 0.000000642857;
    //        //    Serial.println("Force: " + String(force) + " g");
    //
    //        delay(100);
    //      }
    //      else
    //      {
    //        // No pressure detected
    //        delay(100);
    //      }



    lines++;

    Serial.println();
    mySlave.println();
    delay(200);
  } while (lines < 10);

}

//
//// The selectMuxPin function sets the S0, S1, and S2 pins to select the give pin
//void selectMuxPin(byte pin)
//{
//  if (pin > 7) return; // Exit if pin is out of scope
//  for (int i = 0; i < 3; i++)
//  {
//    if (pin & (1 << i))
//      digitalWrite(selectPins[i], HIGH);
//    else
//      digitalWrite(selectPins[i], LOW);
//  }
//}
