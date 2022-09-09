#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "pinSettings.h"
#include "mqtt/mqtt.h"
#include "tempSensor/tempSensor.h"
#include "OTA/OTA.h"

String client_id = "";

// MQTT Broker
const char *mqtt_broker = "mqtt.bee.espertamente.com.br";
const char *topic = "sensors/CofeeMachine/Saeco_xSmall";
const char *mqtt_username = "espertamente";
const char *mqtt_password = "HRdgDOeKASx2YhxavKBa";
const int mqtt_port = 1883;


PubSubClient client(espClient);



void mqttConnect() {
  // Connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  //client.setCallback(callback);

  while (!client.connected()) {
      client_id = "saeco_xsmall_";
      client_id += String(WiFi.macAddress());
      Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
      if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
          Serial.println("MQTT broker connected");
      } else {
          Serial.print("failed with state ");
          Serial.print(client.state());
          delay(2000);
      }
  }
}


void mqttPublish() {

  //Convert float data to strings
  // Allocate the JSON document
  //
  // Inside the brackets, 200 is the RAM allocated to this document.
  // Don't forget to change this value to match your requirement.
  // Use https://arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<200> doc;

  // StaticJsonObject allocates memory on the stack, it can be
  // replaced by DynamicJsonDocument which allocates in the heap.
  //
  // DynamicJsonDocument  doc(200);

  // Add values in the document
  doc["Machine"] = client_id;
  doc["Boiler_Temperature"] = tempC;
  doc["Grinder_Runtime"] = 1;
  doc["Water_Pump_Runtime"] = 1;
 
  // Generate the minified JSON and send it to the Serial port.
  serializeJson(doc, Serial);

  // Start a new line
  Serial.println();

 char outputJson[128];
    serializeJson(doc, outputJson);
  //Publish the data to the topic
  client.publish(topic, outputJson);
  client.loop();
}
