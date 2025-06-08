# IoT Node Details for SMARTrap

This document provides details about the IoT Node used in the SMARTrap project, focusing on hardware simulation for development and the LoRaWAN payload structure. The IoT Node is based on The Things Uno (Arduino Leonardo).

## Chapter 1: Hardware Simulation

### 1.1 Overview
The muskrat trap project leverages the The Things Uno hardware to develop a smart muskrat trap. This section provides an overview of key hardware simulations, the events that need to be communicated, and how these events can be simulated using the onboard components of the HAN IoT Node. The primary goal is to meet the project requirements by ensuring that hardware and software work seamlessly to capture and report events accurately.

### 1.2 Hardware Components for Simulation
-   **HAN IoT Node:** The core microcontroller board (The Things Uno, based on Arduino Leonardo).
-   **Sensors and Actuators:** Simulated using onboard buttons and LEDs to mimic real sensor inputs and outputs.

### 1.3 Events to be Communicated
The muskrat trap must communicate several critical events:
1.  **Trap Status (Door Open/Closed):** Indicates whether the trap is currently set (open) or triggered (closed).
2.  **Catch Detection:** Confirms if a muskrat has been captured.
3.  **Trap Displacement:** Alerts if the trap has been moved from its original position.
4.  **Health Status:** Reports the operational status of the trap, including battery level.

### 1.4 Simulating Events
Given that actual sensors might not always be connected during development, stubs are used to simulate these events. The HAN IoT Node's buttons and LEDs represent sensor inputs and outputs, respectively.

#### 1.4.1 Door Status (Open/Closed)
-   **Simulation Method:** Use button `SWITCH 1` to set the trap door status. When the red button is pressed, the door is considered closed.
-   **Indication:** A pressed red button (closed trap door) sets `LED1` to ON.
-   **Implementation:** Configure an interrupt to detect button presses and update the trap status variable.

#### 1.4.2 Catch Detection
-   **Simulation Method:** Use button `SWITCH 2` to toggle the capture status of a muskrat.
-   **Indication:** Catch detected status (animal inside) sets `LED2` (often labeled LED 02) to ON.
-   **Implementation:** Similar to the trap status, use an interrupt to detect the button press and update the catch status.

#### 1.4.3 Trap Movement
-   **Simulation Method:** Simulate movement using both buttons `SWITCH 1` & `SWITCH 2`. Pressing both buttons at the same time will toggle the trap movement status.
-   **Indication:** Trap movement detected status sets `LED3` (often labeled LED 03) to ON.
-   **Implementation:** Detect simultaneous button presses and set a flag indicating movement.

#### 1.4.4 Health Status (Battery Level)
-   **Simulation Method:** Periodically check and report the position of the potentiometer `POTMETER 2` to simulate battery level.
-   **Indication:** Battery voltage percentage status is indicated by the brightness of `LED4` (often labeled LED 04). High battery percentage means high brightness.
-   **Implementation:** Use a timer interrupt or loop-based check to periodically update and send the health status.

### 1.5 Communication Protocol
The trap uses LoRaWAN for communication. Each event's data is encoded into a compact payload and sent over the network using LoRaWAN's standard protocols to ensure reliable and low-power communication.

### 1.6 Hardware Source Code Reference
For more detailed information about the HAN IoT Node hardware, refer to its [GitLab repository](https://gitlab.com/wlgrw/han-iot-node).

## Chapter 2: LoRaWAN Payload Structure

The data payload is designed to be as small as possible to conserve power and ensure it fits within a single LoRaWAN network package.

### 2.1 Payload Overview
The payload structure is as follows:

| Name                   | ID               | Type             | Size    |
|------------------------|------------------|------------------|---------|
| Identification number  | `id`             | unsigned integer | 4 bytes |
| Payload version number | `version`        | unsigned integer | 1 byte  |
| Door status            | `doorStatus`     | boolean          | 1 bit   |
| Catch detection        | `catchDetect`    | boolean          | 1 bit   |
| Trap Displacement      | `trapDisplacement`| boolean          | 1 bit   |
| Battery status         | `batteryStatus`  | unsigned integer | 1 byte  |
| Date and time          | `unixTime`       | unsigned integer | 4 bytes |

**Total Payload Size:** 11 bytes (10 bytes for discrete fields + 3 boolean bits packed into one of the bytes, typically handled by bitwise operations in the encoder/decoder).

### 2.2 Detailed Payload Breakdown

#### 2.2.1 Identification Number (`id`)
-   **Description**: A unique identification number assigned to each trap.
-   **Encoding**: 4 bytes, unsigned integer (Range: 0 - 4,294,967,295).

#### 2.2.2 Payload Version Number (`version`)
-   **Description**: Indicates the version of the payload format.
-   **Encoding**: 1 byte, unsigned integer (Range: 0 - 255).

#### 2.2.3 Door Status (`doorStatus`)
-   **Description**: Indicates whether the door is open or closed.
-   **Encoding**: 1 bit, boolean.
    -   `0` - Door Open
    -   `1` - Door Closed

#### 2.2.4 Catch Detection (`catchDetect`)
-   **Description**: Indicates whether a catch has been detected.
-   **Encoding**: 1 bit, boolean.
    -   `0` - No Catch
    -   `1` - Catch Detected

#### 2.2.5 Trap Displacement (`trapDisplacement`)
-   **Description**: Indicates if the trap has been displaced from its original position.
-   **Encoding**: 1 bit, boolean.
    -   `0` - No Displacement
    -   `1` - Displaced

*(Note: The three boolean values - `doorStatus`, `catchDetect`, and `trapDisplacement` - are typically packed into a single byte using bitwise operations to save space.)*

#### 2.2.6 Battery Status (`batteryStatus`)
-   **Description**: Provides the battery status of the trap. The value represents the battery level percentage.
-   **Encoding**: 1 byte, unsigned integer (Range: 0 - 255, where 255 could represent 100%).

#### 2.2.7 Date and Time (`unixTime`)
-   **Description**: The timestamp indicating when the data was recorded, represented as the number of seconds since January 1, 1970 (Unix epoch).
-   **Encoding**: 4 bytes, unsigned integer.

This structured payload ensures that all necessary information is transmitted efficiently over the LoRaWAN network.
