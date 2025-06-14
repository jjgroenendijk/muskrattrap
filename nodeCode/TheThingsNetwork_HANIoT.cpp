/*--------------------------------------------------------------------
  This file is part of the HAN IoT shield library.

  This code is free software: Use of this source code is governed by the
  MIT license that can be found in the LICENSE file.
  Original Copyright © 2017 The Things Network

  The program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  --------------------------------------------------------------------*/
/*!
 * \file TheThingsNetwork_HANIoT.cpp
 * \brief Implementation of the TheThingsNetwork_HANIoT class for LoRaWAN communication.
 * \author Remko Welling (remko.welling@han.nl)
 *
 * This file provides the implementation for the TheThingsNetwork_HANIoT class,
 * which facilitates communication with LoRaWAN modules (e.g., RN2483)
 * connected to the HAN IoT Shield. It handles command sending, response parsing,
 * and data exchange with The Things Network or other LoRaWAN networks.
 */
 
#include "TheThingsNetwork_HANIoT.h"

/**
 * \def debugPrintLn(...)
 * \brief Macro for printing a line to the debug stream, if available.
 * Appends a newline character at the end.
 */
#define debugPrintLn(...)                \
  {                                      \
    if (debugStream)                     \
      debugStream->println(__VA_ARGS__); \
  }

/**
 * \def debugPrint(...)
 * \brief Macro for printing to the debug stream, if available.
 * Does not append a newline character.
 */
#define debugPrint(...)                \
  {                                    \
    if (debugStream)                   \
      debugStream->print(__VA_ARGS__); \
  }

/**
 * \def TTN_HEX_CHAR_TO_NIBBLE(c)
 * \brief Converts a hexadecimal character ('0'-'9', 'A'-'F') to its nibble value (0-15).
 */
#define TTN_HEX_CHAR_TO_NIBBLE(c) ((c >= 'A') ? (c - 'A' + 0x0A) : (c - '0'))

/**
 * \def TTN_HEX_PAIR_TO_BYTE(h, l)
 * \brief Converts a pair of hexadecimal characters (high and low nibble) to a byte.
 */
#define TTN_HEX_PAIR_TO_BYTE(h, l) ((TTN_HEX_CHAR_TO_NIBBLE(h) << 4) + TTN_HEX_CHAR_TO_NIBBLE(l))

const char ok[] PROGMEM = "ok";
const char on[] PROGMEM = "on";
const char off[] PROGMEM = "off";
const char accepted[] PROGMEM = "accepted";
const char mac_tx_ok[] PROGMEM = "mac_tx_ok";
const char mac_rx[] PROGMEM = "mac_rx";
const char rn2483[] PROGMEM = "RN2483";

/**
 * \brief Lookup table for common response strings from the LoRaWAN module.
 * Used by `__pgmstrcmp` for efficient string comparison.
 */
const char *const compare_table[] PROGMEM = {ok, on, off, accepted, mac_tx_ok, mac_rx, rn2483};

//#define CMP_OK 0
//#define CMP_ON 1
//#define CMP_OFF 2
//#define CMP_ACCEPTED 3
//#define CMP_MAC_TX_OK 4
//#define CMP_MAC_RX 5
//#define CMP_RN2483 6

#define SENDING "Sending: "
#define SEND_MSG "\r\n"

const char eui[] PROGMEM = "EUI: ";
const char battery[] PROGMEM = "Battery: ";
const char appEui[] PROGMEM = "AppEUI: ";
const char devEui[] PROGMEM = "DevEUI: ";
const char band[] PROGMEM = "Band: ";
const char data_rate[] PROGMEM = "Data Rate: ";
const char rx_delay_1[] PROGMEM = "RX Delay 1: ";
const char rx_delay_2[] PROGMEM = "RX Delay 2: ";
const char version[] PROGMEM = "Version: ";
const char model[] PROGMEM = "Model: ";
const char devaddr[] PROGMEM = "DevAddr: ";

/**
 * \brief Lookup table for strings used in `showStatus()` and other debug messages.
 * These are prefixes for displaying various module parameters.
 */
const char *const show_table[] PROGMEM = {eui, battery, appEui, devEui, band, data_rate, rx_delay_1, rx_delay_2, version, model, devaddr};

#define SHOW_EUI 0
#define SHOW_BATTERY 1
#define SHOW_APPEUI 2
#define SHOW_DEVEUI 3
#define SHOW_BAND 4
#define SHOW_DATA_RATE 5
#define SHOW_RX_DELAY_1 6
#define SHOW_RX_DELAY_2 7
#define SHOW_VERSION 8
#define SHOW_MODEL 9
#define SHOW_DEVADDR 10

const char invalid_sf[] PROGMEM = "Invalid SF";
const char invalid_fp[] PROGMEM = "Invalid frequency plan";
const char unexpected_response[] PROGMEM = "Unexpected response: ";
const char send_command_failed[] PROGMEM = "Send command failed";
const char join_failed[] PROGMEM = "Send join command failed";
const char join_not_accepted[] PROGMEM = "Join not accepted: ";
const char personalize_not_accepted[] PROGMEM = "Personalize not accepted";
const char response_is_not_ok[] PROGMEM = "Response is not OK: ";
const char error_key_length[] PROGMEM = "One or more keys are of invalid length.";
const char check_configuration[] PROGMEM = "Check your coverage, keys and backend status.";

/**
 * \brief Lookup table for error messages.
 * Used by `debugPrintMessage` to provide descriptive error information.
 */
const char *const error_msg[] PROGMEM = {invalid_sf, invalid_fp, unexpected_response, send_command_failed, join_failed, join_not_accepted, personalize_not_accepted, response_is_not_ok, error_key_length, check_configuration};

//#define ERR_INVALID_SF 0
//#define ERR_INVALID_FP 1
//#define ERR_UNEXPECTED_RESPONSE 2
//#define ERR_SEND_COMMAND_FAILED 3
//#define ERR_JOIN_FAILED 4
//#define ERR_JOIN_NOT_ACCEPTED 5
//#define ERR_PERSONALIZE_NOT_ACCEPTED 6
//#define ERR_RESPONSE_IS_NOT_OK 7
//#define ERR_KEY_LENGTH 8
//#define ERR_CHECK_CONFIGURATION 9

const char personalize_accepted[] PROGMEM = "Personalize accepted. Status: ";
const char join_accepted[] PROGMEM = "Join accepted. Status: ";
const char successful_transmission[] PROGMEM = "Successful transmission";
const char successful_transmission_received[] PROGMEM = "Successful transmission. Received ";

/**
 * \brief Lookup table for success messages.
 * Used by `debugPrintMessage` to confirm successful operations.
 */
const char *const success_msg[] PROGMEM = {personalize_accepted, join_accepted, successful_transmission, successful_transmission_received};

//#define SCS_PERSONALIZE_ACCEPTED 0
//#define SCS_JOIN_ACCEPTED 1
//#define SCS_SUCCESSFUL_TRANSMISSION 2
//#define SCS_SUCCESSFUL_TRANSMISSION_RECEIVED 3

const char radio_prefix[] PROGMEM = "radio";
const char radio_set[] PROGMEM = "set";
const char radio_get[] PROGMEM = "get";
const char radio_get_bw[] PROGMEM = "bw";
const char radio_get_prlen[] PROGMEM = "prlen";
const char radio_get_crc[] PROGMEM = "crc";
const char radio_get_cr[] PROGMEM = "cr";
const char radio_get_sf[] PROGMEM = "sf";

/**
 * \brief Lookup table for "radio" command strings.
 * These are parts of commands sent to the LoRaWAN module related to radio configuration.
 */
const char *const radio_table[] PROGMEM = {radio_prefix, radio_set, radio_get, radio_get_bw, radio_get_prlen, radio_get_crc, radio_get_cr, radio_get_sf};

//#define RADIO_PREFIX 0
//#define RADIO_SET 1
//#define RADIO_GET 2
//#define RADIO_GET_BW 3
//#define RADIO_GET_PRLEN 4
//#define RADIO_GET_CRC 5
//#define RADIO_GET_CR 6
//#define RADIO_GET_SF 7

