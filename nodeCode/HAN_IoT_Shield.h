/*--------------------------------------------------------------------
  This file is part of the HAN IoT shield library.

  This code is free software:
  you can redistribute it and/or modify it under the terms of a Creative
  Commons Attribution-NonCommercial 4.0 International License
  (http://creativecommons.org/licenses/by-nc/4.0/) by
  Remko Welling (https://ese.han.nl/~rwelling/) E-mail: remko.welling@han.nl

  The program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  --------------------------------------------------------------------*/

/*!
 * \file HAN_IoT_Shield.h
 * \brief functions to use hardware peripherals on the HAN IoT Shield.
 * \author Remko Welling (remko.welling@han.nl)
 * \date 2024-03-15
 * \version 1.3
 * 
 * Version|Date        |Note
 * -------|------------|----
 * 1.3    | 15- 3-2024 | Reviewed and updated Doxygen documentation. Addressed general TODO for documentation completeness.
 * 1.2    |  4- 2-2019 | Modified include "arduino.h" to "Arduino.h" to be linux compliant. Added Doxygen comments.
 * 1.1    | 27-12-2018 | Updates on documentation
 * 1.0    | 15-12-2018 | Initial version
 * 
 * 
 */

 /*!
  \mainpage HAN IoT Shield Library
  
  \section intro_sec Introduction
  This library provides an interface to the hardware peripherals on the HAN IoT Shield 
  designed for use with Arduino microcontrollers. It simplifies the interaction with 
  LEDs, pushbuttons, potentiometers, and the Dallas one-wire temperature sensor 
  available on the shield.

  \section features_sec Features
  - Easy control of 4 LEDs (2 red, 2 green).
  - Reading states of 2 pushbuttons (red and black).
  - Reading values from 2 potentiometers.
  - Reading temperature from the onboard Dallas DS18S20 sensor.
  - Class-based approach for organized code.

  \section shield_layout_sec Shield Layout
  Refer to the ASCII art diagram within the `HAN_IoT_Shield.h` file for a visual 
  representation of the shield components and their typical placement.

  \section usage_sec Usage
  1. Include `HAN_IoT_Shield.h` in your Arduino sketch.
  2. Create objects of the provided classes (e.g., `iotShieldLED`, `iotShieldButton`).
  3. Use the methods of these objects to control or read from the shield components.

  Example:
  \code{.cpp}
  #include "HAN_IoT_Shield.h"

  iotShieldLED myLed(PIN_LED_1_RED);
  iotShieldButton myButton(PIN_SWITCH_RED);

  void setup() {
    myLed.setState(LED_ON);
  }

  void loop() {
    if (myButton.isPressed()) {
      myLed.setState(LED_OFF);
    } else {
      myLed.setState(LED_ON);
    }
    delay(100);
  }
  \endcode

  ## Shield layout

  
  \verbatim
  
    +-----------------------------+
    | [gr-1] [gr-2] [gr-2] [gr-2] | <- 4 grove connectors
    |                             |
    |   +--------+   +--------+   |  
    |   |        |   |        |   |  
    |   |   P1   |   |   P2   |   |  <- 2 potentiometers
    |   |        |   |        |   |  
    |   +--------+   +--------+   |  
    |                             |
    |     +----+       +----+     |  
    |     |Red |       |Blck|     |  <- 2 push button switches
    |     +----+       +----+     |  
    |                             |
    | [led1] [led3] [led2] [led4] |  <- 4 LEDs
    |                             |
    | [Dallas]                    |  <- Dallas one wire temperature sensor
    +-\                 /---------+
       \---------------/

       
  \endverbatim

  
 */


#ifndef _HAN_IOT_SHIELD_H_
#define _HAN_IOT_SHIELD_H_

#include <Arduino.h> 

#include <OneWire.h>            // one wire library for Dallas one wire sensor
#include <DallasTemperature.h>  // Dallas one wire sensor library

// Defines for LEDs
#define PIN_LED_1_RED    3     ///< @brief Arduino pin for LED 1 (Red).
#define PIN_LED_2_RED    4     ///< @brief Arduino pin for LED 2 (Red).
#define PIN_LED_3_GRN    5     ///< @brief Arduino pin for LED 3 (Green).
#define PIN_LED_4_GRN    6     ///< @brief Arduino pin for LED 4 (Green).

// Defines for pushbutton
#define PIN_SWITCH_BLACK 8     ///< @brief Arduino pin for the Black pushbutton.
#define PIN_SWITCH_RED   9     ///< @brief Arduino pin for the Red pushbutton.
#define RELEASED HIGH          ///< @brief Logic level when a pushbutton is released.
#define PRESSED  LOW           ///< @brief Logic level when a pushbutton is pressed.

// defines for potentiometers.
#define PIN_POT_RED      A0    ///< @brief Arduino analog pin for Potentiometer 1 (Red knob).
#define PIN_POT_WHITE    A1    ///< @brief Arduino analog pin for Potentiometer 2 (White knob).

// defines for Dallase one wire sensor
#define PIN_DALLAS       2     ///< @brief Arduino pin for the Dallas DS18S20 one-wire temperature sensor.

