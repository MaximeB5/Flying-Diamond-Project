/*
 * Flying Diamond Project - Test Repository
 * Purpose      : Test code for the NRF24L01 module (Tx only)
 * File name    : TEST_NRF24L01_TX_01.c
 */

/* Tranmsitter code for the Arduino Radio control with PWM output.
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
    MOSI   ->   D11
    MISO   ->   D12
    CLK    ->   D13
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

const uint64_t my_radio_pipe = 0xE8E8F0F0E1LL;    // This ID code must be the same as in the transmitter.

RF24 radio(9, 10);                                // CE and CSN pins.

const int buttonPin = 2;                          // Button

// The sizeof this struct should not exceed 32 bytes (max size of data that can be send through the NRF24L01 module).
struct Data_to_be_sent {
  byte data; 
};

Data_to_be_sent sent_data;

/**************************************************/

void setup() {
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(my_radio_pipe);

  sent_data.data = 0;

  pinMode(buttonPin, INPUT);

  delay(500);
}

/**************************************************/

void loop() {
  if(digitalRead(buttonPin) == HIGH){	// Button pushed
    sent_data.data = 1;
    radio.write(&sent_data, sizeof(Data_to_be_sent));
  }
  else {
    sent_data.data = 2;
    radio.write(&sent_data, sizeof(Data_to_be_sent));
  }
}