import type { Sensor } from "../types/sensor";

type SensorTableProps = {
  sensors: Sensor[];
  onEdit: (sensor: Sensor) => void;
  onDelete: (sensor: Sensor) => void;
  busySensorId: number | null;
};

export default function SensorTable({
  sensors,
  onEdit,
  onDelete,
  busySensorId,
}: SensorTableProps) {
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
              <th>Actions</th>
            </tr>
          </thead>

          <tbody>
            {sensors.map((sensor) => {
              const busy = busySensorId === sensor.id;

              return (
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

                  <td>
                    <div className="table-actions">
                      <button
                        className="table-action edit"
                        type="button"
                        disabled={busy}
                        onClick={() => onEdit(sensor)}
                      >
                        Edit value
                      </button>
                      <button
                        className="table-action delete"
                        type="button"
                        disabled={busy}
                        onClick={() => onDelete(sensor)}
                      >
                        Delete
                      </button>
                    </div>
                  </td>
                </tr>
              );
            })}

            {sensors.length === 0 && (
              <tr>
                <td colSpan={6} className="empty-table">
                  No sensors registered yet.
                </td>
              </tr>
            )}
          </tbody>
        </table>
      </div>
    </section>
  );
}
