#define RED_PIN 11
#define GREEN_PIN 10
#define BLUE_PIN 9
#define POT_PIN A0
void setup() {
  // put your setup code here, to run once:
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int potVal = analogRead(POT_PIN);
  Serial.println(potVal);
  analogWrite(RED_PIN,125);
  analogWrite(GREEN_PIN,125);
  analogWrite(BLUE_PIN,potVal);
//  delay(500);
//  digitalWrite(LED_PIN,0);
//  delay(500);
}
