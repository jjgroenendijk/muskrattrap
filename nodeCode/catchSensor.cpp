/*!
 * \file catchSensor.cpp
 * \brief Implementation of the catchSensor class.
 * This file contains the implementation for the catchSensor class, which is
 * responsible for managing a catch status (e.g., for a mousetrap) and
 * indicating this status using an LED on the HAN IoT Shield.
 */
#include "catchSensor.h"

/**
 * @brief Constructor for the catchSensor class.
 * Initializes the catch status to false (no catch detected).
 * Any specific hardware initialization for a real sensor would go here,
 * though this class primarily relies on its status being set externally.
 */
catchSensor::catchSensor() : _catchStatus{false}
{
    ///< Initialize catch sensor here
    // Ensure LED is off on initialization, matching the initial _catchStatus.
    leftGreenLED.setState(LED_OFF);
}

/**
 * @brief Destructor for the catchSensor class.
 * Handles any cleanup required for the catch sensor.
 * For instance, it might ensure the LED is turned off.
 */
catchSensor::~catchSensor()
{
    ///< Stop catch sensor here
    // Optionally, ensure LED is off when sensor is destroyed.
    // leftGreenLED.setState(LED_OFF);
}

/**
 * @brief Sets the catch status and updates an LED indicator.
 * This method updates the internal catch status of the sensor.
 * Based on the new status, it controls `leftGreenLED` on the HAN IoT Shield:
 * - If a catch is detected (catchStatus is true), `leftGreenLED` is turned ON.
 * - If no catch is detected (catchStatus is false), `leftGreenLED` is turned OFF.
 * @param catchStatus Boolean value representing the new catch status.
 *                    True indicates a catch, false indicates no catch.
 */
void catchSensor::setCatchStatus(bool catchStatus)
{
    _catchStatus = catchStatus;

    if (catchStatus)
    {
        ///< Turn on LED2 to indicate that the catch is detected
        leftGreenLED.setState(LED_ON);
    }
    else
    {
        ///< Turn off LED2 to indicate that the catch is not detected
        leftGreenLED.setState(LED_OFF);
    }
}