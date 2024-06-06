/*

uint32_t id;           // Identification number (4 bytes)
uint8_t version;       // Payload version number (1 byte)
bool doorStatus;       // Door status (1 bit)
bool catchDetect;      // Catch detection (1 bit)
bool trapDisplacement; // Trap displacement (1 bit)
uint8_t batteryStatus; // Battery status (1 byte)
uint32_t unixTime;     // Date and time (4 bytes)

*/

#include <iostream> // cout, endl
#include <stdint.h> // uint8_t, uint16_t, uint32_t

#include "decoder.h"
#include "encoder.h"

using namespace std;

int main()
{
    // Test 1: known input 1
    payloadEncoder encoder; /// Encoder object
    payloadDecoder decoder; /// Decoder object

    int testVariable1 = 0; /// Test variable containing value that shall be transferred
    int testVariable2 = 0; /// Test variable containing value that shall be transferred

    encoder.setDemoVariable1(testVariable1); // Set variable in encoder object.
    encoder.setDemoVariable2(testVariable2); // Set variable in encoder object.

    int id = 123456;
    int version = 123;
    bool doorStatus = true;
    bool catchDetect = false;
    bool trapDisplacement = false;
    int batteryStatus = 123;
    int unixTime = 1234567890;

    encoder.set_id(id);                             // Give encoder object the id
    encoder.set_version(version);                   // Give encoder object the version
    encoder.set_doorStatus(doorStatus);             // Give encoder object the doorStatus
    encoder.set_catchDetect(catchDetect);           // Give encoder object the catchDetect
    encoder.set_trapDisplacement(trapDisplacement); // Give encoder object the trapDisplacement
    encoder.set_batteryStatus(batteryStatus);       // Give encoder object the batteryStatus
    encoder.set_unixTime(unixTime);                 // Give encoder object the unixTime

    encoder.composePayload();
    encoder.printPayloadBinary();

    uint8_t *payloadBuffer = encoder.getPayload();
    uint8_t payloadSize = encoder.getPayloadSize();

    decoder.setPayload(payloadBuffer);
    decoder.setPayloadSize(payloadSize);
    decoder.decodePayload();

    // debug
    encoder.printPayloadEncoded();
    decoder.printPayloadDecoded();

    int result1 = decoder.getDemoVariable1(); // Retrieve variable from decoder object and save in result1.
    int result2 = decoder.getDemoVariable2(); // Retrieve variable from decoder object and save in result2.

    // evaluate test result of test 1
    cout << "Test 1 result: ";
    if (result1 == testVariable1)
    {
        cout << "PASS" << endl;
    }
    else
    {
        cout << "FAIL" << endl;
    }

    // evaluate test result of test 2
    cout << "Test 2 result: ";
    if (result2 == testVariable2)
    {
        cout << "PASS" << endl;
    }
    else
    {
        cout << "FAIL" << endl;
    }

    return 0;
}