#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <JeeLib.h>

int LDR = 0; // Select input pin for the photocell light sensor.
int val = 0; // Variable to store the value coming from the sensor.
int freq = 60000; //Frequency of readings (in ms)
//indicator led
int LED = 4;
int TRANS = 8;
//rf24
int CHANNEL = 1; //MAX 127
RF24 radio(9,10);
byte pipes[][6] = {"1Node","2Node"};
 
ISR(WDT_vect) { Sleepy::watchdogEvent(); }
 
void setup() {
  
  pinMode(LDR, INPUT); // Declare LDR as an input pin.
  pinMode(LED, OUTPUT); 
  pinMode(TRANS, OUTPUT); 

  digitalWrite(TRANS, HIGH);

  restartRadio();
}
 
void loop() {
  val = analogRead(LDR); // Read current value from the sensor.
  
  digitalWrite(TRANS, HIGH);
  Sleepy::loseSomeTime(100);
  digitalWrite(LED, HIGH);
  restartRadio();
  
  radio.write(&val , sizeof(int) ); //Send via radio
  
  digitalWrite(LED, LOW);
  digitalWrite(TRANS, LOW);
  Sleepy::loseSomeTime(freq);
}

void restartRadio(){
  radio.begin();        // Start up the radio
  radio.setChannel(CHANNEL);
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.setRetries(15,15);                // Max delay between retries & number of retries
  radio.openWritingPipe(pipes[1]);
  //radio.printDetails();                   // Dump the configuration of the rf unit for debugging
  radio.stopListening();
  //radio.setPALevel(RF24_PA_MAX);
}