const char sys_prefix[] PROGMEM = "sys";
const char sys_sleep[] PROGMEM = "sleep";
const char sys_reset[] PROGMEM = "reset";
const char sys_erase_fw[] PROGMEM = "eraseFW";
const char sys_factory_rst[] PROGMEM = "factoryRESET";
const char sys_set[] PROGMEM = "set";
const char sys_get[] PROGMEM = "get";
const char sys_get_ver[] PROGMEM = "ver";
const char sys_get_vdd[] PROGMEM = "vdd";
const char sys_get_hweui[] PROGMEM = "hweui";
const char sys_set_get_nvm[] PROGMEM = "nvm";
const char sys_set_pindig[] PROGMEM = "pindig";

/**
 * \brief Lookup table for "sys" command strings.
 * These are parts of commands sent to the LoRaWAN module related to system operations.
 */
const char *const sys_table[] PROGMEM = {sys_prefix, sys_sleep, sys_reset, sys_erase_fw, sys_factory_rst, sys_set, sys_get, sys_get_ver, sys_get_vdd, sys_get_hweui, sys_set_get_nvm, sys_set_pindig};
//
//#define SYS_PREFIX 0
//#define SYS_SLEEP 1
//#define SYS_RESET 2
//#define SYS_ERASE_FW 3
//#define SYS_FACTORY_RST 4
//#define SYS_SET 5
//#define SYS_GET 6
//#define SYS_GET_VER 7
//#define SYS_GET_VDD 8
//#define SYS_GET_HWEUI 9
//#define SYS_SET_GET_NVM 10
//#define SYS_SET_PINDIG 11

const char mac_prefix[] PROGMEM = "mac";
const char mac_reset[] PROGMEM = "reset";
const char mac_tx[] PROGMEM = "tx";
const char mac_join[] PROGMEM = "join";
const char mac_save[] PROGMEM = "save";
const char mac_force_enable[] PROGMEM = "forceENABLE";
const char mac_pause[] PROGMEM = "pause";
const char mac_resume[] PROGMEM = "resume";
const char mac_set[] PROGMEM = "set";
const char mac_get[] PROGMEM = "get";

/**
 * \brief Lookup table for "mac" command strings.
 * These are parts of commands sent to the LoRaWAN module related to MAC layer operations.
 */
const char *const mac_table[] PROGMEM = {mac_prefix, mac_reset, mac_tx, mac_join, mac_save, mac_force_enable, mac_pause, mac_resume, mac_set, mac_get};

//#define MAC_PREFIX 0
//#define MAC_RESET 1
//#define MAC_TX 2
//#define MAC_JOIN 3
//#define MAC_SAVE 4
//#define MAC_FORCE_ENABLE 5
//#define MAC_PAUSE 6
//#define MAC_RESUME 7
//#define MAC_SET 8
//#define MAC_GET 9

const char mac_devaddr[] PROGMEM = "devaddr";
const char mac_deveui[] PROGMEM = "deveui";
const char mac_appeui[] PROGMEM = "appeui";
const char mac_nwkskey[] PROGMEM = "nwkskey";
const char mac_appskey[] PROGMEM = "appskey";
const char mac_appkey[] PROGMEM = "appkey";
const char mac_pwridx[] PROGMEM = "pwridx";
const char mac_dr[] PROGMEM = "dr";
const char mac_adr[] PROGMEM = "adr";
const char mac_bat[] PROGMEM = "bat";
const char mac_retx[] PROGMEM = "retx";
const char mac_linkchk[] PROGMEM = "linkchk";
const char mac_rxdelay1[] PROGMEM = "rxdelay1";
const char mac_rxdelay2[] PROGMEM = "rxdelay2";
const char mac_band[] PROGMEM = "band";
const char mac_ar[] PROGMEM = "ar";
const char mac_rx2[] PROGMEM = "rx2";
const char mac_ch[] PROGMEM = "ch";
const char mac_gwnb[] PROGMEM = "gwnb";
const char mac_mrgn[] PROGMEM = "mrgn";

/**
 * \brief Lookup table for "mac set/get" parameter names.
 * These are specific parameters that can be configured or queried within the MAC layer.
 */
const char *const mac_options[] PROGMEM = {mac_devaddr, mac_deveui, mac_appeui, mac_nwkskey, mac_appskey, mac_appkey, mac_pwridx, mac_dr, mac_adr, mac_bat, mac_retx, mac_linkchk, mac_rxdelay1, mac_rxdelay2, mac_band, mac_ar, mac_rx2, mac_ch, mac_gwnb, mac_mrgn};

//#define MAC_DEVADDR 0
//#define MAC_DEVEUI 1
//#define MAC_APPEUI 2
//#define MAC_NWKSKEY 3
//#define MAC_APPSKEY 4
//#define MAC_APPKEY 5
//#define MAC_PWRIDX 6
//#define MAC_DR 7
//#define MAC_ADR 8
//#define MAC_BAT 9
//#define MAC_RETX 10
//#define MAC_LINKCHK 11
//#define MAC_RXDELAY1 12
//#define MAC_RXDELAY2 13
//#define MAC_BAND 14
//#define MAC_AR 15
//#define MAC_RX2 16
//#define MAC_CH 17
//#define MAC_GWNB 18
//#define MAC_MRGN 19

const char mac_join_mode_otaa[] PROGMEM = "otaa";
const char mac_join_mode_abp[] PROGMEM = "abp";

/**
 * \brief Lookup table for "mac join" modes.
 * Specifies the LoRaWAN join procedure (OTAA or ABP).
 */
const char *const mac_join_mode[] PROGMEM = {mac_join_mode_otaa, mac_join_mode_abp};

//#define MAC_JOIN_MODE_OTAA 0
//#define MAC_JOIN_MODE_ABP 1

const char channel_dcycle[] PROGMEM = "dcycle";
const char channel_drrange[] PROGMEM = "drrange";
const char channel_freq[] PROGMEM = "freq";
const char channel_status[] PROGMEM = "status";

/**
 * \brief Lookup table for "mac set ch" parameter names.
 * These are parameters related to channel configuration.
 */
const char *const mac_ch_options[] PROGMEM = {channel_dcycle, channel_drrange, channel_freq, channel_status};
//
//#define MAC_CHANNEL_DCYCLE 0
//#define MAC_CHANNEL_DRRANGE 1
//#define MAC_CHANNEL_FREQ 2
//#define MAC_CHANNEL_STATUS 3

const char mac_tx_type_cnf[] PROGMEM = "cnf";
const char mac_tx_type_ucnf[] PROGMEM = "uncnf";

/**
 * \brief Lookup table for "mac tx" message types.
 * Specifies whether a transmission is confirmed or unconfirmed.
 */
const char *const mac_tx_table[] PROGMEM = {mac_tx_type_cnf, mac_tx_type_ucnf};

//#define MAC_TX_TYPE_CNF 0
//#define MAC_TX_TYPE_UCNF 1
//
//#define MAC_TABLE 0
//#define MAC_GET_SET_TABLE 1
//#define MAC_JOIN_TABLE 2
//#define MAC_CH_TABLE 3
//#define MAC_TX_TABLE 4
//#define SYS_TABLE 5
//#define RADIO_TABLE 6
//#define ERR_MESSAGE 7
//#define SUCCESS_MESSAGE 8

/**
 * \brief Compares a RAM string with a PROGMEM string from the `compare_table`.
 * This function is used to efficiently compare received response strings
 * from the LoRaWAN module with known expected strings stored in PROGMEM.
 * \param str1 Pointer to the null-terminated string in RAM.
 * \param str2Index Index of the string in the `compare_table` (PROGMEM).
 * \return An integer less than, equal to, or greater than zero if `str1` is found,
 *         respectively, to be less than, to match, or be greater than `str2`.
 *         Comparison is up to the length of the shorter string.
 */
