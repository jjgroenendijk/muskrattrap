/**
 * @file batterySensor.cpp
 * @brief Implements the batterySensor class for simulating battery level readings.
 * This file contains the method definitions for the batterySensor class,
 * which uses potentiometer 2 on the HAN IoT Shield to simulate battery voltage.
 * @author Project Contributors
 * @date 2024-03-15
 */
#include "batterySensor.h"

/**
 * @brief Construct a new battery Sensor::battery Sensor object.
 *
 * Initializes the internal battery level to 0.
 * Additional hardware initialization for the battery sensor (if any) should be placed here.
 */
batterySensor::batterySensor() : _batteryLevel{0}
{
    // Initialize battery sensor here (e.g., configure ADC pin if not handled by HAN_IoT_Shield)
}

/**
 * @brief Destroy the battery Sensor::battery Sensor object.
 *
 * Placeholder for any cleanup operations needed by the battery sensor.
 */
batterySensor::~batterySensor()
{
    // Stop battery sensor here (e.g., disable ADC or related peripherals if necessary)
}

/**
 * @brief Reads the current battery level from potentiometer 2.
 *
 * The value read from potentiometer 2 (which simulates the battery voltage)
 * is cast to a uint32_t and stored in the private member _batteryLevel before being returned.
 * @return uint32_t The current battery level as a raw ADC value (typically 0-1023).
 */
uint32_t batterySensor::getBatteryLevel()
{
    // Read potmeter 2 to get battery level
    _batteryLevel = static_cast<uint32_t>(potmeter2.getValue());
    return _batteryLevel;
}

/**
 * @brief Sets the internal battery level to a specified value.
 *
 * This function is primarily for simulation or testing purposes, allowing the battery level
 * to be set programmatically.
 * @param batteryLevel The raw ADC value to set as the current battery level.
 */
void batterySensor::setBatteryLevel(uint32_t batteryLevel)
{
    _batteryLevel = batteryLevel;
}