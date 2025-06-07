/*!
* @file encoder.h
* @brief Encoder class for payloadCoder project
* @author Jaap-Jan Groenendijk (github@jjgroenendijk.nl)
* @date 2024-03-15
* @version 1.1
*
* @version log
* Version   Date        Note
* 1.1       2024-03-15  Reviewed and confirmed Doxygen documentation completeness. (Project Contributors)
* 1.0       2024-09-06  Initial version. (Jaap-Jan Groenendijk)
*
* @mainpage Payload Encoder
*
* @section intro_sec Introduction
* This document describes the `payloadEncoder` class, which is responsible for
* encoding various sensor readings and status information into a compact payload
* suitable for LoRaWAN transmission.
*
* @section features_sec Features
* - Encodes ID, version, door status, catch detection, trap displacement,
*   battery status, and Unix time.
* - Provides methods to set individual data fields.
* - Composes the final payload.
* - Allows retrieval of the payload and its size.
* - Supports printing the payload in binary and human-readable formats.
*
* @section usage_sec Usage
* 1. Create an instance of `payloadEncoder`.
* 2. Set the desired data fields using the `set_*` methods.
* 3. Call `composePayload()` to generate the encoded payload.
* 4. Retrieve the payload using `getPayload()` and its size using `getPayloadSize()`.
*/

#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h> /// uint8_t, uint16_t, and uint32_t type

/**
 * @brief Defines the size of the sensor payload in bytes.
 */
const uint8_t SENSOR_PAYLOAD_SIZE = 11; ///< Payload size for sensor

/**
 * @class payloadEncoder
 * @brief Encodes sensor data and status information into a LoRaWAN payload.
 *
 * This class takes various inputs such as sensor readings (door status, catch detection,
 * trap displacement, battery status), identification information (ID, version), and
 * a timestamp (Unix time), and encodes them into a byte array (_buffer).
 * The encoded payload is structured to be compact for efficient transmission over LoRaWAN.
 */
class payloadEncoder
{
private:
    uint32_t _id;           ///< @brief Identification number (4 bytes). Unique identifier for the device or trap.
    uint8_t _version;       ///< @brief Payload version number (1 byte). Indicates the format/version of the payload.
    bool _doorStatus;       ///< @brief Door status (1 bit). True if the door is closed, false if open.
    bool _catchDetect;      ///< @brief Catch detection (1 bit). True if a catch is detected, false otherwise.
    bool _trapDisplacement; ///< @brief Trap displacement (1 bit). True if the trap has been moved, false otherwise.
    uint8_t _batteryStatus; ///< @brief Battery status (1 byte). Represents the battery level, e.g., percentage.
    uint32_t _unixTime;     ///< @brief Date and time (4 bytes). Timestamp of the reading, in Unix time format.
    uint8_t *_buffer;       ///< @brief Buffer containing the encoded payload with sensor data.
    uint8_t _bufferSize;    ///< @brief Size of the payload buffer in bytes.

    /**
     * @brief Adds a uint8_t value to the buffer at the specified index.
     * @param idx_in The index in the buffer where the value should be added.
     * @param value The uint8_t value to be added to the buffer.
     * @return The next free location (index) in the _buffer after adding the value.
     */
    unsigned char add_uint8(unsigned char idx_in, const uint8_t value);

    /**
     * @brief Adds a uint16_t value to the buffer at the specified index.
     * @param idx_in The starting index in the _buffer where the value should be added.
     * @param value The uint16_t value to be added.
     * @return The next free location (index) in the _buffer after adding the value.
     */
    unsigned char add_uint16(unsigned char idx_in, const uint16_t value);

    /**
     * @brief Adds a uint32_t value to the buffer at the specified index.
     * @param idx_in The starting index in the _buffer where the value should be added.
     * @param value The uint32_t value to be added.
     * @return The next free location (index) in the _buffer after adding the value.
     */
    unsigned char add_uint32(unsigned char idx_in, uint32_t value);

    /**
     * @brief Adds a boolean value to the buffer at the specified index and bit position.
     * @param idx_in The index in the buffer where the byte containing the bit is located.
     * @param value The boolean value to be added (true for 1, false for 0).
     * @param pos The bit position (0-7) within the byte at idx_in where the boolean should be stored.
     * @return The index in the _buffer. If a new byte was started for this boolean, it returns idx_in + 1, otherwise idx_in.
     */
    unsigned char add_bool(unsigned char idx_in, bool value, unsigned int pos);

public:
    /**
     * @brief Default constructor for payloadEncoder.
     * Initializes the payload buffer and default values.
     */
    payloadEncoder();

    /**
     * @brief Destructor for payloadEncoder.
     * Frees the allocated memory for the payload buffer.
     */
    ~payloadEncoder();
    
    payloadEncoder(const payloadEncoder &) = delete;            ///< Copy constructor disabled to prevent shallow copies.
    payloadEncoder &operator=(const payloadEncoder &) = delete; ///< Assignment operator disabled to prevent shallow copies.

    /**
     * @brief Prints the payload in binary format to the console.
     * Useful for debugging the exact bitwise representation of the payload.
     */
    void printPayloadBinary();

    /**
     * @brief Composes the payload by encoding all set member variables into the buffer.
     * This function orchestrates the calls to `add_uint32`, `add_uint8`, `add_bool`, etc.,
     * to fill the `_buffer` with the data in the correct order and format.
     */
    void composePayload();

    /**
     * @brief Gets the size of the composed payload.
     * @return The size of the payload in bytes.
     */
    uint8_t getPayloadSize() { return _bufferSize; };

    /**
     * @brief Gets a pointer to the composed payload buffer.
     * @return A pointer to the `_buffer` containing the encoded payload.
     */
    uint8_t *getPayload() { return _buffer; };

    /**
     * @brief Sets the identification number for the payload.
     * @param id The identification number (e.g., device EUI or custom ID).
     */
    void set_id(const uint32_t id) { _id = static_cast<uint32_t>(id); }

    /**
     * @brief Sets the payload version number.
     * @param version The version number of the payload format.
     */
    void set_version(const uint8_t version) { _version = static_cast<uint8_t>(version); }

    /**
     * @brief Sets the door status.
     * @param doorStatus True if the door is closed, false if open.
     */
    void set_doorStatus(const bool doorStatus) { _doorStatus = doorStatus; }

    /**
     * @brief Sets the catch detection status.
     * @param catchDetect True if a catch is detected, false otherwise.
     */
    void set_catchDetect(const bool catchDetect) { _catchDetect = catchDetect; }

    /**
     * @brief Sets the trap displacement status.
     * @param trapDisplacement True if the trap has been moved, false otherwise.
     */
    void set_trapDisplacement(const bool trapDisplacement) { _trapDisplacement = trapDisplacement; }

    /**
     * @brief Sets the battery status.
     * @param batteryStatus The battery level (e.g., percentage from 0 to 255).
     */
    void set_batteryStatus(const uint8_t batteryStatus) { _batteryStatus = static_cast<uint8_t>(batteryStatus); }

    /**
     * @brief Sets the date and time as a Unix timestamp.
     * @param unixTime The Unix timestamp (seconds since epoch).
     */
    void set_unixTime(const uint32_t unixTime) { _unixTime = static_cast<uint32_t>(unixTime); }

    /**
     * @brief Prints the encoded payload in a human-readable format to the console.
     * Displays each field and its value as encoded in the payload.
     */
    void printPayloadEncoded();
};

#endif // ENCODER_H
