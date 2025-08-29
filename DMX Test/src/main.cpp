#include <Arduino.h>
#include "DMXSerial.h"
#include "ws2812.h"                // a specific LED controller that disables interrupts to work better

#define NUM_LEDS 60                // number of RGB LEDs on strip
#define DMXSTART 1                 // first DMX channel
#define DMXLENGTH (NUM_LEDS*3)     // number of DMX channels used (3*60 LEDs)

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
      updateNeopixel(DMXSerial.getBuffer() + DMXSTART, NUM_LEDS); //if we want to update individual LEDs based on channel
    digitalWrite(13, HIGH);
  }

}