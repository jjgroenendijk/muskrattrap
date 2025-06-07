/**
 * @file encoder.cpp
 * @brief Implements the payloadEncoder class for creating LoRaWAN message payloads.
 * This file contains the definitions for the methods of the payloadEncoder class.
 * It handles the serialization of various data types (integers, booleans) into a
 * compact byte buffer, managing byte order (MSB first/Big-Endian for multi-byte types)
 * and bit-level packing for booleans. Memory for the buffer is dynamically allocated.
 * This version is intended for use in the `payloadCoder` host-side utility.
 * @author Project Contributors (Original by Jaap-Jan Groenendijk as per encoder.h)
 * @date 2024-03-15
 * @version 1.1 (Reflecting Doxygen standardization for payloadCoder directory)
 */
#include "encoder.h"
#include <iostream> // For std::cout, std::endl for debugging
#include <stdlib.h> // For malloc(), free()
#include <cstring>  // For std::memset if initializing buffer

/**
 * @brief Constructs a new payloadEncoder object.
 * \details Initializes member variables to default values (0 or false).
 * Allocates memory for the internal payload buffer `_buffer` using `malloc()`
 * with the size defined by `SENSOR_PAYLOAD_SIZE`.
 * Sets `_bufferSize` to 0, indicating an empty payload initially.
 * The buffer is initialized to zeros.
 * @warning The constructor uses `malloc`. The `_buffer` must be freed in the destructor.
 */
payloadEncoder::payloadEncoder() : _id{0},
                                   _version{0},
                                   _doorStatus{0},
                                   _catchDetect{0},
                                   _trapDisplacement{0},
                                   _batteryStatus{0},
                                   _unixTime{0},
                                   _buffer{nullptr},
                                   _bufferSize{0}
{
    _buffer = reinterpret_cast<uint8_t *>(malloc(SENSOR_PAYLOAD_SIZE));
    if (_buffer != nullptr) {
        // Initialize buffer to zeros, especially important for add_bool operations.
        memset(_buffer, 0, SENSOR_PAYLOAD_SIZE);
    } else {
        std::cerr << "Error: Payload buffer malloc failed in payloadEncoder constructor." << std::endl;
        // Consider setting an error state or throwing an exception
    }
}

/**
 * @brief Destroys the payloadEncoder object.
 * \details Frees the memory allocated for the `_buffer` using `free()` to prevent memory leaks.
 * It's safe to call `free()` on a `nullptr`.
 */
payloadEncoder::~payloadEncoder()
{
    free(_buffer);
    _buffer = nullptr; // Good practice to nullify pointer after free
}

/**
 * @brief Composes the payload by encoding all set member variables into the buffer.
 * \details This function populates the `_buffer` with the sensor data and metadata.
 * It calls the internal `add_uint32`, `add_uint8`, and `add_bool` methods
 * to serialize the data fields into the buffer according to the following structure:
 * - Bytes 0-3: ID (`_id`, uint32_t, Big-Endian)
 * - Byte 4: Version (`_version`, uint8_t)
 * - Byte 5: Status Bits (ensure byte is zeroed before setting bits)
 *   - Bit 2: Door Status (`_doorStatus`, bool)
 *   - Bit 1: Catch Detect (`_catchDetect`, bool)
 *   - Bit 0: Trap Displacement (`_trapDisplacement`, bool)
 * - Byte 6: Battery Status (`_batteryStatus`, uint8_t)
 * - Bytes 7-10: Unix Time (`_unixTime`, uint32_t, Big-Endian)
 * The `_bufferSize` is updated to reflect the final size of the encoded payload.
 * If `_buffer` is null (e.g., due to malloc failure), this function does nothing.
 * @note The boolean values are packed into a single byte. The byte `_buffer[_bufferSize]`
 *       (which will become byte 5) should be initialized to 0 before `add_bool` calls
 *       if `add_bool` doesn't manage this (which it does via `&= ~`).
 *       The order of `add_bool` calls (from highest bit to lowest) is important.
 */
