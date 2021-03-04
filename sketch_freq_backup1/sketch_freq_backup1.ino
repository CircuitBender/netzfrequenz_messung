#include <Adafruit_ADS1015.h>
#include <Wire.h>


//find out quelle amplitude de V en tout
//600 samples/sec

// Definitionen
Adafruit_ADS1115 ads;
const float multiplier = 0.1132;// 0.015625 8// 0.03125 4 //0.0625 2 // Gain Factor (4our) // changer????
float NowVoltage = 1000;   // evtl besser faktor 1000 und als integer speichern und am schluss / 1000 zu float
float LastVoltage = 1000;  // evtl besser faktor 1000 und als integer speichern und am schluss / 1000 zu float
const int thresh1 = 120; // Resolution ? 0.001 0.01 0.1 ??? -> changer .... siehe oben evtl auch zu integer in der selben groessenordnung aendern, wie XVoltage
const int thresh2 = 90; // Resolution ? 0.001 0.01 0.1 ??? -> changer .... siehe oben evtl auch zu integer in der selben groessenordnung aendern, wie XVoltage
boolean State = false;
unsigned long marker1 = 0;
// unsigned long marker2 = 0; // ?
unsigned long NowTime;
unsigned long LastTime;
unsigned long period;
float freq;
int OutPin = 7;


// Funktionsdefinitionen
// nur deklarieren ODER FUNKTION SCHREIBEN -> ob variablen (volatile)
//erst unten in der Funktion entstehen ODER ob sie in DEF GLOBAL deklariert wurden

//int InitState() {
//  NowVoltage = ads.readADC_Differential_0_1() * multiplier;
//  if (NowVoltage > thresh1 )
//}

// Setup
void setup() {
  Serial.begin(115200); // baudrate -> higher ? whats possible ?
  Serial.println("Baudrate at 115200");
  
  ads.setGain(GAIN_TWO);      // changer???    four gsi +/- 1.024V 1bit = 0.5mV ???
  ads.begin(); // Sampling Rate ADS ?? I2C Baudrate ??
  Serial.println("ADS1115 BEGIN");
  
  //NowTime = micros(); // millis();1000msec oder 1000000usec = 1sec
  pinMode(OutPin, OUTPUT);      // sets the digital pin 7 as input
  Serial.println("Pin7 Out");

  //NowVoltage = ads.readADC_SingleEnded(0) * multiplier;

  // initialisation function voltage read
  //Serial.println(ads.readADC_SingleEnded(0) * multiplier);
}


// MAIN LOOP
void loop() {
  // while jusk a une seconde, on compte tout
  // enable interrupts to read i2c data
  NowVoltage = ads.readADC_SingleEnded(0) * multiplier;

  // Serial.println(NowVoltage);
  //NowVoltage = ads.readADC_Differential_0_1() * multiplier; // Multiplier fraglich _> mehr rechenoperation -> zeit sparen
  // disable interrupts to read i2c data

  if ((NowVoltage > LastVoltage) && (NowVoltage < thresh1) && (NowVoltage > thresh2) && (State == false))  { // Conditions Syntax checken
    //Serial.print("LastTime "); 
    //Serial.println(LastTime); // spàter rausnehmen nach tests -> NOWTIME & VOLTAGE ?????
    //Serial.print("LastVoltage "); 
    //Serial.println(LastVoltage); // idem
    // NowTime = micros(); // millis();1000msec oder 1000000usec = 1sec

    marker1 = LastTime; // need initFunction  ou ca geregelt
    LastVoltage = NowVoltage;
   // LastTime = NowTime;
    State = true;
    Serial.println("COND1");
    digitalWrite(OutPin, HIGH);

    // return statements ??
  } else if ((NowVoltage > LastVoltage) && (NowVoltage < thresh1) && (State == true)) {
    LastVoltage = NowVoltage;
    // LastTime = NowTime;
    Serial.println("COND2");
    digitalWrite(OutPin, HIGH);


  } else if ((NowVoltage > LastVoltage) && (NowVoltage >= thresh1) && (State == true)) {
    LastVoltage = NowVoltage;
    // LastTime = NowTime;
    State = false;
    Serial.println("COND3");
    digitalWrite(OutPin, HIGH);

  } else {
   //falling
   LastVoltage = NowVoltage;
   // LastTime = NowTime;
   State = false;
   Serial.println("COND4_ELSE");
   digitalWrite(OutPin, LOW);

  }
// send data hier ou oben?
/*  if (marker1 != 0) {
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
  //  delay(1);   
   
  /*
  //float maximum = max();
  // Time Max abspeichern
  time1 = millis() - time_check  ..... max ()
  // Time Max 2 - Time Max 1 = Periode
  float period = time2-time1
  // Frequenz = 1/ Periode
  frequency = 1/period
  //Print Frequenz
  Serial.println(Frequenz)*/
}
