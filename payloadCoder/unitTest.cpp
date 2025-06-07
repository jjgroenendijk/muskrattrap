/**
 * @file unitTest.cpp
 * @brief Implements unit tests for payloadEncoder and payloadDecoder.
 * \details This file contains the definitions for various test functions
 * aimed at verifying the correct operation of the payload encoding and
 * decoding logic. It includes tests for basic functionality, edge cases,
 * and boolean combinations.
 * @author Project Contributors
 * @date 2024-03-15
 */
#include "unitTest.h"
#include "encoder.h"
#include "decoder.h"

#include <iostream> // For std::cout, std::endl
#include <iomanip>  // For std::setw, std::setfill

using namespace std;

/**
 * \brief Test case 01: Basic functionality with typical values.
 * \details This test verifies the core functionality of `payloadEncoder` and
 * `payloadDecoder` by encoding a set of typical, non-edge-case values for all
 * payload fields, then decoding the payload and comparing the results against
 * the original inputs. This serves as a fundamental check
 * of the encode/decode pipeline.
 */
void test01()
{
    // Test 1: known input values
    payloadEncoder encoder; /// Encoder object
    payloadDecoder decoder; /// Decoder object

    // Test 1: initialize test variables
    uint32_t id = 123456;
    uint8_t version = 123;
    bool doorStatus = true;
    bool catchDetect = false;
    bool trapDisplacement = false;
    uint8_t batteryStatus = 123;
    uint32_t unixTime = 1234567890;

    // Test 1: set test variables
    encoder.set_id(id);                             // Give encoder object the id
    encoder.set_version(version);                   // Give encoder object the version
    encoder.set_doorStatus(doorStatus);             // Give encoder object the doorStatus
    encoder.set_catchDetect(catchDetect);           // Give encoder object the catchDetect
    encoder.set_trapDisplacement(trapDisplacement); // Give encoder object the trapDisplacement
    encoder.set_batteryStatus(batteryStatus);       // Give encoder object the batteryStatus
    encoder.set_unixTime(unixTime);                 // Give encoder object the unixTime

    // Test 1: compose payload
    encoder.composePayload();
    // encoder.printPayloadBinary(); // debug

    // Test 1: get payload buffer and size
    uint8_t *payloadBuffer = encoder.getPayload();
    uint8_t payloadSize = encoder.getPayloadSize();

    // Test 1: decode payload
    decoder.setPayload(payloadBuffer);
    decoder.setPayloadSize(payloadSize);
    decoder.decodePayload();

    // encoder.printPayloadEncoded(); // debug
    // decoder.printPayloadDecoded(); // debug

    // Test 1: get decoded variables
    uint32_t result_id = decoder.get_id();
    uint8_t result_version = decoder.get_version();
    bool result_doorStatus = decoder.get_doorStatus();
    bool result_catchDetect = decoder.get_catchDetect();
    bool result_trapDisplacement = decoder.get_trapDisplacement();
    uint8_t result_batteryStatus = decoder.get_batteryStatus();
    uint32_t result_unixTime = decoder.get_unixTime();

    // evaluate test result of test 1
    cout << "Test 1 results " << endl;

    printTestResult("id", id, result_id);
    printTestResult("version", version, result_version);
    printTestResult("doorStatus", doorStatus, result_doorStatus);
    printTestResult("catchDetect", catchDetect, result_catchDetect);
    printTestResult("trapDisplacement", trapDisplacement, result_trapDisplacement);
    printTestResult("batteryStatus", batteryStatus, result_batteryStatus);
    printTestResult("unixTime", unixTime, result_unixTime);
}

/**
 * \brief Test case 02: Edge values (max/min).
 * \details This test uses maximum and minimum possible values for numerical fields
 * (e.g., 0xFFFFFFFF for ID, 0x00 for battery) and varied boolean flags to check
 * how the encoder and decoder handle these edge cases.
 */
