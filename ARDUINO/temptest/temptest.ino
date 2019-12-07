#define PIN_SENSOR A1
#define PIN_SWITCH 9
 
float target = 30;
int del = 0;
void setup()
{
  pinMode(PIN_SENSOR, INPUT);
  pinMode(PIN_SWITCH, OUTPUT);
 
  Serial.begin(9600);
}
 
//float getTemperature() {
//  float data = analogRead(PIN_SENSOR);
//  return (5.0 * data * 100.0) / 1024.0; // Celsius
//}
 
void loop()
{
  // Temperature read
//  float c = getTemperature();
//  Serial.print("Temperature: ");
//  Serial.println(c);
 
  // Regulation
  
  if (del<5)
  {
    digitalWrite(PIN_SWITCH, LOW);
    Serial.println("\tHeater OFF");
    del++;
  } 
  if (del>4 && del<50) {
    digitalWrite(PIN_SWITCH, HIGH);
    Serial.println("\tHeater ON");
    del++;
  }
  if (del==50){
    del=0;
    Serial.print("reset");
  }
  Serial.println(del);
  delay(1000);
}
