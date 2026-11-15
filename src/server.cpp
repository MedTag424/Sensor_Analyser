
#include "crow.h"

#include "MonitoringSystem.h"
#include "Sensor.h"

#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include <stdexcept>

// --------------------------------------------------
// GLOBAL APPLICATION DATA
// --------------------------------------------------

MonitoringSystem monitoringSystem(10);

// Protect shared sensor data when multiple HTTP
// requests arrive at approximately the same time.
std::mutex systemMutex;


// --------------------------------------------------
// HELPER FUNCTIONS
// --------------------------------------------------
// Convert SensorType into the corresponding enum value.
SensorType parseSensorType(const std::string& type)
{
    if (type == "Temperature") return SensorType::TEMPERATURE;
    if (type == "Pressure")    return SensorType::PRESSURE;
    if (type == "Humidity")    return SensorType::HUMIDITY;
    if (type == "Voltage")     return SensorType::VOLTAGE;

    throw std::invalid_argument("Invalid sensor type");
}


// Assign a unit to each sensor type.
// Units are currently defined by the API, not Sensor.
std::string getUnit(SensorType type)
{
    switch (type)
    {
        case SensorType::TEMPERATURE: return "°C";
        case SensorType::PRESSURE:    return "bar";
        case SensorType::HUMIDITY:    return "%";
        case SensorType::VOLTAGE:     return "V";
    }

    return "";
}


// Convert a C++ Sensor object into JSON.
crow::json::wvalue sensorToJson(const Sensor& sensor)
{
    crow::json::wvalue json;

    json["id"]       = sensor.getId();
    json["name"]     = sensor.getName();
    json["type"]     = sensor.getTypeName();
    json["value"]    = sensor.getValue();
    json["unit"]     = getUnit(sensor.getType());
    json["minValue"] = sensor.getMinValue();
    json["maxValue"] = sensor.getMaxValue();
    json["active"]   = sensor.getActive();

    // Your existing Sensor.cpp has a small typo:
    // it returns "Normnal" instead of "Normal".
    std::string status = sensor.getStatus();

    if (status == "Normnal")
        status = "Normal";

    json["status"] = status;

    return json;
}


// Return a JSON error response.
crow::response errorResponse(int status, const std::string& message)
{
    crow::json::wvalue json;
    json["error"] = message;

    return crow::response(status, json);
}


// --------------------------------------------------
// MAIN
// --------------------------------------------------

