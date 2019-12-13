#include <RFM69.h>
#include <SPI.h>
#include <SPIFlash.h>
#include <ShiftRegister74HC595.h>
#include "DFRobot_Heartrate.h"
#include "Arduino.h"

// Addresses for this node. CHANGE THESE FOR EACH NODE!

#define NETWORKID     0   // Must be the same for all nodes
#define MYNODEID      2   // My node ID
#define TONODEID      1   // Destination node ID

// RFM69 frequency, uncomment the frequency of your module:

//#define FREQUENCY   RF69_433MHZ
#define FREQUENCY     RF69_915MHZ

// AES encryption (or not):

#define ENCRYPT       false // Set to "true" to use encryption
#define ENCRYPTKEY    "TOPSECRETPASSWRD" // Use the same 16-byte key on all nodes

// Use ACKnowledge when sending messages (or not):

#define USEACK        true // Request ACKs or not

// Packet sent/received indicator LED (optional):

#define LED           9 // LED positive pin
#define GND           8 // LED ground pin
#define MOSFET 6

// Pulse meter connected to any Analog pin
#define sensorPin A2
#define inPin A0
// Create a library object for our RFM69HCW module:

RFM69 radio;

int tempVal = 0;
int localRate = 0;
int flexInVal = 0;
char buff[50];
int flexHPeak = 0;
int flexLPeak = 1023;
int flexAv = 0;
int sendDelay = 0;
int ran = 0;

float val = 0;
int ledFl = 0;
unsigned long timed;
unsigned long previousMillis = 0;
unsigned long timed2;
unsigned long previousMillis2 = 0;
unsigned long interval = 1333;
boolean ledState = false;

DFRobot_Heartrate heartrate(DIGITAL_MODE);
// create a global shift register object
// parameters: (number of shift registers, data pin, clock pin, latch pin)
ShiftRegister74HC595 sr (1, 5, 3, 4); 

void setup()
{
  // Inbuilt LED
  pinMode(MOSFET, OUTPUT);
  
  // Open a serial port so we can send keystrokes to the module:

  Serial.begin(9600);
  Serial.print("Node ");
  Serial.print(MYNODEID,DEC);
  Serial.println(" ready");  

  // Initialize the RFM69HCW:

  radio.initialize(FREQUENCY, MYNODEID, NETWORKID);
  radio.setHighPower(); // Always use this for RFM69HCW

  // Turn on encryption if desired:

  if (ENCRYPT)
    radio.encrypt(ENCRYPTKEY);
}

