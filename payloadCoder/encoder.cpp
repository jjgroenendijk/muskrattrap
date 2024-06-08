#include "encoder.h"
#include <iostream> // only used for debug output
#include <stdlib.h> // malloc()

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

/**
 * Adds a uint8_t value to the buffer at the specified index.
 *
 * @param idx_in The index in the buffer where the value should be added.
 * @param value The uint8_t value to be added to the buffer.
 * @return The updated index after adding the value.
 */
unsigned char payloadEncoder::add_uint8(unsigned char idx_in, const uint8_t value)
{
    _buffer[idx_in++] = value;
    return (idx_in);
}

/**
 * Adds a 16-bit unsigned integer to the buffer at the specified index.
 *
 * @param idx_in The index in the buffer where the value should be added.
 * @param value The 16-bit unsigned integer value to be added.
 * @return The updated index after adding the value to the buffer.
 */
unsigned char payloadEncoder::add_uint16(unsigned char idx_in, const uint16_t value)
{
    _buffer[idx_in++] = (value >> 8) & 0xFF; // msb
    _buffer[idx_in++] = (value) & 0xFF;      // lsb
    return (idx_in);
}

/**
 * Adds a 32-bit unsigned integer to the buffer.
 *
 * @param idx_in The starting index in the buffer.
 * @param value The value to be added.
 * @return The updated index after adding the value.
 */
unsigned char payloadEncoder::add_uint32(unsigned char idx_in, uint32_t value)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        _buffer[idx_in++] = (value >> 24) & 0xFF; // msb
        value = value << 8;                       // shift-left
    }
    return (idx_in);
}

/**
 * @brief Adds a boolean value to the payload buffer at the specified position.
 *
 * This function sets or clears a specific bit in the buffer based on the given boolean value.
 * If the value is true, the bit at the specified position is set to 1. If the value is false,
 * the bit at the specified position is cleared to 0.
 *
 * @param idx_in The index of the buffer where the boolean value will be added.
 * @param value The boolean value to be added to the buffer.
 * @param pos The position of the bit in the buffer where the boolean value will be added.
 * @return The updated index of the buffer.
 */
unsigned char payloadEncoder::add_bool(unsigned char idx_in, bool value, unsigned int pos)
{
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

void payloadEncoder::printPayloadBinary()
{
    std::cout << "Current payload in binary: ";
    for (unsigned int i = 0; i < _bufferSize; ++i)
    {
        std::bitset<8> binary(_buffer[i]);
        std::cout << binary << " ";
    }
    std::cout << std::endl;
}

/**
 * Prints the encoded payload information.
 */
void payloadEncoder::printPayloadEncoded()
{
    std::cout << "Payload encoded: " << std::endl;
    std::cout << "ID: " << _id << std::endl;
    std::cout << "Version: " << static_cast<int>(_version) << std::endl;
    std::cout << "Door status: " << _doorStatus << std::endl;
    std::cout << "Catch detect: " << _catchDetect << std::endl;
    std::cout << "Trap displacement: " << _trapDisplacement << std::endl;
    std::cout << "Battery status: " << static_cast<int>(_batteryStatus) << std::endl;
    std::cout << "Unix time: " << _unixTime << std::endl;
}