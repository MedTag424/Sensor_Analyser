#include <gtest/gtest.h>
#include "Sensor.h"

// Test sensor construction
TEST(SensorTest, Constructor) {
    Sensor s(101, SensorType::TEMPERATURE,
             "Boiler Temp", 24.5, 0, 50, true);

    EXPECT_EQ(s.getId(), 101);
    EXPECT_EQ(s.getType(), SensorType::TEMPERATURE);
    EXPECT_DOUBLE_EQ(s.getValue(), 24.5);
    EXPECT_TRUE(s.getActive());
}

// Test valid value update
TEST(SensorTest, ValidValueUpdate) {
    Sensor s(101, SensorType::TEMPERATURE,
             "Boiler Temp", 24.5, 0, 50, true);

    EXPECT_TRUE(s.changeValue(35.0));
    EXPECT_DOUBLE_EQ(s.getValue(), 35.0);
}

// Test invalid value update
TEST(SensorTest, InvalidValueUpdate) {
    Sensor s(101, SensorType::TEMPERATURE,
             "Boiler Temp", 24.5, 0, 50, true);

    EXPECT_FALSE(s.changeValue(100.0));
    EXPECT_DOUBLE_EQ(s.getValue(), 24.5);
}

// Test sensor activation
TEST(SensorTest, Activation) {
    Sensor s(101, SensorType::TEMPERATURE,
             "Boiler Temp", 24.5, 0, 50, true);

    s.Activate(false);

    EXPECT_FALSE(s.getActive());
    EXPECT_EQ(s.getStatus(), "Inactive");
}

// Test invalid constructor range
TEST(SensorTest, InvalidConstructorRange) {
    EXPECT_THROW(
        Sensor(101, SensorType::TEMPERATURE,
               "Boiler Temp", 24.5, 50, 0, true),
        std::invalid_argument
    );
}
