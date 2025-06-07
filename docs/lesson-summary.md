# A Comprehensive Guide to the Internet of Things: From Theory to Practice

## Part 1: Introduction to the Internet of Things

### Introduction to the Internet of Things (IoT)

The Internet of Things (IoT) refers to the idea of connecting all sorts of devices to the internet to measure, perceive, and even manipulate their environments, to such an extent that we could go crazy with all of the possibilities that could arise. Examples of IoT devices include smart devices such as smart desks, smart walls, smart rooms, smart chairs, Philips Hue lights, and Nest thermostats. Additionally, mobile technology like smartphones, and wearable tech such as smartwatches and fitness trackers, fall under the definition of IoT devices.

This guide, based on a 14-week course, will cover the Internet of Things (IoT), microcontrollers, and LoRaWAN, exploring the entire chain of activities from sensing and data collection to presentation and interpretation. The content is structured to be engaging and practical, with a focus on hands-on activities and real-world use cases. The learning that takes place is what students put in, in terms of active involvement, which takes the form of questions and discussions around a variety of different topics.

The course is structured with a "flip-classroom" orientation. Students are expected to study the theory, watch videos, and complete programming exercises beforehand. In class, theory is briefly reviewed, questions are answered, and students work on assignments with hands-on activities. To meet the course objectives, students will be introduced to the LoRaWAN ecosystem and IoT system development, using LoRaWAN as a modern, secure-by-design vehicle for these technologies.

### The Promise and Perils of a Connected World

#### Advantages of IoT

Some of the advantages of the Internet of Things (IoT) include: convenience and time-saving, increased comfort, improvements to e-health, greater efficiency, and energy savings. For example, smart homes use IoT to control lights and temperature.

Another example is an IoT mouse trap sensor that could result in less death as a consequence. With a 15 to 20 Euro sensor, the trap can be monitored from the comfort of your home to avoid coming face-to-face with something traumatic.

In an industrial setting, IoT can be implemented for flood or tide information. In England, the Flood Network, a community project, uses a mesh network to measure rain high up in the hills. A short alert is sent to warn if floods are about to come or are already in effect. This saves lives and provides relevant data for researchers. Good IoT solutions can genuinely help people.

#### Disadvantages, Pitfalls, and Ethical Considerations

While we can design many cool IoT products, the question is what are the real consequences? IoT devices have significant security and privacy implications.

IoT presents several challenges, including centralization by large companies, such as Google's Nest Labs, which can lead to a lack of transparency regarding who has access to user data, making long-term predictions difficult. A key concern is the lack of informed consent about how personal data is used. Trust issues can arise, especially if there is no open and honest relationship with data collectors. The omnipresence of data through storage, exchange, and processing can lead to invisibility, making it difficult for users to understand what happens with their information.

The balance between surveillance and privacy is a critical issue, as constant monitoring can infringe upon personal privacy. Data protection becomes paramount due to continuous tracking and the monitoring of sensitive information. Personalized marketing through IoT can also become invasive. A "black box" situation exists where companies possess detailed knowledge that remains inaccessible to consumers or end-users. The ability to "opt-out" of certain services and maintain choices decreases, limiting personal autonomy.

A few years ago, many people's fitness trackers were reporting activity tracks in dark areas of Afghanistan. It turned out this reported location was a secret intelligence headquarters. This highlights that devices and the technology they are built upon are not without risk and are capable of being used in problematic ways. Nest thermostats, for instance, learn your schedule and can predict when you'll be home. While this is a benefit, most people are unaware that Google, Apple, and Facebook make money off the data collected from our devices.

Vulnerabilities exist if IoT devices are remotely controlled through smartphone apps, since these could potentially be stolen or hacked. An example of a potential privacy issue is a children's listening device, marketed as "A Message You Can Hug," which acknowledges in its warning that the child's private voice recordings may be stored in an unsecured Amazon S3 bucket and a MongoDB database without password protection, making them publicly accessible.

## Part 2: Core Technologies and Protocols

### Wireless Communication for IoT

There are many data transport options with many wireless protocol options. These can be categorized as wired or wireless. It is critical that the end user understands the risks involved with any choice.

#### An Overview of Wireless Protocols

There are several wireless technologies for data transport, including WiFi, Bluetooth (BLE), Zigbee, Sigfox, LoRaWAN, NB-IoT, and LTE-Cat-M.

