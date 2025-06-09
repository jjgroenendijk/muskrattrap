#ifndef NODECODE_DISPLACEMENTSENSOR_H
#define NODECODE_DISPLACEMENTSENSOR_H

#include "IOTShieldConfig.h"

/// Trap displacement detection is set to 0 (false), a trap displacement detected is set to 1 (true)

class displacementSensor /// DisplacementStatus class declaration
{
private:
    bool _displacementStatus;

public:
    displacementSensor();  /// constructor declaration, initializes the displacement sensor
    ~displacementSensor(); /// destructor declaration, cleans up the displacement sensor

    // Function for getting the displacement STATUS
    bool getDisplacementStatus() { return _displacementStatus; }

    void displacementSensor::setDisplacementStatus(bool displacementStatus);
};

#endif // NODECODE_DISPLACEMENTSENSOR_H