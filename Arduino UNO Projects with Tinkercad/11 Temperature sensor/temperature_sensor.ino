/*
 * Project: Interfacing TMP36 Temperature Sensor
 * Author: Md Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: Measure ambient temperature in Celsius using TMP36 sensor and Arduino UNO
 */

const int tempPin = A0;  // TMP36 output connected to A0
float temperature = 0;
float temperatureF = 0;
float temperatureK = 0;

void setup() {
  Serial.begin(9600); // Start serial communication
}

void loop() {
  int sensorValue = analogRead(tempPin);   // Read raw ADC value (0–1023)
  float voltage = sensorValue * (5.0 / 1023.0);  // Convert to voltage (0–5V)
  temperature = (voltage - 0.5) * 100.0;   // Convert to Celsius
  temperatureF = (temperature * 9.0 / 5.0) + 32.0; // Convert to Fahrenheit
  temperatureK = temperature + 273.15; // Convert to Kelvin

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Temperature: ");
  Serial.print(temperatureF);
  Serial.println(" °F");
  Serial.print("Temperature: ");
  Serial.print(temperatureK);
  Serial.println(" K");

  delay(1000); // Read every 1 second
}