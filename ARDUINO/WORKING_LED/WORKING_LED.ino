/*
  ShiftRegister74HC595 - Library for simplified control of 74HC595 shift registers.
  Created by Timo Denk (www.timodenk.com), Nov 2014.
  Additional information is available at http://shiftregister.simsso.de/
  Released into the public domain.
*/
int inPin = A0;
//int sensorValue = 0;

unsigned long timed;
unsigned long previousMillis = 0;
unsigned long interval = 1000;
int heaterState = false;
boolean ledState = false;

#include <ShiftRegister74HC595.h>
#include "DFRobot_Heartrate.h"
DFRobot_Heartrate heartrate(DIGITAL_MODE);
// create a global shift register object
// parameters: (number of shift registers, data pin, clock pin, latch pin)
ShiftRegister74HC595 sr (1, 5, 4, 3); 
 
void setup() { 
  Serial.begin(9600);
  pinMode(inPin, INPUT);
}

void loop() {
  uint8_t rateValue;
  heartrate.getValue(inPin);
  rateValue = heartrate.getRate(); ///< Get heart rate value 
  if(rateValue)  {
    Serial.println(rateValue);
    //if(rateValue == 80){
      sr.setAllHigh();

      //sr.setAllLow();
    //}
  }
  else {
    sr.setAllLow();
  }
        delay(20);
//  delay(20);
//  sensorValue = digitalRead(inPin);
//  Serial.println(sensorValue);
//  if(sensorValue == HIGH){
//    if(ledState == false){
//      sr.setAllHigh();
//      ledState == true;
//    }
//  }
//  else {
//    sr.setAllLow();
//    ledState = false;
//  }
 
//  timed = millis();
//  if (timed - previousMillis >= interval){
//    previousMillis = timed;
//    if(!heaterState){
//      heaterState = true;
//    }
//    else if(heaterState){
//      heaterState = false;
//    }
//  }
//  if(heaterState){
//    sr.setAllHigh();
//  }
//  else if(!heaterState){
//    sr.setAllLow();
//  }
}
