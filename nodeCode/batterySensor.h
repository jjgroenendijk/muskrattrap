#ifndef BATTERYSENSOR_H
#define BATTERYSENSOR_H

#include "IOTShieldConfig.h"
#include <Arduino.h>
#include <stdint.h>
#include "HAN_IoT_Shield.h"

/**
 * @brief Minimum battery voltage reading (raw ADC value).
 * This typically corresponds to the lowest expected voltage from the battery.
 */
#define MIN_BATTERY_VOLTAGE 0

/**
 * @brief Maximum battery voltage reading (raw ADC value).
 * This typically corresponds to the highest expected voltage from the battery (e.g., fully charged).
 */
#define MAX_BATTERY_VOLTAGE 1023

/**
 * @class batterySensor
 * @brief Simulates a battery sensor using potentiometer 2 on the HAN IoT Shield.
 *
 * This class provides an interface to read a simulated battery level.
 * The actual battery level is read from an analog input connected to potentiometer 2.
 */
class batterySensor
{
private:
    uint32_t _batteryLevel; ///< Stores the last read battery level (raw ADC value).

public:
    /**
     * @brief Construct a new batterySensor object.
     * Initializes the battery sensor.
     */
    batterySensor();

    /**
     * @brief Destroy the batterySensor object.
     * Performs cleanup if necessary.
     */
    ~batterySensor();

    /**
     * @brief Get the current battery level.
     * Reads the value from potentiometer 2 and returns it as a raw ADC value.
     * @return uint32_t The current battery level (0-1023).
     */
    uint32_t getBatteryLevel();

    /**
     * @brief Set the battery level (for simulation/testing purposes).
     * This method is typically used for testing or when an external mechanism sets the battery level.
     * @param batteryLevel The battery level to set (raw ADC value).
     */
    void setBatteryLevel(uint32_t batteryLevel);
};

#endif // BATTERYSENSOR_H