*   **Bluetooth (BLE)** is suitable for short-range communication.
*   **Zigbee** is also a short-range technology, often used in solar panels for data transport from the solar panels and equalizers.
*   **Sigfox** is a LoRaWAN technology of French origin. While it still exists, its future is uncertain.
*   **LoRaWAN** has become very popular in recent years for smaller networks.
*   **Narrowband IoT (NB-IoT)** is a technology well-suited for roaming and is also particularly good at penetrating buildings.
*   **LTE Cat-M** has some difficulties with roaming outside of the Netherlands.

A historical comparison between 2G and 4G networks is relevant. For transmitting data, 2G networks had speeds limited to 9600 baud, which was insufficient for many data applications. This was addressed with GPRS, allowing speeds up to 56kbps. However, 2G networks are advantageous in terms of battery life. 2G devices can go into a deep sleep mode and only listen to the network at specific intervals, consuming less power. 4G networks don't allow for this same level of power conservation, as they are IP-oriented and lack the synchronous structure of 2G.

Poorly designed electronics can result in "noise" which can interfere with radio signals, an issue known as electromagnetic compatibility (EMC). A device has poor EMC if it malfunctions when a phone call is made nearby. Conversely, a sender with poor EMC might distort radio signals. Well-designed equipment avoids these issues.

#### Low Power Wide Area Networks (LPWAN)

Low Power Wide Area Networks, or LPWANs, are wireless networks designed for long-range communications, typically kilometers up to tens of kilometers, at low bit rates. They often use sensors operated on a battery, with a battery life of around 5 to 10 years. LPWAN data rates range from $0.3$ kbit/s to $50$ kbit/s per channel.

There is no single wireless technology that is optimal for every use case. Important factors to consider include:

*   **Link Budget:** Calculated using the sent power and the receiver sensitivity. The larger the link budget, the larger the possible range.
*   **Interference Immunity:** In unlicensed frequency bands, other devices will cause interference. Licensed frequencies require you to purchase a frequency to use, but you have dedicated signal strength. LoRaWAN has a very high interference immunity, while narrowband IoT has a low interference immunity.
*   **Battery Lifetime:** LoRaWAN and Sigfox, which both use unlicensed spectrum, offer the longest battery lifespans.

#### Deep Dive into LoRaWAN

LoRaWAN is a standard managed by the LoRa Alliance. It is secure by design, making it a valuable subject for study. Students will use a LoRaWAN node and connect through The Things Network, a community-driven network. A gateway for this network will also be supplied and can be installed at home, connected to WiFi, thus extending the network's coverage.

A key aspect of LoRaWAN is that it pushes the boundaries of what is possible in terms of low power consumption and payload size. The challenge in IoT is to make devices energy-efficient, such that batteries last for several years. This has direct consequences for the data that can be sent and the range of those transmissions.

##### The LoRaWAN Standard and LoRa Modulation

LoRa, which stands for "Long Range," is a specific type of modulation technique developed by Cycleo in 2012 and acquired by Semtech. The LoRa modulation is based on Chirp Spread Spectrum (CSS), which has some analogies to frequency modulation (FM). Chirp stands for "Compressed High Intensity Radar Pulse." LoRa modulation uses 'chirping', meaning the signal has a "wibble" or sweep in frequency. This makes it more robust against signal interference, increasing its signal-to-noise ratio (SNR) and enabling better detection.

LoRa modulation involves a phase shift or "sweep step" representing 8 bits of data. Unlike FSK, it doesn't simply transmit 1s and 0s; instead, each sweep step represents 8 bits. The moment this phase shift happens determines the value encoded. If the sweep step happens later in the sweep, the represented number is higher than if it happens earlier.

##### Spreading Factors, Data Rates, and Range

LoRa offers multiple spreading factors, ranging from 7 to 12. Spreading factor selection represents a tradeoff of data rate versus range.

*   A smaller spreading factor (like SF7) results in shorter sweep periods, enabling faster data transmission but with a smaller range.
*   A larger spreading factor (like SF12) leads to longer sweep periods, a slower data rate, but a greater range. The slow sweeps with a spreading factor of 12 are also easier to detect.

##### ISM Bands and Duty Cycles

