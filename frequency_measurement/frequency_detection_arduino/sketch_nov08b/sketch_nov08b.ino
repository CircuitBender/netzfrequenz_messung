#include <Adafruit_ADS1015.h>
#include <Wire.h>

Adafruit_ADS1115 ads;

//find out quelle amplitude de V en tout


// Definitionen

const float multiplier = 0.0625; // Gain Factor (TWO) // changer????

float NowVoltage = 0;   // evtl besser faktor 1000 und als integer speichern und am schluss / 1000 zu float
float LastVoltage = 0;  // evtl besser faktor 1000 und als integer speichern und am schluss / 1000 zu float
const float thresh1 = 0.3; // Resolution ? 0.001 0.01 0.1 ??? -> changer .... siehe oben evtl auch zu integer in der selben groessenordnung aendern, wie XVoltage
boolean State = false;
unsigned long marker1 = 0;
// unsigned long time2 = 0; // ?
long NowTime = 0;
long LastTime = 0;


// Funktionsdefinitionen
// nur deklarieren ODER FUNKTION SCHREIBEN -> ob variablen (volatile)
//erst unten in der Funktion entstehen ODER ob sie in DEF GLOBAL deklariert wurden

// Setup
void setup() {
  Serial.begin(115200); // baudrate -> higher ? whats possible ?
  ads.setGain(GAIN_TWO);      // changer???    four gsi +/- 1.024V 1bit = 0.5mV ???
  ads.begin(); // Sampling Rate ADS ?? I2C Baudrate ??
  // initialisation function voltage read
}


// MAIN LOOP
void loop() {
  // while jusk a une seconde, on compte tout
  
  // read time
  NowTime = micros(); // millis();1000msec oder 1000000usec = 1sec
  NowVoltage = ads.readADC_Differential_0_1() * multiplier; // Multiplier fraglich _> mehr rechenoperation -> zeit sparen

  if ((NowVoltage > LastVoltage && < thresh1) && (State == false))  { // Conditions Syntax checken
    Serial.println(LastTime); // spàter rausnehmen nach tests -> NOWTIME & VOLTAGE ?????
    Serial.print(LastVoltage); // item
    /* 
      
     if (marker1 != 0) {
      period = NowTime- marker1;
      freq = 1 / period;
      Serial.println(freq);
      marker1 = NowTime;
      else 
      marker1 = LastTime; // need initFunction  ou ca geregelt

      
    }
    */
    LastVoltage = NowVoltage;
    LastTime = NowTime;
    State = true;
    
    // return statements ??
    } 
    else if ((NowVoltage > LastVoltage && < thresh1) && (State == true)) {
    LastVoltage = NowVoltage;
    LastTime = NowTime;
    } 
    else if ((NowVoltage > LastVoltage && >= thresh1) && (State == true)) {
    LastVoltage = NowVoltage;
    LastTime = NowTime;
    State = false;
  } else {
   //falling
   LastVoltage = NowVoltage;
   LastTime = NowTime;
  }

  
  //Serial.println(voltage);
  //Serial.print(time_check)

  //float maximum = max();
  /*// Time Max abspeichern
  time1 = millis() - time_check  ..... max ()
  // Time Max 2 - Time Max 1 = Periode
  float period = time2-time1
  // Frequenz = 1/ Periode
  frequency = 1/period
  //Print Frequenz
  Serial.println(Frequenz)*/
}

//int InitState() {
//  NowVoltage = ads.readADC_Differential_0_1() * multiplier;
//  if (NowVoltage > thresh1 )
//}
