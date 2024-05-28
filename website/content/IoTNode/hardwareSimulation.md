---
weight: 1
title: "Hardware Simulation"
---
# Hardware Simulation Overview
The muskrat trap project leverages the The Things Uno hardware, based on the Arduino Leonardo, to develop a smart
muskrat trap.
This page provides an overview of key hardware simulations, the events that need to be communicated, and how these
events can be simulated.
The primary goal is to meet the requirements of the project, ensuring that the hardware and software work seamlessly together to capture and report events accurately.

## Key Hardware Simulation

### Hardware Components
The hardware setup consists of the following key components:
- **HAN IoT Node:** The core microcontroller board based on Arduino Leonardo.
- **Sensors and Actuators:** Simulated using onboard buttons and LEDs to mimic real sensor inputs and outputs.

### Events to be Communicated
The muskrat trap must communicate several critical events to ensure efficient monitoring and control. These events include:
1. **Trap Status (Open/Closed):** Indicates whether the trap is currently set (open) or triggered (closed).
2. **Catch Detection:** Confirms if a muskrat has been captured.
3. **Trap Movement:** Alerts if the trap has been moved from its original position.
4. **Health Status:** Reports the operational status of the trap, including battery level and connectivity.

### Simulating Events
Given that the actual sensors and actuators are not yet implemented, we will use stubs to simulate these events. The HAN IoT Node's buttons and LEDs will represent sensor inputs and outputs, respectively.

#### Trap Status (Open/Closed)
- **Simulation Method:** Use a button to toggle the trap status. Pressing the button changes the state from open to closed or vice versa.
- **Implementation:** Configure an interrupt or polling mechanism to detect button presses and update the trap status variable.

#### Catch Detection
- **Simulation Method:** Use a different button to simulate the capture of a muskrat. Each press of the button indicates a catch.
- **Implementation:** Similar to the trap status, use an interrupt or polling mechanism to detect the button press and update the catch status.

#### Trap Movement
- **Simulation Method:** Simulate movement using a tilt sensor or another button. A press indicates that the trap has been moved.
- **Implementation:** Detect button presses or tilt sensor activation and set a flag indicating movement.

#### Health Status
- **Simulation Method:** Periodically check and report the status of the onboard LEDs to simulate battery level and connectivity status.
- **Implementation:** Use a timer interrupt to periodically update and send the health status.

### Communication Protocol
The trap uses LoRaWAN for communication. Each event's data is encoded and sent over the network using LoRaWAN's standard protocols to ensure reliable and low-power communication.

## Conclusion
For more detailed information about the hardware, please visit the [GitLab
repository](https://gitlab.com/wlgrw/han-iot-node).
