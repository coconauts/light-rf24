/*
Description:
  NRF24L01 server
  
Dependency: 
  RF24 for raspberry PI : https://github.com/TMRh20/RF24/tree/master/RPi
  Install using make && sudo make install
  
Documentation:
  RF24: https://github.com/TMRh20/RF24
  Example: http://hack.lenotta.com/arduino-raspberry-pi-switching-light-with-nrf24l01/
  Onefinestay example: https://github.com/onefinestay/looserver
  
How to run: 
  g++ -L/usr/local/lib/ -lstdc++ -lrt -lrf24-bcm rf24.cpp -o rf24.out
  
Harware configuration:

  NRF24L01:
  __________________
  |_1_| 2         ~ |
  | 3 | 4  [_]    ~ |
  | 5 | 6         ~ |
  | 7 | 8  (   )  ~ |
  ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ 
  Raspberry PI:
  
  1 -> 3.3v
  2 -> GND
  3 -> 22
  4 -> CS0
  5 -> SCLK
  6 -> MOSI
  7 -> MISO
  
*/

#include <iostream> //for usleep
#include <time.h> //for CLOCK_REALTIME
#include <RF24/RF24.h> //for radio
#include <stdio.h> //for printf

using namespace std;

// Setup for GPIO 22 CE and CE0 CSN with SPI Speed @ 8Mhz
RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);

// Radio pipe addresses for the 2 nodes to communicate.
const uint8_t pipes[][6] = {"1Node","2Node"};

int main(int argc, char** argv){
  timespec time;
  // for some reason read() reads 8 bytes, not 1, so make sure we allocate
  // enough memory; otherwise it scribbles over other memory
  int paylad[8];

  radio.begin();
  radio.setChannel(1);
  radio.setRetries(15,15);
  radio.printDetails();

  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);
  radio.startListening();

  while (1) {

    if ( radio.available() ) {      

      radio.read( paylad, sizeof(int) );
      clock_gettime(CLOCK_REALTIME, &time);
      printf("Received: %i at %i.%i \n",paylad[0],time.tv_sec,time.tv_nsec);
    }
    usleep(100 * 1000);
  } 
  return 0;
}