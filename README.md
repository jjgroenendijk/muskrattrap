# IoT-muskrattrap: The Intelligent Muskrat Trap

## Project Overview

The SMARTrap project aims to develop a smart, humane, and efficient solution for controlling muskrat populations using IoT technology. Muskrats pose a significant threat to water management systems in the Netherlands. This project seeks to create a smart trap that detects trap status (open/closed), identifies captures, monitors trap movement, and reports its health status, all while ensuring non-lethal trapping and enabling remote monitoring.

Detailed project documentation, including design choices, technical specifications, and setup guides, can now be found in the `/docs` directory. This includes:

* `docs/project-background.md`: Covers initial research, LPWAN/LoRaWAN comparisons, and trap design considerations.
* `docs/iot-node-details.md`: Details the IoT node hardware simulation and LoRaWAN payload structure.
* `docs/server-and-nodered-setup.md`: Outlines the server-side stack, database, and Node-RED setup.
* `docs/mini-research-summary.md`: The Mini-Research summary in English Markdown.
* `docs/doxygen/`: Doxygen-generated API documentation for the codebase (also published to GitHub Pages).

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

## Work Breakdown Structure

**Legend:**

* `[X]` = Done
* `[~]` = In Progress
* `[ ]` = Open Task

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
    * **Next Step / To-Do:**
      * **[~] Sensor Integration & Payload Population:** (In Progress - Awaiting Verification)
        * **[~] Read Real Sensor Values:** Modify `loop()` to read `potmeter2_test` for battery level and store in `batterySensor`. (Awaiting Verification)
        * **[~] Populate Payload with Real Data:** Update `loop()` to use sensor object states (e.g., `doorSensor.getDoorStatus()`) to populate the `payloadEncoder` instance, replacing `encoder.setTestValues()`. (Awaiting Verification)
  * [~] Implement event-triggered and heartbeat communication.
    * Current `nodeCode.ino` sends data every loop cycle + delay, not based on state changes or `HEARTBEAT_INTERVAL_MS`.
    * **Next Step / To-Do:**
      * **[ ] Track Previous Sensor States:** In `loop()`, store current sensor states before reading new ones.
      * **[ ] Implement Conditional Sending Logic:** Send data if sensor state changed OR heartbeat interval elapsed (using `millis()` and `HEARTBEAT_INTERVAL_MS` from `IOTShieldConfig.h`). Reset heartbeat timer after send.
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
  * **Next Step / To-Do:**
    * **[ ] Review and Add Comments:** Go through `nodeCode.ino` and related headers (`doorSensor.h`, `catchSensor.h`, `displacementSensor.h`, `batterySensor.h`, `encoder.h`, `decoder.h`, `IOTShieldConfig.h`), adding Doxygen-style comments.
* **[ ] Code Cleanup & Refinement (Optional):**
  * **[X] Remove `encoder.setTestValues()`:** After implementing real sensor data population. (Done as part of previous step)
  * **[ ] Review/Remove `knightRider()`:** Decide on its necessity.
  * **[ ] Review/Remove `iotShieldTempSensor`:** Decide on its necessity.
  * **[ ] Consistent Debug Messages:** Ensure clarity and usefulness.

#### Server-Side (`serverSide/`)

* [X] (II.A) Finalize Database Design and Implementation (MySQL).
  * [X] Configured MariaDB to automatically import `serverSide/databaseSetup.sql` on initial startup.
