#ifndef BATTERYSENSOR_H
#define BATTERYSENSOR_H

#include "IOTShieldConfig.h"
#include <Arduino.h>
#include <stdint.h>
#include "HAN_IoT_Shield.h"

#define MIN_BATTERY_VOLTAGE 0
#define MAX_BATTERY_VOLTAGE 1023

/// Battery Sensor is simulated with potmeter 2

class batterySensor /// BatteryStatus class declaration:
{
private:
    uint32_t _batteryLevel;

public:
    batterySensor();    ///< Constructor
    ~batterySensor();   ///< Destructor

    uint32_t getBatteryLevel();
    void setBatteryLevel(uint32_t batteryLevel);
};

#endif // BATTERYSENSOR_H