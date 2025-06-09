# IoT-muskrattrap: The Intelligent Muskrat Trap

---

## Workspace Structure & Key Files

The repository is organized as follows:
- `nodeCode/`: Arduino firmware and sensor logic for the IoT node.
- `payloadCoder/`: C++ payload encoder/decoder and unit tests.
- `serverSide/`: Docker Compose stack (Node-RED, MariaDB, Grafana, etc.).
- `docs/`: All project documentation, research, and Doxygen output.
- `screenshots/`: Dashboard and UI screenshots for verification.
- `.vscode/tasks.json`: VSCode tasks for build, flash, monitor, and documentation.

---

## Project Overview

The SMARTrap project aims to develop a smart, humane, and efficient solution for controlling muskrat populations using IoT technology. Muskrats pose a significant threat to water management systems in the Netherlands. This project seeks to create a smart trap that detects trap status (open/closed), identifies captures, monitors trap movement, and reports its health status, all while ensuring non-lethal trapping and enabling remote monitoring.

Detailed project documentation, including design choices, technical specifications, and setup guides, can now be found in the `/docs` directory. This includes:

- `docs/project-background.md`: Covers initial research, LPWAN/LoRaWAN comparisons, and trap design considerations.
- `docs/iot-node-details.md`: Details the IoT node hardware simulation and LoRaWAN payload structure.
- `docs/server-and-nodered-setup.md`: Outlines the server-side stack, database, and Node-RED setup.
- `docs/mini-research-summary.md`: The Mini-Research summary in English Markdown.
- `docs/doxygen/`: Doxygen-generated API documentation for the codebase (also published to GitHub Pages).

The `docs-old/` directory has been removed as its content has been migrated and consolidated into the `docs/` directory.

## Environment Setup

* **Operating System:** macOS
* **Default Shell:** bash
* **Python Environment:** (To be determined if Python will be used for new development. If so, `uv` will be used for package management.)

## Technology Stack

* **IoT Node Hardware:** The Things Uno (Arduino Leonardo based)
* **Communication:** LoRaWAN (via The Things Network - TTN)
* **Data Processing & Automation:** Node-RED
* **Data Storage:** MySQL (MariaDB)
* **Data Visualization:** Grafana
* **Server Orchestration:** Docker & Docker Compose

## Development setup

### Prerequisites

* Git
* Docker
* Docker Compose
* Arduino IDE (for node development)

### Initial Setup

1. Clone the GitHub repository:

    ```bash
    git clone git@github.com:jjgroenendijk/muskrattrap.git
    cd muskrattrap
    ```

2. Install Arduino CLI and required libraries:

   ```bash
   brew install arduino-cli # or see https://arduino.github.io/arduino-cli/latest/installation/
   arduino-cli core update-index
   arduino-cli core install arduino:avr
   arduino-cli lib install OneWire
   arduino-cli lib install DallasTemperature
   arduino-cli lib install LowPower
   ```

