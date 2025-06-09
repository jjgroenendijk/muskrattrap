/*!
 * \file batterySensor.h
 * \brief Defines the interface for the batterySensor class.
 * This file contains the class definition for batterySensor, which simulates
 * battery level readings, typically using a potentiometer from the HAN IoT Shield.
 */
#ifndef NODECODE_BATTERYSENSOR_H
#define NODECODE_BATTERYSENSOR_H

#include "IOTShieldConfig.h"
#include <Arduino.h>
#include <stdint.h>
#include "HAN_IoT_Shield.h"

// Note: Battery Sensor is simulated with potmeter 2 as mentioned in original comments.

/**
 * @class batterySensor
 * @brief Simulates a battery sensor, providing battery level readings.
 * This class is designed to mimic the behavior of a battery sensor, primarily by
 * reading an analog value from potentiometer 2 on the HAN IoT Shield and
 * interpreting it as a battery level. It also allows for manual setting of the
 * battery level for simulation or testing purposes.
 */
class batterySensor /// BatteryStatus class declaration:
{
private:
    uint32_t _batteryLevel; ///< Stores the current battery level.
    iotShieldLED* _batteryLed; ///< Pointer to the LED used for battery indication.

public:
    /**
     * @brief Constructor for batterySensor.
     * Initializes the battery sensor object.
     * @param led Pointer to the iotShieldLED object to be used for battery level indication.
     */
    batterySensor(iotShieldLED* led);    ///< Constructor

    /**
     * @brief Destructor for batterySensor.
     * Cleans up resources used by the battery sensor object, if any.
     */
    ~batterySensor();   ///< Destructor

    /**
     * @brief Gets the current simulated battery level.
     * In a real scenario, this would read from a hardware sensor. Here, it typically
     * reads from potentiometer 2 on the HAN IoT Shield.
     * @return The current battery level (e.g., a percentage or raw ADC value,
     *         depending on implementation in .cpp and potmeter configuration).
     */
    uint32_t getBatteryLevel();

    /**
     * @brief Sets the current simulated battery level and updates LED brightness.
     * @param batteryLevel The battery level to set (e.g., 0-100).
     */
    void setBatteryLevel(uint32_t batteryLevel);

    /**
     * @brief Updates the battery indicator LED based on the current battery level.
     * Uses PWM to control LED brightness if the LED pin supports PWM.
     * Otherwise, it will turn the LED ON for high levels and OFF for low levels.
     */
    void updateLedIndicator();
};

#endif // NODECODE_BATTERYSENSOR_H