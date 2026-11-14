
#include <gtest/gtest.h>
#include "SensorManager.h"


// 1. TEST ADD SENSOR
TEST(SensorManagerTest, AddSensor) {

    SensorManager manager(5);

    manager.addSensor(new Sensor(
        101, SensorType::TEMPERATURE, "Boiler", 24.5, 0, 50, true
    ));

    manager.addSensor(new Sensor(
        102, SensorType::HUMIDITY, "Humid", 32, 0, 50, true
    ));

    EXPECT_EQ(manager.getCount(), 2);
}


// 2. TEST FIND SENSOR
TEST(SensorManagerTest, FindSensor) {

    SensorManager manager(5);

    manager.addSensor(new Sensor(
        101, SensorType::TEMPERATURE, "Boiler", 24.5, 0, 50, true
    ));

    EXPECT_NE(manager.findSensor(101), nullptr);
    EXPECT_EQ(manager.findSensor(423), nullptr);
}


// 3. TEST REMOVE SENSOR
TEST(SensorManagerTest, RemoveSensor) {

    SensorManager manager(5);

    manager.addSensor(new Sensor(
        101, SensorType::TEMPERATURE, "Boiler", 24.5, 0, 50, true
    ));

    EXPECT_TRUE(manager.removeSensor(101));
    EXPECT_EQ(manager.getCount(), 0);
    EXPECT_FALSE(manager.removeSensor(101));
}


// 4. TEST UPDATE SENSOR
TEST(SensorManagerTest, UpdateSensor) {

    SensorManager manager(5);

    manager.addSensor(new Sensor(
        101, SensorType::TEMPERATURE, "Boiler", 24.5, 0, 50, true
    ));

    EXPECT_TRUE(manager.updateSensor(101, 35.0));
    EXPECT_DOUBLE_EQ(manager.findSensor(101)->getValue(), 35.0);

    EXPECT_FALSE(manager.updateSensor(101, 100.0));
    EXPECT_DOUBLE_EQ(manager.findSensor(101)->getValue(), 35.0);
}


// 5. TEST DYNAMIC RESIZING
TEST(SensorManagerTest, ResizeSensor) {

    SensorManager manager(2);

    for (int i = 0; i < 10; i++) {
        manager.addSensor(new Sensor(
            100 + i, SensorType::TEMPERATURE,
            "Sensor", 25.0, 0, 50, true
        ));
    }

    EXPECT_EQ(manager.getCount(), 10);

    for (int i = 0; i < 10; i++) {
        EXPECT_NE(manager.findSensor(100 + i), nullptr);
    }
}


// 6. TEST ACTIVE SENSOR COUNT
TEST(SensorManagerTest, ActiveCount) {

    SensorManager manager(5);

    manager.addSensor(new Sensor(
        101, SensorType::TEMPERATURE, "T1", 25, 0, 50, true
    ));

    manager.addSensor(new Sensor(
        102, SensorType::HUMIDITY, "H1", 40, 0, 100, true
    ));

    manager.addSensor(new Sensor(
        103, SensorType::PRESSURE, "P1", 50, 0, 100, false
    ));

    EXPECT_EQ(manager.getActiveCount(), 2);
}


// 7. TEST CRITICAL SENSOR COUNT
TEST(SensorManagerTest, CriticalCount) {

    SensorManager manager(5);

    manager.addSensor(new Sensor(
        101, SensorType::TEMPERATURE, "T1", 25, 0, 50, true
    ));

    manager.addSensor(new Sensor(
        102, SensorType::PRESSURE, "P1", 115, 10, 100, true
    ));

    manager.addSensor(new Sensor(
        103, SensorType::HUMIDITY, "H1", 40, 0, 100, true
    ));

    EXPECT_EQ(manager.getCriticalCount(), 1);
}


// 8. TEST SENSOR TYPE BREAKDOWN
TEST(SensorManagerTest, Breakdown) {

    SensorManager manager(5);

    manager.addSensor(new Sensor(
        101, SensorType::TEMPERATURE, "T1", 25, 0, 50, true
    ));

    manager.addSensor(new Sensor(
        102, SensorType::TEMPERATURE, "T2", 30, 0, 50, true
    ));

    manager.addSensor(new Sensor(
        103, SensorType::PRESSURE, "P1", 50, 0, 100, true
    ));

    manager.addSensor(new Sensor(
        104, SensorType::HUMIDITY, "H1", 40, 0, 100, true
    ));

    std::array<int, 4> types = manager.breakdown();

    EXPECT_EQ(types[0], 2);
    EXPECT_EQ(types[1], 1);
    EXPECT_EQ(types[2], 1);
    EXPECT_EQ(types[3], 0);
}

