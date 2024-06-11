/*!
* @file encoder.h
* @brief Encoder class for payloadCoder project
* @author Jaap-Jan Groenendijk (github@jjgroenendijk.nl)
* @date 2024-09-06
* @version 1.0

*/

#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h> /// uint8_t, uint16_t, and uint32_t type

const uint8_t SENSOR_PAYLOAD_SIZE = 11; ///< Payload size for sensor

/**
 * @class payloadEncoder
 * @brief payload endoder class
 *
 * This class wil encode variables for the LoRaWAN application in to a single payload
 * The class is setup using both .h and .cpp files where the setters and getters are
 * placed in to the .cpp file.
 * The `payloadEncoder` class is responsible for encoding payload data that includes various sensor readings and status information.
 * It provides methods to set individual data fields and compose the payload.
 * The encoded payload can be retrieved using the `getPayload()` method.
 * The size of the payload can be obtained using the `getPayloadSize()` method.
 * The encoded payload can be printed in binary format using the `printPayloadBinary()` method.
 * The encoded payload can be printed in a human-readable format using the `printPayloadEncoded()` method.
 */
class payloadEncoder
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

    /// @brief add uint8_t value to the buffer at the specified index.
    /// @param idx_in The index in the buffer where the value should be added.
    /// @param value The uint8_t value to be added to the buffer.
    /// @return First free location at which new dat acan be stored in _buffer
    unsigned char add_uint8(unsigned char idx_in, const uint8_t value);

    /// @brief  add uint16 to payload
    /// @param idx_in start location in _buffer
    /// @param value uint16_t value
    /// @return First free location at which new dat acan be stored in _buffer
    unsigned char add_uint16(unsigned char idx_in, const uint16_t value);

    /// @brief add uint32 to payload
    /// @param idx_in start location in _buffer
    /// @param value uint32_t value
    /// @return First free location at which new dat acan be stored in _buffer
    unsigned char add_uint32(unsigned char idx_in, uint32_t value);

    /// @brief add boolean value to the buffer at the specified index.
    /// @param idx_in The index in the buffer where the value should be added.
    /// @param value The boolean value to be added to the buffer.
    /// @param pos The position in the byte where the boolean value should be added.
    /// @return First free location at which new dat acan be stored in _buffer
    unsigned char add_bool(unsigned char idx_in, bool value, unsigned int pos);

public:
    payloadEncoder();  ///< Constructor
    ~payloadEncoder(); ///< Destructor

    /// Need to find out out what this does exactly. It removes compiling warnings.
    /// @brief  copy constructor
    /// @param payloadEncoder object
    payloadEncoder(const payloadEncoder &) = delete;
    payloadEncoder &operator=(const payloadEncoder &) = delete;

    /// @brief print the payload in binary format
    /// This function prints the payload in binary format to the console.
    void printPayloadBinary();

    /// @brief compose payload
    /// This function composes the payload by adding all the sensor data and status information to the buffer.
    void composePayload();

    /// @brief get payload size
    /// This function returns the size of the payload in bytes.
    /// @return The size of the payload in bytes.
    uint8_t getPayloadSize() { return _bufferSize; };

    /// @brief get payload
    /// This function returns a pointer to the buffer containing the encoded payload.
    /// @return A pointer to the buffer containing the encoded payload.
    uint8_t *getPayload() { return _buffer; };

    /// @brief set the identification number
    /// This function sets the identification number in the payload.
    /// @param id The identification number to be set in the payload.
    void set_id(const uint32_t id) { _id = static_cast<uint32_t>(id); }

    /// @brief set the payload version number
    /// This function sets the payload version number in the payload.
    /// @param version The payload version number to be set in the payload.
    void set_version(const uint8_t version) { _version = static_cast<uint8_t>(version); }

    /// @brief set the door status
    /// This function sets the door status in the payload.
    /// @param doorStatus The door status to be set in the payload.
    void set_doorStatus(const bool doorStatus) { _doorStatus = doorStatus; }

    /// @brief set the catch detection status
    /// This function sets the catch detection status in the payload.
    /// @param catchDetect The catch detection status to be set in the payload.
    void set_catchDetect(const bool catchDetect) { _catchDetect = catchDetect; }

    /// @brief set the trap displacement status
    /// This function sets the trap displacement status in the payload.
    /// @param trapDisplacement The trap displacement status to be set in the payload.
    void set_trapDisplacement(const bool trapDisplacement) { _trapDisplacement = trapDisplacement; }

    /// @brief set the battery status
    /// This function sets the battery status in the payload.
    /// @param batteryStatus The battery status to be set in the payload.
    void set_batteryStatus(const uint8_t batteryStatus) { _batteryStatus = static_cast<uint8_t>(batteryStatus); }

    /// @brief set the date and time
    /// This function sets the date and time in the payload.
    /// @param unixTime The date and time to be set in the payload.
    void set_unixTime(const uint32_t unixTime) { _unixTime = static_cast<uint32_t>(unixTime); }

    /// @brief print the encoded payload
    /// This function prints the encoded payload in a human-readable format to the console.
    void printPayloadEncoded();
};

#endif // ENCODER_H