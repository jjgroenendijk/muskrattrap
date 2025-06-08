#ifndef CATCHESENSOR_H
#define CATCHESENSOR_H

#include "IOTShieldConfig.h"

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

#endif // CATCHESENSOR_H