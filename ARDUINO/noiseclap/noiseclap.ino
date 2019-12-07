#include <Keyboard.h> // library to simulate keyboard events
int sensorPin = A0; // define sensor port (analog A0)
int value = 0;
int treshold = 320;
void setup() {
 // put your setup code here, to run once:
 Keyboard.begin();                  
 Serial.begin(9600);       
}                                 
void loop() {          
 // put your main code here, to run repeatedly:
 value = digitalRead(sensorPin);
 Serial.println(value);                                             
 if(value > treshold){
   //Keyboard.press(' ');
   //Serial.println("clap!");
 }
 else {
   Keyboard.releaseAll();
 }
 delay(1000);
}                                                                                                                                                                                                                                              
