#include <Arduino.h>

#include <ESP8266WiFi.h>

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#include <Wire.h>

// Global sensor variables
unsigned int sensor_cap;
// unsigned int sensor_temp;
// unsigned int sensor_light;

// ThingSpeak client variables
WiFiClient client;
const char *host = "api.thingspeak.com";
const int httpPort = 80;
String ApiKey = "secret";

// Write a register using I2C
void writeI2CRegister8bit(int addr, int value)
{
  Wire.beginTransmission(addr);
  Wire.write(value);
  Wire.endTransmission();
}

// Read a register using I2C
unsigned int readI2CRegister16bit(int addr, int reg)
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

// Read the chirp sensor
void readSensor()
{
  sensor_cap = 0;
  
  for (int i = 0; i < 3; i++) {
    sensor_cap += readI2CRegister16bit(0x20, 0);
    delay(500);
  }

  sensor_cap = (sensor_cap / 3);

  // Temperature sensor
  // sensor_temp = readI2CRegister16bit(0x20, 5);

  // Light sensor
  // writeI2CRegister8bit(0x20, 3);  // request light measurement
  // sensor_light = readI2CRegister16bit(0x20, 4);
}

// Push last read sensor data to ThingSpeak
void pushToThingSpeak()
{
  // Cancel if the client cannot connect to ThingSpeak
  if (!client.connect(host, httpPort))
    return;

  // Push the sensor data
  client.print(String("GET ") + 
    "/update?key=" + ApiKey + 
    "&field1=" + sensor_cap + 
    // "&field2=" + sensor_temp + 
    // "&field3=" + sensor_light + 
    " HTTP/1.1\r\n" +
    "Host: " + host + "\r\n" +
    "Connection: keep-alive\r\n\r\n");

  // Close the connection
  client.stop();
}

void setup()
{

  // Begin I2C and Serial communication
  Wire.begin();
  Serial.begin(9600);

  // Reset the chirp sensor
  writeI2CRegister8bit(0x20, 6);

  // Connect to WiFi using WiFiManager
  WiFiManager wifiManager;
  wifiManager.autoConnect("NodeMCU-Arduino-PlatformIO");
  Serial.println("Connected!");
}

void loop()
{
  // Read the sensors and push to ThingSpeak
  readSensor();
  pushToThingSpeak();

  // Go into deep sleep for 60 seconds to save energy
  // Board is woken up by a reset from pin D0
  // Serial.println("Going to sleep for 1 minute");
  // ESP.deepSleep(60e6);

  // Wait for 1 hour
  delay(36e5);
}