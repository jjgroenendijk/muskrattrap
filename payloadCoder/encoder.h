#ifndef MYPAYLOADENCODER_H
#define MYPAYLOADENCODER_H

#include <stdint.h> // uint8_t, uint16_t, and uint32_t type

const uint8_t SENSOR_PAYLOAD_SIZE = 52; ///< Payload size for sensor

class myPayloadEncoder
{
private:
  uint32_t _testVariable1; ///
  uint16_t _testVariable2;

  uint8_t *_buffer;    ///< buffer containing payload with sensor data
  uint8_t _bufferSize; ///< Size of payload for housekeeping.

  unsigned char add_uint32(unsigned char idx_in, uint32_t value);

  unsigned char add_uint16(unsigned char idx_in, const uint16_t value);

public:
  myPayloadEncoder();  ///< Constructor
  ~myPayloadEncoder(); ///< Destructor

  void setDemoVariable1(const int var) { _testVariable1 = static_cast<uint32_t>(var); };

  void setDemoVariable2(const int var) { _testVariable2 = static_cast<uint16_t>(var); };

  void composePayload();

  uint8_t getPayloadSize() { return _bufferSize; };

  uint8_t *getPayload() { return _buffer; };
};

#endif // MYPAYLOADENCODER_H
