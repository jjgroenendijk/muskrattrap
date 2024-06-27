#ifndef DOORSENSOR_H
#define DOORSENSOR_H

/// An open door is set to 0 (false), a closed door is set to 1 (true)

class doorSensor  /// DoorStatus class declaration:
{
private:
    bool _doorStatus;

public:
    doorSensor();  /// constructor declaration, initializes the door sensor
    ~doorSensor(); /// destructor declaration, cleans up the door sensor

    // Function for getting the door STATUS
    bool getDoorStatus() { return _doorStatus;}
};

#endif // DOORSENSOR_H