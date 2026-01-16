/*
 * Project 16: Dice with 7-Segment Display using ATtiny85 + 74HC595
 * Author: Md Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: Show random dice roll (1–6) on a 7-segment display
 *              using shift register and push button.
 */

// Use one 74HC595 to control a CC 7-segment display
// Note: Operating voltage 3V–6V
// Confirm: segDISPLAY = CATHODE (for Common Cathode)

#define segDISPLAY CATHODE
#define d250 delay(100);

const int buttonPin = 0;
const int ledPin = 1;
const int clockPin = 2;  // SH_CP: Pin 11 of 74HC595
const int latchPin = 3;  // ST_CP: Pin 12 of 74HC595
const int dataPin  = 4;  // DS:    Pin 14 of 74HC595

// Digit pattern for 7-segment display (gfedcba)
// Index 0–6 for dice faces, 7 = OFF, 8 = All segments ON
const byte digit[] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000000, // OFF (index 7)
  B01111111  // All ON (index 8 - for animation)
};

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  #ifdef segDISPLAY
    digitalWrite(ledPin, LOW);   // Common Cathode
  #else
    digitalWrite(ledPin, HIGH);
  #endif

  LEDwrite(8); delay(3000);  // All ON animation
  LEDwrite(7); d250;         // OFF
  LEDwrite(0);               // Show 0 to start
}

void loop() {
  int btn = digitalRead(buttonPin);
  if (btn == HIGH) {
    LEDwrite(7); d250;

    int rolled = RND();      // Generate a number 1–6
    rollDice(2);             // Spin animation
    LEDwrite(7); d250;

    LEDwrite(rolled);        // Show result
  }
}

void LEDwrite(int index) {
  digitalWrite(latchPin, LOW);

  #ifdef segDISPLAY
    shiftOut(dataPin, clockPin, MSBFIRST, digit[index]);   // For CC: direct pattern
  #else
    shiftOut(dataPin, clockPin, MSBFIRST, ~digit[index]);  // For CA: inverted pattern
  #endif

  digitalWrite(latchPin, HIGH);
}

int RND() {
  int seed = analogRead(A1);    // Use floating analog pin for randomness
  randomSeed(seed);
  return random(1, 7);          // Return 1 to 6
}

void rollDice(int times) {
  for (int i = 0; i < times; i++) {
    for (int j = 1; j <= 6; j++) {
      LEDwrite(j); d250;
    }
    for (int j = 5; j >= 2; j--) {
      LEDwrite(j); d250;
    }
  }
  LEDwrite(1); d250;
}
