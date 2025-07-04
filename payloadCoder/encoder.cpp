#include "encoder.h"
#include <iostream> // only used for debug output
#include <stdlib.h> // malloc()

/**
 * @brief Constructs a new payloadEncoder object.
 *
 * This constructor initializes the member variables of the payloadEncoder class,
 * including _id, _version, _doorStatus, _catchDetect, _trapDisplacement,
 * _batteryStatus, and _unixTime. It also allocates memory for the _buffer using
 * malloc() and sets _bufferSize to 0.
 */
payloadEncoder::payloadEncoder() : _id{0},
                                   _version{0},
                                   _doorStatus{0},
                                   _catchDetect{0},
                                   _trapDisplacement{0},
                                   _batteryStatus{0},
                                   _unixTime{0},
                                   _buffer{NULL},
                                   _bufferSize{0}
{
    _buffer = reinterpret_cast<uint8_t *>(malloc(SENSOR_PAYLOAD_SIZE));
}

payloadEncoder::~payloadEncoder()
{
    free(_buffer);
}

void payloadEncoder::composePayload()
{
    /**
     * @brief Composes the payload by adding various data elements to the buffer.
     *
     * This function initializes the buffer size and adds data elements such as ID, version, door status, catch detection,
     * trap displacement, battery status, and UNIX time to the buffer. It also prints the payload size in bytes for debugging purposes.
     */

    _bufferSize = 0; // init

    _bufferSize = add_uint32(_bufferSize, _id);
    _bufferSize = add_uint8(_bufferSize, _version);

    _bufferSize = add_bool(_bufferSize, _doorStatus, 2);
    _bufferSize = add_bool(_bufferSize, _catchDetect, 1);
    _bufferSize = add_bool(_bufferSize, _trapDisplacement, 0);

    _bufferSize = add_uint8(_bufferSize, _batteryStatus);
    _bufferSize = add_uint32(_bufferSize, _unixTime);

    ///  show payload size in bytes for debugging purposes
    std::cout << "Payload size in bytes: " << static_cast<int>(_bufferSize) << std::endl;
}

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
    std::cout << std::endl;
}
*/

void payloadEncoder::printPayloadEncoded()
{
    /**
     * Prints the encoded payload information.
     * This function prints the ID, version, door status, catch detect,
     * trap displacement, battery status, and Unix time of the encoded payload.
     */

    std::cout << "Payload encoded: " << std::endl;
    std::cout << "ID: " << _id << std::endl;
    std::cout << "Version: " << static_cast<int>(_version) << std::endl;
    std::cout << "Door status: " << _doorStatus << std::endl;
    std::cout << "Catch detect: " << _catchDetect << std::endl;
    std::cout << "Trap displacement: " << _trapDisplacement << std::endl;
    std::cout << "Battery status: " << static_cast<int>(_batteryStatus) << std::endl;
    std::cout << "Unix time: " << _unixTime << std::endl;
}
