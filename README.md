# VeilleuseAttiny85

Lamp with 1 led, microphone and Photoresistor for day/night switch

## Components
  - Attiny 85 at 8 MHz
  - Photoresistor 500 Ohm with light and ~30k/40kOhm in darkness
    simple saturated common collector with C495 transistor NPN like schmitt trigger
  - Electret mic for sound detection
    simple ampl with transistor BC547C NPN
    
## Features
  - interruption connected to Photoresistor
  - interruption connected to analog comparison between mic level and adjustable ref voltage
  
## Librairies
  #include <avr/io.h>
  #include <avr/interrupt.h>
  #include <avr/sleep.h>
  #include <util/delay.h>

