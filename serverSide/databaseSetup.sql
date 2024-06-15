SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";

CREATE TABLE `muskrattrap` (
  `autoIncrement` bigint(20) UNSIGNED ZEROFILL NOT NULL,
  `UUID` uuid NOT NULL DEFAULT uuid(),
  `messageSource` varchar(32) DEFAULT NULL COMMENT 'e.g. TTNV3',
  `dateTime` datetime DEFAULT NULL,
  `devID` varchar(32) DEFAULT NULL,
  `appEUI` char(16) DEFAULT NULL COMMENT '64 bit application identifier',
  `devEUI` char(16) DEFAULT NULL COMMENT '64 bit end-device identifier',
  `fcnt` int(11) UNSIGNED DEFAULT NULL COMMENT 'Frame counter ensuring message integrity',
  `port` tinyint(3) UNSIGNED DEFAULT NULL COMMENT 'Application-specific data type identifier',
  `devAddr` char(8) DEFAULT NULL COMMENT '32 bit device address',
  `frequency` float DEFAULT NULL,
  `sf` tinyint(3) UNSIGNED DEFAULT NULL,
  `batteryStatus` tinyint(3) UNSIGNED DEFAULT NULL,
  `catchDetect` tinyint(1) DEFAULT NULL COMMENT 'Boolean',
  `doorStatus` tinyint(1) DEFAULT NULL COMMENT 'Boolean',
  `trapDisplacement` tinyint(1) DEFAULT NULL COMMENT 'Boolean',
  `id` int(11) DEFAULT NULL COMMENT 'as reported by the node',
  `unixTime` int(11) DEFAULT NULL COMMENT 'unixTime',
  `version` tinyint(3) UNSIGNED DEFAULT NULL COMMENT 'payload version'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

ALTER TABLE `muskrattrap`
  ADD PRIMARY KEY (`autoIncrement`);

ALTER TABLE `muskrattrap`
  MODIFY `autoIncrement` bigint(20) UNSIGNED ZEROFILL NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=30;
COMMIT;
