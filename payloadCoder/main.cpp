#include <iostream>
#include "decoder.h"
#include "encoder.h"

using namespace std;

int main()
{
    cout << "Hi!" << endl;

    // Test 1: known input 1
    myPayloadEncoder encoder; /// Encoder object
    myPayloadDecoder decoder; /// Decoder object

    int testVariable1 = 100; /// Test variable containing value that shall be transferred
    int testVariable2 = 200; /// Test variable containing value that shall be transferred

    encoder.setDemoVariable1(testVariable1); // Set variable in encoder object.
    encoder.setDemoVariable2(testVariable2); // Set variable in encoder object.
    encoder.composePayload();

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