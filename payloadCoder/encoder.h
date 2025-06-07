/**
 * @file encoder.h
 * @brief Encoder class for payloadCoder project.
 * This file declares the payloadEncoder class, responsible for converting
 * various sensor readings and status information into a compact byte array
 * suitable for LoRaWAN transmission.
 * @author Jaap-Jan Groenendijk (github@jjgroenendijk.nl)
 * @date 2024-03-15
 * @version 1.1
 *
 * @version log
 * Version   Date        Note
 * 1.1       2024-03-15  Standardized Doxygen comments to use `\` commands and `/** ... */` blocks. (Project Contributors)
 * 1.0       2024-09-06  Initial version. (Jaap-Jan Groenendijk)
 */
#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h> ///< \brief For uint8_t, uint16_t, and uint32_t types.

/**
 * @brief Defines the standard size of the sensor payload in bytes.
 * This constant is used to initialize the buffer for the encoded payload.
 */
const uint8_t SENSOR_PAYLOAD_SIZE = 11; ///< \brief Payload size in bytes for sensor data.

/**
 * @class payloadEncoder
 * @brief Encodes sensor data and status information into a LoRaWAN payload.
 *
 * This class takes various inputs such as sensor readings (door status, catch detection,
 * trap displacement, battery status), identification information (ID, version), and
 * a timestamp (Unix time), and encodes them into an internal byte array (`_buffer`).
 * The encoded payload is structured to be compact for efficient transmission over LoRaWAN.
 * Methods are provided to set each data field, compose the final payload, retrieve it,
 * and print it for debugging purposes.
 */
class payloadEncoder
{
private:
    uint32_t _id;           ///< \brief Identification number (e.g., device ID), 4 bytes.
    uint8_t _version;       ///< \brief Payload format version number, 1 byte.
    bool _doorStatus;       ///< \brief Door status (e.g., true for closed, false for open), 1 bit.
    bool _catchDetect;      ///< \brief Catch detection status (e.g., true if catch detected), 1 bit.
    bool _trapDisplacement; ///< \brief Trap displacement status (e.g., true if trap moved), 1 bit.
    uint8_t _batteryStatus; ///< \brief Battery status (e.g., percentage or coded value), 1 byte.
    uint32_t _unixTime;     ///< \brief Unix timestamp (seconds since epoch), 4 bytes.
    uint8_t *_buffer;       ///< \brief Pointer to the buffer holding the encoded payload data.
    uint8_t _bufferSize;    ///< \brief Current size of the encoded payload in bytes.

    /**
     * @brief Adds a uint8_t value to the internal buffer at the specified index.
     * @param idx_in The index in the buffer where the value should be added.
     * @param value The uint8_t value to be added.
     * @return The next available index in the buffer after adding the value.
     */
    unsigned char add_uint8(unsigned char idx_in, const uint8_t value);

    /**
     * @brief Adds a uint16_t value to the internal buffer at the specified index.
     * Encodes the value in little-endian byte order.
     * @param idx_in The starting index in the buffer where the value should be added.
     * @param value The uint16_t value to be added.
     * @return The next available index in the buffer after adding the value.
     */
    unsigned char add_uint16(unsigned char idx_in, const uint16_t value);

    /**
     * @brief Adds a uint32_t value to the internal buffer at the specified index.
     * Encodes the value in little-endian byte order.
     * @param idx_in The starting index in the buffer where the value should be added.
     * @param value The uint32_t value to be added.
     * @return The next available index in the buffer after adding the value.
     */
    unsigned char add_uint32(unsigned char idx_in, uint32_t value);

    /**
     * @brief Adds a boolean value to a specific bit within a byte in the internal buffer.
     * @param idx_in The index in the buffer of the byte to modify.
     * @param value The boolean value to be added (true sets the bit, false clears it).
     * @param pos The bit position (0-7, where 0 is LSB) within the byte at `idx_in`.
     * @return The index of the byte that was modified. If a new byte was started (not typical for this function's logic), it would return idx_in + 1, otherwise idx_in.
     */
    unsigned char add_bool(unsigned char idx_in, bool value, unsigned int pos);

public:
    /**
     * @brief Default constructor for payloadEncoder.
     * Initializes the payload buffer and sets default values for its members.
     */
    payloadEncoder();

    /**
     * @brief Destructor for payloadEncoder.
     * Frees the dynamically allocated memory for the payload buffer.
     */
    ~payloadEncoder();

    payloadEncoder(const payloadEncoder &) = delete;            ///< \brief Copy constructor disabled to prevent unintended shallow copies and double frees.
    payloadEncoder &operator=(const payloadEncoder &) = delete; ///< \brief Assignment operator disabled for similar reasons.

    /**
     * @brief Prints the current content of the payload buffer in binary format to standard output.
     * Useful for debugging the exact bitwise representation of the payload.
     */
    void printPayloadBinary();

    /**
     * @brief Composes the final payload by encoding all set member variables into the internal buffer.
     * This function orchestrates calls to the private `add_uint*` and `add_bool` methods
     * to fill the `_buffer` according to the defined payload structure.
     */
    void composePayload();

    /**
     * @brief Gets the size of the composed payload.
     * @return The size of the payload in bytes (`_bufferSize`).
     */
    uint8_t getPayloadSize() { return _bufferSize; };

    /**
     * @brief Gets a pointer to the composed payload buffer.
     * @return A pointer to the `_buffer` containing the encoded payload data.
     *         The caller should not free this buffer; it is managed by the payloadEncoder instance.
     */
    uint8_t *getPayload() { return _buffer; };

    /**
     * @brief Sets the identification number for the payload.
     * @param id The identification number (e.g., device EUI or a custom ID).
     */
    void set_id(const uint32_t id) { _id = static_cast<uint32_t>(id); }

    /**
     * @brief Sets the payload version number.
     * @param version The version number of the payload format.
     */
    void set_version(const uint8_t version) { _version = static_cast<uint8_t>(version); }

    /**
     * @brief Sets the door status.
     * @param doorStatus Boolean value representing the door status (e.g., true for closed, false for open).
     */
    void set_doorStatus(const bool doorStatus) { _doorStatus = doorStatus; }

    /**
     * @brief Sets the catch detection status.
     * @param catchDetect Boolean value indicating if a catch has been detected.
     */
    void set_catchDetect(const bool catchDetect) { _catchDetect = catchDetect; }

    /**
     * @brief Sets the trap displacement status.
     * @param trapDisplacement Boolean value indicating if the trap has been moved.
     */
    void set_trapDisplacement(const bool trapDisplacement) { _trapDisplacement = trapDisplacement; }

    /**
     * @brief Sets the battery status.
     * @param batteryStatus The battery level (e.g., a percentage from 0 to 100, or a coded value).
     */
    void set_batteryStatus(const uint8_t batteryStatus) { _batteryStatus = static_cast<uint8_t>(batteryStatus); }

    /**
     * @brief Sets the date and time as a Unix timestamp.
     * @param unixTime The Unix timestamp (number of seconds since January 1, 1970, UTC).
     */
    void set_unixTime(const uint32_t unixTime) { _unixTime = static_cast<uint32_t>(unixTime); }

    /**
     * @brief Prints the values of the fields intended for encoding to standard output.
     * This helps verify the data before or after it's composed into the payload.
     */
    void printPayloadEncoded();
};

#endif // ENCODER_H