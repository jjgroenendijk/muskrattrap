#include "doorSensor.h"
#include "HAN_IoT_Shield.h"


doorSensor::doorSensor() : _doorStatus{false}
{   
    ///< Initialize door sensor here
}

doorSensor::~doorSensor()
{
    ///< Stop door sensor here
}

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