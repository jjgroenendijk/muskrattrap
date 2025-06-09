#ifndef NODECODE_DOORSENSOR_H
#define NODECODE_DOORSENSOR_H

#include "IOTShieldConfig.h"
#include "HAN_IoT_Shield.h" // For leftRedLED

/**
 * @file doorSensor.h
 * @brief Abstraction for the door sensor on the muskrat trap node.
 *
 * Provides methods to read and update the door status.
 */

/// An open door is set to 0 (false), a closed door is set to 1 (true)

class doorSensor /// DoorStatus class declaration:
{
private:
    bool _doorStatus;

public:
    doorSensor();  /// constructor declaration, initializes the door sensor
    ~doorSensor(); /// destructor declaration, cleans up the door sensor

    /**
     * @brief Get the current door status.
     * @return True if closed, false if open
     */
    bool getDoorStatus() const;

    /**
     * @brief Update the door status from hardware or simulation.
     */
    void update();

    void setDoorStatus(bool doorStatus);
};

#endif // NODECODE_DOORSENSOR_H