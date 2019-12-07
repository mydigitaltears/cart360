int sensorPin = A0;   //for analog input
//remember you put the switch towards 'A' not 'D' for analog input

void setup()  {
  Serial.begin(9600);
  //default is 9600, change after opening the serial plotter
 }

void loop()  {
  int heartValue = analogRead(sensorPin);    //reading the analog value
  Serial.println(heartValue);   //printing the value tot the serial plotter
  delay(5);
  }
