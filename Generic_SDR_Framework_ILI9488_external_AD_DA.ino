
/*
 Jabuary 26 2023 ... SDR Generic Framework Beta Test with Hilbert filters 
  
  There is Hilbert filtering  on this release
  FIlter is 251 taps at 48 kHz with a bandwidth of 300Hz-3kHz
  Built on ......
  Arduino 2.0.03
  teensyduino 1.57
  
  Required Libraries ...
  
       ili9488_T3  https://github.com/mjs513/ILI9488_t3
       Openaudio https://github.com/chipaudette/OpenAudio_ArduinoLibrary
         
        si5351  NT7s Library available in your arduino ide library tool..
 
  
  Note the following pinouts have changed 
  
  for display portion
  teensy pin   Display
  13 sck       SCK
  12 miso      MISO
  11 mosi      MOSI
  10 CS        CS
   9 DC        DC
  14 Reset     Reset // reset has been added
   
   for touch portion
   teensy pin  Display
   13 SCK      t_CLK
   5           T_CS
   4           T_IRQ
   11 MOSI     T_DIN  
   12 MISO     R_D0
  
  Rotary encoder for the tuner is now on teensy pins 16,15
  encoder switch sets tuning step ...on pin 17
  Double check your connections ...
 
  A/D Connections
  Teensy 4.0/4.1 A/D board 
     23            MCLK
     21            BCLK  
     20            LRCLK
     8             DATA

  D/A Connections
  Teensy 4.0/4.1 D/A board
    21             BCLK
    20             LRCLK
     7             DATA
 */


#include "ILI9488_Display.h" 
#include "VFO.h"  
#include "DSP2.h"

void setup() {

initVfo();
delay(250);
initDisplay();
delay(250);
DisplayStep();
DisplayMode();
initDsp();

}

void loop() {

changeFrequency();
 setStep();
}
