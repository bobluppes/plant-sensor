#pragma once

#include <WiFiManager.h>
#include <ESP8266WiFi.h>

// TODO: could be a fwd
#include "sensor.h"

// Do we even need this?
#include <DNSServer.h>
#include <ESP8266WebServer.h>

class Thingspeak {
    public:

        // Connects to wifi using WiFiManager
        void init();

        bool push(const sensor_value_t sensor_value);

    private:
        WiFiManager wifi_manager_{};
        WiFiClient client_{};

        const int led_pin_{D1};
};