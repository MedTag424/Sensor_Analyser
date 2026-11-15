import { AlertTriangle, CheckCircle2 } from "lucide-react";
import type { Sensor } from "../types/sensor";

type AlertsPanelProps = {
  sensors: Sensor[];
};

export default function AlertsPanel({ sensors }: AlertsPanelProps) {
  const criticalSensors = sensors.filter(
    (sensor) => sensor.status === "Critical",
  );

  return (
    <section className="panel alerts-panel">
      <div className="panel-heading">
        <div>
          <h3>System alerts</h3>
          <p>Events requiring attention</p>
        </div>

        <span className="alert-count">{criticalSensors.length}</span>
      </div>

      {criticalSensors.length === 0 ? (
        <div className="no-alerts">
          <CheckCircle2 size={22} />
          <span>No active alerts</span>
        </div>
      ) : (
        <div className="alert-list">
          {criticalSensors.map((sensor) => (
            <div className="alert-item" key={sensor.id}>
              <div className="alert-icon">
                <AlertTriangle size={17} />
              </div>

              <div className="alert-content">
                <strong>{sensor.name}</strong>
                <p>
                  Value {sensor.value} {sensor.unit} is outside the normal
                  range ({sensor.minValue}–{sensor.maxValue} {sensor.unit})
                </p>
                <small>Sensor ID: {sensor.id}</small>
              </div>
            </div>
          ))}
        </div>
      )}
    </section>
  );
}
