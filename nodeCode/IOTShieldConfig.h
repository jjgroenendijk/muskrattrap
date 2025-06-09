/*!
 * \file IOTShieldConfig.h
 * \brief Declarations for HAN IoT Shield peripherals and configuration.
 * This header file declares external references to the global objects
 * representing the various components on the HAN IoT Shield, such as
 * potentiometers, buttons, and LEDs. It also declares the configuration
 * function for the shield. These declarations make the shield components
 * accessible from other parts of the application.
 */
#ifndef IOTShieldConfig_h
#define IOTShieldConfig_h

#include <Arduino.h>
#include "HAN_IoT_Shield.h"

// Declare the potmeter objects
/**
 * \brief Extern declaration for Potentiometer 1 (red knob).
 * \sa potmeter1 in IOTShieldConfig.cpp
 */
extern iotShieldPotmeter potmeter1;

/**
 * \brief Extern declaration for Potentiometer 2 (white knob).
 * \sa potmeter2 in IOTShieldConfig.cpp
 */
extern iotShieldPotmeter potmeter2;

// Declare the button objects
/**
 * \brief Extern declaration for the red push button.
 * \sa redButton in IOTShieldConfig.cpp
 */
extern iotShieldButton redButton;

/**
 * \brief Extern declaration for the black push button.
 * \sa blackButton in IOTShieldConfig.cpp
 */
extern iotShieldButton blackButton;

// Declare the LED objects
/**
 * \brief Extern declaration for the left red LED (LED 1).
 * \sa leftRedLED in IOTShieldConfig.cpp
 */
extern iotShieldLED leftRedLED;

/**
 * \brief Extern declaration for the right red LED (LED 2).
 * \sa rightRedLED in IOTShieldConfig.cpp
 */
extern iotShieldLED rightRedLED;

/**
 * \brief Extern declaration for the left green LED (LED 3).
 * \sa leftGreenLED in IOTShieldConfig.cpp
 */
extern iotShieldLED leftGreenLED;

/**
 * \brief Extern declaration for the right green LED (LED 4).
 * \sa rightGreenLED in IOTShieldConfig.cpp
 */
extern iotShieldLED rightGreenLED;

// Heartbeat interval for event/periodic sending (default: 24h, set to 10s for testing)
#define HEARTBEAT_INTERVAL_MS 10000UL


/*!
 * \brief Declares the function to configure the IoT Shield.
 * This function is implemented in IOTShieldConfig.cpp and can be used
 * for any additional setup or configuration required for the IoT shield components.
 * \sa configureIoTShield() in IOTShieldConfig.cpp
 */
void configureIoTShield();

#endif // IOTShieldConfig_h
