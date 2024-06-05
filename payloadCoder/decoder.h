#ifndef MY_PAYLOAD_DECODER_H
#define MY_PAYLOAD_DECODER_H

#include <stdint.h> // uint8_t, uint16_t, and uint32_t type

const uint8_t VALUE_1 = 0;
const uint8_t VALUE_2 = 4;

class myPayloadDecoder
{
private:
  uint8_t *_buffer;    ///< buffer containing payload with sensor data
  uint8_t _bufferSize; ///< Size of payload for housekeeping.

  uint32_t _demoVariable1; ///< demo variable 1, 32 bits sized
  uint16_t _demoVariable2; ///< demo variable 2, 16 bits sized

  uint32_t extract_uint32(const uint8_t *buf, const unsigned char idx = 0);

  uint16_t extract_uint16(const uint8_t *buf, const unsigned char idx = 0);

  uint8_t extract_uint8(const uint8_t *buf, const unsigned char idx = 0);

public:
  myPayloadDecoder();  ///< Constructor
  ~myPayloadDecoder(); ///< Destuctor

  void setPayload(uint8_t *payload) { _buffer = payload; }

  void setPayloadSize(uint8_t size) { _bufferSize = size; }

  void decodePayload();

  int getDemoVariable1() const { return _demoVariable1; }

  int getDemoVariable2() const { return _demoVariable2; }
};

#endif // MY_PAYLOAD_DECODER_H