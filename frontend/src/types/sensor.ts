export type SensorStatus = "Normal" | "Critical" | "Inactive";

export type SensorType =
  | "Temperature"
  | "Pressure"
  | "Humidity"
  | "Voltage";

export interface Sensor {
  id: number;
  name: string;
  type: SensorType;
  value: number;
  unit: string;
  minValue: number;
  maxValue: number;
  status: SensorStatus;
  active: boolean;
}

export interface SensorReading {
  time: string;
  temperature: number;
  pressure: number;
}
