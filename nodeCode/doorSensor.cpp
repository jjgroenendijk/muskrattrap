/**
 * @file doorSensor.cpp
 * @brief Implements the doorSensor class for simulating door status.
 * This file contains method definitions for the doorSensor class, which
 * simulates a door's open/closed state and uses the leftRedLED on the
 * HAN IoT Shield to visually indicate this status.
 * Convention: `_doorStatus = true` means door closed, `_doorStatus = false` means door open.
 * @author Project Contributors
 * @date 2024-03-15
 */
#include "doorSensor.h"
#include "HAN_IoT_Shield.h" // Required for leftRedLED

/**
 * @brief Construct a new doorSensor object.
 * Initializes the door status to `false` (open) by default.
 * For simulation, it ensures the indicator LED (leftRedLED) is set accordingly (OFF for open).
 * Any specific hardware initialization for a real door sensor would go here.
 */
doorSensor::doorSensor() : _doorStatus{false} // Default to door open
{   
    // Initialize door sensor: For simulation, LED OFF indicates door open.
    leftRedLED.setState(LED_OFF);
}

/**
 * @brief Destroy the doorSensor object.
 * Placeholder for any cleanup. Ensures the indicator LED is turned off upon destruction,
 * which is a safe default state.
 */
doorSensor::~doorSensor()
{
    // Stop door sensor: For simulation, ensure LED is off.
    leftRedLED.setState(LED_OFF);
}

/**
 * @brief Sets the door status and updates the corresponding indicator LED.
 * This function updates the internal `_doorStatus` flag.
 * It controls the `leftRedLED` on the HAN IoT Shield:
 * - If `doorStatus` is `true` (door closed), `leftRedLED` is turned ON.
 * - If `doorStatus` is `false` (door open), `leftRedLED` is turned OFF.
 * @param doorStatus The new door status: `true` if the door is considered closed,
 *                   `false` if considered open.
 */
void doorSensor::setDoorStatus( bool doorStatus )
{
    _doorStatus = doorStatus;

    // Update LED based on door status
    if (doorStatus) // doorStatus is true (closed)
    {
        // Turn on leftRedLED to indicate the door is closed.
        leftRedLED.setState(LED_ON);
    }
    else // doorStatus is false (open)
    {
        // Turn off leftRedLED to indicate the door is open.
        leftRedLED.setState(LED_OFF);
    }
}