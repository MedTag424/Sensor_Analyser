
#include "Sensor.h"
#include <iostream>
#include <stdexcept>

Sensor::Sensor(int i, SensorType n, const std::string& N,
               double v, double min, double max, bool state) :
        id(i),
        type(n),
        name(N),
        value(v),
        minValue(min),
        maxValue(max),
        active(state)
{
    if(minValue > maxValue) {
        throw std::invalid_argument("Invalid sensor range");
    }
}

int Sensor::getId() const {
    return id;
}

SensorType Sensor::getType() const {
    return type;
}

std::string Sensor::getName() const {
    return name;
}

double Sensor::getValue() const {
    return value;
}

double Sensor::getMinValue() const {
    return minValue;
}

double Sensor::getMaxValue() const {
    return maxValue;
}

bool Sensor::getActive() const {
    return active;
}

bool Sensor::changeValue(double i) {
    if(i <= maxValue && i >= minValue) {
        value = i;
        return true;
    }
    return false;
}

std::string Sensor::getStatus() const {
    if(active) {
        if(value <= maxValue && value >= minValue) {
            return "Normnal";
        }
        return "Critical";
    }
    return "Inactive";
}

void Sensor::Activate(bool state) {
    active = state;
}

bool Sensor::normalFunction() const {
    return (value <= maxValue && value >= minValue) ? true : false;
}

std::string Sensor::getTypeName() const {
    switch(type) {
        case SensorType::TEMPERATURE:
            return "Temperature";

        case SensorType::PRESSURE:
            return "Pressure";

        case SensorType::HUMIDITY:
            return "Humidity";

        case SensorType::VOLTAGE:
            return "Voltage";
    }

    return "Unknown";
}

void Sensor::displaySensor() const {
    std::cout << "Sesnor Information :" << std::endl;
    std::cout << "ID:" << id << std::endl;
    std::cout << "Type:" << getTypeName() << std::endl;
    std::cout << "Name:" << name << std::endl;
    std::cout << "Current Value:" << value << std::endl;
    std::cout << "Minimum Value:" << minValue << std::endl;
    std::cout << "State:" << getStatus() << std::endl;
}

