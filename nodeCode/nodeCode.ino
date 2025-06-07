/**
 * @file nodeCode.ino
 * @brief Main Arduino sketch for the LoRaWAN muskrat trap node.
 * @author Jaap-Jan Groenendijk (github@jjgroenendijk.nl)
 * @date 2024-09-06 (Assumed, based on encoder.h, needs verification)
 * @version 1.0 (Assumed, needs verification)
 *
 * @mainpage IoT Muskrat Trap Node
 *
 * @section intro_sec Introduction
 * This firmware is designed for an Arduino-based LoRaWAN node that monitors a muskrat trap.
 * It reads sensor data for door status, catch detection, trap displacement, and battery level.
 * The collected data is encoded into a compact payload and transmitted via LoRaWAN to
 * The Things Network (TTN).
 *
 * @section features_sec Features
 * - Monitors door status (open/closed).
 * - Detects if a catch has been made.
 * - Senses if the trap has been displaced.
 * - Measures battery voltage.
 * - Encodes sensor data into a LoRaWAN-friendly payload.
 * - Transmits data on sensor state changes or at regular heartbeat intervals.
 * - Utilizes deep sleep and watchdog timer for power efficiency.
 * - Communicates with a LoRaWAN module (e.g., RN2483 via TheThingsNetwork_HANIoT library).
 * - Uses the HAN IoT Shield for interacting with buttons (simulating sensors) and LEDs.
 *
 * @section hardware_sec Hardware
 * - Arduino Leonardo (or compatible)
 * - HAN IoT Shield (for buttons, LEDs, potentially temperature sensor and potentiometers)
 * - LoRaWAN module connected via Serial1
 * - Sensors for door, catch, and displacement (simulated by buttons on HAN IoT Shield in this version).
 * - Battery monitoring circuit.
 *
 * @section dependencies_sec Dependencies
 * - TheThingsNetwork_HANIoT library (for LoRaWAN communication)
 * - HAN_IoT_Shield library (for shield hardware interaction)
 * - OneWire and DallasTemperature (if using Dallas temperature sensor from the shield)
 * - AVR Sleep and Watchdog Timer libraries (for power management)
 * - Custom encoder/decoder classes for payload management.
 *
 * @section setup_sec Setup
 * 1. Configure LoRaWAN credentials (DevEUI, AppEUI, AppKey) in `secrets.h`.
 * 2. Define the LoRaWAN frequency plan (e.g., `TTN_FP_EU868`).
 * 3. Initialize sensors and LoRaWAN module in the `setup()` function.
 *
 * @section workflow_sec Workflow
 * - The `loop()` function continuously checks sensor states.
 * - If a sensor state changes or if the heartbeat interval is reached, a LoRaWAN message is prepared and sent.
 * - The `payloadEncoder` class is used to create the message payload.
 * - After sending a message or if no event occurs, the MCU enters a low-power sleep mode.
 * - The Watchdog Timer (WDT) wakes the MCU periodically to re-check sensors.
 *
 * @note The current implementation uses buttons on the HAN IoT Shield to simulate sensor inputs:
 *       - Red button pressed (alone): Door closed.
 *       - Black button pressed (alone): Catch detected.
 *       - Both buttons pressed: Trap displaced.
 */

#define ENABLE_DEBUG_SERIAL true // Set to true for debugging, false for production/power testing

#include "TheThingsNetwork_HANIoT.h"
#include "HAN_IoT_Shield.h"
#include "secrets.h"
#include "encoder.h"
#include "decoder.h"
#include "IOTShieldConfig.h"
#include "knightRider.h"
#include "test.h"
#include "doorSensor.h"
#include "catchSensor.h"
#include "displacementSensor.h"
#include "batterySensor.h"

#include <avr/sleep.h> // For MCU sleep modes
#include <avr/wdt.h>   // For Watchdog Timer

const char *devEui = DEVEUI;  ///< @brief Device EUI for LoRaWAN, from TTN Console.
const char *appEui = JOINEUI; ///< @brief Application EUI for LoRaWAN, from TTN Console.
const char *appKey = APPKEY;  ///< @brief Application Key for LoRaWAN, from TTN Console.

#define loraSerial Serial1    ///< @brief Serial interface for LoRaWAN module communication.
#define debugSerial Serial   ///< @brief Serial interface for debugging output.

/**
 * @brief Flag to enable or disable LoRaWAN communication.
 * Set to true to attempt to join and send messages, false for offline testing/debugging.
 */
bool loraCommunication = false;

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868 ///< @brief LoRaWAN frequency plan (e.g., TTN_FP_EU868 for Europe).

