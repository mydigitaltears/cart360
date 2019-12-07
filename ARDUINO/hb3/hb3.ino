int ledPin=13;
int analogPin=0;
  
void setup()
{
  // The included LED of the Arduino (Digital 13), will be used as output here.
  pinMode(ledPin,OUTPUT);
    
  // Serial output initialization
  Serial.begin(9600);
  Serial.println(&amp;quot;Heartbeat detection example code&amp;quot;);
}
  
const int delayMsec = 60; // 100msec per sample
  
// The main program has two tasks: 
// - The LED will light up after detecting a heart beat
// - Calculating of the pulse and outputting of it at the serial out.
  
void loop()
{
  static int beatMsec = 0;
  int heartRateBPM = 0;
      Serial.println(rawValue);
  if (heartbeatDetected(analogPin, delayMsec)) {
    heartRateBPM = 60000 / beatMsec;
    // LED-output for the heart beat heart beat
    digitalWrite(ledPin,1);
  
    // Output of the serial data
    Serial.print(rawValue);
    Serial.print(&amp;quot;, &amp;quot;);
    Serial.println(heartRateBPM);
      
    beatMsec = 0;
  } else {
    digitalWrite(ledPin,0);
  }
  delay(delayMsec);
  beatMsec += delayMsec;
}
