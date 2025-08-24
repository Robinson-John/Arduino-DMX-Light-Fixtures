class NeoPixelDriver {
public:
    void init(int numPixels, int pin);
    void setColor(int pixel, uint32_t color);
    void updateStrip();
    
private:
    int numPixels;
    int pin;
    uint32_t *pixels;
};