int __pgmstrcmp(const char *str1, uint8_t str2Index)
{
  char str2[128];
  strcpy_P(str2, (char *)pgm_read_word(&(compare_table[str2Index])));
  return memcmp(str1, str2, min(strlen(str1), strlen(str2)));
}

/**
 * \brief Calculates the number of digits in a port number.
 * Helper function to determine the length of the port number string when parsing
 * downlink messages. Assumes port numbers are between 0 and 255.
 * \param port The port number.
 * \return The number of digits (1, 2, or 3).
 */
uint8_t __digits(uint8_t port)
{
  if (port >= 100)
  {
    return 3;
  }
  else if (port >= 10)
  {
    return 2;
  }
  return 1;
}

/**
 * \brief Extracts the port number from a received LoRaWAN downlink message string.
 * The input string is expected to start with the port number followed by a space
 * or null terminator.
 * \param s Pointer to the character string (e.g., "15 AABBCC" or "1 AABBCC").
 * \return The extracted port number as a uint8_t.
 */
uint8_t __receivedPort(const char *s)
{
  uint8_t port = 0;
  uint8_t i = 0;
  while (s[i] != ' ' && s[i] != '\0')
  {
    port *= 10;
    port += s[i] - 48;
    i++;
  }
  return port;
}

/**
 * \brief Constructor for TheThingsNetwork_HANIoT.
 * \param modemStream Reference to the Stream object for communication with the LoRaWAN module (e.g., Serial1).
 * \param debugStream Reference to the Stream object for debug output (e.g., Serial).
 * \param fp The frequency plan to use (e.g., TTN_FP_EU868).
 * \param sf The default Spreading Factor to use. If ADR is enabled, this might be overridden by the network.
 * \param fsb Frequency Sub-Band to use for US915 or AU915 frequency plans (0 for default).
 */
TheThingsNetwork_HANIoT::TheThingsNetwork_HANIoT(Stream &modemStream, Stream &debugStream, ttn_fp_t fp, uint8_t sf, uint8_t fsb)
{
  this->debugStream = &debugStream;
  this->modemStream = &modemStream;
  this->modemStream->setTimeout(10000);
  this->fp = fp;
  this->sf = sf;
  this->fsb = fsb;
}

/**
 * \brief Retrieves the Application EUI (AppEUI) from the LoRaWAN module.
 * \param buffer Pointer to the character array to store the AppEUI.
 * \param size Size of the buffer.
 * \return The number of bytes read into the buffer, or 0 on failure.
 */
size_t TheThingsNetwork_HANIoT::getAppEui(char *buffer, size_t size)
{
  return readResponse(MAC_TABLE, MAC_GET_SET_TABLE, MAC_APPEUI, buffer, size);
}

/**
 * \brief Retrieves the Hardware EUI (DevEUI from the module's hardware) from the LoRaWAN module.
 * This is typically used to set the Device EUI (DevEUI) for OTAA.
 * \param buffer Pointer to the character array to store the Hardware EUI.
 * \param size Size of the buffer.
 * \return The number of bytes read into the buffer, or 0 on failure.
 */
size_t TheThingsNetwork_HANIoT::getHardwareEui(char *buffer, size_t size)
{
  return readResponse(SYS_TABLE, SYS_TABLE, SYS_GET_HWEUI, buffer, size);
}

/**
 * \brief Retrieves the module's supply voltage (VDD) in millivolts.
 * \return The supply voltage in mV, or 0 on failure.
 */
uint16_t TheThingsNetwork_HANIoT::getVDD()
{
  if (readResponse(SYS_TABLE, SYS_TABLE, SYS_GET_VDD, buffer, sizeof(buffer)) > 0) {
    return atoi(buffer);
  }
  return 0;
}

/**
 * \brief Internal helper function to print indexed debug messages.
 * Uses `show_table` to fetch message prefixes from PROGMEM.
 * \param index Index in the `show_table`.
 * \param value Optional value string to append to the message.
 */
void TheThingsNetwork_HANIoT::debugPrintIndex(uint8_t index, const char *value)
{
  char message[100];
  strcpy_P(message, (char *)pgm_read_word(&(show_table[index])));
  debugPrint(message);
  if (value)
  {
    debugPrintLn(value);
  }
}

/**
 * \brief Internal helper function to print categorized debug messages.
 * Uses `error_msg` or `success_msg` tables to fetch messages from PROGMEM.
 * \param type Message category (ERR_MESSAGE or SUCCESS_MESSAGE).
 * \param index Index in the corresponding message table.
 * \param value Optional value string to append to the message.
 */
void TheThingsNetwork_HANIoT::debugPrintMessage(uint8_t type, uint8_t index, const char *value)
{
  char message[100];
  switch (type)
  {
  case ERR_MESSAGE:
    strcpy_P(message, (char *)pgm_read_word(&(error_msg[index])));
    break;
  case SUCCESS_MESSAGE:
    strcpy_P(message, (char *)pgm_read_word(&(success_msg[index])));
    break;
  }
  debugPrint(message);
  if (value)
  {
    debugPrintLn(value);
  }
  else
  {
    debugPrintLn();
  }
}

/**
 * \brief Clears the modem's read buffer by reading all available bytes.
 * This is typically done before sending a command to ensure no stale data
 * interferes with reading the response.
 * @internal
 */
void TheThingsNetwork_HANIoT::clearReadBuffer()
{
  while (modemStream->available())
  {
    modemStream->read();
  }
}

/**
 * \brief Reads a line of text from the modem stream until a newline character or timeout.
 * \param buffer Pointer to the character array to store the line.
 * \param size Maximum number of bytes to read into the buffer.
 * \param attempts Number of attempts to read a line before giving up.
 *                 If attempts are exhausted, `needsHardReset` flag is set.
 * \return The number of bytes read (excluding the null terminator), or 0 on failure or timeout.
 *         The received line has its trailing '\r' replaced with '\0'.
 * @internal
 */
size_t TheThingsNetwork_HANIoT::readLine(char *buffer, size_t size, uint8_t attempts)
{
  size_t read = 0;
  while (!read && attempts--)
  {
    read = modemStream->readBytesUntil('\n', buffer, size);
  }
  if (attempts<=0)
  { // If attempts is activated return 0 and set RN state marker
    this->needsHardReset = true; // Inform the application about the radio module is not responsive.
    debugPrintLn("No response from RN module.");
    return 0;
  }
  buffer[read - 1] = '\0'; // set \r to \0
  return read;
}

/**
 * \brief Reads a response from the modem after sending a command (typically a "get" command with one part).
 * \param prefixTable Index of the command prefix in its respective table (e.g., SYS_TABLE for "sys").
 * \param index Index of the specific command part within `prefixTable` (e.g., SYS_GET_VDD for "vdd").
 * \param buffer Pointer to the character array to store the response.
 * \param size Maximum number of bytes to read into the buffer.
 * \return The number of bytes read, or 0 on failure.
 * @internal
 */
size_t TheThingsNetwork_HANIoT::readResponse(uint8_t prefixTable, uint8_t index, char *buffer, size_t size)
{
  clearReadBuffer();
  sendCommand(prefixTable, 0, true, false); // Send prefix (e.g., "sys")
  sendCommand(prefixTable, index, false, false); // Send command part (e.g., "get vdd")
  modemStream->write(SEND_MSG);
  return readLine(buffer, size);
}

/**
 * \brief Reads a response from the modem after sending a "get" command with two parts (e.g., "mac get deveui").
 * \param prefixTable Index of the command prefix in its respective table (e.g., MAC_TABLE for "mac").
 * \param indexTable Index of the parameter name table (e.g., MAC_GET_SET_TABLE for "deveui").
 * \param index Index of the specific parameter name within `indexTable`.
 * \param buffer Pointer to the character array to store the response.
 * \param size Maximum number of bytes to read into the buffer.
 * \return The number of bytes read, or 0 on failure.
 * @internal
 */
