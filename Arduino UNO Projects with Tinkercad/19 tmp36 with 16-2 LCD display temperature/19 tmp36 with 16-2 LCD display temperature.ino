/*
 * Project 19: Display Temperature using TMP36 and 16x2 LCD
 * Author: Md Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: Reads analog voltage from TMP36 and shows °C temperature on LCD
 */

#include <LiquidCrystal.h>

// LCD pin connections: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// TMP36 connected to analog pin
const int tempPin = A0;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temp Sensor Ready");
  delay(3000);
  lcd.clear();
}

void loop() {
  int analogValue = analogRead(tempPin);        // Read voltage from TMP36
  float voltage = analogValue * (5.0 / 1023.0); // Convert to voltage
  float tempC = (voltage - 0.5) * 100.0;        // TMP36 formula for °C

  lcd.setCursor(0, 0);
  lcd.print("Now Temp:");
  lcd.setCursor(0, 1);
  lcd.print(tempC);
  lcd.print(" C");

  delay(1000); // Update every second
}
