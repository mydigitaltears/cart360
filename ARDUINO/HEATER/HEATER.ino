#define MOSFET 6
unsigned long timed;
unsigned long previousMillis = 0;
unsigned long interval = 5000;
int heaterState = false;
void setup() {
  // put your setup code here, to run once:
  pinMode(MOSFET, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  timed = millis();
  //Serial.println(timed);
  if (timed - previousMillis >= interval){
    previousMillis = timed;
    if(!heaterState){
      heaterState = true;
      Serial.println(heaterState);
    }
    else if(heaterState){
      heaterState = false;
      Serial.println(heaterState);
    }
  }
  if(heaterState){
    analogWrite(MOSFET, 255);
  }
  else if(!heaterState){
    analogWrite(MOSFET, 0);
  }
}
