/**
 * @file decoder.h
 * @brief Defines the payloadDecoder class for LoRaWAN payload processing.
 * This file contains the declaration of the payloadDecoder class, which is
 * designed to parse byte arrays received from LoRaWAN devices, extracting
 * sensor data and status information.
 * @author Project Contributors
 * @date 2024-03-15
 * @version 1.1
 */
#ifndef DECODER_H
#define DECODER_H

#include <stdint.h> // uint8_t, uint16_t, and uint32_t type

/**
 * @mainpage Payload Decoder
 *
 * @section intro_sec Introduction
 * This document describes the `payloadDecoder` class, which is responsible for
 * decoding a compact LoRaWAN payload into its constituent sensor readings and
 * status information.
 *
 * @section features_sec Features
 * - Decodes ID, version, door status, catch detection, trap displacement,
 *   battery status, and Unix time from a byte buffer.
 * - Provides methods to set the payload buffer and its size.
 * - Offers getter methods to retrieve individual decoded data fields.
 * - Supports printing the decoded payload in a human-readable format.
 *
 * @section usage_sec Usage
 * 1. Create an instance of `payloadDecoder`.
 * 2. Provide the payload buffer and its size using `setPayload()` and `setPayloadSize()`.
 * 3. Call `decodePayload()` to parse the buffer.
 * 4. Retrieve the decoded data fields using the `get_*()` methods.
 */

/**
 * @class payloadDecoder
 * @brief Decodes a LoRaWAN payload into sensor data and status information.
 *
 * This class takes a byte array (payload) received over LoRaWAN and parses it
 * to extract meaningful data such as sensor states (door status, catch detection,
 * trap displacement, battery status), identification information (ID, version),
 * and a timestamp (Unix time).
 */
class payloadDecoder
{
private:
    uint32_t _id;           ///< @brief Decoded identification number (4 bytes).
    uint8_t _version;       ///< @brief Decoded payload version number (1 byte).
    bool _doorStatus;       ///< @brief Decoded door status (1 bit). True if closed, false if open.
    bool _catchDetect;      ///< @brief Decoded catch detection (1 bit). True if a catch is detected.
    bool _trapDisplacement; ///< @brief Decoded trap displacement (1 bit). True if the trap has been moved.
    uint8_t _batteryStatus; ///< @brief Decoded battery status (1 byte). E.g., percentage.
    uint32_t _unixTime;     ///< @brief Decoded date and time (4 bytes) as a Unix timestamp.
    uint8_t *_buffer;       ///< @brief Pointer to the buffer containing the payload to be decoded.
    uint8_t _bufferSize;    ///< @brief Size of the payload buffer in bytes.

    /**
     * @brief Extracts a uint8_t value from the buffer at the specified index.
     * @param buf Pointer to the buffer.
     * @param idx The index in the buffer from which to extract the value. Defaults to 0.
     * @return The extracted uint8_t value.
     */
    uint8_t extract_uint8(const uint8_t *buf, const unsigned char idx = 0);

    /**
     * @brief Extracts a uint16_t value from the buffer at the specified index.
     * @param buf Pointer to the buffer.
     * @param idx The starting index in the buffer from which to extract the value. Defaults to 0.
     * @return The extracted uint16_t value.
     */
    uint16_t extract_uint16(const uint8_t *buf, const unsigned char idx = 0);

    /**
     * @brief Extracts a uint32_t value from the buffer at the specified index.
     * @param buf Pointer to the buffer.
     * @param idx The starting index in the buffer from which to extract the value. Defaults to 0.
     * @return The extracted uint32_t value.
     */
    uint32_t extract_uint32(const uint8_t *buf, const unsigned char idx = 0);

    /**
     * @brief Extracts a boolean value from the buffer at the specified index and bit position.
     * @param buf Pointer to the buffer.
     * @param idx The index in the buffer where the byte containing the bit is located. Defaults to 0.
     * @param pos The bit position (0-7) within the byte at idx from which to extract the boolean. Defaults to 0.
     * @return The extracted boolean value (true for 1, false for 0).
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
    
    payloadDecoder(const payloadDecoder &) = delete;            ///< Copy constructor disabled.
    payloadDecoder &operator=(const payloadDecoder &) = delete; ///< Assignment operator disabled.

    /**
     * @brief Sets the payload buffer to be decoded.
     * @param payload Pointer to the buffer containing the payload data.
     *                The payloadDecoder does not take ownership of this buffer.
     */
    void setPayload(uint8_t *payload) { _buffer = payload; }

    /**
     * @brief Sets the size of the payload buffer.
     * @param size The size of the payload in bytes.
     */
    void setPayloadSize(uint8_t size) { _bufferSize = size; }

    /**
     * @brief Decodes the payload from the buffer.
     * This function parses the `_buffer` (previously set by `setPayload` and `setPayloadSize`)
     * and populates the internal member variables (_id, _version, etc.) with the decoded values.
     */
    void decodePayload();

    /**
     * @brief Gets the decoded identification number.
     * @return The identification number.
     */
    uint32_t get_id() const { return _id; }

    /**
     * @brief Gets the decoded payload version number.
     * @return The payload version.
     */
    uint8_t get_version() const { return _version; }

    /**
     * @brief Gets the decoded door status.
     * @return True if the door is closed, false if open.
     */
    bool get_doorStatus() const { return _doorStatus; }

    /**
     * @brief Gets the decoded catch detection status.
     * @return True if a catch is detected, false otherwise.
     */
    bool get_catchDetect() const { return _catchDetect; }

    /**
     * @brief Gets the decoded trap displacement status.
     * @return True if the trap has been moved, false otherwise.
     */
    bool get_trapDisplacement() const { return _trapDisplacement; }

    /**
     * @brief Gets the decoded battery status.
     * @return The battery status (e.g., percentage).
     */
    uint8_t get_batteryStatus() const { return _batteryStatus; }

    /**
     * @brief Gets the decoded Unix time.
     * @return The Unix timestamp (seconds since epoch).
     */
    uint32_t get_unixTime() const { return _unixTime; }

    /**
     * @brief Prints the decoded payload in a human-readable format to the console.
     * Displays each decoded field and its value.
     */
    void printPayloadDecoded();
};

#endif // DECODER_H
