#ifndef NODECODE_CATCHSENSOR_H
#define NODECODE_CATCHSENSOR_H

#include "IOTShieldConfig.h"
#include "HAN_IoT_Shield.h" // Required for iotShieldLED, LED_ON, LED_OFF, and LED objects
#include "HAN_IoT_Shield.h" // For rightRedLED

/**
 * @file catchSensor.h
 * @brief Abstraction for the catch sensor on the muskrat trap node.
 *
 * Provides methods to read and update the catch status.
 */

/// A catch detection is set to 0 (false), a catch detected is set to 1 (true)

class catchSensor /// CatchStatus class declaration:
{
private:
    bool _catchStatus;

public:
    catchSensor();  /// constructor declaration, initializes the catch sensor
    ~catchSensor(); /// destructor declaration, cleans up the catch sensor

    /**
     * @brief Get the current catch status.
     * @return True if catch detected
     */
    bool getCatchStatus() const;

    /**
     * @brief Update the catch status from hardware or simulation.
     */
    void update();

    void setCatchStatus( bool catchStatus );
};

#endif // NODECODE_CATCHSENSOR_H