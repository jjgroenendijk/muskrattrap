#ifndef NODECODE_DISPLACEMENTSENSOR_H
#define NODECODE_DISPLACEMENTSENSOR_H

#include "IOTShieldConfig.h"
#include "HAN_IoT_Shield.h" // Required for iotShieldLED, LED_ON, LED_OFF, and LED objects

/**
 * @file displacementSensor.h
 * @brief Abstraction for the displacement sensor on the muskrat trap node.
 *
 * Provides methods to read and update the displacement status.
 */

/// Trap displacement detection is set to 0 (false), a trap displacement detected is set to 1 (true)

class displacementSensor /// DisplacementStatus class declaration
{
private:
    bool _displacementStatus;

public:
    displacementSensor();  /// constructor declaration, initializes the displacement sensor
    ~displacementSensor(); /// destructor declaration, cleans up the displacement sensor

    /**
     * @brief Get the current displacement status.
     * @return True if displaced
     */
    bool getDisplacementStatus() const;

    /**
     * @brief Update the displacement status from hardware or simulation.
     */
    void update();

    // Function for getting the displacement STATUS
    bool getDisplacementStatus() { return _displacementStatus; }

    void setDisplacementStatus(bool displacementStatus);
};

#endif // NODECODE_DISPLACEMENTSENSOR_H