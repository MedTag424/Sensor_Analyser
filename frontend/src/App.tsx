
import { useState } from "react";

import Sidebar from "./components/Sidebar";
import Header from "./components/Header";
import SensorCard from "./components/SensorCard";
import SensorChart from "./components/SensorChart";
import AlertsPanel from "./components/AlertsPanel";
import SensorTable from "./components/SensorTable";

import { mockSensors, mockReadings } from "./data/mockSensors";

import "./App.css";

function App() {
  // Initialize React state with our mock sensor data
  const [sensors, setSensors] = useState(mockSensors);

  // Calculate dashboard statistics
  const activeSensors = sensors.filter(
    (sensor) => sensor.active,
  ).length;

  const criticalSensors = sensors.filter(
    (sensor) => sensor.status === "Critical",
  ).length;

  // Simulate receiving a new temperature reading
  function updateTemperature() {
    setSensors((currentSensors) =>
      currentSensors.map((sensor) =>
        sensor.id === 101
          ? { ...sensor, value: 32.7 }
          : sensor
      )
    );
  }

  return (
    <div className="app-layout">
      <Sidebar />

      <main className="main-content">
        <Header />

        <div className="dashboard-content">
          <section className="welcome-section">
            <div>
              <h2>System overview</h2>
              <p>
                Monitor your industrial sensors and system performance.
              </p>
            </div>

            <div className="live-status">
              <span className="online-dot" />
              Live monitoring
            </div>
          </section>

          <section className="overview-stats">
            <div className="stat-card">
              <span className="stat-label">Total sensors</span>
              <strong>{sensors.length}</strong>
              <small>Registered in system</small>
            </div>

            <div className="stat-card">
              <span className="stat-label">Active sensors</span>
              <strong>{activeSensors}</strong>
              <small>Currently monitoring</small>
            </div>

            <div className="stat-card">
              <span className="stat-label">Critical alerts</span>
              <strong className="critical-number">
                {criticalSensors}
              </strong>
              <small>Require attention</small>
            </div>
          </section>

          <section className="sensor-grid">
            {sensors.slice(0, 4).map((sensor) => (
              <SensorCard
                key={sensor.id}
                sensor={sensor}
              />
            ))}
          </section>

          <section className="main-grid">
            <SensorChart readings={mockReadings} />
            <AlertsPanel sensors={sensors} />
          </section>

          <SensorTable sensors={sensors} />

          {/* Temporary button to simulate a backend update */}
          <button onClick={updateTemperature}>
            Simulate temperature update
          </button>

          <footer className="dashboard-footer">
            SensorFlow Industrial Monitoring
            <span>Frontend demonstration · Mock data</span>
          </footer>
        </div>
      </main>
    </div>
  );
}

export default App;

