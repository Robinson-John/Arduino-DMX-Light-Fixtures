#include <Arduino.h>
#include "DMXSerial.h"
#include "ws2812.h"                // a specific LED controller that disables interrupts to work better

#define NUM_LEDS 60                // number of RGB LEDs on strip
#define DMXSTART 1                 // first DMX channel
#define DMXLENGTH (4)              // number of DMX channels used (1 RGB value for entire strip)
#define TURN_WIDTH 8                // number of pixels used for turn indicator

void setup () {

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);   // used for debugging if we are getting a signal
  DMXSerial.init(DMXProbe);        // initialize DMX bus in manual access mode
  DMXSerial.maxChannel(DMXLENGTH); // "onUpdate" will be called when all new ch data has arrived

  setupNeopixel();                 // setup the LED output hardcoded to pin 12 in ws2812.h

}

struct RGBVal {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

struct RGBVal pixelVals[NUM_LEDS];

uint16_t turnPos; //has to be 16 bit to simplify math later
RGBVal turnColor; // color to use for turn indicator - currently using opposite of base color
uint8_t turnFirstPixel;


void loop() {
  // wait for an incomming DMX packet and write
  // the RGB data for 60 LEDs on the strip
  if (DMXSerial.receive()) {

    digitalWrite(13, LOW); //using LED to signal interrupt on/off
    cli(); //turn off interrupts for processing data

    uint8_t *dmxBuffer = DMXSerial.getBuffer() + DMXSTART;
    RGBVal baseColor;

    for (int i = 0; i < DMXLENGTH; i++) { 
      baseColor.r = *dmxBuffer++;
      baseColor.g = *dmxBuffer++;
      baseColor.b = *dmxBuffer++;
      turnPos = *dmxBuffer++;

    }

    for (int i = 0; i < NUM_LEDS; i++){ //set the array to one color to update later
      pixelVals[i] = baseColor;
    }

    //Calculate turn Color
    if(turnPos != 0){
      //currently uses inverse of base color for simplicitly, can make this more visually appealing later
      turnColor.r = ~baseColor.r; 
      turnColor.g = ~baseColor.g; 
      turnColor.b = ~baseColor.b; 

      // turn indicator will be in a location proportional to the address 3 input
      turnFirstPixel = (turnPos * NUM_LEDS) >> 8;

      for (int i = 0; i < TURN_WIDTH; i++){
        pixelVals[i + turnFirstPixel] = turnColor;
      }

    }


    for (int p = 0; p < NUM_LEDS; p++) {
      // Map the DMX values to the LED strip
      sendPixel(pixelVals[p].r >> 2, pixelVals[p].g >>2, pixelVals[p].b >>2);
    }

    sei(); //turn interrupts back on

    _delay_us((RES / 1000L) + 1); //leave line low long enought for pixels to latch
    
    digitalWrite(13, HIGH);

  }

}