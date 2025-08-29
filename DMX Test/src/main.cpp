#include <Arduino.h>
#include "DMXSerial.h"
#include "ws2812.h"                // a specific LED controller that disables interrupts to work better

#define NUM_LEDS 60                // number of RGB LEDs on strip
#define DMXSTART 1                 // first DMX channel
#define DMXLENGTH (3)              // number of DMX channels used (1 RGB value for entire strip)

void setup () {

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);   // used for debugging if we are getting a signal
  DMXSerial.init(DMXProbe);        // initialize DMX bus in manual access mode
  DMXSerial.maxChannel(DMXLENGTH); // "onUpdate" will be called when all new ch data has arrived

  setupNeopixel();                 // setup the LED output hardcoded to pin 12 in ws2812.h

}


void loop() {
  // wait for an incomming DMX packet and write
  // the RGB data for 60 LEDs on the strip
  if (DMXSerial.receive()) {
    digitalWrite(13, LOW);
    cli(); //turn off interrupts for processing data

    uint8_t *dmxBuffer = DMXSerial.getBuffer() + DMXSTART;
    uint8_t r, g, b;

    for (int i = 0; i < DMXLENGTH; i++) { 
      r = *dmxBuffer++;
      g = *dmxBuffer++;
      b = *dmxBuffer++;

      for (int p = 0; p < NUM_LEDS; p++) {
        // Map the DMX values to the LED strip
        sendPixel(r >> 2, g >>2, b >>2);
      }
    }
      // updateNeopixel(dmxBuffer, NUM_LEDS); //if we want to update individual LEDs based on channel

      sei(); //turn interrupts back on

    _delay_us((RES / 1000L) + 1); //leave line low long enought for pixels to latch
    
    digitalWrite(13, HIGH);

  }

}