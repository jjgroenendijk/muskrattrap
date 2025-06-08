# IoT-muskrattrap: The Intelligent Muskrat Trap

## Project Overview

The SMARTrap project aims to develop a smart, humane, and efficient solution for controlling muskrat populations using IoT technology. Muskrats pose a significant threat to water management systems in the Netherlands. This project seeks to create a smart trap that detects trap status (open/closed), identifies captures, monitors trap movement, and reports its health status, all while ensuring non-lethal trapping and enabling remote monitoring.

Detailed project documentation, including design choices, technical specifications, and setup guides, can be found in the `/docs-old` directory. The Mini-Research summary has been converted to English Markdown and is available at `docs/mini-research-summary.md`. Other documents are pending review and migration to the `docs/` directory.

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

## Replication Guide & Getting Started

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

5. **Node-RED TTN Integration:**
    * Use the JavaScript decoder from `serverSide/javascriptDecoder/decoder.js` and add it to the application decoder in The Things Network console.
    * For Node-RED Git integration (if needed for flow management):
        * Access the Node-RED container: `sudo docker exec -it nodered /bin/bash`
        * Follow the SSH key setup and Git configuration steps outlined in `docs-old/NodeRed/nodeRed.md`.

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

## Design Notes & Rationale

*(This section will document key architectural decisions, technology choices, and learnings, especially those from `context7` if used.)*

* **Database Initialization:** The MariaDB Docker container (from `linuxserver/mariadb`) supports automatic execution of SQL scripts placed in its `/config/initdb.d/` directory during the first run. The `serverSide/docker-compose.yml` file leverages this by mapping the project's `serverSide/databaseSetup.sql` file to `/config/initdb.d/databaseSetup.sql` within the MariaDB container. This ensures that the required database schema is automatically created when the services are first started.
* **Payload Size Clarification:** The LoRaWAN payload is 11 bytes. The specification in `docs-old/IoTNode/payload.md` mentions '10 bytes + 3 bits'; this refers to the three boolean flags (doorStatus, catchDetect, trapDisplacement) being packed into a single byte, contributing to the total 11-byte structure (4 bytes for ID, 1 byte for version, 1 byte for booleans, 1 byte for battery status, and 4 bytes for Unix time). The C++ encoder (`nodeCode/encoder.cpp`, `payloadCoder/encoder.cpp`) and the JavaScript TTN decoder (`serverSide/javascriptDecoder/decoder.js`) are consistent with this 11-byte structure.

* **LPWAN Choice:** LoRaWAN was selected over NB-IoT and LTE-CAT-M due to its superior energy efficiency, long-range capabilities, cost-effectiveness, scalability, and robustness for remote deployments. (Details: `docs-old/projectDescription/01-LPWANComparison.md`)
* **LoRaWAN Provider:** The Things Network (TTN) was chosen over KPN LoRa due to its cost transparency, extensive community support and documentation, flexibility in network expansion, open-source nature, and scalability. (Details: `docs-old/projectDescription/02-LoraComparison.md`)
* **Trap Design:** The trap utilizes magnetic sensors (door), weight sensors (catch detection), and wire-based sensors (movement), along with battery monitoring. (Details: `docs-old/projectDescription/03-trapDesign.md`)
* **Payload Structure:** The LoRaWAN payload is optimized for size (10 bytes + 3 bits) and includes: ID, version, door status, catch detection, trap displacement, battery status, and Unix timestamp. (Details: `docs-old/IoTNode/payload.md`)
* **Hardware Simulation:** Onboard buttons and LEDs of the HAN IoT Node (The Things Uno) are used to simulate sensor inputs and status indicators. (Details: `docs-old/IoTNode/hardwareSimulation.md`)

## Github Workflow for Doxygen

A GitHub workflow has been set up to automatically generate and publish the Doxygen HTML documentation to GitHub Pages. This workflow is defined in `.github/workflows/doxygen-pages.yml`.

The workflow performs the following steps:

1. **Checkout Code**: Checks out the repository code.
2. **Install Doxygen**: Installs Doxygen on the runner.
3. **Read Build Number**: Reads the build number from `payloadCoder/buildnumber.num`.
4. **Generate Documentation**: Runs Doxygen using the `Doxyfile` in the project root.

## Work Breakdown Structure

This section provides a Work Breakdown Structure (WBS) for the project, including task statuses and relevant updates.

### I. Node Development (IoT Device & Payload)

#### I.A Mini-Research Summary & Peer Review
  * `[X]` Converted to Markdown (`docs/mini-research-summary.md`), PII removed, and translated to English.
  * `[X]` Original DOCX (`docs-old/Jaap-Jan Groenendijk LoRaWAN verwerkte feedback.docx`) added to `.gitignore`.
  * `[X]` Convert to PDF as per deliverable requirements (I.A.5).
    * *Update (2025-06-07): Starting conversion.*
    * *Update (2025-06-07): Conversion to PDF done.*
  * `[X]` Locate and submit peer review document (I.A.5).
    * *Update (2025-06-07): Starting peer review document submission.*