void payloadEncoder::composePayload()
{
    if (!_buffer) {
        std::cerr << "Error: Cannot compose payload, buffer is null." << std::endl;
        return;
    }

    _bufferSize = 0; // Reset buffer size for new composition
    // Ensure the byte for booleans is clear if add_bool doesn't guarantee it on first write.
    // However, a common pattern for add_bool is to |= (1 << pos) or &= ~(1 << pos),
    // which requires the byte to be 0 initially for the first set of booleans.
    // This is handled by memset in constructor now.
    // _buffer[5] = 0; // Explicitly clear the byte for boolean packing if needed.

    // Encode ID (uint32_t, Big-Endian)
    _bufferSize = add_uint32(_bufferSize, _id);
    // Encode Version (uint8_t)
    _bufferSize = add_uint8(_bufferSize, _version);

    // Encode boolean status flags into the next byte (byte 5)
    // Note: add_bool for pos 2, then 1, then 0 (LSB). idx_in is returned by add_bool.
    // If it's the same byte, idx_in won't change until pos 0 is written.
    unsigned char statusByteIndex = _bufferSize; // Current byte index for booleans
    add_bool(statusByteIndex, _doorStatus, 2);
    add_bool(statusByteIndex, _catchDetect, 1);
    _bufferSize = add_bool(statusByteIndex, _trapDisplacement, 0); // This will increment _bufferSize

    // Encode Battery Status (uint8_t)
    _bufferSize = add_uint8(_bufferSize, _batteryStatus);
    // Encode Unix Time (uint32_t, Big-Endian)
    _bufferSize = add_uint32(_bufferSize, _unixTime);

    // Debug output for payload size
    // std::cout << "Payload size in bytes: " << static_cast<int>(_bufferSize) << std::endl;
}

/**
 * @brief Adds a uint8_t value to the buffer at the specified index.
 * @param idx_in The current index in the `_buffer` where the value should be written.
 * @param value The uint8_t value to be added.
 * @return The updated index in the `_buffer` after adding the value (idx_in + 1).
 */
unsigned char payloadEncoder::add_uint8(unsigned char idx_in, const uint8_t value)
{
    if (_buffer && idx_in < SENSOR_PAYLOAD_SIZE) {
        _buffer[idx_in++] = value;
    } else {
        std::cerr << "Error: Buffer overflow or null buffer in add_uint8." << std::endl;
    }
    return idx_in;
}

/**
 * @brief Adds a uint16_t value to the buffer at the specified index (Big-Endian).
 * \details The value is added in big-endian format (most significant byte first).
 * @param idx_in The current index in the `_buffer` where the value should be written.
 * @param value The uint16_t value to be added.
 * @return The updated index in the `_buffer` after adding the value (idx_in + 2).
 */
unsigned char payloadEncoder::add_uint16(unsigned char idx_in, const uint16_t value)
{
    if (_buffer && (idx_in + 1) < SENSOR_PAYLOAD_SIZE) {
        _buffer[idx_in++] = (value >> 8) & 0xFF; // MSB
        _buffer[idx_in++] = (value) & 0xFF;      // LSB
    } else {
        std::cerr << "Error: Buffer overflow or null buffer in add_uint16." << std::endl;
    }
    return idx_in;
}

/**
 * @brief Adds a uint32_t value to the buffer at the specified index (Big-Endian).
 * \details The value is added in big-endian format (most significant byte first).
 * @param idx_in The current index in the `_buffer` where the value should be written.
 * @param value The uint32_t value to be added.
 * @return The updated index in the `_buffer` after adding the value (idx_in + 4).
 */
