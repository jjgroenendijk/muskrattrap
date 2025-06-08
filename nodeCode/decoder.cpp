#include "decoder.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h" // Older Arduino
#include <iostream> // Fallback for non-Arduino, cout, endl // debugging only
#endif

// Define debugSerial if not already defined (e.g. for non-Arduino testing)
#ifndef debugSerial
#ifdef ARDUINO
#define debugSerial Serial // Assuming Serial is the debug port on Arduino
#else
#define debugSerial std::cout // Fallback for non-Arduino
#endif
#endif

/// @brief Constructs a new payloadDecoder object.
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
    // Constructor body
}

/// @brief Destructor for the payloadDecoder class.
payloadDecoder::~payloadDecoder()
{
    // Destructor
}

void payloadDecoder::decodePayload()
{
    /**
     * Decodes the payload data.
     * This function prints the payload in binary format and extracts various data fields from the payload buffer.

    std::cout << "Decoder payload binary: ";
    for (int i = 0; i < _bufferSize; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            std::cout << ((_buffer[i] >> j) & 1);
        }
        std::cout << " ";
    }
    std::cout << std::endl;
    */

    _id = static_cast<int>(extract_uint32(_buffer, 0));
    _version = static_cast<int>(extract_uint8(_buffer, 4));
    _doorStatus = extract_bool(_buffer, 5, 2);
    _catchDetect = extract_bool(_buffer, 5, 1);
    _trapDisplacement = extract_bool(_buffer, 5, 0);
    _batteryStatus = static_cast<int>(extract_uint8(_buffer, 6));
    _unixTime = static_cast<int>(extract_uint32(_buffer, 7));
}

uint8_t payloadDecoder::extract_uint8(const uint8_t *buf, const unsigned char idx)
{
    /**
     * Extracts a uint8_t value from the given buffer at the specified index.
     *
     * @param buf The buffer containing the data.
     * @param idx The index of the value to extract.
     * @return The extracted uint8_t value.
     */
    return static_cast<uint8_t>(buf[idx]);
}

uint16_t payloadDecoder::extract_uint16(const uint8_t *buf, const unsigned char idx)
{
    /**
     * @brief Extracts a 16-bit unsigned integer from a buffer at the specified index.
     *
     * This function takes a buffer `buf` and an index `idx` and extracts a 16-bit unsigned integer
     * from the buffer starting at the specified index. The most significant byte is located at `buf[idx]
     * and the least significant byte is located at `buf[idx + 1].
     *
     * @param buf Pointer to the buffer containing the data.
     * @param idx Index of the most significant byte in the buffer.
     * @return The extracted 16-bit unsigned integer value.
     */

    uint16_t value{0};
    value = static_cast<uint16_t>(buf[idx] << 8); // msb
    value |= static_cast<uint16_t>(buf[idx + 1]); // lsb
    return value;
}

uint32_t payloadDecoder::extract_uint32(const uint8_t *buf, const unsigned char idx)
{
    /**
     * Extracts a 32-bit unsigned integer from a buffer at the specified index.
     * This function takes a buffer `buf` and an index `idx` and extracts a 32-bit unsigned integer
     * from the buffer starting at the specified index. The most significant byte is located at `buf[idx]
     * and the least significant byte is located at `buf[idx + 3].
     * @param buf The buffer containing the data.
     * @param idx The index in the buffer where the 32-bit integer starts.
     * @return The extracted 32-bit unsigned integer.
     */

    uint32_t value{0};
    for (uint8_t i = 0; i < 4; i++)
    {
        value |= static_cast<uint32_t>(buf[idx + i] << (24 - (i * 8))); // msb
    }
    return value;
}

bool payloadDecoder::extract_bool(const uint8_t *buf, const unsigned char idx, unsigned int pos)
{
    /**
     * Extracts a boolean value from a buffer at a specified index and position.
     *
     * @param buf The buffer containing the data.
     * @param idx The index of the byte in the buffer.
     * @param pos The position of the bit within the byte.
     * @return The extracted boolean value.
     */
    bool value;
    value = (buf[idx] >> pos) & 1;
    return value;
}

// print payload decoded
void payloadDecoder::printPayloadDecoded()
{
    /**
     * Prints the decoded payload information.
     */
    #ifdef ARDUINO
    debugSerial.println("Payload decoded: ");
    debugSerial.print("ID: "); debugSerial.println(_id);
    debugSerial.print("Version: "); debugSerial.println(static_cast<int>(_version));
    debugSerial.print("Door status: "); debugSerial.println(_doorStatus);
    debugSerial.print("Catch detect: "); debugSerial.println(_catchDetect);
    debugSerial.print("Trap displacement: "); debugSerial.println(_trapDisplacement);
    debugSerial.print("Battery status: "); debugSerial.println(static_cast<int>(_batteryStatus));
    debugSerial.print("Unix time: "); debugSerial.println(_unixTime);
    #else
    std::cout << "Payload decoded: " << std::endl;
    std::cout << "ID: " << _id << std::endl;
    std::cout << "Version: " << static_cast<int>(_version) << std::endl;
    std::cout << "Door status: " << _doorStatus << std::endl;
    std::cout << "Catch detect: " << _catchDetect << std::endl;
    std::cout << "Trap displacement: " << _trapDisplacement << std::endl;
    std::cout << "Battery status: " << static_cast<int>(_batteryStatus) << std::endl;
    std::cout << "Unix time: " << _unixTime << std::endl;
    #endif
}
