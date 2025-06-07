/**
 * @file catchSensor.cpp
 * @brief Implements the catchSensor class for simulating catch detection.
 * This file contains the method definitions for the catchSensor class,
 * which simulates a catch event and uses the leftGreenLED on the HAN IoT
 * Shield to indicate the status.
 * @author Project Contributors
 * @date 2024-03-15
 */
#include "catchSensor.h"

/**
 * @brief Construct a new catch Sensor::catch Sensor object.
 *
 * Initializes the catch status to `false` (no catch detected).
 * Any specific hardware initialization for the catch sensor should be placed here.
 */
catchSensor::catchSensor() : _catchStatus{false}
{
    // Initialize catch sensor here (e.g., configure input pin if using a real sensor)
    // For simulation, ensure the LED is initially off.
    leftGreenLED.setState(LED_OFF);
}

/**
 * @brief Destroy the catch Sensor::catch Sensor object.
 *
 * Placeholder for any cleanup operations needed by the catch sensor.
 * For instance, ensuring an LED is turned off or a pin is reset to a default state.
 */
catchSensor::~catchSensor()
{
    // Stop catch sensor here (e.g., turn off indicator LEDs)
    leftGreenLED.setState(LED_OFF);
}

/**
 * @brief Sets the catch status and updates an indicator LED.
 *
 * This function updates the internal catch status (`_catchStatus`).
 * It also controls `leftGreenLED` on the HAN IoT Shield:
 * - If `catchStatus` is `true`, `leftGreenLED` is turned ON.
 * - If `catchStatus` is `false`, `leftGreenLED` is turned OFF.
 * @param catchStatus The new status of the catch detection (`true` for detected, `false` for not detected).
 */
void catchSensor::setCatchStatus(bool catchStatus)
{
    _catchStatus = catchStatus;

    if (catchStatus)
    {
        // Turn on LED2 to indicate that the catch is detected
        leftGreenLED.setState(LED_ON);
    }
    else
    {
        // Turn off LED2 to indicate that the catch is not detected
        leftGreenLED.setState(LED_OFF);
    }
}