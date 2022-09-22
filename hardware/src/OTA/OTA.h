#ifndef OTA_H

    #define OTA_H
        #include <Arduino.h>              // Main Arduino Library
        #include <ESP8266WiFi.h>

        extern WiFiClient espClient;
        extern String espClientIP;
        extern String espClientMAC;
        
        extern String espClientName;
        extern String espClientHostname;
        extern String espClientPlace;

        void OTAsetup();
        void OTA();
        void espClientPrint();

#endif
