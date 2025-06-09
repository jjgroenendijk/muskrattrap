#ifndef NODECODE_DOORSENSOR_H
#define NODECODE_DOORSENSOR_H

#include "IOTShieldConfig.h"

/// An open door is set to 0 (false), a closed door is set to 1 (true)

class doorSensor /// DoorStatus class declaration:
{
private:
    bool _doorStatus;

public:
    doorSensor();  /// constructor declaration, initializes the door sensor
    ~doorSensor(); /// destructor declaration, cleans up the door sensor

    // Function for getting the door STATUS
    bool getDoorStatus() { return _doorStatus; }

    void setDoorStatus(bool doorStatus);
};

#endif // NODECODE_DOORSENSOR_H