/*
 * Project 22: Digital Potentiometer with Arduino & LCD
 * Author: Md. Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: Reads analog voltage from a voltage divider using 1MΩ and 10kΩ resistors,
 *              displays the voltage on a 16x2 LCD in real-time.
 */

#include <LiquidCrystal.h>

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
float input_voltage = 0.0; // Variable to store calculated input voltage
float r1 = 1000000.0; // 1MΩ resistor   
float r2 = 10000.0;   // 10kΩ resistor

const int analogPin = A0;  // Voltage divider output connected here

void setup() {
  lcd.begin(16, 2);                // Initialize 16x2 LCD
  lcd.setCursor(0, 0);
  lcd.print("Digital Voltage");    // Title on first line
  Serial.begin(9600);              // Fix: Use Serial (not serial)
}

void loop() {
  int sensorValue = analogRead(analogPin);           // Read analog value (0–1023)
  float vout = (sensorValue * 5.0) / 1023.0;         // Voltage at divider output (A0)
  input_voltage = vout * ((r1 + r2) / r2);           // Calculate input voltage from divider

  Serial.print("v= ");
  Serial.println(input_voltage);                     // Print input voltage to serial monitor

  lcd.setCursor(0, 1);                               // Second line
  lcd.print("V: ");
  lcd.print(input_voltage, 2);                       // Show voltage with 2 decimal places
  lcd.print(" V   ");                                // Clear trailing chars

  delay(500);                                        // Update every 0.5 seconds
}
