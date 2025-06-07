/**
 * @file encoder.cpp
 * @brief Implements the payloadEncoder class for creating LoRaWAN message payloads.
 * This file contains the definitions for the methods of the payloadEncoder class.
 * It handles the serialization of various data types (integers, booleans) into a
 * compact byte buffer, managing byte order (MSB first/Big-Endian for multi-byte types)
 * and bit-level packing for booleans. Memory for the buffer is dynamically allocated.
 * @author Project Contributors (Original by Jaap-Jan Groenendijk as per encoder.h)
 * @date 2024-03-15
 */
#include "encoder.h"
#include <stdlib.h> // malloc(), free()
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h" // Older Arduino
#include <iostream> // Fallback for non-Arduino
#endif

// Define debugSerial if not already defined (e.g. for non-Arduino testing)
#ifndef debugSerial
#ifdef ARDUINO
#define debugSerial Serial ///< \brief Defines Serial as the debug output stream on Arduino.
#else
#define debugSerial std::cout ///< \brief Defines std::cout as the debug output stream for non-Arduino environments.
#endif
#endif

/**
 * @brief Constructs a new payloadEncoder object.
 * \details Initializes member variables to default values (0 or false).
 * Allocates memory for the internal payload buffer `_buffer` using `malloc()`
 * with the size defined by `SENSOR_PAYLOAD_SIZE`.
 * Sets `_bufferSize` to 0, indicating an empty payload initially.
 * @warning The constructor uses `malloc`. The `_buffer` must be freed in the destructor.
 */
