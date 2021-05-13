#include <ApiClient.h>

// ThingSpeak client variables
WiFiClient client;
HTTPClient http;
const char *host = HOST;
const int httpPort = PORT;
const String url = ENDPOINT;
const String key = KEY;

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

    http.begin(client, "http://" + (String) host + url + "?code=" + key);
    http.addHeader("Content-Type", "application/json");

    // Generate JSON body for POST request
    const String data = String("{") +
                        "\"device\":\"" + (String) DEVICE_ID + "\"," +
                        "\"humidity\":\"" + (String) *humidity + "\"," +
                        "\"temperature\":\"" + (String) *temperature + "\"," +
                        "\"light\":\"" + (String) *light + "\"" +
                        "}";

    auto httpCode = http.POST(data);
    Serial.println("POST to " + (String) host + " returns status code " + httpCode);

    // Close the connection
    client.stop();

    digitalWrite(NETWORK_LED, LOW);
}
