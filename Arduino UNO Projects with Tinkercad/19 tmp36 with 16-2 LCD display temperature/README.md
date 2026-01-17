# 🌡️ Temperature Display with TMP36 Sensor & 16×2 LCD

![Arduino Project](https://img.shields.io/badge/Arduino-UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Beginner-green?style=for-the-badge)
![Sensor](https://img.shields.io/badge/TMP36-Temperature-red?style=for-the-badge)

## 📋 Table of Contents
- [Overview](#-overview)
- [Components Required](#-components-required)
- [TMP36 Sensor Basics](#-tmp36-sensor-basics)
- [16×2 LCD Basics](#-162-lcd-basics)
- [Circuit Diagram](#-circuit-diagram)
- [How It Works](#-how-it-works)
- [Step-by-Step Guide](#-step-by-step-guide)
- [Code Explanation](#-code-explanation)
- [Simulation](#-simulation)
- [Troubleshooting](#-troubleshooting)
- [Learning Outcomes](#-learning-outcomes)
- [Author](#-author)

---

## 🎯 Overview

This project creates a **digital thermometer** using the **TMP36 analog temperature sensor** and displays real-time temperature readings on a **16×2 LCD display**. The system continuously monitors ambient temperature and updates the display every second, making it perfect for weather stations, room monitoring, and embedded system learning.

### Key Features:
- ✅ Real-time temperature monitoring
- ✅ Analog voltage to temperature conversion
- ✅ 16×2 LCD display with adjustable contrast
- ✅ Temperature range: -40°C to +125°C
- ✅ Accuracy: ±2°C (typical)
- ✅ Foundation for weather stations and IoT devices

---

## 🧰 Components Required

| Component | Quantity | Specification |
|-----------|----------|---------------|
| Arduino UNO | 1 | ATmega328P based |
| TMP36 Temperature Sensor | 1 | Analog output, -40°C to +125°C |
| 16×2 LCD Display | 1 | Parallel interface (HD44780 compatible) |
| 10kΩ Potentiometer | 1 | LCD contrast adjustment |
| 220Ω Resistor | 1 | LCD backlight (optional) |
| Breadboard | 1 | For circuit assembly |
| Jumper Wires | ~20 | Male-to-Male |
| USB Cable | 1 | Programming & power |

### 💰 Estimated Cost: $10-15 USD

---

## 🔬 TMP36 Sensor Basics

### What is TMP36?

The **TMP36** is a low-voltage, precision analog temperature sensor that outputs a voltage **linearly proportional** to temperature in Celsius.

### TMP36 Specifications:

| Parameter | Value |
|-----------|-------|
| Operating Voltage | 2.7V - 5.5V |
| Operating Current | <50 μA |
| Temperature Range | -40°C to +125°C |
| Output Voltage at 0°C | 500 mV (0.5V) |
| Scale Factor | 10 mV/°C |
| Accuracy | ±2°C (typical) |
| Response Time | <30 seconds |
| Package | TO-92 (3-pin) |

### TMP36 Pinout:

```
TMP36 Temperature Sensor
(Flat side facing you)

┌─────────────────┐
│                 │
│  TMP36          │
│                 │
└─┬───┬───┬───────┘
  │   │   │
  1   2   3
  
Pin 1 (Left):   +Vs (Power)    → 5V
Pin 2 (Middle): Vout (Signal)  → A0
Pin 3 (Right):  GND (Ground)   → GND

⚠️ IMPORTANT: Check orientation!
   Reversed connection can damage sensor
```

### Voltage-to-Temperature Formula:

```
TMP36 Output Characteristics:
┌──────────────────────────────────┐
│ Output Voltage = 500mV + (10mV/°C × Temp) │
│                                  │
│ At  0°C: 500mV (0.5V)           │
│ At 10°C: 600mV (0.6V)           │
│ At 25°C: 750mV (0.75V)          │
│ At 50°C: 1000mV (1.0V)          │
│ At 100°C: 1500mV (1.5V)         │
└──────────────────────────────────┘

Conversion Formula:
  Temperature (°C) = (Vout - 0.5) × 100
  
  or
  
  Temperature (°C) = (Vout - 500mV) / 10mV

Example:
  If Vout = 0.75V
  Temperature = (0.75 - 0.5) × 100
              = 0.25 × 100
              = 25°C
```

### Temperature vs Voltage Graph:

```
Voltage (V)
2.0V ├─────────────────────────────┐ 150°C
     │                          ╱  │
1.5V ├────────────────────╱        │ 100°C
     │                 ╱           │
1.0V ├────────────╱                │  50°C
     │         ╱                   │
0.5V ├────╱                        │   0°C
     │ ╱                           │
0.0V ├─────────────────────────────┘ -50°C
     0    25    50    75   100   125
            Temperature (°C)

Linear relationship: 10mV per 1°C
Slope = 10mV/°C
Offset = 500mV at 0°C
```

### ADC Conversion:

Arduino UNO has a **10-bit ADC** (0-1023):

```
ADC Conversion:
  Voltage = (ADC Value / 1023) × Reference Voltage
  Voltage = (ADC Value / 1023) × 5.0V

ADC Value → Voltage → Temperature:

Step 1: Read ADC
  int adcValue = analogRead(A0);  // 0-1023

Step 2: Convert to Voltage
  float voltage = adcValue × (5.0 / 1023.0);

Step 3: Convert to Temperature
  float tempC = (voltage - 0.5) × 100.0;
```

**ADC Value Examples:**

| ADC Value | Voltage (V) | Temperature (°C) |
|-----------|-------------|------------------|
| 102 | 0.50 | 0 |
| 153 | 0.75 | 25 |
| 204 | 1.00 | 50 |
| 306 | 1.50 | 100 |

---

## 📺 16×2 LCD Basics

### What is 16×2 LCD?

A **16×2 LCD** is a basic character display that can show **16 characters per row** and has **2 rows** (total 32 characters).

### LCD Specifications:

| Parameter | Value |
|-----------|-------|
| Display Type | Character LCD |
| Display Size | 16 columns × 2 rows |
| Controller | HD44780 or compatible |
| Operating Voltage | 5V |
| Operating Current | ~1-2 mA (without backlight) |
| Backlight Current | ~20-60 mA |
| Character Size | 5×8 dots |
| Interface Modes | 4-bit or 8-bit parallel |

### LCD Pin Configuration:

```
16×2 LCD Pinout (Top View)
┌────────────────────────────────┐
│  ■■■■■■■■■■■■■■■■■■■■■■■■■■■  │
│                                │
│  1  2  3  4  5  6  7-10 11-14 15 16│
└────────────────────────────────┘

Pin Map:
1  (VSS)   → Ground
2  (VDD)   → +5V Power
3  (VO)    → Contrast (0-5V via pot)
4  (RS)    → Register Select
5  (RW)    → Read/Write (GND = Write)
6  (EN)    → Enable
7  (D0)    → Data bit 0 (unused in 4-bit)
8  (D1)    → Data bit 1 (unused in 4-bit)
9  (D2)    → Data bit 2 (unused in 4-bit)
10 (D3)    → Data bit 3 (unused in 4-bit)
11 (D4)    → Data bit 4
12 (D5)    → Data bit 5
13 (D6)    → Data bit 6
14 (D7)    → Data bit 7
15 (A/LED+)→ Backlight anode (+5V)
16 (K/LED-)→ Backlight cathode (GND)
```

### 4-Bit vs 8-Bit Mode:

```
8-Bit Mode:
  ✅ Faster data transfer
  ❌ Uses 8 data pins (D0-D7)
  ❌ Requires 11 Arduino pins total

4-Bit Mode:
  ✅ Uses only 4 data pins (D4-D7)
  ✅ Requires only 7 Arduino pins total
  ✅ Saves pins for other components
  ❌ Slightly slower (negligible)
  
This project uses 4-bit mode!
```

### LCD Control Signals:

| Pin | Name | Function |
|-----|------|----------|
| **RS** | Register Select | LOW = Command, HIGH = Data |
| **RW** | Read/Write | LOW = Write, HIGH = Read |
| **EN** | Enable | HIGH pulse to latch data |

**Operation Timing:**
```
EN (Enable) Signal:
     ┌────┐
─────┘    └───── Data is latched on falling edge
     ↑    ↑
   Setup Hold
```

### Contrast Control:

```
10kΩ Potentiometer Wiring:
┌─────────────────────────┐
│  Pot (Top View)         │
│                         │
│    ┌───────┐           │
│    │   ●   │ Middle → LCD VO (Pin 3)
│ ┌──┴───────┴──┐        │
│ │             │        │
│ GND          5V        │
└─────────────────────────┘

Turning clockwise/counterclockwise:
  - Too dark: Turn potentiometer
  - Too light: Turn opposite direction
  - Just right: Characters clearly visible
```

---

## 🔌 Circuit Diagram

### Complete Connection Table:

**TMP36 Temperature Sensor:**
| TMP36 Pin | Arduino Pin | Description |
|-----------|-------------|-------------|
| Pin 1 (Left) | 5V | Power supply |
| Pin 2 (Middle) | A0 | Analog output |
| Pin 3 (Right) | GND | Ground |

**16×2 LCD Display:**
| LCD Pin | Arduino Pin | Description |
|---------|-------------|-------------|
| 1 (VSS) | GND | Ground |
| 2 (VDD) | 5V | Power |
| 3 (VO) | Potentiometer middle | Contrast |
| 4 (RS) | D7 | Register Select |
| 5 (RW) | GND | Write mode |
| 6 (EN) | D8 | Enable |
| 7-10 | Not connected | Unused (4-bit mode) |
| 11 (D4) | D9 | Data bit 4 |
| 12 (D5) | D10 | Data bit 5 |
| 13 (D6) | D11 | Data bit 6 |
| 14 (D7) | D12 | Data bit 7 |
| 15 (LED+) | 5V (via 220Ω) | Backlight anode |
| 16 (LED-) | GND | Backlight cathode |

**10kΩ Potentiometer:**
| Pot Terminal | Connection |
|--------------|------------|
| Left | GND |
| Middle | LCD Pin 3 (VO) |
| Right | 5V |

### Circuit Wiring Diagram:

```
Arduino UNO                        TMP36 Sensor
┌─────────────┐                   ┌──────────┐
│             │                   │  TMP36   │
│   5V  ●─────┼───────────────────┤ Pin 1    │
│             │                   │          │
│   A0  ●─────┼───────────────────┤ Pin 2    │
│             │                   │  (Vout)  │
│  GND  ●─────┼───────────────────┤ Pin 3    │
│             │                   └──────────┘
│             │
│             │                   16×2 LCD Display
│             │                   ┌──────────────┐
│   5V  ●─────┼───────────────────┤ VDD (2)      │
│  GND  ●─────┼───────────────────┤ VSS (1)      │
│             │                   │ RW (5)       │
│             │   ┌───Pot───┐     │              │
│   5V  ●─────┼───┤Right    │     │              │
│  GND  ●─────┼───┤Left     │     │              │
│             │   │Middle───┼─────┤ VO (3)       │
│             │   └─────────┘     │              │
│   D7  ●─────┼───────────────────┤ RS (4)       │
│   D8  ●─────┼───────────────────┤ EN (6)       │
│   D9  ●─────┼───────────────────┤ D4 (11)      │
│  D10  ●─────┼───────────────────┤ D5 (12)      │
│  D11  ●─────┼───────────────────┤ D6 (13)      │
│  D12  ●─────┼───────────────────┤ D7 (14)      │
│             │    [220Ω]         │              │
│   5V  ●─────┼────[===]──────────┤ LED+ (15)    │
│  GND  ●─────┼───────────────────┤ LED- (16)    │
└─────────────┘                   └──────────────┘
```

### 🖼️ Circuit Diagrams:
![Circuit 1](circuit.png)
![Circuit 2](circuit(2).png)

---

## ⚙️ How It Works

### System Operation Flow:

```
System Flowchart:
┌────────────────────────────┐
│  Arduino powers up         │
└──────────────┬─────────────┘
               ↓
┌────────────────────────────┐
│  Initialize LCD            │
│  - Set 4-bit mode          │
│  - Display "Temp Sensor    │
│    Ready"                  │
└──────────────┬─────────────┘
               ↓
         Wait 3 seconds
               ↓
┌────────────────────────────┐
│  Clear LCD                 │
└──────────────┬─────────────┘
               ↓
┌────────────────────────────┐
│  Main Loop (continuous)    │
└──────────────┬─────────────┘
               ↓
    ┌──────────┴──────────┐
    │                     │
    ↓                     ↓
Read TMP36           Display on LCD
(Analog A0)          Row 1: "Now Temp:"
    │                Row 2: "XX.XX C"
    ↓
Convert ADC to Voltage
voltage = ADC × 5/1023
    ↓
Convert Voltage to °C
tempC = (V - 0.5) × 100
    ↓
Wait 1 second
    ↓
Loop back to Read
```

### Temperature Reading Process:

```
Detailed Reading Cycle:

Step 1: TMP36 measures ambient temperature
  → Internal circuit generates voltage
  → Voltage = 500mV + (10mV × Temperature)

Step 2: Arduino reads analog pin A0
  → ADC converts voltage to 10-bit value (0-1023)
  → analogRead(A0) returns integer

Step 3: Convert ADC to voltage
  → voltage = (ADC_value / 1023) × 5.0V
  → Example: ADC=153 → (153/1023)×5 = 0.75V

Step 4: Apply TMP36 formula
  → tempC = (voltage - 0.5) × 100
  → Example: (0.75 - 0.5) × 100 = 25°C

Step 5: Format and display
  → lcd.print(tempC) → "25.00"
  → lcd.print(" C") → "25.00 C"

Step 6: Update every second
  → delay(1000) → Wait 1000ms
  → Loop repeats
```

### Temperature Calculation Examples:

```
Example 1: Room Temperature (25°C)
  ADC Reading: 153
  Voltage: 153 × (5.0/1023) = 0.748V
  Temperature: (0.748 - 0.5) × 100 = 24.8°C
  Display: "24.80 C"

Example 2: Warm Day (35°C)
  ADC Reading: 174
  Voltage: 174 × (5.0/1023) = 0.850V
  Temperature: (0.850 - 0.5) × 100 = 35.0°C
  Display: "35.00 C"

Example 3: Cold Room (10°C)
  ADC Reading: 123
  Voltage: 123 × (5.0/1023) = 0.601V
  Temperature: (0.601 - 0.5) × 100 = 10.1°C
  Display: "10.10 C"

Example 4: Freezing Point (0°C)
  ADC Reading: 102
  Voltage: 102 × (5.0/1023) = 0.498V
  Temperature: (0.498 - 0.5) × 100 = -0.2°C
  Display: "-0.20 C"
```

---

## 📝 Step-by-Step Guide

### 1. **Identify Component Pins**

**TMP36 Sensor:**
   - Flat side facing you
   - Left pin = Power (+5V)
   - Middle pin = Analog output (A0)
   - Right pin = Ground (GND)

**16×2 LCD:**
   - Check datasheet or common pinout
   - Pins numbered 1-16 from left to right
   - Some LCDs have pin labels on PCB

### 2. **Set Up Power Rails**
   ```
   Breadboard power rails:
     Red rail → Arduino 5V
     Blue rail → Arduino GND
   ```

### 3. **Connect TMP36 Sensor**
   ```
   TMP36 Pin 1 (Left) → 5V
   TMP36 Pin 2 (Middle) → Arduino A0
   TMP36 Pin 3 (Right) → GND
   ```
   
   **⚠️ Critical:** Double-check orientation!

### 4. **Connect Potentiometer**
   ```
   Left terminal → GND
   Middle terminal → LCD Pin 3 (VO)
   Right terminal → 5V
   ```

### 5. **Connect LCD Power**
   ```
   LCD Pin 1 (VSS) → GND
   LCD Pin 2 (VDD) → 5V
   LCD Pin 3 (VO) → Potentiometer middle
   ```

### 6. **Connect LCD Control Pins**
   ```
   LCD Pin 4 (RS) → Arduino D7
   LCD Pin 5 (RW) → GND
   LCD Pin 6 (EN) → Arduino D8
   ```

### 7. **Connect LCD Data Pins (4-bit mode)**
   ```
   LCD Pin 11 (D4) → Arduino D9
   LCD Pin 12 (D5) → Arduino D10
   LCD Pin 13 (D6) → Arduino D11
   LCD Pin 14 (D7) → Arduino D12
   ```
   
   Note: Pins 7-10 (D0-D3) remain unconnected

### 8. **Connect LCD Backlight (Optional)**
   ```
   LCD Pin 15 (LED+) → 5V (via 220Ω resistor)
   LCD Pin 16 (LED-) → GND
   ```
   
   Resistor limits current to protect backlight LED

### 9. **Install LiquidCrystal Library**
   - Open Arduino IDE
   - Library usually pre-installed
   - Verify: **Sketch > Include Library > LiquidCrystal**

### 10. **Upload Code**
   - Copy code from `19 tmp36 with 16-2 LCD display temperature.ino`
   - Select: **Tools > Board > Arduino UNO**
   - Select: **Tools > Port > [Your COM Port]**
   - Click **Upload**

### 11. **Adjust LCD Contrast**
   - Power on Arduino
   - LCD should show "Temp Sensor Ready"
   - If characters not visible:
     - Turn potentiometer slowly
     - Stop when characters clear

### 12. **Verify Temperature Display**
   - After 3 seconds, LCD clears
   - Row 1: "Now Temp:"
   - Row 2: Current temperature (e.g., "25.50 C")
   - Updates every second

---

## 💻 Code Explanation

### Full Code:

```cpp
/*
 * Project 19: Temperature Display with TMP36 & LCD
 * Author: Md Akhinoor Islam
 * Description: Real-time temperature monitoring on 16×2 LCD
 */

#include <LiquidCrystal.h>

// LCD pin connections: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// TMP36 connected to analog pin A0
const int tempPin = A0;

void setup() {
  lcd.begin(16, 2);              // Initialize 16×2 LCD
  lcd.setCursor(0, 0);           // Position at (column 0, row 0)
  lcd.print("Temp Sensor Ready");
  delay(3000);                   // Wait 3 seconds
  lcd.clear();                   // Clear display
}

void loop() {
  int analogValue = analogRead(tempPin);        // Read ADC (0-1023)
  float voltage = analogValue * (5.0 / 1023.0); // Convert to voltage
  float tempC = (voltage - 0.5) * 100.0;        // TMP36 formula

  lcd.setCursor(0, 0);           // Row 1, Column 1
  lcd.print("Now Temp:");
  
  lcd.setCursor(0, 1);           // Row 2, Column 1
  lcd.print(tempC);              // Print temperature
  lcd.print(" C");               // Add unit
  lcd.print("  ");               // Clear any leftover chars

  delay(1000);                   // Update every second
}
```

### Code Breakdown:

#### 1️⃣ **Include Library**

```cpp
#include <LiquidCrystal.h>
```

**Purpose:**
- Arduino's built-in library for LCD control
- Provides functions: `begin()`, `print()`, `setCursor()`, etc.
- Handles 4-bit/8-bit communication automatically

#### 2️⃣ **Initialize LCD Object**

```cpp
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
```

**Constructor Parameters:**

| Parameter | Arduino Pin | LCD Pin | Function |
|-----------|-------------|---------|----------|
| 1st (7) | D7 | RS (4) | Register Select |
| 2nd (8) | D8 | EN (6) | Enable |
| 3rd (9) | D9 | D4 (11) | Data bit 4 |
| 4th (10) | D10 | D5 (12) | Data bit 5 |
| 5th (11) | D11 | D6 (13) | Data bit 6 |
| 6th (12) | D12 | D7 (14) | Data bit 7 |

**Syntax:**
```cpp
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
```

#### 3️⃣ **Define Sensor Pin**

```cpp
const int tempPin = A0;
```

- `A0` = Analog pin 0
- Arduino UNO has 6 analog pins (A0-A5)
- `const` = Value won't change during runtime

#### 4️⃣ **Setup Function**

```cpp
void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temp Sensor Ready");
  delay(3000);
  lcd.clear();
}
```

**Step-by-Step:**

```cpp
lcd.begin(16, 2);
```
- Initializes LCD with 16 columns and 2 rows
- Configures LCD for 4-bit mode
- Must be called before any LCD operations

```cpp
lcd.setCursor(0, 0);
```
- Sets cursor position to (column 0, row 0)
- **Column 0** = 1st column (0-indexed)
- **Row 0** = 1st row (0-indexed)

**LCD Coordinate System:**
```
    Column: 0 1 2 3 4 5 ... 15
Row 0:      T e m p   S e n s o r
Row 1:      2 5 . 5 0   C
```

```cpp
lcd.print("Temp Sensor Ready");
```
- Prints string at current cursor position
- Continues until end of string
- Auto-wraps to next line if > 16 characters

```cpp
delay(3000);
lcd.clear();
```
- Wait 3000ms (3 seconds)
- `clear()` erases entire display
- Resets cursor to (0, 0)

#### 5️⃣ **Main Loop**

```cpp
void loop() {
  int analogValue = analogRead(tempPin);
  float voltage = analogValue * (5.0 / 1023.0);
  float tempC = (voltage - 0.5) * 100.0;
  
  lcd.setCursor(0, 0);
  lcd.print("Now Temp:");
  
  lcd.setCursor(0, 1);
  lcd.print(tempC);
  lcd.print(" C");
  lcd.print("  ");
  
  delay(1000);
}
```

**Step 1: Read Analog Value**
```cpp
int analogValue = analogRead(tempPin);
```

| What | Value |
|------|-------|
| Function | `analogRead(A0)` |
| Returns | Integer 0-1023 (10-bit ADC) |
| Time | ~100 microseconds |

**ADC Resolution:**
```
10-bit ADC:
  2^10 = 1024 steps
  0V → 0
  5V → 1023
  Resolution: 5V / 1023 = 4.89 mV per step
```

**Step 2: Convert to Voltage**
```cpp
float voltage = analogValue * (5.0 / 1023.0);
```

**Calculation:**
```
Formula: Voltage = (ADC / 1023) × Vref
         Voltage = (ADC / 1023) × 5.0

Why 5.0 and 1023.0 (not 1024)?
  - Arduino counts 0-1023 = 1024 total values
  - But 0 represents 0V, 1023 represents 5V
  - Division by 1023 gives accurate voltage

Example:
  analogValue = 512
  voltage = 512 × (5.0 / 1023.0)
          = 512 × 0.004887
          = 2.502V
```

**Step 3: Convert to Temperature**
```cpp
float tempC = (voltage - 0.5) * 100.0;
```

**TMP36 Formula Explained:**

```
TMP36 Equation:
  Vout = 500mV + (10mV/°C × Temperature)

Rearranging:
  Vout - 500mV = 10mV/°C × Temperature
  Temperature = (Vout - 500mV) / (10mV/°C)
  Temperature = (Vout - 0.5V) / 0.01V
  Temperature = (Vout - 0.5) × 100

Example:
  voltage = 0.75V
  tempC = (0.75 - 0.5) × 100
        = 0.25 × 100
        = 25.0°C
```

**Step 4: Display Row 1**
```cpp
lcd.setCursor(0, 0);
lcd.print("Now Temp:");
```

**LCD Output:**
```
Row 1: |N|o|w| |T|e|m|p|:| | | | | | | |
       0 1 2 3 4 5 6 7 8 9 ...     15
```

**Step 5: Display Row 2**
```cpp
lcd.setCursor(0, 1);
lcd.print(tempC);
lcd.print(" C");
lcd.print("  ");
```

**Why extra spaces?**
```
Without "  ":
  First: "25.50 C"
  Next:  "23.8 C"  → "23.8 C0" (leftover "0")

With "  ":
  First: "25.50 C  "
  Next:  "23.80 C  " → Clean display
```

**LCD Display Example:**
```
┌────────────────┐
│Now Temp:       │ Row 0
│25.50 C         │ Row 1
└────────────────┘
```

**Step 6: Update Interval**
```cpp
delay(1000);
```

- Wait 1000 milliseconds (1 second)
- Prevents display flickering
- Reduces power consumption
- Gives readable update rate

---

### Key Functions Reference:

| Function | Purpose | Parameters | Return |
|----------|---------|------------|--------|
| `lcd.begin(cols, rows)` | Initialize LCD | columns, rows | void |
| `lcd.clear()` | Clear display | none | void |
| `lcd.setCursor(col, row)` | Set cursor position | column (0-15), row (0-1) | void |
| `lcd.print(data)` | Print text/number | string or number | size_t |
| `analogRead(pin)` | Read analog value | pin (A0-A5) | int (0-1023) |
| `delay(ms)` | Wait | milliseconds | void |

---

## 🌐 Simulation

### Try it Online:
🔗 **[View on Tinkercad](https://www.tinkercad.com/things/dGNSZIXZWaz-19-tmp36-with-16-2-lcd-display-temperature)**

Features:
- Interactive temperature slider
- Real-time LCD update
- Contrast adjustment simulation
- Virtual temperature range testing

---

## 🔧 Troubleshooting

### Common Issues:

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| LCD shows nothing | No power | Check 5V and GND connections |
| LCD shows white boxes | Contrast too high/low | Adjust potentiometer |
| Garbled characters | Loose data wires | Check D9-D12 connections |
| Wrong temperature | TMP36 reversed | Check flat side orientation |
| Negative temperature | Wrong formula | Verify `(voltage - 0.5) × 100` |
| Temperature doesn't change | ADC not reading | Check A0 connection |
| Display flickers | Too fast update | Increase delay to 1000ms |
| Backlight too bright | No current limiting | Add 220Ω resistor |
| LCD initialized but blank | No contrast adjustment | Rotate potentiometer |

### Temperature Reading Issues:

**Symptom: Always shows 0°C or strange value**

**Causes:**
1. TMP36 wiring wrong
2. A0 pin disconnected
3. Sensor damaged

**Debug Code:**
```cpp
void loop() {
  int analogValue = analogRead(tempPin);
  Serial.print("ADC: ");
  Serial.print(analogValue);
  Serial.print(" | Voltage: ");
  float voltage = analogValue * (5.0 / 1023.0);
  Serial.print(voltage);
  Serial.print("V | Temp: ");
  float tempC = (voltage - 0.5) * 100.0;
  Serial.print(tempC);
  Serial.println("°C");
  delay(1000);
}
```

**Expected Output:**
```
ADC: 153 | Voltage: 0.75V | Temp: 25.0°C
ADC: 154 | Voltage: 0.75V | Temp: 25.1°C
```

### LCD Display Issues:

**Symptom: Can't see any characters**

**Solutions:**
1. Rotate potentiometer slowly
2. Check LCD power (pins 1 & 2)
3. Verify backlight (pins 15 & 16)
4. Test with simple code:
```cpp
void setup() {
  lcd.begin(16, 2);
  lcd.print("TEST");
}
void loop() {}
```

**Symptom: Random characters**

**Causes:**
- Data pins (D4-D7) loose
- RS or EN pin wrong
- Interference from other circuits

**Solution:**
- Recheck all LCD connections
- Use shorter wires
- Verify pin numbers in code

---

## 🎓 Learning Outcomes

### 📚 Concepts Covered:

| Concept | Description | Applications |
|---------|-------------|--------------|
| **Analog Sensing** | Reading continuous voltage signals | Sensors, instrumentation |
| **ADC Conversion** | Digital representation of analog | Data acquisition |
| **Linear Sensors** | Voltage proportional to measurement | TMP36, LM35, pressure sensors |
| **LCD Interfacing** | Character display control | User interfaces, meters |
| **4-bit Communication** | Efficient pin usage | Resource-constrained systems |
| **Data Formatting** | Clean display presentation | All display applications |

### 🚀 Skills Gained:
- ✅ Understanding analog temperature sensors
- ✅ ADC reading and voltage conversion
- ✅ Mathematical formula implementation
- ✅ LCD 4-bit mode configuration
- ✅ Real-time data display techniques
- ✅ Contrast control and calibration

### 🔄 Project Extensions:

1. **Temperature Logger** - Save data to SD card
2. **Min/Max Display** - Track daily highs and lows
3. **Temperature Alarm** - Buzzer for threshold alerts
4. **Multiple Sensors** - Compare room temperatures
5. **Celsius to Fahrenheit** - Button to switch units
6. **Graph on LCD** - Visual temperature trend
7. **WiFi Module** - Send data to cloud/web server

---

## 📁 Project Files

| File | Description |
|------|-------------|
| `README.md` | Complete project documentation |
| `19 tmp36 with 16-2 LCD display temperature.ino` | Arduino source code |
| `Code & Circuit Explanation(for beginner).md` | Bengali tutorial |
| `circuit.png` | Circuit diagram 1 |
| `circuit(2).png` | Circuit diagram 2 |
| `license` | MIT License |

---

## 👨‍🎓 Author

**Md Akhinoor Islam**  
📚 Energy Science and Engineering (ESE)  
🏫 Khulna University of Engineering & Technology (KUET)  
🌐 [GitHub Profile](https://github.com/Akhinoor14)

---

## 📄 License

This project is licensed under the MIT License.

---

## 🤝 Contributing

Enhance this project:
- Add temperature graphing
- Implement calibration routine
- Create data logging feature
- Add multiple display units
- Share your temperature monitoring projects!

---

## ⭐ Show Your Support

If this helped you learn about temperature sensing and LCD displays, give it a ⭐!

---

### 📌 Real-World Applications:

- 🏠 **Home Automation** - Room temperature monitoring
- 🌡️ **Weather Stations** - Outdoor temperature tracking
- 🔬 **Laboratory** - Precise temperature control
- 🏭 **Industrial** - Process temperature monitoring
- 🚗 **Automotive** - Engine temperature display
- 🍲 **Cooking** - Food temperature monitoring
- 💻 **PC Monitoring** - Component temperature tracking

Happy Temperature Monitoring! 🎉🌡️
