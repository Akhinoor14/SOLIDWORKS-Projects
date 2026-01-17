# 📟 Digital Potentiometer with Voltage Divider

![Arduino](https://img.shields.io/badge/Arduino-UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![LCD](https://img.shields.io/badge/Display-16x2_LCD-blue?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Beginner-brightgreen?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Complete-success?style=for-the-badge)

A comprehensive Arduino project that demonstrates **voltage divider principles** using a 1MΩ and 10kΩ resistor network. The Arduino reads the divided voltage through its ADC, calculates the original input voltage using the voltage divider formula, and displays the result in real-time on a 16×2 LCD display.

---

## 📑 Table of Contents

- [Overview](#-overview)
- [Learning Objectives](#-learning-objectives)
- [Components Required](#-components-required)
- [Voltage Divider Theory](#-voltage-divider-theory)
- [Circuit Diagram](#-circuit-diagram)
- [Circuit Connections](#-circuit-connections)
- [Code Explanation](#-code-explanation)
- [How It Works](#-how-it-works)
- [Mathematical Analysis](#-mathematical-analysis)
- [LCD Display Format](#-lcd-display-format)
- [Calibration & Testing](#-calibration--testing)
- [Troubleshooting](#-troubleshooting)
- [Real-World Applications](#-real-world-applications)
- [Project Extensions](#-project-extensions)
- [Challenges](#-challenges)
- [Author](#-author)

---

## 🎯 Overview

This project demonstrates the fundamental electronics concept of **voltage division** using two resistors in series. The Arduino measures the voltage at the divider's midpoint and reverse-calculates the input voltage using the divider formula. This technique is essential for:
- **Scaling down high voltages** to Arduino-safe levels (0-5V)
- **Understanding ADC operation** and analog signal processing
- **Implementing sensor interfacing** circuits
- **Voltage monitoring** in battery-powered systems

### Key Features:
- ✅ 1MΩ + 10kΩ voltage divider network
- ✅ Real-time analog voltage measurement
- ✅ Voltage divider formula implementation
- ✅ 16×2 LCD display with 2 decimal precision
- ✅ Serial Monitor debugging output
- ✅ Foundation for sensor signal conditioning

---

## 🎓 Learning Objectives

By completing this project, you will learn:

| Concept | Description | Practical Application |
|---------|-------------|----------------------|
| **Voltage Divider** | Series resistors divide voltage proportionally | Signal scaling, sensor conditioning |
| **ADC Fundamentals** | Convert analog voltage to digital value | All analog measurements |
| **Resistor Networks** | How resistor ratios affect voltage | Circuit design, impedance matching |
| **Formula Implementation** | Coding mathematical equations | Engineering calculations |
| **LCD Interfacing** | Display numerical data in real-time | User interfaces, instrumentation |
| **Floating-Point Math** | Precision arithmetic in microcontrollers | Scientific computing |

---

## 🧰 Components Required

| Component | Quantity | Specifications | Purpose |
|-----------|----------|----------------|---------|
| Arduino UNO | 1 | ATmega328P, 5V logic | Microcontroller |
| 16×2 LCD Display | 1 | HD44780 compatible, 4-bit mode | Voltage display |
| 1MΩ Resistor | 1 | ±5% tolerance (Brown-Black-Green) | Upper divider resistor (R1) |
| 10kΩ Resistor | 1 | ±5% tolerance (Brown-Black-Orange) | Lower divider resistor (R2) |
| 10kΩ Potentiometer | 1 | For LCD contrast | Display adjustment |
| 220Ω Resistor | 1 (optional) | For LCD backlight | Current limiting |
| Breadboard | 1 | 830 tie-points | Prototyping |
| Jumper Wires | ~20 | Male-to-Male | Connections |
| USB Cable | 1 | Type A to Type B | Programming & Power |

### 💰 Estimated Cost: ৳300-500 ($4-6 USD)

---

## 🔬 Voltage Divider Theory

### What is a Voltage Divider?

A **voltage divider** is a fundamental circuit consisting of two resistors in series that divides an input voltage into a smaller output voltage. The output voltage is determined by the ratio of the resistances.

### Basic Voltage Divider Circuit:

```
Voltage Divider Schematic:
         Vin (5V from Arduino)
          │
          ├──── Input Voltage
          │
         ╱╲
        │  │  R1 (1MΩ) ← Upper Resistor
        │  │
          │
          ├──── Vout (Node A) → to A0
          │
         ╱╲
        │  │  R2 (10kΩ) ← Lower Resistor
        │  │
          │
         GND
```

### The Voltage Divider Formula:

```
Output Voltage:
  Vout = Vin × (R2 / (R1 + R2))

Reverse Calculation (to find Vin):
  Vin = Vout × ((R1 + R2) / R2)

Where:
  Vin  = Input voltage (what we want to find)
  Vout = Output voltage (measured by Arduino at A0)
  R1   = Upper resistor (1MΩ)
  R2   = Lower resistor (10kΩ)
```

### Our Implementation:

**Given:**
- R1 = 1,000,000 Ω (1 MΩ)
- R2 = 10,000 Ω (10 kΩ)
- Vin = 5V (Arduino supply)

**Calculate Vout:**
```
Vout = 5V × (10,000 / (1,000,000 + 10,000))
     = 5V × (10,000 / 1,010,000)
     = 5V × 0.00990099
     = 0.0495V (approximately 49.5 mV)
```

**Reverse Calculation (from code):**
```
Vin = Vout × ((1,000,000 + 10,000) / 10,000)
    = Vout × (1,010,000 / 10,000)
    = Vout × 101
    = 0.0495V × 101
    = 5.00V ✓
```

### Divider Ratio Analysis:

```
Divider Ratio = (R1 + R2) / R2
              = (1,000,000 + 10,000) / 10,000
              = 1,010,000 / 10,000
              = 101

This means:
  - Output voltage is 101 times smaller than input
  - To recover input: multiply output by 101
  - This allows measuring voltages up to 505V (theoretically)
    but limited by Arduino's 5V ADC reference
```

### Why These Resistor Values?

```
Design Considerations:
┌────────────────────────────────────────┐
│ R1 = 1MΩ (High Resistance):           │
│   ✅ Minimal current draw              │
│   ✅ Low power consumption             │
│   ✅ High input impedance              │
│   ❌ Susceptible to noise              │
│                                        │
│ R2 = 10kΩ (Moderate Resistance):      │
│   ✅ Good balance with R1              │
│   ✅ Suitable for Arduino ADC input    │
│   ✅ Creates 101:1 division ratio      │
│                                        │
│ Divider Ratio = 101:1                 │
│   ✅ Large scaling factor              │
│   ✅ Allows high voltage measurement   │
│   ⚠️ But limited by 5V Arduino limit  │
└────────────────────────────────────────┘

Current Through Divider:
  I = Vin / (R1 + R2)
    = 5V / 1,010,000Ω
    = 4.95 µA (microamperes)
  
  Power Dissipation:
  P = I² × (R1 + R2)
    = (4.95µA)² × 1,010,000Ω
    = 24.75 µW (microwatts)
  
  Very low power consumption!
```

---

## 📐 Circuit Diagram

### Complete System Schematic:

```
Arduino UNO                    Voltage Divider
┌─────────────────┐           ┌──────────────────┐
│                 │   +5V     │                  │
│   5V  ●─────────┼───────────┤●─────┐           │
│                 │           │      │           │
│                 │           │     ╱╲           │
│                 │           │    │  │ R1 (1MΩ) │
│                 │           │    │  │          │
│                 │           │     ╲╱           │
│                 │           │      │           │
│                 │  Node A   │      │           │
│   A0  ●─────────┼───────────┤──────┴─── Vout  │
│                 │           │      │           │
│                 │           │     ╱╲           │
│                 │           │    │  │ R2 (10kΩ)│
│                 │           │    │  │          │
│                 │           │     ╲╱           │
│                 │           │      │           │
│  GND  ●─────────┼───────────┤──────┴───────────┤
│                 │           └──────────────────┘
│                 │
│                 │           16×2 LCD Display
│                 │           ┌──────────────────┐
│   5V  ●─────────┼───────────┤ VDD (2)          │
│  GND  ●─────────┼───────────┤ VSS (1)          │
│                 │           │ RW (5)           │
│                 │   ┌─Pot─┐ │                  │
│   5V  ●─────────┼───┤R   │ │                  │
│  GND  ●─────────┼───┤L   │ │                  │
│                 │   │M───┼─┤ VO (3)           │
│                 │   └────┘ │                  │
│  D12  ●─────────┼───────────┤ RS (4)           │
│  D11  ●─────────┼───────────┤ EN (6)           │
│   D5  ●─────────┼───────────┤ D4 (11)          │
│   D4  ●─────────┼───────────┤ D5 (12)          │
│   D3  ●─────────┼───────────┤ D6 (13)          │
│   D2  ●─────────┼───────────┤ D7 (14)          │
│                 │  [220Ω]   │                  │
│   5V  ●─────────┼───[===]───┤ LED+ (15)        │
│  GND  ●─────────┼───────────┤ LED- (16)        │
└─────────────────┘           └──────────────────┘

Key Points:
  • Node A = Junction of R1 and R2 (voltage divider output)
  • A0 reads divided voltage (Vout)
  • Code multiplies Vout by 101 to get original Vin
```

### Physical Breadboard Layout:

```
Breadboard View (Top):
┌───────────────────────────────────────────────────┐
│  Power Rails:                                     │
│  [+5V] ────────────────────────────────────       │
│  [GND] ────────────────────────────────────       │
│                                                   │
│  Voltage Divider:                                 │
│    +5V ─── [1MΩ] ─── Node A ─── [10kΩ] ─── GND  │
│                        │                          │
│                        └─── to A0                 │
│                                                   │
│  LCD Display (16×2):                              │
│    RS→D12, EN→D11, D4-D7→D5-D2                    │
│    Contrast pot connected to VO                   │
│    VSS→GND, VDD→+5V                               │
│                                                   │
│  Arduino UNO mounted on breadboard                │
└───────────────────────────────────────────────────┘
```

---

## 🔌 Circuit Connections

### Detailed Pin Mapping:

**Voltage Divider Network:**

| Component | Terminal | Arduino Pin | Wire Color (suggested) | Function |
|-----------|----------|-------------|------------------------|----------|
| 1MΩ Resistor (R1) | Leg 1 | 5V | Red | Input voltage |
| 1MΩ Resistor (R1) | Leg 2 | Node A → A0 | Yellow | Divider output |
| 10kΩ Resistor (R2) | Leg 1 | Node A (with R1 Leg 2) | - | Junction point |
| 10kΩ Resistor (R2) | Leg 2 | GND | Black | Ground reference |

**16×2 LCD Display (4-bit mode):**

| LCD Pin | Pin # | Arduino Pin | Function |
|---------|-------|-------------|----------|
| VSS | 1 | GND | Ground |
| VDD | 2 | 5V | Power supply |
| VO | 3 | Pot middle | Contrast adjustment |
| RS | 4 | D12 | Register Select |
| RW | 5 | GND | Read/Write (Write mode) |
| EN | 6 | D11 | Enable |
| D4 | 11 | D5 | Data bit 4 |
| D5 | 12 | D4 | Data bit 5 |
| D6 | 13 | D3 | Data bit 6 |
| D7 | 14 | D2 | Data bit 7 |
| LED+ | 15 | 5V (via 220Ω) | Backlight anode |
| LED- | 16 | GND | Backlight cathode |

**Potentiometer (LCD Contrast):**

| Terminal | Connection |
|----------|------------|
| Left | GND |
| Middle | LCD VO (Pin 3) |
| Right | 5V |

---

### Step-by-Step Wiring Guide:

```
STEP 1: Create Voltage Divider
  Arduino 5V → 1MΩ Resistor Leg 1
  1MΩ Resistor Leg 2 → Node A (breadboard row)
  Node A → 10kΩ Resistor Leg 1
  10kΩ Resistor Leg 2 → Arduino GND

STEP 2: Connect ADC Input
  Node A → Arduino A0 (yellow wire)

STEP 3: LCD Power
  LCD VSS (Pin 1) → GND
  LCD VDD (Pin 2) → 5V

STEP 4: LCD Control Pins
  LCD RS (Pin 4) → D12
  LCD RW (Pin 5) → GND (write mode)
  LCD EN (Pin 6) → D11

STEP 5: LCD Data Pins (4-bit mode)
  LCD D4 (Pin 11) → D5
  LCD D5 (Pin 12) → D4
  LCD D6 (Pin 13) → D3
  LCD D7 (Pin 14) → D2

STEP 6: LCD Backlight
  LCD LED+ (Pin 15) → 5V (optionally via 220Ω resistor)
  LCD LED- (Pin 16) → GND

STEP 7: LCD Contrast Potentiometer
  Pot Left → GND
  Pot Middle → LCD VO (Pin 3)
  Pot Right → 5V

STEP 8: Verify All Connections
  ✓ Voltage divider: 5V → 1MΩ → Node A → 10kΩ → GND
  ✓ Node A connected to A0
  ✓ LCD in 4-bit mode (only D4-D7 connected)
  ✓ LCD RS, EN on D12, D11
  ✓ Common ground for all components
```

---

## 💻 Code Explanation

### Complete Arduino Code:

```cpp
/*
 * Project 22: Digital Potentiometer with Voltage Divider
 * Author: Md. Akhinoor Islam
 * Department: ESE (Energy Science and Engineering), KUET
 * Description: Reads analog voltage from a 1MΩ + 10kΩ voltage divider,
 *              calculates the input voltage using divider formula,
 *              and displays it on a 16×2 LCD in real-time.
 */

#include <LiquidCrystal.h>

// LCD initialization (RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Voltage divider resistor values
const float R1 = 1000000.0;  // 1 MΩ (upper resistor)
const float R2 = 10000.0;    // 10 kΩ (lower resistor)

// Analog input pin
const int analogPin = A0;

// Variables
float inputVoltage = 0.0;    // Calculated input voltage
float vout = 0.0;            // Measured output voltage at Node A

void setup() {
  // Initialize Serial for debugging
  Serial.begin(9600);
  Serial.println("Digital Potentiometer - Voltage Divider");
  Serial.println("========================================");
  
  // Initialize LCD (16 columns, 2 rows)
  lcd.begin(16, 2);
  
  // Display title on first row
  lcd.setCursor(0, 0);
  lcd.print("Digital Voltage");
  
  delay(1000);
}

void loop() {
  // Read analog value from voltage divider (0-1023)
  int sensorValue = analogRead(analogPin);
  
  // Convert ADC reading to actual voltage (0-5V)
  vout = (sensorValue * 5.0) / 1023.0;
  
  // Calculate input voltage using voltage divider formula
  // Vin = Vout × ((R1 + R2) / R2)
  inputVoltage = vout * ((R1 + R2) / R2);
  
  // Display on LCD (second row)
  lcd.setCursor(0, 1);
  lcd.print("V: ");
  lcd.print(inputVoltage, 2);  // 2 decimal places
  lcd.print(" V   ");           // Extra spaces clear old text
  
  // Debug output to Serial Monitor
  Serial.print("ADC: ");
  Serial.print(sensorValue);
  Serial.print(" | Vout: ");
  Serial.print(vout, 4);
  Serial.print("V | Vin: ");
  Serial.print(inputVoltage, 2);
  Serial.println("V");
  
  delay(500);  // Update twice per second
}
```

---

### 📖 Line-by-Line Code Breakdown:

#### 1. Library Include

```cpp
#include <LiquidCrystal.h>
```

**Purpose:**
- Include Arduino's built-in LCD library
- Provides functions for LCD control: `begin()`, `print()`, `setCursor()`, `clear()`

#### 2. LCD Object Declaration

```cpp
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
```

**Constructor Parameters:**
```cpp
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
                 (12, 11, 5,  4,  3,  2);
```

| Parameter | Arduino Pin | LCD Pin | Function |
|-----------|-------------|---------|----------|
| RS | D12 | 4 | Register Select |
| EN | D11 | 6 | Enable |
| D4 | D5 | 11 | Data bit 4 |
| D5 | D4 | 12 | Data bit 5 |
| D6 | D3 | 13 | Data bit 6 |
| D7 | D2 | 14 | Data bit 7 |

#### 3. Resistor Value Constants

```cpp
const float R1 = 1000000.0;  // 1 MΩ
const float R2 = 10000.0;    // 10 kΩ
```

**Why `const float`?**
- `const` = value cannot be changed (safety)
- `float` = floating-point number (decimal precision)
- `.0` suffix ensures floating-point arithmetic

**Resistor Values:**
```
R1 = 1,000,000 Ω = 1 MΩ
R2 = 10,000 Ω = 10 kΩ

Divider Ratio = (R1 + R2) / R2
              = 1,010,000 / 10,000
              = 101
```

#### 4. Analog Pin Definition

```cpp
const int analogPin = A0;
```

- Defines which analog pin reads the voltage divider output
- A0 is Arduino's first analog input (10-bit ADC)

#### 5. Global Variables

```cpp
float inputVoltage = 0.0;
float vout = 0.0;
```

- `inputVoltage` - Calculated original voltage (Vin)
- `vout` - Measured voltage at Node A (voltage divider output)
- Initialized to 0.0 for clarity

#### 6. Setup Function

```cpp
void setup() {
  Serial.begin(9600);
  Serial.println("Digital Potentiometer - Voltage Divider");
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Digital Voltage");
  delay(1000);
}
```

**Breakdown:**

**a) Serial Communication:**
```cpp
Serial.begin(9600);
Serial.println("Digital Potentiometer - Voltage Divider");
```
- Initialize Serial at 9600 baud
- Print startup header for identification

**b) LCD Initialization:**
```cpp
lcd.begin(16, 2);
```
- Initialize 16×2 LCD (16 columns, 2 rows)
- Configures 4-bit communication mode
- Must be called before any LCD operations

**c) Display Title:**
```cpp
lcd.setCursor(0, 0);
lcd.print("Digital Voltage");
```
- `setCursor(column, row)` - Position cursor at (0, 0) = top-left
- Display permanent title on first row

**d) Startup Delay:**
```cpp
delay(1000);
```
- Wait 1 second before starting measurements
- Allows LCD to stabilize and user to see title

---

#### 7. Main Loop - Analog Reading

```cpp
int sensorValue = analogRead(analogPin);
```

**Function: `analogRead()`**

| Aspect | Details |
|--------|---------|
| Purpose | Read analog voltage on pin A0 |
| Return Type | Integer (int) |
| Range | 0 to 1023 (10-bit ADC) |
| Voltage Mapping | 0 = 0V, 1023 = 5V |
| Resolution | 5V / 1023 = 4.89 mV per step |
| Conversion Time | ~100 microseconds |

**Example Readings:**
```
5V input (before divider):
  Vout at Node A = 5V × (10k / 1010k) = 0.0495V
  ADC = (0.0495 / 5.0) × 1023 ≈ 10
  
2.5V input:
  Vout = 2.5V × 0.0099 = 0.02475V
  ADC ≈ 5
```

---

#### 8. ADC to Voltage Conversion

```cpp
vout = (sensorValue * 5.0) / 1023.0;
```

**Formula Explanation:**

```
Goal: Convert ADC value (0-1023) to actual voltage (0-5V)

Formula: Vout = (ADC / 1023) × Vref
Where: Vref = 5.0V (Arduino reference voltage)

Simplified: Vout = ADC × (5.0 / 1023.0)

Why 1023 not 1024?
  - ADC range: 0 to 1023 (that's 1024 values total)
  - But: 0 represents 0V, 1023 represents 5V
  - Division by 1023 gives correct mapping

Example Calculations:
  sensorValue = 0
    vout = 0 × (5.0/1023) = 0.000V
  
  sensorValue = 10 (from 5V input)
    vout = 10 × (5.0/1023) = 0.0489V
  
  sensorValue = 1023
    vout = 1023 × (5.0/1023) = 5.000V
```

---

#### 9. Input Voltage Calculation

```cpp
inputVoltage = vout * ((R1 + R2) / R2);
```

**Voltage Divider Formula Reverse:**

```
Standard Divider Formula:
  Vout = Vin × (R2 / (R1 + R2))

Rearranged to Find Vin:
  Vin = Vout × ((R1 + R2) / R2)

Substituting Our Values:
  Vin = Vout × ((1,000,000 + 10,000) / 10,000)
      = Vout × (1,010,000 / 10,000)
      = Vout × 101

Example Calculation:
  vout = 0.0489V (measured at Node A)
  inputVoltage = 0.0489 × 101
               = 4.94V ≈ 5V ✓
```

**Why Multiply by 101?**
```
The divider reduces voltage by factor of 101
To recover original voltage: multiply by 101
This is the "reverse" of voltage division
```

---

#### 10. LCD Display

```cpp
lcd.setCursor(0, 1);
lcd.print("V: ");
lcd.print(inputVoltage, 2);
lcd.print(" V   ");
```

**Breakdown:**

**a) Position Cursor:**
```cpp
lcd.setCursor(0, 1);
```
- Column 0, Row 1 (second line, leftmost position)
- LCD coordinates: (0,0) = top-left, (15,1) = bottom-right

**b) Print Label:**
```cpp
lcd.print("V: ");
```
- Display "V: " prefix for clarity

**c) Print Voltage:**
```cpp
lcd.print(inputVoltage, 2);
```
- Second parameter `2` = number of decimal places
- `inputVoltage = 5.00` displays as "5.00"

**d) Clear Trailing Characters:**
```cpp
lcd.print(" V   ");
```
- Prints " V" unit
- Extra spaces clear previous longer text
- Prevents ghost characters from previous updates

**LCD Display Format:**
```
Row 0: |D|i|g|i|t|a|l| |V|o|l|t|a|g|e| |
       0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

Row 1: |V|:| |5|.|0|0| |V| | | | | | | |
       0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
```

---

#### 11. Serial Monitor Debug Output

```cpp
Serial.print("ADC: ");
Serial.print(sensorValue);
Serial.print(" | Vout: ");
Serial.print(vout, 4);
Serial.print("V | Vin: ");
Serial.print(inputVoltage, 2);
Serial.println("V");
```

**Sample Serial Output:**
```
Digital Potentiometer - Voltage Divider
========================================
ADC: 10 | Vout: 0.0489V | Vin: 4.94V
ADC: 10 | Vout: 0.0489V | Vin: 4.94V
ADC: 11 | Vout: 0.0538V | Vin: 5.43V
```

**Debug Information:**
- `ADC` - Raw ADC reading (0-1023)
- `Vout` - Voltage at Node A (4 decimal places)
- `Vin` - Calculated input voltage (2 decimal places)

---

#### 12. Loop Delay

```cpp
delay(500);
```

- Wait 500 milliseconds (0.5 seconds)
- Updates display twice per second
- Prevents flicker and reduces serial spam
- Balance between responsiveness and stability

---

## ⚙️ How It Works

### System Operation Flow:

```
┌─────────────────────────────────────────┐
│  POWER ON                               │
└──────────────┬──────────────────────────┘
               ↓
┌─────────────────────────────────────────┐
│  INITIALIZATION                         │
│  • Serial @ 9600 baud starts            │
│  • LCD initialized (16×2)               │
│  • Display "Digital Voltage" title      │
│  • R1=1MΩ, R2=10kΩ defined              │
└──────────────┬──────────────────────────┘
               ↓
┌─────────────────────────────────────────┐
│  MAIN LOOP (Continuous)                 │
└──────────────┬──────────────────────────┘
               ↓
       ┌───────┴───────┐
       │               │
       ↓               ↓
┌──────────────┐ ┌─────────────┐
│ MEASURE      │ │ CALCULATE   │
│ Analog A0    │ │ • ADC→Vout  │
│ (0-1023)     │ │ • Vout×101  │
└──────┬───────┘ └──────┬──────┘
       │                │
       └────────┬───────┘
                ↓
      ┌───────────────────┐
      │ DISPLAY RESULTS   │
      │ • LCD: "V: X.XXV" │
      │ • Serial: Debug   │
      └─────────┬─────────┘
                ↓
          Wait 500ms
                ↓
          Repeat Loop
```

### Physical Process:

```
Input Voltage (5V) → R1 (1MΩ) → Node A → R2 (10kΩ) → GND
                                    │
                                    ↓
                            Arduino A0 (ADC)
                                    ↓
                        Digital Value (0-1023)
                                    ↓
                    Convert to Voltage (Vout)
                                    ↓
                    Multiply by 101 (Vin)
                                    ↓
                        Display on LCD
```

---

## 📊 Mathematical Analysis

### Complete Voltage Calculation Example:

**Given:**
- Arduino 5V supply
- R1 = 1 MΩ
- R2 = 10 kΩ

**Step 1: Voltage Divider Output**
```
Vout = Vin × (R2 / (R1 + R2))
     = 5V × (10,000 / 1,010,000)
     = 5V × 0.00990099
     = 0.0495V (49.5 mV)
```

**Step 2: ADC Reading**
```
ADC = (Vout / Vref) × 1023
    = (0.0495 / 5.0) × 1023
    = 0.0099 × 1023
    = 10.13 ≈ 10
```

**Step 3: Voltage Conversion**
```
Vout = (ADC / 1023) × 5.0
     = (10 / 1023) × 5.0
     = 0.0489V
```

**Step 4: Input Voltage Calculation**
```
Vin = Vout × ((R1 + R2) / R2)
    = 0.0489V × ((1,000,000 + 10,000) / 10,000)
    = 0.0489V × 101
    = 4.94V
```

**Accuracy Analysis:**
```
Expected: 5.00V
Calculated: 4.94V
Error: (5.00 - 4.94) / 5.00 × 100% = 1.2%

Error Sources:
  • ADC quantization (10-bit resolution)
  • Resistor tolerance (±5%)
  • Arduino voltage reference variation
  • Floating-point rounding
```

---

## 📺 LCD Display Format

### Display States:

#### Normal Operation:
```
┌────────────────┐
│Digital Voltage │ Row 0 (static)
│V: 5.00 V       │ Row 1 (updates every 0.5s)
└────────────────┘
```

#### Different Input Voltages:
```
5V Input:
┌────────────────┐
│Digital Voltage │
│V: 5.00 V       │
└────────────────┘

3.3V Input (if using external source):
┌────────────────┐
│Digital Voltage │
│V: 3.33 V       │
└────────────────┘

12V Input (if divider allows - see safety!):
┌────────────────┐
│Digital Voltage │
│V: 12.12 V      │
└────────────────┘
```

---

## 🔍 Calibration & Testing

### Test Procedure:

#### 1. **Basic Functionality Test**
```
Setup:
  - Use Arduino's own 5V supply
  - No external voltage source
  
Expected Results:
  - LCD shows approximately 4.9-5.1V
  - Serial Monitor matches LCD reading
  
Serial Output:
  ADC: 10 | Vout: 0.0489V | Vin: 4.94V
```

#### 2. **Resistor Verification**
```
Use multimeter to measure actual resistances:
  
Measure R1:
  Expected: 1 MΩ (1,000,000 Ω)
  Tolerance: ±5% (950,000 - 1,050,000 Ω)
  
Measure R2:
  Expected: 10 kΩ (10,000 Ω)
  Tolerance: ±5% (9,500 - 10,500 Ω)

Update code with actual values if needed:
  const float R1 = 982000.0;  // Measured value
  const float R2 = 9850.0;    // Measured value
```

#### 3. **ADC Verification**
```
Multimeter Test:
  1. Set multimeter to DC Voltage mode
  2. Red probe → Node A
  3. Black probe → Arduino GND
  
Comparison:
  Multimeter reading: 0.049V
  Serial Monitor Vout: 0.0489V
  
  Difference < 5mV = Good!
```

#### 4. **Calculation Verification**
```
Manual Calculation:
  Measured Vout = 0.049V
  Calculated Vin = 0.049 × 101 = 4.949V
  Arduino displays: 4.94V
  
  Match within 0.01V = Correct!
```

---

## 🔧 Troubleshooting

### Common Issues and Solutions:

| Problem | Possible Cause | Solution |
|---------|----------------|----------|
| **LCD blank** | No power | Check VDD (pin 2) to 5V |
| | Contrast not adjusted | Turn potentiometer slowly |
| **LCD shows boxes** | Contrast too high | Adjust potentiometer |
| | Wrong pin connections | Verify D2-D5, D11-D12 |
| **Voltage always 0V** | Node A disconnected | Check connection to A0 |
| | Resistor open circuit | Test resistors with multimeter |
| **Voltage always 5V** | Short circuit in divider | Check resistor connections |
| | ADC pin floating | Verify A0 connection |
| **Voltage unstable/flickering** | Poor connections | Re-seat all wires |
| | Electromagnetic interference | Keep wires short |
| **Wrong voltage reading** | Wrong resistor values | Verify R1=1MΩ, R2=10kΩ |
| | Code formula error | Check multiplication factor |
| | Resistor tolerance | Measure actual values |
| **LCD text garbled** | Wrong LCD pins | Check D2-D5 to LCD D7-D4 |
| | Poor LCD power | Verify VDD and VSS |
| **Serial Monitor empty** | Not opened | Tools → Serial Monitor |
| | Wrong baud rate | Set to 9600 |
| **Voltage too high/low** | Resistor mismatch | Re-check color codes |
| | Formula error | Verify (R1+R2)/R2 = 101 |

---

### Advanced Debugging:

#### Test ADC Reading:
```cpp
void loop() {
  int adc = analogRead(analogPin);
  Serial.print("Raw ADC: ");
  Serial.println(adc);
  delay(500);
}
// Expected: ~10 for 5V input
// If 0: check A0 connection
// If 1023: possible short to 5V
```

#### Test Voltage Conversion:
```cpp
void loop() {
  int adc = analogRead(analogPin);
  float v = (adc * 5.0) / 1023.0;
  Serial.print("ADC: ");
  Serial.print(adc);
  Serial.print(" → Voltage: ");
  Serial.print(v, 4);
  Serial.println("V");
  delay(500);
}
// Expected: ~0.0489V for 5V input
```

#### Test LCD Independently:
```cpp
void setup() {
  lcd.begin(16, 2);
  lcd.print("LCD Test");
  lcd.setCursor(0, 1);
  lcd.print("Line 2");
}
void loop() {}
// Expected: Two lines of clear text
```

---

## 🌍 Real-World Applications

### Where This Technology is Used:

| Application | Description | Industry |
|-------------|-------------|----------|
| **Battery Monitoring** | Measure high-voltage batteries | Automotive, renewable energy |
| **Power Supply Design** | Voltage sensing and regulation | Electronics |
| **Sensor Signal Conditioning** | Scale sensor outputs to ADC range | Industrial automation |
| **Multimeter Circuits** | High voltage measurement capability | Instrumentation |
| **Solar Panel Systems** | Monitor panel voltage (often >12V) | Renewable energy |
| **Motor Controllers** | Voltage feedback for control loops | Robotics |
| **Data Acquisition** | Multi-range voltage measurement | Research, testing |
| **Smart Home** | Monitor mains voltage (with safety) | IoT, home automation |

---

### Industry Example: Battery Voltage Monitor

```
12V Battery Monitoring System:
┌────────────────────────────────────────┐
│ 12V Lead-Acid Battery                 │
│   ├─ (+) Terminal                     │
│   └─ (-) Terminal                     │
├────────────────────────────────────────┤
│ Voltage Divider (for Arduino ADC)     │
│   ├─ R1: 220kΩ                        │
│   ├─ R2: 100kΩ                        │
│   └─ Divider ratio: 3.2:1             │
│        (12V → 3.75V safe for Arduino) │
├────────────────────────────────────────┤
│ Arduino Processing                     │
│   ├─ ADC reads divided voltage        │
│   ├─ Multiplies by 3.2                │
│   ├─ Displays actual battery voltage  │
│   └─ Triggers alarm if < 10.5V        │
├────────────────────────────────────────┤
│ User Interface                         │
│   ├─ LCD display (voltage)            │
│   ├─ LED indicator (battery health)   │
│   └─ Buzzer (low voltage alarm)       │
└────────────────────────────────────────┘
```

---

## 🚀 Project Extensions

### Beginner Level:

#### 1. **Add LED Voltage Indicator**
```cpp
#define LED_LOW A1
#define LED_MED A2
#define LED_HIGH A3

void setup() {
  pinMode(LED_LOW, OUTPUT);
  pinMode(LED_MED, OUTPUT);
  pinMode(LED_HIGH, OUTPUT);
}

void loop() {
  // ... voltage calculation ...
  
  if (inputVoltage < 3.0) {
    digitalWrite(LED_LOW, HIGH);
    digitalWrite(LED_MED, LOW);
    digitalWrite(LED_HIGH, LOW);
  } else if (inputVoltage < 4.0) {
    digitalWrite(LED_LOW, LOW);
    digitalWrite(LED_MED, HIGH);
    digitalWrite(LED_HIGH, LOW);
  } else {
    digitalWrite(LED_LOW, LOW);
    digitalWrite(LED_MED, LOW);
    digitalWrite(LED_HIGH, HIGH);
  }
}
```

#### 2. **Min/Max Voltage Tracking**
```cpp
float minVoltage = 100.0;
float maxVoltage = 0.0;

void loop() {
  // ... voltage calculation ...
  
  if (inputVoltage < minVoltage) minVoltage = inputVoltage;
  if (inputVoltage > maxVoltage) maxVoltage = inputVoltage;
  
  lcd.setCursor(0, 1);
  lcd.print("L:");
  lcd.print(minVoltage, 1);
  lcd.print(" H:");
  lcd.print(maxVoltage, 1);
}
```

#### 3. **Voltage Threshold Alarm**
```cpp
#define BUZZER 8
#define THRESHOLD 3.5

if (inputVoltage < THRESHOLD) {
  tone(BUZZER, 1000, 200);  // Beep warning
}
```

---

### Intermediate Level:

#### 4. **Multi-Range Voltmeter**
```cpp
// Switchable divider ratios for different ranges
#define RANGE_5V 0
#define RANGE_12V 1
#define RANGE_24V 2

int selectedRange = RANGE_5V;
float dividerRatio;

void selectRange(int range) {
  switch(range) {
    case RANGE_5V:
      dividerRatio = 1.0;  // Direct connection
      break;
    case RANGE_12V:
      dividerRatio = 3.2;  // 220k/100k divider
      break;
    case RANGE_24V:
      dividerRatio = 6.0;  // 500k/100k divider
      break;
  }
}
```

#### 5. **Data Logging to SD Card**
```cpp
#include <SD.h>
File dataFile;

void loop() {
  // ... voltage calculation ...
  
  dataFile = SD.open("voltage.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.print(millis());
    dataFile.print(",");
    dataFile.println(inputVoltage);
    dataFile.close();
  }
}
```

#### 6. **Averaging Filter (Noise Reduction)**
```cpp
const int numReadings = 10;
int readings[numReadings];
int readIndex = 0;
long total = 0;

void loop() {
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(analogPin);
  total = total + readings[readIndex];
  readIndex = (readIndex + 1) % numReadings;
  
  int average = total / numReadings;
  vout = (average * 5.0) / 1023.0;
  // ... rest of calculation ...
}
```

---

### Advanced Level:

#### 7. **WiFi IoT Voltage Monitor**
```cpp
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

void loop() {
  // ... voltage calculation ...
  
  ThingSpeak.setField(1, inputVoltage);
  ThingSpeak.writeFields(channelID, apiKey);
  
  // View data on ThingSpeak cloud dashboard
}
```

#### 8. **Calibration Mode**
```cpp
bool calibrationMode = false;
float calibrationFactor = 1.0;

void enterCalibrationMode() {
  // Apply known voltage
  // Measure ADC value
  // Calculate calibration factor
  float knownVoltage = 5.00;  // Measured with precision multimeter
  float measuredVoltage = calculateVoltage();
  calibrationFactor = knownVoltage / measuredVoltage;
}

void loop() {
  // ... normal calculation ...
  inputVoltage = inputVoltage * calibrationFactor;
}
```

---

## 🎯 Challenges

### 🟢 Beginner:
- [ ] Display voltage as a percentage (0-100%)
- [ ] Add button to reset min/max values
- [ ] Create bar graph display on LCD using custom characters

### 🟡 Intermediate:
- [ ] Build 3-range voltmeter (5V/12V/24V) with selector switch
- [ ] Add voltage trend arrow (↑ increasing, ↓ decreasing, → stable)
- [ ] Log voltage to SD card with timestamps

### 🔴 Advanced:
- [ ] Design auto-ranging voltmeter (automatically selects divider)
- [ ] Create web-based voltage monitoring dashboard
- [ ] Build precision voltmeter with calibration and temperature compensation

---

## 📚 Technical Reference

### Arduino Functions Used:

| Function | Syntax | Return | Description |
|----------|--------|--------|-------------|
| `analogRead()` | `analogRead(pin)` | int (0-1023) | Read analog voltage |
| `lcd.begin()` | `lcd.begin(cols, rows)` | void | Initialize LCD |
| `lcd.setCursor()` | `lcd.setCursor(col, row)` | void | Position cursor |
| `lcd.print()` | `lcd.print(data, decimals)` | void | Print text/number |
| `Serial.begin()` | `Serial.begin(baud)` | void | Initialize serial |
| `Serial.print()` | `Serial.print(data, decimals)` | void | Print to serial |
| `delay()` | `delay(ms)` | void | Pause execution |

### Resistor Color Codes:

**1MΩ Resistor:**
```
┌──[Brown][Black][Green][Gold]──┐
│    1      0      ×100k  ±5%   │
│  = 1,000,000 Ω = 1 MΩ         │
└───────────────────────────────┘
```

**10kΩ Resistor:**
```
┌──[Brown][Black][Orange][Gold]──┐
│    1      0      ×1000   ±5%   │
│  = 10,000 Ω = 10 kΩ            │
└────────────────────────────────┘
```

---

## 👨‍🎓 Author

**Md. Akhinoor Islam**  
📚 Department: Energy Science and Engineering (ESE)  
🏫 Institution: Khulna University of Engineering & Technology (KUET)  
🌐 GitHub: [@Akhinoor14](https://github.com/Akhinoor14)  
📧 Contact: [GitHub Profile](https://github.com/Akhinoor14)

---

## 🔗 Related Projects

- [Project 20: Light Intensity with LDR](../20%20Light%20intensity%20Measurement%20using%20LDR%20sensor/)
- [Project 19: TMP36 with LCD](../19%20tmp36%20with%2016-2%20LCD%20display%20temperature/)
- [Project 15: 16×2 LCD Display](../15%20Interfacing%2016-2%20Lcd%20display/)
- [Project 11: Temperature Sensor](../11%20Temperature%20sensor/)

---

## 📖 Learning Resources:

- [Arduino ADC Reference](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/)
- [Voltage Divider Calculator](https://ohmslawcalculator.com/voltage-divider-calculator)
- [LiquidCrystal Library](https://www.arduino.cc/en/Reference/LiquidCrystal)
- [Resistor Color Code](https://www.digikey.com/en/resources/conversion-calculators/conversion-calculator-resistor-color-code)

---

## 📜 License

This project is part of the **40 Arduino Projects Series** by Akhinoor Islam.  
Licensed under MIT License - see [LICENSE](../LICENSE) file for details.

---

## ✅ Project Completion Checklist:

- [ ] All components gathered
- [ ] Resistors verified (1MΩ and 10kΩ)
- [ ] Voltage divider assembled correctly
- [ ] Node A connected to A0
- [ ] LCD wired in 4-bit mode
- [ ] LCD contrast adjusted
- [ ] Code uploaded successfully
- [ ] Serial Monitor configured (9600 baud)
- [ ] LCD displays voltage (~5V)
- [ ] Serial Monitor shows ADC, Vout, Vin
- [ ] Voltage reading stable (±0.1V)
- [ ] Formula calculation verified manually

---

**Happy Building! 🎉**  
**Master voltage dividers and analog measurement fundamentals! 📟**

---

### 🌟 Key Takeaways:

1. **Voltage dividers** - Essential circuit for scaling voltages
2. **ADC operation** - Converting analog to digital with 10-bit resolution
3. **Formula implementation** - Translating math into code
4. **Real-time display** - User interface for measurements
5. **Precision arithmetic** - Floating-point calculations in embedded systems

Master this project and you'll understand voltage measurement, the foundation of multimeters, data acquisition systems, and sensor interfacing! 🚀