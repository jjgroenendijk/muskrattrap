#include "displacementSensor.h"
#include "HAN_IoT_Shield.h"

displacementSensor::displacementSensor() : _displacementStatus{false}
{
    ///< Initialize displacement sensor here
    // Use leftGreenLED (LED3) for displacement indication
    leftGreenLED.setState(LED_OFF);
}

displacementSensor::~displacementSensor()
{
    ///< Stop displacement sensor here
    leftGreenLED.setState(LED_OFF);
}

void displacementSensor::setDisplacementStatus(bool displacementStatus)
{
    _displacementStatus = displacementStatus;

    /// Turn on leftGreenLED depending on the displacement status
    if (displacementStatus)
    {
        ///< Turn on leftGreenLED to indicate that the trap is displaced
        leftGreenLED.setState(LED_ON);
    }
    else
    {
        ///< Turn off leftGreenLED to indicate that the trap is not displaced
        leftGreenLED.setState(LED_OFF);
    }
}