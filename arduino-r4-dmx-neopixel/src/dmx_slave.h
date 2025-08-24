class DMXSlave {
public:
    DMXSlave();
    void init();
    void readDMX();
    uint8_t getChannelValue(uint8_t channel);

private:
    uint8_t dmxData[512]; // Array to hold DMX data
};