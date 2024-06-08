#include "decoder.h"
#include <iostream> // cout, endl // debugging only

payloadDecoder::payloadDecoder() : _buffer{nullptr}
{
}

payloadDecoder::~payloadDecoder()
{
}

void payloadDecoder::decodePayload()
{
  // print paylaod in binary format
  std::cout << "Payload in binary format: ";
  for (int i = 0; i < _bufferSize; i++)
  {
    for (int j = 7; j >= 0; j--)
    {
      std::cout << ((_buffer[i] >> j) & 1);
    }
    std::cout << " ";
  }

  std::cout << std::endl;

  _id = static_cast<int>(extract_uint32(_buffer, 0));
  _version = static_cast<int>(extract_uint8(_buffer, 4));
  _doorStatus = extract_bool(_buffer, 5, 2);
  _catchDetect = extract_bool(_buffer, 5, 1);
  _trapDisplacement = extract_bool(_buffer, 5, 0);
  _batteryStatus = static_cast<int>(extract_uint8(_buffer, 6));
  _unixTime = static_cast<int>(extract_uint32(_buffer, 7));
}

// UINT8
uint8_t payloadDecoder::extract_uint8(const uint8_t *buf, const unsigned char idx)
{
  return static_cast<uint8_t>(buf[idx]);
}

// UINT16
uint16_t payloadDecoder::extract_uint16(const uint8_t *buf, const unsigned char idx)
{
  uint16_t value{0};
  value = static_cast<uint16_t>(buf[idx] << 8); // msb
  value |= static_cast<uint16_t>(buf[idx + 1]);   // lsb
  return value;
}

// UINT32
uint32_t payloadDecoder::extract_uint32(const uint8_t *buf, const unsigned char idx)
{
  uint32_t value{0};
  for (uint8_t i = 0; i < 4; i++)
  {
    value |= static_cast<uint32_t>(buf[idx + i] << (24 - (i * 8))); // msb
  }
  return value;
}

// extract boolean
bool payloadDecoder::extract_bool(const uint8_t *buf, const unsigned char idx, unsigned int pos)
{
  bool value;
  value = (buf[idx] >> pos) & 1;
  return value;
}

// print payload decoded
void payloadDecoder::printPayloadDecoded()
{
  std::cout << "Payload decoded: " << std::endl;
  std::cout << "ID: " << _id << std::endl;
  std::cout << "Version: " << static_cast<int>(_version) << std::endl;
  std::cout << "Door status: " << _doorStatus << std::endl;
  std::cout << "Catch detect: " << _catchDetect << std::endl;
  std::cout << "Trap displacement: " << _trapDisplacement << std::endl;
  std::cout << "Battery status: " << static_cast<int>(_batteryStatus) << std::endl;
  std::cout << "Unix time: " << _unixTime << std::endl;
}