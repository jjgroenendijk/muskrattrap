/**
 * @file unitTest.h
 * @brief Declarations for unit test functions for the payload encoder and decoder.
 * This file contains prototypes for functions designed to test the functionality
 * of the `payloadEncoder` and `payloadDecoder` classes, ensuring data is
 * encoded and decoded correctly.
 * @author Project Contributors
 * @date 2024-03-15
 * @version 1.0
 */
#ifndef unitTest_H
#define unitTest_H

#include <string>

/**
 * @brief Test case 01: Basic functionality and simple values.
 * \details This test typically encodes a predefined set of straightforward values
 * (ID, version, statuses, battery, time) using `payloadEncoder`, then decodes
 * the resulting payload using `payloadDecoder`. It verifies that the decoded
 * values exactly match the original inputs. This serves as a fundamental check
 * of the encode/decode pipeline.
 */
void test01();

/**
 * @brief Test case 02: Testing with zero or edge values.
 * \details This test focuses on encoding and decoding scenarios involving zero values
 * for numerical fields and potentially edge cases for boolean flags or other data.
 * It helps ensure robustness and correct handling of minimal or boundary inputs.
 */
void test02();

/**
 * @brief Test case 03: Boolean combinations in payloadEncoder and payloadDecoder.
 * @details This test iterates through all 8 combinations of `doorStatus`, `catchDetect`,
 * and `trapDisplacement` to ensure correct encoding and decoding of these packed booleans.
 * It uses fixed values for other payload fields (id, version, batteryStatus, unixTime).
 * For each combination, it encodes the payload, decodes it, and then prints the 
 * comparison results for all fields using the `printTestResult` helper function.
 */
void test03();

/**
 * @brief Prints the result of a single test comparison for a named field.
 * \details This utility function is used by the test cases to output the original
 * input value and the decoded result value for a specific field, along with
 * a status indicating whether they match.
 * @param type A string describing the value being tested (e.g., "ID", "Version", "Door Status").
 * @param input The original input value provided to the encoder.
 * @param result The decoded result value obtained from the decoder.
 */
void printTestResult(const std::string& type, int input, int result);

#endif // unitTest_H
