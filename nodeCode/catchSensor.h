#ifndef CATCHESENSOR_H
#define CATCHESENSOR_H

#include "IOTShieldConfig.h"

/**
 * @class catchSensor
 * @brief Manages the status of a catch detection mechanism.
 *
 * This class simulates a catch sensor. It uses an LED (leftGreenLED)
 * on the HAN IoT Shield to visually indicate whether a catch has been detected.
 * A status of `false` means no catch, and `true` means a catch is detected.
 */
class catchSensor
{
private:
    bool _catchStatus; ///< Stores the current catch status (false = no catch, true = catch detected).

public:
    /**
     * @brief Construct a new catchSensor object.
     * Initializes the catch status to `false` (no catch).
     */
    catchSensor();

    /**
     * @brief Destroy the catchSensor object.
     * Performs cleanup if necessary.
     */
    ~catchSensor();

    /**
     * @brief Get the current catch status.
     * @return bool The current catch status (`true` if catch detected, `false` otherwise).
     */
    bool getCatchStatus() { return _catchStatus; }

    /**
     * @brief Set the catch status and update the corresponding LED.
     * If a catch is detected (status is true), the left green LED is turned on.
     * Otherwise, it is turned off.
     * @param catchStatus The new catch status to set.
     */
    void setCatchStatus( bool catchStatus );
};

#endif // CATCHESENSOR_H