# IoT-muskrattrap: The Intelligent Muskrat Trap

## Project Overview

The SMARTrap project aims to develop a smart, humane, and efficient solution for controlling muskrat populations using IoT technology. Muskrats pose a significant threat to water management systems in the Netherlands. This project seeks to create a smart trap that detects trap status (open/closed), identifies captures, monitors trap movement, and reports its health status, all while ensuring non-lethal trapping and enabling remote monitoring.

Detailed project documentation, including design choices, technical specifications, and setup guides, can now be found in the `/docs` directory. This includes:
*   `docs/project-background.md`: Covers initial research, LPWAN/LoRaWAN comparisons, and trap design considerations.
*   `docs/iot-node-details.md`: Details the IoT node hardware simulation and LoRaWAN payload structure.
*   `docs/server-and-nodered-setup.md`: Outlines the server-side stack, database, and Node-RED setup.
*   `docs/mini-research-summary.md`: The Mini-Research summary in English Markdown.
*   `docs/doxygen/`: Doxygen-generated API documentation for the codebase (also published to GitHub Pages).

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

5. **Node-RED TTN Integration & Setup:**
    * **Credential Encryption:** The Node-RED `flows_cred.json` file (which stores sensitive credentials for your flows) is encrypted. A `credentialSecret` is defined in `serverSide/nodered/settings.js`.
        *   **ACTION REQUIRED FOR NEW USERS/DEPLOYMENTS:** The current `credentialSecret` in `serverSide/nodered/settings.js` is a placeholder (`change_this_to_a_strong_secret`). For security, change this to a strong, unique secret and store your chosen secret securely. Failure to use a strong, unique secret poses a security risk. After changing it, restart Node-RED and re-deploy your flows (make any minor change and deploy) to apply the new encryption key.
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

## Work Breakdown Structure

#### Payload Coder (`payloadCoder/`)

* [X] Implement and test C++ payload encoder/decoder classes (Custom binary format).
  * [X] Corrected `add_uint32` bug in `payloadEncoder.cpp`.
  * [X] Updated getter return types in `payloadDecoder.h` for type consistency.
  * [X] Enhanced unit tests in `unitTest.cpp` (type corrections, min/max values, all boolean combinations).
  * [~] Ensure compatibility with Cayenne LPP (Lower priority; focus on custom binary format).
  * [~] Input validation of payload data (Handled by sensor/simulation logic in `nodeCode.ino`).
  * [~] Add warning flag for when data is clipping (Covered by input validation handling).
* [X] (I.D) Document with Doxygen.

#### LoRaWAN Node (`nodeCode/`)

* [~] Implement prototype LoRaWAN node on HAN IoT Node.
  * [~] Emulate sensors using onboard components and integrate with payload.
    * Sensor objects (`doorSensor`, `catchSensor`, `displacementSensor`, `batterySensor`) are instantiated.
    * Simulated sensor states (buttons for door, catch, displacement) are updated in the loop.
    * **Next Step:** Integrate actual simulated sensor values (including `POTMETER 2` for battery) into the LoRaWAN payload instead of `encoder.setTestValues()`.
    * Consolidated `encoder.h/cpp` and `decoder.h/cpp` from `payloadCoder/` into `nodeCode/`.
  * [~] Implement event-triggered and heartbeat communication.
    * Current `nodeCode.ino` sends data every loop cycle + delay, not based on state changes or `HEARTBEAT_INTERVAL_MS`.
    * **Next Step:** Implement logic to send data only when sensor states change or at the `HEARTBEAT_INTERVAL_MS`. Requires tracking previous sensor states.
  * [~] Implement sleep functionality for maximum battery life.
    * [X] Added basic MCU sleep using Watchdog Timer (WDT) (Likely handled by TTN library).
    * [X] Optimize general power usage.
      * Conditionalized `debugSerial` output.
      * Comments regarding further optimization exist.
    * [~] Optimize data transmission (Target: once every 24 hours for routine updates) (In Progress).
      * [X] `HEARTBEAT_INTERVAL_MS` constant changed to 24 hours (but not yet used by send logic).
      * [X] **Flash Firmware (Working Version):**
        * `[X] User reverted to an older working version of nodeCode.`
        * `[X] User manually set loraCommunication = true.`
        * `[ ] (Optional) Modify \`HEARTBEAT_INTERVAL_MS\` to 10 seconds for testing if needed.`
        * `[X] Firmware (working version with LoRa enabled) successfully flashed by user.`
* [~] (I.D) Document with Doxygen (In Progress).
  * **Next Step:** Review and add Doxygen comments to `nodeCode.ino` and related headers/source files.

#### Server-Side (`serverSide/`)

* [~] (II.A) Finalize Database Design and Implementation (MySQL).
  * [X] Configured MariaDB to automatically import `serverSide/databaseSetup.sql` on initial startup.
