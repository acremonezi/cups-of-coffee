#ifndef tempSensor_H

    #define tempSensor_H
    
        #include <Arduino.h>
        #include "pinSettings.h"        // Pin Settings Setup

        extern float tempC;

        void tempSensorSetup();
        void tempSensor();

#endif


