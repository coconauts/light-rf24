#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <JeeLib.h>

#define LDR 0 // Select input pin for the photocell light sensor.
#define FREQ 60000 //Frequency of readings (in ms)

#define LED 4 //indicator led
#define TRANS 8 //transinstor pin (base) to reduce consumption while sleeping

int val = 0; // Variable to store the value coming from the sensor.

//rf24
#define CHANNEL 1 //MAX 127
RF24 radio(9,10);
byte pipes[][6] = {"1Node","2Node"};
 
ISR(WDT_vect) { Sleepy::watchdogEvent(); }

void setup() {
    
  pinMode(LDR, INPUT); // Declare LDR as an input pin.
  pinMode(LED, OUTPUT); 
  pinMode(TRANS, OUTPUT);  
}
 
void loop() {
  digitalWrite(TRANS, HIGH);
  val = analogRead(LDR); // Read current value from the sensor.
  digitalWrite(LED, HIGH);
  
  restartRadio();
  radio.write(&val , sizeof(int) ); //Send via radio
  stopRadio();
  
  digitalWrite(LED, LOW);
  digitalWrite(TRANS, LOW);
  Sleepy::loseSomeTime(FREQ);
}

void stopRadio(){
  
  radio.powerDown();
  
  pinMode(13, LOW);
  pinMode(12, LOW);
  pinMode(11, LOW);
  pinMode(10, LOW);
  pinMode(9, LOW);
}

void restartRadio(){
  radio.begin(); // Start up the radio
  radio.setChannel(CHANNEL);
  radio.setAutoAck(1);     // Ensure autoACK is enabled
  radio.setRetries(15,15); // Max delay between retries & number of retries
  radio.openWritingPipe(pipes[1]);
  //radio.printDetails();  // Dump the configuration of the rf unit for debugging
  radio.stopListening();
  //radio.setPALevel(RF24_PA_MAX);
}
