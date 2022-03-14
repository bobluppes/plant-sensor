#include "sensor.h"

#include <cmath>

void Sensor::init() {
    dht_.begin();
    pinMode(error_led_pin_, OUTPUT);
    digitalWrite(error_led_pin_, LOW);
}

sensor_value_t Sensor::read() {
    digitalWrite(error_led_pin_, LOW);

    auto sensor_value {analogRead(analog_in_pin_)};
    auto moisture_level {map(sensor_value, wet_value_, dry_value_, 100, 0)};

    float temperature {dht_.readTemperature()};
    float humidity {dht_.readHumidity()};

    if (isnan(moisture_level) || std::isnan(temperature) || std::isnan(humidity))
        digitalWrite(error_led_pin_, HIGH);

    return {moisture_level, temperature, humidity};
}