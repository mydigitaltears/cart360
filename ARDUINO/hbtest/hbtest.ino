#include <Wire.h> 
#define HBDEBUG(i)

int sensorPin = A0;

double alpha = 0.75;

int period = 100;

double change = 0.0;

double minval = 0.0;

const int delayMsec = 60; // 100msec per sample

void setup()
{
  Serial.begin(9600);

  delay(1000);
}

void loop() {
  static double oldValue = 0;
  static double oldChange = 0;
  int rawValue = analogRead(sensorPin);
  double value = alpha*oldValue+(1-alpha)*rawValue;

  oldValue = value;

  static int beatMsec = 0;
  int heartRateBPM = 0;
  if(heartbeatDetected(sensorPin,delayMsec)){
    heartRateBPM = 60000 / beatMsec;
    Serial.println(heartRateBPM);
    beatMsec = 0;
  }
  else{
    
  }
  delay(delayMsec);
  beatMsec += delayMsec;
}

bool heartbeatDetected(int IRSensorPin, int delay)
{
  static int maxValue = 0;
  static bool isPeak = false;
  int rawValue;
  bool result = false;

  rawValue = analogRead(IRSensorPin);
  rawValue *= (1000/delay);
  HBDEBUG(Serial.print(isPeak); Serial.print("p, "));
  HBDEBUG(Serial.print(rawValue); Serial.print("r, "));
  HBDEBUG(Serial.print(maxValue); Serial.print("m, "));

  // If sensor shifts, then max is out of whack.
  // Just reset max to a new baseline.

  if (rawValue * 4L < maxValue) {

    maxValue = rawValue * 0.8;

    HBDEBUG(Serial.print("RESET, "));

  }

  

  // Detect new peak

  if (rawValue > maxValue - (1000/delay)) {

    if (rawValue > maxValue) {

      maxValue = rawValue;

    }

    // Only return true once per peak.

    if (isPeak == false) {

      result = true;

      //Serial.print(result); Serial.print(",  *");

    }

    isPeak = true;

  } else if (rawValue < maxValue - (3000/delay)) {

    isPeak = false;

    maxValue-=(1000/delay);

 }
  HBDEBUG(Serial.print("\n"));
  return result;
}