int main()
{
    // Initialize the existing sample sensors.
    monitoringSystem.addSensor(
        new Sensor(101, SensorType::TEMPERATURE,
                   "Boiler Temp", 24.5, 0, 50, true)
    );

    monitoringSystem.addSensor(
        new Sensor(102, SensorType::PRESSURE,
                   "Main Pressure", 115, 10, 100, true)
    );

    monitoringSystem.addSensor(
        new Sensor(103, SensorType::HUMIDITY,
                   "Room Humidity", 45, 0, 100, true)
    );

    monitoringSystem.addSensor(
        new Sensor(104, SensorType::VOLTAGE,
                   "Battery Voltage", 12.2, 10, 14, true)
    );

    monitoringSystem.addSensor(
        new Sensor(105, SensorType::TEMPERATURE,
                   "Motor Temp", 85, 0, 80, true)
    );


    // Create the Crow web application.
    crow::SimpleApp app;


    // --------------------------------------------------
    // ROUTE 1: HOME
    // GET /
    // --------------------------------------------------

    CROW_ROUTE(app, "/")
    ([]()
    {
        return "Sensor Analyser API is running";
    });


    // --------------------------------------------------
    // ROUTE 2: GET ALL SENSORS
    // GET /api/sensors
    // --------------------------------------------------

    CROW_ROUTE(app, "/api/sensors")
    ([]
    {
        std::lock_guard<std::mutex> lock(systemMutex);

        std::vector<crow::json::wvalue> sensors;

        for (int i = 0; i < monitoringSystem.getSensorCount(); i++)
        {
            const Sensor* sensor = monitoringSystem.getSensor(i);

            if (sensor != nullptr)
                sensors.push_back(sensorToJson(*sensor));
        }

        crow::json::wvalue response;
        response["sensors"] = std::move(sensors);

        return response;
    });


    // --------------------------------------------------
    // ROUTE 3: GET ONE SENSOR
    // GET /api/sensors/101
    // --------------------------------------------------

    CROW_ROUTE(app, "/api/sensors/<int>")
    ([](int id)
    {
        std::lock_guard<std::mutex> lock(systemMutex);

        const Sensor* sensor = monitoringSystem.findSensor(id);

        if (sensor == nullptr)
            return errorResponse(404, "Sensor not found");

        return crow::response(sensorToJson(*sensor));
    });


    // --------------------------------------------------
    // ROUTE 4: CREATE A SENSOR
    // POST /api/sensors
    // --------------------------------------------------

    CROW_ROUTE(app, "/api/sensors")
    .methods(crow::HTTPMethod::POST)
    ([](const crow::request& request)
    {
        auto body = crow::json::load(request.body);

        if (!body)
            return errorResponse(400, "Invalid JSON");

        try
        {
            // Read information sent by the frontend.
            int id = body["id"].i();
            std::string name = body["name"].s();
            std::string typeName = body["type"].s();

            double value = body["value"].d();
            double minValue = body["minValue"].d();
            double maxValue = body["maxValue"].d();

            bool active = body["active"].b();

            SensorType type = parseSensorType(typeName);

            std::lock_guard<std::mutex> lock(systemMutex);

            // Prevent duplicate sensor IDs.
            if (monitoringSystem.findSensor(id) != nullptr)
                return errorResponse(409, "Sensor ID already exists");

            // Create the sensor and transfer ownership
            // to MonitoringSystem.
            auto sensor = std::make_unique<Sensor>(
                id, type, name, value, minValue, maxValue, active
            );

            monitoringSystem.addSensor(sensor.get());
            sensor.release();

            crow::json::wvalue response;
            response["message"] = "Sensor created";
            response["id"] = id;

            return crow::response(201, response);
        }
        catch (const std::exception& e)
        {
            return errorResponse(400, e.what());
        }
    });


    // --------------------------------------------------
    // ROUTE 5: UPDATE SENSOR VALUE
    // PUT /api/sensors/101
    // --------------------------------------------------

    CROW_ROUTE(app, "/api/sensors/<int>")
    .methods(crow::HTTPMethod::PUT)
    ([](const crow::request& request, int id)
    {
        auto body = crow::json::load(request.body);

        if (!body)
            return errorResponse(400, "Invalid JSON");

        try
        {
            double newValue = body["value"].d();

            std::lock_guard<std::mutex> lock(systemMutex);

            if (monitoringSystem.findSensor(id) == nullptr)
                return errorResponse(404, "Sensor not found");

            // Your existing changeValue() only accepts
            // values inside the sensor's configured range.
            if (!monitoringSystem.updateSensor(id, newValue))
                return errorResponse(422, "Value outside allowed range");

            crow::json::wvalue response;
            response["message"] = "Sensor updated";
            response["id"] = id;
            response["value"] = newValue;

            return crow::response(response);
        }
        catch (const std::exception& e)
        {
            return errorResponse(400, e.what());
        }
    });


    // --------------------------------------------------
    // ROUTE 6: DELETE SENSOR
    // DELETE /api/sensors/101
    // --------------------------------------------------

    CROW_ROUTE(app, "/api/sensors/<int>")
    .methods(crow::HTTPMethod::DELETE)
    ([](int id)
    {
        std::lock_guard<std::mutex> lock(systemMutex);

        if (!monitoringSystem.removeSensor(id))
            return errorResponse(404, "Sensor not found");

        crow::json::wvalue response;
        response["message"] = "Sensor deleted";
        response["id"] = id;

        return crow::response(response);
    });


    // --------------------------------------------------
    // ROUTE 7: GET STATISTICS
    // GET /api/statistics
    // --------------------------------------------------

    CROW_ROUTE(app, "/api/statistics")
    ([]
    {
        std::lock_guard<std::mutex> lock(systemMutex);

        crow::json::wvalue response;

        response["totalSensors"] = monitoringSystem.getSensorCount();
        response["activeSensors"] = monitoringSystem.getActiveCount();
        response["criticalSensors"] = monitoringSystem.getCriticalCount();
        response["inactiveSensors"] = monitoringSystem.getInactiveCount();
        response["averageTemperature"] = monitoringSystem.getAverageTemp();

        auto types = monitoringSystem.getBreakdown();

        crow::json::wvalue breakdown;

        breakdown["temperature"] = types[0];
        breakdown["pressure"] = types[1];
        breakdown["humidity"] = types[2];
        breakdown["voltage"] = types[3];

        response["breakdown"] = std::move(breakdown);

        return response;
    });


    // --------------------------------------------------
    // START SERVER
    // --------------------------------------------------

    app.port(18080)
       .bindaddr("127.0.0.1")
       .multithreaded()
       .run();

    return 0;
}

