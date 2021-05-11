#include <ApiClient.h>

// ThingSpeak client variables
WiFiClient client;
const char *host = "YOUR_API_HOST";
const int httpPort = YOUR_API_PORT;

void ApiClient::init() {
    pinMode(NETWORK_LED, OUTPUT);

    digitalWrite(NETWORK_LED, HIGH);

    // Connect to WiFi using WiFiManager
    WiFiManager wifiManager;
    wifiManager.autoConnect("NodeMCU-Arduino-PlatformIO");
    Serial.println("Connected!");

    digitalWrite(NETWORK_LED, LOW);
}

// Push last read sensor data to ThingSpeak
void ApiClient::pushToAPI(unsigned int *humidity, unsigned int *temperature, unsigned int *light)
{
    // Cancel if the client cannot connect to ThingSpeak
    if (!client.connect(host, httpPort)) {
        Serial.print("Cant connect to " + (String) host + ":" + (String) httpPort);
        bool led_state = HIGH;
        for (int i = 0; i < 8; i++) {
            led_state = !led_state;
            digitalWrite(NETWORK_LED, led_state);
            delay(500);
            if (client.connect(host, httpPort)) {
                Serial.print(" connected");
                post(humidity, temperature, light);
                break;
            } else {
                Serial.print(".");
            }
        }
        Serial.print("\n");
        return;
    }

    post(humidity, temperature, light);
}

void ApiClient::post(unsigned int *humidity, unsigned int *temperature, unsigned int *light)
{
    digitalWrite(NETWORK_LED, HIGH);

    // Push the sensor data
    client.print(String("POST ") +
                 "/api?humidity=" + *humidity +
                 "&temperature=" + *temperature +
                 "&light=" + *light +
                 " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: keep-alive\r\n\r\n");

    // Close the connection
    client.stop();

    digitalWrite(NETWORK_LED, LOW);
}
