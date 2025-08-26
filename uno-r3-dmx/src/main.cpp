#include <Arduino.h>
#include "neopixelDriver.h"
#include "config.h"

NeoPixelDriver mediumRing(16, MEDIUM_RING_PIN, NEO_WGRB + NEO_KHZ800);
NeoPixelDriver largeRing(24, LARGE_RING_PIN, NEO_GRB + NEO_KHZ800);
NeoPixelDriver smallRing(7, SMALL_RING_PIN, NEO_WGRB + NEO_KHZ800);

typedef struct {
  int channel;
  int value;
} DMXFrame;

// put function declarations here:

DMXFrame handleSerial() {
    if (!Serial.available()) return DMXFrame{-1, -1};
    String line = Serial.readStringUntil('\n');
    line.trim();
    if (line.length() == 0) return DMXFrame{-1, -1};

    // Buffer for parsing
    char buf[64];
    line.toCharArray(buf, sizeof(buf));

    // Try "SET <CHANNEL> <VALUE>" 
    int channel;
    int value;
    int matched = sscanf(buf, "SET %d %d", &channel, &value);
    if (matched < 2) {
        matched = sscanf(buf, "%d %d", &channel, &value);
    }

    if (matched == 2) {
        Serial.println("Setting DMX channel to " + String(channel) + " value " + String(value));
        return DMXFrame{channel, value};
    }

    Serial.println("Unknown command. Use: SET <CHANNEL> <VALUE>");
    return DMXFrame{-1, -1};
}

void updateAllStrips(){
  mediumRing.updateStrip();
  largeRing.updateStrip();
  smallRing.updateStrip();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mediumRing.init();
  largeRing.init();
  smallRing.init();

}

DMXFrame response;

void loop() {
  response = handleSerial();

  if (response.channel != -1) {
    // Process valid DMX frame
    switch (response.channel) {
      case 1:
        // Handle channel 1
        Serial.println("Setting DMX channel to 1 value " + String(response.value));
        Serial.println("Setting Medium Ring");
        mediumRing.setAllPixels(response.value);
        Serial.println("Setting Small Ring");
        smallRing.setAllPixels(response.value);
        Serial.println("Setting Large Ring");
        largeRing.setAllPixels(response.value);

        delay(100);
        updateAllStrips();
        break;
      case 2:
        // Handle channel 2
        Serial.println("Setting DMX channel to 2 value " + String(response.value));
        mediumRing.colorWipe(response.value, 50);
        smallRing.colorWipe(response.value, 50);
        largeRing.colorWipe(response.value, 50); 
        break;

      case 3:
        // Handle channel 3
        Serial.println("Setting DMX channel to 3 value " + String(response.value));
        mediumRing.theaterChaseRainbow(response.value);
        smallRing.theaterChaseRainbow(response.value);
        largeRing.theaterChaseRainbow(response.value);

        mediumRing.setAllPixels(0x000000);
        smallRing.setAllPixels(0x000000);
        largeRing.setAllPixels(0x000000);
        // updateAllStrips();
    }

  }

  delay(100);
}