/*
 * Project: RGB LED Control with PWM
 * Author: Md Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: Smoothly change colors of RGB LED using PWM
 */

const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Red to Green
  for (int i = 0; i <= 255; i++) {
    analogWrite(redPin, 255 - i);   // Red fades out
    analogWrite(greenPin, i);       // Green fades in
    delay(10);
  }

  // Green to Blue
  for (int i = 0; i <= 255; i++) {
    analogWrite(greenPin, 255 - i); // Green fades out
    analogWrite(bluePin, i);        // Blue fades in
    delay(10);
  }

  // Blue to Red
  for (int i = 0; i <= 255; i++) {
    analogWrite(bluePin, 255 - i);  // Blue fades out
    analogWrite(redPin, i);         // Red fades in
    delay(10);
  }
}
