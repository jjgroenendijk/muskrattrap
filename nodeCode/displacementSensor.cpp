/**
 * @file displacementSensor.cpp
 * @brief Implements the displacementSensor class for simulating trap displacement.
 * This file contains method definitions for the displacementSensor class,
 * which simulates a trap displacement event and uses the rightRedLED on the
 * HAN IoT Shield to indicate the status.
 * @author Project Contributors
 * @date 2024-03-15
 */
#include "displacementSensor.h"
#include "HAN_IoT_Shield.h" // Required for rightRedLED

/**
 * @brief Construct a new displacementSensor object.
 * Initializes the displacement status to `false` (not displaced) by default.
 * Any specific hardware initialization for a real displacement sensor would go here.
 * For simulation purposes, it ensures the indicator LED (rightRedLED) is initially off.
 */
displacementSensor::displacementSensor() : _displacementStatus{false}
{
    // Initialize displacement sensor: For simulation, ensure LED is off.
    rightRedLED.setState(LED_OFF);
}

/**
 * @brief Destroy the displacementSensor object.
 * Placeholder for any cleanup. Ensures the indicator LED is turned off upon destruction.
 */
displacementSensor::~displacementSensor()
{
    // Stop displacement sensor: For simulation, ensure LED is off.
    rightRedLED.setState(LED_OFF);
}

/**
 * @brief Sets the displacement status and updates the corresponding indicator LED.
 * This function updates the internal `_displacementStatus` flag.
 * It controls the `rightRedLED` on the HAN IoT Shield to visually reflect this status:
 * - If `displacementStatus` is `true` (displaced), `rightRedLED` is turned ON.
 * - If `displacementStatus` is `false` (not displaced), `rightRedLED` is turned OFF.
 * @param displacementStatus The new displacement status: `true` if the trap is
 *                           considered displaced, `false` otherwise.
 */
void displacementSensor::setDisplacementStatus(bool displacementStatus)
{
    _displacementStatus = displacementStatus;

    // Update LED based on displacement status
    if (displacementStatus)
    {
        // Turn on rightRedLED (typically LED2 or similar physical LED) to indicate displacement.
        rightRedLED.setState(LED_ON);
    }
    else
    {
        // Turn off rightRedLED to indicate no displacement.
        rightRedLED.setState(LED_OFF);
    }
}