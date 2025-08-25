#include <Arduino.h>
#include "neopixelDriver.h"
#include "config.h"

NeoPixelDriver pixelRing(16, RING_PIN);

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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pixelRing.init();
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
        pixelRing.colorWipe(255, 50);
        break;
      case 2:
        // Handle channel 2
        Serial.println("Setting DMX channel to 2 value " + String(response.value));
        pixelRing.colorWipe(response.value, 50);
        break;
    }

  }
}