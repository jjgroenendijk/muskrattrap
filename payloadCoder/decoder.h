#ifndef DECODER_H
#define DECODER_H

#include <stdint.h> // uint8_t, uint16_t, and uint32_t type

/// \brief payload decode class
/// This class wil decode variables out of a payload for use in a LoRaWAN application.
/// The class is setup using both .h and .cpp files where the setters and getters are
/// placed in to the .h file.
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

  int get_id() const { return _id; }
  int get_version() const { return _version; }
  bool get_doorStatus() const { return _doorStatus; }
  bool get_catchDetect() const { return _catchDetect; }
  bool get_trapDisplacement() const { return _trapDisplacement; }
  int get_batteryStatus() const { return _batteryStatus; }
  int get_unixTime() const { return _unixTime; }

  void printPayloadDecoded();
};

#endif // DECODER_H