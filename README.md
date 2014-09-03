This repository contains a few examples about how to send analog readings From Arduino to Raspberry via Radio (nRF24L01 aka RF24).

All details are here: http://coconauts.net/blog/2014/09/03/send-readings-from-arduino-to-raspberry-via-radio/

### Connecting the RF24 

Connecting the RF24 is not that hard if you follow any of the schemas below:

<img src="https://raw.githubusercontent.com/coconauts/light-rf24/master/schemas/arduino-simple.png" />

```
  __________________
  |_1_| 2         ~ |
  | 3 | 4  [_]    ~ |
  | 5 | 6         ~ |
  | 7 | 8  (   )  ~ |
  ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾ 
  NRF24L01    Arduino  Raspberry
  
  1           3.3v     3.3v
  2           GND      GND
  3           D9       22
  4           D10      CS0
  5           D13      SCLK
  6           D11      MOSI
  7           D12      MISO
```

### Coding the RF24

#### Arduino

First you need to download the RF24 libraries for Arduino, you can find them [here](https://github.com/TMRh20/RF24), just copy the whole folder into your Arduino libraries.

Once the libraries are copied, you can run any of theArduino scripts in this repo.

#### Raspberry

First, download the c++ library for your Raspberry PI available [here](https://github.com/TMRh20/RF24/tree/master/RPi) , install them with `make` and `make install`. 
You can also compile and test the examples.

Then compile and run the raspberry code using `g++ -lstdc++ -lrt -lrf24-bcm rf24.cpp -o rf24.out` and `./rf24.out`
