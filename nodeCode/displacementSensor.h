#ifndef DISPLACEMENTSENSOR_H
#define DISPLACEMENTSENSOR_H

#include "IOTShieldConfig.h"

/**
 * @class displacementSensor
 * @brief Manages the status of a trap displacement sensor.
 *
 * This class simulates a displacement sensor. It uses an LED (rightRedLED)
 * on the HAN IoT Shield to visually indicate whether the trap has been displaced.
 * A status of `false` means no displacement, and `true` means displacement is detected.
 */
class displacementSensor
{
private:
    bool _displacementStatus; ///< Stores the current displacement status (false = not displaced, true = displaced).

public:
    /**
     * @brief Construct a new displacementSensor object.
     * Initializes the displacement status to `false` (not displaced).
     */
    displacementSensor();

    /**
     * @brief Destroy the displacementSensor object.
     * Performs cleanup if necessary.
     */
    ~displacementSensor();

    /**
     * @brief Get the current displacement status.
     * @return bool The current displacement status (`true` if displaced, `false` otherwise).
     */
    bool getDisplacementStatus() { return _displacementStatus; }

    /**
     * @brief Set the displacement status and update the corresponding LED.
     * If displacement is detected (status is true), the right red LED is turned on.
     * Otherwise, it is turned off.
     * @param displacementStatus The new displacement status to set.
     */
    void setDisplacementStatus(bool displacementStatus);
};

#endif // DISPLACEMENTSENSOR_H