size_t TheThingsNetwork_HANIoT::readResponse(uint8_t prefixTable, uint8_t indexTable, uint8_t index, char *buffer, size_t size)
{
  clearReadBuffer();
  sendCommand(prefixTable, 0, true, false);      // Send prefix (e.g., "mac")
  sendCommand(MAC_TABLE, MAC_GET, true, false); // Send "get"
  sendCommand(indexTable, index, false, false); // Send parameter name (e.g., "deveui")
  modemStream->write(SEND_MSG);
  return readLine(buffer, size);
}

/**
 * \brief Performs auto-baud detection with the LoRaWAN module.
 * Sends a break character (0x00) followed by 0x55 and a "sys get ver" command
 * repeatedly until a response is received or attempts are exhausted.
 * This helps synchronize communication if the baud rate is unknown or has changed.
 * Sets `baudDetermined` to true upon successful detection.
 * Based on a technique by @jpmeijers.
 * @internal
 */
void TheThingsNetwork_HANIoT::autoBaud()
{
  // Courtesy of @jpmeijers
  modemStream->setTimeout(2000);
  uint8_t attempts = 10;
  size_t length = 0;
  while (attempts-- && length == 0)
  {
    delay(100);
    modemStream->write((byte)0x00);
    modemStream->write(0x55);
    modemStream->write(SEND_MSG);
    sendCommand(SYS_TABLE, 0, true, false);
    sendCommand(SYS_TABLE, SYS_GET, true, false);
    sendCommand(SYS_TABLE, SYS_GET_VER, false, false);
    modemStream->write(SEND_MSG);
    length = modemStream->readBytesUntil('\n', buffer, sizeof(buffer));
  }
  delay(100);
  clearReadBuffer();
  modemStream->setTimeout(10000);
  baudDetermined = true;
}

/**
 * \brief Resets the LoRaWAN module and initializes basic configuration.
 * Performs auto-baud detection, resets the module, retrieves and displays
 * module version and EUI. Sets DevEUI from Hardware EUI and configures ADR.
 * \param adr Boolean indicating whether to enable Adaptive Data Rate (ADR).
 * @internal This method is called by public methods like personalize() and provision().
 */
void TheThingsNetwork_HANIoT::reset(bool adr)
{
  autoBaud();
  size_t length = readResponse(SYS_TABLE, SYS_RESET, buffer, sizeof(buffer));

  autoBaud();
  length = readResponse(SYS_TABLE, SYS_TABLE, SYS_GET_VER, buffer, sizeof(buffer));

  // buffer contains "RN2xx3[xx] x.x.x ...", splitting model from version
  char *model = strtok(buffer, " ");
  debugPrintIndex(SHOW_MODEL, model);
  char *version = strtok(NULL, " ");
  debugPrintIndex(SHOW_VERSION, version);

  readResponse(SYS_TABLE, SYS_TABLE, SYS_GET_HWEUI, buffer, sizeof(buffer));
  sendMacSet(MAC_DEVEUI, buffer);
  if (adr)
  {
    sendMacSet(MAC_ADR, "on");
  }
  else
  {
    sendMacSet(MAC_ADR, "off");
  }
  this->adr = adr;
  this->needsHardReset = false;
}

/**
 * \brief Performs a hardware reset of the LoRaWAN module.
 * Pulls the specified reset pin LOW, waits, then pulls it HIGH.
 * \param resetPin The Arduino pin connected to the module's reset line.
 */
void TheThingsNetwork_HANIoT::resetHard(uint8_t resetPin){
  digitalWrite(resetPin, LOW);
  delay(1000);
  digitalWrite(resetPin, HIGH);
}

/**
 * \brief Saves the current MAC state of the LoRaWAN module to its non-volatile memory.
 * This includes settings like DevEUI, AppEUI, AppKey, join status, etc.
 * Useful to persist configuration across power cycles or resets.
 * @internal This method is called by public methods like provision().
 */
void TheThingsNetwork_HANIoT::saveState()
{
  debugPrint(SENDING);
  sendCommand(MAC_TABLE, MAC_PREFIX, true);
  sendCommand(MAC_TABLE, MAC_SAVE, false);
  modemStream->write(SEND_MSG);
  debugPrintLn();
  waitForOk();
}

/**
 * \brief Registers a callback function to be invoked when a downlink message is received.
 * \param cb Pointer to the callback function. The function should take three arguments:
 *           - `const uint8_t* payload`: Pointer to the byte array containing the downlink payload.
 *           - `size_t size`: Size of the payload in bytes.
 *           - `port_t port`: The port number on which the message was received.
 */
void TheThingsNetwork_HANIoT::onMessage(void (*cb)(const uint8_t *payload, size_t size, port_t port))
{
  messageCallback = cb;
}

/**
 * \brief Configures the LoRaWAN module for Activation By Personalization (ABP) using provided keys.
 * \param devAddr Device Address (4 bytes, hex string, e.g., "01234567").
 * \param nwkSKey Network Session Key (16 bytes, hex string, e.g., "0123...DEF0").
 * \param appSKey Application Session Key (16 bytes, hex string, e.g., "0123...DEF0").
 * \return True if personalization was accepted by the module, false otherwise.
 *         Also performs a module reset and configures channels.
 */
bool TheThingsNetwork_HANIoT::personalize(const char *devAddr, const char *nwkSKey, const char *appSKey)
{
  reset(adr);
  if (strlen(devAddr) != 8 || strlen(appSKey) != 32 || strlen(nwkSKey) != 32)
  {
    debugPrintMessage(ERR_MESSAGE, ERR_KEY_LENGTH);
    return false;
  }
  sendMacSet(MAC_DEVADDR, devAddr);
  sendMacSet(MAC_NWKSKEY, nwkSKey);
  sendMacSet(MAC_APPSKEY, appSKey);
  return personalize();
}

/**
 * \brief Completes the ABP process using previously set DevAddr, NwkSKey, and AppSKey.
 * This function is typically called after setting the keys individually or if they are already
 * stored in the module. It configures channels, sets SF, and sends the "mac join abp" command.
 * \return True if personalization was accepted, false otherwise.
 */
bool TheThingsNetwork_HANIoT::personalize()
{
  configureChannels(fsb);
  setSF(sf);
  sendJoinSet(MAC_JOIN_MODE_ABP);
  readLine(buffer, sizeof(buffer));
  if (__pgmstrcmp(buffer, CMP_ACCEPTED) != 0)
  {
    debugPrintMessage(ERR_MESSAGE, ERR_PERSONALIZE_NOT_ACCEPTED, buffer);
    debugPrintMessage(ERR_MESSAGE, ERR_CHECK_CONFIGURATION);
    return false;
  }

  readResponse(MAC_TABLE, MAC_CH_TABLE, MAC_CHANNEL_STATUS, buffer, sizeof(buffer));
  debugPrintMessage(SUCCESS_MESSAGE, SCS_PERSONALIZE_ACCEPTED, buffer);
  return true;
}

/**
 * \brief Provisions the device for Over-The-Air Activation (OTAA) using AppEUI and AppKey.
 * The Hardware EUI of the module is used as the DevEUI.
 * \param appEui Application EUI (8 bytes, hex string, e.g., "0123456789ABCDEF").
 * \param appKey Application Key (16 bytes, hex string, e.g., "0123...DEF0").
 * \return True if provisioning commands were accepted by the module, false otherwise.
 *         Performs a module reset and saves the state.
 */
bool TheThingsNetwork_HANIoT::provision(const char *appEui, const char *appKey)
{
  reset(adr);
  if (strlen(appEui) != 16 || strlen(appKey) != 32)
  {
    debugPrintMessage(ERR_MESSAGE, ERR_KEY_LENGTH);
    return false;
  }
  readResponse(SYS_TABLE, SYS_TABLE, SYS_GET_HWEUI, buffer, sizeof(buffer));
  sendMacSet(MAC_DEVEUI, buffer);
  sendMacSet(MAC_APPEUI, appEui);
  sendMacSet(MAC_APPKEY, appKey);
  saveState();
  return true;
}

