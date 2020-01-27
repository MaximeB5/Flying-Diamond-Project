/*
 * Flying Diamond Project - Test Repository
 * Purpose      : Test code for the NRF24L01 module (Rx only)
 * File name    : TEST_03_RX_NRF24L01_ANALOG_DATA.c
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
    VCC    ->   3.3V
    CE     ->   D9
    CSN    ->   D10
    MOSI   ->   D11
    MISO   ->   D12
    CLK    ->   D13
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
struct Received_data {
  byte data;
};

Received_data received_data;

/**************************************************/

void setup() {
  /*  Considering we're powering both Tx and Rx modules at the same time, we delay the Rx module in order to find
      the Tx module (got some issues without that trick : the Rx module wasn't finding the Tx module).
  */
  delay(5000);
  
  Serial.begin(9600);

  // We reset the received values.
  received_data.data = 0;
 
  // Once again, begin and radio configuration.
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);  
  radio.openReadingPipe(1, my_radio_pipe);
  
  // We start the radio comunication.
  radio.startListening();
}

/**************************************************/

unsigned long last_Time = 0;

void receive_the_data() {
  while ( radio.available() )
  {
    radio.read(&received_data, sizeof(Received_data));
    last_Time = millis(); // Here we receive the data.
  }
}

/**************************************************/

void loop() {
  receive_the_data();
  Serial.print("received data -> data : ");
  Serial.println(received_data.data);
  int inputDataForESC = map(received_data.data, 0, 1023, 0, 179); // We map the analog data received to be conformed with ESC data limits (0 = stop; 179 = max speed).
  Serial.print("input data mapped for the ESC : ");
  Serial.println(inputDataForESC);
  delay(500);
}