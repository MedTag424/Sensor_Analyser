
#include "SensorManager.h"

#include <iostream>
#include <stdexcept>

SensorManager::SensorManager(int initialCapacity) :
    capacity(initialCapacity),
    count(0)
{
    if (initialCapacity <= 0) {
        throw std::invalid_argument("Capacity must be positive");
    }

    sensors = new Sensor*[capacity];
}

SensorManager::~SensorManager() {
    for (int i = 0; i < count; i++) {
        delete sensors[i];
    }

    delete[] sensors;
}

int SensorManager::getCount() {
    return count;
}

void SensorManager::resizeSensor() {
    int newCapacity = capacity * 2;
    Sensor** new_sensors = new Sensor*[newCapacity];

    for (int i = 0; i < count; i++) {
        new_sensors[i] = sensors[i];
    }

    capacity = newCapacity;
    delete[] sensors;
    sensors = new_sensors;
}

Sensor* SensorManager::getSensor(int i) {
    if (i < count && i >= 0)
        return sensors[i];

    return nullptr;
}

void SensorManager::addSensor(Sensor* s) {
    if (s == nullptr) {
        return;
    }

    if (capacity <= count) {
        resizeSensor();
    }

    sensors[count] = s;
    count++;
}

int SensorManager::sensorIndex(int ID) {
    int i;

    for (i = 0; i < count; i++) {
        if (sensors[i]->getId() == ID) {
            return i;
        }
    }

    return -1;
}

Sensor* SensorManager::findSensor(int ID) {
    int i;

    for (i = 0; i < count; i++) {
        if (sensors[i]->getId() == ID) {
            return sensors[i];
        }
    }

    return nullptr;
}

bool SensorManager::removeSensor(int ID) {
    int index = sensorIndex(ID);

    if (index == -1) {
        return false;
    }

    delete sensors[index];

    if (index < count - 1) {
        for (int i = index; i < count - 1; i++) {
            sensors[i] = sensors[i + 1];
        }
    }

    count--;
    return true;
}

void SensorManager::displayAll() {
    for (int i = 0; i < count; i++) {
        std::cout << "Sensor" << i << ":" << std::endl;
        sensors[i]->displaySensor();
        std::cout << std::endl;
    }
}

int SensorManager::getActiveCount() {
    int c = 0;

    for (int i = 0; i < count; i++) {
        if (sensors[i]->getActive()) {
            c++;
        }
    }

    return c;
}

int SensorManager::getCriticalCount() {
    int c = 0;

    for (int i = 0; i < count; i++) {
        if (sensors[i]->getStatus() == "Critical") {
            c++;
        }
    }

    return c;
}

int SensorManager::getInactiveCount() {
    int c = 0;

    for (int i = 0; i < count; i++) {
        if (sensors[i]->getStatus() == "Inactive") {
            c++;
        }
    }

    return c;
}

bool SensorManager::updateSensor(int id, double newValue) {
    Sensor* sensor = findSensor(id);

    if (sensor == nullptr) {
        return false;
    }

    return sensor->changeValue(newValue);
}

std::array<int, 4> SensorManager::breakdown() {
    std::array<int, 4> types = {0, 0, 0, 0};

    for (int i = 0; i < count; i++) {
        switch (sensors[i]->getType()) {

            case SensorType::TEMPERATURE:
                types[0]++;
                break;

            case SensorType::PRESSURE:
                types[1]++;
                break;

            case SensorType::HUMIDITY:
                types[2]++;
                break;

            case SensorType::VOLTAGE:
                types[3]++;
                break;
        }
    }

    return types;
}

