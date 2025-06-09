# Grading guide

## **Period 1 Portfolio**

### **Mini-Research Summary (Essay)**

* Research different wireless technologies.
  * Investigate at least 4 wireless technologies, including LoRaWAN and NB-IoT.
  * Analyze the key characteristics of each technology (e.g., infrastructure, power consumption, costs, usability) relevant to your chosen use case.
* Write a comparative analysis essay.
  * The essay must be a minimum of 2 and a maximum of 4 pages.
  * Structure the essay with a clear introduction, body, and conclusion.
  * Categorize the researched technologies based on their characteristics.
  * Provide a well-supported recommendation for the best technology for your use case.
  * Use correct APA-style citations for all sources.
* Participate in the peer review process.
  * Submit a draft of your essay for review by a peer.
  * Provide a constructive review for at least one peer's essay.
  * Incorporate the feedback you receive into your final version.
* Finalize and submit the essay.
  * Ensure the final document is saved as a PDF.
  * Add the final essay to your Git repository for submission.

### **Payload Encoder & Decoder**

* Design a payload structure.
  * Define a compact and efficient data structure for your sensor data.
  * Ensure the structure is compatible with the Cayenne Low Power Payload (LPP) format.
* Implement the payload encoder and decoder in C++.
  * Create a C++ class for the encoder to build the payload.
  * Create a C++ class for the decoder to parse the payload.
  * Implement methods for adding different sensor values to the payload.
  * Implement methods for retrieving different sensor values from the payload.
* Develop unit tests.
  * Create a suite of unit tests for both the encoder and decoder.
  * Include tests for successful encoding and decoding.
  * Include tests for edge cases and potential failure scenarios.
* Document the implementation.
  * Create a UML class diagram illustrating the design of your encoder and decoder classes.
  * Write comprehensive Doxygen documentation for the source code.

### **LoRaWAN Node Prototype**

* Design the node's application logic.
  * Select at least two sensors to implement for your use case (emulation is permitted).
  * Design the transmission strategy, considering event-driven and periodic data sending.
  * Ensure the design respects the LoRaWAN duty cycle and The Things Network's Fair Use Policy.
* Implement the node's firmware.
  * Write the application code for the HAN IoT node.
  * Use a blank sketch; do not use the example code as a template.
  * Implement the logic to read (or emulate) sensors.
  * Implement the designed transmission strategy.
* Set up the application in The Things Network (TTN).
  * Create a new application in TTN.
  * Register and configure your physical device within the TTN application.
* Document the prototype.
  * Create detailed documentation for the node's firmware using Doxygen.
  * Include sections on design choices, operation, sensor selection, and how the test program works.

## **Period 2 Portfolio**

### **Backend Implementation**

* Design and implement a database.
  * Design a database schema in the first normal form.
  * The database must be able to store time-series data from all sensors.
  * Create a UML class diagram of the database design.
  * Implement the database using MySQL/MariaDB.
* Develop a Node-RED flow for data processing.
  * Create a flow to subscribe to MQTT messages from your TTN application.
  * Parse the incoming JSON data to extract relevant sensor and metadata.
  * Insert the processed data into the database.
  * Add the exported flow (`.js` file) to your Git repository.
* Implement a TTN payload decoder in Javascript.
  * Write a Javascript function for the TTN console to decode the incoming binary payload.
  * Ensure all sensor values and information are correctly decoded.
  * Add the decoder script (`.js` file) to your Git repository.
* Create a data dashboard.
  * Use Grafana to connect to your database.
  * Create visualizations (e.g., graphs, gauges) to display the sensor data as a time-series.
  * Take screenshots of the final dashboard to include in your portfolio.

### **Transfer Documentation**

* Write a technical hand-over document.
  * The document must provide all necessary instructions for a colleague to rebuild and continue development of the entire project.
  * This includes setting up the hardware, firmware, TTN application, and backend components.
  * The preferred format is Doxygen or Markdown.
  * The document must be an integral part of the Git repository.

### **Final Presentation**

* Prepare a technical demonstration.
  * Create a presentation of approximately 10 minutes.
  * Focus on demonstrating the complete data flow from the physical node to the Grafana dashboard.
  * Be prepared to explain and motivate your technical design choices.
* Deliver the presentation.
  * Perform the live demonstration for the assessor and your peers.
  * Answer questions during the subsequent Q&A session.
