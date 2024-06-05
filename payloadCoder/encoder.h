#ifndef payloadEncoder_H
#define payloadEncoder_H

#include <stdint.h> // uint8_t, uint16_t, and uint32_t type

const uint8_t SENSOR_PAYLOAD_SIZE = 52; ///< Payload size for sensor

class payloadEncoder
{
private:
  uint32_t id;           // Identification number (4 bytes)
  uint8_t version;       // Payload version number (1 byte)
  bool doorStatus;       // Door status (1 bit)
  bool catchDetect;      // Catch detection (1 bit)
  bool trapDisplacement; // Trap displacement (1 bit)
  uint8_t batteryStatus; // Battery status (1 byte)
  uint32_t unixTime;     // Date and time (4 bytes)

  uint32_t _testVariable1;
  uint16_t _testVariable2;

  uint8_t *_buffer;    ///< buffer containing payload with sensor data
  uint8_t _bufferSize; ///< Size of payload for housekeeping.

  unsigned char add_uint8(unsigned char idx_in, const uint8_t value);
  unsigned char add_uint16(unsigned char idx_in, const uint16_t value);
  unsigned char add_uint32(unsigned char idx_in, uint32_t value);
  unsigned char add_StatusBools(unsigned char idx_in, bool doorStatus, bool catchDetect, bool trapDisplacement);

public:
  payloadEncoder();  ///< Constructor
  ~payloadEncoder(); ///< Destructor

  void setDemoVariable1(const int var)
  {
    _testVariable1 = static_cast<uint32_t>(var);
  };

  void setDemoVariable2(const int var)
  {
    _testVariable2 = static_cast<uint16_t>(var);
  };

  void printPayloadBinary();

  void composePayload();

  uint8_t getPayloadSize()
  {
    return _bufferSize;
  };

  uint8_t *getPayload()
  {
    return _buffer;
  };
};

#endif // payloadEncoder_H
