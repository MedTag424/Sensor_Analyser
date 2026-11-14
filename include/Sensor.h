
#pragma once

#include <string>

enum class SensorType {
    TEMPERATURE,
    PRESSURE,
    HUMIDITY,
    VOLTAGE
};

class Sensor {
private:
    int id;
    SensorType type;
    std::string name;
    double value;
    double minValue;
    double maxValue;
    bool active;

public:
    Sensor(int i, SensorType n, const std::string& N,
           double v, double min, double max, bool state);

    ~Sensor() = default;

    int getId() const;
    SensorType getType() const;
    std::string getName() const;
    double getValue() const;
    double getMinValue() const;
    double getMaxValue() const;
    bool getActive() const;

    bool changeValue(double i);
    std::string getStatus() const;
    void Activate(bool state);
    bool normalFunction() const;
    std::string getTypeName() const;
    void displaySensor() const;
};

