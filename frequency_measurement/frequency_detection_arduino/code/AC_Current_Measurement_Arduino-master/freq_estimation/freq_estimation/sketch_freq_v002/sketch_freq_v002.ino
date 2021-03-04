#include <Adafruit_ADS1015.h>
#include <Wire.h>

// Sampling Rate ?? 600 samples/sec

// DEFINITIONS:
//ADS115
Adafruit_ADS1115 ads;
const float multiplier = 0.1132;// 0.015625 8// 0.03125 4 //0.0625 2 // Gain Factor (4our) // changer????
float NowVoltage = 1000;   // evtl besser faktor 1000 und als integer speichern und am schluss / 1000 zu float
float LastVoltage = 1000;  // evtl besser faktor 1000 und als integer speichern und am schluss / 1000 zu float
const int thresh1 = 120; // Resolution ? 0.001 0.01 0.1 ??? -> changer .... siehe oben evtl auch zu integer in der selben groessenordnung aendern, wie XVoltage
const int thresh2 = 200; // Resolution ? 0.001 0.01 0.1 ??? -> changer .... siehe oben evtl auch zu integer in der selben groessenordnung aendern, wie XVoltage
boolean State = false;
//TIME
unsigned long baudrate = 115300;
unsigned long i2c_baudrate = 100000;
unsigned long marker1 = 0;
unsigned long NowTime;
unsigned long LastTime;
unsigned long period;
float freq;
// PINS
// OUT
int OutPin = 7;


// FUNCTION/METHOD DECLARATIONS

// Setup
void setup() {
  // baudrate
  Serial.begin(baudrate); 
  Serial.print("Baudrate at ");
  Serial.println(baudrate);
  //ADS11X5
  ads.setGain(GAIN_TWO);      // changer???    four gsi +/- 1.024V 1bit = 0.5mV ???
  ads.begin(); // Sampling Rate ADS ?? I2C Baudrate ??
  // ADS1115 Write Register to obtain 3300Samples per Second
  //Wire.beginTransmission(byte(0x48));
  //Wire.write(byte(0x00C0));

  Wire.setClock(i2c_baudrate); // Setting I2C Baudrate to 400khz
  Serial.println("ADS1115 BEGIN");

  // Digital Pins
  pinMode(OutPin, OUTPUT);      // sets the digital pin 7 as input
  Serial.println("Digital Pin 7 Out");

  // Getting Nowtime
  NowTime = micros();
  Serial.print("NowTime ");
  Serial.println(NowTime);

  // Getting NowVoltage
  NowVoltage = ads.readADC_SingleEnded(0) * multiplier;
  Serial.print("NowVoltage ");
  Serial.println(NowVoltage);
}


// MAIN LOOP
void loop() {
  interrupts();
  NowVoltage = ads.readADC_SingleEnded(0) * multiplier;
  if (NowVoltage < 110) {
      NowVoltage = ads.readADC_SingleEnded(0) * multiplier;
  }
  else if (NowVoltage == LastVoltage) {
      NowVoltage = ads.readADC_SingleEnded(0) * multiplier;
  }
  else if (NowVoltage > 110) {
      Serial.print("NowVoltage ");
      Serial.println(NowVoltage);  
  }



if ((NowVoltage > LastVoltage) && (NowVoltage > thresh1) && (NowVoltage < thresh2) && (State == false))  { // Conditions Syntax checken
   // noInterrupts();
    NowTime = micros(); // millis();1000msec oder 1000000usec = 1sec
    marker1 = NowTime;  
    State = true;
    Serial.println("COND1_RISING_EDGE_BETWEEN_THRESH1_THRESH2");
    digitalWrite(OutPin, HIGH);
//    interrupts();
    } 
    else if ((NowVoltage > LastVoltage) && (NowVoltage > thresh2) && (State == true)) { //NowVoltage < thresh1 originally
//    noInterrupts();
    LastVoltage = NowVoltage;
    Serial.println("COND2_RISING");
    digitalWrite(OutPin, HIGH);
//    interrupts();
    } else if ((NowVoltage < LastVoltage) && (NowVoltage > thresh2) && (State == true)) {
 //   noInterrupts();
    LastVoltage = NowVoltage;
    //State = false;
    Serial.println("COND3_FALLING");
    digitalWrite(OutPin, HIGH);
//    interrupts();
    } else if ((NowVoltage < LastVoltage) && (NowVoltage <= thresh1) && (State == true)) {
//    noInterrupts();
    LastVoltage = NowVoltage;
    State = false;
    Serial.println("COND4_FALLING_LOWER_THAN_THRESH1");
      if (NowVoltage < 30) {
      NowVoltage = 0;
      }
    digitalWrite(OutPin, LOW);
//    interrupts();
    } else {
//    noInterrupts();
      State = false;
      LastVoltage = NowVoltage;
    //Serial.println("COND5_ELSE");
      digitalWrite(OutPin, LOW);
//    interrupts();
}
//  noInterrupts();
 /*if (marker1 != 0) {
        // send data, ou selon interrupts on regarder
        period = (LastTime - marker1); // in microseconds
        freq = 1000000 / period;
        Serial.print("Freq ");
        Serial.println(freq);
        Serial.print("LastTime ");
        Serial.println(LastTime);
        Serial.print("marker1 ");
        Serial.println(marker1);
      }
 */
 //  interrupts();   
} // END MAIN LOOP
