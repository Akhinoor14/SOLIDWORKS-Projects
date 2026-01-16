/*
 * Project 16: Dice with 7-Segment Display using ATtiny85 + 74HC595
 * Author: Md Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: Show random dice roll (1–6) on 7-segment using shift register and push button
 */

// Use one 74HC595 to control a CC/CA seven-segment display
// Note: operating voltage 3V–6V
// Remove remarks if you're using CC (Common Cathode) 7-seg. display

#define segDISPLAY CATHODE
#define d250 delay(250);

const int buttonPin = 0;
const int ledPin = 1;
const int clockPin = 2;  // SHCP: Pin 11 of 74HC595
const int latchPin = 3;  // STCP: Pin 12 of 74HC595
const int dataPin  = 4;  // DS:   Pin 14 of 74HC595

// Digit pattern for 7-segment display (gfedcba)
const byte digit[] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000000, // OFF
  B01111111  // 8 (for transition animation)
};

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  #ifdef segDISPLAY
    digitalWrite(ledPin, LOW);   // OFF for CA
  #else
    digitalWrite(ledPin, HIGH);  // ON for CC
  #endif

  LEDwrite(8);
  delay(3000);
  LEDwrite(7); d250;
  LEDwrite(0);
}

void LEDwrite(int data) {
    
  digitalWrite(latchPin, LOW);
  
  #ifdef segDISPLAY
    shiftOut(dataPin, clockPin, MSBFIRST, digit[data]);
  #else
    shiftOut(dataPin, clockPin, MSBFIRST, ~digit[data]);
  #endif

  digitalWrite(latchPin, HIGH);
}

int RND() {
  int seed = 0;  // Random seed
  int digit = 0;
  while( digit > 6 || digit <= 0) {
    seed = (seed * 53)+ 21;  // Read from A1 for randomness
    digit = seed % 6;
    randomSeed (analogRead (PB5));
    seed = random (50) + digit ;
    digit += seed;    // Generate a random number between 1 and 6
  }
  return digit;        // Return 1–6
}

void rollDice(int times) {
  for (int i = 0; i < times; i++) 
    LEDwrite(0); d250;
    LEDwrite(1); d250;
    LEDwrite(2); d250;
    LEDwrite(3); d250;
    LEDwrite(4); d250;
    LEDwrite(5); d250;
    LEDwrite(6); d250;


}

void loop() {
  int btn = 0;
  btn = digitalRead(buttonPin);
  if (btn == HIGH) {
    LEDwrite(7); d250;
    int digit = RND();
    rollDice(2);
    LEDwrite(7); d250;
    if (digit ==0) LEDwrite(0);
    else if (digit ==1) LEDwrite(1);
    else if (digit ==2) LEDwrite(2);
    else if (digit ==3) LEDwrite(3);
    else if (digit ==4) LEDwrite(4);
    else if (digit ==5) LEDwrite(5);
    else if (digit ==6) LEDwrite(6);
      }
}
// End of code
// This code is designed to run on an ATtiny85 microcontroller with a 74HC595 shift register to control a 7-segment display. It generates a random number between 1 and 6 when a button is pressed, simulating a dice roll. The display shows the rolled number with a brief animation before displaying the final result. The code includes functionality for both common cathode and common anode displays, depending on the defined `segDISPLAY` macro.
// The `RND` function generates a random number, and the `rollDice` function creates a rolling animation by sequentially lighting up the segments of the display. The `LEDwrite` function handles the output to the 7-segment display using the shift register, allowing for efficient control of the display with minimal pins used on the microcontroller.
// The setup initializes the pins and displays an initial animation before entering the main loop, where it waits for a button press to trigger the dice roll. The code is structured to be easily adaptable for different display types and configurations, making it versatile for various projects involving 7-segment displays and random number generation.
// The project is suitable for educational purposes, demonstrating basic microcontroller programming, interfacing with external components like shift registers and displays, and implementing random number generation in embedded systems. It can be used as a foundation for more complex projects involving user input and visual output, such as games or interactive displays.