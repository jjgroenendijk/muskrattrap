/**
 * @file main.cpp
 * @brief Main file for the payloadCoder host-side utility.
 * \details This utility is used for testing the payload encoding and decoding logic
 * that might be deployed on a LoRaWAN end node. It executes a series of unit tests.
 * @author Jaap-Jan Groenendijk (github@jjgroenendijk.nl)
 * @date 2024-03-15
 * @version 1.1
 * @version log
 * Version   Date        Note
 * 1.1       2024-03-15  Standardized Doxygen comments, updated date. (Project Contributors)
 * 1.0       2024-09-06  Initial version. (Jaap-Jan Groenendijk)
 * @copyright Copyright Remko Welling 2022. Creative Commons Attribution-NonCommercial 4.0 International
 * @license CC BY-NC 4.0
 * 
 * \mainpage Payload Coder Utility
 * \section intro_sec Introduction
 * This project provides a command-line utility to test the `payloadEncoder`
 * and `payloadDecoder` classes. These classes are designed for creating and
 * parsing compact LoRaWAN payloads.
 *
 * \section classes_sec Classes
 * - \b payloadEncoder: Encodes various sensor readings and status information
 *   into a compact byte array suitable for LoRaWAN transmission.
 * - \b payloadDecoder: Decodes a byte array (payload) received over LoRaWAN
 *   back into the original structured data.
 *
 * \section usage_sec Usage
 * The `main` function in `main.cpp` executes a series of predefined unit tests
 * (e.g., `test01()`, `test02()`, `test03()`) defined in `unitTest.cpp`.
 * These tests verify the correctness of the encoding and decoding processes.
 * Compile and run the executable to see test results.
 *
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