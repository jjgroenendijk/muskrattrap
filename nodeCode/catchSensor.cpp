#include "catchSensor.h"

catchSensor::catchSensor() : _catchStatus{false}
{
    ///< Initialize catch sensor here
}

catchSensor::~catchSensor()
{
    ///< Stop catch sensor here
}

void catchSensor::setCatchStatus(bool catchStatus)
{
    _catchStatus = catchStatus;

    if (catchStatus)
    {
        ///< Turn on LED2 to indicate that the catch is detected
        leftGreenLED.setState(LED_ON);
    }
    else
    {
        ///< Turn off LED2 to indicate that the catch is not detected
        leftGreenLED.setState(LED_OFF);
    }
}