---
weight: 5
title: "Current progress"
---
# Current progress

## To Do
This project isn't finished. Main points for finishing this project are as follows:

### payloadCoder
- Input validation of payload data (clip data to outer ranges when out of range).
- Add warning flag for when data is clipping to maximum values

### Grafana
- Add additional visualizations
- Publish dashboard on public internet
- Add alerts for when a muskrat has been trapped.

### Node programming
- Event triggered communication
- Button based sensor simulation
- Sleep implementation for maximum battery life.
- General power usage optimization
- Data transmission optimization. Change interval of data transmission to once every 24 hours.

## Getting started
To continue development, follow these steps:

Clone the github repository:

    git clone git@github.com:jjgroenendijk/muskrattrap.git

To recreate the hosting environment, use docker and docker-compose.

    cd serverSide/docker-compose.yml
    docker-compose up -d

Use the website pages on this website to recreate the setup.

To continue development on The Things Uno, install the Arduino IDE and open file: `nodeCode/nodeCode.ino`.
Make sure to edit file `nodeCode/secrets.example.h` and add your own keys from TTN to this file.
Rename `secrets.example.h` to `secrets.h`.