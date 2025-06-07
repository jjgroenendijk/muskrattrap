#ifndef DOORSENSOR_H
#define DOORSENSOR_H

#include "IOTShieldConfig.h"

/// An open door is set to 0 (false), a closed door is set to 1 (true)

/**
 * @brief Class for managing the door sensor.
 */
class doorSensor /// DoorStatus class declaration:
{
private:
    bool _doorStatus; ///< Stores the current status of the door (true for closed, false for open).

public:
    /**
     * @brief Construct a new door Sensor object.
     */
    doorSensor();  /// constructor declaration, initializes the door sensor

    /**
     * @brief Destroy the door Sensor object.
     */
    ~doorSensor(); /// destructor declaration, cleans up the door sensor

    /**
     * @brief Get the current door status.
     * 
     * @return true if the door is closed, false if open.
     */
    bool getDoorStatus() { return _doorStatus; }

    /**
     * @brief Set the door status and control LED2 accordingly.
     * 
     * @param doorStatus True if the door is closed, false if open.
     */
    void setDoorStatus(bool doorStatus);
};

#endif // DOORSENSOR_H