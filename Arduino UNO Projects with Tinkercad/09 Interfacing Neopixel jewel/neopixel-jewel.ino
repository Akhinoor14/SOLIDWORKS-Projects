/*
 * Project: NeoPixel Jewel (7 LEDs) Control
 * Author: Md Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: Control a 7-pixel NeoPixel jewel with Arduino UNO using Adafruit NeoPixel library
 */

#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 7

Adafruit_NeoPixel ring(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  ring.begin();
  ring.show(); // All off initially
}

void loop() {
  // RED cycle
  for (int i = 0; i < NUMPIXELS; i++) {
    ring.setPixelColor(i, ring.Color(255, 0, 0));
    ring.show();
    delay(150);
    ring.setPixelColor(i, 0);
  }

  // GREEN cycle
  for (int i = 0; i < NUMPIXELS; i++) {
    ring.setPixelColor(i, ring.Color(0, 255, 0));
    ring.show();
    delay(150);
    ring.setPixelColor(i, 0);
  }

  // BLUE cycle
  for (int i = 0; i < NUMPIXELS; i++) {
    ring.setPixelColor(i, ring.Color(0, 0, 255));
    ring.show();
    delay(150);
    ring.setPixelColor(i, 0);
  }
}