* [X] (II.B) Implement Node-RED flows for TTN data reception and MySQL storage.
  * Current Focus: Setting up Node-RED to receive data from The Things Network (TTN) and store it in a MySQL database.
  * Sub-tasks:
    * `[X] Start Docker Compose stack (if not already running).`
    * `[X] Add TTN and MySQL environment variables to Node-RED service in \`docker-compose.yml\`.`
    * `[X] Refactor Node-RED environment variables to use an external \`variables.env\` file (\`serverSide/variables.env\`) and apply to all services.`
    * `[X] Reset corrupted \`flows_cred.json\` to resolve credential loading error.`
    * `[X] **Action Required:** Update placeholder values for TTN & MySQL credentials in \`serverSide/variables.env\`. (User confirmed completion)`
    * `[X] Configure Node-RED TTN integration (decoder already done, ensure TTN application is configured with the decoder).`
      * `[X] Confirm TTN application created and decoder function (\\\\`serverSide/javascriptDecoder/decoder.js\\\\`) added to the TTN application\\\'s payload formatters. (User confirmed completion)`
      * `[X] Obtain TTN Application ID (TTN_APP_NAME, TTN_APP_KEY_PASSWORD in serverSide/variables.env)`
      * `[X] Add and configure MQTT input node in Node-RED.`
        *   The `flows.json` was updated to hardcode `broker` ("eu1.cloud.thethings.network") and `port` ("1883") from `variables.env` due to editor limitations in referencing environment variables for these specific fields.
        *   **(User Confirmed Completion - 2025-06-08):** Manually configure the MQTT broker node ("muskrattrap@ttn") credentials in the Node-RED editor. In the "Security" tab of the broker configuration, set "Username" and "Password" fields, preferably using the "Environment Variable" input type if available for credentials, to reference `TTN_APP_NAME` and `TTN_APP_KEY_PASSWORD`. If "Environment Variable" type is not available for credentials, try `{{TTN_APP_NAME}}` and `{{TTN_APP_KEY_PASSWORD}}` or, as a last resort, enter the literal values.
    * `[X] Configure Node-RED MySQL connection.`
        *   The `flows.json` was updated to hardcode `host` ("mariadb"), `port` ("3306"), `db` ("muskrattrap_db"), and `tz` ("Europe/Amsterdam") from `variables.env` due to editor limitations.
        *   **(User Confirmed Completion - 2025-06-08):** Manually configure the MySQL database node ("mariadb") credentials in the Node-RED editor. Set the "User" and "Password" fields.
            *   For "User", use the value of the `MYSQL_USER` environment variable (which is `mysql_user`).
            *   For "Password", use the value of the `MYSQL_PASSWORD` environment variable (which is `mysql_password`).
            *   If the Node-RED editor allows referencing environment variables for credentials, use `MYSQL_USER` and `MYSQL_PASSWORD`. Otherwise, use the literal values.
    * `[X] Verify data reception from TTN via MQTT node.`
    * `[X] Verify data processing by "Unifier TTNV3" function.`
    * `[X] Verify data insertion into MySQL via "database command transformer" function and MySQL node.`
* [X] (II.D) Implement JavaScript TTN Payload Decoder.
* [X] Added VSCode task "Start/Update Server Applications (Docker Compose)" to `.vscode/tasks.json`.
* [X] (I.D, II.A.3) Document relevant parts with Doxygen/Markdown. (Consolidated from `docs-old` to `docs`)

#### Visualization & Reporting (Grafana & Node-RED UI)

* [X] Implement Node-RED UI Dashboard.
  * [X] Initial design included individual UI elements for single trap display.
  * [X] Refined dashboard strategy to focus on a `ui_table` for a multi-trap overview.
  * [X] Removed single-trap `ui_text` and `ui_gauge` nodes.
  * [X] Added a "Manage Trap Data for Table" function node that:
    * Stores the latest status of each trap in Node-RED's flow context, keyed by `devID`, to support scalability for many devices.
    * Formats data for display (e.g., booleans to "Open"/"Closed", battery to percentage, extracts RSSI/SNR from first gateway).
    * Calculates and stores total active catches in flow context (`flow.activeCatchesCount`).
    * Calculates and stores the average RSSI of all reporting traps in flow context (`flow.averageRssiValue`).
    * Calculates and stores the total number of monitored traps in flow context (`flow.totalTrapsMonitored`).
    * Outputs an array of all trap data objects for the main table.
  * [X] Added a `ui_table` node ("Trap Status Overview") to the "Dashboard" tab in the "Trap Overview" group.
    * Columns: Trap ID, Last Seen, Door, Catch, Displaced, Battery, RSSI, SNR.
    * Populated by the "Manage Trap Data for Table" function.
  * [X] Added a "Summary Stats" group to the "Dashboard" tab.
    * [X] Added an "Active Catches" counter (`ui_text` node) that displays the total number of traps with a detected catch.
    * [X] Added an "Average RSSI" display (`ui_text` node) showing the average signal strength across all traps.
    * [X] Added a "Total Traps" counter (`ui_text` node) showing the total number of unique traps that have reported.
    * All summary stats are updated periodically.
  * [X] The "Unifier TTNV3" node is now wired to the "Manage Trap Data for Table" function.
  * [X] The `ui_table` ("Trap Status Overview"), "Active Catches" counter, "Average RSSI" display, and "Total Traps" counter are key dashboard components.
