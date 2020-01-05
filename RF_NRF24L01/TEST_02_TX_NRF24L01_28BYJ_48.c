/*
 * Flying Diamond Project - Test Repository
 * Purpose      : Test code for the NRF24L01 module (Rx only) and the stepper motor 28BYJ-48
 * File name    : TEST_02_TX_NRF24L01_28BYJ_48.c
 */

/* Receiver code for the Arduino Radio control with PWM output.
 * 
 * Requirements : Install the NRF24 library to your IDE.
 *
 * This code has been written to be uploaded on the following targets : Arduino UNO, NANO, Pro mini (5V,16MHz).
 *
 * Connect a NRF24 module to it :
 
    Module // Arduino UNO,NANO
    
    GND    ->   GND
    Vcc    ->   3.3V
    CE     ->   D9
    CSN    ->   D10
    CLK    ->   D13
    MOSI   ->   D11
    MISO   ->   D12

This code receive 1 channels and prints the value on the serial monitor.
*/

/**************************************************/

#include <SPI.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

const uint64_t my_radio_pipe = 0xE8E8F0F0E1LL;    // This ID code must be the same as in the transmitter.

RF24 radio(9, 10);                                // CE and CSN pins.

// The sizeof this struct should not exceed 32 bytes (max size of data that can be send through the NRF24L01 module).
struct DataToBeSend {
  byte n1;
  byte n2;
  byte n3;
  byte n4;
};

DataToBeSend sData;

int stepNumber = 0;

/******************************/
/* Function */

void oneStep(bool dir) {
  if (dir)
  {
    switch(stepNumber) {
      case 0:
        sData.n1 = 1;
        sData.n2 = 0;
        sData.n3 = 0;
        sData.n4 = 0;
        radio.write(&sData, sizeof(DataToBeSend));
      break;

      case 1:
        sData.n1 = 0;
        sData.n2 = 1;
        sData.n3 = 0;
        sData.n4 = 0;
        radio.write(&sData, sizeof(DataToBeSend));
      break;

      case 2:
        sData.n1 = 0;
        sData.n2 = 0;
        sData.n3 = 1;
        sData.n4 = 0;
        radio.write(&sData, sizeof(DataToBeSend));
      break;

      case 3:
        sData.n1 = 0;
        sData.n2 = 0;
        sData.n3 = 0;
        sData.n4 = 1;
        radio.write(&sData, sizeof(DataToBeSend));
      break;
    }
  }
  else if (!dir)
  {
    switch(stepNumber) {
      case 0:
        sData.n1 = 0;
        sData.n2 = 0;
        sData.n3 = 0;
        sData.n4 = 1;
        radio.write(&sData, sizeof(DataToBeSend));
      break;

      case 1:
        sData.n1 = 0;
        sData.n2 = 0;
        sData.n3 = 1;
        sData.n4 = 0;
        radio.write(&sData, sizeof(DataToBeSend));
      break;

      case 2:
        sData.n1 = 0;
        sData.n2 = 1;
        sData.n3 = 0;
        sData.n4 = 0;
        radio.write(&sData, sizeof(DataToBeSend));
      break;

      case 3:
        sData.n1 = 1;
        sData.n2 = 0;
        sData.n3 = 0;
        sData.n4 = 0;
        radio.write(&sData, sizeof(DataToBeSend));
      break;
    }
  }

  ++stepNumber;

  if (stepNumber > 3) {
    stepNumber = 0;
  }
}

/**************************************************/

void setup() {
  Serial.begin(9600);

  // We reset the data.
  sData.n1 = 0;
  sData.n2 = 0;
  sData.n3 = 0;
  sData.n4 = 0;
 
  // Once again, begin and radio configuration.
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  //radio.setPALevel(RF24_PA_LOW);  
  radio.openWritingPipe(my_radio_pipe);
  
  delay(500);
}

/**************************************************/

void loop() {
  for (int i = 0; i < 1000; ++i)
  {
    oneStep(false);
    delay(2);
  }

  for (int i = 0; i < 1000; ++i)
  {
    oneStep(true);
    delay(2);
  }
}