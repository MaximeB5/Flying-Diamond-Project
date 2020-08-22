# Flying Diamond Project
Test codes for the modules

#----------------------------------------------------------------------------------------------------------------------------------

This repository has no other purpose than to give test codes for the modules used in the 'Flying Diamond Project'.
The final version of the codes used for this project will be placed in the directory nammed Final.

#----------------------------------------------------------------------------------------------------------------------------------

List of modules :
  - RF modules :
    - NRF24L01
    
  - Motor modules :
    - Stepper motor 28BYJ 48
    - Brushless motor #REF?
    
  - Ultrasonic sensors :
    - HC SR04
#----------------------------------------------------------------------------------------------------------------------------------

List of codes :
  - RF modules :
    - NRF24L01 :
      - TEST_00_RX_NRF24L01.c (generic test)
      - TEST_00_TX_NRF24L01.c (generic test)
      - TEST_01_RX_NRF24L01.c (receiving data from a push button)
      - TEST_01_TX_NRF24L01.c (transmitting data with a push button)
      - TEST_02_RX_NRF24L01_28BYJ_48.c (receiving hard coded data to control a stepper motor)
      - TEST_02_TX_NRF24L01_28BYJ_48.c (transmitting hard coded data to control a stepper motor)
      - TEST_03_RX_NRF24L01_ANALOG_DATA (receiving analog data and mapping them for the ESC used to control the brushless motor)
      - TEST_03_TX_NRF24L01_ANALOG_DATA (transmitting analog data from a potentiometer)
    
  - Motor modules :
    - Stepper motor 28BYJ-48
      - TEST_STEPPER_MOTOR_01.c (basic test, run the motor in one direction then in the other)
      
  - Ultrasonic sensors :
    - HC SR04
        - HC_SR04_Ultrasonic_Sensor (send an eight cycle sonic burst at 40 kHZ during 10µs and then get the echo if it exists. Repeat this every 500ms)
      
#----------------------------------------------------------------------------------------------------------------------------------

Updated on 08/22/2020.
