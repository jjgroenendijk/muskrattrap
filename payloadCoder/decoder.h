/**
 * @file decoder.h
 * @brief Class definition for payloadDecoder, used to parse LoRaWAN payloads.
 * This file declares the payloadDecoder class, which is responsible for
 * extracting structured data from a raw byte array received via LoRaWAN.
 * @author Project Contributors
 * @date 2024-03-15
 * @version 1.0
 */
#ifndef DECODER_H
#define DECODER_H

#include <stdint.h> // uint8_t, uint16_t, and uint32_t type

/**
 * @class payloadDecoder
 * @brief Decodes variables from a LoRaWAN payload.
 * This class takes a raw byte array (payload) and its size, typically received
 * from a LoRaWAN network, and provides methods to extract meaningful sensor
 * readings and status information. The internal structure of the payload (e.g.,
 * byte order, data types per field) is defined by the encoding process and
 * must be known for correct decoding.
 */
class payloadDecoder
{
private:
    uint32_t _id;           ///< \brief Decoded identification number (e.g., device ID), typically 4 bytes.
    uint8_t _version;       ///< \brief Decoded payload version number, typically 1 byte.
    bool _doorStatus;       ///< \brief Decoded door status (e.g., true for closed, false for open), typically 1 bit.
    bool _catchDetect;      ///< \brief Decoded catch detection status (e.g., true if a catch is detected), typically 1 bit.
    bool _trapDisplacement; ///< \brief Decoded trap displacement status (e.g., true if trap moved), typically 1 bit.
    uint8_t _batteryStatus; ///< \brief Decoded battery status (e.g., percentage or voltage), typically 1 byte.
    uint32_t _unixTime;     ///< \brief Decoded Unix timestamp (seconds since epoch), typically 4 bytes.
    uint8_t *_buffer;       ///< \brief Pointer to the buffer containing the raw payload data.
    uint8_t _bufferSize;    ///< \brief Size of the payload buffer in bytes.

    /**
     * @brief Extracts a uint8_t value from the buffer at the specified index.
     * @param buf Pointer to the buffer containing the payload.
     * @param idx The index in the buffer from which to extract the value. Defaults to 0.
     * @return The extracted uint8_t value.
     */
    uint8_t extract_uint8(const uint8_t *buf, const unsigned char idx = 0);

    /**
     * @brief Extracts a uint16_t value from the buffer at the specified index.
     * Assumes little-endian byte order for the 16-bit value within the buffer.
     * @param buf Pointer to the buffer containing the payload.
     * @param idx The starting index in the buffer from which to extract the value. Defaults to 0.
     * @return The extracted uint16_t value.
     */
    uint16_t extract_uint16(const uint8_t *buf, const unsigned char idx = 0);

    /**
     * @brief Extracts a uint32_t value from the buffer at the specified index.
     * Assumes little-endian byte order for the 32-bit value within the buffer.
     * @param buf Pointer to the buffer containing the payload.
     * @param idx The starting index in the buffer from which to extract the value. Defaults to 0.
     * @return The extracted uint32_t value.
     */
    uint32_t extract_uint32(const uint8_t *buf, const unsigned char idx = 0);

    /**
     * @brief Extracts a boolean value from a specific bit within a byte in the buffer.
     * @param buf Pointer to the buffer containing the payload.
     * @param idx The index in the buffer where the byte containing the bit is located. Defaults to 0.
     * @param pos The bit position (0-7, where 0 is the LSB) within the byte at `idx`. Defaults to 0.
     * @return The extracted boolean value (true if the bit is 1, false if 0).
     */
    bool extract_bool(const uint8_t *buf, const unsigned char idx = 0, unsigned int pos = 0);

public:
    /**
     * @brief Default constructor for payloadDecoder.
     */
    payloadDecoder();

    /**
     * @brief Destructor for payloadDecoder.
     */
    ~payloadDecoder();

    payloadDecoder(const payloadDecoder &) = delete;            ///< \brief Copy constructor disabled to prevent unintended shallow copies.
    payloadDecoder &operator=(const payloadDecoder &) = delete; ///< \brief Assignment operator disabled to prevent unintended shallow copies.

    /**
     * @brief Sets the internal buffer to point to the provided payload data.
     * The payloadDecoder does not take ownership of this buffer nor does it copy the data.
     * The caller must ensure the payload buffer remains valid for the lifetime of decoding operations.
     * @param payload Pointer to the byte array containing the payload to be decoded.
     */
    void setPayload(uint8_t *payload) { _buffer = payload; }

    /**
     * @brief Sets the size of the payload buffer.
     * This must be called before `decodePayload()` to ensure correct parsing.
     * @param size The size of the payload in bytes.
     */
    void setPayloadSize(uint8_t size) { _bufferSize = size; }

    /**
     * @brief Decodes the payload from the buffer set by `setPayload` and `setPayloadSize`.
     * This method parses the raw byte buffer and populates the internal member
     * variables (e.g., `_id`, `_version`, `_doorStatus`) with the extracted values.
     * The specific byte order and field mapping are implemented within this function's definition.
     */
    void decodePayload();

    /**
     * @brief Gets the decoded identification number.
     * @return The identification number (uint32_t).
     */
    uint32_t get_id() const { return _id; }

    /**
     * @brief Gets the decoded payload version number.
     * @return The payload version (uint8_t).
     */
    uint8_t get_version() const { return _version; }

    /**
     * @brief Gets the decoded door status.
     * @return bool True if the door is closed (example convention), false if open. Check implementation for exact meaning.
     */
    bool get_doorStatus() const { return _doorStatus; }

    /**
     * @brief Gets the decoded catch detection status.
     * @return bool True if a catch is detected, false otherwise.
     */
    bool get_catchDetect() const { return _catchDetect; }

    /**
     * @brief Gets the decoded trap displacement status.
     * @return bool True if the trap has been moved, false otherwise.
     */
    bool get_trapDisplacement() const { return _trapDisplacement; }

    /**
     * @brief Gets the decoded battery status.
     * @return The battery status (uint8_t), e.g., a percentage.
     */
    uint8_t get_batteryStatus() const { return _batteryStatus; }

    /**
     * @brief Gets the decoded Unix time.
     * @return The Unix timestamp (uint32_t) representing seconds since the epoch.
     */
    uint32_t get_unixTime() const { return _unixTime; }

    /**
     * @brief Prints the decoded payload fields and their values to the standard output.
     * Useful for debugging and verifying the decoding process.
     */
    void printPayloadDecoded();
};

#endif // DECODER_H
