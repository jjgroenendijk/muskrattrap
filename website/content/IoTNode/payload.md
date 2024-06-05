---
weight: 3
title: "Payload"
---

# Payload

The muskrat trap's payload consists of multiple elements to communicate various statuses. Below is the detailed breakdown of the payload structure:

#### 1. Identification Number (4 bytes)
- **Description**: A unique identification number assigned to each trap.
- **Encoding**: 4 bytes integer

#### 2. Version number (1 byte)
- **Description**: 
- **Encoding**: 1 byte integer (0-255)

#### 3. Door Status (1 bit)
- **Description**: Indicates whether the door is open or closed.
- **Encoding**: 
  - `0` - Door Open
  - `1` - Door Closed

#### 4. Catch Detection (1 bit)
- **Description**: Indicates whether a catch has been detected.
- **Encoding**: 
  - `0` - No Catch
  - `1` - Catch Detected

#### 5. Trap Displacement (1 bit)
- **Description**: Indicates if the trap has been displaced from its original position.
- **Encoding**: 
  - `0` - No Displacement
  - `1` - Displaced

#### 6. Battery Status (1 byte)
- **Description**: Provides the battery status of the trap. The value can range from 0 to 255, representing the battery level percentage.
- **Encoding**: 1 byte integer (0-255)


### Combined Payload Structure
The payload is transmitted as a sequence of bits, with each segment encoded as described above. The total payload size
is 7 bytes (6 bytes + 3 bits).