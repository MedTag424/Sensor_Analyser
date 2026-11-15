import type { Sensor, SensorType } from "../types/sensor";

const API_URL = "/api";

interface SensorsResponse {
  sensors: Sensor[];
}

export interface NewSensor {
  id: number;
  name: string;
  type: SensorType;
  value: number;
  minValue: number;
  maxValue: number;
  active: boolean;
}

async function checkResponse(response: Response): Promise<void> {
  if (response.ok) return;

  let message = `Request failed: ${response.status}`;

  try {
    const data = await response.json();
    if (typeof data.error === "string") message = data.error;
  } catch {
    // Keep the status-based message when the response isn't JSON.
  }

  throw new Error(message);
}

export async function getSensors(): Promise<Sensor[]> {
  const response = await fetch(`${API_URL}/sensors`);
  await checkResponse(response);

  const data: SensorsResponse = await response.json();
  return data.sensors;
}

export async function createSensor(sensor: NewSensor): Promise<void> {
  const response = await fetch(`${API_URL}/sensors`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(sensor),
  });

  await checkResponse(response);
}

export async function updateSensorValue(
  id: number,
  value: number,
): Promise<void> {
  const response = await fetch(`${API_URL}/sensors/${id}`, {
    method: "PUT",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ value }),
  });

  await checkResponse(response);
}

export async function deleteSensor(id: number): Promise<void> {
  const response = await fetch(`${API_URL}/sensors/${id}`, {
    method: "DELETE",
  });

  await checkResponse(response);
}
