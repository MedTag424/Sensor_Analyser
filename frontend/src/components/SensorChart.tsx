import {
  ResponsiveContainer,
  LineChart,
  Line,
  XAxis,
  YAxis,
  CartesianGrid,
  Tooltip,
} from "recharts";

import type { SensorReading } from "../types/sensor";

type SensorChartProps = {
  readings: SensorReading[];
};

export default function SensorChart({ readings }: SensorChartProps) {
  return (
    <section className="panel chart-panel">
      <div className="panel-heading">
        <div>
          <h3>Sensor history</h3>
          <p>Recent temperature and pressure readings</p>
        </div>

        <span className="chart-period">Last 30 minutes</span>
      </div>

      <div className="chart-legend">
        <span><i className="legend-temperature" /> Temperature (°C)</span>
        <span><i className="legend-pressure" /> Pressure (bar)</span>
      </div>

      <div className="chart-container">
        <ResponsiveContainer width="100%" height="100%">
          <LineChart data={readings}>
            <CartesianGrid stroke="#263244" strokeDasharray="3 3" />
            <XAxis
              dataKey="time"
              stroke="#8290a5"
              tickLine={false}
              axisLine={false}
            />
            <YAxis
              yAxisId="temperature"
              stroke="#8290a5"
              tickLine={false}
              axisLine={false}
            />
            <YAxis
              yAxisId="pressure"
              orientation="right"
              stroke="#8290a5"
              tickLine={false}
              axisLine={false}
            />
            <Tooltip
              contentStyle={{
                background: "#172234",
                border: "1px solid #334155",
                borderRadius: "8px",
                color: "#f1f5f9",
              }}
            />
            <Line
              yAxisId="temperature"
              type="monotone"
              dataKey="temperature"
              stroke="#38bdf8"
              strokeWidth={2}
              dot={false}
              activeDot={{ r: 5 }}
            />
            <Line
              yAxisId="pressure"
              type="monotone"
              dataKey="pressure"
              stroke="#a78bfa"
              strokeWidth={2}
              dot={false}
              activeDot={{ r: 5 }}
            />
          </LineChart>
        </ResponsiveContainer>
      </div>
    </section>
  );
}