/**
 * \brief Provisions the device for Over-The-Air Activation (OTAA) using specified DevEUI, AppEUI, and AppKey.
 * \param devEui Device EUI (8 bytes, hex string, e.g., "0123456789ABCDEF").
 * \param appEui Application EUI (8 bytes, hex string, e.g., "0123456789ABCDEF").
 * \param appKey Application Key (16 bytes, hex string, e.g., "0123...DEF0").
 * \return True if provisioning commands were accepted by the module, false otherwise.
 *         Performs a module reset and saves the state.
 */
bool TheThingsNetwork_HANIoT::provision(const char *devEui, const char *appEui, const char *appKey)
{
  reset(adr);
  if (strlen(appEui) != 16 || strlen(appKey) != 32) // Should also check devEui length (16)
  {
    debugPrintMessage(ERR_MESSAGE, ERR_KEY_LENGTH);
    return false;
  }
  sendMacSet(MAC_DEVEUI, devEui);
  sendMacSet(MAC_APPEUI, appEui);
  sendMacSet(MAC_APPKEY, appKey);
  saveState();
  return true;
}

/**
 * \brief Attempts to join the LoRaWAN network using OTAA with previously provisioned keys.
 * \param retries Number of join attempts (-1 for indefinite retries).
 * \param retryDelay Delay in milliseconds between join attempts.
 * \return True if join was successful (accepted by the network), false otherwise.
 *         Configures channels and sets SF before attempting to join.
 */
bool TheThingsNetwork_HANIoT::join(int8_t retries, uint32_t retryDelay)
{
  int8_t attempts = 0;
  configureChannels(fsb);
  setSF(sf);
  while (retries == -1 || attempts <= retries)
  {
    attempts++;
    if (!sendJoinSet(MAC_JOIN_MODE_OTAA))
    {
      debugPrintMessage(ERR_MESSAGE, ERR_JOIN_FAILED);
      delay(retryDelay);
      continue;
    }
    readLine(buffer, sizeof(buffer));
    if (__pgmstrcmp(buffer, CMP_ACCEPTED) != 0)
    {
      debugPrintMessage(ERR_MESSAGE, ERR_JOIN_NOT_ACCEPTED, buffer);
      debugPrintMessage(ERR_MESSAGE, ERR_CHECK_CONFIGURATION);
      delay(retryDelay);
      continue;
    }
    readResponse(MAC_TABLE, MAC_CH_TABLE, MAC_CHANNEL_STATUS, buffer, sizeof(buffer));
    debugPrintMessage(SUCCESS_MESSAGE, SCS_JOIN_ACCEPTED, buffer);
    readResponse(MAC_TABLE, MAC_GET_SET_TABLE, MAC_DEVADDR, buffer, sizeof(buffer));
    debugPrintIndex(SHOW_DEVADDR, buffer);
    return true;
  }
  return false;
}

/**
 * \brief Provisions with AppEUI, AppKey and then attempts to join the LoRaWAN network (OTAA).
 * The Hardware EUI of the module is used as the DevEUI.
 * \param appEui Application EUI (8 bytes, hex string).
 * \param appKey Application Key (16 bytes, hex string).
 * \param retries Number of join attempts (-1 for indefinite retries).
 * \param retryDelay Delay in milliseconds between join attempts.
 * \return True if provisioning and join were successful, false otherwise.
 */
bool TheThingsNetwork_HANIoT::join(const char *appEui, const char *appKey, int8_t retries, uint32_t retryDelay)
{
  return provision(appEui, appKey) && join(retries, retryDelay);
}

/**
 * \brief Provisions with DevEUI, AppEUI, AppKey and then attempts to join the LoRaWAN network (OTAA).
 * \param devEui Device EUI (8 bytes, hex string).
 * \param appEui Application EUI (8 bytes, hex string).
 * \param appKey Application Key (16 bytes, hex string).
 * \param retries Number of join attempts (-1 for indefinite retries).
 * \param retryDelay Delay in milliseconds between join attempts.
 * \return True if provisioning and join were successful, false otherwise.
 */
bool TheThingsNetwork_HANIoT::join(const char *devEui, const char *appEui, const char *appKey, int8_t retries, uint32_t retryDelay)
{
  return provision(devEui, appEui, appKey) && join(retries, retryDelay);
}

/**
 * \brief Sends a byte array payload over LoRaWAN.
 * \param payload Pointer to the byte array containing the data to send.
 * \param length Size of the payload in bytes.
 * \param port The LoRaWAN port number to send the data on (1-223).
 * \param confirm True for a confirmed uplink (requires acknowledgment), false for unconfirmed.
 * \param sf Optional: Spreading Factor to use for this transmission. If 0 or not provided, uses default or ADR-determined SF.
 * \return A `ttn_response_t` code indicating the outcome (e.g., TTN_SUCCESSFUL_TRANSMISSION, TTN_ERROR_SEND_COMMAND_FAILED).
 *         If a downlink message is received as part of a confirmed uplink or piggybacked on an unconfirmed one,
 *         the `messageCallback` (if registered) will be invoked.
 */
ttn_response_t TheThingsNetwork_HANIoT::sendBytes(const uint8_t *payload, size_t length, port_t port, bool confirm, uint8_t sf)
{
  if (sf != 0)
  {
    setSF(sf);
  }

  uint8_t mode = confirm ? MAC_TX_TYPE_CNF : MAC_TX_TYPE_UCNF;
  if (!sendPayload(mode, port, (uint8_t *)payload, length))
  {
    debugPrintMessage(ERR_MESSAGE, ERR_SEND_COMMAND_FAILED);
    return TTN_ERROR_SEND_COMMAND_FAILED;
  }

  readLine(buffer, sizeof(buffer));

  if (__pgmstrcmp(buffer, CMP_MAC_TX_OK) == 0)
  {
    debugPrintMessage(SUCCESS_MESSAGE, SCS_SUCCESSFUL_TRANSMISSION);
    return TTN_SUCCESSFUL_TRANSMISSION;
  }

  if (__pgmstrcmp(buffer, CMP_MAC_RX) == 0)
  {
    port_t downlinkPort = __receivedPort(buffer + 7);
    char *data = buffer + 7 + __digits(downlinkPort) + 1;
    size_t downlinkLength = strlen(data) / 2;
    if (downlinkLength > 0)
    {
      uint8_t downlink[downlinkLength];
      for (size_t i = 0, d = 0; i < downlinkLength; i++, d += 2)
      {
        downlink[i] = TTN_HEX_PAIR_TO_BYTE(data[d], data[d + 1]);
      }
      debugPrintMessage(SUCCESS_MESSAGE, SCS_SUCCESSFUL_TRANSMISSION_RECEIVED, data);
      if (messageCallback)
      {
        messageCallback(downlink, downlinkLength, downlinkPort);
      }
    }
    else
    {
      debugPrintMessage(SUCCESS_MESSAGE, SCS_SUCCESSFUL_TRANSMISSION);
    }
    return TTN_SUCCESSFUL_RECEIVE;
  }

  debugPrintMessage(ERR_MESSAGE, ERR_UNEXPECTED_RESPONSE, buffer);
  return TTN_ERROR_UNEXPECTED_RESPONSE;
}

/**
 * \brief Sends an empty payload, often used to poll for downlink messages.
 * \param port The LoRaWAN port number (1-223).
 * \param confirm True for a confirmed uplink, false for unconfirmed.
 * \return A `ttn_response_t` code indicating the outcome.
 *         The `messageCallback` (if registered) will be invoked if a downlink is received.
 */
ttn_response_t TheThingsNetwork_HANIoT::poll(port_t port, bool confirm)
{
  uint8_t payload[] = {0x00};
  return sendBytes(payload, 1, port, confirm);
}

/**
 * \brief Displays various status parameters of the LoRaWAN module on the debug stream.
 * This includes EUI, battery voltage, AppEUI, DevEUI, data rate, and RX delay settings.
 */
