/*
 * Project 23 (Alternative): Digital Voltmeter with ATtiny85 (Polling-Based)
 * Author: Md. Akhinoor Islam
 * Description: Reads analog voltage using ATtiny85 ADC,
 *              converts it to voltage, and displays it using
 *              3 multiplexed 7-segment displays via 74HC595 shift register.
 */

#define DATA_PIN 0   // PB0 → DS
#define CLOCK_PIN 1  // PB1 → SH_CP
#define LATCH_PIN 2  // PB2 → ST_CP
#define DIGIT1_PIN 3 // PB3 → Digit 1 enable
#define DIGIT2_PIN 4 // PB4 → Digit 2 enable

const byte digitMap[11] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111, // 9
  0b01000000  // 10 = Error (dash)
};

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(DIGIT1_PIN, OUTPUT);
  pinMode(DIGIT2_PIN, OUTPUT);
  pinMode(A1, INPUT); // Analog input from potentiometer
}

void loop() {
  int adcValue = analogRead(A1); // Read analog voltage
  float voltage = adcValue * (5.0 / 1023.0); // Convert to voltage
  int displayVal = voltage * 100; // e.g., 4.23V → 423

  if (adcValue >= 1023) {
    displayDigits(10, 10, 10); // Show "---" for error
  } else {
    int hundreds = displayVal / 100;
    int tens = (displayVal / 10) % 10;
    int ones = displayVal % 10;

    // Multiplexed display
    for (int i = 0; i < 50; i++) {
      displayDigits(hundreds, tens, ones);
    }
  }
}

void displayDigits(int d1, int d2, int d3) {
  // Digit 1 (hundreds)
  digitalWrite(DIGIT1_PIN, LOW);
  digitalWrite(DIGIT2_PIN, HIGH);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, digitMap[d1]);
  latch();
  delay(2); // Reduced delay to prevent overcurrent

  // Digit 2 (tens)
  digitalWrite(DIGIT1_PIN, HIGH);
  digitalWrite(DIGIT2_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, digitMap[d2]);
  latch();
  delay(2); // Reduced delay to prevent overcurrent

  // Digit 3 (ones)
  digitalWrite(DIGIT1_PIN, LOW);
  digitalWrite(DIGIT2_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, digitMap[d3]);
  latch();
  delay(2); // Reduced delay to prevent overcurrent
}

void latch() {
  digitalWrite(LATCH_PIN, LOW);
  digitalWrite(LATCH_PIN, HIGH);
}

// --- Prevent 8-bit register (shift register/7-segment) overcurrent/overflow ---

/*
 * If your 8-bit shift register or USB is overloaded:
 * 1. Make sure you have a current-limiting resistor (e.g., 100Ω) in series with each segment pin (total 8 resistors).
 * 2. Never connect 7-segment display segments directly to 5V or GND without resistors.
 * 3. Only one digit should be ON at a time (multiplexing). If you turn on multiple digits at once, current will add up and can overload the register or USB.
 * 4. Reduce the delay in displayDigits() (e.g., delay(2) instead of delay(5)) to make multiplexing faster and reduce average current.
 * 5. If possible, use higher-value resistors (220Ω–470Ω) for each segment to further limit current.
 * 6. Double-check wiring for shorts or mistakes.
 * 7. If using common anode/cathode, make sure digit enable logic is correct (only one digit LOW at a time).
 *
 * Example fix in code:
 * - Use delay(2) instead of delay(5) in displayDigits().
 * - Make sure only one digit enable pin is LOW at a time.
 */
