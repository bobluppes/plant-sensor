#include "thingspeak.h"

#include "credentials.h"

void Thingspeak::init() {
    pinMode(led_pin_, OUTPUT);
    digitalWrite(led_pin_, HIGH);

    wifi_manager_.autoConnect(AUTOCONNECT_SSID, AUTOCONNECT_PASSWORD);

    digitalWrite(led_pin_, LOW);
}

bool Thingspeak::push(const sensor_value_t sensor_value) {

    if (!client_.connect(HOST, HTTP_PORT)){
        Serial.println("couldnt connect");
        return false;
    }

    digitalWrite(led_pin_, HIGH);

    client_.print(String("GET ") +
                 "/update?key=" + KEY +
                 "&field1=" + sensor_value.moisture_level +
                 "&field2=" + sensor_value.temperature +
                 "&field3=" + sensor_value.humidity +
                 " HTTP/1.1\r\n" +
                 "Host: " + HOST + "\r\n" +
                 "Connection: keep-alive\r\n\r\n");

    client_.stop();

    digitalWrite(led_pin_, LOW);

    Serial.println("made get");

    return true;
}