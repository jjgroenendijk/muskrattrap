# IoT-muskrattrap: The Intelligent Muskrat Trap

## Project Overview
The SMARTrap project aims to develop a smart, humane, and efficient solution for controlling muskrat populations using IoT technology. Muskrats pose a significant threat to water management systems in the Netherlands. This project seeks to create a smart trap that detects trap status (open/closed), identifies captures, monitors trap movement, and reports its health status, all while ensuring non-lethal trapping and enabling remote monitoring.

Detailed project documentation, including design choices, technical specifications, and setup guides, can be found in the `/docs-old` directory. The Mini-Research summary has been converted to English Markdown and is available at `docs/mini-research-summary.md`. Other documents are pending review and migration to the `docs/` directory.

## Environment Setup
*   **Operating System:** macOS
*   **Default Shell:** bash
*   **Python Environment:** (To be determined if Python will be used for new development. If so, `uv` will be used for package management.)

## Technology Stack
*   **IoT Node Hardware:** The Things Uno (Arduino Leonardo based)
*   **Communication:** LoRaWAN (via The Things Network - TTN)
*   **Data Processing & Automation:** Node-RED
*   **Data Storage:** MySQL (MariaDB)
*   **Data Visualization:** Grafana
*   **Server Orchestration:** Docker & Docker Compose

## Replication Guide & Getting Started

### Prerequisites
*   Git
*   Docker
*   Docker Compose
*   Arduino IDE (for node development)

### Initial Setup
1.  Clone the GitHub repository:
    ```bash
    git clone git@github.com:jjgroenendijk/muskrattrap.git
    cd muskrattrap
    ```

### Server-Side Development
1.  Navigate to the server-side directory:
    ```bash
    cd serverSide
    ```
2.  Ensure the `docker-compose.yml` file has a secure password for MariaDB (currently `# change this to a secure password`).
3.  Start the services:
    ```bash
    docker-compose up -d
    ```
4.  **Node-RED TTN Integration:**
    *   Use the JavaScript decoder from `serverSide/javascriptDecoder/decoder.js` and add it to the application decoder in The Things Network console.
    *   For Node-RED Git integration (if needed for flow management):
        *   Access the Node-RED container: `sudo docker exec -it nodered /bin/bash`
        *   Follow the SSH key setup and Git configuration steps outlined in `docs-old/NodeRed/nodeRed.md`.

### Node (The Things Uno) Development
1.  Open the Arduino project: `nodeCode/nodeCode.ino` using the Arduino IDE.
2.  **Configure Secrets:**
    *   Copy `nodeCode/secrets.example.h` to `nodeCode/secrets.h`.
    *   Edit `nodeCode/secrets.h` and add your personal keys from The Things Network (TTN).

## Progress Tracker
*(This section will be updated as tasks are started, completed, or blocked. For a detailed Work Breakdown Structure (WBS) and academic deliverables, please refer to `progress.md`.)*

*   **2025-06-07 19:34 - Initial Setup:** `README.md` structured based on project documentation. Context gathered from `docs-old` directory and `progress.md`. OS: macOS, Shell: bash.

### Key Outstanding Technical Tasks (derived from `docs-old/projectDescription/04-toDo.md` and `progress.md`):

#### Payload Coder (`payloadCoder/` & `examples/payload/MyPayloadEncoderDecoder/`) - Corresponds to `progress.md` item I.B.
*   `[ ]` Implement and test C++ payload encoder/decoder classes.
    *   `[ ]` Ensure compatibility with Cayenne LPP.
    *   `[ ]` Input validation of payload data (clip data to outer ranges when out of range).
    *   `[ ]` Add warning flag for when data is clipping to maximum values.
*   `[ ]` (I.D) Document with Doxygen.

