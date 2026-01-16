/*
 * Project: Ultrasonic Sensor Interfacing
 * Author: Md Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: Measure distance using HC-SR04 sensor and Arduino
 */

const int trigPin = 9;
const int echoPin = 10;
long duration;
float distance;

void setup() {
  Serial.begin(9600);              // Serial Monitor চালু করা
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);      // আগে LOW দিয়ে শুরু
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);     // HIGH pulse 10 μs
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH); // Echo pin এ HIGH pulse কতক্ষন থাকে
  distance = duration * 0.034 / 2;   // সময় → দূরত্বে রূপান্তর

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500); // অর্ধ সেকেন্ড বিরতি
}
