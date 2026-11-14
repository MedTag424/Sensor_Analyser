
#include <gtest/gtest.h>
#include "MonitoringSystem.h"


// 1. TEST ADD SENSOR
TEST(MonitoringSystemTest, AddSensor) {

    MonitoringSystem system(5);

    system.addSensor(new Sensor(
        101, SensorType::TEMPERATURE, "T1", 25, 0, 50, true
    ));

    EXPECT_DOUBLE_EQ(system.getAverageTemp(), 25.0);
}


// 2. TEST AVERAGE TEMPERATURE
TEST(MonitoringSystemTest, AverageTemperature) {

    MonitoringSystem system(5);

    system.addSensor(new Sensor(
        101, SensorType::TEMPERATURE, "T1", 20, 0, 50, true
    ));

    system.addSensor(new Sensor(
        102, SensorType::TEMPERATURE, "T2", 40, 0, 50, true
    ));

    system.addSensor(new Sensor(
        103, SensorType::TEMPERATURE, "T3", 100, 0, 150, false
    ));

    EXPECT_DOUBLE_EQ(system.getAverageTemp(), 30.0);
}


// 3. TEST UPDATE SENSOR
TEST(MonitoringSystemTest, UpdateSensor) {

    MonitoringSystem system(5);

    system.addSensor(new Sensor(
        101, SensorType::TEMPERATURE, "T1", 20, 0, 50, true
    ));

    EXPECT_TRUE(system.updateSensor(101, 30));

    EXPECT_DOUBLE_EQ(system.getAverageTemp(), 30.0);

    EXPECT_FALSE(system.updateSensor(101, 100));

    EXPECT_DOUBLE_EQ(system.getAverageTemp(), 30.0);
}


// 4. TEST REMOVE SENSOR
TEST(MonitoringSystemTest, RemoveSensor) {

    MonitoringSystem system(5);

    system.addSensor(new Sensor(
        101, SensorType::TEMPERATURE, "T1", 20, 0, 50, true
    ));

    system.addSensor(new Sensor(
        102, SensorType::TEMPERATURE, "T2", 40, 0, 50, true
    ));

    EXPECT_TRUE(system.removeSensor(101));

    EXPECT_DOUBLE_EQ(system.getAverageTemp(), 40.0);

    EXPECT_FALSE(system.removeSensor(101));
}


// 5. TEST NO ACTIVE TEMPERATURE SENSORS
TEST(MonitoringSystemTest, NoActiveTemperatureSensors) {

    MonitoringSystem system(5);

    system.addSensor(new Sensor(
        101, SensorType::TEMPERATURE, "T1", 25, 0, 50, false
    ));

    EXPECT_DOUBLE_EQ(system.getAverageTemp(), 0.0);
}

