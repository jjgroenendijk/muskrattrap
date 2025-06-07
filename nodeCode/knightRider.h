/**
 * @file knightRider.h
 * @brief Declaration for the knightRider LED animation function.
 * This file contains the function prototype for a "Knight Rider" style
 * LED animation sequence, typically implemented using the LEDs on the
 * HAN IoT Shield.
 * @author Project Contributors
 * @date 2024-03-15
 * @version 1.0
 */
#ifndef KNIGHTRIDER_H
#define KNIGHTRIDER_H

#include "IOTShieldConfig.h"

/**
 * @brief Executes a "Knight Rider" style LED animation on the HAN IoT Shield LEDs.
 * This function creates a visual effect where the LEDs light up sequentially,
 * moving back and forth, similar to the scanner light on the KITT car from
 * the Knight Rider TV series. It utilizes the LEDs (leftRedLED, rightRedLED,
 * leftGreenLED, rightGreenLED) declared in IOTShieldConfig.h.
 */
void knightRider(void);

#endif
