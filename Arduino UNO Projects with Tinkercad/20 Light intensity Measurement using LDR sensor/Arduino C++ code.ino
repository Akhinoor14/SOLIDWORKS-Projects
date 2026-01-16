/*
 * Project 20: Light Intensity Measurement with Arduino, LDR & LED
 * Author: Md. Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: Reads light-dependent resistor (LDR) voltage, 
 *              adjusts LED brightness via PWM, and prints voltage to Serial.
 */

const int ldrPin = A0;    // Analog input from LDR + fixed resistor divider
const int ledPin = 9;     // PWM output to LED

void setup() {
  pinMode(ledPin, OUTPUT);      // LED as output
  Serial.begin(9600);           // Initialize serial for voltage readout
}

void loop() {
  int sensorValue = analogRead(ldrPin);                       // 0–1023
  float voltage = sensorValue * (5.0 / 1023.0);               // Convert to volts
  int brightness = map(sensorValue, 0, 1023, 0, 255);         // Map to PWM range

  analogWrite(ledPin, brightness);                            // Set LED brightness
  Serial.print("Light Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");                                       // Print voltage

  delay(500);                                                 // Update twice per second
}

 