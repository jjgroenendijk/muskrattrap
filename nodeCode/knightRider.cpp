#include "knightRider.h"


void knightRider(void) {
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
