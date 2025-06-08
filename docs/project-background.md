# Project Background: Smart Muskrat Trap

This document outlines the initial research, design considerations, and technology choices for the SMARTrap project, an intelligent muskrat trap solution.

## Chapter 1: LPWAN Technology Comparison

### 1.1 Communication Network for Smart Traps
To make a muskrat trap smart, it needs network communication. Since the trap can be placed in remote locations, it's essential to maximize battery life. Energy efficiency is crucial. The trap doesn't need high-speed communication but must have a good range. Several existing LPWAN technologies were considered for the muskrat trap, namely LoRaWAN, NB-IoT, and LTE-CAT-M.

### 1.2 LoRaWAN
LoRaWAN, which stands for Long Range Wide Area Network, is a communication network optimized for energy-efficient long-distance communication. The development of LoRa started in 2009 when two friends in France wanted to develop long-distance communication technology with low power consumption. Nicolas Sornin and Olivier Seller, the inventors of LoRa, met their third partner, François Sforza, in 2010. The three developers founded Cycleo in 2010. They began developing for the metering industry, adding wireless communication capabilities to gas, water, and electricity meters using Chirp Spread Spectrum (CSS) modulation technology.

In 2012, Cycleo was acquired by SemTech, who collaborated with the founders to improve the technology and develop the necessary chips for end devices and gateways. At the same time, a proprietary MAC protocol called "LoRaMAC" was created and later renamed "LoRaWAN". In 2015, the LoRa Alliance was established to support and promote the global adoption of the LoRaWAN standard. The ongoing development of the LoRaWAN protocol is managed by the open and non-profit organization LoRa Alliance, with SemTech as one of its founding members.

LoRa offers a range of 3 kilometers in urban areas and up to 10 kilometers in rural areas. This extensive range is achieved with energy consumption that is 3 to 5 times lower than other LPWAN technologies. The available bandwidth provided by LoRa varies between 290 bps and 50 kbps.

### 1.3 NB-IoT
Narrowband Internet of Things (NB-IoT) is also a communication network optimized for low energy consumption and long distances. The main technical difference from LoRaWAN is that NB-IoT uses existing LTE networks. NB-IoT operates within the license of 2G/3G/4G, so existing network operators do not need additional licenses. NB-IoT focuses on indoor coverage, low cost, long battery life, and high connection density. It uses a subset of the LTE standard but limits the used frequencies to 180 kHz and 200 kHz. The GmSA reported in 2019 that 101 network operators worldwide support the NB-IoT network, and 153 operators are investing in NB-IoT technology.

### 1.4 LTE-CAT-M
LTE-CAT-M, also known as LTE-MTC, is a type of radio technology for IoT and machine-to-machine communication. It offers benefits such as higher speed and mobility but is more expensive and requires more bandwidth than NB-IoT. In March 2019, the Global Mobile Suppliers Association reported that more than 100 operators had deployed/launched NB-IoT or LTE-M networks. LTE-CAT-M has some advantages over NB-IoT, such as the ability to achieve speeds up to 1 Mbps. In the IoT world, this is a very high speed. LTE-CAT-M also supports voice data transmission and works with moving devices. However, LTE-CAT-M has higher power consumption and higher hardware costs compared to LoRaWAN and NB-IoT.

### 1.5 Conclusion: LPWAN Choice
LoRaWAN is the network of choice for the Muskrat trap for the following reasons:
- **Energy Efficiency**: LoRaWAN is highly energy-efficient, making it ideal for battery-powered devices like the muskrat trap that need to operate for extended periods without frequent battery replacements.
- **Long Range**: The extensive range of LoRaWAN (up to 10 kilometers in rural areas) ensures that traps placed in remote locations can reliably communicate with the network.
- **Cost-Effectiveness**: LoRaWAN technology is cost-effective, both in terms of deployment and operation, making it suitable for widespread use across various locations.
- **Scalability**: LoRaWAN networks can be easily scaled, allowing for the addition of more traps and other IoT devices without significant changes to the infrastructure.
- **Robustness**: The LoRaWAN protocol is robust and can handle the environmental challenges typically encountered in outdoor and rural settings where the traps will be placed.

## Chapter 2: LoRaWAN Provider Comparison

### 2.1 Context for Provider Choice
For the described use case, two different LoRa networks are considered: The Things Network (TTN) and KPN LoRa. These two networks are built on LoRaWAN technology. Both TTN and KPN Things are facilitated by commercial parties. The use case for the muskrat trap requires the traps to be placed in various locations across the Netherlands, mainly in rural areas along dikes. To minimize animal suffering, it's important that the trap sends a signal when a muskrat is caught so that the animal can be released alive from the trap. Once a signal is received by the water boards, a nature manager can release the muskrat from the trap. Quicker release means less suffering for the animal. The trap should ideally send a signal immediately when it is closed and life is detected. Since the traps are placed in rural areas, a good range of the chosen LPWAN technology is crucial. Additionally, it should be possible to expand the network if the signal coverage is insufficient.

