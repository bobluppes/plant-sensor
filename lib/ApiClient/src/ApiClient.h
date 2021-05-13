#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>

#include <../../../src/config.h>

#define NETWORK_LED D4

class ApiClient {
public:

    void init();

    // Push last read sensor data to ThingSpeak
    void pushToAPI(unsigned int *humidity, unsigned int *temperature, unsigned int *light);

private:

    void post(unsigned int *humidity, unsigned int *temperature, unsigned int *light);
};
