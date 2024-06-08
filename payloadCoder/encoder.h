#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h> // uint8_t, uint16_t, and uint32_t type

const uint8_t SENSOR_PAYLOAD_SIZE = 52; ///< Payload size for sensor

class payloadEncoder
{
private:
  uint32_t _id;           // Identification number (4 bytes)
  uint8_t _version;       // Payload version number (1 byte)
  bool _doorStatus;       // Door status (1 bit)
  bool _catchDetect;      // Catch detection (1 bit)
  bool _trapDisplacement; // Trap displacement (1 bit)
  uint8_t _batteryStatus; // Battery status (1 byte)
  uint32_t _unixTime;     // Date and time (4 bytes)

  uint8_t *_buffer;    ///< buffer containing payload with sensor data
  uint8_t _bufferSize; ///< Size of payload for housekeeping.

  unsigned char add_uint8(unsigned char idx_in, const uint8_t value);
  unsigned char add_uint16(unsigned char idx_in, const uint16_t value);
  unsigned char add_uint32(unsigned char idx_in, uint32_t value);
  unsigned char add_bool(unsigned char idx_in, bool value, unsigned int pos);

public:
  payloadEncoder();  ///< Constructor
  ~payloadEncoder(); ///< Destructor

  void printPayloadBinary();
  void composePayload();
  uint8_t getPayloadSize() { return _bufferSize; };
  uint8_t *getPayload() { return _buffer; };

  void set_id(const uint32_t id) { _id = static_cast<uint32_t>(id); }
  void set_version(const uint8_t version) { _version = static_cast<uint8_t>(version); }
  void set_doorStatus(const bool doorStatus) { _doorStatus = doorStatus; }
  void set_catchDetect(const bool catchDetect) { _catchDetect = catchDetect; }
  void set_trapDisplacement(const bool trapDisplacement) { _trapDisplacement = trapDisplacement; }
  void set_batteryStatus(const uint8_t batteryStatus) { _batteryStatus = static_cast<uint8_t>(batteryStatus); }
  void set_unixTime(const uint32_t unixTime) { _unixTime = static_cast<uint32_t>(unixTime); }

  void printPayloadEncoded();
};

#endif // ENCODER_H