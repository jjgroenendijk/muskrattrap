#include "decoder.h"

myPayloadDecoder::myPayloadDecoder() : _buffer{nullptr}
{
}

myPayloadDecoder::~myPayloadDecoder()
{
}

void myPayloadDecoder::decodePayload()
{
  _demoVariable1 = static_cast<int>(extract_uint32(_buffer, 0));
  _demoVariable2 = static_cast<int>(extract_uint16(_buffer, 4));
}

// UINT8
uint8_t myPayloadDecoder::extract_uint8(const uint8_t *buf, const unsigned char idx)
{
  return (uint8_t)buf[idx];
}

// UINT16
uint16_t myPayloadDecoder::extract_uint16(const uint8_t *buf, const unsigned char idx)
{
  uint16_t value{0};
  value = ((uint16_t)buf[idx] << 8); // msb
  value |= (uint16_t)buf[idx + 1];   // lsb
  return value;
}

// UINT32
uint32_t myPayloadDecoder::extract_uint32(const uint8_t *buf, const unsigned char idx)
{
  uint32_t value{0};
  for (uint8_t i = 0; i < 4; i++)
  {
    value |= ((uint32_t)buf[idx + i] << (24 - (i * 8))); // msb
  }
  return value;
}