/**
 * @class iotShieldPotmeter
 * @brief Manages a potentiometer on the HAN IoT Shield.
 *
 * This class allows reading the analog value from a potentiometer and mapping it
 * to a specified range.
 */
class iotShieldPotmeter
{
private:
  uint8_t _pin;                 ///< @brief Hardware pin to which the potentiometer is connected.
  int16_t _aRange;            ///< @brief Minimum value of the output range.
  int16_t _bRange;            ///< @brief Maximum value of the output range.

public:
  /**
   * @brief Constructor for iotShieldPotmeter.
   * @param hardwarePin Arduino analog input pin to which the potentiometer is connected.
   * @param minimumValue The minimum value of the desired output range. Default is 0.
   * @param maximumValue The maximum value of the desired output range. Default is 1023.
   * @pre Requires an analog input pin. The potentiometer should apply 0 to VCC to this pin.
   */
  iotShieldPotmeter(uint8_t hardwarePin, int minimumValue = 0, int maximumValue = 1023);

  /**
   * @brief Default destructor.
   */
  ~iotShieldPotmeter();

  /**
   * @brief Reads the value from the potentiometer and maps it to the specified range.
   * This function transposes the raw analog value (0-1023) into the range
   * specified by `minimumValue` and `maximumValue` during object creation.
   * @return float The mapped value from the potentiometer within the specified range.
   */
  float getValue(void);
};

/**
 * @enum buttonState_t
 * @brief Represents the state of a pushbutton.
 */
typedef enum { 
    BUTTON_PRESSED,   ///< Indicates the button is currently pressed.
    BUTTON_RELEASED   ///< Indicates the button is currently released.
} buttonState_t;
                 
/**
 * @class iotShieldButton
 * @brief Manages a pushbutton on the HAN IoT Shield.
 *
 * This class allows reading the state of a pushbutton (pressed or released).
 */
class iotShieldButton
{
private:
  uint8_t _pin;                 ///< @brief Hardware pin to which the pushbutton is connected.

public:
  /**
   * @brief Constructor for iotShieldButton.
   * @param hardwarePin Arduino digital input pin to which the button is connected.
   * @pre Requires a digital input pin. The button should deliver HIGH when RELEASED and LOW when PRESSED.
   */
  iotShieldButton(uint8_t hardwarePin);

  /**
   * @brief Default destructor.
   */
  ~iotShieldButton();

  /**
   * @brief Gets the current state of the pushbutton as an enum.
   * @return buttonState_t The current state (BUTTON_PRESSED or BUTTON_RELEASED).
   */
  buttonState_t getState();

  /**
   * @brief Checks if the pushbutton is currently pressed.
   * @return bool True if the button is pressed, false otherwise.
   */
  bool isPressed();
};

/**
 * @enum ledState_t
 * @brief Represents the state of an LED.
 */
typedef enum { 
    LED_ON,   ///< Indicates the LED should be turned on.
    LED_OFF   ///< Indicates the LED should be turned off.
} ledState_t;

/**
 * @class iotShieldLED
 * @brief Manages an LED on the HAN IoT Shield.
 *
 * This class allows controlling the state of an LED (on or off).
 */
class iotShieldLED
{
private:
  uint8_t _pin;                 ///< @brief Hardware pin to which the LED is connected.

public:
  /**
   * @brief Constructor for iotShieldLED.
   * @param hardwarePin Arduino digital output pin to which the LED is connected.
   * @pre Requires a digital output pin.
   */
  iotShieldLED(uint8_t hardwarePin);

  /**
   * @brief Default destructor.
   */
  ~iotShieldLED();

  /**
   * @brief Sets the state of the LED.
   * @param state The desired state of the LED (LED_ON or LED_OFF).
   */
  void setState(ledState_t state);

};

/**
 * @class iotShieldTempSensor
 * @brief Manages the Dallas one-wire temperature sensor on the HAN IoT Shield.
 *
 * This class allows reading the temperature in degrees Celsius from the DS18S20 sensor.
 */
class iotShieldTempSensor
{
private:
  float   _temperature;         ///< @brief Local storage for the last read temperature.
  OneWire _oneWireInterface;    ///< @brief OneWire interface object for communication with the sensor.
  DallasTemperature _sensors;   ///< @brief DallasTemperature library object to manage sensors on the OneWire bus.
  
public:
  /**
   * @brief Constructor for iotShieldTempSensor.
   * @param hardwarePin Arduino digital pin to which the Dallas sensor's data line is connected. Defaults to PIN_DALLAS.
   * @pre Requires a digital pin for the OneWire interface.
   */
  iotShieldTempSensor(uint8_t hardwarePin = PIN_DALLAS);

  /**
   * @brief Default destructor.
   */
  ~iotShieldTempSensor();

  /**
   * @brief Reads the current temperature from the Dallas sensor.
   * @return float The temperature in degrees Celsius. Returns a pre-defined error value if the read fails (check DallasTemperature library specifics).
   */
  float getTemperatureCelsius();

};

#endif // _HAN_IOT_SHIELD_H_
