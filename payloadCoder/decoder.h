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
    uint32_t _id;           ///< Identification number (4 bytes)
    uint8_t _version;       ///< Payload version number (1 byte)
    bool _doorStatus;       ///< Door status (1 bit)
    bool _catchDetect;      ///< Catch detection (1 bit)
    bool _trapDisplacement; ///< Trap displacement (1 bit)
    uint8_t _batteryStatus; ///< Battery status (1 byte)
    uint32_t _unixTime;     ///< Date and time (4 bytes)

    uint8_t *_buffer;    ///< buffer containing payload with sensor data
    uint8_t _bufferSize; ///< Size of payload for housekeeping.

    /// \brief extract uint8 from payload
    /// \param buf pointer to buffer
    /// \param idx index in buffer
    /// \return uint8_t value
    uint8_t extract_uint8(const uint8_t *buf, const unsigned char idx = 0);

    /// \brief extract uint16 from payload
    /// \param buf pointer to buffer
    /// \param idx index in buffer
    /// \return uint16_t value
    uint16_t extract_uint16(const uint8_t *buf, const unsigned char idx = 0);

    /// \brief extract uint32 from payload
    /// \param buf pointer to buffer
    /// \param idx index in buffer
    /// \return uint32_t value
    uint32_t extract_uint32(const uint8_t *buf, const unsigned char idx = 0);

    /// \brief extract boolean from payload
    /// \param buf pointer to buffer
    /// \param idx index in buffer
    /// \param pos position in byte
    /// \return boolean value
    bool extract_bool(const uint8_t *buf, const unsigned char idx = 0, unsigned int pos = 0);

public:
    payloadDecoder();  ///< Constructor
    ~payloadDecoder(); ///< Destuctor

    /// \brief set payload
    /// Copy the payload to the buffer
    /// \param payload pointer to buffer
    void setPayload(uint8_t *payload) { _buffer = payload; }

    /// \brief set payload size
    /// Set the size of the payload
    /// \param size size of payload
    void setPayloadSize(uint8_t size) { _bufferSize = size; }

    /// \brief decode payload
    /// Extract the variables from the payload
    void decodePayload();

    /// \brief get ID
    /// Fetch the ID from the payload
    /// \return ID
    int get_id() const { return _id; }

    /// \brief get version
    /// Fetch the version number from the payload
    /// \return version
    int get_version() const { return _version; }

    /// \brief get door status
    /// Fetch the door status from the payload
    /// \return door status
    bool get_doorStatus() const { return _doorStatus; }

    /// \brief get catch detection
    /// Fetch the catch detection from the payload
    /// \return catch detection
    bool get_catchDetect() const { return _catchDetect; }

    /// \brief get trap displacement
    /// Fetch the trap displacement from the payload
    /// \return trap displacement
    bool get_trapDisplacement() const { return _trapDisplacement; }

    /// \brief get battery status
    /// Fetch the battery status from the payload
    /// \return battery status
    int get_batteryStatus() const { return _batteryStatus; }

    /// \brief get unix time
    /// Fetch the unix time from the payload
    /// \return unix time
    int get_unixTime() const { return _unixTime; }

    /// \brief print decoded payload
    /// Print the decoded payload to the console
    void printPayloadDecoded();
};

#endif // DECODER_H