void TheThingsNetwork_HANIoT::showStatus()
{
  readResponse(SYS_TABLE, SYS_TABLE, SYS_GET_HWEUI, buffer, sizeof(buffer));
  debugPrintIndex(SHOW_EUI, buffer);
  readResponse(SYS_TABLE, SYS_TABLE, SYS_GET_VDD, buffer, sizeof(buffer));
  debugPrintIndex(SHOW_BATTERY, buffer);
  readResponse(MAC_TABLE, MAC_GET_SET_TABLE, MAC_APPEUI, buffer, sizeof(buffer));
  debugPrintIndex(SHOW_APPEUI, buffer);
  readResponse(MAC_TABLE, MAC_GET_SET_TABLE, MAC_DEVEUI, buffer, sizeof(buffer));
  debugPrintIndex(SHOW_DEVEUI, buffer);
  readResponse(MAC_TABLE, MAC_GET_SET_TABLE, MAC_DR, buffer, sizeof(buffer));
  debugPrintIndex(SHOW_DATA_RATE, buffer);
  readResponse(MAC_TABLE, MAC_GET_SET_TABLE, MAC_RXDELAY1, buffer, sizeof(buffer));
  debugPrintIndex(SHOW_RX_DELAY_1, buffer);
  readResponse(MAC_TABLE, MAC_GET_SET_TABLE, MAC_RXDELAY2, buffer, sizeof(buffer));
  debugPrintIndex(SHOW_RX_DELAY_2, buffer);
}

/**
 * \brief Configures LoRaWAN channels for the EU868 frequency plan.
 * Sets default channels, data rates, duty cycles, and RX2 window parameters.
 * @internal This method is called by `configureChannels`.
 */
void TheThingsNetwork_HANIoT::configureEU868()
{
  sendMacSet(MAC_RX2, "3 869525000");
  sendChSet(MAC_CHANNEL_DRRANGE, 1, "0 6");

  char buf[10];
  uint32_t freq = 867100000;
  uint8_t ch;
  for (ch = 0; ch < 8; ch++)
  {
    sendChSet(MAC_CHANNEL_DCYCLE, ch, "799");
    if (ch > 2)
    {
      sprintf(buf, "%lu", freq);
      sendChSet(MAC_CHANNEL_FREQ, ch, buf);
      sendChSet(MAC_CHANNEL_DRRANGE, ch, "0 5");
      sendChSet(MAC_CHANNEL_STATUS, ch, "on");
      freq = freq + 200000;
    }
  }
  sendMacSet(MAC_PWRIDX, TTN_PWRIDX_EU868);
}

/**
 * \brief Configures LoRaWAN channels for the US915 frequency plan.
 * \param fsb Frequency Sub-Band (1-8). If 0, all 72 channels are potentially configured.
 *            Activates a specific block of 8 channels for 125kHz plus one 500kHz channel.
 * @internal This method is called by `configureChannels`.
 */
void TheThingsNetwork_HANIoT::configureUS915(uint8_t fsb)
{
  uint8_t ch;
  uint8_t chLow = fsb > 0 ? (fsb - 1) * 8 : 0;
  uint8_t chHigh = fsb > 0 ? chLow + 7 : 71;
  uint8_t ch500 = fsb + 63;
  for (ch = 0; ch < 72; ch++)
  {
    if (ch == ch500 || (ch <= chHigh && ch >= chLow))
    {
      sendChSet(MAC_CHANNEL_STATUS, ch, "on");
      if (ch < 63)
      {
        sendChSet(MAC_CHANNEL_DRRANGE, ch, "0 3");
      }
    }
    else
    {
      sendChSet(MAC_CHANNEL_STATUS, ch, "off");
    }
  }
  sendMacSet(MAC_PWRIDX, TTN_PWRIDX_US915);
}

/**
 * \brief Configures LoRaWAN channels for the AU915 frequency plan.
 * \param fsb Frequency Sub-Band (1-8). If 0, all 72 channels are potentially configured.
 *            Activates a specific block of 8 channels for 125kHz plus one 500kHz channel.
 * @internal This method is called by `configureChannels`.
 */
void TheThingsNetwork_HANIoT::configureAU915(uint8_t fsb)
{
  uint8_t ch;
  uint8_t chLow = fsb > 0 ? (fsb - 1) * 8 : 0;
  uint8_t chHigh = fsb > 0 ? chLow + 7 : 71;
  uint8_t ch500 = fsb + 63;
  for (ch = 0; ch < 72; ch++)
  {
    if (ch == ch500 || (ch <= chHigh && ch >= chLow))
    {
      sendChSet(MAC_CHANNEL_STATUS, ch, "on");
      if (ch < 63)
      {
        sendChSet(MAC_CHANNEL_DRRANGE, ch, "0 3");
      }
    }
    else
    {
      sendChSet(MAC_CHANNEL_STATUS, ch, "off");
    }
  }
  sendMacSet(MAC_PWRIDX, TTN_PWRIDX_AU915);
}

/**
 * \brief Configures LoRaWAN channels for the AS920-923 frequency plan (e.g., Thailand).
 * Sets default channels, data rates, and other regional parameters.
 * @internal This method is called by `configureChannels`.
 * \note ADR might be turned off due to module limitations or plan specifics.
 */
void TheThingsNetwork_HANIoT::configureAS920_923()
{
  /* RN2903AS 1.0.3rc9 defaults
   * CH0 = 923.2MHz
   * CH1 = 923.4MHz
   */
  sendMacSet(MAC_ADR, "off"); // TODO: remove when ADR is implemented for this plan
  sendMacSet(MAC_RX2, "2 923200000");

  char buf[10];
  uint32_t freq = 922000000;
  uint8_t ch;
  for (ch = 0; ch < 8; ch++)
  {
    sendChSet(MAC_CHANNEL_DCYCLE, ch, "799");
    if (ch > 1)
    {
      sprintf(buf, "%lu", freq);
      sendChSet(MAC_CHANNEL_FREQ, ch, buf);
      sendChSet(MAC_CHANNEL_DRRANGE, ch, "0 5");
      sendChSet(MAC_CHANNEL_STATUS, ch, "on");
      freq = freq + 200000;
    }
  }
  // TODO: SF7BW250/DR6 channel, not properly supported by RN2903AS yet
  //sendChSet(MAC_CHANNEL_DCYCLE, 8, "799");
  //sendChSet(MAC_CHANNEL_FREQ, 8, "922100000");
  //sendChSet(MAC_CHANNEL_DRRANGE, 8, "6 6");
  //sendChSet(MAC_CHANNEL_STATUS, 8, "on");
  // TODO: Add FSK channel on 921800000
  sendMacSet(MAC_PWRIDX, TTN_PWRIDX_AS920_923);
}

/**
 * \brief Configures LoRaWAN channels for the AS923-925 frequency plan (e.g., Indonesia).
 * Sets default channels, data rates, and other regional parameters.
 * @internal This method is called by `configureChannels`.
 * \note ADR might be turned off due to module limitations or plan specifics.
 */
void TheThingsNetwork_HANIoT::configureAS923_925()
{
  /* RN2903AS 1.0.3rc9 defaults
   * CH0 = 923.2MHz
   * CH1 = 923.4MHz
   */
  sendMacSet(MAC_ADR, "off"); // TODO: remove when ADR is implemented for this plan
  sendMacSet(MAC_RX2, "2 923200000");

  char buf[10];
  uint32_t freq = 923600000;
  uint8_t ch;
  for (ch = 0; ch < 8; ch++)
  {
    sendChSet(MAC_CHANNEL_DCYCLE, ch, "799");
    if (ch > 1)
    {
      sprintf(buf, "%lu", freq);
      sendChSet(MAC_CHANNEL_FREQ, ch, buf);
      sendChSet(MAC_CHANNEL_DRRANGE, ch, "0 5");
      sendChSet(MAC_CHANNEL_STATUS, ch, "on");
      freq = freq + 200000;
    }
  }
  // TODO: SF7BW250/DR6 channel, not properly supported by RN2903AS yet
  //sendChSet(MAC_CHANNEL_DCYCLE, 8, "799");
  //sendChSet(MAC_CHANNEL_FREQ, 8, "924500000");
  //sendChSet(MAC_CHANNEL_DRRANGE, 8, "6 6");
  //sendChSet(MAC_CHANNEL_STATUS, 8, "on");
  // TODO: Add FSK channel on 924800000
  sendMacSet(MAC_PWRIDX, TTN_PWRIDX_AS923_925);
}

