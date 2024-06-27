#include "IOTShieldConfig.h"

// Define the potmeter objects
iotShieldPotmeter potmeter1(PIN_POT_RED, -20, 500);
iotShieldPotmeter potmeter2(PIN_POT_WHITE, 0, 100);

// Define the button objects
iotShieldButton redButton(PIN_SWITCH_RED);
iotShieldButton blackButton(PIN_SWITCH_BLACK);

// Define the LED objects
iotShieldLED leftRedLED(PIN_LED_1_RED);
iotShieldLED rightRedLED(PIN_LED_2_RED);
iotShieldLED leftGreenLED(PIN_LED_3_GRN);
iotShieldLED rightGreenLED(PIN_LED_4_GRN);

void configureIoTShield() {
    // Any additional configuration code can go here
}
