#include <Keyboard.h> // library to simulate keyboard events
int sensorPin = A0; // define sensor port (analog A0)
int value = 0;
int threshold = 320;
void setup() {
 // put your setup code here, to run once:
 Keyboard.begin();
 Serial.begin(9600);
 }                                
void loop() {
 // put your main code here, to run repeatedly:
 value = analogRead(sensorPin);
 Serial.println(value);                      
 if(value > threshold){                           
//   Keyboard.press('');
   Serial.println("high");
 }                
 else {                                                                                                      
   Keyboard.releaseAll();
 }                                                           
 delay(10);                                                            
}

                                                                                