LoRa makes use of ISM (Industrial, Scientific, and Medical) bands. These are unlicensed frequency bands, but not unregulated. There are power limits, and one must either use 'Listen Before Talk' (LBT) to avoid interfering with other transmissions or comply with a duty cycle restriction. The duty cycle limits the percentage of time transmission can occur within a given period. For example, in one frequency band (868.700-869.200 MHz), there may be a duty cycle of less than 0.1%. The Rijksinspectie for Digital Infrastructure is the governmental body in the Netherlands responsible for enforcing these regulations.

##### Device Classes (A, B, C)

LoRaWAN devices are categorized into classes A, B, and C. As a standard, all nodes must implement Class A.

*   **Class A:** The most energy-efficient class. The node is mostly in deep sleep mode and only transmits when it has data to share. After sending, the network can communicate back to the node for a short period. For The Things Network, after a packet is sent, the node listens for a downlink packet on the same frequency after 5 seconds. If nothing is received, it listens again a second later on a specific frequency ($869.525$ MHz) with a spreading factor of 9 before returning to sleep.
*   **Class B:** Utilizes beacons for synchronized time slots, allowing communication between the node and the network at predetermined times. It offers shorter latency for downlink messages than Class A.
*   **Class C:** Devices are not battery-powered; they use a permanent power supply. These nodes can continuously listen for downlink messages, resulting in very low latency. An example is a pump in a field that needs continuous control.

##### Network Architecture and Operators

LoRaWAN uses a star-of-stars network architecture. Sensors connect to gateways, and the gateways connect to a core network server. The core network server then connects to the application. Data received by more than one gateway is de-duplicated by the core network server.

There are many LoRaWAN network operators worldwide. Prominent networks in the Netherlands include KPN, The Things Network, and Helium.

*   **The Things Network (TTN):** A global collaborative IoT ecosystem where people create networks, devices, and solutions using LoRaWAN. It's a community-driven network and is free for small-scale projects under a "fair use policy," which typically allows 30 seconds of airtime and 10 downlink messages per day per device.
*   **KPN:** A commercial service with national coverage in the Netherlands, costing around 50 Euro per year per device.
*   **ChirpStack:** An open-source LoRaWAN Network Server (LNS) stack. It doesn't offer coverage on its own; users must set up their own servers and gateways. This provides complete control and independence.

### Application Layer Protocols

#### MQTT: The Publish-Subscribe Protocol for IoT

MQTT (Message Queuing Telemetry Transport) is a simple and easy-to-use protocol developed in 1999. It is based on a publish-subscribe messaging protocol built on top of the TCP/IP protocol suite. Its goals were to create a protocol with a small code footprint and limited bandwidth, making it suitable for IoT solutions. MQTT is message-oriented; every message is a discrete chunk of data, opaque to the broker.

##### Core Concepts: Broker, Clients, and Topics

MQTT's architecture centers around clients and a broker. Sensors act as clients, publishing data (e.g., a temperature reading) to the MQTT broker. Other clients can subscribe to these topics to receive the published data.

A topic consists of one or more topic levels, separated by a forward slash (`/`), for example, `myhome/groundfloor/livingroom/temperature`. Topics are case-sensitive.

MQTT offers wildcards to subscribe to multiple topics:
*   **Single-level wildcard (`+`):** Replaces a single topic level. `myhome/groundfloor/+/temperature` would match temperatures in the `livingroom` and `kitchen`.
*   **Multi-level wildcard (`#`):** Replaces multiple topic levels at the end of a topic. `myhome/groundfloor/#` would match all topics under `groundfloor`.

Best practices for MQTT topics include:
*   Don't begin a topic with a forward slash.
*   Don't use spaces in a topic.
*   Keep topics short and concise.
*   Embed a unique identifier or Client ID in the topic.
*   Avoid subscribing to `#` on a public broker, as you will receive everything.

##### Practical Usage with Mosquitto and MQTT-spy

Mosquitto is a popular open-source MQTT broker. You can use command-line tools to interact with it:
*   **Subscribe:** `mosquitto_sub -d -h test.mosquitto.org -t ESEIot/#`
*   **Publish:** `mosquitto_pub -h test.mosquitto.org -t ESEIot/test/ -m "Hello world"`

MQTT-spy is a graphical Java application for sending and receiving MQTT messages. It can format JSON payloads for better readability.

