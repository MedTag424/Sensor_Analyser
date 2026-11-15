
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

    //Changes to match the backend and not needing to access methods through the manager

      int getSensorCount();
      Sensor* getSensor(int index);
      Sensor* findSensor(int id);

      int getActiveCount();
      int getCriticalCount();
      int getInactiveCount();

      std::array<int, 4> getBreakdown();
};