### 2.2 KPN LoRa
KPN, a commercial Dutch BV, facilitates the KPN Things network. KPN does not share information about the use of its LoRa network on its websites. KPN was asked to clarify the costs of using the KPN Things network but did not respond. KPN offers the possibility to place an additional gateway if the range for end devices is insufficient. KPN also offers location determination through the LoRa network, advertising a precision of 50 to 100 meters. Researchers estimate the precision of KPN's location determination at 174 meters.

### 2.3 The Things Network (TTN)
The Things Industries offers free use of the TTN network and commercial support on a network server with a service level agreement (SLA) if needed. To connect more than 10 devices and 10 gateways to TTN, a subscription is required. The business model of The Things Industries is clear and fair. According to ttnmapper.org, TTN seems to have slightly less coverage than KPN Things. However, the methodology for determining coverage is not published by KPN, making a correct comparison difficult. Users can place a new antenna if the signal proves inadequate in practice. This allows TTN network users to expand the network coverage as needed.

### 2.4 Conclusion: LoRaWAN Provider Choice
The muskrat trap must operate on a battery that needs minimal replacement. Considering the energy consumption of the different LPWAN technologies, LoRaWAN is the most logical choice for the communication network. LoRaWAN's greater range also makes it better suited than NB-IoT or LTE-CAT-M.

KPN advertises location determination for its LoRa network, but it is not precise enough for the use case. To minimize animal suffering, locating a caught muskrat trap should not take hours within a radius of over 300 meters. TTN has more online documentation available than KPN, making TTN a better choice for a study project.

**Why Choose The Things Network over KPN LoRa?**
- **Cost Transparency**: TTN provides clear and transparent pricing models. In contrast, KPN did not respond to requests for cost clarification, making budgeting and planning more challenging.
- **Community Support and Documentation**: TTN has extensive online documentation and community support, making it easier for developers and users to find solutions and best practices. This is particularly beneficial for a study project where access to resources and community knowledge is crucial.
- **Flexibility and Control**: TTN allows users to place new antennas to extend network coverage as needed. This flexibility ensures that users can adapt the network to their specific requirements without relying on a single provider's infrastructure.
- **Open-Source Nature**: TTN's open-source nature encourages innovation and customization, allowing for more tailored solutions to specific use cases. This is advantageous for developing a unique product like the SMARTrap.
- **Scalability**: TTN's scalable model allows for easy addition of devices and gateways, which is ideal for expanding the muskrat trap network across various locations in the Netherlands.

## Chapter 3: Muskrat Trap Design Considerations

The SMARTrap is a sophisticated muskrat trap designed to ensure efficient and humane monitoring and control of muskrat populations. It incorporates various sensors and IoT functionalities to provide real-time status updates and enhance the overall trapping process.

### 3.1 Sensor Integration
1.  **Magnetic Sensor on the Door**: The trap is equipped with a magnetic sensor placed on the door. This sensor detects whether the door is open or closed. When the door is closed, the sensor triggers a signal indicating that the trap is set and ready to capture a muskrat.
2.  **Weight Sensor on the Bottom**: To detect the presence of an animal inside the trap, a weight sensor is installed on the bottom. This sensor acts like a button that gets pressed when an animal's weight is detected. Once the weight sensor is triggered, it indicates that an animal is inside the trap.
3.  **Movement Detection Sensor**: A wire-based sensor is used to detect if the trap has been moved from its original position. If the wire is broken, it signifies that the trap has been displaced, and a signal is sent to notify the change in position.

### 3.2 Signal Transmission
-   **Animal Captured Signal**: If both the door is closed and the weight sensor detects an animal inside the trap, a signal is sent to the server application. This ensures that the muskrat manager is immediately informed about the capture, allowing for prompt action to release the animal humanely.
-   **Trap Movement Signal**: If the movement detection sensor indicates that the trap has been moved (wire broken), a signal is sent to alert the managers. This feature helps in preventing theft or unauthorized relocation of the trap.

### 3.3 Housekeeping and Maintenance
-   **Battery Status Monitoring**: To ensure the trap remains operational, the status of the battery is continuously monitored and transmitted. This data helps in timely maintenance, ensuring the trap does not run out of power and remains functional over extended periods.

### 3.4 Summary of Design
The SMARTrap's design integrates multiple sensors to provide comprehensive monitoring and control. The magnetic sensor, weight sensor, and movement detection sensor work together to ensure real-time updates on the trap's status. Additionally, battery status monitoring ensures the trap's reliability and longevity, making it an effective tool for humane muskrat management.
