import type { Sensor } from "../types/sensor";

type SensorTableProps = {
  sensors: Sensor[];
};

export default function SensorTable({ sensors }: SensorTableProps) {
  return (
    <section className="panel table-panel" id="sensors">
      <div className="panel-heading">
        <div>
          <h3>All sensors</h3>
          <p>Current status of connected sensors</p>
        </div>

        <span className="table-count">{sensors.length} sensors</span>
      </div>

      <div className="table-wrapper">
        <table>
          <thead>
            <tr>
              <th>Sensor</th>
              <th>Type</th>
              <th>Current value</th>
              <th>Normal range</th>
              <th>Status</th>
            </tr>
          </thead>

          <tbody>
            {sensors.map((sensor) => (
              <tr key={sensor.id}>
                <td>
                  <div className="table-sensor-name">
                    <strong>{sensor.name}</strong>
                    <small>ID: {sensor.id}</small>
                  </div>
                </td>

                <td>{sensor.type}</td>

                <td className="table-value">
                  {sensor.value} {sensor.unit}
                </td>

                <td>
                  {sensor.minValue}–{sensor.maxValue} {sensor.unit}
                </td>

                <td>
                  <span className={`status-pill ${sensor.status.toLowerCase()}`}>
                    <span />
                    {sensor.status}
                  </span>
                </td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    </section>
  );
}
