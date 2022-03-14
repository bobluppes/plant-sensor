#include <Arduino.h>

#include "thingspeak.h"
#include "sensor.h"

Thingspeak thingspeak;
Sensor sensor;

void setup()
{

    // Begin Serial communication
    Serial.begin(9600);

    // Initialize the thingspeak class
    thingspeak.init();

    sensor.init();

}

void loop()
{

    auto sensor_value {sensor.read()};
    thingspeak.push(sensor_value);

    Serial.println("Moisture: " + String(sensor_value.moisture_level) + "\tTemperature: " +
        String(sensor_value.temperature) + "\tHumidity: " + String(sensor_value.humidity));

    // Go into deep sleep for 60 seconds to save energy
    // Board is woken up by a reset from pin D0
//     ESP.deepSleep(60e6);

    delay(1);
}