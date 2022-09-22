#include <Arduino.h>                    // Main Arduino Library
#include "pinSettings.h"                // Pin Settings Setup
#include "OTA/OTA.h"                    // Over-The-Air (OTA)
#include "tempSensor/tempSensor.h"      // OneWire Temperature Sensor
#include "mqtt/mqtt.h"                  // MQTT Service


void setup() {
  pinSettings();                        // Pin Settings Setup
  OTAsetup();                           // OTA - Setup
  tempSensorSetup();                    // OneWire Temperature Sensor
  mqttConnect();                        // MQTT Setup
  espClientPrint();                     // Print ESP Client IP and MAC Address
}

void loop() {
  OTA();                                // OTA
  tempSensor();                         // OneWire
  mqttPublish();                        // MQTT Publish
}