#### HTTP and REST APIs

HTTP (Hypertext Transfer Protocol), particularly through REST APIs, is another way to exchange data. A REST (Representational State Transfer) API communicates between a client and a server through requests and responses.

##### Core Concepts: GET, POST, and other Methods

Commonly used methods within HTTP-based REST APIs are:
*   **`GET`:** Used to obtain or retrieve information.
*   **`POST`:** Used to send or create new information, typically in the request body (e.g., as a JSON structure).
*   **`PUT`:** Used to create or replace the state of a target resource.
*   **`DELETE`:** Used to delete a target resource.

##### Working with APIs using Postman

Postman is a tool that simplifies working with APIs. It allows you to prepare and send various HTTP requests (GET, POST, etc.) and view the server's response, which is often in JSON format. For example, a GET request to Bitvavo's market API might yield a JSON response like `{"market": "INCH-EUR", "status": "trading", ... }`. Postman is excellent for testing and debugging API interactions.

##### Finding and Using Open Data APIs

Many organizations provide open data via REST APIs, often requiring an API key for access.
*   **OpenWeatherMap:** Provides global weather data, forecasts, and historical data.
*   **Bitvavo:** Provides real-time market data for cryptocurrency trading.
*   **Nationale Data Openbaar Vervoer (NDOV):** Delivers timetables and current data for public transport in the Netherlands.
*   **data.overheid.nl:** The Dutch government's open data portal.

To get weather data from OpenWeatherMap, you can use an API call for current weather by city ID. To get the temperature in degrees Celsius, you can add `&units=metric` to the API call.

## Part 3: Building an IoT Solution

### The IoT Node: Hardware and Software

#### Microcontrollers and Development Environments

The course involves work with embedded systems and microcontrollers. Basic expertise in C programming, microcontrollers, and versioning (git) is expected.

Arduino sketches, while based on C/C++, have a slightly different structure. They use `setup()` and `loop()` functions instead of a traditional `main()` function. The `setup()` function runs once at the beginning, and the `loop()` function executes repeatedly.

Function prototypes are not explicitly declared in the sketch itself because the Arduino environment automatically generates them before compiling the code. The Arduino `main.cpp` file, located in the core files of the IDE, contains the actual `main()` function which calls `setup()` once and then calls `loop()` in an infinite loop.

### Handling Data: Payloads and Encoding

#### The Importance of Efficient Payloads

In LoRaWAN, it's important to minimize data usage because there is a limited payload size (max 51 bytes for some data rates) and airtime (Fair Use Policy). Smart payload encoding allows for sending more messages per day or extending battery life.

For example, a JSON structure like `"Count": 1234, "Temperature": 20.635` can be 40 bytes. By removing the counter, shortening the key to `t`, and removing JSON overhead, the payload can be reduced to just a few bytes. Representing `20.63` as a 16-bit signed integer (by multiplying by 100 to get `2063`) reduces the payload to just 2 bytes.

#### Data Formats: JSON and Binary Encoding

JSON (JavaScript Object Notation) is a human-readable format for structuring data. It uses key-value pairs, where keys are strings in double quotes and values can be strings, numbers, booleans, arrays, or other objects.

```json
{
  "givenName": "Remko",
  "age": 54,
  "grades": [5.5, 7.0, 9.1]
}
```

While readable, JSON has significant overhead. For constrained devices, binary encoding is far more efficient. This involves representing data at the bit and byte level.

Data received from The Things Network via MQTT is often packaged in a JSON structure. This includes metadata and the payload. The raw byte array of the payload within this JSON is often Base64 encoded. Base64 is used to represent binary data in an ASCII string format, preventing control characters from interfering with communication channels. To use the raw data, it must be decoded from Base64 back into a byte array.

#### Designing a Custom Payload

Creating a custom payload involves answering key questions:
*   What data types are the values (e.g., `uint8_t`, `float`)?
*   How many bytes are needed to carry this information?
*   What math is needed to fit the data into the allocated bytes?

For example, to send a float like `65.786`, you might multiply it by 100 to get `6578.6`, round it to `6579`, and then send it as a 16-bit integer (`uint16_t`). The receiving end would then divide by 100 to reconstruct the float. This sacrifices some precision for a much smaller payload.

