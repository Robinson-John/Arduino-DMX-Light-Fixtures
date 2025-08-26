#include "neopixelDriver.h"
#include <Adafruit_NeoPixel.h>

NeoPixelDriver::NeoPixelDriver(int numPixels, int pin, neoPixelType type) {
    this->numPixels = numPixels;
    this->pin = pin;
    this->strip = Adafruit_NeoPixel(numPixels, pin, type);

}

void NeoPixelDriver::init() {
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void NeoPixelDriver::setColor(uint16_t pixel, uint32_t color) {
    for (uint16_t i = 0; i < numPixels; i++) {
        strip.setPixelColor(i, color);
    }
}

void NeoPixelDriver::updateStrip() {
    strip.show();
}

// Fill the dots one after the other with a color
void NeoPixelDriver::colorWipe(int c, int wait) {
  Serial.println("Color wipe with color: " + String(c) + " and wait: " + String(wait));
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    Serial.println("Setting pixel " + String(i) + " to color: " + String(c));
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void NeoPixelDriver::setAllPixels(uint32_t color) {
    for (uint16_t i = 0; i < numPixels; i++) {
        Serial.println("Setting pixel " + String(i) + " to color: " + String(color));
        strip.setPixelColor(i, color);
        strip.show();
    }
    //must call show() to update the strip
}

//Theatre-style crawling lights with rainbow effect
void NeoPixelDriver::theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t NeoPixelDriver::Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}