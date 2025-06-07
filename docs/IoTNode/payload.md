---
weight: 3
title: "Payload"
---

# Payload

The data payload is made as small as possible to use less power and to make sure the payload fits inside a single
package on the LoRaWAN network.

## Payload overview
In short the payload structure is as follows:

| Name                   	| ID               	| Type             	| Size    	|
|------------------------	|------------------	|------------------	|---------	|
| Identification number  	| `id`               	| unsigned integer 	| 4 bytes 	|
| Payload version number 	| `version`          	| unsigned integer 	| 1 byte  	|
| Door status            	| `doorStatus`       	| boolean          	| 1 bit   	|
| Catch detection        	| `catchDetect`      	| boolean          	| 1 bit   	|
| Trap Displacement      	| `trapDisplacement` 	| boolean          	| 1 bit   	|
| Battery status         	| `batteryStatus`    	| unsigned integer 	| 1 byte  	|
| Date and time          	| `unixTime`         	| unsigned integer 	| 4 bytes 	|

Below is the detailed breakdown of the payload structure:

### 1. Identification Number
- **Description**: A unique identification number assigned to each trap.
- **Encoding**: 4 bytes integer (0-4294967296)

### 2. Version number
- **Description**: Indicates the version of the payload format.
- **Encoding**: 1 byte integer (0-255)

### 3. Door Status
- **Description**: Indicates whether the door is open or closed.
- **Encoding**: 1 bit boolean
  - `0` - Door Open
  - `1` - Door Closed

### 4. Catch Detection
- **Description**: Indicates whether a catch has been detected.
- **Encoding**: 1 bit boolean
  - `0` - No Catch
  - `1` - Catch Detected

### 5. Trap Displacement
- **Description**: Indicates if the trap has been displaced from its original position.
- **Encoding**: 1 bit boolean
  - `0` - No Displacement
  - `1` - Displaced

### 6. Battery Status
- **Description**: Provides the battery status of the trap. The value can range from 0 to 255, representing the battery
  level percentage.
- **Encoding**: 1 byte integer (0-255)

### 7. Date and time (unixtime)
- **Description**: The timestamp indicating when the data was recorded, represented as the number of seconds since January 1, 1970 (Unix epoch).
- **Encoding**: 4 bytes integer (0-4294967296)

### Combined Payload Structure
The payload is transmitted as a sequence of bits, with each segment encoded as described above. The total payload size
is 11 bytes (actually, it is 10 bytes + 3 bits).