Bit-shifting is a crucial technique for manipulating byte arrays. The bitwise operators are: `&` (AND), `|` (OR), `^` (XOR), `~` (NOT), `>>` (right shift), and `<<` (left shift).

#### C/C++ for Payload Encoding and Decoding

To encode a 16-bit unsigned integer (`uint16_t`) into a 2-byte array in C++:

```cpp
// value is a uint16_t, buffer is a byte array, idx is the starting index
// Store the Most Significant Byte (MSB)
buffer[idx++] = (value >> 8) & 0xFF;
// Store the Least Significant Byte (LSB)
buffer[idx++] = value & 0xFF;
```

To decode it back:

```cpp
// buffer is a byte array, idx is the starting index
uint16_t value = 0;
// Reconstruct the value from MSB and LSB
value = (uint16_t)buffer[idx] << 8;
value = value | buffer[idx + 1];
```

It is best practice to develop and unit test these encoder/decoder classes in a standard C++ environment (like Qt or VS Code) where debugging is easier, before deploying them to the constrained Arduino environment.

#### JavaScript for Payload Decoding in The Things Network

The Things Network uses a JavaScript function to decode uplink payloads. You define a function `decodeUplink` that takes an `input` object.

```javascript
function decodeUplink(input) {
  // input.bytes is an array of bytes from the payload
  // input.fPort is the frame port
  var data = {}; // Create an empty object to hold the decoded data
  var warnings = []; // Create an empty array for warnings

  // Example: Decode a 16-bit battery value from the first two bytes
  data.battery = (input.bytes[0] << 8) | input.bytes[1];
  
  // Example: Decode temperature (signed 16-bit, scaled by 100)
  var temp = (input.bytes[2] << 8) | input.bytes[3];
  // Handle signed value
  if (temp & 0x8000) {
    temp = temp - 0x10000;
  }
  data.temperature = temp / 100.0;

  if (data.temperature < -10) {
    warnings.push("it's cold");
  }

  return {
    data: data,
    warnings: warnings
  };
}
```

It's important to keep the decoder simple (KISS - Keep It Stupid Simple).

#### The Cayenne Low Power Payload (LPP) Format

Cayenne LPP is a standard helpful for rapid prototyping. It uses an implicit schema where each data point is prefixed with a channel number and a data type identifier. This allows for easy integration but is less efficient than a custom binary payload.

For example, a payload of `03, 67, 01, 10` would be decoded as:
*   Channel `03`
*   Type `67` (Temperature)
*   Value `0110` (hex) = `272` (decimal). The standard dictates dividing by 10, so the temperature is `27.2`°C.

### The Back-End: Processing, Storage, and Visualization

#### Introduction to Node-RED

Node-RED is a visual programming tool built on Node.js, a JavaScript runtime environment. It is used for wiring together hardware devices, APIs, and online services.

##### Core Concepts: Flows, Nodes, and the Editor

Node-RED provides a browser-based editor to create "flows" by connecting "nodes" using a drag-and-drop interface. Each node performs a specific task.
*   **Inject Node:** Manually or periodically injects a message into a flow.
*   **Debug Node:** Displays messages in the debug sidebar.
*   **Function Node:** Allows writing custom JavaScript code to process messages.
*   **MQTT Node:** Subscribes to or publishes to MQTT topics.

All information within Node-RED is passed as a message object, which typically has a `msg.payload` property containing the data.

Node-RED also features a dashboard UI, accessible at `<host_ip>:1880/ui`, for creating simple user interfaces with gauges, charts, and buttons. You can also store data in variables scoped to the flow or globally, known as "context."

#### Containerization with Docker

Containerization, using tools like Docker, offers a simplified way to package and run applications. It involves segmenting an operating system to isolate libraries and functionalities, creating 'containers' that encapsulate everything an application needs to run. This allows for consistent deployment across different environments and simplifies version management. For example, you can have a container for Node-RED, one for a database like MySQL, and one for a web server, all running isolated on the same host.

#### Database Fundamentals

##### Introduction to Databases and SQL

A database's function is to collect, organize, and link data. A Database Management System (DBMS), like MySQL or PostgreSQL, is the software used to manage the database. SQL (Structured Query Language) is the standard language used to interact with relational databases.

SQL commands include:
*   `SELECT`: To retrieve data.
*   `INSERT`: To add new data.
*   `UPDATE`: To modify existing data.
*   `DELETE`: To remove data.

