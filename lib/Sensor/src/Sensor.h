#include <Arduino.h>
#include <Wire.h>

class Sensor {
public:

    void init();

    // Write a register using I2C
    void writeI2CRegister8bit(int addr, int value);

    // Read a register using I2C
    unsigned int readI2CRegister16bit(int addr, int reg);

    void read(unsigned int *humidity, unsigned int *temperature, unsigned int *light);

    // Read the chirp sensor
    void readHumidity(unsigned int *humidity);
    void readTemperature(unsigned int *temperature);
    void readLight(unsigned int *light);
};