/**
 * @brief Global instance of TheThingsNetwork_HANIoT library for LoRaWAN communication.
 */
TheThingsNetwork_HANIoT ttn(loraSerial, debugSerial, freqPlan);

// iotShieldTempSensor temperatureSensor; // Example, if used

// Declare sensor objects
/** @brief Object representing the door sensor. */
doorSensor doorSensor;
/** @brief Object representing the catch sensor. */
catchSensor catchSensor;
/** @brief Object representing the displacement sensor. */
displacementSensor displacementSensor;
/** @brief Object representing the battery sensor. */
batterySensor batterySensor;

// Variables to store previous sensor states for event detection
bool prevDoorStatus = false; ///< @brief Previous state of the door sensor.
bool prevCatchStatus = false; ///< @brief Previous state of the catch sensor.
bool prevDisplacementStatus = false; ///< @brief Previous state of the displacement sensor.

// Heartbeat interval configuration
// const unsigned long HEARTBEAT_INTERVAL_MS = 24UL * 60UL * 60UL * 1000UL; // 24 hours
/**
 * @brief Interval for sending heartbeat messages, in milliseconds.
 * Currently set to 5 minutes for testing purposes.
 */
// const unsigned long HEARTBEAT_INTERVAL_MS = 5UL * 60UL * 1000UL; // 5 minutes for testing
const unsigned long HEARTBEAT_INTERVAL_MS = 24UL * 60UL * 60UL * 1000UL; // 24 hours for production
/**
 * @brief Timestamp of the last heartbeat message sent.
 */
unsigned long lastHeartbeatTime = 0;

/**
 * @brief Setup function, runs once at startup or reset.
 *
 * Initializes serial communication, LoRaWAN module (if enabled),
 * and sensor states. Attempts to join the LoRaWAN network.
 */
void setup()
{
    // Disable watchdog timer early, in case it was left on from a previous reset
    wdt_disable();

    if (loraCommunication)
    {
        loraSerial.begin(57600);
    }

    // debugSerial.begin(9600); // Original line
#if ENABLE_DEBUG_SERIAL
    debugSerial.begin(9600);
#endif

    // Wait a maximum of 10s for Serial Monitor
    // while (!debugSerial && millis() < 10000) // Original line
    //     ; // Original line
#if ENABLE_DEBUG_SERIAL
    while (!debugSerial && millis() < 10000)
        ;
    debugSerial.println(F("DEBUG: Setup function started. Serial communication is working.")); // Diagnostic print
#endif

    if (loraCommunication)
    {
#if ENABLE_DEBUG_SERIAL
        debugSerial.println(F("-- STATUS"));
#endif
        ttn.showStatus();

#if ENABLE_DEBUG_SERIAL
        debugSerial.println(F("-- JOIN"));
#endif
        if (ttn.join(devEui, appEui, appKey)) {
#if ENABLE_DEBUG_SERIAL
            debugSerial.println(F("Join successful. Initializing heartbeat timer and previous states."));
#endif
            lastHeartbeatTime = millis(); // Initialize heartbeat timer after successful join
            prevDoorStatus = doorSensor.getDoorStatus();
            prevCatchStatus = catchSensor.getCatchStatus();
            prevDisplacementStatus = displacementSensor.getDisplacementStatus();
        } else {
#if ENABLE_DEBUG_SERIAL
            debugSerial.println(F("Join failed. Check keys and coverage."));
#endif
            // Consider how to handle failed join, e.g. retry or halt.
        }
    }
}

/**
 * @brief Main loop function, runs repeatedly.
 *
 * Checks sensor states, detects events (state changes or heartbeat interval),
 * prepares and sends LoRaWAN messages, and manages power-saving sleep modes.
 */
