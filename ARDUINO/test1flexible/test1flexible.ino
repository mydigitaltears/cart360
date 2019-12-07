int sensorPin = A0; // define sensor port (analog A0)
int value = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(sensorPin);
  Serial.println(value);
}
