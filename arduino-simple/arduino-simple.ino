#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int CHANNEL = 1; //MAX 127
RF24 radio(9,10);
byte pipes[][6] = {"1Node","2Node"};

void setup() {
  Serial.begin(9600);
  Serial.println("Setup radio\n\r");

  // Setup and configure rf radio
  radio.begin();                          // Start up the radio
  radio.setChannel(CHANNEL);
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.setRetries(15,15);                // Max delay between retries & number of retries
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging
  radio.stopListening();
}

void loop(void){
  radio.powerUp();
  int time = (int) millis();
  Serial.println("Sending message");
  radio.write(&time , sizeof(int) );
  radio.powerDown(); 
  delay(1000);
}