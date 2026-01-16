
/*
 * Project 18: Piano with Arduino UNO using Push Buttons & Buzzer
 * Author: Md Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: Play 8 musical notes using 8 push buttons and a piezo buzzer
 */

const int buzzerPin = 9; // Piezo buzzer connected to digital pin 9

// Define note frequencies (C4 to C5)
int notes[] = {262, 294, 330, 349, 392, 440, 494, 523};

// Assign push button pins (D2–D9)
int buttonPins[] = {2, 3, 4, 5, 6, 7, 8, 10};

void setup() {
  // Set all button pins as input with internal pull-down using external resistors
  for (int i = 0; i < 8; i++) {
    pinMode(buttonPins[i], INPUT);
  }
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  for (int i = 0; i < 8; i++) {
    if (digitalRead(buttonPins[i]) == HIGH) {
      tone(buzzerPin, notes[i]);
      delay(800);       // Short delay to avoid continuous tone
      noTone(buzzerPin);
    }
  }
}

