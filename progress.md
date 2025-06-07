# Work Breakdown Structure (WBS) for IoT Deliverables

The overarching deliverable for the IoT course is an Individual Portfolio, which must be maintained as a Git repository on Gitlab (or a similar website offering private repositories). This portfolio serves as comprehensive evidence of a student's skills, capabilities, and future potential. The portfolio is submitted in two distinct parts, corresponding to two releases of the Git repository.

## I. Period 1 Deliverables (Submitted as Git Repository Release 3)

### Legend

* [X]: Done
* [~]: In Progress
* [ ]: To Do

### I.A. Mini-Research Summary

**Description:** A concise, written essay (2-4 pages) that presents a methodical analysis of various wireless technologies within IoT, specifically assessing their suitability for the student's chosen use-case.

**Tasks/Components:**

* [ ] **I.A.1. Research and Source Analysis:**
  * [ ] Conduct a short research (inventory) on at least four wireless technologies, including LoRaWAN networks (The Things Network, KPN) and LPWAN standards (NB-IoT, LTE-Cat-M).
  * [ ] Methodically treat self-chosen or provided sources (describe, summarise, analyse, synthesise) based on a research question.
  * [ ] Identify and justify the core properties of these wireless technologies relevant to the chosen use-case (e.g., infrastructure, energy consumption, costs).
  * [ ] Categorise the selected networks/technologies based on these core properties, supporting the categorisation with cited sources.
* [ ] **I.A.2. Essay Composition:**
  * [ ] Develop an original analysis and/or argumentation based on the researched sources.
  * [ ] Formulate conclusions and, if applicable, define follow-up questions.
  * [ ] Structure the essay with a clear introduction, core chapters, and a conclusion.
  * [ ] Ensure a clear distinction is made between the student's own opinion, the opinions of others, and factual information.
  * [ ] Maintain a pleasant and appropriate writing style for the target audience, adhering to correct Dutch or English language rules.
* [ ] **I.A.3. Formatting and Referencing:**
  * [ ] Ensure the document is between 2 and 4 pages in length.
  * [ ] Apply APA guidelines for referencing sources within the text and for the bibliography.
  * [ ] Limit spelling errors to a maximum of 3 per page.
* [ ] **I.A.4. Peer Review Process:**
  * [ ] Prepare a concept summary for peer review by fellow students.
  * [ ] Participate in the peer-review process by reviewing at least one other student's concept summary.
  * [ ] Utilise Microsoft Word's "Track changes" and "Comments" features for providing feedback.
  * [ ] Incorporate feedback received from peer reviews into the final summary.
* [ ] **I.A.5. Submission:**
  * [ ] Submit the final summary, along with the received peer review, as a PDF file within the Git repository.

**Grading Weight:** 20% of the Period 1 final grade.
**Timeline:** Concept by Week 3. Final submission by Week 5.

### I.B. Payload-Encoder and -Decoder Class with Unit Test

**Description:** The design, implementation, and testing of C++ classes responsible for encoding and decoding sensor data payloads for the LoRaWAN node.

**Tasks/Components:**

* [ ] **I.B.1. Design and Implementation:**
  * [ ] Determine the specific sensors to be used for the chosen use-case, as these will define the payload content.
  * [ ] Implement the payload encoder class, including a constructor that allows specifying buffer size.
  * [ ] Implement the following methods for the encoder: void reset(void), uint8_t getSize(void), uint8_t *getBuffer(void), and setters for adding various sensor values (variables) to the payload.
  * [ ] Implement the payload decoder class, including the methods: void setPayloadSize(uint8_t size) and void setPayload(uint8_t *payload).
  * [ ] Implement getters for the decoder to retrieve and decode sensor values from the payload.
  * [ ] Ensure the payload encoder/decoder is compatible with the Cayenne LPP library.
  * [ ] Plan to reuse the implemented encoder in the LoRaWAN node application.
* [ ] **I.B.2. Unit Testing:**
  * [ ] Develop comprehensive unit tests for both the payload encoder and decoder classes.
  * [ ] Include test cases that intentionally fail to demonstrate robust testing.
  * [ ] Design and execute relevant and edge test cases to ensure functionality under various conditions.
