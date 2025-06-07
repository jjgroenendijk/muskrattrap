/**
 * @file knightRider.cpp
 * @brief Implements the knightRider LED animation function.
 * This file contains the definition of the `knightRider` function, which
 * creates a "Knight Rider" style scanning light effect using the LEDs
 * on the HAN IoT Shield.
 * @author Project Contributors
 * @date 2024-03-15
 */
#include "knightRider.h"

/**
 * @brief Executes the Knight Rider LED animation sequence.
 * \details The animation cycles through the LEDs in the following order:
 * Left Red -> Left Green -> Right Red -> Right Green, then reverses:
 * Right Green -> Right Red -> Left Green -> Left Red.
 * Each LED is turned on for a short duration (100ms) before being turned off,
 * creating a scanning effect.
 */
void knightRider(void) {
    // Sequence: LED1 (Left Red) -> LED3 (Left Green) -> LED2 (Right Red) -> LED4 (Right Green)
    leftRedLED.setState(LED_ON);
    delay(100);
    leftRedLED.setState(LED_OFF);
    leftGreenLED.setState(LED_ON);
    delay(100);
    leftGreenLED.setState(LED_OFF);
    rightRedLED.setState(LED_ON);
    delay(100);
    rightRedLED.setState(LED_OFF);
    rightGreenLED.setState(LED_ON);
    delay(100);
    rightGreenLED.setState(LED_OFF);
    rightGreenLED.setState(LED_ON);
    delay(100);
    rightGreenLED.setState(LED_OFF);
    rightRedLED.setState(LED_ON);
    delay(100);
    rightRedLED.setState(LED_OFF);
    leftGreenLED.setState(LED_ON);
    delay(100);
    leftGreenLED.setState(LED_OFF);
    leftRedLED.setState(LED_ON);
    delay(100);
    leftRedLED.setState(LED_OFF);
}
