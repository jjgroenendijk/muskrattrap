#ifndef unitTest_H
#define unitTest_H

#include <string>


void test01();

void test02();

/**
 * @brief Test case for boolean combinations in payloadEncoder and payloadDecoder.
 * 
 * This test iterates through all 8 combinations of doorStatus, catchDetect, 
 * and trapDisplacement to ensure correct encoding and decoding of the packed booleans.
 * It uses fixed values for other payload fields (id, version, batteryStatus, unixTime).
 * For each combination, it encodes the payload, decodes it, and then prints the 
 * comparison results for all fields using the printTestResult helper function.
 */
void test03();

void printTestResult(const std::string& type, int input, int result);

#endif // unitTest_H
