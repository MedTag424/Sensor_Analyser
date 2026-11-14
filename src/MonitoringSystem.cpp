
#include "MonitoringSystem.h"

#include <iostream>

MonitoringSystem::MonitoringSystem(int capacity) : manager(capacity) {}

void MonitoringSystem::addSensor(Sensor* s) {
    manager.addSensor(s);
}

bool MonitoringSystem::removeSensor(int id) {
    return manager.removeSensor(id);
}

bool MonitoringSystem::updateSensor(int id, double value) {
    return manager.updateSensor(id, value);
}

double MonitoringSystem::getAverageTemp() {
    double total = 0;
    double tempCount = 0;

    for (int i = 0; i < manager.getCount(); i++) {
        Sensor* s = manager.getSensor(i);

        if (s != nullptr &&
            s->getType() == SensorType::TEMPERATURE &&
            s->getActive()) {
            total += s->getValue();
            tempCount++;
        }
    }

    return (tempCount == 0) ? 0 : (total / tempCount);
}

void MonitoringSystem::displayReport() {
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "       INDUSTRIAL MONITORING SYSTEM     \n";
    std::cout << "========================================\n";

    std::cout << "GENERAL STATS" << std::endl;
    std::cout << "-------------\n";
    std::cout << "Total snesors:" << manager.getCount() << std::endl;
    std::cout << "Active sensors:" << manager.getActiveCount() << std::endl;
    std::cout << "Inactive sensors:" << manager.getInactiveCount() << std::endl;
    std::cout << "Critical sensors:" << manager.getCriticalCount() << std::endl;
    std::cout << "Average Temperature:" << getAverageTemp() << std::endl;
    std::cout << "\n";

    std::cout << "SENSOR BREAKDOWN\n";
    std::cout << "-------------\n";

    auto types = manager.breakdown();

    std::cout << "Temperature sensors:" << types[0] << std::endl;
    std::cout << "Pressure sensors:" << types[1] << std::endl;
    std::cout << "Humidity sensors:" << types[2] << std::endl;
    std::cout << "Voltage sensors:" << types[3] << std::endl;
    std::cout << "\n";

    std::cout << "ALERTS\n";
    std::cout << "------\n";

    if (manager.getCriticalCount() == 0) {
        std::cout << "None\n";
    }
    else {
        for (int i = 0; i < manager.getCount(); i++) {
            if (manager.getSensor(i)->getStatus() == "Critical") {
                std::cout << "[CRITICAL]"
                          << manager.getSensor(i)->getTypeName()
                          << ":"
                          << manager.getSensor(i)->getValue();
            }
        }
    }

    std::cout << "======================================\n";
}

