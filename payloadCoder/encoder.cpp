#include "encoder.h"
#include <iostream> // only used for debug output
#include <stdlib.h> // malloc()

payloadEncoder::payloadEncoder() : id{0},
                                   version{0},
                                   doorStatus{1},
                                   catchDetect{1},
                                   trapDisplacement{1},
                                   batteryStatus{0},
                                   unixTime{0},

                                   _testVariable1{0},
                                   _testVariable2{0},

                                   _buffer{NULL},
                                   _bufferSize{0}
{
    _buffer = reinterpret_cast<uint8_t *>(malloc(SENSOR_PAYLOAD_SIZE));
}

payloadEncoder::~payloadEncoder()
{
    free(_buffer);
}

void payloadEncoder::composePayload()
{
    _bufferSize = 0; // init
    _bufferSize = add_uint32(_bufferSize, _testVariable1);
    _bufferSize = add_uint16(_bufferSize, _testVariable2);

    _bufferSize = add_uint32(_bufferSize, id);
    _bufferSize = add_uint8(_bufferSize, version);

    _bufferSize = add_StatusBools(_bufferSize, doorStatus, catchDetect, trapDisplacement);

    _bufferSize = add_uint8(_bufferSize, batteryStatus);
    _bufferSize = add_uint32(_bufferSize, unixTime);

    // debug
    // show payload size
    std::cout << "Payload size in bytes: " << static_cast<int>(_bufferSize) << std::endl;
}

// UINT8
unsigned char payloadEncoder::add_uint8(unsigned char idx_in, const uint8_t value)
{
    _buffer[idx_in++] = value;
    return (idx_in);
}

// UINT16
unsigned char payloadEncoder::add_uint16(unsigned char idx_in, const uint16_t value)
{
    _buffer[idx_in++] = (value >> 8) & 0xFF; // msb
    _buffer[idx_in++] = (value) & 0xFF;      // lsb
    return (idx_in);
}

// UINT32
unsigned char payloadEncoder::add_uint32(unsigned char idx_in, uint32_t value)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        _buffer[idx_in++] = (value >> 24) & 0xFF; // msb
        value = value << 8;                       // shift-left
    }
    return (idx_in);
}

unsigned char payloadEncoder::add_StatusBools(unsigned char idx_in, bool doorStatus, bool catchDetect, bool trapDisplacement)
{
    uint8_t compressedStatusByte = 0;

    compressedStatusByte |= (doorStatus << 2);
    compressedStatusByte |= (catchDetect << 1);
    compressedStatusByte |= trapDisplacement;

    _buffer[idx_in++] = compressedStatusByte;
    return (idx_in);
}

void payloadEncoder::printPayloadBinary()
{
    std::cout << "Current payload in binary: ";
    for (unsigned int i = 0; i < _bufferSize; ++i)
    {
        std::bitset<8> binary(_buffer[i]);
        std::cout << binary << " ";
    }
    std::cout << std::endl;
}