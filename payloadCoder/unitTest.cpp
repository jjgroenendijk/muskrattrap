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

    const char separator = ' ';
    const int width = 16;

    // evaluate test result of test 1
    cout << "Test 1 results " << endl;
    cout << setw(width) << setfill(separator) << "Type" << setw(width) << setfill(separator) << "INPUT" << setw(width) << "RESULT" << endl;
    cout << setw(width) << setfill(separator) << "id" << setw(width) << setfill(separator) << id << setw(width) << result_id << endl;
    cout << setw(width) << setfill(separator) << "version" << setw(width) << setfill(separator) << version << setw(width) << result_version << endl;
    cout << setw(width) << setfill(separator) << "doorStatus" << setw(width) << setfill(separator) << doorStatus << setw(width) << result_doorStatus << endl;
    cout << setw(width) << setfill(separator) << "catchDetect" << setw(width) << setfill(separator) << catchDetect << setw(width) << result_catchDetect << endl;
    cout << setw(width) << setfill(separator) << "trapDisplacement" << setw(width) << setfill(separator) << trapDisplacement << setw(width) << result_trapDisplacement << endl;
    cout << setw(width) << setfill(separator) << "batteryStatus" << setw(width) << setfill(separator) << batteryStatus << setw(width) << result_batteryStatus << endl;
    cout << setw(width) << setfill(separator) << "unixTime" << setw(width) << setfill(separator) << unixTime << setw(width) << result_unixTime << endl;
}

void printFixedWidth(const std::string &type, int input, int result)
{
    const char separator = ' ';
    const int width = 16;
    std::cout << std::setw(width) << std::setfill(separator) << type
              << std::setw(width) << std::setfill(separator) << input
              << std::setw(width) << std::setfill(separator) << result
              << std::endl;
}