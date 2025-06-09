/*!
 * \file catchSensor.cpp
 * \brief Implementation of the catchSensor class.
 * This file contains the implementation for the catchSensor class, which is
 * responsible for managing a catch status (e.g., for a mousetrap) and
 * indicating this status using an LED on the HAN IoT Shield.
 */
#include "catchSensor.h"

// Use rightRedLED (LED 2, pin 4) for catch indication
extern iotShieldLED rightRedLED;

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
    rightRedLED.setState(LED_OFF);
}

/**
 * @brief Destructor for the catchSensor class.
 * Handles any cleanup required for the catch sensor.
 * For instance, it might ensure the LED is turned off.
 */
catchSensor::~catchSensor()
{
    // Ensure LED is off when sensor object is destructed
    rightRedLED.setState(LED_OFF);
}

/**
 * @brief Sets the catch status and updates the corresponding LED.
 * This method updates the internal catch status of the sensor.
 * Based on the new status, it controls `rightRedLED` on the HAN IoT Shield:
 * - If a catch is detected (catchStatus is true), `rightRedLED` is turned ON.
 * - If no catch is detected (catchStatus is false), `rightRedLED` is turned OFF.
 * @param catchStatus Boolean value representing the new catch status.
 *                    True indicates a catch, false indicates no catch.
 */
void catchSensor::setCatchStatus(bool catchStatus)
{
    _catchStatus = catchStatus;

    // Turn on/off rightRedLED based on the catch status
    if (_catchStatus)
    {
        // Turn on rightRedLED to indicate a catch
        rightRedLED.setState(LED_ON);
    }
    else
    {
        // Turn off rightRedLED to indicate no catch
        rightRedLED.setState(LED_OFF);
    }
}