#ifndef MY_PAYLOAD_DECODER_H
#define MY_PAYLOAD_DECODER_H

#include <stdint.h> // uint8_t, uint16_t, and uint32_t type

const uint8_t VALUE_1 = 0;
const uint8_t VALUE_2 = 4;

class payloadDecoder
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

  uint32_t _demoVariable1; ///< demo variable 1, 32 bits sized
  uint16_t _demoVariable2; ///< demo variable 2, 16 bits sized

  uint8_t extract_uint8(const uint8_t *buf, const unsigned char idx = 0);
  uint16_t extract_uint16(const uint8_t *buf, const unsigned char idx = 0);
  uint32_t extract_uint32(const uint8_t *buf, const unsigned char idx = 0);
  bool extract_bool(const uint8_t *buf, const unsigned char idx = 0, unsigned int pos = 0);

public:
  payloadDecoder();  ///< Constructor
  ~payloadDecoder(); ///< Destuctor

  void setPayload(uint8_t *payload) { _buffer = payload; }
  void setPayloadSize(uint8_t size) { _bufferSize = size; }
  void decodePayload();
  int getDemoVariable1() const { return _demoVariable1; }
  int getDemoVariable2() const { return _demoVariable2; }

  int get_id() const { return _id; }
  int get_version() const { return _version; }
  bool get_doorStatus(const uint8_t *buf);
  bool get_catchDetect(const uint8_t *buf);
  bool get_trapDisplacement(const uint8_t *buf);
  int get_batteryStatus() const { return _batteryStatus; }
  int get_unixTime() const { return _unixTime; }

  void printPayloadDecoded();
};

#endif // MY_PAYLOAD_DECODER_H