/**
 * \brief Configures LoRaWAN channels for the KR920-923 frequency plan (South Korea).
 * Sets default channels, data rates, and other regional parameters.
 * @internal This method is called by `configureChannels`.
 * \note ADR might be turned off due to module limitations or plan specifics.
 */
void TheThingsNetwork_HANIoT::configureKR920_923()
{
  sendMacSet(MAC_ADR, "off"); // TODO: remove when ADR is implemented for this plan
  sendMacSet(MAC_RX2, "0 921900000"); // KR still uses SF12 for now. Might change to SF9 later.

  //disable two default LoRaWAN channels
  sendChSet(MAC_CHANNEL_STATUS, 0, "off");
  sendChSet(MAC_CHANNEL_STATUS, 1, "off");

  char buf[10];
  uint32_t freq = 922100000;
  uint8_t ch;
  for (ch = 2; ch < 9; ch++)
  {
    sendChSet(MAC_CHANNEL_DCYCLE, ch, "799");
    sprintf(buf, "%lu", freq);
    sendChSet(MAC_CHANNEL_FREQ, ch, buf);
    sendChSet(MAC_CHANNEL_DRRANGE, ch, "0 5");
    sendChSet(MAC_CHANNEL_STATUS, ch, "on");
    freq = freq + 200000;
  }
  sendMacSet(MAC_PWRIDX, TTN_PWRIDX_KR920_923);
}

/**
 * \brief Configures LoRaWAN channels for the IN865-867 frequency plan (India).
 * Sets default channels, data rates, and other regional parameters.
 * @internal This method is called by `configureChannels`.
 * \note ADR might be turned off due to module limitations or plan specifics.
 */
void TheThingsNetwork_HANIoT::configureIN865_867()
{
  sendMacSet(MAC_ADR, "off"); // TODO: remove when ADR is implemented for this plan
  sendMacSet(MAC_RX2, "2 866550000"); // SF10

  // Disable the three default LoRaWAN channels
  sendChSet(MAC_CHANNEL_STATUS, 0, "off");
  sendChSet(MAC_CHANNEL_STATUS, 1, "off");
  sendChSet(MAC_CHANNEL_STATUS, 2, "off");

  // Channel 3
  sendChSet(MAC_CHANNEL_DCYCLE, 3, "299");
  sendChSet(MAC_CHANNEL_FREQ, 3, "865062500");
  sendChSet(MAC_CHANNEL_DRRANGE, 3, "0 5");
  sendChSet(MAC_CHANNEL_STATUS, 3, "on");

  // Channel 4
  sendChSet(MAC_CHANNEL_DCYCLE, 4, "299");
  sendChSet(MAC_CHANNEL_FREQ, 4, "865402500");
  sendChSet(MAC_CHANNEL_DRRANGE, 4, "0 5");
  sendChSet(MAC_CHANNEL_STATUS, 4, "on");

  // Channel 5
  sendChSet(MAC_CHANNEL_DCYCLE, 5, "299");
  sendChSet(MAC_CHANNEL_FREQ, 5, "865985000");
  sendChSet(MAC_CHANNEL_DRRANGE, 5, "0 5");
  sendChSet(MAC_CHANNEL_STATUS, 5, "on");

  sendMacSet(MAC_PWRIDX, TTN_PWRIDX_IN865_867);
}

/**
 * \brief Configures LoRaWAN channels based on the selected frequency plan (`fp`).
 * Calls the appropriate region-specific configuration function (e.g., `configureEU868`).
 * Also sets the default retransmission attempts for confirmed uplinks.
 * \param fsb Frequency Sub-Band, used by some frequency plans like US915 and AU915.
 * @internal
 */
void TheThingsNetwork_HANIoT::configureChannels(uint8_t fsb)
{
  switch (fp)
  {
  case TTN_FP_EU868:
    configureEU868();
    break;
  case TTN_FP_US915:
    configureUS915(fsb);
    break;
  case TTN_FP_AU915:
    configureAU915(fsb);
    break;
  case TTN_FP_AS920_923:
    configureAS920_923();
    break;
  case TTN_FP_AS923_925:
    configureAS923_925();
    break;
  case TTN_FP_KR920_923:
    configureKR920_923();
    break;
  case TTN_FP_IN865_867:
    configureIN865_867();
    break;
  default:
    debugPrintMessage(ERR_MESSAGE, ERR_INVALID_FP);
    break;
  }
  sendMacSet(MAC_RETX, TTN_RETX);
}

/**
 * \brief Sets the Spreading Factor (SF) on the LoRaWAN module.
 * Converts the SF value (e.g., 7-12) to the corresponding Data Rate (DR) index
 * based on the current frequency plan.
 * \param sf The desired Spreading Factor.
 * \return True if the command to set the DR was acknowledged by the module, false otherwise.
 * @internal
 */
bool TheThingsNetwork_HANIoT::setSF(uint8_t sf)
{
  uint8_t dr;
  switch (fp)
  {
  case TTN_FP_EU868:
  case TTN_FP_IN865_867:
  case TTN_FP_AS920_923:
  case TTN_FP_AS923_925:
  case TTN_FP_KR920_923:
    dr = 12 - sf;
    break;
  case TTN_FP_US915:
  case TTN_FP_AU915:
    dr = 10 - sf;
    break;
  }
  char s[2];
  s[0] = '0' + dr;
  s[1] = '\0';
  return sendMacSet(MAC_DR, s);
}

/**
 * \brief Sends a command part (string token) to the LoRaWAN module from PROGMEM tables.
 * \param table Index indicating which PROGMEM table to use (e.g., MAC_TABLE, SYS_TABLE).
 * \param index Index of the specific command string within the selected table.
 * \param appendSpace If true, a space character is sent after the command string.
 * \param print If true, the command string is also printed to the debug stream.
 * @internal This method is used for constructing and sending AT-like commands.
 */
void TheThingsNetwork_HANIoT::sendCommand(uint8_t table, uint8_t index, bool appendSpace, bool print)
{
  char command[100];
  switch (table)
  {
  case MAC_TABLE:
    strcpy_P(command, (char *)pgm_read_word(&(mac_table[index])));
    break;
  case MAC_GET_SET_TABLE:
    strcpy_P(command, (char *)pgm_read_word(&(mac_options[index])));
    break;
  case MAC_JOIN_TABLE:
    strcpy_P(command, (char *)pgm_read_word(&(mac_join_mode[index])));
    break;
  case MAC_CH_TABLE:
    strcpy_P(command, (char *)pgm_read_word(&(mac_ch_options[index])));
    break;
  case MAC_TX_TABLE:
    strcpy_P(command, (char *)pgm_read_word(&(mac_tx_table[index])));
    break;
  case SYS_TABLE:
    strcpy_P(command, (char *)pgm_read_word(&(sys_table[index])));
    break;
  case RADIO_TABLE:
    strcpy_P(command, (char *)pgm_read_word(&(radio_table[index])));
    break;
  default:
    return;
  }
  modemStream->write(command);
  if (appendSpace)
  {
    modemStream->write(" ");
  }
  if (print)
  {
    debugPrint(command);
    debugPrint(F(" "));
  }
}

/**
 * \brief Sends a "mac set <parameter> <value>" command to the LoRaWAN module.
 * \param index Index of the parameter in `mac_options` (e.g., MAC_DEVEUI).
 * \param value The value to set for the parameter.
 * \return True if the command was acknowledged ("ok"), false otherwise.
 * @internal
 */
