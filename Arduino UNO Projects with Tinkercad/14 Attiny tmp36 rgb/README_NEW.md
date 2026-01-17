# 🌡️ ATtiny85 Temperature Indicator with RGB LED

![ATtiny85](https://img.shields.io/badge/MCU-ATtiny85-blue?style=for-the-badge)
![TMP36](https://img.shields.io/badge/Sensor-TMP36-green?style=for-the-badge)
![RGB](https://img.shields.io/badge/Output-RGB%20LED-red?style=for-the-badge)
![Power](https://img.shields.io/badge/Battery-3V%20Coin%20Cell-orange?style=for-the-badge)
![Level](https://img.shields.io/badge/Difficulty-Intermediate-yellow?style=for-the-badge)

---

## 📚 Table of Contents
- [Project Overview](#-project-overview)
- [Key Features](#-key-features)
- [Components Required](#-components-required)
- [ATtiny85 Architecture](#-attiny85-architecture)
- [TMP36 Temperature Sensor](#-tmp36-temperature-sensor)
- [RGB LED Color Theory](#-rgb-led-color-theory)
- [Temperature Color Zones](#-temperature-color-zones)
- [Circuit Diagram](#-circuit-diagram)
- [Pin Configuration](#-pin-configuration)
- [Working Principle](#-working-principle)
- [Code Explanation](#-code-explanation)
- [Power Management](#-power-management)
- [Calibration Guide](#-calibration-guide)
- [Troubleshooting](#-troubleshooting)
- [Applications](#-applications)
- [Learning Outcomes](#-learning-outcomes)

---

## 🎯 Project Overview

This project creates a **portable, battery-operated temperature indicator** using the ATtiny85 microcontroller, TMP36 temperature sensor, and a common cathode RGB LED. The system displays **five distinct color zones** corresponding to different temperature ranges, making it perfect for wearable thermometers, environmental monitoring, or refrigerator temperature indicators.

### 🌟 What Makes This Special?

- **Low Power Design**: Runs on a 3V coin cell battery (CR2032)
- **Compact Size**: ATtiny85's 8-pin DIP package fits anywhere
- **Visual Feedback**: Intuitive color-coded temperature indication
- **No Display Required**: Colors directly represent temperature
- **Minimal Components**: Only 7 components total
- **Portable**: Perfect for wearable or remote monitoring

---

## ✨ Key Features

| Feature | Description |
|---------|-------------|
| **Microcontroller** | ATtiny85 - 8KB Flash, 512B RAM, 8-pin DIP |
| **Temperature Range** | -40°C to +125°C (sensor capability) |
| **Color Zones** | 5 distinct colors for different temp ranges |
| **Power Source** | 3V coin cell (CR2032) with on/off switch |
| **Current Draw** | ~20mA active, <1µA sleep mode |
| **Battery Life** | 10+ hours continuous (220mAh battery) |
| **Update Rate** | 1 second per reading |
| **Accuracy** | ±2°C (TMP36 typical) |

---

## 🧰 Components Required

### Essential Components:

| Component | Specification | Quantity | Purpose |
|-----------|--------------|----------|---------|
| **ATtiny85** | 8-pin DIP, 8KB Flash | 1 | Main microcontroller |
| **TMP36** | Analog temperature sensor | 1 | Temperature sensing |
| **RGB LED** | Common Cathode, 5mm | 1 | Visual color output |
| **Resistors** | 220Ω, 1/4W | 3 | Current limiting (R, G, B) |
| **Coin Cell Battery** | CR2032, 3V, 220mAh | 1 | Power source |
| **Battery Holder** | CR2032 compatible | 1 | Battery mounting |
| **DIP Switch** | SPST, 2-position | 1 | Power on/off control |
| **Capacitor** | 0.1µF ceramic | 1 | Power supply filtering |
| **Breadboard** | Half-size | 1 | Prototyping (optional) |
| **Jumper Wires** | Male-to-Male | 10 | Connections |

### Optional Components:

- **ATtiny85 Programmer** (USBtinyISP or Arduino as ISP)
- **8-pin DIP Socket** (for easy removal)
- **PCB** (for permanent installation)
- **Enclosure** (for protection)

### Total Cost Estimate: ~$8-12 USD

---

## 🔬 ATtiny85 Architecture

### Why ATtiny85?

The **ATtiny85** is a powerful yet tiny microcontroller from the AVR family, perfect for low-power, space-constrained projects.

```
ATtiny85 Features:
┌──────────────────────────────────────┐
│ • 8KB Flash Memory (program storage) │
│ • 512 Bytes SRAM (variables)         │
│ • 512 Bytes EEPROM (data storage)    │
│ • 6 I/O Pins (2 reserved for power)  │
│ • 4 PWM Channels (for RGB dimming)   │
│ • 10-bit ADC (for temperature)       │
│ • 8 MHz Internal Oscillator          │
│ • Operating Voltage: 2.7V - 5.5V     │
│ • Power Consumption: ~8mA @ 8MHz     │
│ • Sleep Mode: <1µA                   │
└──────────────────────────────────────┘
```

### ATtiny85 Pinout:

```
ATtiny85 DIP-8 Package:
        ┌────────┐
  RESET │1  ●  8│ VCC (+3V)
   PB3  │2     7│ PB2 (A1) ← TMP36 (Analog Input)
   PB4  │3     6│ PB1 ← GREEN LED (PWM)
   GND  │4     5│ PB0 ← RED LED (PWM)
        └────────┘
                   ↑
              BLUE LED (PWM)

Pin Functions:
  Pin 1: RESET (keep HIGH, pull-up)
  Pin 2: PB3 (Digital I/O, not used here)
  Pin 3: PB4 (PWM) → BLUE LED
  Pin 4: GND (Ground)
  Pin 5: PB0 (PWM) → RED LED
  Pin 6: PB1 (PWM) → GREEN LED
  Pin 7: PB2/A1 (ADC) → TMP36 Vout
  Pin 8: VCC (+3V Power)
```

### ATtiny85 vs Arduino UNO:

| Feature | ATtiny85 | Arduino UNO |
|---------|----------|-------------|
| Flash | 8 KB | 32 KB |
| RAM | 512 B | 2 KB |
| Digital Pins | 6 | 14 |
| Analog Pins | 4 (shared) | 6 |
| PWM Pins | 4 | 6 |
| Size | 8-pin DIP | 28-pin DIP |
| Power | ~8 mA | ~45 mA |
| Cost | ~$1 | ~$20 |
| **Best For** | **Portable, low-power** | **Complex, prototyping** |

---

## 🌡️ TMP36 Temperature Sensor

### TMP36 Overview:

The **TMP36** is a precision analog temperature sensor with a **linear voltage output** proportional to temperature.

```
TMP36 Features:
┌────────────────────────────────────┐
│ • Voltage Output: 10mV/°C          │
│ • Range: -40°C to +125°C           │
│ • Accuracy: ±2°C (typical)         │
│ • Supply Voltage: 2.7V - 5.5V      │
│ • Current Draw: <50µA              │
│ • No Calibration Required          │
│ • Linear + 500mV Offset            │
└────────────────────────────────────┘
```

### TMP36 Pinout (TO-92 Package):

```
Front View (Flat Side):
      ┌───────┐
      │ TMP36 │
      │       │
      │ _____ │
      └───────┘
       │  │  │
       1  2  3
       │  │  │
       │  │  └─── GND (Ground)
       │  └────── Vout (to ATtiny A1)
       └───────── VCC (+3V)

Pin Configuration:
  Pin 1: VCC (+3V from battery)
  Pin 2: Vout (Analog voltage to A1)
  Pin 3: GND (Common ground)
```

### Voltage-to-Temperature Formula:

The TMP36 outputs voltage according to:

$$
V_{out} = (T_{°C} \times 10mV) + 500mV
$$

To convert voltage back to temperature:

$$
T_{°C} = \frac{V_{out} - 500mV}{10mV/°C}
$$

$$
T_{°C} = (V_{out} - 0.5V) \times 100
$$

### Example Calculations:

| Temperature | TMP36 Output Voltage | ADC Reading (3V ref) |
|-------------|---------------------|---------------------|
| -40°C | 100 mV | ~34 (0.1V) |
| -20°C | 300 mV | ~102 (0.3V) |
| 0°C | 500 mV | ~170 (0.5V) |
| 25°C | 750 mV | ~256 (0.75V) |
| 50°C | 1000 mV | ~341 (1.0V) |
| 100°C | 1500 mV | ~512 (1.5V) |
| 125°C | 1750 mV | ~597 (1.75V) |

### 3V Reference ADC Conversion:

With ATtiny85 running on **3V**, the ADC conversion is:

$$
V_{out} = \frac{ADC_{raw}}{1023} \times 3.0V
$$

**Important Note**: With 3V supply, TMP36 can only measure up to **~80°C** before voltage exceeds VCC!

```
Maximum measurable temperature (3V system):
  Vout_max = 3.0V (cannot exceed VCC)
  Temp_max = (3.0 - 0.5) × 100 = 250°C (theoretical)
  
But TMP36 output maxes at VCC - 0.2V ≈ 2.8V:
  Temp_max_actual = (2.8 - 0.5) × 100 = 230°C
  
However, TMP36 absolute max = +125°C (datasheet)
```

---

## 🎨 RGB LED Color Theory

### Common Cathode RGB LED:

```
RGB LED Structure:
    ┌──────────────┐
    │   Red Die    │──── R (anode)
    │  Green Die   │──── G (anode)
    │   Blue Die   │──── B (anode)
    │              │
    │ Common (─)   │──── Cathode (GND)
    └──────────────┘

Pinout (5mm RGB LED):
     Longest pin = Common Cathode
     
  R    GND    G    B
  │     │     │    │
  ●     ●     ●    ●
        ↑
    Longest (cathode to GND)

Current Limiting:
  ATtiny85 → 220Ω → LED anode
  LED cathode → GND
```

### Color Mixing with PWM:

```
PWM (Pulse Width Modulation):
  analogWrite(pin, 0)   → 0% duty → OFF
  analogWrite(pin, 128) → 50% duty → HALF
  analogWrite(pin, 255) → 100% duty → FULL

RGB Color Examples:
┌─────────────┬─────┬───────┬──────┬────────────┐
│ Color       │ Red │ Green │ Blue │ Hex Code   │
├─────────────┼─────┼───────┼──────┼────────────┤
│ Red         │ 255 │   0   │   0  │ #FF0000    │
│ Green       │  0  │  255  │   0  │ #00FF00    │
│ Blue        │  0  │   0   │  255 │ #0000FF    │
│ Yellow      │ 255 │  255  │   0  │ #FFFF00    │
│ Cyan        │  0  │  255  │  255 │ #00FFFF    │
│ Magenta     │ 255 │   0   │  255 │ #FF00FF    │
│ White       │ 255 │  255  │  255 │ #FFFFFF    │
│ Orange      │ 255 │  165  │   0  │ #FFA500    │
│ Purple      │ 128 │   0   │  128 │ #800080    │
└─────────────┴─────┴───────┴──────┴────────────┘
```

### Color Psychology for Temperature:

```
Human Color Association:
  🔵 Blue → Cold, Ice, Winter
  🟢 Green → Comfortable, Normal, Safe
  🟠 Orange → Warm, Caution
  🔴 Red → Hot, Danger, Alert

This project uses intuitive color mapping!
```

---

## 🌈 Temperature Color Zones

This project divides temperature into **5 distinct zones**, each with a unique color:

### Zone Table:

```
┌──────┬─────────────────┬───────────┬──────────────┬─────────────────┐
│ Zone │ Temperature     │ Color     │ RGB Values   │ Meaning         │
├──────┼─────────────────┼───────────┼──────────────┼─────────────────┤
│  1   │ ≤ -20°C         │ 🔵 Blue   │ (0, 0, 255)  │ Deep Freeze     │
│  2   │ -20°C to 10°C   │ 🩵 Cyan   │ (0, 255, 255)│ Cold/Cool       │
│  3   │ 10°C to 35°C    │ 🟢 Green  │ (0, 255, 0)  │ Comfortable     │
│  4   │ 35°C to 60°C    │ 🟠 Orange │ (255, 165, 0)│ Warm/Caution    │
│  5   │ > 60°C          │ 🔴 Red    │ (255, 0, 0)  │ Hot/Danger      │
└──────┴─────────────────┴───────────┴──────────────┴─────────────────┘
```

### Visual Temperature Scale:

```
Temperature Line:
-40°C    -20°C     0°C     10°C    25°C    35°C    60°C   100°C
  │        │        │        │       │       │       │       │
  ├────────┼────────┼────────┼───────┼───────┼───────┼───────┤
  │  BLUE  │  CYAN  │ CYAN   │ GREEN │ GREEN │ORANGE │  RED  │
  │ Zone 1 │ Zone 2 │ Zone 2 │ Zone 3│ Zone 3│ Zone 4│ Zone 5│
  └────────┴────────┴────────┴───────┴───────┴───────┴───────┘
   Freezer  Winter    Fridge   Room   Body    Fever    Boil
```

### Practical Applications by Zone:

| Zone | Color | Temperature | Real-World Example |
|------|-------|-------------|-------------------|
| 1 | 🔵 Blue | ≤ -20°C | Deep freezer, Antarctica |
| 2 | 🩵 Cyan | -20°C to 10°C | Refrigerator, cold room |
| 3 | 🟢 Green | 10°C to 35°C | Room temperature, comfort zone |
| 4 | 🟠 Orange | 35°C to 60°C | Hot weather, fever, warm engine |
| 5 | 🔴 Red | > 60°C | Boiling water, engine overheating |

### Code Logic:

```cpp
if (temperature <= -20) {
  // Zone 1: Blue
  setColor(0, 0, 255);
}
else if (temperature > -20 && temperature <= 10) {
  // Zone 2: Cyan
  setColor(0, 255, 255);
}
else if (temperature > 10 && temperature <= 35) {
  // Zone 3: Green
  setColor(0, 255, 0);
}
else if (temperature > 35 && temperature <= 60) {
  // Zone 4: Orange
  setColor(255, 165, 0);
}
else {
  // Zone 5: Red (> 60°C)
  setColor(255, 0, 0);
}
```

---

## 🔌 Circuit Diagram

### Complete Circuit:

```
3V Coin Cell Battery Circuit:
┌─────────────────────────────────────────────────────────┐
│                                                         │
│  ┌──────┐  DIP Switch                                  │
│  │ CR   │    ┌────┐                                     │
│  │2032  │────┤ SW ├─────┬──────────────────────┬───────┤
│  │ 3V   │    └────┘     │                      │       │
│  └──────┘               │                      │       │
│    220mAh              VCC                    VCC     VCC
│                         │                      │       │
│                    ┌────┴────┐            ┌────┴────┐  │
│                    │  0.1µF  │            │  TMP36  │  │
│                    │   CAP   │            │  Sensor │  │
│                    └────┬────┘            │         │  │
│                         │              ┌──┤1  Vcc   │  │
│                        GND             │  │         │  │
│                                        │  │2  Vout  ├──┼──→ A1 (Pin 7)
│                                        │  │         │  │
│                                        │  │3  GND   ├──┼──→ GND
│         ATtiny85                       │  └─────────┘  │
│      ┌────────┐                        │               │
│      │1  ●  8│────────────────────────┘               │
│ NC ──┤2     7│────────────────────────────────────────┘
│      │        │ (PB2/A1: TMP36 input)
│      │3     6│──┐
│ BLUE │        │  │ GREEN
│  LED │4     5│──┼─────────┐
│      └────┬───┘  │         │ RED LED
│           │      │         │
│          GND     │         │
│           │      │         │
│           ├──────┼─────────┼───────────────────────────┤
│           │      │         │                           │
│           │      │         │                           │
│         ┌─┴─┐  ┌─┴─┐     ┌─┴─┐                         │
│         │220│  │220│     │220│ (Current limiting)      │
│         │Ω  │  │Ω  │     │Ω  │                         │
│         └─┬─┘  └─┬─┘     └─┬─┘                         │
│           │      │         │                           │
│         ┌─┴──────┴─────────┴─┐                         │
│         │    RGB LED          │                         │
│         │  (Common Cathode)   │                         │
│         │                     │                         │
│         │  B    GND   G    R  │                         │
│         │  │     │    │    │  │                         │
│         └──┼─────┼────┼────┼──┘                         │
│            │     │    │    │                            │
│      PB4 ──┘     │    │    └── PB0                      │
│            │     │    │                                 │
│      Pin 3 ──────┘    └─────── PB1                      │
│                                                          │
│                       Pin 6                              │
│                                                          │
│            All GND pins connected together              │
└─────────────────────────────────────────────────────────┘
```

### Breadboard Layout:

```
Breadboard View:
┌─────────────────────────────────────────────┐
│     Battery Holder                          │
│        (+) (─)                              │
│         │   │                               │
│         │   └─────┐                         │
│         │         │                         │
│       ┌─┴─┐       │                         │
│       │ S │ DIP   │                         │
│       │ W │Switch │                         │
│       └─┬─┘       │                         │
│         │         │                         │
│    ═════╬═════════╬═════════════════════    │
│    ─────┼─────────┼─────────────────────    │ Power Rails
│         │         │                         │
│    ═════╬═════════╬═════════════════════    │
│         │         │                         │
│      [ATtiny85]   │   [TMP36]   [RGB]       │
│         DIP       │    TO-92    LED         │
│                   │                         │
│    ═════════════════════════════════════    │
│    ─────────────────────────────────────    │ GND Rails
└─────────────────────────────────────────────┘
```

---

## 📍 Pin Configuration

### Complete Pin Mapping:

| ATtiny85 | Physical Pin | Function | Connected To | Signal Type |
|----------|-------------|----------|--------------|-------------|
| **RESET** | Pin 1 | Reset (pull-up) | Not Connected | Digital |
| **PB3** | Pin 2 | GPIO | Not Used | - |
| **PB4** | Pin 3 | PWM Output | Blue LED (via 220Ω) | PWM (OC1B) |
| **GND** | Pin 4 | Ground | Common GND | Power |
| **PB0** | Pin 5 | PWM Output | Red LED (via 220Ω) | PWM (OC0A) |
| **PB1** | Pin 6 | PWM Output | Green LED (via 220Ω) | PWM (OC0B) |
| **PB2 (A1)** | Pin 7 | ADC Input | TMP36 Vout | Analog |
| **VCC** | Pin 8 | Power | +3V (via switch) | Power |

### Arduino Pin Names vs ATtiny85:

```
Arduino IDE Code    ATtiny85 Physical    Function
─────────────────────────────────────────────────
analogRead(A1)  →   Pin 7 (PB2/ADC1)  →  TMP36
analogWrite(0)  →   Pin 5 (PB0)       →  Red LED
analogWrite(1)  →   Pin 6 (PB1)       →  Green LED
analogWrite(4)  →   Pin 3 (PB4)       →  Blue LED
```

### PWM Capability:

| Pin | PWM Timer | Frequency | Used For |
|-----|-----------|-----------|----------|
| PB0 | Timer0 (OC0A) | ~490 Hz | Red LED |
| PB1 | Timer0 (OC0B) | ~490 Hz | Green LED |
| PB4 | Timer1 (OC1B) | ~490 Hz | Blue LED |

**Note**: PWM frequency is set by timer prescaler (default: 64).

---

## ⚙️ Working Principle

### System Flow:

```
┌─────────────────────────────────────────────────────┐
│                   SYSTEM FLOW                       │
└─────────────────────────────────────────────────────┘
                         │
                    Power ON
                         │
                         ▼
              ┌──────────────────┐
              │   ATtiny85 Boot  │
              │  • Setup pins    │
              │  • Init ADC      │
              └─────────┬────────┘
                        │
                        ▼
              ┌──────────────────┐
              │  Read TMP36      │ ◄─────────┐
              │  • ADC on A1     │           │
              │  • Get raw value │           │
              └─────────┬────────┘           │
                        │                    │
                        ▼                    │
              ┌──────────────────┐           │
              │ Convert to Temp  │           │
              │ • Voltage calc   │           │
              │ • Apply formula  │           │
              └─────────┬────────┘           │
                        │                    │
                        ▼                    │
              ┌──────────────────┐           │
              │ Determine Zone   │           │
              │ • Check ranges   │           │
              │ • Select color   │           │
              └─────────┬────────┘           │
                        │                    │
                        ▼                    │
              ┌──────────────────┐           │
              │  Set RGB Color   │           │
              │  • PWM Red pin   │           │
              │  • PWM Green pin │           │
              │  • PWM Blue pin  │           │
              └─────────┬────────┘           │
                        │                    │
                        ▼                    │
              ┌──────────────────┐           │
              │   Delay 1 sec    │           │
              └─────────┬────────┘           │
                        │                    │
                        └────────────────────┘
                    (Infinite Loop)
```

### Step-by-Step Operation:

#### Step 1: ADC Reading

```cpp
int raw = analogRead(tempPin);
// ATtiny85 reads 10-bit ADC: 0-1023
// Example: raw = 256 (for ~25°C)
```

#### Step 2: Voltage Conversion

```cpp
float voltage = raw * (3.0 / 1023.0);
// voltage = 256 * 0.00293 = 0.75V
```

#### Step 3: Temperature Calculation

```cpp
float temperature = (voltage - 0.5) * 100.0;
// temperature = (0.75 - 0.5) * 100 = 25°C
```

#### Step 4: Zone Detection

```cpp
if (temperature <= -20)        → Zone 1: Blue
else if (temperature <= 10)    → Zone 2: Cyan
else if (temperature <= 35)    → Zone 3: Green
else if (temperature <= 60)    → Zone 4: Orange
else                           → Zone 5: Red
```

#### Step 5: Color Output

```cpp
void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);      // PWM duty: 0-255
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
```

---

## 💻 Code Explanation

### Complete Code:

```cpp
/*
 * ATtiny85 Temperature Indicator with RGB LED
 * 5 Color Zones for Temperature Ranges
 * Powered by 3V Coin Cell Battery
 */

// Pin Definitions
const int redPin = 0;      // PB0 (Pin 5) - Red LED
const int greenPin = 1;    // PB1 (Pin 6) - Green LED
const int bluePin = 4;     // PB4 (Pin 3) - Blue LED
const int tempPin = A1;    // PB2 (Pin 7) - TMP36 Vout

void setup() {
  // Configure RGB pins as OUTPUT
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  // TMP36 pin is INPUT by default (ADC)
  // No need to set pinMode for analog pins
}

void loop() {
  // Step 1: Read raw ADC value (0-1023)
  int raw = analogRead(tempPin);
  
  // Step 2: Convert ADC to voltage (3V reference)
  float voltage = raw * (3.0 / 1023.0);
  
  // Step 3: Convert voltage to temperature (Celsius)
  // TMP36 formula: T = (Vout - 0.5V) × 100
  float temperature = (voltage - 0.5) * 100.0;
  
  // Step 4: Determine color zone and set RGB
  if (temperature <= -20) {
    // Zone 1: Deep Freeze (≤ -20°C)
    setColor(0, 0, 255);  // Blue
  }
  else if (temperature > -20 && temperature <= 10) {
    // Zone 2: Cold/Cool (-20°C to 10°C)
    setColor(0, 255, 255);  // Cyan
  }
  else if (temperature > 10 && temperature <= 35) {
    // Zone 3: Comfortable (10°C to 35°C)
    setColor(0, 255, 0);  // Green
  }
  else if (temperature > 35 && temperature <= 60) {
    // Zone 4: Warm/Caution (35°C to 60°C)
    setColor(255, 165, 0);  // Orange
  }
  else {
    // Zone 5: Hot/Danger (> 60°C)
    setColor(255, 0, 0);  // Red
  }
  
  // Step 5: Wait 1 second before next reading
  delay(1000);
}

// Function to set RGB LED color
void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
```

### Code Breakdown:

#### Pin Definitions:

```cpp
const int redPin = 0;      // Arduino pin 0 = ATtiny85 PB0
const int greenPin = 1;    // Arduino pin 1 = ATtiny85 PB1
const int bluePin = 4;     // Arduino pin 4 = ATtiny85 PB4
const int tempPin = A1;    // Analog input A1 = ATtiny85 PB2
```

#### Setup Function:

```cpp
void setup() {
  pinMode(redPin, OUTPUT);    // Red LED can do PWM
  pinMode(greenPin, OUTPUT);  // Green LED can do PWM
  pinMode(bluePin, OUTPUT);   // Blue LED can do PWM
  
  // tempPin (A1) is ADC input
  // Default mode is INPUT, no pinMode needed
}
```

#### ADC Reading:

```cpp
int raw = analogRead(tempPin);
```

**What happens internally:**

1. ATtiny85 connects A1 to 10-bit ADC
2. ADC reference = VCC (3.0V)
3. Conversion time: ~100 µs
4. Returns value: 0 (0V) to 1023 (3V)

#### Voltage Calculation:

```cpp
float voltage = raw * (3.0 / 1023.0);
```

**Mathematical explanation:**

$$
V_{out} = \frac{ADC_{raw}}{ADC_{max}} \times V_{ref}
$$

$$
V_{out} = \frac{ADC_{raw}}{1023} \times 3.0V
$$

**Example:**
- If `raw = 341` (at 50°C):
- `voltage = 341 × 0.00293 = 1.0V`

#### Temperature Conversion:

```cpp
float temperature = (voltage - 0.5) * 100.0;
```

**TMP36 formula derivation:**

$$
V_{out} = T_{°C} \times 0.01 + 0.5
$$

Solving for temperature:

$$
T_{°C} = \frac{V_{out} - 0.5}{0.01} = (V_{out} - 0.5) \times 100
$$

**Example:**
- `voltage = 1.0V`
- `temperature = (1.0 - 0.5) × 100 = 50°C`

#### Zone Detection Logic:

```cpp
if (temperature <= -20) {
  setColor(0, 0, 255);  // Blue: RGB(0, 0, 255)
}
```

**Condition breakdown:**

```
Temperature Check Flow:
  Is temp ≤ -20?     → YES: Blue (Zone 1)
                     → NO: Continue
  Is temp ≤ 10?      → YES: Cyan (Zone 2)
                     → NO: Continue
  Is temp ≤ 35?      → YES: Green (Zone 3)
                     → NO: Continue
  Is temp ≤ 60?      → YES: Orange (Zone 4)
                     → NO: Red (Zone 5)
```

#### PWM Color Setting:

```cpp
void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);      // Set red brightness (0-255)
  analogWrite(greenPin, green);  // Set green brightness (0-255)
  analogWrite(bluePin, blue);    // Set blue brightness (0-255)
}
```

**analogWrite() explanation:**

```
analogWrite(pin, value):
  • value = 0: LED OFF (0% duty cycle)
  • value = 128: LED HALF (50% duty cycle)
  • value = 255: LED FULL (100% duty cycle)

PWM Frequency: ~490 Hz (fast enough for human eye)

Example: setColor(255, 165, 0) → Orange
  Red: 100% ON
  Green: 65% ON (165/255 = 0.647)
  Blue: 0% OFF
  Result: Orange color
```

---

## 🔋 Power Management

### Battery Specifications:

```
CR2032 Coin Cell:
┌───────────────────────────────┐
│ Voltage: 3.0V (nominal)       │
│ Capacity: 220 mAh             │
│ Chemistry: Lithium            │
│ Discharge: Stable voltage     │
│ Shelf Life: 10 years          │
│ Cost: ~$1 each                │
└───────────────────────────────┘
```

### Current Consumption Analysis:

| Component | Current Draw | Notes |
|-----------|-------------|-------|
| ATtiny85 (active) | ~8 mA | @ 8 MHz internal clock |
| TMP36 sensor | ~50 µA | Negligible |
| RGB LED (1 color) | ~10 mA | One channel at 255 |
| RGB LED (all 3) | ~30 mA | All channels at 255 |
| **Total (typical)** | **~20 mA** | One or two colors active |

### Battery Life Calculation:

$$
Battery Life = \frac{Battery Capacity}{Current Draw}
$$

$$
Battery Life = \frac{220 mAh}{20 mA} = 11 hours
$$

```
Operating Scenarios:
┌────────────────────┬──────────┬───────────────┐
│ Scenario           │ Current  │ Battery Life  │
├────────────────────┼──────────┼───────────────┤
│ Typical operation  │ 20 mA    │ ~11 hours     │
│ All LEDs full      │ 38 mA    │ ~6 hours      │
│ Single LED         │ 18 mA    │ ~12 hours     │
│ With sleep mode    │ ~1 mA    │ ~220 hours    │
└────────────────────┴──────────┴───────────────┘
```

### Power Optimization Tips:

1. **Reduce LED brightness** (50% = half current):
```cpp
void setColor(int red, int green, int blue) {
  // Dim to 50% to save power
  analogWrite(redPin, red / 2);
  analogWrite(greenPin, green / 2);
  analogWrite(bluePin, blue / 2);
}
```

2. **Sleep mode between readings**:
```cpp
#include <avr/sleep.h>
#include <avr/power.h>

void enterSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();  // Sleep here
  sleep_disable();
}

void loop() {
  // Read and display temperature
  // ...
  
  delay(900);      // Awake for 100ms
  enterSleep();    // Sleep for 900ms
}
// Battery life: 10x longer!
```

3. **Lower clock speed** (4 MHz instead of 8 MHz):
```cpp
// In setup():
CLKPR = (1 << CLKPCE);  // Enable clock prescaler change
CLKPR = (1 << CLKPS0);  // Divide by 2 → 4 MHz
// Current: ~4 mA (half of 8 MHz)
```

---

## 🔧 Calibration Guide

### Why Calibration?

- TMP36 tolerance: ±2°C
- ATtiny85 ADC errors
- 3V battery voltage drift
- Resistor tolerances

### Calibration Methods:

#### Method 1: Software Offset

```cpp
// Add calibration offset
float temperature = (voltage - 0.5) * 100.0;
temperature += CALIBRATION_OFFSET;  // e.g., -2.5°C

// At top of code:
#define CALIBRATION_OFFSET -2.5  // Adjust as needed
```

#### Method 2: Reference Thermometer

```
Steps:
1. Place your device and a reference thermometer together
2. Wait 5 minutes for thermal equilibrium
3. Note both temperatures:
   - Reference: 25.0°C
   - Your device: 27.5°C
   - Offset: 27.5 - 25.0 = +2.5°C
4. Subtract offset: temperature -= 2.5;
```

#### Method 3: Two-Point Calibration

```cpp
// Measure at two known temperatures
// Ice water (0°C) and boiling water (100°C)

float calibrate(float rawTemp) {
  // Measured: 0°C reads as 2°C, 100°C reads as 98°C
  // Linear correction:
  float slope = (100.0 - 0.0) / (98.0 - 2.0);  // = 1.0417
  float intercept = 0.0 - (2.0 * slope);       // = -2.08
  return (rawTemp * slope) + intercept;
}
```

### Testing Color Zones:

```cpp
// Simulate temperatures to test colors
void testColors() {
  float testTemps[] = {-30, -10, 5, 20, 30, 40, 70};
  
  for (int i = 0; i < 7; i++) {
    float temperature = testTemps[i];
    
    // Apply zone logic
    if (temperature <= -20) setColor(0, 0, 255);
    else if (temperature <= 10) setColor(0, 255, 255);
    else if (temperature <= 35) setColor(0, 255, 0);
    else if (temperature <= 60) setColor(255, 165, 0);
    else setColor(255, 0, 0);
    
    delay(2000);  // 2 seconds per color
  }
}
```

---

## 🐛 Troubleshooting

### Common Issues:

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| **No LED light** | Dead battery | Replace CR2032, check switch |
| | Wrong LED type | Verify common cathode RGB |
| | Missing resistors | Add 220Ω to each LED leg |
| **Wrong colors** | Pin mapping error | Check redPin/greenPin/bluePin |
| | Code upload error | Re-upload with correct board |
| **LED always red** | TMP36 disconnected | Check Vout to A1 connection |
| | Overheating sensor | Let sensor cool down |
| **Flickering** | Loose wires | Secure all connections |
| | Low battery | Battery < 2.7V, replace |
| **No color change** | Sensor reading wrong | Check TMP36 pinout (VCC/Vout/GND) |
| | Formula error | Verify 3V reference in code |
| **Blue tint always on** | Common anode LED | Use common cathode type |

### Diagnostic Code:

```cpp
// Add to loop() for debugging
void debugTemperature() {
  int raw = analogRead(tempPin);
  float voltage = raw * (3.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100.0;
  
  // Blink LED to show temperature (1 blink = 10°C)
  int blinks = temperature / 10;
  for (int i = 0; i < blinks; i++) {
    setColor(255, 255, 255);  // White flash
    delay(200);
    setColor(0, 0, 0);        // Off
    delay(200);
  }
  delay(2000);
}
```

### TMP36 Pin Test:

```
Use multimeter (voltage mode):
  Pin 1 (VCC): Should read ~3.0V
  Pin 2 (Vout): Should read 0.5V - 2.5V (temp dependent)
  Pin 3 (GND): Should read 0V

If Pin 2 reads 3V or 0V constantly:
  → TMP36 is damaged or wired backwards
```

---

## 🚀 Applications

### 1. Wearable Body Temperature Monitor

```
Features:
  • Attach to clothing/wristband
  • Green = normal (36.5-37.5°C)
  • Orange/Red = fever alert
  • Cyan = hypothermia warning
```

### 2. Refrigerator/Freezer Alarm

```
Features:
  • Mount inside fridge
  • Blue = proper freezing (<-18°C)
  • Cyan = refrigerator range (2-8°C)
  • Green/Orange = door open too long
```

### 3. CPU/Electronics Cooling Monitor

```
Features:
  • Attach to heatsink
  • Green = cool (<40°C)
  • Orange = warm (40-70°C)
  • Red = overheating (>70°C)
```

### 4. Baby Room Temperature Indicator

```
Features:
  • Safe range: 18-22°C (Green/Cyan)
  • Too cold: Blue
  • Too hot: Orange/Red
  • Silent visual feedback
```

### 5. Greenhouse Climate Control

```
Features:
  • Optimal: 20-30°C (Green)
  • Too cold: Cyan/Blue (add heat)
  • Too hot: Orange/Red (add ventilation)
```

---

## 📚 Learning Outcomes

### Skills Gained:

```
✅ ATtiny85 microcontroller programming
✅ Low-power embedded system design
✅ Analog sensor interfacing (TMP36)
✅ ADC (Analog-to-Digital Conversion)
✅ PWM for RGB LED control
✅ Color mixing and color theory
✅ Battery-powered circuit design
✅ Voltage reference calculations
✅ Temperature sensing principles
✅ Conditional logic and zones
✅ 3V system design constraints
```

### Advanced Concepts:

- **Voltage Dividers**: TMP36 output impedance
- **PWM Duty Cycle**: analogWrite() implementation
- **ADC Resolution**: 10-bit (0-1023) vs real-world voltage
- **Reference Voltage**: Using VCC vs external AREF
- **Thermal Equilibrium**: Sensor response time (~30s)
- **Power Budgeting**: Current draw analysis

---

## 🎯 Project Challenges

### Challenge 1: Add Fahrenheit Mode

```cpp
// Add button to switch between °C and °F
bool isFahrenheit = false;

float toFahrenheit(float celsius) {
  return (celsius * 9.0 / 5.0) + 32.0;
}

// Different color zones for Fahrenheit:
// Zone 1: ≤ -4°F (Blue)
// Zone 2: -4°F to 50°F (Cyan)
// Zone 3: 50°F to 95°F (Green)
// Zone 4: 95°F to 140°F (Orange)
// Zone 5: > 140°F (Red)
```

### Challenge 2: Add Sleep Mode

```cpp
#include <avr/sleep.h>

// Read every 10 seconds, sleep in between
// Battery life: 20x longer!
```

### Challenge 3: Add Smooth Color Transitions

```cpp
// Instead of instant color changes,
// gradually fade between colors using PWM
void fadeToColor(int targetR, int targetG, int targetB) {
  // Implement smooth fade over 1 second
}
```

### Challenge 4: EEPROM Data Logging

```cpp
#include <EEPROM.h>

// Store min/max temperatures in EEPROM
// Blink LED in patterns to display history
```

---

## 📖 References

- [ATtiny85 Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf)
- [TMP36 Datasheet](https://www.analog.com/media/en/technical-documentation/data-sheets/TMP35_36_37.pdf)
- [Arduino ATtiny Core](https://github.com/SpenceKonde/ATTinyCore)

---

## 👨‍💻 Author

**Md. Akhinoor Islam**  
📚 Energy Science and Engineering (ESE)  
🏫 Khulna University of Engineering & Technology (KUET)

---

## 📄 License

MIT License - Free to use, modify, and distribute!

---

### 🎉 Success Tips

1. **Test TMP36 first** - Verify correct pinout (VCC/Vout/GND)
2. **Use common cathode RGB** - Common anode won't work
3. **Check battery voltage** - Must be >2.7V for reliable operation
4. **Calibrate with reference** - Use ice water (0°C) for accuracy
5. **Secure connections** - Use breadboard firmly or solder
6. **Program before final assembly** - Easier to debug on breadboard

**Good luck building your portable temperature indicator! 🌡️🔵🟢🔴**