payloadEncoder::payloadEncoder() : _id{0},
                                   _version{0},
                                   _doorStatus{0},
                                   _catchDetect{0},
                                   _trapDisplacement{0},
                                   _batteryStatus{0},
                                   _unixTime{0},
                                   _buffer{nullptr}, // Initialize to nullptr before malloc
                                   _bufferSize{0}
{
    _buffer = reinterpret_cast<uint8_t *>(malloc(SENSOR_PAYLOAD_SIZE));
    if (_buffer == nullptr) {
        // Handle malloc failure, e.g., by setting an error state or logging
        #if defined(ARDUINO)
        if(debugSerial) debugSerial.println("Error: Payload buffer malloc failed.");
        #else
        std::cerr << "Error: Payload buffer malloc failed." << std::endl;
        #endif
        // Potentially set _bufferSize to a state indicating error, or throw exception
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
 * - Byte 5: Status Bits
 *   - Bit 2: Door Status (`_doorStatus`, bool)
 *   - Bit 1: Catch Detect (`_catchDetect`, bool)
 *   - Bit 0: Trap Displacement (`_trapDisplacement`, bool)
 * - Byte 6: Battery Status (`_batteryStatus`, uint8_t)
 * - Bytes 7-10: Unix Time (`_unixTime`, uint32_t, Big-Endian)
 * The `_bufferSize` is updated to reflect the final size of the encoded payload.
 * If `_buffer` is null (e.g., due to malloc failure), this function does nothing.
 * @note The boolean values are packed into a single byte, with bit 2 for doorStatus,
 * bit 1 for catchDetect, and bit 0 for trapDisplacement. This order is critical
 * for the `add_bool` calls.
 */
void payloadEncoder::composePayload()
{
    if (!_buffer) return; // Do nothing if buffer allocation failed

    _bufferSize = 0; // Initialize buffer size for new composition

    // Encode ID (uint32_t, Big-Endian)
    _bufferSize = add_uint32(_bufferSize, _id);
    // Encode Version (uint8_t)
    _bufferSize = add_uint8(_bufferSize, _version);

    _bufferSize = add_bool(_bufferSize, _doorStatus, 2);
    _bufferSize = add_bool(_bufferSize, _catchDetect, 1);
    _bufferSize = add_bool(_bufferSize, _trapDisplacement, 0);

    _bufferSize = add_uint8(_bufferSize, _batteryStatus);
    _bufferSize = add_uint32(_bufferSize, _unixTime);

    ///  show payload size in bytes for debugging purposes
    #ifdef ARDUINO
    debugSerial.print("Payload size in bytes: ");
    debugSerial.println(static_cast<int>(_bufferSize));
    #else
    // std::cout << "Payload size in bytes: " << static_cast<int>(_bufferSize) << std::endl; // Keep for non-arduino if needed
    #endif
}

/**
 * @brief Adds a uint8_t value to the buffer at the specified index.
 *
 * @param idx_in The current index in the `_buffer` where the value should be written.
 * @param value The uint8_t value to be added.
 * @return The updated index in the `_buffer` after adding the value (idx_in + 1).
 */
unsigned char payloadEncoder::add_uint8(unsigned char idx_in, const uint8_t value)
{
    /**
     * Adds a uint8_t value to the buffer at the specified index.
     *
     * @param idx_in The index in the buffer where the value should be added.
     * @param value The uint8_t value to be added to the buffer.
     * @return The updated index after adding the value.
     */
    _buffer[idx_in++] = value;
    return (idx_in);
}

/**
 * @brief Adds a uint16_t value to the buffer at the specified index.
 *
 * The value is added in big-endian format (most significant byte first).
 * @param idx_in The current index in the `_buffer` where the value should be written.
 * @param value The uint16_t value to be added.
 * @return The updated index in the `_buffer` after adding the value (idx_in + 2).
 */
unsigned char payloadEncoder::add_uint16(unsigned char idx_in, const uint16_t value)
{
    /**
     * Adds a 16-bit unsigned integer to the buffer at the specified index.
     *
     * @param idx_in The index in the buffer where the value should be added.
     * @param value The 16-bit unsigned integer value to be added.
     * @return The updated index after adding the value to the buffer.
     */

    _buffer[idx_in++] = (value >> 8) & 0xFF; // msb
    _buffer[idx_in++] = (value) & 0xFF;      // lsb

    return (idx_in);
}

/**
 * @brief Adds a uint32_t value to the buffer at the specified index.
 *
 * The value is added in big-endian format (most significant byte first).
 * @param idx_in The current index in the `_buffer` where the value should be written.
 * @param value The uint32_t value to be added.
 * @return The updated index in the `_buffer` after adding the value (idx_in + 4).
 */
unsigned char payloadEncoder::add_uint32(unsigned char idx_in, uint32_t value)
{
    /**
     * Adds a 32-bit unsigned integer to the buffer.
     *
     * @param idx_in The starting index in the buffer.
     * @param value The value to be added.
     * @return The updated index after adding the value.
     */

    _buffer[idx_in++] = (value >> 24) & 0xFF; // MSB
    _buffer[idx_in++] = (value >> 16) & 0xFF;
    _buffer[idx_in++] = (value >> 8) & 0xFF;
    _buffer[idx_in++] = value & 0xFF;         // LSB
    return (idx_in);
}

/**
 * @brief Adds a boolean value to the payload buffer at a specific bit position within a byte.
 *
 * This function sets or clears a specific bit in the `_buffer` at `idx_in` based on the `value`.
 * If `value` is true, the bit at `pos` is set to 1; otherwise, it's cleared to 0.
 * If `pos` is 0, it implies this is the last bit being packed into the current byte, so `idx_in` is incremented.
 *
 * @param idx_in The index of the byte in `_buffer` to modify.
 * @param value The boolean value to be added.
 * @param pos The bit position (0-7, where 0 is typically the LSB) within the byte `_buffer[idx_in]`.
 * @return The updated index. It increments `idx_in` if `pos` is 0, otherwise returns `idx_in` unchanged.
 */
unsigned char payloadEncoder::add_bool(unsigned char idx_in, bool value, unsigned int pos)
{
    /**
     * @brief Adds a boolean value to the payload buffer at the specified position.
     *
     * This function sets or clears a specific bit in the buffer based on the given boolean value.
     * If the value is true, the bit at the specified position is set to 1.
     * If the value is false, the bit at the specified position is set to 0.
     *
     * @param idx_in The index of the buffer where the boolean value will be added.
     * @param value The boolean value to be added to the buffer.
     * @param pos The position of the bit in the buffer where the boolean value will be added.
     * @return The updated index of the buffer.
     */

    if (value)
    {
        _buffer[idx_in] |= (1 << pos);
    }
    else
    {
        _buffer[idx_in] &= ~(1 << pos);
    }
    if (pos == 0)
    {
        idx_in++;
    }
    return (idx_in);
}

/**
 * @brief Prints the payload in binary format to the `debugSerial`.
 *
 * Iterates through the `_buffer` and prints each byte as an 8-bit binary number.
 * This function is primarily for debugging purposes to inspect the raw payload.
 * @note This function is commented out in the original code, potentially due to
 * `std::bitset` not being readily available or suitable for all Arduino environments.
 * If uncommented and `std::bitset` is not available, it would need an alternative implementation.
 */
/*
void payloadEncoder::printPayloadBinary()
{
    
     * Prints the payload in binary format for debugging purposes.
     *
     * This function converts each byte in the payload buffer to its binary representation
     * and prints it to the standard output. The binary representation is displayed as a
     * sequence of 8 bits, separated by spaces.
     *
     * @note This function assumes that the payload buffer has been properly initialized
     *       and contains valid data.

    std::cout << "Encoder payload binary: ";
    for (unsigned int i = 0; i < _bufferSize; ++i)
    {
        std::bitset<8> binary(_buffer[i]); /// convert to binary
        std::cout << binary << " ";
    }
    // std::cout << std::endl; // Arduino doesn't have std::bitset easily
}
*/

/**
 * @brief Prints the encoded payload data in a human-readable format to the `debugSerial`.
 *
 * This function displays the values of all the member variables (`_id`, `_version`,
 * `_doorStatus`, `_catchDetect`, `_trapDisplacement`, `_batteryStatus`, `_unixTime`)
 * that were used to compose the payload. Useful for verifying the data before encoding
 * or for debugging the encoded output.
 */
void payloadEncoder::printPayloadEncoded()
{
    /**
     * Prints the encoded payload information.
     * This function prints the ID, version, door status, catch detect,
     * trap displacement, battery status, and Unix time of the encoded payload.
     */
    #ifdef ARDUINO
    debugSerial.println("Payload encoded: ");
    debugSerial.print("ID: "); debugSerial.println(_id);
    debugSerial.print("Version: "); debugSerial.println(static_cast<int>(_version));
    debugSerial.print("Door status: "); debugSerial.println(_doorStatus);
    debugSerial.print("Catch detect: "); debugSerial.println(_catchDetect);
    debugSerial.print("Trap displacement: "); debugSerial.println(_trapDisplacement);
    debugSerial.print("Battery status: "); debugSerial.println(static_cast<int>(_batteryStatus));
    debugSerial.print("Unix time: "); debugSerial.println(_unixTime);
    #else
    std::cout << "Payload encoded: " << std::endl;
    std::cout << "ID: " << _id << std::endl;
    std::cout << "Version: " << static_cast<int>(_version) << std::endl;
    std::cout << "Door status: " << _doorStatus << std::endl;
    std::cout << "Catch detect: " << _catchDetect << std::endl;
    std::cout << "Trap displacement: " << _trapDisplacement << std::endl;
    std::cout << "Battery status: " << static_cast<int>(_batteryStatus) << std::endl;
    std::cout << "Unix time: " << _unixTime << std::endl;
    #endif
}
