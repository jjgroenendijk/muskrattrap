/*!
 * \file batterySensor.cpp
 * \brief Implementation of the batterySensor class.
 * This file contains the implementation for the batterySensor class,
 * which is responsible for providing simulated battery level readings,
 * typically by reading a value from a potentiometer on the HAN IoT Shield.
 */
#include "batterySensor.h"

// Assuming PIN_LED_4_GRN (pin 6) is a PWM pin on Leonardo and will be used for battery.
// This object needs to be accessible, ensure it's declared in IOTShieldConfig.h and defined in IOTShieldConfig.cpp
// For example: extern iotShieldLED rightGreenLED; (if rightGreenLED is on a PWM pin like 6)

/**
 * @brief Constructor for the batterySensor class.
 * Initializes the battery level to 0 and stores the provided LED object.
 * @param led Pointer to the iotShieldLED object used for battery indication.
 */
batterySensor::batterySensor(iotShieldLED* led) : _batteryLevel{0}, _batteryLed{led}
{
    if (_batteryLed) {
        // Ensure the LED pin is set to OUTPUT, which should be handled by iotShieldLED constructor.
        // For PWM, no special pinMode is usually needed beyond OUTPUT.
    }
}

/**
 * @brief Destructor for the batterySensor class.
 * Handles any cleanup required for the battery sensor.
 * Turns off the battery LED if it was assigned.
 */
batterySensor::~batterySensor()
{
    if (_batteryLed) {
        analogWrite(_batteryLed->getPin(), 0); // Turn off LED by setting PWM to 0
    }
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
    // Read potmeter 2 to get battery level, potmeter2 is configured 0-100
    _batteryLevel = static_cast<uint32_t>(potmeter2.getValue());
    // Update LED indicator whenever battery level is read and potentially changed
    updateLedIndicator(); 
    return _batteryLevel;
}

/**
 * @brief Sets the battery level and updates the LED indicator.
 * This method allows for manually setting the battery level, which can be
 * useful for testing or simulation purposes where an actual hardware sensor
 * reading is not desired.
 * @param batteryLevel The battery level to set (expected 0-100).
 */
void batterySensor::setBatteryLevel(uint32_t batteryLevel)
{
    _batteryLevel = batteryLevel;
    if (_batteryLevel > 100) _batteryLevel = 100; // Cap at 100 for percentage
    // Update LED indicator when battery level is set manually
    updateLedIndicator();
}

/**
 * @brief Updates the battery indicator LED based on the current battery level.
 * Uses PWM to control LED brightness. Assumes battery level is 0-100.
 */
void batterySensor::updateLedIndicator() {
    if (_batteryLed) {
        // Map battery level (0-100) to PWM value (0-255)
        uint8_t pwmValue = map(_batteryLevel, 0, 100, 0, 255);
        analogWrite(_batteryLed->getPin(), pwmValue);
        // For debugging PWM value:
        // debugSerial.print("DEBUG: Battery LED PWM set to: ");
        // debugSerial.println(pwmValue);
    } else {
        // debugSerial.println("DEBUG: Battery LED object not set.");
    }
}

// Need to add a getPin() method to iotShieldLED class in HAN_IoT_Shield.h/cpp
// to allow batterySensor to get the pin number for analogWrite.