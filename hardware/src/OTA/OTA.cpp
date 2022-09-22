#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "OTA/OTA.h"


#ifndef STASSID
    #define STASSID "Quantum_IoT"
    #define STAPSK  "Y7Q9vD8V10b!!!"

    #define NAME "Saeco xSmall"           // Coffee Machine Name
    #define HOSTNAME "Saeco_xSmall"       // Coffee Machine Network Hostname
    #define PLACE "Alcides Home"
#endif


const char* ssid = STASSID;
const char* password = STAPSK;

String espClientIP = "";
String espClientMAC = "";
String espClientName = "";
String espClientHostname = "";
String espClientPlace = "";

WiFiClient espClient;

void OTAsetup() {
  Serial.begin(9600);
  Serial.println("Booting");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname(HOSTNAME);
  WiFi.hostname(HOSTNAME);

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });

  ArduinoOTA.begin();

  // Store Wifi IP and MAC
  espClientIP = WiFi.localIP().toString().c_str();
  espClientMAC = WiFi.macAddress();
  espClientName = NAME;
  espClientHostname = WiFi.hostname();
  espClientPlace = PLACE;

  // Print IP and MAC
  espClientPrint();
  
}

void OTA() {
  ArduinoOTA.handle();
}

void espClientPrint() {
  // Print IP and MAC Addresses
  Serial.println("-------------------------------------");
  Serial.println("Ready !!!");
  Serial.print("Machine Name: ");
  Serial.println(espClientName);
  Serial.print("Hostname: ");
  Serial.println(espClientHostname);
  Serial.print("Place: ");
  Serial.println(espClientPlace);
  Serial.print("IP address: ");
  Serial.println(espClientIP);
  Serial.print("MAC address: ");
  Serial.println(espClientMAC);
  Serial.println("-------------------------------------");
}