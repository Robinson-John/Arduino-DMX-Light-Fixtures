#include <Arduino.h>
#include <unity.h>
#include "dmx_slave.h"
#include "neopixel_driver.h"

DMXSlave dmxSlave;
NeoPixelDriver neoPixelDriver;

void setUp() {
    dmxSlave.init();
    neoPixelDriver.init();
}

void test_DMXRead() {
    // Simulate DMX input and test the read functionality
    dmxSlave.readDMX();
    int channelValue = dmxSlave.getChannelValue(1); // Assuming channel 1 is used
    TEST_ASSERT_GREATER_THAN(0, channelValue); // Check if the value is valid
}

void test_NeoPixelColor() {
    // Test setting a color on the NeoPixel strip
    neoPixelDriver.setColor(255, 0, 0); // Set to red
    neoPixelDriver.updateStrip();
    // Add assertions to verify the color is set correctly
    // This would require a way to read back the color, which may need to be implemented
}

void test_NeoPixelUpdate() {
    // Test updating the NeoPixel strip based on DMX input
    dmxSlave.readDMX();
    int channelValue = dmxSlave.getChannelValue(1);
    neoPixelDriver.setColor(channelValue, 0, 0); // Set color based on DMX value
    neoPixelDriver.updateStrip();
    // Add assertions to verify the NeoPixel strip updated correctly
}

void loop() {
    // This function is intentionally left blank for unit tests
}

void runTests() {
    UNITY_BEGIN();
    RUN_TEST(test_DMXRead);
    RUN_TEST(test_NeoPixelColor);
    RUN_TEST(test_NeoPixelUpdate);
    UNITY_END();
}

void setup() {
    setUp();
    runTests();
}