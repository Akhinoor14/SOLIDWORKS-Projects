/*
 * Project 18: Piano with Arduino UNO using Push Buttons & Buzzer
 * Author: Md Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: Play 8 musical notes using 8 push buttons and a piezo buzzer
 */

const int buzzerPin = 9; // Piezo buzzer connected to digital pin 9

// Define note frequencies (C4 to C5)
int notes[] = {262, 294, 330, 349, 392, 440, 494, 523};

// Assign push button pins (D2–D8, D10) -- D9 is for buzzer, so skip it
int buttonPins[] = {2, 3, 4, 5, 6, 7, 8, 10};

void setup() {
  // Use INPUT_PULLUP for reliable button reading (connect button to GND)
  for (int i = 0; i < 8; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  for (int i = 0; i < 8; i++) {
    // Button pressed = LOW (because of INPUT_PULLUP)
    if (digitalRead(buttonPins[i]) == LOW) {
      tone(buzzerPin, notes[i]);
      // Wait until button released for better playability
      while (digitalRead(buttonPins[i]) == LOW) {
        delay(10);
      }
      noTone(buzzerPin);
    }
  }
}

