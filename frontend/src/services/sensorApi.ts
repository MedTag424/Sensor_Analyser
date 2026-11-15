
import type { Sensor } from "../types/sensor";

const API_URL = "/api";

interface SensorsResponse {
  sensors: Sensor[];
}

export async function getSensors(): Promise<Sensor[]> {
  const response = await fetch(`${API_URL}/sensors`);

  if (!response.ok) {
    throw new Error(`Failed to fetch sensors: ${response.status}`);
  }

  const data: SensorsResponse = await response.json();

  return data.sensors;
}

