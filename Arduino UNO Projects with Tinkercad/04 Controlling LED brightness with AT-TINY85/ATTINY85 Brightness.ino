/*
 * Project: LED Brightness Control with ATtiny85
 * Author: Md Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: Control LED brightness using potentiometer and ATtiny85
 */

const int potPin = A3; // Potentiometer analog pin
const int ledPin = 0;  // LED connected to PB0 (Pin 5)

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int potValue = analogRead(potPin);            // Range: 0–1023
  int brightness = map(potValue, 0, 1023, 0, 255); // Map to PWM range
  analogWrite(ledPin, brightness);              // Adjust LED brightness
  delay(10); // Smooth update
}