unsigned char payloadEncoder::add_uint32(unsigned char idx_in, uint32_t value)
{
    if (_buffer && (idx_in + 3) < SENSOR_PAYLOAD_SIZE) {
        _buffer[idx_in++] = (value >> 24) & 0xFF; // MSB
        _buffer[idx_in++] = (value >> 16) & 0xFF;
        _buffer[idx_in++] = (value >> 8) & 0xFF;
        _buffer[idx_in++] = value & 0xFF;         // LSB
    } else {
        std::cerr << "Error: Buffer overflow or null buffer in add_uint32." << std::endl;
    }
    return idx_in;
}

/**
 * @brief Adds a boolean value to the payload buffer at a specific bit position within a byte.
 * \details This function sets or clears a specific bit in the `_buffer` at `idx_in` based on `value`.
 * If `value` is true, the bit at `pos` is set to 1; otherwise, it's cleared to 0.
 * The byte `_buffer[idx_in]` should be initialized to zero before the first bit is set
 * for a new set of boolean flags (handled by `memset` in constructor).
 * If `pos` is 0 (LSB), it implies this is the last bit being packed into the current byte,
 * so the function increments `idx_in` to move to the next byte.
 * @param idx_in The index of the byte in `_buffer` to modify.
 * @param value The boolean value to be added (true sets bit, false clears bit).
 * @param pos The bit position (0-7, where 0 is LSB) within the byte `_buffer[idx_in]`.
 * @return The index for the next byte if `pos` was 0 (indicating byte completion), otherwise `idx_in`.
 */
unsigned char payloadEncoder::add_bool(unsigned char idx_in, bool value, unsigned int pos)
{
    if (!_buffer || idx_in >= SENSOR_PAYLOAD_SIZE) {
        std::cerr << "Error: Buffer overflow or null buffer in add_bool." << std::endl;
        // If idx_in is already out of bounds, and pos is 0, returning idx_in+1 would be worse.
        // So just return current (likely invalid) idx_in.
        return idx_in;
    }

    if (value)
    {
        _buffer[idx_in] |= (1 << pos);
    }
    else
    {
        _buffer[idx_in] &= ~(1 << pos);
    }

    if (pos == 0) // If the LSB (position 0) was just written, this byte is considered complete.
    {
        idx_in++; // Move to the next byte index for subsequent operations.
    }
    return idx_in;
}

/**
 * @brief Prints the payload buffer in binary format to standard output.
 * \details Iterates through the `_buffer` up to `_bufferSize` and prints each byte
 * as an 8-bit binary number. This function is primarily for debugging purposes.
 * @note This function is currently commented out in the source. The original may have
 *       intended to use `std::bitset` which is not standard in all C++ environments
 *       (especially embedded). An alternative manual implementation would be needed
 *       if this functionality is required and `std::bitset` is unavailable.
 */
/*
void payloadEncoder::printPayloadBinary()
{
    // std::cout << "Encoder payload binary: ";
    // for (unsigned int i = 0; i < _bufferSize; ++i)
    // {
    //    // Manual way to print bits if std::bitset is not available:
    //    for (int j = 7; j >= 0; --j) {
    //        std::cout << ((_buffer[i] >> j) & 1);
    //    }
    //    std::cout << " ";
    // }
    // std::cout << std::endl;
}
*/

/**
 * @brief Prints the values of the fields intended for encoding to standard output.
 * \details This function displays the current values of all the member variables
 * (`_id`, `_version`, `_doorStatus`, etc.) that are used to compose the payload.
 * Useful for verifying the data before it's encoded or for debugging.
 */
void payloadEncoder::printPayloadEncoded()
{
    std::cout << "Payload fields to be encoded: " << std::endl;
    std::cout << "ID: " << _id << std::endl;
    std::cout << "Version: " << static_cast<int>(_version) << std::endl;
    std::cout << "Door status: " << _doorStatus << std::endl;
    std::cout << "Catch detect: " << _catchDetect << std::endl;
    std::cout << "Trap displacement: " << _trapDisplacement << std::endl;
    std::cout << "Battery status: " << static_cast<int>(_batteryStatus) << std::endl;
    std::cout << "Unix time: " << _unixTime << std::endl;
}