* [ ] **I.B.3. Documentation (Doxygen):**
  * [ ] Generate UML class diagrams representing the design of the encoder and decoder classes.
  * [ ] Document the program code (encoder/decoder classes) and payload composition using Doxygen format.
  * [ ] Create a dedicated .dox documentation file within the Git repository, including design choices, the composition of the payload, and the class diagram.
  * [ ] Annotate all source code files, variables, defines, functions, and classes with Doxyblocks and Doxygen tags.

**Grading Weight:** 30% of the Period 1 final grade.
**Timeline:** Submitted by Week 8.

### I.C. Prototype LoRaWAN Node Realization

**Description:** The development and implementation of a functional prototype LoRaWAN node using the provided HAN IoT node, with sensors emulated through the onboard components.

**Tasks/Components:**

* [ ] **I.C.1. Use Case Analysis and Application Design:**
  * [ ] Thoroughly study the chosen use case to understand its requirements and functionalities.
  * [ ] Design the IoT application for the node based on the use case.
  * [ ] Select the necessary sensors for the application and provide a clear motivation for their choice in the documentation.
* [ ] **I.C.2. Node Implementation:**
  * [ ] Implement two or more emulated sensors in the HAN IoT node. Use the available buttons, potentiometers, and LEDs on the board to simulate sensor readings and act as a user interface.
  * [ ] Develop a strategy for sending data via LoRaWAN, distinguishing between event-driven and periodic information transmission.
  * [ ] Ensure the transmission strategy adheres to applicable Duty Cycle and/or Fair Use Policy (FUP) limitations.
  * [ ] Write the program code for the node (sketch and additional source files) starting from a blank sketch, without using example code as a template.
* [ ] **I.C.3. The Things Network (TTN) Application Setup:**
  * [ ] Create an application within The Things Network (TTN) console, assigning appropriate names.
  * [ ] Register and configure the prototype nodes within the created TTN application.
* [ ] **I.C.4. Documentation (Doxygen):**
  * [ ] Document the entire node application within the Git repository using Doxygen format.
  * [ ] Create a dedicated .dox documentation file that includes:
    * [ ] The design choices underlying the implementation.
    * [ ] A detailed explanation of the node's operation.
    * [ ] The chosen sensors and their justification.
    * [ ] The method used to emulate the sensors.
    * [ ] The operation of the test program used to demonstrate the use-case functions.
  * [ ] Comment the application code in the Git repository using Doxygen tags.

**Grading Weight:** 40% of the Period 1 final grade.
**Timeline:** Program code of the node submitted by Week 11.

### I.D. Doxygen Documentation (Integrated Deliverable)

**Description:** This is an overarching deliverable, integrated throughout the project, requiring all code and project documentation to be meticulously maintained in Doxygen format. This ensures comprehensive, consistent, and navigatable documentation.

**Tasks/Components:**