bool TheThingsNetwork_HANIoT::sendMacSet(uint8_t index, const char *value)
{
  clearReadBuffer();
  debugPrint(SENDING);
  sendCommand(MAC_TABLE, MAC_PREFIX, true);
  sendCommand(MAC_TABLE, MAC_SET, true);
  sendCommand(MAC_GET_SET_TABLE, index, true);
  modemStream->write(value);
  modemStream->write(SEND_MSG);
  debugPrintLn(value);
  return waitForOk();
}

/**
 * \brief Waits for an "ok" response from the LoRaWAN module after sending a command.
 * \return True if "ok" is received within the timeout, false otherwise.
 *         Prints an error message if a different response or no response is received.
 * @internal
 */
bool TheThingsNetwork_HANIoT::waitForOk()
{
  readLine(buffer, sizeof(buffer));
  if (__pgmstrcmp(buffer, CMP_OK) != 0)
  {
    debugPrintMessage(ERR_MESSAGE, ERR_RESPONSE_IS_NOT_OK, buffer);
    return false;
  }
  return true;
}

/**
 * \brief Sends a "mac set ch <parameter>" command to the LoRaWAN module.
 * Used for configuring channel parameters like duty cycle, frequency, data rate range, and status.
 * \param index Index of the channel parameter in `mac_ch_options` (e.g., MAC_CHANNEL_DCYCLE).
 * \param channel The channel ID to configure.
 * \param value The value to set for the parameter.
 * \return True if the command was acknowledged ("ok"), false otherwise.
 * @internal
 */
bool TheThingsNetwork_HANIoT::sendChSet(uint8_t index, uint8_t channel, const char *value)
{
  clearReadBuffer();
  char ch[5];
  if (channel > 9)
  {
    ch[0] = ((channel - (channel % 10)) / 10) + 48;
    ch[1] = (channel % 10) + 48;
    ch[2] = '\0';
  }
  else
  {
    ch[0] = channel + 48;
    ch[1] = '\0';
  }
  debugPrint(F(SENDING));
  sendCommand(MAC_TABLE, MAC_PREFIX, true);
  sendCommand(MAC_TABLE, MAC_SET, true);
  sendCommand(MAC_GET_SET_TABLE, MAC_CH, true);
  sendCommand(MAC_CH_TABLE, index, true);
  modemStream->write(ch);
  modemStream->write(" ");
  modemStream->write(value);
  modemStream->write(SEND_MSG);
  debugPrint(channel);
  debugPrint(F(" "));
  debugPrintLn(value);
  return waitForOk();
}

/**
 * \brief Sends a "mac join <type>" command (e.g., "mac join otaa" or "mac join abp").
 * \param type Index of the join mode in `mac_join_mode` (MAC_JOIN_MODE_OTAA or MAC_JOIN_MODE_ABP).
 * \return True if the command was acknowledged ("ok"), false otherwise.
 * @internal
 */
bool TheThingsNetwork_HANIoT::sendJoinSet(uint8_t type)
{
  clearReadBuffer();
  debugPrint(F(SENDING));
  sendCommand(MAC_TABLE, MAC_PREFIX, true);
  sendCommand(MAC_TABLE, MAC_JOIN, true);
  sendCommand(MAC_JOIN_TABLE, type, false);
  modemStream->write(SEND_MSG);
  debugPrintLn();
  return waitForOk();
}

/**
 * \brief Sends a "mac tx <type> <port> <payload>" command to the LoRaWAN module.
 * This is the core function for transmitting uplink data.
 * \param mode Message type from `mac_tx_table` (MAC_TX_TYPE_CNF or MAC_TX_TYPE_UCNF).
 * \param port The LoRaWAN port number.
 * \param payload Pointer to the byte array of the payload.
 * \param length Length of the payload in bytes.
 * \return True if the command was acknowledged ("ok"), false otherwise.
 * @internal The actual success of transmission and reception of downlink
 * is handled by `sendBytes`.
 */
bool TheThingsNetwork_HANIoT::sendPayload(uint8_t mode, uint8_t port, uint8_t *payload, size_t length)
{
  clearReadBuffer();
  debugPrint(F(SENDING));
  sendCommand(MAC_TABLE, MAC_PREFIX, true);
  sendCommand(MAC_TABLE, MAC_TX, true);
  sendCommand(MAC_TX_TABLE, mode, true);
  char sport[4];
  if (port > 99)
  {
    sport[0] = ((port - (port % 100)) / 100) + 48;
    sport[1] = (((port % 100) - (port % 10)) / 10) + 48;
    sport[2] = (port % 10) + 48;
    sport[3] = '\0';
  }
  else if (port > 9)
  {
    sport[0] = ((port - (port % 10)) / 10) + 48;
    sport[1] = (port % 10) + 48;
    sport[2] = '\0';
  }
  else
  {
    sport[0] = port + 48;
    sport[1] = '\0';
  }
  modemStream->write(sport);
  modemStream->print(" ");
  debugPrint(sport);
  debugPrint(F(" "));
  uint8_t i = 0;
  for (i = 0; i < length; i++)
  {
    if (payload[i] < 16)
    {
      modemStream->print("0");
      modemStream->print(payload[i], HEX);
      debugPrint(F("0"));
      debugPrint(payload[i], HEX);
    }
    else
    {
      modemStream->print(payload[i], HEX);
      debugPrint(payload[i], HEX);
    }
  }
  modemStream->write(SEND_MSG);
  debugPrintLn();
  return waitForOk();
}

/**
 * \brief Puts the LoRaWAN module into sleep mode for a specified duration.
 * \param mseconds Duration to sleep in milliseconds. Must be >= 100.
 * After sleeping, `wake()` must be called to re-establish communication.
 */
void TheThingsNetwork_HANIoT::sleep(uint32_t mseconds)
{
  if (mseconds < 100)
  {
    return;
  }

  debugPrint(F(SENDING));
  sendCommand(SYS_TABLE, SYS_PREFIX, true);
  sendCommand(SYS_TABLE, SYS_SLEEP, true);

  sprintf(buffer, "%lu", mseconds);
  modemStream->write(buffer);
  modemStream->write(SEND_MSG);
  debugPrintLn(buffer);
}

/**
 * \brief Wakes the LoRaWAN module after it has been put to sleep.
 * Performs auto-baud detection to re-establish communication.
 */
void TheThingsNetwork_HANIoT::wake()
{
  autoBaud();
}

/**
 * \brief Configures the LoRaWAN module to perform a link check periodically.
 * The module will then include a MAC command in uplinks to request a link status
 * from the network server. The results (demodulation margin and number of gateways)
 * can be retrieved using `getLinkCheckMargin()` and `getLinkCheckGateways()`.
 * \param seconds Interval in seconds for sending link check requests. 0 disables it.
 */
void TheThingsNetwork_HANIoT::linkCheck(uint16_t seconds)
{
  clearReadBuffer();
  debugPrint(SENDING);
  sendCommand(MAC_TABLE, MAC_PREFIX, true);
  sendCommand(MAC_TABLE, MAC_SET, true);
  sendCommand(MAC_GET_SET_TABLE, MAC_LINKCHK, true);

  sprintf(buffer, "%u", seconds);
  modemStream->write(buffer);
  modemStream->write(SEND_MSG);
  debugPrintLn(buffer);
  waitForOk();
}

/**
 * \brief Retrieves the number of gateways that successfully received the last link check request.
 * \return The number of gateways.
 */
uint8_t TheThingsNetwork_HANIoT::getLinkCheckGateways()
{
  readResponse(MAC_TABLE, MAC_GET_SET_TABLE, MAC_GWNB, buffer, sizeof(buffer));
  return strtol(buffer, NULL, 10);
}

/**
 * \brief Retrieves the demodulation margin (in dB) of the last link check request.
 * This indicates the quality of the link to the best gateway.
 * \return The link margin in dB.
 */
uint8_t TheThingsNetwork_HANIoT::getLinkCheckMargin()
{
  readResponse(MAC_TABLE, MAC_GET_SET_TABLE, MAC_MRGN, buffer, sizeof(buffer));
  return strtol(buffer, NULL, 10);
}
