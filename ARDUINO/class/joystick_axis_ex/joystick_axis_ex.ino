#include <Joystick.h>

const int pinToButtonMap = 10;
Joystick_ Joystick;

int scale = 3;
float speedScale = 1023;

float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void setup() {
  Joystick.begin();
}

void loop() {
  int rawX = analogRead(A0);
  int rawY = analogRead(A1);
  int rawZ = analogRead(A2);
  
  float scaledX, scaledY, scaledZ; // Scaled values for each axis
  scaledX = mapf(rawX, 280, 400, 0, speedScale); // 3.3/5 * 1023 =~ 675
  scaledY = mapf(rawY, 280, 400, 0, speedScale);
  scaledZ = mapf(rawZ, 280, 400, 0, speedScale);
  
  Joystick.setYAxis(constrain(speedScale-scaledY, 0, 1023));
  Joystick.setXAxis(constrain(scaledZ, 0, 1023));
  delay(20);
}
