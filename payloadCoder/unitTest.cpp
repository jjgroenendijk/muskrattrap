#include "unitTest.h"
#include "encoder.h"
#include "decoder.h"

#include <iostream> // cout, endl // debugging only
#include <iomanip>  // setw for table formatting

using namespace std;

void test01()
{

    // Test 1: known input 1
    payloadEncoder encoder; /// Encoder object
    payloadDecoder decoder; /// Decoder object

    // Test 1: initialize test variables
    int id = 123456;
    int version = 123;
    bool doorStatus = true;
    bool catchDetect = false;
    bool trapDisplacement = false;
    int batteryStatus = 123;
    int unixTime = 1234567890;

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
    encoder.printPayloadBinary(); // debug

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
    int result_id = decoder.get_id();
    int result_version = decoder.get_version();
    bool result_doorStatus = decoder.get_doorStatus();
    bool result_catchDetect = decoder.get_catchDetect();
    bool result_trapDisplacement = decoder.get_trapDisplacement();
    int result_batteryStatus = decoder.get_batteryStatus();
    int result_unixTime = decoder.get_unixTime();

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
 * @brief This function tests the payloadEncoder and payloadDecoder classes.
 * 
 * It sets various values for the payloadEncoder object, composes the payload,
 * prints the binary representation of the payload, and then decodes the payload
 * using the payloadDecoder object. Finally, it compares the decoded values with
 * the original values and prints the test results.
 */
void test02()
{

    // Test 2

    // Create encoder and decoder objects
    payloadEncoder encoder;
    payloadDecoder decoder;

    // Initialize test variables
    int id = 123456;
    int version = 1237878;
    bool doorStatus = 0;
    bool catchDetect = 2;
    bool trapDisplacement = false;
    int batteryStatus = -1;
    int unixTime = 1.0;

    // Set test variables
    encoder.set_id(id);                             // Give encoder object the id
    encoder.set_version(version);                   // Give encoder object the version
    encoder.set_doorStatus(doorStatus);             // Give encoder object the doorStatus
    encoder.set_catchDetect(catchDetect);           // Give encoder object the catchDetect
    encoder.set_trapDisplacement(trapDisplacement); // Give encoder object the trapDisplacement
    encoder.set_batteryStatus(batteryStatus);       // Give encoder object the batteryStatus
    encoder.set_unixTime(unixTime);                 // Give encoder object the unixTime

    // Compose payload
    encoder.composePayload();
    encoder.printPayloadBinary(); // debug

    // Get payload buffer and size
    uint8_t *payloadBuffer = encoder.getPayload();
    uint8_t payloadSize = encoder.getPayloadSize();

    // Decode payload
    decoder.setPayload(payloadBuffer);
    decoder.setPayloadSize(payloadSize);
    decoder.decodePayload();

    // Get decoded variables
    int result_id = decoder.get_id();
    int result_version = decoder.get_version();
    bool result_doorStatus = decoder.get_doorStatus();
    bool result_catchDetect = decoder.get_catchDetect();
    bool result_trapDisplacement = decoder.get_trapDisplacement();
    int result_batteryStatus = decoder.get_batteryStatus();
    int result_unixTime = decoder.get_unixTime();

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

void printTestResult(const std::string &type, int input, int result)
{
    const char separator = ' ';
    const int width = 16;
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