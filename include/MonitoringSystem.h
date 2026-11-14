
#pragma once

#include "SensorManager.h"

class MonitoringSystem {
private:
    SensorManager manager;

public:
    MonitoringSystem(int capacity = 5);

    void addSensor(Sensor* s);
    bool removeSensor(int id);
    bool updateSensor(int id, double value);
    double getAverageTemp();
    void displayReport();
};

