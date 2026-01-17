# 💡 Light Intensity Measurement with LDR Sensor

![Arduino](https://img.shields.io/badge/Arduino-UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Sensor](https://img.shields.io/badge/Sensor-LDR-yellow?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Beginner-brightgreen?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Complete-success?style=for-the-badge)

A comprehensive Arduino project that measures ambient light intensity using an **LDR (Light Dependent Resistor)** sensor, displays real-time voltage readings on the Serial Monitor, and controls LED brightness proportionally to light levels using PWM.

---

## 📑 Table of Contents

- [Overview](#-overview)
- [Learning Objectives](#-learning-objectives)
- [Components Required](#-components-required)
- [LDR Sensor Theory](#-ldr-sensor-theory)
- [Voltage Divider Circuit](#-voltage-divider-circuit)
- [Circuit Diagram](#-circuit-diagram)
- [Circuit Connections](#-circuit-connections)
- [Code Explanation](#-code-explanation)
- [How It Works](#-how-it-works)
- [Serial Monitor Output](#-serial-monitor-output)
- [PWM LED Control](#-pwm-led-control)
- [Calibration & Testing](#-calibration--testing)
- [Troubleshooting](#-troubleshooting)
- [Real-World Applications](#-real-world-applications)
- [Project Extensions](#-project-extensions)
- [Challenges](#-challenges)
- [Author](#-author)

---

## 🎯 Overview

This project demonstrates how to use an **LDR (Light Dependent Resistor)** photoresistor to measure ambient light intensity. The Arduino reads the analog voltage from a voltage divider circuit, calculates the actual voltage, and provides visual feedback through a PWM-controlled LED whose brightness varies with light levels.

### Key Features:
- ✅ Real-time light intensity measurement
- ✅ Voltage divider circuit implementation
- ✅ ADC (Analog-to-Digital Conversion) demonstration
- ✅ PWM LED brightness control (proportional feedback)
- ✅ Serial Monitor voltage display
- ✅ Multimeter verification capability
- ✅ Foundation for automatic lighting systems

---

## 🎓 Learning Objectives

By completing this project, you will learn:

| Concept | Description | Practical Application |
|---------|-------------|----------------------|
| **LDR Operation** | Resistance varies with light intensity | Light sensors, photometry |
| **Voltage Divider** | Two resistors divide voltage proportionally | Sensor interfacing, signal conditioning |
| **ADC Conversion** | Converting analog signals to digital values | All analog sensor applications |
| **PWM Output** | Pulse Width Modulation for analog-like control | LED dimming, motor speed control |
| **Serial Communication** | Real-time data monitoring | Debugging, data logging |
| **Mapping Function** | Scale values between ranges | Range conversion, calibration |

---

## 🧰 Components Required

| Component | Quantity | Specifications | Purpose |
|-----------|----------|----------------|---------|
| Arduino UNO | 1 | ATmega328P, 5V logic | Microcontroller |
| LDR (Photoresistor) | 1 | 5-10kΩ @ 10 lux | Light sensing |
| LED | 1 | Any color, ~20mA | Visual feedback |
| 10kΩ Resistor | 1 | ±5% tolerance | Voltage divider (fixed) |
| 220Ω Resistor | 1 | ±5% tolerance | LED current limiting |
| Breadboard | 1 | 830 tie-points | Prototyping |
| Jumper Wires | ~15 | Male-to-Male | Connections |
| USB Cable | 1 | Type A to Type B | Programming & Power |
| Multimeter | 1 (optional) | DC voltage measurement | Verification |

### 💰 Estimated Cost: ৳400-600 ($5-7 USD)

---

## 🔬 LDR Sensor Theory

### What is an LDR?

An **LDR (Light Dependent Resistor)**, also called a **photoresistor** or **photocell**, is a passive resistive sensor whose resistance decreases as light intensity increases.

### LDR Construction:

```
LDR Cross-Section View
┌─────────────────────┐
│   Glass/Epoxy Case  │
│  ┌───────────────┐  │
│  │ Semiconductor │  │ ← Cadmium Sulfide (CdS)
│  │   Material    │  │   or similar photoresistive material
│  └───────────────┘  │
│        ╱╲           │
│    Lead  Lead       │
└─────────────────────┘
```

### LDR Characteristics:

| Parameter | Dark Condition | Bright Light | Notes |
|-----------|----------------|--------------|-------|
| Resistance | 1 MΩ - 10 MΩ | 100 Ω - 1 kΩ | Varies by model |
| Response Time | 10-100 ms | 10-100 ms | Slow compared to photodiodes |
| Spectral Peak | ~550 nm | (Green light) | Similar to human eye |
| Temperature Effect | ±0.5%/°C | Coefficient | Minimal for general use |
| Power Rating | 100-200 mW | Max dissipation | Avoid overheating |
| Linearity | Non-linear | Log relationship | Between light & resistance |

### Light vs Resistance Relationship:

```
Resistance (Ω)
1M  ├────────●                    Dark
    │         ╲
100k├          ╲
    │           ●                 Dim room
10k ├            ╲
    │             ╲
1k  ├              ●              Indoor light
    │               ╲
100 ├                ●────────    Bright sunlight
    │
    └────────────────────────
      0    500   1000  5000  10000
         Light Intensity (lux)

Relationship: R ∝ 1/Light^γ
Where γ ≈ 0.5 to 0.9 (depends on LDR type)
```

### LDR Symbol:

```
Standard Schematic Symbol:
    ┌─────┐
    │ ▒▒▒ │  ← Resistor
    └─────┘
      ↙ ↙    ← Arrows indicate light sensitivity
```

---

## ⚡ Voltage Divider Circuit

### Basic Voltage Divider Theory:

A voltage divider splits an input voltage into a smaller output voltage using two resistors in series:

```
Voltage Divider Circuit:
        +5V
         │
         ├──── Vin
         │
        ╱╲
       │  │  R1 (LDR - Variable)
       │  │
         │
         ├──── Vout (Node A) → to A0
         │
        ╱╲
       │  │  R2 (10kΩ - Fixed)
       │  │
         │
        GND

Formula:
  Vout = Vin × (R2 / (R1 + R2))
```

### Our Implementation:

**Configuration:**
- **R1** = LDR (variable, changes with light)
- **R2** = 10kΩ (fixed resistor)
- **Vin** = 5V (Arduino supply)
- **Vout** = Node A (connected to A0)

### Voltage Calculation Examples:

| Light Condition | LDR Resistance | R2 (Fixed) | Vout Calculation | Vout | ADC Value |
|-----------------|----------------|------------|------------------|------|-----------|
| **Darkness** | 1 MΩ | 10 kΩ | 5V × (10k/(1M+10k)) | ~0.05V | ~10 |
| **Dim Room** | 100 kΩ | 10 kΩ | 5V × (10k/(100k+10k)) | ~0.45V | ~92 |
| **Office Light** | 10 kΩ | 10 kΩ | 5V × (10k/(10k+10k)) | 2.5V | 512 |
| **Bright Light** | 1 kΩ | 10 kΩ | 5V × (10k/(1k+10k)) | ~4.55V | ~931 |

**Key Insight:**
- More light → Lower LDR resistance → Higher Vout
- Less light → Higher LDR resistance → Lower Vout

### Why 10kΩ for R2?

```
Choosing R2 value:
  - Too small (1kΩ): Limited voltage range, low sensitivity
  - Just right (10kΩ): Matches LDR mid-range, best sensitivity
  - Too large (1MΩ): Poor response, noise susceptible

Optimal R2 ≈ LDR resistance at target light level
For general use: 10kΩ is standard
```

---

## 📐 Circuit Diagram

### Complete Circuit Schematic:

```
Arduino UNO                          LDR & Voltage Divider
┌─────────────────┐                 ┌──────────────────┐
│                 │     +5V         │                  │
│   5V  ●─────────┼─────────────────┤● LDR             │
│                 │                 │  (Leg 1)         │
│                 │                 │                  │
│                 │                 │● LDR             │
│                 │     Node A      │  (Leg 2)         │
│   A0  ●─────────┼─────────────────┤●─────┐           │
│                 │                 │      │           │
│                 │                 │     ╱╲           │
│                 │                 │    │  │ 10kΩ     │
│                 │                 │    │  │          │
│                 │                 │     ╲╱           │
│                 │                 │      │           │
│  GND  ●─────────┼─────────────────┤──────┴───────────┤
│                 │                 └──────────────────┘
│                 │
│                 │                 LED Circuit
│                 │                 ┌──────────────────┐
│                 │                 │                  │
│   D9  ●─────────┼─────────────────┤● 220Ω Resistor   │
│       (PWM)     │     [220Ω]      │                  │
│                 │     [====]      │                  │
│                 │       │         │      LED         │
│                 │       ├─────────┤●  ──┬──  Anode  │
│                 │       │         │   ──┴──          │
│                 │       │         │     │   Cathode  │
│  GND  ●─────────┼───────┴─────────┤─────●            │
│                 │                 │                  │
└─────────────────┘                 └──────────────────┘

Note: Node A is the junction between LDR and 10kΩ resistor
```

### Physical Layout Diagram:

```
Breadboard Top View:
┌────────────────────────────────────────────┐
│  Arduino UNO                               │
│  ┌──────────┐                              │
│  │ D9  ●    │                              │
│  │ A0  ●    │                              │
│  │ 5V  ●    │                              │
│  │ GND ●    │                              │
│  └──────────┘                              │
│                                            │
│  Breadboard:                               │
│  ─────────────────────────────────────     │
│   + + + + + + + + + + (Power Rail +)       │
│   - - - - - - - - - - (Ground Rail -)      │
│                                            │
│   LDR:     ●───●                           │
│            │   │                           │
│   From 5V──┘   └──┬── Node A → A0         │
│                   │                        │
│               [10kΩ]                       │
│                   │                        │
│                  GND                       │
│                                            │
│   LED Circuit:                             │
│   D9 ─[220Ω]─ LED(+)─ LED(-)─ GND         │
│                                            │
└────────────────────────────────────────────┘
```

---

## 🔌 Circuit Connections

### Detailed Connection Table:

**LDR Voltage Divider:**

| Component | Terminal | Arduino Pin | Wire Color (suggested) |
|-----------|----------|-------------|------------------------|
| LDR | Leg 1 | 5V | Red |
| LDR | Leg 2 | Node A → A0 | Yellow |
| 10kΩ Resistor | Leg 1 | Node A (with LDR Leg 2) | - |
| 10kΩ Resistor | Leg 2 | GND | Black |

**LED Circuit:**

| Component | Terminal | Arduino Pin | Wire Color (suggested) |
|-----------|----------|-------------|------------------------|
| 220Ω Resistor | Leg 1 | D9 (PWM) | Orange |
| 220Ω Resistor | Leg 2 | LED Anode (+) | - |
| LED | Anode (+) | Via 220Ω from D9 | - |
| LED | Cathode (-) | GND | Black |

### Step-by-Step Wiring Guide:

```
Step 1: Power the LDR
  Arduino 5V → LDR Leg 1

Step 2: Create Node A (Voltage Divider Output)
  LDR Leg 2 → Node A (use breadboard row)
  Node A → Arduino A0

Step 3: Complete Voltage Divider
  Node A → 10kΩ Resistor Leg 1
  10kΩ Resistor Leg 2 → Arduino GND

Step 4: LED with Current Limiting
  Arduino D9 → 220Ω Resistor → LED Anode (+)
  LED Cathode (-) → Arduino GND

Step 5: Verify Connections
  ✓ LDR has +5V and goes to divider
  ✓ Node A connected to A0
  ✓ 10kΩ goes to GND
  ✓ LED has proper polarity
  ✓ All grounds common
```

### Important Notes:

⚠️ **LDR Polarity:** LDRs are non-polarized (no + or -), can be connected either way  
⚠️ **LED Polarity:** Connect anode (+, longer leg) toward D9, cathode (-, shorter leg) toward GND  
⚠️ **Node A:** Critical junction point - must connect to both 10kΩ resistor AND A0  
⚠️ **Common Ground:** All GND connections must be connected together  

---

## 💻 Code Explanation

### Complete Arduino Code:

```cpp
/*
 * Project 20: Light Intensity Measurement with LDR Sensor
 * Author: Md. Akhinoor Islam
 * Department: ESE (Energy Science and Engineering), KUET
 * Description: Measures ambient light intensity using LDR,
 *              displays voltage on Serial Monitor, and controls
 *              LED brightness via PWM proportional to light level.
 */

// Pin Definitions
const int ldrPin = A0;    // Analog input from voltage divider
const int ledPin = 9;     // PWM output to LED (D9 supports PWM)

void setup() {
  // Initialize LED pin as output
  pinMode(ledPin, OUTPUT);
  
  // Initialize Serial communication at 9600 baud
  Serial.begin(9600);
  
  // Startup message
  Serial.println("Light Intensity Measurement System");
  Serial.println("===================================");
  delay(1000);
}

void loop() {
  // Read analog value from LDR voltage divider (0-1023)
  int sensorValue = analogRead(ldrPin);
  
  // Convert ADC reading to actual voltage (0-5V)
  float voltage = sensorValue * (5.0 / 1023.0);
  
  // Map ADC reading to PWM range for LED brightness (0-255)
  int brightness = map(sensorValue, 0, 1023, 0, 255);
  
  // Set LED brightness using PWM
  analogWrite(ledPin, brightness);
  
  // Display voltage reading on Serial Monitor
  Serial.print("Light Voltage: ");
  Serial.print(voltage, 3);  // 3 decimal places
  Serial.print(" V | ADC: ");
  Serial.print(sensorValue);
  Serial.print(" | LED: ");
  Serial.print(brightness);
  Serial.println(" /255");
  
  // Update twice per second (500ms delay)
  delay(500);
}
```

---

### 📖 Line-by-Line Code Breakdown:

#### 1. Pin Definitions

```cpp
const int ldrPin = A0;
const int ledPin = 9;
```

**Explanation:**
- `const int` = constant integer (value won't change)
- `ldrPin = A0` = analog pin A0 for voltage divider input
- `ledPin = 9` = digital pin D9 with PWM capability

**Why A0?**
- Arduino UNO has 6 analog pins (A0-A5)
- A0 is conventionally first choice for single analog sensor
- All analog pins have 10-bit ADC (0-1023 resolution)

**Why D9 for LED?**
- D9 supports PWM (Pulse Width Modulation)
- Arduino UNO PWM pins: 3, 5, 6, 9, 10, 11 (marked with ~)
- PWM allows smooth brightness control

---

#### 2. Setup Function

```cpp
void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Light Intensity Measurement System");
  Serial.println("===================================");
  delay(1000);
}
```

**Breakdown:**

```cpp
pinMode(ledPin, OUTPUT);
```
- Configures D9 as OUTPUT
- Allows Arduino to send PWM signals to LED
- INPUT mode is default for analog pins (A0 doesn't need pinMode)

```cpp
Serial.begin(9600);
```
- Initializes serial communication at **9600 baud rate**
- Baud rate = bits per second
- 9600 is standard for Arduino (others: 115200, 57600)
- Must match Serial Monitor baud rate setting

```cpp
Serial.println("Light Intensity Measurement System");
```
- `println()` prints text followed by newline
- Startup message for user confirmation
- Helps identify program start in Serial Monitor

```cpp
delay(1000);
```
- Pauses for 1000ms (1 second)
- Allows time for startup message to be read
- Stabilizes before starting measurements

---

#### 3. Main Loop - Sensor Reading

```cpp
int sensorValue = analogRead(ldrPin);
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

**ADC (Analog-to-Digital Converter) Explanation:**

```
10-bit ADC Resolution:
  2^10 = 1024 possible values (0-1023)
  
  Voltage Range: 0V to 5V (Arduino reference voltage)
  
  Mapping:
    0 ADC → 0.000V
    512 ADC → 2.500V (approximately)
    1023 ADC → 5.000V

Example Readings:
  Dark Room (0.5V): ADC ≈ 102
  Office Light (2.5V): ADC ≈ 512
  Bright Light (4.5V): ADC ≈ 922
```

---

#### 4. Voltage Conversion

```cpp
float voltage = sensorValue * (5.0 / 1023.0);
```

**Formula Breakdown:**

```
Goal: Convert ADC reading (0-1023) to actual voltage (0-5V)

Formula: Voltage = (ADC / 1023) × Vref
Where: Vref = 5.0V (Arduino reference voltage)

Simplified: Voltage = ADC × (5.0 / 1023.0)

Why 1023 not 1024?
  - ADC counts from 0 to 1023 = 1024 total values
  - But 0 means 0V and 1023 means 5V
  - Dividing by 1023 gives correct voltage mapping

Example Calculations:
  sensorValue = 0
    voltage = 0 × (5.0/1023.0) = 0.000V
  
  sensorValue = 512
    voltage = 512 × (5.0/1023.0) = 2.502V
  
  sensorValue = 1023
    voltage = 1023 × (5.0/1023.0) = 5.000V
```

**Data Type: `float`**
- Float = floating-point number (decimal)
- Needed for fractional voltage values
- Arduino floats: 32-bit, ~6-7 significant digits

---

#### 5. Brightness Mapping

```cpp
int brightness = map(sensorValue, 0, 1023, 0, 255);
```

**Function: `map()`**

```
Syntax: map(value, fromLow, fromHigh, toLow, toHigh)

Purpose: Re-scale a number from one range to another

Our Usage:
  value: sensorValue (0-1023 from ADC)
  fromLow: 0 (minimum ADC)
  fromHigh: 1023 (maximum ADC)
  toLow: 0 (minimum PWM)
  toHigh: 255 (maximum PWM)

Mathematical Formula:
  output = (value - fromLow) × (toHigh - toLow) / (fromHigh - fromLow) + toLow
  
  brightness = (sensorValue - 0) × (255 - 0) / (1023 - 0) + 0
  brightness = sensorValue × 255 / 1023

Example Mappings:
  ADC 0 → PWM 0 (LED off)
  ADC 512 → PWM 128 (LED half brightness)
  ADC 1023 → PWM 255 (LED full brightness)
```

**Why Map to 0-255?**
- `analogWrite()` accepts values 0-255 (8-bit)
- 0 = 0% duty cycle (LED off)
- 255 = 100% duty cycle (LED full brightness)
- Values in between = proportional brightness

---

#### 6. PWM LED Control

```cpp
analogWrite(ledPin, brightness);
```

**Function: `analogWrite()`**

| Parameter | Description |
|-----------|-------------|
| **Pin** | ledPin (D9) - must be PWM-capable |
| **Value** | brightness (0-255) |
| **Effect** | Sets PWM duty cycle |

**PWM (Pulse Width Modulation) Explanation:**

```
PWM Concept:
  Rapidly toggles digital pin HIGH/LOW to simulate analog voltage
  
PWM Frequency on Arduino UNO:
  ~490 Hz (D9, D10)
  ~980 Hz (D3, D11)

Duty Cycle Examples:
  brightness = 0 (0%):
    ──────────────────────  (Always LOW)
    LED OFF
  
  brightness = 64 (25%):
    ──┐   ┐   ┐   ┐   ┐   ┐
      └───┘   └───┘   └───┘
    LED DIM
  
  brightness = 128 (50%):
    ──┐ ┐ ┐ ┐ ┐ ┐ ┐ ┐ ┐ ┐
      └─┘ └─┘ └─┘ └─┘ └─┘
    LED MEDIUM
  
  brightness = 255 (100%):
    ──────────────────────  (Always HIGH)
    LED FULL BRIGHTNESS

Human Eye Perception:
  - PWM too fast to see flicker (>60 Hz)
  - Perceives average brightness
  - Smooth dimming effect
```

---

#### 7. Serial Monitor Output

```cpp
Serial.print("Light Voltage: ");
Serial.print(voltage, 3);
Serial.print(" V | ADC: ");
Serial.print(sensorValue);
Serial.print(" | LED: ");
Serial.print(brightness);
Serial.println(" /255");
```

**Serial Print Functions:**

| Function | Behavior |
|----------|----------|
| `Serial.print()` | Print without newline |
| `Serial.println()` | Print with newline (moves to next line) |

**Format Specifiers:**

```cpp
Serial.print(voltage, 3);
```
- Second parameter `3` = number of decimal places
- `voltage = 2.502V` displays as "2.502"
- Without specifier: may show "2.50" (default 2 decimals)

**Sample Serial Monitor Output:**

```
Light Intensity Measurement System
===================================
Light Voltage: 0.488 V | ADC: 100 | LED: 25 /255
Light Voltage: 0.488 V | ADC: 100 | LED: 25 /255
Light Voltage: 2.456 V | ADC: 503 | LED: 125 /255
Light Voltage: 4.512 V | ADC: 924 | LED: 230 /255
Light Voltage: 4.756 V | ADC: 974 | LED: 243 /255
```

---

#### 8. Loop Delay

```cpp
delay(500);
```

**Purpose:**
- Wait 500 milliseconds (0.5 seconds)
- Updates display twice per second
- Prevents Serial Monitor flooding

**Why 500ms?**
- Fast enough for responsive feedback
- Slow enough to read comfortably
- Reduces power consumption
- Minimizes Serial buffer overflow

**Alternative Delays:**
```cpp
delay(100);   // 10 updates/sec - very responsive, scrolls fast
delay(500);   // 2 updates/sec - good balance (our choice)
delay(1000);  // 1 update/sec - slow but easy to read
```

---

## ⚙️ How It Works

### System Flow Diagram:

```
┌─────────────────────────────────────────┐
│  Arduino Powers Up                      │
└───────────────┬─────────────────────────┘
                ↓
┌─────────────────────────────────────────┐
│  setup() Executes Once                  │
│  - Configure D9 as OUTPUT               │
│  - Start Serial @ 9600 baud             │
│  - Display startup message              │
└───────────────┬─────────────────────────┘
                ↓
┌─────────────────────────────────────────┐
│  Main Loop Begins (Repeats Forever)     │
└───────────────┬─────────────────────────┘
                ↓
       ┌────────┴────────┐
       │                 │
       ↓                 ↓
┌──────────────┐   ┌─────────────┐
│ Read Sensor  │   │ Control LED │
│ (Analog A0)  │   │ (PWM D9)    │
└──────┬───────┘   └──────┬──────┘
       │                  │
       ↓                  ↓
ADC → Voltage      Map to PWM
(0-1023)           (0-255)
       │                  │
       ↓                  ↓
Calculate Voltage   Set Brightness
V = ADC × 5/1023    analogWrite()
       │                  │
       └────────┬─────────┘
                ↓
      ┌───────────────────┐
      │ Display on Serial │
      │ Voltage | ADC |   │
      │ LED Brightness    │
      └─────────┬─────────┘
                ↓
         Wait 500ms
                ↓
         Loop Again
```

### Physical Process:

```
Light Source → LDR → Voltage Divider → Arduino A0 → Processing → Outputs

Step-by-Step:
1. Light hits LDR surface
2. LDR resistance decreases
3. Voltage divider output increases
4. Arduino ADC samples voltage
5. Converts to digital value (0-1023)
6. Calculates actual voltage
7. Maps to PWM brightness
8. Sends PWM to LED
9. Displays data on Serial Monitor
10. Waits 500ms
11. Repeats from step 4
```

---

## 📊 Serial Monitor Output

### How to Open Serial Monitor:

```
Method 1: Arduino IDE Menu
  Tools → Serial Monitor

Method 2: Keyboard Shortcut
  Ctrl + Shift + M (Windows/Linux)
  Cmd + Shift + M (Mac)

Method 3: Icon
  Click magnifying glass icon (top-right)
```

### Configuration:

```
Serial Monitor Settings (bottom-right):
  ✓ Baud Rate: 9600 (MUST match Serial.begin(9600))
  ✓ Line Ending: Newline (or "Both NL & CR")
  ✓ Autoscroll: Enabled (checkbox)
```

### Sample Output Analysis:

```
Light Intensity Measurement System
===================================
Light Voltage: 0.488 V | ADC: 100 | LED: 25 /255
```

**Reading Interpretation:**

| Data | Value | Meaning |
|------|-------|---------|
| **Voltage** | 0.488 V | Actual voltage at Node A |
| **ADC** | 100 | Raw ADC reading (0-1023) |
| **LED** | 25 /255 | PWM brightness (10% duty cycle) |

**Condition:** Dark environment (high LDR resistance)

---

```
Light Voltage: 2.502 V | ADC: 512 | LED: 128 /255
```

**Reading Interpretation:**

| Data | Value | Meaning |
|------|-------|---------|
| **Voltage** | 2.502 V | Mid-range voltage |
| **ADC** | 512 | Exactly half of ADC range |
| **LED** | 128 /255 | 50% brightness |

**Condition:** Moderate lighting (LDR ≈ 10kΩ, equal to R2)

---

```
Light Voltage: 4.756 V | ADC: 974 | LED: 243 /255
```

**Reading Interpretation:**

| Data | Value | Meaning |
|------|-------|---------|
| **Voltage** | 4.756 V | High voltage (near 5V max) |
| **ADC** | 974 | Near maximum ADC value |
| **LED** | 243 /255 | 95% brightness |

**Condition:** Bright light (low LDR resistance)

---

## 💡 PWM LED Control

### LED Brightness Response:

| Light Level | LDR (Ω) | Node A Voltage | ADC Value | PWM Value | LED State |
|-------------|---------|----------------|-----------|-----------|-----------|
| **Darkness** | 1 MΩ | 0.05 V | ~10 | ~2 | Nearly off |
| **Dim Room** | 100 kΩ | 0.45 V | ~92 | ~23 | Very dim |
| **Indoor Light** | 10 kΩ | 2.50 V | 512 | 128 | Half brightness |
| **Bright Light** | 1 kΩ | 4.55 V | 931 | 232 | Nearly full |
| **Direct Sunlight** | 100 Ω | 4.95 V | 1013 | 253 | Full brightness |

### Visual Representation:

```
Light Level:  [Dark] ────────────→ [Bright]
LDR:          [High Ω] ──────────→ [Low Ω]
Voltage:      [Low V] ───────────→ [High V]
ADC:          [Low] ─────────────→ [High]
LED:          [Dim] ─────────────→ [Bright]

System Behavior: LED brightness proportional to ambient light
```

---

## 🔍 Calibration & Testing

### Test Procedure:

#### 1. **Darkness Test**
```
Setup:
  - Cover LDR completely with hand or opaque object
  
Expected Results:
  - Voltage: < 0.5V
  - ADC: < 100
  - LED: Very dim or off
  
Serial Output:
  Light Voltage: 0.244 V | ADC: 50 | LED: 12 /255
```

#### 2. **Room Light Test**
```
Setup:
  - Normal indoor lighting
  - LDR facing ceiling light
  
Expected Results:
  - Voltage: 1.5V - 3.5V
  - ADC: 300 - 700
  - LED: Medium brightness
  
Serial Output:
  Light Voltage: 2.456 V | ADC: 503 | LED: 125 /255
```

#### 3. **Flashlight Test**
```
Setup:
  - Shine flashlight directly on LDR
  - Distance: 5-10 cm
  
Expected Results:
  - Voltage: > 4.0V
  - ADC: > 800
  - LED: Very bright
  
Serial Output:
  Light Voltage: 4.658 V | ADC: 954 | LED: 238 /255
```

### Multimeter Verification:

**Measuring Node A Voltage:**

```
Multimeter Setup:
  1. Set to DC Voltage mode (V⎓)
  2. Range: 20V or auto
  3. Red probe → Node A (LDR & 10kΩ junction)
  4. Black probe → Arduino GND
  
Comparison:
  Multimeter Reading: 2.51V
  Serial Monitor: 2.502V
  
  Difference < 50mV = Good calibration!
  Difference > 100mV = Check connections
```

### Expected Behavior:

✅ **Correct Operation:**
- Covering LDR decreases voltage and dims LED
- Bright light increases voltage and brightens LED
- Serial Monitor shows smooth voltage changes
- LED brightness changes proportionally

❌ **Incorrect Operation:**
- LED brightness opposite to light level
- No voltage change when covering LDR
- Voltage stuck at 0V or 5V
- Serial Monitor shows constant values

---

## 🔧 Troubleshooting

### Common Issues and Solutions:

| Problem | Possible Cause | Solution |
|---------|----------------|----------|
| **No Serial output** | Serial Monitor not open | Open Tools → Serial Monitor |
| | Wrong baud rate | Set to 9600 in Monitor |
| | USB cable disconnected | Check USB connection |
| **Voltage always 0V** | LDR not powered | Check 5V connection to LDR |
| | A0 disconnected | Verify Node A → A0 wire |
| | 10kΩ shorted to GND before A0 | Check voltage divider order |
| **Voltage always 5V** | LDR open circuit | Check LDR connections |
| | 10kΩ resistor missing | Verify voltage divider complete |
| | A0 directly to 5V | Check Node A junction |
| **Voltage doesn't change** | LDR damaged | Test with multimeter (resistance check) |
| | Wrong resistor value | Verify 10kΩ (brown-black-orange) |
| | Breadboard poor contact | Re-seat components |
| **LED doesn't light** | Wrong polarity | Flip LED (long leg to resistor) |
| | No current limiting resistor | Add 220Ω resistor |
| | D9 disconnected | Check PWM wire |
| | LED burned out | Test with new LED |
| **LED always full bright** | D9 shorted to 5V | Check wiring |
| | Code not uploaded | Re-upload sketch |
| | Wrong pin in code | Verify `ledPin = 9` |
| **LED brightness opposite** | map() parameters swapped | Use `map(sensorValue, 0, 1023, 0, 255)` |
| **Flickering LED** | Poor connections | Check all wires firmly seated |
| | delay() too short | Increase to 500ms or more |
| | Power supply noise | Add 100μF capacitor across 5V-GND |
| **Erratic readings** | Electromagnetic interference | Keep wires short, add 0.1μF capacitor at A0 |
| | Floating voltage | Ensure 10kΩ resistor connected to GND |

---

### Advanced Debugging:

#### Isolate Sensor Circuit:
```cpp
void loop() {
  int sensorValue = analogRead(ldrPin);
  Serial.print("Raw ADC: ");
  Serial.println(sensorValue);
  delay(500);
}
// Expected: ADC changes when covering/uncovering LDR
```

#### Test LED Independently:
```cpp
void loop() {
  for (int i = 0; i <= 255; i += 5) {
    analogWrite(ledPin, i);
    delay(50);
  }
}
// Expected: LED smoothly fades from off to full brightness
```

#### Check Voltage Calculation:
```cpp
void loop() {
  int adc = analogRead(ldrPin);
  float v1 = adc * (5.0 / 1023.0);
  float v2 = (adc / 1023.0) * 5.0;  // Same result
  Serial.print("Method 1: ");
  Serial.print(v1);
  Serial.print("V | Method 2: ");
  Serial.print(v2);
  Serial.println("V");
  delay(1000);
}
// Expected: Both methods show same voltage
```

---

## 🌍 Real-World Applications

### Where This Technology is Used:

| Application | Description | Industry |
|-------------|-------------|----------|
| **Street Lighting** | Auto on/off at dusk/dawn | Municipal infrastructure |
| **Garden Lights** | Solar-powered outdoor lighting | Residential, landscaping |
| **Camera Metering** | Exposure control | Photography |
| **Smart Homes** | Automatic blinds, lighting | Home automation |
| **Greenhouses** | Monitor plant light exposure | Agriculture |
| **Security Systems** | Day/night mode switching | Safety & security |
| **Display Auto-Brightness** | Phone/laptop screens | Consumer electronics |
| **Photometry** | Scientific light measurement | Research, industry |

---

### Industrial Example: Street Light Controller

```
Enhanced Street Light System:
┌────────────────────────────────────┐
│ LDR Sensor                         │
│   ↓                                │
│ Arduino Controller                 │
│   ↓                                │
│ Relay Module                       │
│   ↓                                │
│ High-Power LED Street Lamp         │
│                                    │
│ Logic:                             │
│ if (voltage < 1.5V) {  // Dark    │
│   relay.on();  // Turn lights ON  │
│ } else {               // Bright  │
│   relay.off(); // Turn lights OFF │
│ }                                  │
└────────────────────────────────────┘
```

---

## 🚀 Project Extensions

### Beginner Level:

#### 1. **Add Threshold Detection**
```cpp
if (voltage < 1.0) {
  Serial.println("Status: DARK - Turn lights ON");
} else if (voltage < 3.0) {
  Serial.println("Status: MODERATE - Partial lighting");
} else {
  Serial.println("Status: BRIGHT - Lights OFF");
}
```

#### 2. **Reverse LED Control**
```cpp
// LED bright in darkness, dim in light
int brightness = map(sensorValue, 0, 1023, 255, 0);  // Reversed mapping
```

#### 3. **Add Buzzer Alert**
```cpp
const int buzzerPin = 8;
if (voltage > 4.5) {  // Very bright
  tone(buzzerPin, 1000, 100);  // Beep
}
```

---

### Intermediate Level:

#### 4. **LCD Display**
```cpp
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Light Monitor");
}

void loop() {
  // ... existing code ...
  lcd.setCursor(0, 1);
  lcd.print("V: ");
  lcd.print(voltage, 2);
  lcd.print("V  ");
  delay(500);
}
```

#### 5. **Data Logging to SD Card**
```cpp
#include <SD.h>
File dataFile = SD.open("light.txt", FILE_WRITE);
if (dataFile) {
  dataFile.print(millis());
  dataFile.print(",");
  dataFile.println(voltage);
  dataFile.close();
}
```

#### 6. **Moving Average Filter (Smooth Readings)**
```cpp
const int numReadings = 10;
int readings[numReadings];
int readIndex = 0;
int total = 0;

void loop() {
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(ldrPin);
  total = total + readings[readIndex];
  readIndex = (readIndex + 1) % numReadings;
  
  int average = total / numReadings;
  float voltage = average * (5.0 / 1023.0);
  // ... rest of code ...
}
```

---

### Advanced Level:

#### 7. **WiFi IoT Dashboard (ESP8266)**
```cpp
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

void loop() {
  // ... read sensor ...
  ThingSpeak.setField(1, voltage);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  delay(20000);  // Update every 20 seconds
}
```

#### 8. **Automatic Relay Control**
```cpp
const int relayPin = 7;
const float DARK_THRESHOLD = 1.5;  // Volts

void loop() {
  // ... read sensor ...
  if (voltage < DARK_THRESHOLD) {
    digitalWrite(relayPin, HIGH);  // Turn external light ON
  } else {
    digitalWrite(relayPin, LOW);   // Turn external light OFF
  }
}
```

#### 9. **Hysteresis Control (Prevents Flickering)**
```cpp
const float TURN_ON_THRESHOLD = 1.5;   // V
const float TURN_OFF_THRESHOLD = 2.0;  // V
bool lightState = false;

void loop() {
  // ... read voltage ...
  if (!lightState && voltage < TURN_ON_THRESHOLD) {
    lightState = true;
    digitalWrite(relayPin, HIGH);
  } else if (lightState && voltage > TURN_OFF_THRESHOLD) {
    lightState = false;
    digitalWrite(relayPin, LOW);
  }
}
```

---

## 🎯 Challenges

### 🟢 Beginner:
- [ ] Measure and display light in percentage (0-100%)
- [ ] Add a second LED that turns on when it's dark
- [ ] Create a "light meter" with 5 LEDs showing intensity

### 🟡 Intermediate:
- [ ] Log minimum and maximum light levels over time
- [ ] Create a sunrise/sunset detector with timestamps
- [ ] Build a plant growth light monitor with LCD display

### 🔴 Advanced:
- [ ] Design automatic window blinds controller
- [ ] Create solar panel tracking system (maximize light exposure)
- [ ] Build IoT weather station with light, temperature, humidity

---

## 📚 Technical Reference

### Arduino Functions Used:

| Function | Syntax | Return | Description |
|----------|--------|--------|-------------|
| `analogRead()` | `analogRead(pin)` | int (0-1023) | Read analog voltage |
| `analogWrite()` | `analogWrite(pin, value)` | void | Set PWM duty cycle (0-255) |
| `map()` | `map(value, fromLow, fromHigh, toLow, toHigh)` | long | Re-scale range |
| `pinMode()` | `pinMode(pin, mode)` | void | Configure pin direction |
| `Serial.begin()` | `Serial.begin(baud)` | void | Initialize serial |
| `Serial.print()` | `Serial.print(data)` | void | Print without newline |
| `Serial.println()` | `Serial.println(data)` | void | Print with newline |
| `delay()` | `delay(ms)` | void | Pause execution |

### Resistor Color Codes:

**10kΩ Resistor:**
```
┌──[Brown][Black][Orange][Gold]──┐
│    1      0      ×1000  ±5%    │
│  = 10,000 Ω = 10 kΩ            │
└────────────────────────────────┘
```

**220Ω Resistor:**
```
┌──[Red][Red][Brown][Gold]──┐
│   2    2    ×10    ±5%    │
│ = 220 Ω                   │
└───────────────────────────┘
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

- [Project 11: Temperature Sensor](../11%20Temperature%20sensor/)
- [Project 19: TMP36 with LCD Display](../19%20tmp36%20with%2016-2%20LCD%20display%20temperature/)
- [Project 10: Interfacing Photodiode](../10%20Interfacing%20Photodiode/)
- [Project 22: Digital Potentiometer](../22%20Digital%20Potentiometer/)

---

## 📖 Learning Resources:

- [Arduino Analog Input Tutorial](https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogInput)
- [PWM Basics](https://www.arduino.cc/en/Tutorial/Foundations/PWM)
- [Voltage Divider Calculator](https://ohmslawcalculator.com/voltage-divider-calculator)
- [LDR Datasheet](https://components101.com/resistors/ldr-datasheet)

---

## 📜 License

This project is part of the **40 Arduino Projects Series** by Akhinoor Islam.  
Licensed under MIT License - see [LICENSE](../LICENSE) file for details.

---

## ✅ Project Completion Checklist:

- [ ] All components gathered
- [ ] Circuit wired according to diagram
- [ ] Code uploaded successfully
- [ ] Serial Monitor configured (9600 baud)
- [ ] Voltage readings make sense (0-5V range)
- [ ] LED brightness responds to light
- [ ] Covering LDR dims LED
- [ ] Bright light brightens LED
- [ ] Multimeter verification matches Serial output
- [ ] Documentation understood

---

**Happy Building! 🎉**  
**Measure light, control brightness, and learn Arduino fundamentals! 💡**

---

### 🌟 Key Takeaways:

1. **LDRs are simple analog sensors** - resistance changes with light
2. **Voltage dividers** - fundamental circuit for sensor interfacing
3. **ADC conversion** - bridge between analog world and digital processing
4. **PWM control** - simulate analog output with digital pins
5. **Serial debugging** - essential skill for development

Master this project and you'll understand the foundation of countless sensor applications! 🚀