#include <Mouse.h>
int scale = 3;
float mouseSpeed = 20.0;
void setup()
{
  Mouse.begin();
}
void loop()
{
  // Get raw accelerometer data for each axis
  int rawX = analogRead(A0);
  int rawY = analogRead(A1);
  int rawZ = analogRead(A2);
  float scaledX, scaledY, scaledZ; // Scaled values for each axis
  scaledX = mapf(rawX, 0, 675, -scale, scale); // 3.3/5 * 1023 =~ 675
  scaledY = mapf(rawY, 0, 675, -scale, scale);
  scaledZ = mapf(rawZ, 0, 675, -scale, scale);
  delay(10);
  Mouse.move(scaledZ * mouseSpeed, -scaledY * mouseSpeed, 0);
}

// Same functionality as Arduino's standard map function, except using floats
float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