void loop()
{
    ///< Loop indication for debugging
#if ENABLE_DEBUG_SERIAL
    debugSerial.println("-- LOOP");
#endif
    // knightRider();

    ///< Check the red button (door sensor)
    if (redButton.isPressed() && !blackButton.isPressed())
    {
        // debugSerial.println(F("-- DOOR CLOSED")); // Debug moved to event detection
        doorSensor.setDoorStatus(true);
    }
    else
    {
        doorSensor.setDoorStatus(false);
    }

    ///< Check the black button (catch sensor)
    if (blackButton.isPressed() && !redButton.isPressed())
    {
        // debugSerial.println(F("-- CATCH DETECTED")); // Debug moved to event detection
        catchSensor.setCatchStatus(true);
    }
    else
    {
        catchSensor.setCatchStatus(false);
    }

    ///< Check the red and black button (displacement sensor)
    if (redButton.isPressed() && blackButton.isPressed())
    {
        // debugSerial.println(F("-- TRAP DISPLACEMENT DETECTED")); // Debug moved to event detection
        displacementSensor.setDisplacementStatus(true);
    }
    else
    {
        displacementSensor.setDisplacementStatus(false);
    }

    ///< Check the battery level
    // Consider reading battery level less frequently if it changes slowly, e.g., only before sending a message.
    uint8_t currentBatteryLevel = batterySensor.getBatteryLevel();
#if ENABLE_DEBUG_SERIAL
    debugSerial.print(F("-- BATTERY LEVEL: "));
    debugSerial.println(currentBatteryLevel);
#endif

    // --- Event Detection Logic ---
    bool sendLoraMessage = false;
    unsigned long currentTime = millis();

    // Get current sensor states
    bool currentDoorStatus = doorSensor.getDoorStatus();
    bool currentCatchStatus = catchSensor.getCatchStatus();
    bool currentDisplacementStatus = displacementSensor.getDisplacementStatus();

    // Check for state changes
    if (currentDoorStatus != prevDoorStatus) {
#if ENABLE_DEBUG_SERIAL
        debugSerial.print(F("Door status changed from ")); debugSerial.print(prevDoorStatus);
        debugSerial.print(F(" to ")); debugSerial.print(currentDoorStatus); debugSerial.println(F(". Triggering send."));
#endif
        sendLoraMessage = true;
        prevDoorStatus = currentDoorStatus;
    }
    if (currentCatchStatus != prevCatchStatus) {
#if ENABLE_DEBUG_SERIAL
        debugSerial.print(F("Catch status changed from ")); debugSerial.print(prevCatchStatus);
        debugSerial.print(F(" to ")); debugSerial.print(currentCatchStatus); debugSerial.println(F(". Triggering send."));
#endif
        sendLoraMessage = true;
        prevCatchStatus = currentCatchStatus;
    }
    if (currentDisplacementStatus != prevDisplacementStatus) {
#if ENABLE_DEBUG_SERIAL
        debugSerial.print(F("Displacement status changed from ")); debugSerial.print(prevDisplacementStatus);
        debugSerial.print(F(" to ")); debugSerial.print(currentDisplacementStatus); debugSerial.println(F(". Triggering send."));
#endif
        sendLoraMessage = true;
        prevDisplacementStatus = currentDisplacementStatus;
    }

    // Check for heartbeat
    // Ensure loraCommunication is true before checking heartbeat, to avoid sending if not joined.
    if (loraCommunication && (currentTime - lastHeartbeatTime >= HEARTBEAT_INTERVAL_MS)) {
#if ENABLE_DEBUG_SERIAL
        debugSerial.println(F("Heartbeat interval. Triggering send."));
#endif
        sendLoraMessage = true;
        lastHeartbeatTime = currentTime;
    }
    
    if (loraCommunication && sendLoraMessage)
    {
#if ENABLE_DEBUG_SERIAL
        debugSerial.println(F("Preparing to send LoRaWAN message due to event/heartbeat."));
#endif
        payloadEncoder encoder;

        // Set actual sensor values and other payload data
        // TODO: Get a real device ID, perhaps from MAC address or a constant
        encoder.set_id(1234); // Example ID
        // TODO: Define payload version, e.g., as a constant
        encoder.set_version(1); // Example version

        encoder.set_doorStatus(currentDoorStatus); 
        encoder.set_catchDetect(currentCatchStatus); 
        encoder.set_trapDisplacement(currentDisplacementStatus); 
        encoder.set_batteryStatus(currentBatteryLevel); 

        // TODO: Implement a way to get current Unix time if required by TTN/application
        // For now, using a placeholder. If TTN adds a timestamp, this might not be needed in payload.
        encoder.set_unixTime(0); // Example Unix time

        // Compose payload
        encoder.composePayload();
        // encoder.printPayloadEncoded(); // Optional: for debugging via Serial monitor

        uint8_t *payloadBuffer = encoder.getPayload();
        uint8_t payloadSize = encoder.getPayloadSize();

        // Send it off
        ttn.sendBytes(payloadBuffer, payloadSize);

        // Wait for the message to be sent
        // delay(10000); // Original delay. This delay might impact responsiveness and power consumption.
                      // Consider if this long delay is always needed or if ttn.sendBytes is blocking enough,
                      // or if the library provides a callback/status for TX completion.
        delay(1000); // Reduced delay. Verify necessity and actual time needed for TX completion or downlink window.
    }

    // After all operations, or if no message was sent, prepare for sleep.
    // If a message was sent, the delay has passed.
    // If no message was sent, we proceed to sleep directly.

    // Put LoRa module to sleep if loraCommunication is active.
    // The duration should be long enough to save power but short enough
    // to wake up for the next potential heartbeat or sensor check cycle.
    // Since WDT will wake MCU every ~1s for sensor checks,
    // we can put LoRa module to sleep for a slightly longer, but still relatively short period,
    // or rely on it waking up upon next command.
    // For now, let's not add specific ttn.sleep() here, assuming WDT wakes MCU for checks,
    // and ttn module wakes on next command if it auto-sleeps.
    // This part needs more refinement based on RN2483 power behavior and library.

    if (loraCommunication) {
#if ENABLE_DEBUG_SERIAL
        debugSerial.println(F("Putting LoRa module to sleep for heartbeat interval.")); // This message might be misleading now
#endif
        // ttn.sleep(HEARTBEAT_INTERVAL_MS); 
        // Commented out: Explicitly sleeping the LoRa module for the full HEARTBEAT_INTERVAL_MS here
        // might be inefficient if the MCU wakes up much sooner (e.g., every 1s via WDT).
        // The LoRa module (e.g., RN2483) often has its own auto-sleep mechanisms,
        // or the library might manage its power state more effectively after a command.
        // Leaving this commented relies on those implicit behaviors or requires further
        // investigation into optimal LoRa module sleep strategy for this specific hardware/library.
    }

    // Consider longer WDT intervals (e.g., WDTO_2S, WDTO_4S, WDTO_8S) for further power savings,
    // balancing responsiveness to sensor changes with power consumption.
    // Current: WDTO_1S wakes MCU approx. every 1 second.
    setupWatchdog(WDTO_1S); // Setup WDT for ~1 second interrupt
    system_sleep();         // Put MCU to sleep
}

