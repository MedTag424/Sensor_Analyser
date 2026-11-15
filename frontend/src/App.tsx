import { useCallback, useEffect, useState, type FormEvent } from "react";

import Sidebar from "./components/Sidebar";
import Header from "./components/Header";
import SensorCard from "./components/SensorCard";
import SensorChart from "./components/SensorChart";
import AlertsPanel from "./components/AlertsPanel";
import SensorTable from "./components/SensorTable";

import { mockReadings } from "./data/mockSensors";
import {
  createSensor,
  deleteSensor,
  getSensors,
  updateSensorValue,
  type NewSensor,
} from "./services/sensorApi";

import type { Sensor, SensorType } from "./types/sensor";

import "./App.css";

const SENSOR_TYPES: SensorType[] = [
  "Temperature",
  "Pressure",
  "Humidity",
  "Voltage",
];

const EMPTY_FORM = {
  id: "",
  name: "",
  type: "Temperature" as SensorType,
  value: "",
  minValue: "0",
  maxValue: "100",
};

function App() {
  const [sensors, setSensors] = useState<Sensor[]>([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);
  const [notice, setNotice] = useState<string | null>(null);
  const [showCreateForm, setShowCreateForm] = useState(false);
  const [form, setForm] = useState(EMPTY_FORM);
  const [saving, setSaving] = useState(false);
  const [busySensorId, setBusySensorId] = useState<number | null>(null);
  const [lastUpdated, setLastUpdated] = useState<Date | null>(null);

  // Fetch the latest sensor list from the C++ API.
  const loadSensors = useCallback(async (showLoading = false) => {
    if (showLoading) setLoading(true);

    try {
      const data = await getSensors();
      setSensors(data);
      setError(null);
      setLastUpdated(new Date());
    } catch (err) {
      setError(
        err instanceof Error ? err.message : "Could not load sensors",
      );
    } finally {
      setLoading(false);
    }
  }, []);

  // Initial fetch, then refresh automatically every five seconds.
  useEffect(() => {
    void loadSensors(true);

    const intervalId = window.setInterval(() => {
      void loadSensors();
    }, 5000);

    return () => window.clearInterval(intervalId);
  }, [loadSensors]);

  const activeSensors = sensors.filter((sensor) => sensor.active).length;
  const criticalSensors = sensors.filter(
    (sensor) => sensor.status === "Critical",
  ).length;

  function updateForm<K extends keyof typeof EMPTY_FORM>(
    field: K,
    value: (typeof EMPTY_FORM)[K],
  ) {
    setForm((current) => ({ ...current, [field]: value }));
  }

  async function handleCreateSensor(event: FormEvent<HTMLFormElement>) {
    event.preventDefault();
    setNotice(null);
    setError(null);

    const newSensor: NewSensor = {
      id: Number(form.id),
      name: form.name.trim(),
      type: form.type,
      value: Number(form.value),
      minValue: Number(form.minValue),
      maxValue: Number(form.maxValue),
      active: true,
    };

    if (
      !Number.isFinite(newSensor.id) ||
      !Number.isFinite(newSensor.value) ||
      !Number.isFinite(newSensor.minValue) ||
      !Number.isFinite(newSensor.maxValue) ||
      newSensor.minValue > newSensor.maxValue
    ) {
      setError("Please enter valid numbers and a minimum not greater than the maximum.");
      return;
    }

    setSaving(true);

    try {
      await createSensor(newSensor);
      await loadSensors();
      setForm(EMPTY_FORM);
      setShowCreateForm(false);
      setNotice("Sensor created successfully.");
    } catch (err) {
      setError(err instanceof Error ? err.message : "Could not create sensor.");
    } finally {
      setSaving(false);
    }
  }

  async function handleEditSensor(sensor: Sensor) {
    const enteredValue = window.prompt(
      `Enter a new value for ${sensor.name} (${sensor.minValue}–${sensor.maxValue} ${sensor.unit}):`,
      String(sensor.value),
    );

    if (enteredValue === null) return;

    const newValue = Number(enteredValue);

    if (enteredValue.trim() === "" || !Number.isFinite(newValue)) {
      setError("Please enter a valid numeric value.");
      return;
    }

    setBusySensorId(sensor.id);
    setError(null);
    setNotice(null);

    try {
      await updateSensorValue(sensor.id, newValue);
      await loadSensors();
      setNotice(`${sensor.name} updated successfully.`);
    } catch (err) {
      setError(err instanceof Error ? err.message : "Could not update sensor.");
    } finally {
      setBusySensorId(null);
    }
  }

  async function handleDeleteSensor(sensor: Sensor) {
    const confirmed = window.confirm(
      `Delete "${sensor.name}" (ID: ${sensor.id})? This cannot be undone.`,
    );

    if (!confirmed) return;

    setBusySensorId(sensor.id);
    setError(null);
    setNotice(null);

    try {
      await deleteSensor(sensor.id);
      await loadSensors();
      setNotice(`${sensor.name} deleted successfully.`);
    } catch (err) {
      setError(err instanceof Error ? err.message : "Could not delete sensor.");
    } finally {
      setBusySensorId(null);
    }
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
              <p>Monitor your industrial sensors and system performance.</p>
              <p className="refresh-meta">
                {lastUpdated
                  ? `Last updated at ${lastUpdated.toLocaleTimeString()}`
                  : "Waiting for backend data"}
                {" · "}Automatic refresh every 5 seconds
              </p>
            </div>

            <div className="welcome-actions">
              <div className={`live-status ${error ? "offline" : ""}`}>
                <span className="online-dot" />
                {error ? "Connection issue" : "Backend connected"}
              </div>
              <button
                className="primary-button"
                type="button"
                onClick={() => {
                  setShowCreateForm((current) => !current);
                  setNotice(null);
                }}
              >
                {showCreateForm ? "Close form" : "+ Add sensor"}
              </button>
            </div>
          </section>

          {loading && <p className="feedback-message">Loading sensors...</p>}
          {error && <p className="feedback-message error" role="alert">{error}</p>}
          {notice && <p className="feedback-message success" role="status">{notice}</p>}

          {showCreateForm && (
            <section className="panel create-panel">
              <div className="panel-heading">
                <div>
                  <h3>Add a new sensor</h3>
                  <p>Register a sensor in the C++ monitoring system</p>
                </div>
              </div>

              <form className="sensor-form" onSubmit={handleCreateSensor}>
                <label>
                  Sensor ID
                  <input
                    type="number"
                    value={form.id}
                    onChange={(event) => updateForm("id", event.target.value)}
                    required
                  />
                </label>

                <label>
                  Sensor name
                  <input
                    type="text"
                    value={form.name}
                    onChange={(event) => updateForm("name", event.target.value)}
                    required
                  />
                </label>

                <label>
                  Sensor type
                  <select
                    value={form.type}
                    onChange={(event) => updateForm("type", event.target.value as SensorType)}
                  >
                    {SENSOR_TYPES.map((type) => (
                      <option key={type} value={type}>{type}</option>
                    ))}
                  </select>
                </label>

                <label>
                  Initial value
                  <input
                    type="number"
                    step="any"
                    value={form.value}
                    onChange={(event) => updateForm("value", event.target.value)}
                    required
                  />
                </label>

                <label>
                  Minimum value
                  <input
                    type="number"
                    step="any"
                    value={form.minValue}
                    onChange={(event) => updateForm("minValue", event.target.value)}
                    required
                  />
                </label>

                <label>
                  Maximum value
                  <input
                    type="number"
                    step="any"
                    value={form.maxValue}
                    onChange={(event) => updateForm("maxValue", event.target.value)}
                    required
                  />
                </label>

                <div className="form-actions">
                  <button
                    className="secondary-button"
                    type="button"
                    onClick={() => {
                      setShowCreateForm(false);
                      setForm(EMPTY_FORM);
                    }}
                  >
                    Cancel
                  </button>
                  <button className="primary-button" type="submit" disabled={saving}>
                    {saving ? "Creating..." : "Create sensor"}
                  </button>
                </div>
              </form>
            </section>
          )}

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
              <strong className="critical-number">{criticalSensors}</strong>
              <small>Require attention</small>
            </div>
          </section>

          <section className="sensor-grid">
            {sensors.slice(0, 4).map((sensor) => (
              <SensorCard key={sensor.id} sensor={sensor} />
            ))}
          </section>

          <section className="main-grid">
            <SensorChart readings={mockReadings} />
            <AlertsPanel sensors={sensors} />
          </section>

          <SensorTable
            sensors={sensors}
            onEdit={handleEditSensor}
            onDelete={handleDeleteSensor}
            busySensorId={busySensorId}
          />

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
