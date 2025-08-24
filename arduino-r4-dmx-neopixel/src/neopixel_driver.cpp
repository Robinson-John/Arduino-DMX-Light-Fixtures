// #include "neopixel_driver.h"
// #include <Adafruit_NeoPixel.h>

// NeoPixelDriver::NeoPixelDriver(uint16_t numPixels, uint8_t pin) 
//     : numPixels(numPixels), pin(pin), strip(numPixels, pin, NEO_GRB + NEO_KHZ800) {}

// void NeoPixelDriver::init() {
//     strip.begin();
//     strip.show(); // Initialize all pixels to 'off'
// }

// void NeoPixelDriver::setColor(uint32_t color) {
//     for (uint16_t i = 0; i < numPixels; i++) {
//         strip.setPixelColor(i, color);
//     }
// }

// void NeoPixelDriver::updateStrip() {
//     strip.show();
// }