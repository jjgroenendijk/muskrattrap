#include "displacementSensor.h"
#include "HAN_IoT_Shield.h"

/**
 * @brief Construct a new displacement Sensor::displacement Sensor object
 * 
 */
displacementSensor::displacementSensor() : _displacementStatus{false}
{
    ///< Initialize displacement sensor here
}

/**
 * @brief Destroy the displacement Sensor::displacement Sensor object
 * 
 */
displacementSensor::~displacementSensor()
{
    ///< Stop displacement sensor here
}

/**
 * @brief Set the displacement status and control LED3 accordingly.
 * 
 * @param displacementStatus True if the trap is displaced, false otherwise.
 */
void displacementSensor::setDisplacementStatus(bool displacementStatus)
{
    _displacementStatus = displacementStatus;

    /// Turn on LED3 depending on the displacement status
    if (displacementStatus)
    {
        ///< Turn on LED3 to indicate that the trap is displaced
        rightRedLED.setState(LED_ON);
    }
    else
    {
        ///< Turn off LED3 to indicate that the trap is not displaced
        rightRedLED.setState(LED_OFF);
    }
}