// Watchdog Interrupt Service Routine
/**
 * @brief Watchdog Timer Interrupt Service Routine (ISR).
 *
 * This ISR is called when the Watchdog Timer wakes the MCU from sleep.
 * It disables the WDT to allow normal code execution until the next sleep cycle.
 */
ISR(WDT_vect) {
   wdt_disable(); // Disable watchdog until next sleep cycle
}

/**
 * @brief Puts the microcontroller unit (MCU) into a low-power sleep mode.
 *
 * Configures the deepest sleep mode (SLEEP_MODE_PWR_DOWN), disables peripherals
 * like the ADC to save power, and then puts the CPU to sleep.
 * Upon waking (e.g., by WDT interrupt), it re-enables peripherals.
 */
void system_sleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Choose the deepest sleep mode
  sleep_enable();
  
#if ENABLE_DEBUG_SERIAL
  debugSerial.println(F("Disabling ADC."));
#endif
  ADCSRA &= ~_BV(ADEN); // Disable ADC
  
  // Optional: disable ADC, BOD, etc. before sleep for more power saving
  // ADCSRA &= ~(1 << ADEN); // Disable ADC
  // MCUCR |= (1 << BODSE) | (1 << BODS); // Disable Brown Out Detector (sequence required)
  // MCUCR &= ~(1 << BODSE);


  sleep_cpu(); // Enter sleep mode

  // --- CPU WAKES UP HERE ---
  sleep_disable(); // Disable sleep mode
  
#if ENABLE_DEBUG_SERIAL
  debugSerial.println(F("Re-enabling ADC."));
#endif
  ADCSRA |= _BV(ADEN);  // Re-enable ADC
  
  // Optional: re-enable peripherals disabled before sleep
  // ADCSRA |= (1 << ADEN); // Re-enable ADC
  
  // WDT is disabled by ISR
}

/**
 * @brief Configures and enables the Watchdog Timer (WDT).
 *
 * The WDT is set up to generate an interrupt after a specified period,
 * waking the MCU from sleep. This allows for periodic sensor checks.
 *
 * @param period The timeout period for the WDT. Can be values like WDTO_1S, WDTO_2S, etc.
 *               (e.g., WDTO_1S for a 1-second timeout).
 */
void setupWatchdog(uint8_t period) {
  // Clear the reset flag
  MCUSR &= ~(1 << WDRF);

  // Configure WDT
  // In order to change WDE or the prescaler, we need to set WDCE (Watchdog Change Enable)
  // and WDE at the same time. WDE is then automatically cleared by hardware after 4 cycles.
  WDTCSR |= (1 << WDCE) | (1 << WDE);

  // Set new watchdog timeout prescaler
  WDTCSR = (1 << WDIE) | (period & 0x07) | ((period >> 3) & 0x01 ? (1 << WDP3) : 0x00); // Set WDIE for interrupt mode
  
  wdt_reset(); // Reset watchdog timer
}
