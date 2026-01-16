/*
 * Project: NeoPixel Strip Control (4 LEDs)
 * Author: Md Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: Cycle through colors on a 4-pixel NeoPixel strip using Adafruit NeoPixel library
 */

#include <Adafruit_NeoPixel.h>

#define PIN 6           // Data pin
#define NUMPIXELS 4     // Total number of NeoPixels

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();       // Initialize the strip
  strip.show();        // Turn OFF all pixels initially
}

void loop() {
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0)); // RED
    strip.show();
    delay(200);
    strip.setPixelColor(i, strip.Color(0, 0, 0)); // OFF
  }

  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(0, 255, 0)); // GREEN
    strip.show();
    delay(200);
    strip.setPixelColor(i, strip.Color(0, 0, 0)); // OFF
  }

  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 255)); // BLUE
    strip.show();
    delay(200);
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
}
