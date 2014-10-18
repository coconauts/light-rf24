#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <JeeLib.h>

#define LDR 0 // Select input pin for the photocell light sensor.
#define FREQ 60000 //Frequency of readings (in ms)

#define POWER 8 //power pin to reduce consumption while sleeping

int val = 0; // Variable to store the value coming from the sensor.

//rf24
#define DEVICE_ID 1
#define CHANNEL 1 //MAX 127
RF24 radio(9,10);
byte pipe[]= {"light"};
 
ISR(WDT_vect) { Sleepy::watchdogEvent(); }

#define MAX_SENSOR_VALUE 1023
#define MAX_RADIO_VALUE 254

void setup() {
    
  pinMode(LDR, INPUT); // Declare LDR as an input pin.
  pinMode(POWER, OUTPUT);  
}
 
void loop() {
  digitalWrite(POWER, HIGH);
  val = analogRead(LDR); // Read current value from the sensor.
  
  restartRadio();
  radio.write(&val , sizeof(val) ); //Send via radio
  stopRadio();
  
  digitalWrite(POWER, LOW);
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
  radio.openWritingPipe(pipe);
  radio.stopListening();
}