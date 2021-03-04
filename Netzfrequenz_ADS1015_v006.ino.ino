////  FILE: Netzfrequenz_ADS1015_v005.ino
//  AUTHOR: Maria Sedykh für ETH Power Electronics Lab
// VERSION: 0.0.5
// PURPOSE: Netzfrequenz Messung
//    based on ADS_continuous.ino for the ADS1X15 Library by Rob.Tillaart v0.1.0

// INSTRUCTIONS (on your own risk)
// Split Core SCT013 5A/1V an L1 anschliessen
// L und K an LowPassFilter 332 Hz
// Halbwellengleichrichter (Half Bridge Rectifier)
// L an A0 des Ads1015 K an GND des ADS1015
// ADS1015 an Arduino anschliessen (siehe Adafruit Webseite)

#include "ADS1X15.h"
// choose you sensor
// ADS1013 ADS(0x48);
// ADS1014 ADS(0x48);
 ADS1015 ADS(0x48);
// ADS1113 ADS(0x48);
// ADS1114 ADS(0x48);
//ADS1115 ADS(0x48);

// Definitionen
int32_t baudrate = 115200;
const float multiplier = 0.0625;// 0.015625 8// 0.03125 4 //0.0625 2 // Gain Factor (4our) // 0.1132changer????
int32_t LastVoltage = 0;   // Integer Werte !! müssen konvertiert werden zu Voltage
int32_t NowVoltage = 0;   // Integer Werte !! müssen konvertiert werden zu Voltage
int32_t Threshold = 500;
bool Falling = false, Rising = false, Falling_Edge, Rising_Edge;
long TimeMS = 0, NowTimeFalling = 0, NowTimeRising = 0, LastTimeFalling = 0, LastTimeRising = 0, PeriodFalling = 0, PeriodRising =0;
float FrequencyFalling = 0, FrequencyRising = 0, Period;

void setup()
{
  Serial.begin(baudrate);
  /*Serial.println(" Baudrate");

  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);
  */

  ADS.begin();
  // Serial.println("ADS1015 BEGIN");
  delay(1000);
  ADS.setGain(8);      // Gain eight
  // Serial.println("GAIN_EIGHT");
  ADS.setDataRate(7);  // fast
  ADS.setMode(0);      // continuous mode
  ADS.readADC(0);      // first read to trigger
  delay(1000);
  Wire.setClock(400000);
  delay(1000);

}

void loop()
{
  NowVoltage = ADS.getLastValue(); // reading voltage as Bits
if (NowVoltage > Threshold){
  /*Serial.print("LastVoltage: "); 
  Serial.print(LastVoltage); 
  Serial.print(" ");
  Serial.print("NowVoltage: "); 
  Serial.print(NowVoltage); 
  Serial.print(" ");
  */
    if (NowVoltage < LastVoltage){
        // Serial.print(" Falling");
        if (Falling == false){
          Falling_Edge = true; 
          Rising_Edge = false; 
          // Falling = true;
          // Serial.print(" FALLING EDGE DETECTED! ");
          NowTimeFalling = micros();
          TimeMS = millis();
          PeriodFalling = NowTimeFalling - LastTimeFalling;
          Period = PeriodFalling; // Konvertierung Int to Float
          FrequencyFalling = 1000000 / Period;
          if ((FrequencyFalling < 60) && (FrequencyFalling > 40)) {
          // Serial.print(" FREQUENCY_FALLING: ");
          Serial.print(TimeMS);
          Serial.print(",");
          Serial.print(NowTimeFalling);
          Serial.print(",");
          Serial.println(FrequencyFalling);
          // Serial.println("/n");

          }
        }    
        Falling = true;
        Rising = false;
        // Serial.println(" ");
      } 
      else if (NowVoltage > LastVoltage) {
        // Serial.print(" Rising");
        if (Rising == false){
          Rising_Edge = true; 
          Falling_Edge = false;
          // Rising = true; 
          // Serial.print(" RISING EDGE DETECTED! ");
          /*NowTimeRising = micros();
          PeriodRising = NowTimeRising - LastTimeRising;
          FrequencyRising = 1000000 / PeriodRising;
          Serial.print(" FREQUENCY_FALLING: ");
          Serial.print(FrequencyRising); */
        } 
        Rising = true;
        Falling = false;
        // Serial.println(" ");
      }
  LastVoltage = NowVoltage;
  LastTimeFalling = NowTimeFalling;
  //LastTimeRising = NowTimeRising;
  }//ENDIF
} // END MAIN
// -- END OF FILE --
