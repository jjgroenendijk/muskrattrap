---
weight: 3
title: "LoRaWAN Comparison"
---

# LoRaWAN Comparison
For the described use case, two different LoRa networks are considered: The Things Network (TTN) and KPN LoRa.
These two networks are built on LoRaWAN technology.
Both TTN and KPN Things are facilitated by commercial parties.
The use case for the muskrat trap requires the traps to be placed in various locations across the Netherlands, mainly in
rural areas along dikes.
To minimize animal suffering, it's important that the trap sends a signal when a muskrat is caught so that the animal
can be released alive from the trap.
Once a signal is received by the water boards, a nature manager can release the muskrat from the trap.
Quicker release means less suffering for the animal.
The trap should ideally send a signal immediately when it is closed and life is detected.
Since the traps are placed in rural areas, a good range of the chosen LPWAN technology is crucial.
Additionally, it should be possible to expand the network if the signal coverage is insufficient.

## KPN LoRa
KPN, a commercial Dutch BV, facilitates the KPN Things network.
KPN does not share information about the use of its LoRa network on its websites.
KPN was asked to clarify the costs of using the KPN Things network but did not respond.
KPN offers the possibility to place an additional gateway if the range for end devices is insufficient.
KPN also offers location determination through the LoRa network, advertising a precision of 50 to 100 meters.
Researchers estimate the precision of KPN's location determination at 174 meters.

## The Things Network (TTN)
The Things Industries offers free use of the TTN network and commercial support on a network server with a service level
agreement (SLA) if needed.
To connect more than 10 devices and 10 gateways to TTN, a subscription is required.
The business model of The Things Industries is clear and fair.
According to ttnmapper.org, TTN seems to have slightly less coverage than KPN Things.
However, the methodology for determining coverage is not published by KPN, making a correct comparison difficult.
Users can place a new antenna if the signal proves inadequate in practice.
This allows TTN network users to expand the network coverage as needed.

## Conclusion
The muskrat trap must operate on a battery that needs minimal replacement.
Considering the energy consumption of the different LPWAN technologies, LoRaWAN is the most logical choice for the
communication network.
LoRaWAN's greater range also makes it better suited than NB-IoT or LTE-CAT-M.
KPN advertises location determination for its LoRa network, but it is not precise enough for the use case.
To minimize animal suffering, locating a caught muskrat trap should not take hours within a radius of over 300 meters.
TTN has more online documentation available than KPN, making TTN a better choice for a study project.

**Why Choose The Things Network over KPN LoRa?**
- **Cost Transparency**: TTN provides clear and transparent pricing models. In contrast, KPN did not respond to requests for cost clarification, making budgeting and planning more challenging.
- **Community Support and Documentation**: TTN has extensive online documentation and community support, making it easier for developers and users to find solutions and best practices. This is particularly beneficial for a study project where access to resources and community knowledge is crucial.
- **Flexibility and Control**: TTN allows users to place new antennas to extend network coverage as needed. This flexibility ensures that users can adapt the network to their specific requirements without relying on a single provider's infrastructure.
- **Open-Source Nature**: TTN's open-source nature encourages innovation and customization, allowing for more tailored solutions to specific use cases. This is advantageous for developing a unique product like the SMARTrap.
- **Scalability**: TTN's scalable model allows for easy addition of devices and gateways, which is ideal for expanding the muskrat trap network across various locations in the Netherlands.