* [X] (II.B) Implement Node-RED flows for TTN data reception and MySQL storage.
  * Current Focus: Setting up Node-RED to receive data from The Things Network (TTN) and store it in a MySQL database.
  * Sub-tasks:
    * `[X] Start Docker Compose stack (if not already running).`
    * `[X] Add TTN and MySQL environment variables to Node-RED service in \`docker-compose.yml\`.`
    * `[X] Refactor Node-RED environment variables to use an external \`.env\` file (\`serverSide/.env\`) and apply to all services.`
    * `[X] Reset corrupted \`flows_cred.json\` to resolve credential loading error.`
    * `[X] **Action Required:** Update placeholder values for TTN & MySQL credentials in \`serverSide/.env\`. (User confirmed completion)`
    * `[X] Configure Node-RED TTN integration (decoder already done, ensure TTN application is configured with the decoder).`
      * `[X] Confirm TTN application created and decoder function (\\\\`serverSide/javascriptDecoder/decoder.js\\\\`) added to the TTN application\\\'s payload formatters. (User confirmed completion)`
      * `[X] Obtain TTN Application ID (TTN_APP_NAME, TTN_APP_KEY_PASSWORD in serverSide/.env)`
      * `[X] Add and configure MQTT input node in Node-RED.`
        * The `flows.json` was updated to hardcode `broker` ("eu1.cloud.thethings.network") and `port` ("1883") from \`.env\` due to editor limitations in referencing environment variables for these specific fields.
        * **(User Confirmed Completion - 2025-06-08):** Manually configure the MQTT broker node ("muskrattrap@ttn") credentials in the Node-RED editor. In the "Security" tab of the broker configuration, set "Username" and "Password" fields, preferably using the "Environment Variable" input type if available for credentials, to reference `TTN_APP_NAME` and `TTN_APP_KEY_PASSWORD`. If "Environment Variable" type is not available for credentials, try `{{TTN_APP_NAME}}` and `{{TTN_APP_KEY_PASSWORD}}` or, as a last resort, enter the literal values.
    * `[X] Configure Node-RED MySQL connection.`
      * The `flows.json` was updated to hardcode `host` ("mariadb"), `port` ("3306"), `db` ("muskrattrap_db"), and `tz` ("Europe/Amsterdam") from \`.env\` due to editor limitations.
      * **(User Confirmed Completion - 2025-06-08):** Manually configure the MySQL database node ("mariadb") credentials in the Node-RED editor. Set the "User" and "Password" fields.
        * For "User", use the value of the `MYSQL_USER` environment variable (which is `mysql_user`).
        * For "Password", use the value of the `MYSQL_PASSWORD` environment variable (which is `mysql_password`).
        * If the Node-RED editor allows referencing environment variables for credentials, use `MYSQL_USER` and `MYSQL_PASSWORD`. Otherwise, use the literal values.
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
* [X] Implement Grafana Dashboard.
  * [X] Configure Grafana data source provisioning (Verified via MCP tool, MySQL datasource `deodcfz2cewhsd` is available)
  * [X] Create initial Grafana dashboard for MuskratTrap (`MuskratTrap Overview`, UID `0520bd8f-87c6-4e91-9360-bb66843c3cd8`)
    * [X] Add panels for `trap_data` (active catches, door status, battery levels) - Added "Trap Data Overview" table panel.
  * [X] Implement alerts in Grafana for significant events
    * [X] Set up Grafana alert provisioning structure (`serverSide/grafana/provisioning/`).
    * [X] Added `alerting_config.yml` to define alert providers.
    * [X] Updated `docker-compose.yml` to mount provisioning directories.
    * [X] Created initial "TrapCatchDetected" alert rule in `serverSide/grafana/provisioning/alerting/catch_detected_alert.yml`.
    * [X] Created "TrapLowBattery" alert rule in `serverSide/grafana/provisioning/alerting/low_battery_alert.yml`.
    * [X] Created "TrapDisplaced" alert rule in `serverSide/grafana/provisioning/alerting/trap_displaced_alert.yml`.
    * [X] Created "TrapOffline" alert rule in `serverSide/grafana/provisioning/alerting/trap_offline_alert.yml`.
    * [X] All Grafana dashboard and alert configuration tasks are now considered complete.

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

## Progress Tracker

### In Progress
- Verify sensor integration and payload population via serial monitor output.
- Address `printPayloadEncoded()` in `encoder.cpp/h` (implement or remove).
- Implement event-triggered and heartbeat communication in `nodeCode.ino`.
- Add/review Doxygen comments for all relevant files.
- Code cleanup & refinement (optional).

### Done
- VS Code task: LoRaWAN Node: Compile, Flash & Monitor (Debug) (now working, see Design Notes)
- Sensor data integration in `nodeCode.ino` (pending verification)
- Task output redirection to `.vscode/task_output.log`
- Arduino CLI upload errors resolved (see Design Notes)

## Design Notes & Rationale

- **OS/Shell:** macOS, default shell: bash. All shell commands and scripts are written for this environment.
- **Arduino Leonardo Upload:** The correct way to upload is to use `arduino-cli upload -p <port> --fqbn arduino:avr:leonardo ...` without specifying a programmer. The Leonardo bootloader is auto-detected; specifying `-P avr109` is not supported by `arduino-cli` and causes errors. This matches Arduino IDE behavior and is now confirmed to work.
- **Debugging Approach:** Used `.vscode/task_output.log` and `tail` for efficient log analysis, as required by project policy.
- **Sensor Integration:** Real sensor data is now read and encoded in the LoRaWAN payload. Awaiting verification via serial monitor.

## Replication Guide

1. Install Arduino CLI and dependencies (see below).
2. Use VS Code and run the task: "LoRaWAN Node: Compile, Flash & Monitor (Debug)".
3. Monitor `.vscode/task_output.log` for build/upload status.
4. Use the serial monitor for runtime output.

**Dependencies:**
- Arduino CLI (macOS, tested with bash)
- Board: Arduino Leonardo (`arduino:avr:leonardo`)
- All required libraries are listed in the project and should be installed via Arduino CLI or Library Manager.

---

(For further details, see previous tracker entries and code comments.)
