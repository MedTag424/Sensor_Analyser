
cmake_minimum_required(VERSION 3.20)

project(SensorSystem LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Common compiler warnings
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
)

# Debugging and sanitizer options
add_compile_options(
    -fsanitize=address,undefined
    -fno-omit-frame-pointer
    -g
)

add_link_options(
    -fsanitize=address,undefined
)

# Include directory
include_directories(include)


# ==============================
# MAIN APPLICATION
# ==============================

add_executable(sensor_system
    src/main.cpp
    src/Sensor.cpp
    src/SensorManager.cpp
    src/MonitoringSystem.cpp
)


# ==============================
# TESTING CONFIGURATION
# ==============================

enable_testing()

find_package(GTest REQUIRED)

include(GoogleTest)


# ==============================
# SENSOR TESTS
# ==============================

add_executable(sensor_tests
    tests/SensorTests.cpp
    src/Sensor.cpp
)

target_link_libraries(sensor_tests
    PRIVATE GTest::gtest_main
)

gtest_discover_tests(sensor_tests)


# ==============================
# SENSOR MANAGER TESTS
# ==============================

add_executable(sensor_manager_tests
    tests/SensorManagerTests.cpp
    src/SensorManager.cpp
    src/Sensor.cpp
)

target_link_libraries(sensor_manager_tests
    PRIVATE GTest::gtest_main
)

gtest_discover_tests(sensor_manager_tests)


# ==============================
# MONITORING SYSTEM TESTS
# ==============================

add_executable(monitoring_system_tests
    tests/MonitoringSystemTests.cpp
    src/MonitoringSystem.cpp
    src/SensorManager.cpp
    src/Sensor.cpp
)

target_link_libraries(monitoring_system_tests
    PRIVATE GTest::gtest_main
)

gtest_discover_tests(monitoring_system_tests)

