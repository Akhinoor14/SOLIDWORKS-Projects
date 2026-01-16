/*
 * Project: Breathing LED
 * Author: Md Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: A single LED gradually brightens and dims using PWM
 */

const int ledPin = 9; // PWM pin

void setup() {
  pinMode(ledPin, OUTPUT); // D9 পিনকে output বানানো হলো
}

void loop() {
  // Brighten LED
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(ledPin, brightness); // LED brightness বাড়ানো
    delay(10); // সামান্য বিরতি
  }

  // Dim LED
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(ledPin, brightness); // LED brightness কমানো
    delay(10); // সামান্য বিরতি
  }
}
