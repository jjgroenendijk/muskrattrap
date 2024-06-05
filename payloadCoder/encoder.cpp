#include "encoder.h"
#include <stdlib.h> // malloc()

myPayloadEncoder::myPayloadEncoder() : _testVariable1{0},
                                       _testVariable2{0},
                                       _buffer{NULL},
                                       _bufferSize{0}
{
    _buffer = reinterpret_cast<uint8_t *>(malloc(SENSOR_PAYLOAD_SIZE));
}

myPayloadEncoder::~myPayloadEncoder()
{
    free(_buffer);
}

void myPayloadEncoder::composePayload()
{
    _bufferSize = 0; // init
    _bufferSize = add_uint32(_bufferSize, _testVariable1);
    _bufferSize = add_uint16(_bufferSize, _testVariable2);
}

// UINT16
unsigned char myPayloadEncoder::add_uint16(unsigned char idx_in, const uint16_t value)
{
    _buffer[idx_in++] = (value >> 8) & 0xFF; // msb
    _buffer[idx_in++] = (value) & 0xFF;      // lsb
    return (idx_in);
}

// UINT32
unsigned char myPayloadEncoder::add_uint32(unsigned char idx_in, uint32_t value)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        _buffer[idx_in++] = (value >> 24) & 0xFF; // msb
        value = value << 8;                       // shift-left
    }
    return (idx_in);
}
