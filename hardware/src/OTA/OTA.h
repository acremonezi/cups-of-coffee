#ifndef OTA_H

    #define OTA_H
        #include <Arduino.h>              // Main Arduino Library
        #include <ESP8266WiFi.h>
        extern WiFiClient espClient;
        void OTAsetup();
        void OTA();

#endif
