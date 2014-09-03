/*
Dependency: 
  * RF24 for arduino: https://github.com/TMRh20/RF24
    Copy all files to $arduino/libraries
  
Documentation:
  RF24: https://github.com/TMRh20/RF24
  Example: http://hack.lenotta.com/arduino-raspberry-pi-switching-light-with-nrf24l01/
  Onefinestay example: https://github.com/onefinestay/looserver
    
Harware configuration:

  NRF24L01:
  __________________
  |_1_| 2         ~ |
  | 3 | 4  [_]    ~ |
  | 5 | 6         ~ |
  | 7 | 8  (   )  ~ |
  ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ 
  Arduino:
  
  1 -> 3.3v
  2 -> GND
  3 -> D9
  4 -> D10
  5 -> D13
  6 -> D11
  7 -> D12

*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <JeeLib.h>

int LDR = 0; // Select input pin for the photocell light sensor.
int val = 0; // Variable to store the value coming from the sensor.
int freq = 60000; //Frequency of readings (in ms)
//indicator led
int LED = 4;
//rf24
int CHANNEL = 1; //MAX 127
RF24 radio(9,10);
byte pipes[][6] = {"1Node","2Node"};
 
ISR(WDT_vect) { Sleepy::watchdogEvent(); }
 
void setup() {
  
  pinMode(LDR, INPUT); // Declare LDR as an input pin.
  pinMode(LED, OUTPUT); 

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
 
void loop() {
  val = analogRead(LDR); // Read current value from the sensor.
  radio.powerUp();
  
  digitalWrite(LED, HIGH);
  
  radio.write(&val , sizeof(int) ); //Send via radio
  
  radio.powerDown();
  digitalWrite(LED, LOW);
  Sleepy::loseSomeTime(freq);
}