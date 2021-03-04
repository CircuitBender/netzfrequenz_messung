#include <Adafruit_ADS1015.h>
#include <Wire.h>

Adafruit_ADS1115 ads;


// Definitionen

const float multiplier = 0.1132;// 0.015625 8// 0.03125 4 //0.0625 2 // Gain Factor (4our) // changer????

float NowVoltage = 0;   // evtl besser faktor 1000 und als integer speichern und am schluss / 1000 zu float

void setup() {
  Serial.begin(115200); // baudrate -> higher ? whats possible ?
  ads.setGain(GAIN_TWO);
  ads.begin(); // Sampling Rate ADS ?? I2C Baudrate ??
}


// MAIN LOOP
void loop() {
  //NowTime = micros(); // millis();1000msec oder 1000000usec = 1sec
  NowVoltage = ads.readADC_SingleEnded(0) * multiplier;
  Serial.println(NowVoltage);


}
