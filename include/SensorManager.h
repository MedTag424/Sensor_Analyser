
#pragma once

#include "Sensor.h"
#include <array>

class SensorManager {
private:
    Sensor** sensors;
    int capacity;
    int count;

public:
    SensorManager(int initialCapacity = 5);
    ~SensorManager();

    int getCount();
    void resizeSensor();
    Sensor* getSensor(int i);
    void addSensor(Sensor* s);
    int sensorIndex(int ID);
    Sensor* findSensor(int ID);
    bool removeSensor(int ID);
    void displayAll();
    int getActiveCount();
    int getCriticalCount();
    int getInactiveCount();
    bool updateSensor(int id, double newValue);
    std::array<int, 4> breakdown();

    SensorManager(const SensorManager&) = delete;
    SensorManager& operator=(const SensorManager&) = delete;
};

