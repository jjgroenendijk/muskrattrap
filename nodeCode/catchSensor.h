#ifndef NODECODE_CATCHSENSOR_H
#define NODECODE_CATCHSENSOR_H

#include "IOTShieldConfig.h"
#include "HAN_IoT_Shield.h" // Required for iotShieldLED, LED_ON, LED_OFF, and LED objects
#include "HAN_IoT_Shield.h" // For rightRedLED

/// A catch detection is set to 0 (false), a catch detected is set to 1 (true)

class catchSensor /// CatchStatus class declaration:
{
private:
    bool _catchStatus;

public:
    catchSensor();  /// constructor declaration, initializes the catch sensor
    ~catchSensor(); /// destructor declaration, cleans up the catch sensor

    // Function for getting the catch STATUS
    bool getCatchStatus() { return _catchStatus; }

    void setCatchStatus( bool catchStatus );
};

#endif // NODECODE_CATCHSENSOR_H