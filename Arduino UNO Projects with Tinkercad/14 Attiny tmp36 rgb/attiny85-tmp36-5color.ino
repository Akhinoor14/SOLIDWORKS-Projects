/*
 * Project 14: TMP36 + ATtiny85 + RGB LED + DIP Power Switch
 * Author: Md Akhinoor Islam
 * Description: Show 5 distinct color zones from -40°C to +125°C using TMP36 and RGB LED
 */

const int redPin   = 0;  // PB0 → Pin 5
const int greenPin = 1;  // PB1 → Pin 6
const int bluePin  = 4;  // PB4 → Pin 3
const int tempPin  = A1; // PB2 → Pin 7 (TMP36 analog input)

float temperature;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  int raw = analogRead(tempPin);
  float voltage = raw * (3.0 / 1023.0);           // TMP36 powered by 3V coin cell
  temperature = (voltage - 0.5) * 100.0;          // TMP36 voltage → °C

  // Map temperature ranges to 5 distinct color zones
  if (temperature <= -20) {
    setColor(0, 0, 255);   // Deep Cold → Blue
  }
  else if (temperature > -20 && temperature <= 10) {
    setColor(0, 255, 255); // Cool → Cyan
  }
  else if (temperature > 10 && temperature <= 35) {
    setColor(0, 255, 0);   // Normal → Green
  }
  else if (temperature > 35 && temperature <= 60) {
    setColor(255, 165, 0); // Warm → Orange
  }
  else {
    setColor(255, 0, 0);   // Hot → Red
  }

  delay(1000); // Update every 1s
}

void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}
