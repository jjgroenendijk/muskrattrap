/*!
 * \file batterySensor.cpp
 * \brief Implementation of the batterySensor class.
 * This file contains the implementation for the batterySensor class,
 * which is responsible for providing simulated battery level readings,
 * typically by reading a value from a potentiometer on the HAN IoT Shield.
 */
#include "batterySensor.h"

/**
 * @brief Constructor for the batterySensor class.
 * Initializes the battery level to 0.
 * Any specific hardware initialization for a real battery sensor would go here.
 */
batterySensor::batterySensor() : _batteryLevel{0}
{
    ///< Initialize battery sensor here
}

/**
 * @brief Destructor for the batterySensor class.
 * Handles any cleanup required for the battery sensor.
 */
batterySensor::~batterySensor()
{
    ///< Stop battery sensor here
}

/**
 * @brief Gets the current battery level.
 * Reads the value from potentiometer 2 (potmeter2) on the HAN IoT Shield
 * to simulate a battery level reading. The raw potentiometer value is
 * cast to a uint32_t.
 * @return The current battery level as a uint32_t value.
 *         The range depends on the potentiometer's configuration (0-100 in this case).
 */
uint32_t batterySensor::getBatteryLevel()
{
    /// Read potmeter 2 to get battery level

    _batteryLevel = static_cast<uint32_t>(potmeter2.getValue());
    return _batteryLevel;
}

/**
 * @brief Sets the battery level.
 * This method allows for manually setting the battery level, which can be
 * useful for testing or simulation purposes where an actual hardware sensor
 * reading is not desired.
 * @param batteryLevel The battery level to set.
 */
void batterySensor::setBatteryLevel(uint32_t batteryLevel)
{
    _batteryLevel = batteryLevel;
}