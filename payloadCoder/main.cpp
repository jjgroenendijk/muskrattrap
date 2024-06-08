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
#include "decoder.h"
#include "encoder.h"
#include "unitTest.h"

using namespace std;

int main()
{
    // Test 1
    test01();

    return 0;
}