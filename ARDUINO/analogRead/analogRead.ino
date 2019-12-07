//int sensorPin = A0; 
int inPin = 7;
int sensorValue = 0;
int ledPin = 13; 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(inPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //sensorValue = analogRead(sensorPin);
  sensorValue = digitalRead(inPin);
  Serial.println(sensorValue);
  if(sensorValue == HIGH){
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
}
