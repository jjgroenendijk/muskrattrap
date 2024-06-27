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
        ///< Turn on LED1 to indicate that the catch is detected
        leftRedLED.setState(LED_ON);
    }
    else
    {
        ///< Turn off LED1 to indicate that the catch is not detected
        leftRedLED.setState(LED_OFF);
    }
}