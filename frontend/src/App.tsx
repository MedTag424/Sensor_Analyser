
import { useEffect, useState } from "react";

import Sidebar from "./components/Sidebar";
import Header from "./components/Header";
import SensorCard from "./components/SensorCard";
import SensorChart from "./components/SensorChart";
import AlertsPanel from "./components/AlertsPanel";
import SensorTable from "./components/SensorTable";

import { mockReadings } from "./data/mockSensors";
import { getSensors } from "./services/sensorApi";

import type { Sensor } from "./types/sensor";

import "./App.css";

function App() {
  // Sensors received from the C++ backend
  const [sensors, setSensors] = useState<Sensor[]>([]);

  // API request states
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);

  // Fetch sensors when the dashboard first loads
  useEffect(() => {
    async function loadSensors() {
      try {
        const data = await getSensors();
        setSensors(data);
        setError(null);
      } catch (err) {
        setError(
          err instanceof Error
            ? err.message
            : "Could not load sensors"
        );
      } finally {
        setLoading(false);
      }
    }

    loadSensors();
  }, []);

  // Calculate dashboard statistics
  const activeSensors = sensors.filter(
    (sensor) => sensor.active
  ).length;

  const criticalSensors = sensors.filter(
    (sensor) => sensor.status === "Critical"
  ).length;

  return (
    <div className="app-layout">
      <Sidebar />

      <main className="main-content">
        <Header />

        <div className="dashboard-content">

          {/* API connection status */}
          {loading && (
            <p>Loading sensors from backend...</p>
          )}

          {error && (
            <p role="alert">
              Backend connection error: {error}
            </p>
          )}

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

          <footer className="dashboard-footer">
            SensorFlow Industrial Monitoring
            <span>Connected to C++ backend</span>
          </footer>

        </div>
      </main>
    </div>
  );
}

export default App;

