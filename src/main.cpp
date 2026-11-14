
#include <iostream>
#include <limits>
#include <string>
#include "MonitoringSystem.h"

int main() {

    MonitoringSystem system(5);

    // Initialize sample sensors
    system.addSensor(new Sensor(101, SensorType::TEMPERATURE,
                                "Boiler Temp", 24.5, 0, 50, true));

    system.addSensor(new Sensor(102, SensorType::PRESSURE,
                                "Main Pressure", 115, 10, 100, true));

    system.addSensor(new Sensor(103, SensorType::HUMIDITY,
                                "Room Humidity", 45, 0, 100, true));

    system.addSensor(new Sensor(104, SensorType::VOLTAGE,
                                "Battery Voltage", 12.2, 10, 14, true));

    system.addSensor(new Sensor(105, SensorType::TEMPERATURE,
                                "Motor Temp", 85, 0, 80, true));

    int choice = 0;

    do {
        std::cout << "\n========== SENSOR MONITORING SYSTEM ==========\n";
        std::cout << "1. Display monitoring report\n";
        std::cout << "2. Add sensor\n";
        std::cout << "3. Remove sensor\n";
        std::cout << "4. Update sensor value\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose an option: ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Enter a number.\n";
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {

            case 1:
                system.displayReport();
                break;

            case 2: {
                int id, type;
                double value, minValue, maxValue;
                std::string name;

                std::cout << "Enter sensor ID: ";
                std::cin >> id;

                std::cout << "Enter sensor name (one word): ";
                std::cin >> name;

                std::cout << "Sensor type:\n";
                std::cout << "0 = Temperature\n";
                std::cout << "1 = Pressure\n";
                std::cout << "2 = Humidity\n";
                std::cout << "3 = Voltage\n";
                std::cout << "Choose type: ";
                std::cin >> type;

                if (type < 0 || type > 3) {
                    std::cout << "Invalid sensor type.\n";
                    break;
                }

                std::cout << "Enter current value: ";
                std::cin >> value;

                std::cout << "Enter minimum value: ";
                std::cin >> minValue;

                std::cout << "Enter maximum value: ";
                std::cin >> maxValue;

                try {
                    system.addSensor(new Sensor(
                        id,
                        static_cast<SensorType>(type),
                        name,
                        value,
                        minValue,
                        maxValue,
                        true
                    ));

                    std::cout << "Sensor added successfully.\n";
                }
                catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << '\n';
                }

                break;
            }

            case 3: {
                int id;

                std::cout << "Enter sensor ID to remove: ";
                std::cin >> id;

                if (system.removeSensor(id))
                    std::cout << "Sensor removed successfully.\n";
                else
                    std::cout << "Sensor not found.\n";

                break;
            }

            case 4: {
                int id;
                double value;

                std::cout << "Enter sensor ID: ";
                std::cin >> id;

                std::cout << "Enter new value: ";
                std::cin >> value;

                if (system.updateSensor(id, value))
                    std::cout << "Sensor updated successfully.\n";
                else
                    std::cout << "Update failed. Check ID and value range.\n";

                break;
            }

            case 5:
                std::cout << "Exiting monitoring system...\n";
                break;

            default:
                std::cout << "Invalid option. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}