void test02()
{
    // Test 2: Edge case values
    payloadEncoder encoder;
    payloadDecoder decoder;

    // Initialize test variables
    uint32_t id = 0xFFFFFFFF;          // Max uint32_t
    uint8_t version = 0xFF;            // Max uint8_t
    bool doorStatus = false;
    bool catchDetect = true;
    bool trapDisplacement = true;
    uint8_t batteryStatus = 0;         // Min uint8_t
    uint32_t unixTime = 0;             // Min uint32_t

    // Set test variables
    encoder.set_id(id);
    encoder.set_version(version);
    encoder.set_doorStatus(doorStatus);
    encoder.set_catchDetect(catchDetect);
    encoder.set_trapDisplacement(trapDisplacement);
    encoder.set_batteryStatus(batteryStatus);
    encoder.set_unixTime(unixTime);

    // Compose payload
    encoder.composePayload();
    // encoder.printPayloadBinary(); // debug

    // Get payload buffer and size
    uint8_t *payloadBuffer = encoder.getPayload();
    uint8_t payloadSize = encoder.getPayloadSize();

    // Decode payload
    decoder.setPayload(payloadBuffer);
    decoder.setPayloadSize(payloadSize);
    decoder.decodePayload();

    // Get decoded variables
    uint32_t result_id = decoder.get_id();
    uint8_t result_version = decoder.get_version();
    bool result_doorStatus = decoder.get_doorStatus();
    bool result_catchDetect = decoder.get_catchDetect();
    bool result_trapDisplacement = decoder.get_trapDisplacement();
    uint8_t result_batteryStatus = decoder.get_batteryStatus();
    uint32_t result_unixTime = decoder.get_unixTime();

    // evaluate test result of test 2
    cout << endl << "Test 2 results " << endl;

    printTestResult("id", id, result_id);
    printTestResult("version", version, result_version);
    printTestResult("doorStatus", doorStatus, result_doorStatus);
    printTestResult("catchDetect", catchDetect, result_catchDetect);
    printTestResult("trapDisplacement", trapDisplacement, result_trapDisplacement);
    printTestResult("batteryStatus", batteryStatus, result_batteryStatus);
    printTestResult("unixTime", unixTime, result_unixTime);
}

/**
 * \brief Prints the formatted result of a single field comparison for a test case.
 * \details This utility function, defined in `unitTest.cpp`, takes the name of the
 * field being tested (type), the original input value, and the decoded result value.
 * It prints these in a tabular format using `std::setw` and `std::setfill` for alignment,
 * followed by "OK" if the input and result match, or "ERROR" otherwise.
 * Its primary Doxygen documentation is in `unitTest.h`.
 * @param type A string describing the value being tested (e.g., "id", "version").
 * @param input The original input value to the encoder.
 * @param result The decoded result value from the decoder.
 */
void printTestResult(const std::string &type, int input, int result)
{
    const char separator = ' ';
    const int width = 16; // Column width for formatted output
    std::cout << std::setw(width) << std::setfill(separator) << type
              << std::setw(width) << std::setfill(separator) << input
              << std::setw(width) << std::setfill(separator) << result;

    // if input and result are the same, print "OK", otherwise print "ERROR"
    if (input == result)
    {
        std::cout << std::setw(width) << std::setfill(separator) << "OK" << std::endl;
    }
    else
    {
        std::cout << std::setw(width) << std::setfill(separator) << "ERROR" << std::endl;
    }
}

/**
 * \brief Test case 03: All boolean combinations.
 * \details This test iterates through all 8 possible combinations of the three boolean
 * status flags (`doorStatus`, `catchDetect`, `trapDisplacement`) to ensure they are
 * encoded and decoded correctly, particularly their packing into a single byte.
 * Other numerical fields are kept constant for this test.
 */
void test03()
{
    cout << endl
         << "Test 3 results (Boolean Combinations)" << endl;
    payloadEncoder encoder;
    payloadDecoder decoder;

    // Constant values for non-boolean fields
    const uint32_t id = 777;
    const uint8_t version = 7;
    const uint8_t batteryStatus = 77;
    const uint32_t unixTime = 7777777;

    encoder.set_id(id);
    encoder.set_version(version);
    encoder.set_batteryStatus(batteryStatus);
    encoder.set_unixTime(unixTime);

    for (int i = 0; i < 8; ++i)
    {
        bool doorStatus = (i >> 2) & 1;       // Bit 2
        bool catchDetect = (i >> 1) & 1;      // Bit 1
        bool trapDisplacement = i & 1;        // Bit 0

        cout << "Testing: DS=" << doorStatus << ", CD=" << catchDetect << ", TD=" << trapDisplacement << endl;

        encoder.set_doorStatus(doorStatus);
        encoder.set_catchDetect(catchDetect);
        encoder.set_trapDisplacement(trapDisplacement);

        encoder.composePayload();

        uint8_t *payloadBuffer = encoder.getPayload();
        uint8_t payloadSize = encoder.getPayloadSize();

        decoder.setPayload(payloadBuffer);
        decoder.setPayloadSize(payloadSize);
        decoder.decodePayload();

        // Verify all fields, focusing on booleans
        printTestResult("  id", id, decoder.get_id());
        printTestResult("  version", version, decoder.get_version());
        printTestResult("  doorStatus", doorStatus, decoder.get_doorStatus());
        printTestResult("  catchDetect", catchDetect, decoder.get_catchDetect());
        printTestResult("  trapDisplacement", trapDisplacement, decoder.get_trapDisplacement());
        printTestResult("  batteryStatus", batteryStatus, decoder.get_batteryStatus());
        printTestResult("  unixTime", unixTime, decoder.get_unixTime());
        cout << "---" << endl;
    }
}
