#include <Adafruit_ADS1015.h>
#include <ADS1115_WE.h>
#include <Wire.h>

Adafruit_ADS1115 ads;

const float FACTOR = 5; //20A/1V from teh CT

const float multiplier = 0.0625;

void setup() {
  Serial.begin(9600);

  ads.setGain(GAIN_TWO);      // four gsi +/- 1.024V 1bit = 0.5mV
  ads.begin();

}

void printMeasure(String prefix, float value, String postfix)
{
  Serial.print(prefix);
  Serial.print(value, 3);
  Serial.println(postfix);
}

void loop() {
  float currentRMS = getcurrent();

  printMeasure("Irms: ", currentRMS, "A");
  delay(1000);

}

float getcurrent()
{
  float voltage;
  float current;
  float sum = 0;
  long time_check = millis();
  int counter = 0;

  while (millis() - time_check < 1000)
  {
    voltage = ads.readADC_Differential_0_1() * multiplier;
    current = voltage * FACTOR;
    //current /= 1000.0;

    sum += sq(current);
    counter = counter + 1;
  }

  current = sqrt(sum / counter);
  return (current);
}
