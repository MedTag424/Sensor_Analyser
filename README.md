
# Industrial Sensor Monitoring System

A C++20 application for managing and monitoring industrial sensors.

## Features

- Sensor creation and management
- Dynamic memory allocation and resizing
- Sensor activation and deactivation
- Measurement validation
- Critical sensor detection
- Temperature statistics
- Interactive terminal interface

## Project Structure

```text
sensor-analyser/
├── include/
├── src/
├── build/
├── CMakeLists.txt
└── README.md
```

## Technologies

- C++20
- CMake
- GCC

## Build Instructions

Configure the project:

```bash
cmake -S . -B build
```

Build:

```bash
cmake --build build
```

Run:

```bash
./build/sensor_system
```

## Future Improvements

- Unit testing with GoogleTest
- Improved memory safety
- REST API
- Interactive graphical dashboard