#### I.B Payload Coder (`payloadCoder/` & `examples/payload/MyPayloadEncoderDecoder/`)
  * `[X]` Implement and test C++ payload encoder/decoder classes. (Custom binary format)
    * `[X]` Corrected `add_uint32` bug in `payloadEncoder.cpp`.
    * `[X]` Updated getter return types in `payloadDecoder.h` for type consistency.
    * `[X]` Enhanced unit tests in `unitTest.cpp` (type corrections, min/max values, all boolean combinations).
    * `[~]` Ensure compatibility with Cayenne LPP. (Decided this is lower priority; focusing on custom binary format).
    * `[~]` Input validation of payload data (clip data to outer ranges when out of range). (Handled by sensor/simulation logic in `nodeCode.ino`).
    * `[~]` Add warning flag for when data is clipping to maximum values. (Covered by input validation point).

#### I.C LoRaWAN Node (`nodeCode/`)
  * `[~]` Implement prototype LoRaWAN node on HAN IoT Node.
    * `[X]` Emulate sensors using onboard components as per `docs-old/IoTNode/hardwareSimulation.md`.
      * Consolidated `encoder.h/cpp` and `decoder.h/cpp` from `payloadCoder/` into `nodeCode/`.
    * `[X]` Implement event-triggered communication.
      * Added logic to detect changes in sensor states (door, catch, displacement).
      * Initialized previous sensor states after successful LoRaWAN join.
    * `[~]` Implement sleep functionality for maximum battery life.
      * `[X]` Added basic MCU sleep using Watchdog Timer (WDT).
      * `[X]` Optimize general power usage.
        * Conditionalized all `debugSerial` output.
        * Commented out explicit `ttn.sleep(HEARTBEAT_INTERVAL_MS)`.
        * Added comments regarding further optimization.
        * Created separate Debug and Release build/flash tasks.
        * Tested Debug build on device.
        * *Update (2025-06-07): Optimized general power usage for the LoRaWAN node.*
      * `[~]` Optimize data transmission (e.g., target once every 24 hours for routine updates). (In Progress)
        * `[X]` Changed `HEARTBEAT_INTERVAL_MS` to 24 hours.
        * *Update (2025-06-07): Optimizing data transmission for the LoRaWAN node. Changed `HEARTBEAT_INTERVAL_MS` to 24 hours.*

#### I.D Doxygen Documentation (Node & Payload)
  * `[X]` (Payload Coder) Document with Doxygen. (Reviewed and updated Doxygen comments).
  * `[~]` (LoRaWAN Node) Document with Doxygen.
    * *Update (2025-06-07 19:45): Started Doxygen documentation for `nodeCode/`.*
  * `[ ]` Ensure all Doxygen documentation is complete and integrated across the project.
    * *Update (2025-06-07): Task (I.D) Postponed.*

### II. Server-Side Development & Visualization

#### II.A Database Design and Implementation (MySQL)
  * `[ ]` Finalize Database Design and Implementation.
  * `[ ]` (Part of I.D, II.A.3) Document relevant parts with Doxygen/Markdown.
  * *Update (2025-06-07): Configured `serverSide/docker-compose.yml` for MariaDB to automatically import `serverSide/databaseSetup.sql` on initial startup.*

#### II.B Node-RED Development
  * `[ ]` Implement Node-RED flows for data reception from TTN, processing, and storage into MySQL.

#### II.C Visualization & Reporting (Grafana & Node-RED UI)
  * `[ ]` Implement Node-RED UI Dashboard.
  * `[ ]` Implement Grafana Dashboard.
    * `[ ]` Add additional relevant visualizations.
    * `[ ]` (Optional/Future) Publish dashboard on public internet.
    * `[ ]` Implement alerts in Grafana for when a muskrat has been trapped.

#### II.D TTN Payload Decoder (JavaScript)
  * `[X]` Implement JavaScript TTN Payload Decoder. (Verified existing `serverSide/javascriptDecoder/decoder.js`).

### III. Project Documentation & Management

#### III.A Doxygen Setup & GitHub Pages Workflow
  * `[X]` Set up Doxygen configuration for `nodeCode`, `payloadCoder`, and `serverSide` directories.
  * `[X]` Ensure Doxygen output is in `docs/doxygen`.
  * `[X]` Create a VS Code task to build all Doxygen documentation.
    * *Update (2025-06-07): Create a VS Code task to build all Doxygen documentation. This involved creating/configuring `Doxyfile` and defining `tasks.json` entry.*
  * `[X]` Create a GitHub workflow action to:
    * `[X]` Execute Doxygen documentation generation.
    * `[X]` Publish the resulting HTML to GitHub Pages.
  * `[X]` Integrate `buildnumber.num` into the Doxygen documentation. (Handled by GitHub workflow).
  * *Update (2025-06-07): Verified Doxygen GitHub Action functionality, including build number integration.*

#### III.B VSCode Task Enhancements
  * *Update (2025-06-07): Added VSCode task "Start/Update Server Applications (Docker Compose)" to `.vscode/tasks.json`.*

#### III.C Documentation Content Review & Migration
  * `[~]` Review content in `docs-old/` and migrate relevant information to a new `docs/` directory. (Mini-Research Summary migrated).
  * `[ ]` Ensure `README.md` appropriately refers to `docs-old/` and eventually to new `docs/` as content is migrated.

### IV. General Updates & Initial Setup
  * *Update (2025-06-07 19:34): Initial Setup: `README.md` structured based on project documentation. Context gathered from `docs-old` directory and `progress.md`. OS: macOS, Shell: bash.*
