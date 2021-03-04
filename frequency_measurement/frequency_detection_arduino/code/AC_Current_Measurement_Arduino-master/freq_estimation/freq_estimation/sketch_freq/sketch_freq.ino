#include <Adafruit_ADS1015.h>
#include <Wire.h>

Adafruit_ADS1115 ads;

//600 samples/sec

// Definitionen

const float multiplier = 0.1132;// 0.015625 8// 0.03125 4 //0.0625 2 // Gain Factor (4our) // changer????

float NowVoltage = 0;   // evtl besser faktor 1000 und als integer speichern und am schluss / 1000 zu float
float LastVoltage = 0;  // evtl besser faktor 1000 und als integer speichern und am schluss / 1000 zu float
const float thresh1 = 50; // Resolution ? 0.001 0.01 0.1 ??? -> changer .... siehe oben evtl auch zu integer in der selben groessenordnung aendern, wie XVoltage
bool State = false;
unsigned long marker1 = 0;
unsigned long NowTime;
unsigned long LastTime;
unsigned long period;
float freq;


//int InitState() {
//  NowVoltage = ads.readADC_Differential_0_1() * multiplier;
//  if (NowVoltage > thresh1 )
//}

void setup() {
  Serial.begin(115200); // baudrate -> higher ? whats possible ?
  ads.setGain(GAIN_TWO);
  ads.begin(); // Sampling Rate ADS ?? I2C Baudrate ??
  
  //NowTime = micros(); // millis();1000msec oder 1000000usec = 1sec
  // initialisation function voltage read
}


// MAIN LOOP
void loop() {
  // while jusk a une seconde, on compte tout
  // enable interrupts to read i2c data
  
  NowTime = micros(); // millis();1000msec oder 1000000usec = 1sec
  NowVoltage = ads.readADC_SingleEnded(0) * multiplier;
  // Serial.println(ads.readADC_SingleEnded(0) * multiplier);
  Serial.println(NowVoltage);
  
  //NowVoltage = ads.readADC_Differential_0_1() * multiplier; // Multiplier fraglich _> mehr rechenoperation -> zeit sparen
  // disable interrupts to read i2c data

  if ((NowVoltage > LastVoltage) && (NowVoltage < thresh1) && (State == false))  { // Conditions Syntax checken
    //Serial.print("LastTime "); 
    //Serial.println(LastTime); // spàter rausnehmen nach tests -> NOWTIME & VOLTAGE ?????
    //Serial.print("LastVoltage "); 
    //Serial.println(LastVoltage); // idem
    if (marker1 != 0) {
      // send data, ou selon interrupts on regarder
      period = (LastTime - marker1);
      freq = 1000000 / period;
      Serial.print("Freq "); 
      Serial.println(freq); 
      Serial.print("LastTime ");
      Serial.println(LastTime);
      Serial.print("marker1 ");
      Serial.println(marker1); 
      }
    marker1 = LastTime; // need initFunction  ou ca geregelt
    LastVoltage = NowVoltage;
    LastTime = NowTime;
    State = true;

    // return statements ??
  } else if ((NowVoltage > LastVoltage) && (NowVoltage < thresh1) && (State == true)) {
    LastVoltage = NowVoltage;
    LastTime = NowTime;

  } else if ((NowVoltage > LastVoltage) && (NowVoltage >= thresh1) && (State == true)) {
    LastVoltage = NowVoltage;
    LastTime = NowTime;
    State = false;

  } else {
   //falling
   LastVoltage = NowVoltage;
   LastTime = NowTime;
   //State = false;
  }
// send data hier ou oben?

}