##### Database Design and Normalization

The initial step in designing a database is identifying what information to store, its name, and its data type (e.g., `datetime`, `text`, `float`, `int`). This can be documented with a UML class diagram.

A **primary key** is a column (or set of columns) that uniquely identifies each row in a table. A common approach is to use an auto-incrementing integer ID.

**Normalization** is the process of organizing columns and tables to minimize data redundancy.
*   **First Normal Form (1NF):** Data is in a table, rows are unique (via a primary key), and there are no repeating groups of columns.
*   **Second Normal Form (2NF):** Is in 1NF, and all non-key attributes are fully functionally dependent on the primary key.
*   **Third Normal Form (3NF):** Is in 2NF, and all attributes are dependent only on the primary key (no transitive dependencies).

The initial goal should be to at least achieve 1NF.

##### Practical Database Management with phpMyAdmin

A LAMP (Linux, Apache, MySQL/MariaDB, PHP) server can be installed on a Raspberry Pi for web development and database management. phpMyAdmin is a web-based interface that simplifies the management of MySQL databases, allowing you to create databases, design tables, and run SQL queries through a graphical interface.

#### Integrating Node-RED with Databases

Node-RED can interact directly with a MySQL database by installing the `node-red-node-mysql` module. This provides a MySQL node that can execute queries.

To insert data, a **Template node** is used to construct the SQL `INSERT` statement. The Template node uses Mustache formatting, which replaces placeholders like `{{payload.temperature}}` with values from the incoming message object.

A typical flow would be:
`MQTT In Node` -> `Function Node (to parse/prepare data)` -> `Template Node (to build SQL query)` -> `MySQL Node (to execute query)`

#### Data Visualization with Grafana

Grafana is a powerful open-source platform for monitoring and data visualization. It connects to various data sources, including MySQL, and allows you to create complex and interactive dashboards.

You can build queries in Grafana to pull specific data from your database. For example, to get the latest weight measurement from a `Devices` table:

```sql
SELECT weightKg 
FROM beehive.Devices 
WHERE date(received_at) = DATE(CURRENT_TIMESTAMP) 
ORDER BY received_at DESC 
LIMIT 1;
```

Grafana is excellent for creating time-series graphs to display sensor data like temperature, light levels, or battery voltage over time, allowing for the identification of trends and events.

## Part 4: Software Engineering for IoT

### Development Methodologies

#### The V-Model: Verification and Validation

The V-model is a structured software development approach where testing activities are planned in parallel with development phases.
*   **Verification:** "Are we building the product right?" (i.e., does it meet specifications?).
*   **Validation:** "Are we building the right product?" (i.e., does it meet user needs?).

The model pairs development stages (requirements, design, coding) with corresponding testing stages (acceptance testing, system testing, integration testing, unit testing).

### Testing and Quality Assurance

#### The Role of Unit Testing

Unit testing involves testing small, individual parts (units or functions) of a program in isolation. Good unit tests act as documentation, help fix bugs early, save costs, and give developers confidence to make changes. Finding and fixing a bug early in the development cycle is significantly cheaper than fixing it after deployment.

#### Testing Methodologies: Whitebox vs. Blackbox

*   **Whitebox Testing:** The tester knows the internal workings of the code and writes tests to cover specific paths and logic.
*   **Blackbox Testing:** The tester knows nothing about the internal code and tests the functionality by providing valid and invalid inputs to see if the output is correct. This includes boundary testing, where values at the edges of valid ranges are tested.

### Documentation

#### Documenting Code with Doxygen

Doxygen is a tool for generating software reference documentation directly from comments in the source code. It supports many languages, including C++.

Documentation is written in special comment blocks, called "Doxyblocks," using tags like `\file`, `\brief`, `\param`, and `\return`.

```cpp
/// \file pelmew_rotorsteering.h
/// \brief Steering class for PE1MEW Arduino Rotor Controller
/// \date 20-7-2016
/// \author Remko Welling (PE1MEW)

/// \brief Get next step for future calls.
/// \param actualStep at the time the function getSignal() was called.
/// \return incremented step.
unsigned int getStep(unsigned int actualStep) const;
```

Doxygen can generate documentation in various formats like HTML and can also create diagrams (e.g., class diagrams) if integrated with a tool like Graphviz.

