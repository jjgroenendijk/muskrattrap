---
weight: 3
title: "Database setup"
---

## Database layout
The database layout is as follows:

| Name            | Data Type                  | Comment                                   |
|-----------------|----------------------------|-------------------------------------------|
| autoIncrement   | bigint(20) UNSIGNED ZEROFILL |                                           |
| UUID            | uuid                       | Default value is generated with uuid()    |
| messageSource   | varchar(32)                | e.g. TTNV3                                |
| dateTime        | datetime                   |                                           |
| devID           | varchar(32)                |                                           |
| appEUI          | char(16)                   | 64 bit application identifier             |
| devEUI          | char(16)                   | 64 bit end-device identifier              |
| fcnt            | int(11) UNSIGNED           | Frame counter ensuring message integrity  |
| port            | tinyint(3) UNSIGNED        | Application-specific data type identifier |
| devAddr         | char(8)                    | 32 bit device address                     |
| frequency       | float                      |                                           |
| sf              | tinyint(3) UNSIGNED        |                                           |
| batteryStatus   | tinyint(3) UNSIGNED        |                                           |
| catchDetect     | tinyint(1)                 | Boolean                                   |
| doorStatus      | tinyint(1)                 | Boolean                                   |
| trapDisplacement| tinyint(1)                 | Boolean                                   |
| id              | int(11)                    | as reported by the node                   |
| unixTime        | int(11)                    | unixTime                                  |
| version         | tinyint(3) UNSIGNED        | payload version                           |

## Database setup
The database is initialized with the following command:
<iframe frameborder="0" scrolling="no" style="width:100%; height:751px;" allow="clipboard-write" src="https://emgithub.com/iframe.html?target=https%3A%2F%2Fgithub.com%2Fjjgroenendijk%2Fmuskrattrap%2Fblob%2Fmain%2FserverSide%2FdatabaseSetup.sql&style=github&type=code&showBorder=on&showLineNumbers=on&showFileMeta=on&showCopy=on"></iframe>
