#pragma once

#include <Arduino.h>
#include "DHT.h"

#define DHT_TYPE DHT11
#define DHT_PIN D4

struct sensor_value_t {
    long moisture_level{};
    float temperature{};
    float humidity{};
};

class Sensor {
    public:

        void init();

        sensor_value_t read();

    private:
        const int analog_in_pin_{A0};
        const int error_led_pin_{D6};

        DHT dht_{DHT_PIN, DHT_TYPE};

        int dry_value_ {687};
        int wet_value_ {281};
};