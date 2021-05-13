#include <Arduino.h>

#include <Wire.h>

#include <Sensor.h>
#include <ApiClient.h>

#include <config.h>

// CONNECTIONS
// MISO => D6
// VCC => 3V
// SCK/SCL => D1
// MOSI/SDA => D2
// RESET => RST
// GND => G

Sensor sensor;
ApiClient api;

// Global sensor variables
unsigned int humidity;
unsigned int temperature;
unsigned int light;

void debugPrint() {
    Serial.println(
            "Humidity: " + (String) humidity +
            "\tTemperature: " + (String) temperature +
            "\tLight: " + (String) light
            );
}

void setup()
{

    // Serial communication
    Serial.begin(115200);
    Serial.println("\nSensor ID: " + (String) DEVICE_ID);

    sensor.init();

    api.init();
}

void loop()
{
    // Read the sensors and push to ThingSpeak
    sensor.read(&humidity, &temperature, &light);
    debugPrint();
    api.pushToAPI(&humidity, &temperature, &light);

    // Go into deep sleep for 60 seconds to save energy
    // Board is woken up by a reset from pin D0
     Serial.println("Going to sleep for 1 hour");
     ESP.deepSleep(3600e6);

    // Wait for 1 second
    // delay(1);
}