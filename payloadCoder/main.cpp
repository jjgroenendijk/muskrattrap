/**
 * @file main.cpp
 * @brief Main file for the payloadCoder project
 * @author Jaap-Jan Groenendijk (github@jjgroenendijk.nl)
 * @date 2024-09-06
 * @version 1.0
 * @copyright Copyright Remko Welling 2022. Creative Commons Attribution-NonCommercial 4.0 International
 * @license CC BY-NC 4.0
 * 
 * \mainpage
 * This project is a simple example of a payload encoder and decoder for a LoRaWAN application.
 * The project consists of two classes: payloadEncoder and payloadDecoder. The payloadEncoder class
 * encodes variables into a single payload, and the payloadDecoder class decodes the payload back into
 * the original variables. The project also contains a unit test that tests the encoder and decoder classes.
 */

#include "decoder.h"
#include "encoder.h"
#include "unitTest.h"

using namespace std;

int main()
{
    // Test 1
    test01();

    // Test 2
    test02();

    return 0;
}