### Tools and Techniques

#### Version Control with Git

Students are expected to be familiar with version control using Git. A portfolio assignment will require a Git repository at GitLab.

#### AI-Assisted Coding with ChatGPT

Tools like ChatGPT can assist with code generation, but issues may arise. It is useful for inspiration, but it's important to ensure the generated code meets required coding styles (indentation, no magic numbers) and that the overall architecture is sound. An AI tool cannot figure out the architecture on its own; that requires the thoughtfulness of a software engineer.

#### Cross-Platform Development with Cygwin

Cygwin is a tool that provides a Linux-like environment on Windows, making it POSIX-compliant. This allows you to write an application that can be compiled and run on both Windows and Linux without changes to the source code, which is useful when working with tools like Makefiles.

## Part 5: Security and Privacy

### Securing IoT Communications

#### Fundamentals of Encryption

Encryption is crucial to safeguard information transmitted over IoT networks.
*   **Plaintext:** The original, readable message.
*   **Ciphertext:** The encrypted, unreadable message.
*   **Cipher:** The algorithm used to transform plaintext to ciphertext.

LoRaWAN uses AES-128 symmetric encryption by design.

#### Symmetric vs. Asymmetric Encryption

*   **Symmetric Encryption:** Uses the same key for both encryption and decryption. It is fast but requires a secure way to share the key. Examples include the Caesar cipher and AES (Advanced Encryption Standard).
*   **Asymmetric Encryption:** Uses a key pair: a public key (shared with everyone) and a private key (kept secret). A message encrypted with the public key can only be decrypted with the corresponding private key. It is slower but solves the key distribution problem. An example is the Diffie-Hellman key exchange.

#### Secure Shell (SSH) and Key Exchange

SSH is a protocol used to securely connect to a remote computer. When connecting for the first time, the server presents a "fingerprint," which is a hash of its public key. This allows the client to verify the server's identity in subsequent connections to prevent man-in-the-middle attacks. The SSH negotiation process uses the Diffie-Hellman key exchange to securely agree upon a shared symmetric key for the session.

#### Hashing for Data Integrity

Hashing is a one-way process that maps data of any size to a fixed-size string of characters. Even a tiny change in the input data results in a completely different hash. This ensures data integrity, confirming that information has not been altered. Common hashing algorithms include MD5 and SHA.

#### The Quantum Computing Threat

The security of current asymmetric encryption methods largely relies on the difficulty of factoring large prime numbers. Quantum computers, however, may be able to break this type of encryption very quickly. This is prompting research into quantum-resistant encryption methods. Symmetric encryption with a sufficiently long key is considered to be more resistant to quantum computing threats.

### Data Privacy and Regulation

#### Privacy Challenges in IoT

Public spaces are increasingly being monitored by sensors collecting data on crowd size, sound levels, and air quality. While this can be useful, it also presents privacy challenges. Municipalities bear the responsibility of overseeing these spaces and their new obligations with the implementation of sensors.

#### Understanding the General Data Protection Regulation (GDPR)

The GDPR (in Dutch: AVG) is a European regulation designed to protect the rights of individuals regarding their personal data. It applies to the automated or structured manual processing of personal information.

*   **Personal Information:** Any information related to an identified or identifiable person (name, address, ID number, etc.).
*   **Data Processing:** Any operation performed on personal data, such as collecting, storing, using, or deleting it.

