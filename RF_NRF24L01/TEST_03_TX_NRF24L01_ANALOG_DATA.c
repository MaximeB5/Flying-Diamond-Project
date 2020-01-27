/*
 * Flying Diamond Project - Test Repository
 * Purpose      : Test code for the NRF24L01 module (Tx only) with a potentiometer.
 * File name    : TEST_03_TX_NRF24L01_ANALOG_DATA.c
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
    VCC    ->   3.3V
    CE     ->   D9
    CSN    ->   D10
    MOSI   ->   D11
    MISO   ->   D12
    CLK    ->   D13

    POTENTIOMETER   ->  A0
*/

/**************************************************/

#include <SPI.h>
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

const uint64_t my_radio_pipe = 0xE8E8F0F0E1LL;    // This ID code must be the same as in the transmitter.

RF24 radio(9, 10);                                // CE and CSN pins.

const int potentiometer = A0;                     // Potentiometer pin set at Analog Input 0.

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

  sent_data.data = 0; // default value (can be seen like a reset)

  pinMode(potentiometer, INPUT);

  delay(500); // init delay
}

/**************************************************/

void loop() {
    sent_data.data = analogRead(potentiometer);
    // Serial.print("Analog read : "); Serial.println(sent_data.data);  // default : set in comment since it's just for debugging
    radio.write(&sent_data, sizeof(Data_to_be_sent));
}