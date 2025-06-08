# Server-Side and Node-RED Setup for SMARTrap

This document details the server-side infrastructure, database setup, and Node-RED configuration for the SMARTrap project.

## Chapter 1: Hosting Stack

The SMARTrap project utilizes a containerized server environment for portability and ease of administration.

### 1.1 Core Technologies
The server environment is built upon the following open-source projects:
-   **Docker:** For containerization of services.
-   **Docker Compose:** For orchestrating multi-container Docker applications.
-   **Node-RED:** For visual programming of IoT flows, data processing, and TTN integration.
-   **MariaDB (MySQL compatible):** As the primary database for storing trap data.
-   **Grafana:** For data visualization and dashboarding.
-   *(The original documentation mentioned Arch Linux as a base OS, but with Docker, the host OS has less direct impact on the services themselves.)*

### 1.2 Portability
The entire hosting stack is defined within a `docker-compose.yml` file located in the `serverSide/` directory. This allows the environment to run on various platforms, from a Raspberry Pi to larger servers.

### 1.3 Docker Compose Overview
The `serverSide/docker-compose.yml` file defines and configures all the necessary services. Key services typically include:
-   Node-RED
-   MariaDB (or MySQL)
-   phpMyAdmin (for database administration)
-   Grafana

*(For the exact structure and latest version of the Docker Compose file, refer to `serverSide/docker-compose.yml` in the project repository.)*

## Chapter 2: Database Setup

### 2.1 Database Schema
The MariaDB database stores data received from the muskrat traps via The Things Network and Node-RED. The primary table for trap data has a layout similar to the following (refer to `serverSide/databaseSetup.sql` for the definitive schema):

| Column Name        | Data Type                  | Comment                                            |
|--------------------|----------------------------|----------------------------------------------------|
| autoIncrement      | BIGINT(20) UNSIGNED ZEROFILL| Auto-incrementing primary key                      |
| UUID               | UUID                       | Default value generated with `uuid()` function     |
| messageSource      | VARCHAR(32)                | Source of the message (e.g., "TTNV3")              |
| dateTime           | DATETIME                   | Timestamp of data reception/processing             |
| devID              | VARCHAR(32)                | Device ID from TTN                                 |
| appEUI             | CHAR(16)                   | LoRaWAN Application EUI (if applicable)            |
| devEUI             | CHAR(16)                   | LoRaWAN Device EUI                                 |
| fcnt               | INT(11) UNSIGNED           | Frame counter from LoRaWAN message                 |
| port               | TINYINT(3) UNSIGNED        | LoRaWAN FPort                                      |
| devAddr            | CHAR(8)                    | LoRaWAN Device Address                             |
| frequency          | FLOAT                      | Transmission frequency                             |
| sf                 | TINYINT(3) UNSIGNED        | Spreading Factor used for transmission             |
| batteryStatus      | TINYINT(3) UNSIGNED        | Battery level reported by the node (0-255)         |
| catchDetect        | TINYINT(1)                 | Boolean (0 or 1) indicating if a catch was detected|
| doorStatus         | TINYINT(1)                 | Boolean (0 or 1) indicating trap door status       |
| trapDisplacement   | TINYINT(1)                 | Boolean (0 or 1) indicating if trap was moved      |
| id                 | INT(11)                    | Trap's own identification number from payload      |
| unixTime           | INT(11) UNSIGNED           | Unix timestamp from payload                        |
| version            | TINYINT(3) UNSIGNED        | Payload version number from payload                |

*(Note: The exact column names, types, and constraints should always be verified against the `serverSide/databaseSetup.sql` file.)*

### 2.2 Database Initialization
The MariaDB service, as configured in `serverSide/docker-compose.yml`, is typically set up to automatically execute any `*.sql` files found in its `/config/initdb.d/` directory upon its first startup. The project's `serverSide/databaseSetup.sql` script is mapped to this directory, ensuring the database schema and necessary tables are created automatically when the MariaDB container is launched for the first time.

## Chapter 3: Node-RED Setup

Node-RED is used to:
-   Receive data from The Things Network (TTN) via MQTT.
-   Decode the binary LoRaWAN payload using a JavaScript decoder.
-   Process the decoded data.
-   Store the data in the MariaDB database.
-   Potentially provide a UI dashboard for monitoring.

### 3.1 Git Integration with Node-RED (Optional)
If managing Node-RED flows using Git, specific steps are needed within the Node-RED Docker container due to its isolated environment.

**Steps for Git Setup inside the Node-RED Docker container:**

1.  **Access the Docker Container:**
    ```bash
    sudo docker exec -it nodered /bin/bash
    ```
    *(Replace `nodered` with the actual service name from your `docker-compose.yml` if different.)*

2.  **Create SSH Key:** Generate an SSH key pair within the container. Do not set a passphrase if you need unattended Git operations.
    ```bash
    ssh-keygen -t rsa -b 4096 -C "your_email@example.com"
    ```
    *(Store the public key (`~/.ssh/id_rsa.pub`) with your Git provider, e.g., GitHub deploy keys.)*

3.  **Start SSH Agent (Optional, for convenience):**
    ```bash
    eval $(ssh-agent -s)
    ```

4.  **Add SSH Key to Agent (Optional):**
    ```bash
    ssh-add ~/.ssh/id_rsa 
    ```
    *(If you named your key differently, adjust the path.)*

5.  **Configure Git User:**
    ```bash
    git config --global user.name "Your Git Username"
    git config --global user.email "your_email@example.com"
    ```

6.  **Set Upstream URL:** Ensure your Node-RED project (within `/data` in the container) is linked to the correct remote repository.
    ```bash
    # Example:
    # cd /data  (or your Node-RED project directory)
    # git remote set-url origin "git@github.com:your_username/your_nodered_flows_repo.git"
    ```

7.  **Test Git Connection:**
    ```bash
    ssh -T git@github.com 
    # Should show a success message from GitHub.
    # git remote show origin 
    # Should show details of your remote repository.
    ```

These steps are primarily for developers who wish to version control their Node-RED flows directly from within the running container's environment. Standard Node-RED project features for Git integration might offer alternative workflows.

### 3.2 Node-RED Flows
The actual Node-RED flows (typically defined in `flows.json` within the Node-RED data directory, often mapped from `serverSide/nodered/flows.json`) will contain nodes for:
-   **MQTT In:** Subscribing to the appropriate TTN application topic.
-   **Function Node(s):** For decoding the payload (using the JavaScript decoder from `serverSide/javascriptDecoder/decoder.js`), transforming data, and preparing SQL queries.
-   **MySQL Node:** For executing SQL queries to insert data into the MariaDB database.
-   **Dashboard Nodes (ui_table, etc.):** If a Node-RED based UI is implemented.

Refer to the `README.md` and the `serverSide/nodered/flows.json` file for specific details on the current Node-RED flow implementation and credential management (e.g., using `variables.env`).
