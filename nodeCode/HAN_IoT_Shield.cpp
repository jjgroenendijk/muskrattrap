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
 * \file HAN_IoT_Shield.cpp
 * \brief Implementation of the HAN IoT Shield library.
 * \author Remko Welling (remko.welling@han.nl
 */

#include "HAN_IoT_Shield.h"

// Functions for class: iotShieldPotmeter
/*!
 * \brief Constructor for iotShieldPotmeter.
 * \param hardwarePin The analog pin connected to the potentiometer.
 * \param minimumValue The minimum value the potentiometer can return.
 * \param maximumValue The maximum value the potentiometer can return.
 */
iotShieldPotmeter::iotShieldPotmeter(uint8_t hardwarePin, 
                                     int minimumValue, 
                                     int maximumValue):
  _pin(hardwarePin),
  _aRange(maximumValue),
  _bRange(minimumValue)
{  
}

/*!
 * \brief Destructor for iotShieldPotmeter.
 */
iotShieldPotmeter::~iotShieldPotmeter(){};

/*!
 * \brief Reads the value from the potentiometer.
 * \return The current value of the potentiometer, mapped to the specified range.
 */
float iotShieldPotmeter::getValue()
{
  int rawValue    = analogRead(_pin);
  int mappedValue = map(rawValue, 0, 1023, _aRange, _bRange);
  return static_cast<float>(mappedValue);
}

// Functions for class: iotShieldButton
/*!
 * \brief Constructor for iotShieldButton.
 * \param hardwarePin The digital pin connected to the button.
 */
iotShieldButton::iotShieldButton(uint8_t hardwarePin):
  _pin(hardwarePin),
  _lastReadState(LOW),
  _lastStableState(LOW),
  _debounceDelay(50),
  _lastDebounceTime(0)
{  
}

/*!
 * \brief Destructor for iotShieldButton.
 */
iotShieldButton::~iotShieldButton(){};

/*!
 * \brief Gets the current state of the button.
 * \return BUTTON_PRESSED or BUTTON_RELEASED.
 */
buttonState_t iotShieldButton::getState()
{
  uint8_t state = digitalRead(_pin);
  buttonState_t returnValue = BUTTON_RELEASED;
  
  // test if red pushbutton is pressed.
  if(state == PRESSED)
  {
    returnValue = BUTTON_PRESSED;
  }
  return returnValue;
}

/*!
 * \brief Checks if the button is currently pressed.
 * \return True if the button is pressed, false otherwise.
 */
bool iotShieldButton::isPressed()
{
  uint8_t state = digitalRead(_pin);
  bool returnValue = false;
  
  // test if red pushbutton is pressed.
  if(state == PRESSED)
  {
    returnValue = true;
  }
  return returnValue;
};

bool iotShieldButton::wasPressedDebounced() {
    bool reading = (digitalRead(_pin) == PRESSED);
    if (reading != _lastReadState) {
        _lastDebounceTime = millis();
    }
    _lastReadState = reading;
    if ((millis() - _lastDebounceTime) > _debounceDelay) {
        if (reading != _lastStableState) {
            _lastStableState = reading;
            if (_lastStableState) {
                // Rising edge: button was just pressed
                return true;
            }
        }
    }
    return false;
}

// Functions for class: iotShieldLED
/*!
 * \brief Constructor for iotShieldLED.
 * \param hardwarePin The digital pin connected to the LED.
 */
iotShieldLED::iotShieldLED(uint8_t hardwarePin):
  _pin(hardwarePin)
{  
   pinMode(_pin, OUTPUT);
}

/*!
 * \brief Destructor for iotShieldLED.
 */
iotShieldLED::~iotShieldLED(){};

/*!
 * \brief Sets the state of the LED.
 * \param state The desired state of the LED (LED_ON or LED_OFF).
 */
void iotShieldLED::setState(ledState_t state)
{
  if( state == LED_ON)
  {
    digitalWrite(_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  else
  {
    digitalWrite(_pin, LOW);   // turn the LED on (HIGH is the voltage level)
  }
}

// Functions for class: iotShieldTempsensor
/*!
 * \brief Constructor for iotShieldTempSensor.
 * \param hardwarePin The digital pin connected to the temperature sensor's OneWire interface.
 */
iotShieldTempSensor::iotShieldTempSensor(uint8_t hardwarePin):
  _temperature(0.0),
  _oneWireInterface(hardwarePin),
  _sensors(&_oneWireInterface)
{
  // Start up the Dallas Temperature library
  _sensors.begin();
}

/*!
 * \brief Destructor for iotShieldTempSensor.
 */
iotShieldTempSensor::~iotShieldTempSensor(){};

/*!
 * \brief Reads the temperature from the sensor.
 * \return The temperature in degrees Celsius.
 */
float iotShieldTempSensor::getTemperatureCelsius()
{
  _sensors.requestTemperatures();              // Send the command to get temperatures from single wire sensors
  _temperature = _sensors.getTempCByIndex(0);  // Read the temperature from the first sensor 
  return _temperature;
}
