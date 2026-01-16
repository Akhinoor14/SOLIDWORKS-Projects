/*
 * Project: PIR Motion Sensor with LED
 * Author: Md Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: Detect motion with PIR sensor and light up an LED using Arduino
 */

const int pirPin = 2;     // PIR sensor output pin
const int ledPin = 13;    // Onboard LED (or external LED)

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int motionState = digitalRead(pirPin);

  if (motionState == HIGH) {
    digitalWrite(ledPin, HIGH);     // Turn on LED
    Serial.println("Motion Detected!");
  } else {
    digitalWrite(ledPin, LOW);      // Turn off LED
    Serial.println("No Motion");
  }

  delay(500); // Small delay for stability
}
