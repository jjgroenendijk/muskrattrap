/**
 * @file IOTShieldConfig.h
 * @brief Configuration and global external declarations for HAN IoT Shield components.
 * This file declares external instances of the HAN IoT Shield library classes,
 * making them globally accessible across different source files in an Arduino project.
 * It also provides a function to initialize these components.
 * @author Project Contributors
 * @date 2024-03-15
 * @version 1.0
 */
#ifndef IOTShieldConfig_h
#define IOTShieldConfig_h

#include <Arduino.h>
#include "HAN_IoT_Shield.h"

// Declare the potmeter objects
extern iotShieldPotmeter potmeter1;     ///< \brief Extern declaration for Potentiometer 1 on the HAN IoT Shield.
extern iotShieldPotmeter potmeter2;     ///< \brief Extern declaration for Potentiometer 2 on the HAN IoT Shield.

// Declare the button objects
extern iotShieldButton redButton;       ///< \brief Extern declaration for the Red Pushbutton on the HAN IoT Shield.
extern iotShieldButton blackButton;     ///< \brief Extern declaration for the Black Pushbutton on the HAN IoT Shield.

// Declare the LED objects
extern iotShieldLED leftRedLED;        ///< \brief Extern declaration for the Left Red LED (LED1) on the HAN IoT Shield.
extern iotShieldLED rightRedLED;       ///< \brief Extern declaration for the Right Red LED (LED2) on the HAN IoT Shield.
extern iotShieldLED leftGreenLED;      ///< \brief Extern declaration for the Left Green LED (LED3) on the HAN IoT Shield.
extern iotShieldLED rightGreenLED;     ///< \brief Extern declaration for the Right Green LED (LED4) on the HAN IoT Shield.

/**
 * @brief Initializes and configures the components on the HAN IoT Shield.
 * This function typically sets up the pin modes for the LEDs, buttons,
 * and other peripherals connected to the shield. It should be called once
 * in the `setup()` routine of an Arduino sketch to ensure all shield
 * peripherals are ready for use.
 */
void configureIoTShield();

#endif // IOTShieldConfig_h
