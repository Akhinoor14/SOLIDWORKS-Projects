/*
 * Project 15: Interfacing 16×2 LCD with ATtiny85
 * Author: Md Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: Display message on LCD and show mm:ss time on second line.
 */

#include <LiquidCrystal.h>

// LCD connected in 4-bit mode: RS, EN, D4, D5, D6
const int rs = 0;  // PB0 → Pin 5
const int en = 1;  // PB1 → Pin 6
const int d4 = 2;  // PB2 → Pin 7
const int d5 = 3;  // PB3 → Pin 2
const int d6 = 4;  // PB4 → Pin 3
const int d7 = 5;  // PB5 → Pin 4

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

unsigned long previousMillis = 0;
int seconds = 0;
int minutes = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("this is Akhinoor");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;

    seconds++;
    if (seconds == 60) {
      seconds = 0;
      minutes++;
      if (minutes == 100) minutes = 0;
    }

    lcd.setCursor(0, 1);
    lcd.print("welcome    ");

    lcd.setCursor(11, 1);
    if (minutes < 10) lcd.print('0');
    lcd.print(minutes);
    lcd.print(':');
    if (seconds < 10) lcd.print('0');
    lcd.print(seconds);
  }
}
