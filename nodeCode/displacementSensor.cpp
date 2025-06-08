#include "displacementSensor.h"
#include "HAN_IoT_Shield.h"

displacementSensor::displacementSensor() : _displacementStatus{false}
{
    ///< Initialize displacement sensor here
}

displacementSensor::~displacementSensor()
{
    ///< Stop displacement sensor here
}

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