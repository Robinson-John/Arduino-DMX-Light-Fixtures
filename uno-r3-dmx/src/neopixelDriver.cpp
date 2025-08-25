#include "neopixelDriver.h"
#include <Adafruit_NeoPixel.h>

NeoPixelDriver::NeoPixelDriver(int numPixels, int pin) {
    this->numPixels = numPixels;
    this->pin = pin;
    this->strip = Adafruit_NeoPixel(numPixels, pin, NEO_GRB + NEO_KHZ800);

}

void NeoPixelDriver::init() {
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void NeoPixelDriver::setColor(int pixel, int color) {
    for (uint16_t i = 0; i < numPixels; i++) {
        strip.setPixelColor(i, color);
    }
}

void NeoPixelDriver::updateStrip() {
    strip.show();
}

// Fill the dots one after the other with a color
void NeoPixelDriver::colorWipe(int c, int wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}