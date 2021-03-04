#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1015 ads1015;

int16_t adc0;
int inPin = 7;   // pushbutton connected to digital pin 7
int val = 0;     // variable to store the read value
bool State = false;
unsigned long marker1 = 0;
float freq = 0;
long NowTime = 0;
float period;

void setup(void)
{
  Serial.begin(9600); // hoeher setzen ? 115200
  Serial.println("Hello!");
  
  Serial.println("Single-ended readings from AIN0 with >3.0V comparator");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV)");
  //Serial.println("Comparator Threshold: 1000 (3.000V)"); //korrekter Faktor fuer 0.3V
  Serial.println("Comparator Threshold: 100 (0.300V)"); //korrekter Faktor fuer 0.3V

  pinMode(inPin, INPUT);      // sets the digital pin 7 as input

  ads1015.begin();
  
  // Setup 3V comparator on channel 0
  ads1015.startComparator_SingleEnded(0, 100);
}

void loop(void)
{

  // Comparator will only de-assert after a read
  adc0 = ads1015.getLastConversionResults();
  Serial.print("AIN0: "); Serial.println(adc0);
  //val = digitalRead(inPin);   // read the input pin

  NowTime = micros(); // millis();1000msec oder 1000000usec = 1sec

  if ((digitalRead(inPin) == HIGH) && (State == false))  { 
    Serial.println(NowTime); 
    Serial.print("HIGH ");
    
    if (marker1 != 0){     
      period = NowTime- marker1;
      freq = 1000000 / period;
      Serial.println(freq); 
      Serial.println(NowTime);
    }
    
    marker1 = NowTime; // need initFunction  ou ca geregelt
    State = true;
    
    // return statements ??
    // high nach dem ersten switch
  //} else if ((digitalRead(inPin) == HIGH) && (State == true)) {
  //  NowTime = NowTime;
  //} else if ((digitalRead(inPin) == LOW) && (State == true)) {
  // NowTime = NowTime;
  //  State = false;
  
  } else {
    State = false;
  }

}