* [ ] **I.D.1. Doxygen Environment Setup:**
  * [ ] Install Doxygen software on the development machine.
  * [ ] Install Graphviz, which Doxygen uses to generate diagrams (e.g., class, dependency, inheritance).
  * [ ] Configure Doxywizzard (Doxygen's graphical front-end) to define project settings, source directories, output format (HTML preferred), and diagram generation.
  * [ ] Set up a logical folder structure for storing Doxygen documentation within the project.
* [ ] **I.D.2. General Project Documentation:**
  * [ ] Create a mainpage.dox file as the main entry point for the documentation, including the project title and introductory sections.
  * [ ] Use Doxyblocks (special comment blocks) to encapsulate Doxygen-compatible mark-up text throughout the project for structured documentation.
  * [ ] Apply Markdown language for formatting documentation pages, including multi-level headers, bullet lists, and simple tables.
* [ ] **I.D.3. Code-Level Documentation (Annotation):**
  * [ ] Annotate all source code files (e.g., .c, .cpp, .h, .hpp, .dox) with Doxyblocks and specific Doxygen tags.
  * [ ] For each file, include \file, \brief (short description of functions), \date, \author, and \version tags.
  * [ ] Document variables using \var and \brief for their purpose.
  * [ ] Document functions using \fn, \brief (short description), \param (for each parameter with its name and description), \return (description of return value), \pre (optional precondition), and \post (optional postcondition) tags.
  * [ ] Document structures (\struct), unions (\union), enumeration types (\enum), and classes (\class) with their respective tags.
  * [ ] Utilise \todo and \bug tags to track work in progress, planned features, or identified bugs within the code.

**Grading Weight:** 10% of the Period 1 final grade.
**Timeline:** This is integrated throughout the development of the Payload-Encoder/-Decoder and Node Prototype, with specific check-ins aligned with those deliverables.

## II. Period 2 Deliverables (Submitted as Git Repository Release 4)

### II.A. Database Design and Implementation

**Description:** The design and implementation of a database solution tailored to the chosen use case, ensuring it is in the first normal form and capable of storing time-series sensor data.

**Tasks/Components:**

* [ ] **II.A.1. Database Design:**
  * [ ] Identify all the necessary information from the sensors and application that needs to be stored in the database.
  * [ ] Determine appropriate data types for each piece of information.
  * [ ] Identify unique identifiers and define primary keys for tables.
  * [ ] Design the database schema, ensuring it adheres to the first normal form to minimise redundancy and potential issues.
  * [ ] Create a UML class diagram to visually represent the designed database structure.
  * [ ] Plan the naming conventions for the database and its tables.
* [ ] **II.A.2. Database Implementation:**
  * [ ] Install and configure a LAMP (Linux Apache MySQL PHP) server on a Raspberry Pi, with a focus on setting up the MySQL database component.
  * [ ] Access and manage the MySQL installation via PHPMyAdmin.
  * [ ] Create the database and a dedicated user with necessary permissions for database creation and management.
  * [ ] Implement the designed tables and their structures within MySQL.
* [ ] **II.A.3. Documentation (Doxygen):**
  * [ ] Document the database design and implementation in a dedicated .dox Doxygen file.
  * [ ] Include the design choices that informed the database structure.
  * [ ] Embed the UML class diagram of the designed database within this documentation.

**Grading Weight:** Equal weight with other Period 2 assignments.
**Timeline:** Part of "Back-end assignment and transfer documentation" submitted by Week 17.

### II.B. Node-RED Flow Design and Implementation

**Description:** Development of a Node-RED flow to serve as the backend for the IoT application, handling data reception, processing, and storage from The Things Network.

**Tasks/Components:**

* [ ] **II.B.1. Node-RED Environment Preparation:**
  * [ ] Install Node-RED on a Raspberry Pi, configuring it for auto-start.
  * [ ] Secure the Node-RED installation by setting an administrator password.
  * [ ] Configure projects within the Node-RED environment for organised development.
  * [ ] Install any required UI-nodes within the Node-RED palette for dashboarding capabilities.
* [ ] **II.B.2. Flow Development:**
  * [ ] Design and implement a Node-RED flow that receives data from the application configured in The Things Network (TTN). This will primarily involve using MQTT nodes to subscribe to data topics from TTN.
  * [ ] Implement data processing logic within the flow to extract relevant sensor information and metadata received from TTN's JSON data structure.
  * [ ] Integrate the flow with the previously designed database to store the processed sensor data. This involves using database nodes (e.g., MySQL nodes) to insert data.
  * [ ] Develop a separate, second flow in Node-RED specifically dedicated to creating a dashboard for the use-case.
* [ ] **II.B.3. Submission:**
  * [ ] Export the Node-RED flow(s) as ASCII .js files and include them in the Git repository for the portfolio.

**Grading Weight:** Equal weight with other Period 2 assignments.
**Timeline:** Part of "Back-end assignment and transfer documentation" submitted by Week 17.

### II.C. Dashboard Implementation (Node-RED UI & Grafana)

**Description:** The creation of visual dashboards using both Node-RED's built-in UI and Grafana to present the collected and stored sensor data effectively.

**Tasks/Components:**

* [ ] **II.C.1. Node-RED UI Dashboard Development:**
  * [ ] Design and implement a user interface dashboard directly within Node-RED, displaying key data related to the use-case.
* [ ] **II.C.2. Grafana Setup and Dashboard Creation:**
  * [ ] Install Grafana on the Raspberry Pi where the database and Node-RED are running.
  * [ ] Configure Grafana to connect to the MySQL database containing the sensor data.
  * [ ] Design and implement a comprehensive Grafana dashboard to visualise the stored data, including sensor readings and health-state information of the nodes.
* [ ] **II.C.3. Submission:**
  * [ ] Include screenshots of the functional Grafana dashboard in the portfolio.

**Grading Weight:** Equal weight with other Period 2 assignments.
**Timeline:** Part of "Back-end assignment and transfer documentation" submitted by Week 17.

### II.D. TTN Payload Decoder Implementation (JavaScript)

**Description:** Development of a JavaScript function to decode the LoRaWAN payload directly within The Things Network (TTN) console, making sensor data readable for downstream applications.

**Tasks/Components:**

* [ ] **II.D.1. Decoder Development:**
  * [ ] Write a JavaScript payload formatter (decoder) according to The Things Industries' specifications for payload formatters.
  * [ ] Ensure the decoder correctly interprets and extracts all sensor values and information transmitted by the LoRaWAN node.
  * [ ] Leverage and adapt the existing C++ payload decoder code developed in Period 1 for this JavaScript implementation where applicable.
* [ ] **II.D.2. Submission:**
  * [ ] Add the JavaScript payload decoder code as an ASCII file with a .js extension to the portfolio.

**Grading Weight:** Equal weight with other Period 2 assignments.
**Timeline:** Part of "Back-end assignment and transfer documentation" submitted by Week 17.

### II.E. Transfer Documentation

**Description:** Creation of a concise, technically-oriented document designed to facilitate the handover of the developed application, enabling a colleague to rebuild and further develop the system.

**Tasks/Components:**

* [ ] **II.E.1. Document Content Creation:**
  * [ ] Compile a document containing all necessary instructions and guidelines for a colleague to reconstruct the entire developed IoT application.
  * [ ] Focus on technical details essential for seamless knowledge transfer and future development efforts.
* [ ] **II.E.2. Formatting and Inclusion:**
  * [ ] Prepare the document, with Doxygen or Markdown language preferred, although a Word document is acceptable.
  * [ ] Ensure the document is an integral part of the Git repository.

**Grading Weight:** Equal weight with other Period 2 assignments.
**Timeline:** Part of "Back-end assignment and transfer documentation" submitted by Week 17.

### II.F. Technical Presentation

**Description:** A culminating presentation and live demonstration of the complete IoT solution, from the sensor node to the visual dashboards, with a focus on justifying design decisions.

**Tasks/Components:**

* [ ] **II.F.1. Presentation Preparation:**
  * [ ] Create presentation slides that are simple and clear, prioritising visual figures over extensive text or source code.
  * [ ] Structure the presentation to last approximately 10 minutes.
  * [ ] Prepare to articulate and justify all design choices made throughout the project.
* [ ] **II.F.2. Live Demonstration:**
  * [ ] Conduct a live demonstration showcasing the full functionality of the implemented IoT application, from the LoRaWAN node sending data, through its processing in The Things Network and Node-RED, and finally its visualisation on the Grafana dashboard.
* [ ] **II.F.3. Q&A Session:**
  * [ ] Be ready to answer questions posed by the evaluators and audience following the presentation.

**Grading Weight:** Equal weight with other Period 2 assignments.
**Timeline:** Final presentation takes place in Week 18.

## III. General Project Management & Overarching Tasks

### III.A. Git Repository Management

**Description:** Establishing and consistently maintaining the Git repository as the central hub for version control and submission of all project deliverables.

**Tasks/Components:**

* [ ] **III.A.1. Repository Setup:**
  * [ ] Create a Gitlab account (or an account on a comparable platform offering private repositories).
  * [ ] Initialise and configure a new Git repository specifically for the IoT portfolio.
* [ ] **III.A.2. Version Control Practices:**
  * [ ] Regularly commit changes to the repository, ensuring detailed and descriptive commit messages.
  * [ ] Push local changes to the remote Gitlab repository frequently to maintain an up-to-date backup.
  * [ ] Grant the instructor "Reporter" access to the repository.
* [ ] **III.A.3. Release Management:**
  * [ ] Create "Release 3" of the Git repository for the Period 1 submission, ensuring it contains the mini-research summary, the payload-encoder/-decoder, and the prototype LoRaWAN node deliverables.
  * [ ] Create "Release 4" of the Git repository for the Period 2 submission, including all remaining assignments (database, Node-RED flows, dashboards, TTN decoder, transfer documentation).

### III.B. Use Case Selection and Registration

**Description:** The process of selecting an individual use-case that will serve as the foundation for the entire project's development and formally registering it with the instructor.

**Tasks/Components:**

* [ ] **III.B.1. Use Case Review:**
  * [ ] Examine the available use cases provided for the course (e.g., Beehive, Electric fence monitoring, Flex desk management, Boat flooding detection, Initiate predictive maintenance, Pest control, Garbage bin monitor, Radiation measurement, Rainwater buffering, Smart Forest Fire Alarm, MTB-routeteller).
* [ ] **III.B.2. Selection and Formalisation:**
  * [ ] Choose one individual use-case from the provided list.
  * [ ] Register the chosen use-case with the course instructor for approval.

### III.C. Software & Hardware Setup

**Description:** The installation of all required software and the acquisition and configuration of specific hardware platforms necessary for the development, testing, and deployment of the IoT solution.

**Tasks/Components:**

* [ ] **III.C.1. Software Installation:**
  * [ ] Install TortoiseGit for Git integration.
  * [ ] Install Arduino IDE for node programming.
  * [ ] Install Visual Studio Code for general development.
  * [ ] Install Doxygen for code documentation generation.
  * [ ] Install Paho MQTT-Spy for MQTT message analysis.
  * [ ] Install Virtual Box and import the "IoT Virtual machine" for development environment consistency.
  * [ ] Install Node-RED on the Raspberry Pi.
  * [ ] Install LAMP (Linux, Apache, MySQL, PHP) stack on the Raspberry Pi, specifically for the database.
  * [ ] Install Grafana on the Raspberry Pi for data visualisation.
* [ ] **III.C.2. Hardware Management:**
  * [ ] Obtain the necessary hardware, including the HAN IoT node and The Things Indoor Gateway (TTIG), either through loan from the course or by using compatible personal hardware.
  * [ ] Perform initial testing and commissioning of the provided hardware.
* [ ] **III.C.3. Account Creation & Configuration:**
  * [ ] Create a user account for The Things Network (TTN).
  * [ ] Ensure the TTN user ID is provided to the instructor so they can add it as a collaborator to the TTN organisation.
  * [ ] Create an account for Cayenne.
  * [ ] Create an account on OpenWeatherMap and obtain an API key for potential use with external data sources.

### III.D. Continuous Learning and Interaction

**Description:** Active engagement with course materials, lectures, and instructors to foster deep understanding, problem-solving, and continuous improvement throughout the project lifecycle.

**Tasks/Components:**

* [ ] **III.D.1. Flipped Classroom Engagement:**
  * [ ] Before Lessons: Proactively study theoretical topics, review provided lesson materials (documentation, exercises), and prepare specific questions for in-class discussion.
  * [ ] During Lessons: Participate in class discussions, seek clarification on theoretical concepts, and work on practical exercises and assignments.
  * [ ] After Lessons: Consolidate learning by reviewing notes, practising exercises, and taking weekly formative assessments.
* [ ] **III.D.2. Regular Consultation:**
  * [ ] Engage with lecturers on a weekly basis to discuss project requirements, design challenges, and progress to ensure alignment and receive timely feedback.
* [ ] **III.D.3. Responsible Disclosure:**
  * [ ] Actively provide feedback to the author of the course materials by sharing experiences, problems, errors, or suggestions to contribute to the continuous improvement of the course content.
