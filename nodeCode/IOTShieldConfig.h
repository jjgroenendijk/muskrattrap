#ifndef IOTShieldConfig_h
#define IOTShieldConfig_h

#include <Arduino.h>
#include "HAN_IoT_Shield.h"

// Declare the potmeter objects
extern iotShieldPotmeter potmeter1;
extern iotShieldPotmeter potmeter2;

// Declare the button objects
extern iotShieldButton redButton;
extern iotShieldButton blackButton;

// Declare the LED objects
extern iotShieldLED leftRedLED;
extern iotShieldLED rightRedLED;
extern iotShieldLED leftGreenLED;
extern iotShieldLED rightGreenLED;


// Function to configure the HAN IoT Shield
void configureIoTShield();

#endif // IOTShieldConfig_h
