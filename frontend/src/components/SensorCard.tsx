import {
  Thermometer,
  Gauge,
  Droplets,
  Zap,
  type LucideIcon,
} from "lucide-react";

import type { Sensor, SensorType } from "../types/sensor";

type SensorCardProps = {
  sensor: Sensor;
};

const sensorIcons: Record<SensorType, LucideIcon> = {
  Temperature: Thermometer,
  Pressure: Gauge,
  Humidity: Droplets,
  Voltage: Zap,
};

export default function SensorCard({ sensor }: SensorCardProps) {
  const Icon = sensorIcons[sensor.type];

  return (
    <article className="sensor-card">
      <div className="sensor-card-top">
        <div className={`sensor-icon ${sensor.type.toLowerCase()}`}>
          <Icon size={20} />
        </div>

        <span className={`status-pill ${sensor.status.toLowerCase()}`}>
          <span />
          {sensor.status}
        </span>
      </div>

      <p className="sensor-type">{sensor.type}</p>
      <h2 className="sensor-value">
        {sensor.value}
        <span>{sensor.unit}</span>
      </h2>

      <div className="sensor-card-bottom">
        <span>{sensor.name}</span>
        <span>ID: {sensor.id}</span>
      </div>
    </article>
  );
}