#### LoRaWAN Node (`nodeCode/`) - Corresponds to `progress.md` item I.C.
*   `[ ]` Implement prototype LoRaWAN node on HAN IoT Node.
    *   `[ ]` Emulate sensors using onboard components as per `docs-old/IoTNode/hardwareSimulation.md`.
    *   `[ ]` Implement event-triggered communication.
    *   `[ ]` Implement sleep functionality for maximum battery life.
    *   `[ ]` Optimize general power usage.
    *   `[ ]` Optimize data transmission (e.g., target once every 24 hours for routine updates).
*   `[ ]` (I.D) Document with Doxygen.

#### Server-Side (`serverSide/`)
*   `[ ]` (II.A) Finalize Database Design and Implementation (MySQL).
*   `[ ]` (II.B) Implement Node-RED flows for data reception from TTN, processing, and storage into MySQL.
*   `[ ]` (II.D) Implement JavaScript TTN Payload Decoder.
*   `[ ]` (I.D, II.A.3) Document relevant parts with Doxygen/Markdown.

#### Visualization & Reporting (Grafana & Node-RED UI) - Corresponds to `progress.md` item II.C.
*   `[ ]` Implement Node-RED UI Dashboard.
*   `[ ]` Implement Grafana Dashboard.
    *   `[ ]` Add additional relevant visualizations.
    *   `[ ]` (Optional/Future) Publish dashboard on public internet.
    *   `[ ]` Implement alerts in Grafana for when a muskrat has been trapped.

#### General Documentation & Project Management (Refer to `progress.md` for full list)
*   `[~]` (I.A) Mini-Research Summary:
    *   `[X]` Converted to Markdown (`docs/mini-research-summary.md`), PII removed, and translated to English.
    *   `[X]` Original DOCX (`docs-old/Jaap-Jan Groenendijk LoRaWAN verwerkte feedback.docx`) added to `.gitignore`.
    *   `[ ]` Convert to PDF as per deliverable requirements (I.A.5).
    *   `[ ]` Locate and submit peer review document (I.A.5).
*   `[ ]` (II.E) Create Transfer Documentation.
*   `[ ]` (III.A) Manage Git releases (Release 3 for Period 1, Release 4 for Period 2).
*   `[ ]` (I.D) Ensure all Doxygen documentation is complete and integrated across the project.

#### Documentation Review & Enhancement
*   `[~]` Review content in `docs-old/` and migrate relevant information to a new `docs/` directory. (Mini-Research Summary migrated to `docs/mini-research-summary.md`).
*   `[ ]` Ensure `README.md` appropriately refers to the `docs-old/` directory for current detailed context, and eventually to the new `docs/` directory as content is migrated.

## Design Notes & Rationale
*(This section will document key architectural decisions, technology choices, and learnings, especially those from `context7` if used.)*

*   **LPWAN Choice:** LoRaWAN was selected over NB-IoT and LTE-CAT-M due to its superior energy efficiency, long-range capabilities, cost-effectiveness, scalability, and robustness for remote deployments. (Details: `docs-old/projectDescription/01-LPWANComparison.md`)
*   **LoRaWAN Provider:** The Things Network (TTN) was chosen over KPN LoRa due to its cost transparency, extensive community support and documentation, flexibility in network expansion, open-source nature, and scalability. (Details: `docs-old/projectDescription/02-LoraComparison.md`)
*   **Trap Design:** The trap utilizes magnetic sensors (door), weight sensors (catch detection), and wire-based sensors (movement), along with battery monitoring. (Details: `docs-old/projectDescription/03-trapDesign.md`)
*   **Payload Structure:** The LoRaWAN payload is optimized for size (10 bytes + 3 bits) and includes: ID, version, door status, catch detection, trap displacement, battery status, and Unix timestamp. (Details: `docs-old/IoTNode/payload.md`)
*   **Hardware Simulation:** Onboard buttons and LEDs of the HAN IoT Node (The Things Uno) are used to simulate sensor inputs and status indicators. (Details: `docs-old/IoTNode/hardwareSimulation.md`)
