/*
 * Flying Diamond Project - Test Repository
 * Purpose      : Test code for the NRF24L01 module (Rx only) and the stepper motor 28BYJ-48
 * File name    : TEST_02_RX_NRF24L01_28BYJ_48.c
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

const int stepperPin_1 = 3;
const int stepperPin_2 = 4;
const int stepperPin_3 = 5;
const int stepperPin_4 = 6;

// The sizeof this struct should not exceed 32 bytes (max size of data that can be send through the NRF24L01 module).
struct ReceivedData {
  byte n1;
  byte n2;
  byte n3;
  byte n4;
};

ReceivedData rData;

/**************************************************/
/* Functions */

void cmdMotor(byte n1, byte n2, byte n3, byte n4) {
  n1 == 0 ? digitalWrite(stepperPin_1, LOW) : digitalWrite(stepperPin_1, HIGH);
  n2 == 0 ? digitalWrite(stepperPin_2, LOW) : digitalWrite(stepperPin_2, HIGH);
  n3 == 0 ? digitalWrite(stepperPin_3, LOW) : digitalWrite(stepperPin_3, HIGH);
  n4 == 0 ? digitalWrite(stepperPin_4, LOW) : digitalWrite(stepperPin_4, HIGH);
}


unsigned long last_Time = 0;

void receive_the_data() {
  while ( radio.available() )
  {
    radio.read(&rData, sizeof(rData));
    last_Time = millis(); // Here we receive the data.
  }
}

/**************************************************/

void setup() {
  delay(5000);  // Considering we're powering both Tx and Rx modules at the same time, we delay the Rx module in order he finds Tx without troubles (got some issues without that).
  
  Serial.begin(9600);

  // We reset the received values.
  rData.n1 = 0;
  rData.n2 = 0;
  rData.n3 = 0;
  rData.n4 = 0;
 
  // Once again, begin and radio configuration.
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  //radio.setPALevel(RF24_PA_LOW);  
  radio.openReadingPipe(1,my_radio_pipe);
  
  // We start the radio comunication.
  radio.startListening();
}

/**************************************************/

void loop() {
  receive_the_data();

  int checkSum = 0;
  checkSum = rData.n1 + rData.n2 + rData.n3 + rData.n4;

  if (checkSum == 1) {
    cmdMotor(rData.n1, rData.n2, rData.n3, rData.n4);
  }
  else {
    Serial.print("Error : checkSum = ");
    Serial.println(checkSum);
  }
}