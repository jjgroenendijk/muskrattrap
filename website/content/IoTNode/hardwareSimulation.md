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

## Hardware Components
The hardware setup consists of the following key components:
- **HAN IoT Node:** The core microcontroller board based on Arduino Leonardo.
- **Sensors and Actuators:** Simulated using onboard buttons and LEDs to mimic real sensor inputs and outputs.

## Events to be Communicated
The muskrat trap must communicate several critical events to ensure efficient monitoring and control. These events include:
1. **Trap Status (Door Open/Closed):** Indicates whether the trap is currently set (open) or triggered (closed).
2. **Catch Detection:** Confirms if a muskrat has been captured.
3. **Trap Displacement:** Alerts if the trap has been moved from its original position.
4. **Health Status:** Reports the operational status of the trap, including battery level and connectivity.

## Simulating Events
Given that the actual sensors and actuators are not yet implemented, we will use stubs to simulate these events. The HAN IoT Node's buttons and LEDs will represent sensor inputs and outputs, respectively.

### Door Status (Open/Closed)
- **Simulation Method:** Use a button `SWITCH 1` to toggle the trap status. When the red button is pressed, the door is considered closed.
  A pressed red button, a closed trap door, sets LED1 to on.
- **Implementation:** Configure an interrupt to detect button presses and update the trap status variable.

### Catch Detection
- **Simulation Method:** Use button `SWITCH 2` to toggle the capture status of a muskrat. Catch detected status (animal inside) sets `LED 02` to ON.
- **Implementation:** Similar to the trap status, use an interrupt to detect the button press and update the catch status.

### Trap Movement
- **Simulation Method:** Simulate movement using both buttons `SWITCH 1` & `SWITCH 2`. Pressing both buttons at the same
  time will toggle the trap movement status. Trap movement detected status sets `LED 03` to ON.
- **Implementation:** Detect both button presses and set a flag indicating movement.

### Health Status
- **Simulation Method:** Periodically check and report the position of the potentiometer `POTMETER 2` to simulate battery
  level. Battery voltage ercentage status is indicated by the brightness of `LED 04` High battery percentage means high brightness.
- **Implementation:** Use a timer interrupt to periodically update and send the health status.

## Communication Protocol
The trap uses LoRaWAN for communication. Each event's data is encoded and sent over the network using LoRaWAN's standard protocols to ensure reliable and low-power communication.

## Source code
For more detailed information about the hardware, please visit the [GitLab
repository](https://gitlab.com/wlgrw/han-iot-node).
