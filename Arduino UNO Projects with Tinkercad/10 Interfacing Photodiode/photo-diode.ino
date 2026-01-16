/*
 * Project: Interfacing Photodiode with Arduino
 * Author: Md Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: Measure light intensity using a photodiode as an analog sensor
 */

const int sensorPin = A0;  // Photodiode connected to analog pin A0
int lightValue = 0;

void setup() {
  Serial.begin(9600);      // Start serial communication
}

void loop() {
  lightValue = analogRead(sensorPin);   // Read value from photodiode
  Serial.print("Light Intensity: ");
  Serial.println(lightValue);           // Print the value to Serial Monitor
  delay(500);                           // Wait for 0.5 seconds
}
