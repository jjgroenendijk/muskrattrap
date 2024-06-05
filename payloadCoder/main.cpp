#include <iostream>     // cout, endl
#include <stdint.h>     // uint8_t, uint16_t, uint32_t

#include "decoder.h"
#include "encoder.h"

using namespace std;

struct payload_t {
    uint32_t id;          // Identification number (4 bytes)
    uint8_t version;      // Payload version number (1 byte)
    bool doorStatus;      // Door status (1 bit)
    bool catchDetect;     // Catch detection (1 bit)
    bool trapDisplacement; // Trap displacement (1 bit)
    uint8_t batteryStatus; // Battery status (1 byte)
    uint32_t unixTime;    // Date and time (4 bytes)
};

void printPayload(payload_t payload)
{
    cout << "ID: " << payload.id << endl;
    cout << "Version: " << static_cast<int>(payload.version) << endl;
    cout << "Door status: " << payload.doorStatus << endl;
    cout << "Catch detection: " << payload.catchDetect << endl;
    cout << "Trap displacement: " << payload.trapDisplacement << endl;
    cout << "Battery status: " << static_cast<int>(payload.batteryStatus) << endl;
    cout << "Unix time: " << payload.unixTime << endl;
}

int main()
{
    cout << "Hi!" << endl;

    payload_t payload_01; // demo payload for testing

    payload_01.id = 1; // Identification number
    payload_01.version = 1; // Payload version number
    payload_01.doorStatus = true; // Door status
    payload_01.catchDetect = false; // Catch detection
    payload_01.trapDisplacement = true; // Trap displacement
    payload_01.batteryStatus = 240; // Battery status
    payload_01.unixTime = 1234567890; // Date and time

    printPayload(payload_01);    

    // Test 1: known input 1
    payloadEncoder encoder; /// Encoder object
    payloadDecoder decoder; /// Decoder object

    int testVariable1 = 001; /// Test variable containing value that shall be transferred
    int testVariable2 = 003; /// Test variable containing value that shall be transferred

    encoder.setDemoVariable1(testVariable1); // Set variable in encoder object.
    encoder.setDemoVariable2(testVariable2); // Set variable in encoder object.
    encoder.composePayload();

    // debug
    encoder.printPayloadBinary();

    uint8_t *payloadBuffer = encoder.getPayload();
    uint8_t payloadSize = encoder.getPayloadSize();

    decoder.setPayload(payloadBuffer);
    decoder.setPayloadSize(payloadSize);
    decoder.decodePayload();

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