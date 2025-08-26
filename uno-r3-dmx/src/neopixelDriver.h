#include <Adafruit_NeoPixel.h>

class NeoPixelDriver {
public:
    NeoPixelDriver(int numPixels, int pin, neoPixelType type);
    void init();
    void setColor(uint16_t pixel, uint32_t color);
    void updateStrip();
    void colorWipe(int c, int wait);
    void setAllPixels(uint32_t color);
    void theaterChaseRainbow(uint8_t wait);
    uint32_t Wheel(byte WheelPos);
    Adafruit_NeoPixel strip;

private:
    int numPixels;
    int pin;
    int *pixels;
};