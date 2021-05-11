#include <Sensor.h>

void Sensor::init()
{
    // Begin I2C communication
    Wire.begin();

    // Reset the chirp sensor
    writeI2CRegister8bit(0x20, 6);
}

// Write a register using I2C
void Sensor::writeI2CRegister8bit(int addr, int value)
{
    Wire.beginTransmission(addr);
    Wire.write(value);
    Wire.endTransmission();
}

// Read a register using I2C
unsigned int Sensor::readI2CRegister16bit(int addr, int reg)
{
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.endTransmission();
    delay(1000);
    Wire.requestFrom(addr, 2);
    unsigned int t = Wire.read() << 8;
    t = t | Wire.read();
    return t;
}

void Sensor::read(unsigned int *humidity, unsigned int *temperature, unsigned int *light) {
    readHumidity(humidity);
    readTemperature(temperature);
    readLight(light);
}

// Read the chirp sensor
void Sensor::readHumidity(unsigned int *sensor_cap)
{
    *sensor_cap = 0;

    for (int i = 0; i < 3; i++) {
        *sensor_cap += readI2CRegister16bit(0x20, 0);
        delay(500);
    }

    *sensor_cap = (*sensor_cap / 3);

}

void Sensor::readTemperature(unsigned int *temperature) {
    *temperature = readI2CRegister16bit(0x20, 5);
}

void Sensor::readLight(unsigned int *light) {
    writeI2CRegister8bit(0x20, 3);  // request light measurement
    *light = readI2CRegister16bit(0x20, 4);
}