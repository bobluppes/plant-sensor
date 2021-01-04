# Plant Sensor
Reads soil humidity data from nodeMCU connected to soil sensor. The nodeMCU kernel is implemented in the PlatformIO framework.

## Setup
* Install PlatformIO extension (works for VSCode)
* Add ThingSpeak channel with single field
* Add ThingSpeak API key on line 20 in `src/main.cpp`
* Flash the NodeMCU

*The NodeMCU connects to a previously saved WiFi network using the WiFiManager library*

## Example
An example ThingSpeak channel is hosted [here](https://thingspeak.com/channels/1090659). Data on this channel may be outdated or invalid due to moving the sensor.
