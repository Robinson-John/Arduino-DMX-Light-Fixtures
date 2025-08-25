#include <Adafruit_NeoPixel.h>

class NeoPixelDriver {
public:
    NeoPixelDriver(int numPixels, int pin);
    void init();
    void setColor(int pixel, int color);
    void updateStrip();
    void colorWipe(int c, int wait);

private:
    Adafruit_NeoPixel strip;
    int numPixels;
    int pin;
    int *pixels;
};