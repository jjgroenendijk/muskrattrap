/*!
 * \file IOTShieldConfig.cpp
 * \brief Instantiation and configuration of HAN IoT Shield peripherals.
 * This file creates global objects for the various components on the
 * HAN IoT Shield, such as potentiometers, buttons, and LEDs,
 * making them available for use throughout the application.
 */
#include "IOTShieldConfig.h"

// Define the potmeter objects
/**
 * \brief Potentiometer 1, typically with a red knob.
 * Mapped to a range of -20 to 500.
 */
iotShieldPotmeter potmeter1(PIN_POT_RED, -20, 500);

/**
 * \brief Potentiometer 2, typically with a white knob.
 * Mapped to a range of 0 to 100.
 */
iotShieldPotmeter potmeter2(PIN_POT_WHITE, 0, 100);

// Define the button objects
/**
 * \brief The red push button on the shield.
 */
iotShieldButton redButton(PIN_SWITCH_RED);

/**
 * \brief The black push button on the shield.
 */
iotShieldButton blackButton(PIN_SWITCH_BLACK);

// Define the LED objects
/**
 * \brief The left red LED (LED 1) on the shield.
 */
iotShieldLED leftRedLED(PIN_LED_1_RED);

/**
 * \brief The right red LED (LED 2) on the shield.
 */
iotShieldLED rightRedLED(PIN_LED_2_RED);

/**
 * \brief The left green LED (LED 3) on the shield.
 */
iotShieldLED leftGreenLED(PIN_LED_3_GRN);

/**
 * \brief The right green LED (LED 4) on the shield.
 */
iotShieldLED rightGreenLED(PIN_LED_4_GRN);

/*!
 * \brief Configures the IoT Shield.
 * This function can be used for any additional setup or
 * configuration required for the IoT shield components beyond
 * their initial instantiation. Currently, it serves as a placeholder.
 */
void configureIoTShield() {
    // Any additional configuration code can go here
}