3. Install Docker & Docker Compose (see https://docs.docker.com/get-docker/)
4. Copy `serverSide/example.env` to `serverSide/.env` and configure secrets and passwords as needed before running the stack:
   ```bash
   cp serverSide/example.env serverSide/.env
   # Edit serverSide/.env to set secure values for all secrets and passwords
   ```

### Development Workflow with VSCode Tasks

This project includes VSCode tasks for common development actions, defined in `.vscode/tasks.json`. You can run these tasks from the Command Palette (View > Command Palette or Ctrl+Shift+P/Cmd+Shift+P) by typing "Tasks: Run Task" and selecting the desired task.

Available tasks:

* **Compile LoRaWAN Node (nodeCode.ino):** Compiles the main Arduino sketch for the LoRaWAN node using `arduino-cli`.
* **Build PayloadCoder Executable:** Builds the C++ `payloadCoder` test executable using `make` in the `payloadCoder/` directory.
* **Run PayloadCoder Unit Tests:** Runs the unit tests for the C++ `payloadCoder` by executing the compiled test program. This task depends on the successful build of the executable.
* **Monitor Arduino (nodeCode.ino) - Auto-detect Port:** Opens a serial monitor for the LoRaWAN node using `arduino-cli monitor`. This task attempts to automatically find the serial port for an Arduino Leonardo-compatible board (works best on macOS/Linux if only one such board is connected). If it fails, or if you have multiple boards, you might need to use the manual command line method described in the "Node (The Things Uno) Development" section.
* **Generate Doxygen Documentation:** Generates Doxygen documentation for the entire project using the `Doxyfile` in the project root. The output will be in `docs/doxygen`.
* **Start/Update Server Applications (Docker Compose):** Starts or updates all server-side applications (Node-RED, MariaDB, phpMyAdmin, Grafana) defined in `serverSide/docker-compose.yml`. It uses the `--force-recreate` flag to ensure containers are updated with any image changes. This task is run from the `serverSide/` directory.

These tasks help streamline the compilation and testing processes directly within VSCode.

### Server-Side Development

1. Navigate to the server-side directory:

    ```bash
    cd serverSide
    ```

2. Ensure the `docker-compose.yml` file has a secure password for MariaDB (currently `# change this to a secure password`).
3. Start the services:

    ```bash
    docker-compose up -d
    ```

    Alternatively, use the "Start/Update Server Applications (Docker Compose)" VSCode task.

4. **Database Initialization:**
    * The MariaDB service in `serverSide/docker-compose.yml` is configured to automatically import any `*.sql` files placed in its `/config/initdb.d/` directory upon first startup.
    * The project's `serverSide/databaseSetup.sql` is mapped to this directory, ensuring the database schema is created when the MariaDB container is first run.

5. **Node-RED TTN Integration & Setup:**
    * **Credential Encryption:** The Node-RED `flows_cred.json` file (which stores sensitive credentials for your flows) is encrypted. A `credentialSecret` is defined in `serverSide/nodered/settings.js`.
        * **ACTION REQUIRED FOR NEW USERS/DEPLOYMENTS:** The current `credentialSecret` in `serverSide/nodered/settings.js` is a placeholder (`change_this_to_a_strong_secret`). For security, change this to a strong, unique secret and store your chosen secret securely. Failure to use a strong, unique secret poses a security risk. After changing it, restart Node-RED and re-deploy your flows (make any minor change and deploy) to apply the new encryption key.
    * Use the JavaScript decoder from `serverSide/javascriptDecoder/decoder.js` and add it to the application decoder in The Things Network console.
    * For Node-RED Git integration (if needed for flow management), refer to the setup guide in `docs/server-and-nodered-setup.md`.
    * **Note on `serverSide/nodered`:** This directory was previously managed as a Git submodule. It has now been integrated directly into the main repository. Its contents are part of the main project's working tree and should be staged and committed as regular files.

### Node (The Things Uno) Development

1. Open the Arduino project: `nodeCode/nodeCode.ino` using the Arduino IDE.
2. **Configure Secrets:**
    * Copy `nodeCode/secrets.example.h` to `nodeCode/secrets.h`.
    * Edit `nodeCode/secrets.h` and add your personal keys from The Things Network (TTN).
3. **Compiling with `arduino-cli` (Recommended):**
    * Ensure `arduino-cli` is installed (see [arduino-cli installation guide](https://arduino.github.io/arduino-cli/latest/installation/)).
    * Update core index and install the AVR core (for Arduino Leonardo / The Things Uno):

        ```bash
        arduino-cli core update-index
        arduino-cli core install arduino:avr
        ```

    * Install necessary libraries:

        ```bash
        arduino-cli lib install OneWire
        arduino-cli lib install DallasTemperature
        # TheThingsNetwork library is included locally in nodeCode/
        ```

    * Compile the sketch (from the project root directory):

        ```bash
        arduino-cli compile --fqbn arduino:avr:leonardo nodeCode/nodeCode.ino
        ```

    * **Finding your The Things Uno's Serial Port:**
        Before uploading, you need to identify the serial port your The Things Uno is connected to. Run the following command:

        ```bash
        arduino-cli board list
        ```

        Look for an entry corresponding to "Arduino Leonardo" (as The Things Uno is Leonardo-based) and note its port (e.g., `/dev/cu.usbmodemXXXX` on macOS/Linux, or `COMX` on Windows).
    * **Uploading the Sketch:**
        Once you have the port, use it in the upload command. Replace `YOUR_SERIAL_PORT` with the identified port:

        ```bash
        arduino-cli upload -p YOUR_SERIAL_PORT --fqbn arduino:avr:leonardo nodeCode/nodeCode.ino
        ```

        For example:

        ```bash
        # arduino-cli upload -p /dev/cu.usbmodem11401 --fqbn arduino:avr:leonardo nodeCode/nodeCode.ino
        ```

        (Note: Ensure no other applications, like a serial monitor, are using the port, as this can cause "Resource busy" errors. Uploading might also require specific permissions.)
    * **Monitoring Serial Output:**
        You can monitor the serial output from your The Things Uno using `arduino-cli` directly in your terminal or via a VSCode task:
        * **VSCode Task (Recommended):** Run the "Monitor Arduino (nodeCode.ino) - Auto-detect Port" task from the Command Palette. This will attempt to find your Arduino's port automatically.
        * **Command Line (Manual Port):** If the auto-detect task fails or you prefer to specify the port manually, first identify your port with `arduino-cli board list`. Then, replace `YOUR_SERIAL_PORT` with the identified port:

            ```bash
            arduino-cli monitor -p YOUR_SERIAL_PORT --fqbn arduino:avr:leonardo
            ```

## Project context

This section provides a comprehensive overview of the project's background, design, and implementation details, consolidating information from various project documents.

### Project Rationale and Technology Selection

#### Challenge: Muskrat Management

In the Netherlands, water boards are tasked with controlling muskrat populations to prevent damage to dikes and subsequent flooding. The SMARTrap project was initiated to create a humane and efficient IoT solution for this task. The goal is a low-cost, sustainable, and user-friendly "smart" trap that provides remote monitoring capabilities to reduce animal suffering and improve management efficiency.

#### LPWAN Technology Comparison

A core requirement for the smart trap is a communication network with long range and very low power consumption, as the traps are battery-powered and located in remote areas. Three Low Power Wide Area Network (LPWAN) technologies were evaluated:

  * **LoRaWAN (Long Range Wide Area Network):** Optimized for energy-efficient, long-distance communication. It offers a range of 3 km in urban and up to 10 km in rural areas, with 3 to 5 times lower energy consumption than other LPWAN technologies.
  * **NB-IoT (Narrowband Internet of Things):** Uses existing LTE networks and is optimized for low energy use and long distances, with a focus on indoor coverage.
  * **LTE-CAT-M:** Offers higher speeds and mobility than NB-IoT but at the cost of higher power consumption and hardware costs.

**Conclusion:** LoRaWAN was selected as the most suitable technology due to its superior energy efficiency, extensive range in rural settings, cost-effectiveness, and robustness, all of which are critical for this application.

#### LoRaWAN Provider Comparison: TTN vs. KPN

Two LoRaWAN network providers in the Netherlands were considered:

  * **KPN LoRa:** A commercial network provided by KPN. Information on costs was not provided upon request. While KPN offers location determination, its precision of 174 meters is insufficient for quickly locating a trap.
  * **The Things Network (TTN):** A community-driven network with a clear and fair business model, offering free use for small-scale projects and paid tiers for larger deployments. Crucially, TTN allows users to extend network coverage by adding their own gateways and has extensive online documentation, which is highly beneficial for a study project.

**Conclusion:** The Things Network (TTN) was chosen over KPN LoRa due to its cost transparency, extensive community support and documentation, and the flexibility to expand the network where needed.

### SMARTrap System Design and Operation

#### Conceptual Sensor Integration

The SMARTrap is designed with multiple sensors to provide a complete picture of its status:

1.  **Magnetic Door Sensor:** Detects if the trap door is open or closed.
2.  **Weight Sensor:** A sensor on the bottom of the trap detects the weight of a captured animal.
3.  **Movement Detection Sensor:** A wire-based sensor detects if the trap has been moved from its position.

A signal is transmitted to the server application when the door is closed and the weight sensor is triggered, indicating a successful capture. A separate signal is sent if the trap is moved. The trap also continuously monitors and reports its battery status for maintenance.

#### Communicated Events

The IoT node must communicate four critical events:

1.  **Trap Status (Door Open/Closed):** Indicates if the trap is set or has been triggered.
2.  **Catch Detection:** Confirms if an animal has been captured.
3.  **Trap Displacement:** Alerts if the trap has been moved.
4.  **Health Status:** Reports the operational status, primarily the battery level.

### IoT Node Implementation

#### Hardware and Development Simulation

Development and simulation are performed using The Things Uno (based on Arduino Leonardo), which is the core of the IoT node. To facilitate development without physical sensors, onboard components are used for simulation:

  * **Door Status (Closed):** Simulated by pressing `SWITCH 1`, which turns `LED1` ON.
  * **Catch Detection:** Simulated by pressing `SWITCH 2`, which turns `LED2` ON.
  * **Trap Movement:** Simulated by pressing `SWITCH 1` and `SWITCH 2` simultaneously, which turns `LED3` ON.
  * **Battery Level:** Simulated by reading the position of `POTMETER 2`, with the brightness of `LED4` indicating the level.

#### LoRaWAN Payload Structure

To conserve power and airtime, data is encoded into a compact binary payload. The total payload size is 11 bytes.

| Name | ID | Type | Size | Description |
| :--- | :--- | :--- | :--- | :--- |
| Identification number | `id` | unsigned integer | 4 bytes | A unique ID assigned to each trap. |
| Payload version number | `version` | unsigned integer | 1 byte | Version of the payload format. |
| Door status | `doorStatus` | boolean | 1 bit | `0` for Open, `1` for Closed. |
| Catch detection | `catchDetect` | boolean | 1 bit | `0` for No Catch, `1` for Catch Detected. |
| Trap Displacement | `trapDisplacement` | boolean | 1 bit | `0` for No Displacement, `1` for Displaced. |
| Battery status | `batteryStatus` | unsigned integer | 1 byte | Battery level percentage (0-255). |
| Date and time | `unixTime` | unsigned integer | 4 bytes | Unix epoch timestamp of the event. |

*(Note: The three boolean values are packed into a single byte using bitwise operations to save space.)*

### Server-Side Architecture

The server-side infrastructure is managed using a portable, containerized environment.

#### Hosting Stack (Docker)

The environment is orchestrated using Docker and Docker Compose, defining all services in the `serverSide/docker-compose.yml` file. This allows the stack to run on various platforms. The core services include:

  * Node-RED
  * MariaDB (MySQL)
  * Grafana
  * phpMyAdmin

#### Database Schema

Data from the traps is stored in a MariaDB database. The primary table is structured as follows (refer to `serverSide/databaseSetup.sql` for the definitive schema):

| Column Name | Data Type | Comment |
| :--- | :--- | :--- |
| autoIncrement | BIGINT(20) UNSIGNED ZEROFILL | Auto-incrementing primary key. |
| UUID | UUID | Default value generated with `uuid()` function. |
| messageSource | VARCHAR(32) | Source of the message (e.g., "TTNV3"). |
| dateTime | DATETIME | Timestamp of data reception/processing. |
| devID | VARCHAR(32) | Device ID from TTN. |
| devEUI | CHAR(16) | LoRaWAN Device EUI. |
| fcnt | INT(11) UNSIGNED | LoRaWAN frame counter. |
| port | TINYINT(3) UNSIGNED | LoRaWAN FPort. |
| devAddr | CHAR(8) | LoRaWAN Device Address. |
| frequency | FLOAT | Transmission frequency. |
| sf | TINYINT(3) UNSIGNED | Spreading Factor used. |
| batteryStatus | TINYINT(3) UNSIGNED | Battery level from payload (0-255). |
| catchDetect | TINYINT(1) | Boolean (0/1) for catch detection. |
| doorStatus | TINYINT(1) | Boolean (0/1) for door status. |
| trapDisplacement | TINYINT(1) | Boolean (0/1) for trap movement. |
| id | INT(11) | Trap's unique ID from payload. |
| unixTime | INT(11) UNSIGNED | Unix timestamp from payload. |
| version | TINYINT(3) UNSIGNED | Payload version from payload. |

#### Data Flow and Processing (Node-RED)

Node-RED serves as the central processing hub for IoT data. Its primary functions are:

  * **Receive Data:** Subscribes to The Things Network (TTN) via an MQTT connection to receive incoming trap data.
  * **Decode Payload:** Uses a JavaScript function to decode the compact binary LoRaWAN payload into a usable format.
  * **Store Data:** Processes the decoded data and executes SQL queries to insert it into the MariaDB database for storage and later analysis.