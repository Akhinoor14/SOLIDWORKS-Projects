/*
 * Project: Servo Motor Interfacing
 * Author: Md Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: Control servo motor angle using Arduino
 */

#include <Servo.h> // Servo library

Servo myServo;     // Servo object create

void setup() {
  myServo.attach(9); // Servo signal pin connected to D9
}

void loop() {
  for (int angle = 0; angle <= 180; angle += 1) {
    myServo.write(angle); // Move to angle
    delay(15);            // Small pause for motion
  }

  for (int angle = 180; angle >= 0; angle -= 1) {
    myServo.write(angle);
    delay(15);
  }
}
