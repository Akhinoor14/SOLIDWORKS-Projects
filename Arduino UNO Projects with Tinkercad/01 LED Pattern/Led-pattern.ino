/*
 * Project: LED Pattern Project with Potentiometer
 * Author: Md Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: 5 LEDs blink based on analog voltage level from a potentiometer
 */

const int potPin = A0;              // Potentiometer pin
const int leds[] = {2, 3, 4, 5, 6}; // LED pins

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT);
  }
  Serial.begin(9600); // Debugging help
}

void loop() {
  int potValue = analogRead(potPin); // Range: 0–1023
  Serial.println(potValue);          // Optional: see value in Serial Monitor

  // Voltage zone logic
  if (potValue < 200) {
    digitalWrite(leds[0], HIGH);  // Only LED 1 ON
    for (int i = 1; i < 5; i++) digitalWrite(leds[i], LOW);
  } else if (potValue < 400) {
    for (int i = 0; i < 2; i++) digitalWrite(leds[i], HIGH);
    for (int i = 2; i < 5; i++) digitalWrite(leds[i], LOW);
  } else if (potValue < 600) {
    for (int i = 0; i < 3; i++) digitalWrite(leds[i], HIGH);
    for (int i = 3; i < 5; i++) digitalWrite(leds[i], LOW);
  } else if (potValue < 800) {
    for (int i = 0; i < 4; i++) digitalWrite(leds[i], HIGH);
    digitalWrite(leds[4], LOW);
  } else {
    for (int i = 0; i < 5; i++) digitalWrite(leds[i], HIGH);
  }

  delay(300); // Blink delay
}
