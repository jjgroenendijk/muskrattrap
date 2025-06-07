#include "doorSensor.h"
#include "HAN_IoT_Shield.h"

/**
 * @brief Construct a new door Sensor::door Sensor object
 * 
 */
doorSensor::doorSensor() : _doorStatus{false}
{   
    ///< Initialize door sensor here
}

/**
 * @brief Destroy the door Sensor::door Sensor object
 * 
 */
doorSensor::~doorSensor()
{
    ///< Stop door sensor here
}

/**
 * @brief Set the door status and control LED1 accordingly.
 * 
 * @param doorStatus True if the door is closed, false if open.
 */
void doorSensor::setDoorStatus( bool doorStatus )
{
    _doorStatus = doorStatus;

    /// Turn on LED1 depending on the door status
    if (doorStatus)
    {
        ///< Turn on LED1 to indicate that the door is closed
        leftRedLED.setState(LED_ON);
    }
    else
    {
        ///< Turn off LED1 to indicate that the door is open
        leftRedLED.setState(LED_OFF);
    }
}