* [~] Implement Grafana Dashboard.
  * [ ] Add additional relevant visualizations.
  * [ ] Implement alerts in Grafana for when a muskrat has been trapped.

#### General Documentation & Project Management

* [X] (I.A) Mini-Research Summary:
  * [X] Converted to Markdown, PII removed, and translated to English.
  * [X] Original DOCX added to `.gitignore`.
  * [X] Converted to PDF.
  * [X] Located and submitted peer review document.

#### Documentation Review & Enhancement

* [X] Review content in `docs-old/` and migrate relevant information to `docs/`. (Completed, `docs-old` removed)
* [X] Ensure `README.md` appropriately refers to `docs/` (and no longer `docs-old/`).
* [X] Set up Doxygen configuration (`Doxyfile` in root):
  * [X] Configured `PROJECT_NAME`.
  * [X] Configured `OUTPUT_DIRECTORY` to `docs/doxygen`.
  * [X] Configured `INPUT` to include `nodeCode`, `payloadCoder`, `serverSide`.
  * [X] Set `RECURSIVE = YES`.
  * [X] Set `EXTRACT_ALL = YES`.
  * [X] Set `EXTRACT_PRIVATE = YES`.
  * [X] Set `HAVE_DOT = NO`.
* [X] Create a VS Code task to build all Doxygen documentation:
  * [X] Added `tasks.json` entry to execute Doxygen using the root `Doxyfile`.
* [X] Create a GitHub workflow action to:
  * [X] Execute Doxygen documentation generation.
  * [X] Publish the resulting HTML to GitHub Pages.
* [X] Integrate `buildnumber.num` into the Doxygen documentation.

## Design Notes & Rationale

*(This section will document key architectural decisions, technology choices, and learnings.)*

* **Database Initialization:** The MariaDB Docker container (from `linuxserver/mariadb`) supports automatic execution of SQL scripts placed in its `/config/initdb.d/` directory during the first run. The `serverSide/docker-compose.yml` file leverages this by mapping the project's `serverSide/databaseSetup.sql` file to `/config/initdb.d/databaseSetup.sql` within the MariaDB container. This ensures that the required database schema is automatically created when the services are first started.
* **Payload Size Clarification:** The LoRaWAN payload is 11 bytes. The specification in `docs/iot-node-details.md` mentions '10 bytes + 3 bits'; this refers to the three boolean flags (doorStatus, catchDetect, trapDisplacement) being packed into a single byte, contributing to the total 11-byte structure (4 bytes for ID, 1 byte for version, 1 byte for booleans, 1 byte for battery status, and 4 bytes for Unix time). The C++ encoder (`nodeCode/encoder.cpp`, `payloadCoder/encoder.cpp`) and the JavaScript TTN decoder (`serverSide/javascriptDecoder/decoder.js`) are consistent with this 11-byte structure.

* **LPWAN Choice:** LoRaWAN was selected over NB-IoT and LTE-CAT-M due to its superior energy efficiency, long-range capabilities, cost-effectiveness, scalability, and robustness for remote deployments. (Details: `docs/project-background.md`)
* **LoRaWAN Provider:** The Things Network (TTN) was chosen over KPN LoRa due to its cost transparency, extensive community support and documentation, flexibility in network expansion, open-source nature, and scalability. (Details: `docs/project-background.md`)
* **Trap Design:** The trap utilizes magnetic sensors (door), weight sensors (catch detection), and wire-based sensors (movement), along with battery monitoring. (Details: `docs/project-background.md`)
* **Payload Structure:** The LoRaWAN payload is optimized for size and includes: ID, version, door status, catch detection, trap displacement, battery status, and Unix timestamp. (Details: `docs/iot-node-details.md`)
* **Hardware Simulation:** Onboard buttons and LEDs of the HAN IoT Node (The Things Uno) are used to simulate sensor inputs and status indicators. (Details: `docs/iot-node-details.md`)

## Github Workflow for Doxygen

A GitHub workflow has been set up to automatically generate and publish the Doxygen HTML documentation to GitHub Pages. This workflow is defined in `.github/workflows/doxygen-pages.yml`.

The workflow performs the following steps:

1. **Checkout Code**: Checks out the repository code.
2. **Install Doxygen**: Installs Doxygen on the runner.
3. **Read Build Number**: Reads the build number from `payloadCoder/buildnumber.num`.
4. **Generate Documentation**: Runs Doxygen using the `Doxyfile` in the project root.

### Viewing Container Logs

To view the logs of a specific container managed by Docker Compose, you can use the following command from the directory containing your `docker-compose.yml` file (e.g., `serverSide/`):

```bash
docker-compose logs <service_name>
```

Replace `<service_name>` with the name of the service as defined in your `docker-compose.yml` file (e.g., `nodered`, `mariadb`, `phpmyadmin`).

For example, to view the logs for the Node-RED container:

```bash
docker-compose logs nodered
```

To follow the logs in real-time, you can add the `-f` flag:

```bash
docker-compose logs -f <service_name>
```
