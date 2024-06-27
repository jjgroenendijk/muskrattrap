#include "batterySensor.h"

batterySensor::batterySensor() : _batteryLevel{0}
{
    ///< Initialize battery sensor here
}

batterySensor::~batterySensor()
{
    ///< Stop battery sensor here
}

uint32_t batterySensor::getBatteryLevel()
{
    /// Read potmeter 2 to get battery level

    _batteryLevel = static_cast<uint32_t>(potmeter2.getValue());
    return _batteryLevel;
}

void batterySensor::setBatteryLevel(uint32_t batteryLevel)
{
    _batteryLevel = batteryLevel;
}