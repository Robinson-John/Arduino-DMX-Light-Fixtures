#define DMX_CHANNEL_START 1
#define DMX_CHANNEL_COUNT 12

#define DMX_INPUT_PIN 2
#define NEOPIXEL_PIN 6
#define NEOPIXEL_COUNT 30  // Adjust this to the number of NeoPixels in your strip

#define DMX_TIMEOUT 1000 // Timeout for DMX signal in milliseconds

// Color definitions
#define COLOR_RED 0xFF0000
#define COLOR_GREEN 0x00FF00
#define COLOR_BLUE 0x0000FF
#define COLOR_WHITE 0xFFFFFF

// Function to map DMX values to NeoPixel brightness
#define DMX_TO_BRIGHTNESS(value) ((value) * 255 / 255) // Assuming DMX value is 0-255