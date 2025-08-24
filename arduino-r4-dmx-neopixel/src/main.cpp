#include <Arduino.h>
#include "config.h"
// #include "dmx_slave.h"
// #include "neopixel_driver.h"
#include <Arduino_LED_Matrix.h>

// DMXSlave dmxSlave;
// NeoPixelDriver neoPixelDriver;
ArduinoLEDMatrix matrix;

void setup() {
    // dmxSlave.init();
    // neoPixelDriver.init();
    matrix.begin();

    Serial.begin(115200);
    Serial.println("To update Matrix display send: SET <channel> <value>");
    //1 channel for each column, value is how far down the row the lights go
    delay(200);
}

uint8_t frame[8][12] = { //heart
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
  };
  
// unsigned long frame[] = { //smily face
//     0x19819,
//     0x80000001,
//     0x81f8000
// };

bool frameUpdated = true;


//currently using serial input as proxy for dmx inputs as dmx hardware has not arrived
void handleSerial() {
    if (!Serial.available()) return;
    String line = Serial.readStringUntil('\n');
    line.trim();
    if (line.length() == 0) return;

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
        if (channel < 0 || channel >= 12) {
            Serial.println("Error: channel out of range");
            return;
        }
        if (value < 0 || value > 255) {
            Serial.println("Error: value out of range");
            return;
        }
        Serial.println("Parsed channel " + String(channel) + " value " + String(value)); //TODO remove
        char row = value/32; //0-7
        Serial.println("Setting row " + String(row) + " for channel " + String(channel)); //TODO remove

        for (int i = 0; i < 8; i++) {
            if (i <= row && value != 0) {
                frame[i][channel] = 1; // LED on
                Serial.println("Frame " + String(i) + "," + String(channel) + " set to 1"); //TODO remove
            } else {
                frame[i][channel] = 0; // LED off
                Serial.println("Frame " + String(i) + "," + String(channel) + " set to 0"); //TODO remove
            }
        }

        frameUpdated = true;
        Serial.print("OK set Channel ");
        Serial.print(channel);
        Serial.print(" first ");
        Serial.print(row);
        Serial.println(" rows.");
        return;
    }

    Serial.println("Unknown command. Use: SET <CHANNEL> <VALUE>");
}

void loop() {
    handleSerial();
    // dmxSlave.readDMX();
    // for (int i = 0; i < NUM_PIXELS; i++) {
    //     uint8_t r = dmxSlave.getChannelValue(i * 3);     // Red channel
    //     uint8_t g = dmxSlave.getChannelValue(i * 3 + 1); // Green channel
    //     uint8_t b = dmxSlave.getChannelValue(i * 3 + 2); // Blue channel
    //     neoPixelDriver.setColor(i, r, g, b);
    // }
    // neoPixelDriver.updateStrip();

    if (frameUpdated) {
        matrix.renderBitmap(frame, 8, 12);
        frameUpdated = false;
    }

    delay(500); // Small delay to avoid overwhelming the loop
}