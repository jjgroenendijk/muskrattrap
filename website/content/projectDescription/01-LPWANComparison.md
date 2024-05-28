---
weight: 2
title: "LPWAN Comparison"
---

# LPWAN Comparison

## Communication Network for Smart Traps
To make a muskrat trap smart, it needs network communication.
Since the trap can be placed in remote locations, it's essential to maximize battery life. Energy efficiency is crucial.
The trap doesn't need high-speed communication but must have a good range.
Several existing LPWAN technologies were considered for the muskrat trap, namely LoRaWAN, NB-IoT, and LTE-CAT-M.

### LoRaWAN
LoRaWAN, which stands for Long Range Wide Area Network, is a communication network optimized for energy-efficient
long-distance communication.
The development of LoRa started in 2009 when two friends in France wanted to develop long-distance communication
technology with low power consumption.
Nicolas Sornin and Olivier Seller, the inventors of LoRa, met their third partner, François Sforza, in 2010.
The three developers founded Cycleo in 2010.
They began developing for the metering industry, adding wireless communication capabilities to gas, water, and electricity meters using Chirp Spread Spectrum (CSS) modulation technology.

In 2012, Cycleo was acquired by SemTech, who collaborated with the founders to improve the technology and develop the
necessary chips for end devices and gateways.
At the same time, a proprietary MAC protocol called "LoRaMAC" was created and later renamed "LoRaWAN".
In 2015, the LoRa Alliance was established to support and promote the global adoption of the LoRaWAN standard.
The ongoing development of the LoRaWAN protocol is managed by the open and non-profit organization LoRa Alliance, with SemTech as one of its founding members.

LoRa offers a range of 3 kilometers in urban areas and up to 10 kilometers in rural areas. This extensive range is achieved with energy consumption that is 3 to 5 times lower than other LPWAN technologies. The available bandwidth provided by LoRa varies between 290 bps and 50 kbps.

### NB-IoT
Narrowband Internet of Things (NB-IoT) is also a communication network optimized for low energy consumption and long distances. The main technical difference from LoRaWAN is that NB-IoT uses existing LTE networks. NB-IoT operates within the license of 2G/3G/4G, so existing network operators do not need additional licenses. NB-IoT focuses on indoor coverage, low cost, long battery life, and high connection density. It uses a subset of the LTE standard but limits the used frequencies to 180 kHz and 200 kHz (Grant Svetlana, 2016). The GmSA reported in 2019 that 101 network operators worldwide support the NB-IoT network, and 153 operators are investing in NB-IoT technology.

### LTE-CAT-M
LTE-CAT-M, also known as LTE-MTC, is a type of radio technology for IoT and machine-to-machine communication.
It offers benefits such as higher speed and mobility but is more expensive and requires more bandwidth than NB-IoT.
In March 2019, the Global Mobile Suppliers Association reported that more than 100 operators had deployed/launched NB-IoT or LTE-M networks.
LTE-CAT-M has some advantages over NB-IoT, such as the ability to achieve speeds up to 1 Mbps.
In the IoT world, this is a very high speed. LTE-CAT-M also supports voice data transmission and works with moving
devices.
However, LTE-CAT-M has higher power consumption and higher hardware costs compared to LoRaWAN and NB-IoT.

## Conclusion
LoRaWAN is the network of choice for the Muskrat trap for the following reasons:
- **Energy Efficiency**: LoRaWAN is highly energy-efficient, making it ideal for battery-powered devices like the muskrat trap that need to operate for extended periods without frequent battery replacements.
- **Long Range**: The extensive range of LoRaWAN (up to 10 kilometers in rural areas) ensures that traps placed in remote locations can reliably communicate with the network.
- **Cost-Effectiveness**: LoRaWAN technology is cost-effective, both in terms of deployment and operation, making it suitable for widespread use across various locations.
- **Scalability**: LoRaWAN networks can be easily scaled, allowing for the addition of more traps and other IoT devices without significant changes to the infrastructure.
- **Robustness**: The LoRaWAN protocol is robust and can handle the environmental challenges typically encountered in
  outdoor and rural settings where the traps will be placed.