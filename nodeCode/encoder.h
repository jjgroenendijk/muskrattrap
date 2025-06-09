/*!
 * @file encoder.h
 * @brief Payload encoder for muskrat trap LoRaWAN node. Encodes sensor and status data into a compact binary format.
 *
 * Fields encoded: id, version, door status, catch detect, trap displacement, battery status, unix time.
 * Usage: Set fields via setters, then call composePayload() to generate the payload buffer.
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
    uint8_t *_buffer;       ///< buffer containing payload with sensor data
    uint8_t _bufferSize;    ///< Size of payload for housekeeping.

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
    payloadEncoder();                                           ///< Constructor
    ~payloadEncoder();                                          ///< Destructor
    payloadEncoder(const payloadEncoder &) = delete;            ///< Copy constructor disabled
    payloadEncoder &operator=(const payloadEncoder &) = delete; ///< Assignment operator disabled

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

    /**
     * @brief Set the device ID for the payload.
     * @param id Device identifier (uint32_t)
     */
    void set_id(uint32_t id);

    /**
     * @brief Set the payload version.
     * @param version Version number (uint8_t)
     */
    void set_version(uint8_t version);

    /**
     * @brief Set the door status.
     * @param doorStatus True if closed, false if open
     */
    void set_doorStatus(bool doorStatus);

    /**
     * @brief Set the catch detect flag.
     * @param catchDetect True if catch detected
     */
    void set_catchDetect(bool catchDetect);

    /**
     * @brief Set the trap displacement flag.
     * @param trapDisplacement True if trap displaced
     */
    void set_trapDisplacement(bool trapDisplacement);

    /**
     * @brief Set the battery status (0-255).
     * @param batteryStatus Battery level (uint8_t)
     */
    void set_batteryStatus(uint8_t batteryStatus);

    /**
     * @brief Set the unix time for the payload.
     * @param unixTime Unix timestamp (uint32_t)
     */
    void set_unixTime(uint32_t unixTime);

    /// @brief print the encoded payload
    /// This function prints the encoded payload in a human-readable format to the console.
    void printPayloadEncoded();

    /// @brief set test values
    /// This function sets test values for the payload encoder.
    /// The test values are used to verify the correct encoding of the payload.
    void setTestValues();
};

#endif // ENCODER_H