/**
 * @file doorSensor.h
 * @brief Defines the doorSensor class for managing a simulated door status.
 * This file contains the declaration of the doorSensor class, which simulates
 * a door sensor (open/closed) and uses an LED on the HAN IoT Shield to
 * indicate the status. Convention: true indicates door closed, false indicates door open.
 * @author Project Contributors
 * @date 2024-03-15
 * @version 1.1
 */
#ifndef DOORSENSOR_H
#define DOORSENSOR_H

#include "IOTShieldConfig.h"

/**
 * @class doorSensor
 * @brief Manages the status of a simulated door sensor.
 * This class tracks whether a door is considered open or closed.
 * It uses the convention that `true` means the door is closed,
 * and `false` means the door is open. The status can be indicated
 * visually using an LED on the HAN IoT Shield.
 */
class doorSensor
{
private:
    bool _doorStatus; ///< Stores the current status of the door (true for closed, false for open).

public:
    /**
     * @brief Construct a new doorSensor object.
     * Initializes the door status, typically to a default state (e.g., closed or open based on application logic).
     */
    doorSensor();

    /**
     * @brief Destroy the doorSensor object.
     * Performs cleanup if necessary.
     */
    ~doorSensor();

    /**
     * @brief Get the current door status.
     * @return bool True if the door is considered closed, false if it's considered open.
     */
    bool getDoorStatus() { return _doorStatus; }

    /**
     * @brief Set the door status and updates an indicator LED.
     * Controls an LED (typically LED2 on HAN IoT Shield) based on the door status:
     * LED ON might indicate door open, and LED OFF might indicate door closed, or vice-versa,
     * depending on the specific implementation in the .cpp file.
     * @param doorStatus The new door status to set (true for closed, false for open).
     */
    void setDoorStatus(bool doorStatus);
};

#endif // DOORSENSOR_H