/**
 * @file decoder.cpp
 * @brief Implements the payloadDecoder class for parsing LoRaWAN message payloads.
 * This file contains the definitions for the methods of the payloadDecoder class,
 * including the core `decodePayload` method and helper utilities for extracting
 * various data types from a raw byte buffer. It handles byte ordering (MSB first)
 * and bit-level extraction for boolean flags. This version is intended for
 * use in the `payloadCoder` host-side utility.
 * @author Project Contributors
 * @date 2024-03-15
 */
#include "decoder.h"
#include <iostream> // For std::cout, std::endl for debugging
#include <cstring>  // For std::memcpy if needed, though not currently used for extraction

/**
 * @brief Constructs a new payloadDecoder object.
 * \details Initializes all internal data members to zero or nullptr.
 * The actual payload buffer and its size must be set using
 * `setPayload()` and `setPayloadSize()` before decoding.
 */
payloadDecoder::payloadDecoder() : _id{0},
                                   _version{0},
                                   _doorStatus{0},
                                   _catchDetect{0},
                                   _trapDisplacement{0},
                                   _batteryStatus{0},
                                   _unixTime{0},
                                   _buffer{nullptr},
                                   _bufferSize{0}
{
    // Constructor body is empty; initialization is done via initializer list.
}

/**
 * @brief Destructor for the payloadDecoder class.
 * \details Currently, no dynamic memory is managed directly by this class,
 * so the destructor is empty. The payload buffer is managed externally.
 */
payloadDecoder::~payloadDecoder()
{
    // Destructor body is empty.
}

/**
 * @brief Decodes the payload from the internal buffer using a predefined structure.
 * \details This function populates the decoder's internal member variables
 * (e.g., `_id`, `_version`, `_doorStatus`) by extracting data from the
 * `_buffer`. The extraction assumes a specific byte order (MSB first/Big-Endian for multi-byte types)
 * and field layout:
 * - Bytes 0-3: ID (uint32_t)
 * - Byte 4: Version (uint8_t)
 * - Byte 5: Status bits
 *   - Bit 2: Door Status (1 = closed, 0 = open) - MSB direction for bits
 *   - Bit 1: Catch Detect (1 = detected, 0 = not detected)
 *   - Bit 0: Trap Displacement (1 = displaced, 0 = not displaced) - LSB
 * - Byte 6: Battery Status (uint8_t)
 * - Bytes 7-10: Unix Time (uint32_t)
 *
 * The `setPayload()` and `setPayloadSize()` methods must be called before this.
 * @note Assumes `_buffer` points to valid data and `_bufferSize` is correctly set.
 *       Minimum payload size expected is 11 bytes for all fields.
 */
void payloadDecoder::decodePayload()
{
    // The commented-out binary print is useful for debugging payload structure.
    /*
    std::cout << "Decoder payload binary: ";
    for (int i = 0; i < _bufferSize; i++) {
        for (int j = 7; j >= 0; j--) { // Print MSB of byte first
            std::cout << ((_buffer[i] >> j) & 1);
        }
        std::cout << " ";
    }
    std::cout << std::endl;
    */

    if (!_buffer || _bufferSize < 11) { // Check for minimum expected size.
        std::cerr << "Error: Payload buffer not set or too small for decoding. Size: "
                  << static_cast<int>(_bufferSize) << std::endl;
        return;
    }

    _id = extract_uint32(_buffer, 0);
    _version = extract_uint8(_buffer, 4);
    // Status byte (byte 5): Bit 2 = Door, Bit 1 = Catch, Bit 0 = Displacement
    _doorStatus = extract_bool(_buffer, 5, 2);       // Bit 2
    _catchDetect = extract_bool(_buffer, 5, 1);      // Bit 1
    _trapDisplacement = extract_bool(_buffer, 5, 0); // Bit 0 (LSB)
    _batteryStatus = extract_uint8(_buffer, 6);
    _unixTime = extract_uint32(_buffer, 7);
}

/**
 * @brief Extracts an 8-bit unsigned integer (uint8_t) from the buffer at the specified index.
 * @param buf Pointer to the buffer containing the payload data.
 * @param idx The index in the buffer from which to extract the byte.
 * @return The extracted uint8_t value.
 */
uint8_t payloadDecoder::extract_uint8(const uint8_t *buf, const unsigned char idx)
{
    return static_cast<uint8_t>(buf[idx]);
}

/**
 * @brief Extracts a 16-bit unsigned integer (uint16_t) from the buffer, assuming MSB first (Big-Endian).
 * @param buf Pointer to the buffer containing the payload data.
 * @param idx The starting index in the buffer for the 2-byte value. `buf[idx]` is MSB, `buf[idx+1]` is LSB.
 * @return The extracted uint16_t value.
 */
uint16_t payloadDecoder::extract_uint16(const uint8_t *buf, const unsigned char idx)
{
    uint16_t value{0};
    value = static_cast<uint16_t>(buf[idx] << 8); // MSB
    value |= static_cast<uint16_t>(buf[idx + 1]); // LSB
    return value;
}

/**
 * @brief Extracts a 32-bit unsigned integer (uint32_t) from the buffer, assuming MSB first (Big-Endian).
 * @param buf Pointer to the buffer containing the payload data.
 * @param idx The starting index in the buffer for the 4-byte value. `buf[idx]` is MSB, `buf[idx+3]` is LSB.
 * @return The extracted uint32_t value.
 */
uint32_t payloadDecoder::extract_uint32(const uint8_t *buf, const unsigned char idx)
{
    uint32_t value{0};
    // Loop constructs the 32-bit value from 4 bytes, MSB first.
    // buf[idx] is shifted left by 24 bits (becomes the most significant byte).
    // buf[idx+1] is shifted left by 16 bits.
    // buf[idx+2] is shifted left by 8 bits.
    // buf[idx+3] is the least significant byte.
    for (uint8_t i = 0; i < 4; i++)
    {
        value |= static_cast<uint32_t>(buf[idx + i] << (24 - (i * 8)));
    }
    return value;
}

/**
 * @brief Extracts a boolean value from a specific bit within a byte in the buffer.
 * @param buf Pointer to the buffer containing the payload data.
 * @param idx The index of the byte in the buffer from which to extract the bit.
 * @param pos The bit position (0-7, where 0 is the LSB) within the byte `buf[idx]`.
 * @return True if the specified bit is 1, false if it is 0.
 */
bool payloadDecoder::extract_bool(const uint8_t *buf, const unsigned char idx, unsigned int pos)
{
    bool value;
    value = (buf[idx] >> pos) & 1; // Shift the desired bit to LSB position and mask with 1.
    return value;
}

/**
 * @brief Prints the decoded payload fields and their values to standard output (std::cout).
 * \details This function is useful for debugging and verifying that the payload
 * has been decoded as expected on a host system.
 */
void payloadDecoder::printPayloadDecoded()
{
    std::cout << "Payload decoded: " << std::endl;
    std::cout << "ID: " << _id << std::endl;
    std::cout << "Version: " << static_cast<int>(_version) << std::endl;
    std::cout << "Door status: " << _doorStatus << std::endl;
    std::cout << "Catch detect: " << _catchDetect << std::endl;
    std::cout << "Trap displacement: " << _trapDisplacement << std::endl;
    std::cout << "Battery status: " << static_cast<int>(_batteryStatus) << std::endl;
    std::cout << "Unix time: " << _unixTime << std::endl;
}