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
    Serial.println("To update Matrix display send: SET <row> <column> <value>");
    delay(200);
}

uint8_t frame[8][12] = { //heart
    { 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0 },
    { 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 }
  };
  
// unsigned long frame[] = { //smily face
//     0x19819,
//     0x80000001,
//     0x81f8000
// };

bool frameUpdated = true;
int FRAME_LEN = sizeof(frame) / sizeof(frame[0]);


void handleSerial() {
    if (!Serial.available()) return;
    String line = Serial.readStringUntil('\n');
    line.trim();
    if (line.length() == 0) return;

    // Buffer for parsing
    char buf[64];
    line.toCharArray(buf, sizeof(buf));

    // Try "SET <row> <column> <value>" or "<row> <column>"
    int row, col;
    char valStr[32];
    int matched = sscanf(buf, "SET %d %d %31s", &row, &col, valStr);
    if (matched < 3) {
        matched = sscanf(buf, "%d %d %31s", &row, &col, valStr);
    }

    if (matched == 3) {
        if (row < 0 || row >= 8 || col < 0 || col >= 12) {
            Serial.println("Error: row/column out of range");
            return;
        }
        boolean val = strtoul(valStr, NULL, 0);
        frame[row][col] = val;
        frameUpdated = true;
        Serial.print("OK set frame[");
        Serial.print(row);
        Serial.print("][");
        Serial.print(col);
        Serial.print("] = ");
        Serial.println(String(frame[row][col]));
        return;
    }

    Serial.println("Unknown command. Use: SET <row> <column> <value>  or  PRINT");
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