GDPR states that personal data can only be processed if there is a legitimate basis, such as:
1.  **Consent:** The individual has given clear permission.
2.  **Contract:** Processing is necessary to fulfill a contract.
3.  **Legal Obligation:** The law requires the data to be processed.
4.  **Vital Interests:** Necessary to protect someone's life.
5.  **Public Task:** Necessary for a task in the public interest.
6.  **Legitimate Interests:** Necessary for the legitimate interests of the organization (unless overridden by the individual's rights).

## Part 6: IoT in Action: Case Studies

### Comprehensive Case Study: Beehive Monitoring

This project utilizes IoT technology to create "smart" beehives for the beekeeper association *De Blije Bij*.

#### Project Goals and System Architecture

The system is designed to monitor several factors to prevent vandalism and track the health of the bees:
*   **Hive Tilt:** An accelerometer triggers an alert if the hive is tilted, indicating tampering.
*   **Bee Activity:** Sound levels are analyzed to assess bee activity.
*   **Hive Weight:** Tracks honey and food stores.
*   **GPS Location:** For tracking stolen hives.

The architecture is as follows:
1.  **Beehive Node:** An Arduino Leonardo with sensors collects data every 30 minutes.
2.  **Gateway & TTN:** The node transmits a compact payload via the LoRa network to The Things Network.
3.  **Node-RED & Database:** Data flows via MQTT from TTN to a Node-RED instance running on a Raspberry Pi. Node-RED processes the data and stores it in an SQL database.
4.  **Grafana Dashboard:** Data is visualized on a Grafana dashboard for the end user.

A "Unifyer" concept can be used to gather and format data consistently if it comes from different sources (e.g., TTN, Helium, ChirpStack).

#### Data Acquisition, Processing, and Analysis

To create compact payloads and conserve battery life, sensor data, originally in float format, is converted to integers with a scaling factor. The receiving end reconstructs the float by multiplying the integer by the scaling factor.

Within Node-RED, data arrives from TTN via MQTT. It is injected into a MySQL database named `beehive_sensor`. Filtering is essential to focus on relevant data (e.g., uplink messages from a specific device ID) and prevent overloading the debugger. Incomplete data objects should be rejected to ensure data quality.

When an alarm is triggered (e.g., a hive is tilted), the system should alert users only when necessary, not overwhelm them with constant monitoring. This intelligence can be built into the Node-RED flow.

#### Dashboarding and Visualization

The Grafana dashboard displays charts for weight, sound level (bee activity), temperature, and battery percentage. An alert is triggered if the hive is tilted. A Node-RED dashboard can also provide a user interface, for example, connecting a lamp to an LED UI for a visual notification.

### Case Study: Apeldoorn Heat Stress Measurement

This project measures heat stress in the city of Apeldoorn to address the urban heat island effect.

#### Citizen Science and Sensor Design

The city involved its community in the project (citizen science) to increase engagement. The goal was to collect temperature and humidity data to generate heat maps and identify problem areas.

The sensor nodes were designed to be low-cost and buildable by community members, using open-source hardware (KiCad) and software (Arduino) with through-hole components. The MJS (Meet je Stad - Measure your City) node, based on an ATmega328P and an RFM95 LoRa radio, was used.

#### Power Optimization with Solar

The project explored powering a LoRaWAN node with a dust sensor using solar energy. Energy usage calculations were performed to determine battery life. By optimizing the code for low power and adding a diode to the solar panel to prevent power leakage, the operational life of the node was significantly extended, running for years without issues, even through winter.

### Mini-Case Study: Raspberry Pi Projects

#### Troubleshooting a Camera with ChatGPT

The speaker shared an experience using ChatGPT to write code for a Raspberry Pi 3 camera setup. While ChatGPT can assist with code generation, issues like incorrect information order can hinder functionality. When a configuration object was overwritten, the speaker suggested simple debugging steps like using "Control Z" to revert changes.

#### Setting up a LAMP Server and Network Troubleshooting

The course covers practical setup on a Raspberry Pi, including installing a LAMP server for database management. Troubleshooting network connectivity is also a key skill. Challenges arise when a device is behind a NAT, making it unscannable from an external network. A 'link-local' IP address (starting with `169.254.x.x`) indicates a failure to get an IP from a DHCP server. For virtual machines, it's important to set the network adapter to 'bridged' mode to place it on the same network as the host, allowing it to be discoverable.

## Part 7: Conclusion and Final Project

### Final Assignment Overview

The final assignment brings all the learned concepts together, requiring students to build a complete IoT solution.

#### Bringing It All Together: From Sensor to Dashboard

The lab tasks for the final assignment include:
1.  **Install Grafana** on a Raspberry Pi.
2.  **Design a database** for a chosen application, creating an entity-relationship diagram with fields and data types.
3.  **Implement the database** in MySQL using PHPMyAdmin.
4.  **Connect Node-RED** to your application in The Things Network, subscribing to MQTT topics.
5.  **Inject data** received from TTN into your database using Node-RED and a MySQL node.
6.  **Create a view in Grafana** to visualize the data from your database.

The submission requires a zip file of the code repository, including the database design. This project demonstrates a comprehensive understanding of the entire IoT data pipeline, from payload decoding to data visualization.