void loop()
{
  // Set up a "buffer" for characters that we'll send:
  static char sendbuffer[62];
  static int sendlength = 0;

   // SENDING

  // In this section, we'll gather serial characters and
  // send them to the other node if we (1) get a carriage return,
  // or (2) the buffer is full (61 characters).

  // If there is any serial input, add it to the buffer:

  if (Serial.available() > 0)
  {
    char input = Serial.read();

    if (input != '\r') // not a carriage return
    {
      sendbuffer[sendlength] = input;
      sendlength++;
    }

    // If the input is a carriage return, or the buffer is full:

    if ((input == '\r') || (sendlength == 61)) // CR or buffer full
    {
      // Send the packet!


      Serial.print("sending to node ");
      Serial.print(TONODEID, DEC);
      Serial.print(", message [");
      for (byte i = 0; i < sendlength; i++)
        Serial.print(sendbuffer[i]);
      Serial.println("]");

      // There are two ways to send packets. If you want
      // acknowledgements, use sendWithRetry():

      if (USEACK)
      {
        if (radio.sendWithRetry(TONODEID, sendbuffer, sendlength))
          Serial.println("ACK received!");
        else
          Serial.println("no ACK received");
      }

      // If you don't need acknowledgements, just use send():

      else // don't use ACK
      {
        radio.send(TONODEID, sendbuffer, sendlength);
      }

      sendlength = 0; // reset the packet
    }
  }


  // RECEIVING

  // In this section, we'll check with the RFM69HCW to see
  // if it has received any packets:

  if (radio.receiveDone()) // Got one!
  {
    // Print out the information:

    Serial.print("received from node ");
    Serial.print(radio.SENDERID, DEC);
    Serial.print(", message [");

    // The actual message is contained in the DATA array,
    // and is DATALEN bytes in size:

    for (byte i = 0; i < radio.DATALEN; i++){
      Serial.print((char)radio.DATA[i]);
      buff[i]=(char)radio.DATA[i];
    }
 
    // RSSI is the "Receive Signal Strength Indicator",
    // smaller numbers mean higher power.

    Serial.print("], RSSI ");
    Serial.println(radio.RSSI);

    // Send an ACK if requested.
    // (You don't need this code if you're not using ACKs.)

    if (radio.ACKRequested())
    {
      radio.sendACK();
      Serial.println("ACK sent");
    }
  }

    tempVal = atoi(buff);
    if(tempVal > 200){
      flexInVal = tempVal;
    }
    if(tempVal < 200){
      localRate = tempVal;
    }
  if(flexInVal > flexHPeak && flexInVal < 1000){
    flexHPeak = flexInVal;
  }
  if(flexInVal < flexLPeak && flexInVal >50){
    flexLPeak = flexInVal;
  }
  int flexM = map(flexInVal,flexLPeak,flexHPeak,50,200);
  int flexC = constrain(flexM,50,200);
  //flexLPeak++;
  //flexHPeak--;
  analogWrite(MOSFET, flexC);

  // HB SENSOR SECTION:
uint8_t rateValue;
  heartrate.getValue(inPin);
  rateValue = heartrate.getRate(); ///< Get heart rate value 
  if(rateValue)  {
    if(rateValue == localRate){
      ledFl = 16;
      val = rateValue;
      val = val/60*1000;
    }
    //Serial.println(rateValue);
    char buff[50];
    sprintf(buff,"%d",rateValue);
    buff[2]=buff[1];
    buff[1]=buff[0];
    buff[0]=48;
    byte sendSize = strlen(buff);
    radio.send(TONODEID, buff, sendSize);
  }
//  int strtch = analogRead(A5);
//  if(sendDelay < 32){
//    flexAv += strtch;
//    sendDelay++;
//  }
//  if(sendDelay ==32){
//    Serial.println(flexAv/32);
//timed2 = millis();
//if (timed2 - previousMillis2 >= interval){
//    previousMillis2 = timed2;
//    char buff[50];
//    ran = 90;
//    sprintf(buff,"%d", ran);
//    buff[2]=buff[1];
//    buff[1]=buff[0];
//    buff[0]=48;
//    byte sendSize = strlen(buff);
//    //radio.send(TONODEID, buff, sendSize);
//}
//if (ran == localRate){
//    ledFl = 16;
//    val = ran;
//    val = val/60*1000;
//}

if(ledFl > 0){
    timed = millis();
    if (timed - previousMillis >= val/4){
      //Serial.println(val);
      previousMillis = timed;
      ledFl--;
      if(!ledState){
        ledState = true;
      }
      else if(ledState){
        ledState = false;
      }
    }
    if(ledState){
      sr.setAllHigh();
    }
    else if (!ledState){
      sr.setAllLow();
    }
  }
  else {
    sr.setAllLow();
  }

  int strtch = analogRead(sensorPin);
  if(sendDelay < 32){
    flexAv += strtch;
    sendDelay++;
  }
  if(sendDelay ==32){
    //Serial.println(flexAv/32);
    flexHPeak--;
    char buff[50];
    sprintf(buff,"%d",flexAv/32);
    byte sendSize = strlen(buff);
    radio.send(TONODEID, buff, sendSize);
    Serial.println(flexC);
    sendDelay = 0;
    flexAv=0;
  }
  delay(10);
}
