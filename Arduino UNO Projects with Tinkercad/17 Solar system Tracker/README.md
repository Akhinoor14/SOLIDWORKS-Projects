# ☀️ Dual-Axis Solar Tracking System

![Arduino](https://img.shields.io/badge/Arduino-UNO-00979D?style=for-the-badge&logo=arduino)
![Servo](https://img.shields.io/badge/Servo-Dual%20Axis-orange?style=for-the-badge)
![LDR](https://img.shields.io/badge/Sensors-4x%20LDR-green?style=for-the-badge)
![Solar](https://img.shields.io/badge/Application-Solar%20Tracking-yellow?style=for-the-badge)
![Level](https://img.shields.io/badge/Difficulty-Intermediate-blue?style=for-the-badge)

---

## 📚 Table of Contents
- [Project Overview](#-project-overview)
- [Key Features](#-key-features)
- [Components Required](#-components-required)
- [LDR Sensor Theory](#-ldr-sensor-theory)
- [Dual-Axis Tracking](#-dual-axis-tracking)
- [Circuit Diagram](#-circuit-diagram)
- [Pin Configuration](#-pin-configuration)
- [Working Principle](#-working-principle)
- [Code Explanation](#-code-explanation)
- [Tracking Algorithm](#-tracking-algorithm)
- [Calibration Guide](#-calibration-guide)
- [Troubleshooting](#-troubleshooting)
- [Applications](#-applications)
- [Learning Outcomes](#-learning-outcomes)

---

## 🎯 Project Overview

This project implements an **automated dual-axis solar tracking system** using Arduino UNO, 4 LDR sensors, and 2 servo motors. The system continuously monitors light intensity from four directions (top-left, top-right, bottom-left, bottom-right) and adjusts the solar panel position to face the brightest light source - maximizing solar energy capture throughout the day!

### 🌟 What Makes This Special?

```
✅ Dual-axis tracking (azimuth + elevation)
✅ 4-quadrant light sensing with LDRs
✅ Real-time position adjustment (1° increments)
✅ Dynamic range control via potentiometers
✅ Smooth servo movement (no jitter)
✅ Up to 40% more energy capture vs fixed panels
✅ Complete renewable energy application
✅ Tinkercad simulation available
```

### ☀️ Energy Efficiency Comparison:

```
Fixed Solar Panel:     ████████░░ (80% average efficiency)
Single-Axis Tracker:   ██████████░ (90% efficiency)
Dual-Axis Tracker:     ████████████ (95-98% efficiency) ⭐
```

---

## ✨ Key Features

| Feature | Specification |
|---------|--------------|
| **Tracking Type** | Dual-axis (azimuth + elevation) |
| **Horizontal Range** | 0° - 180° (adjustable via pot) |
| **Vertical Range** | 0° - 45° (adjustable via pot) |
| **Light Sensors** | 4× LDR (quadrant configuration) |
| **Servo Motors** | 2× SG90/MG995 (H + V axes) |
| **Update Rate** | 300ms (smooth tracking) |
| **Adjustment Step** | 1° per cycle (precise) |
| **Sensitivity** | Configurable tolerance (default: 15) |
| **Power Supply** | 5V (USB or external) |
| **Current Draw** | ~300mA (both servos active) |

---

## 🧰 Components Required

### Essential Components:

| Component | Specification | Quantity | Purpose |
|-----------|--------------|----------|---------|
| **Arduino UNO** | ATmega328P, 16MHz | 1 | Main controller |
| **Servo Motor** | SG90 (9g) or MG995 (metal gear) | 2 | Horizontal + Vertical movement |
| **LDR** | GL5528, 5-10kΩ @ 10 lux | 4 | Light intensity sensing |
| **Resistor** | 10kΩ, 1/4W | 4 | Voltage divider for LDRs |
| **Potentiometer** | 10kΩ, linear taper | 2 | Servo range control |
| **Breadboard** | Half-size (400 points) | 1 | Prototyping |
| **Jumper Wires** | Male-to-Male, various lengths | 20+ | Connections |
| **Power Supply** | 5V 2A adapter or USB | 1 | Power source |

### Optional Components:

- **Capacitor** (100µF, 16V) - Power supply filtering for servos
- **Diode** (1N4007) - Reverse polarity protection
- **Switch** (SPST) - Power on/off control
- **Solar Panel** (small 5V) - Actual tracking demonstration
- **Mounting Frame** - Cardboard/3D printed structure
- **External Power** (6V battery pack) - Independent servo power

### Total Cost Estimate: ~$15-25 USD (₹1200-2000)

---

## 🔬 LDR Sensor Theory

### What is an LDR?

**LDR (Light Dependent Resistor)** or **photoresistor** is a passive sensor whose resistance changes with light intensity. More light = lower resistance!

```
LDR Characteristics:

Dark Resistance:    1MΩ - 10MΩ (very high)
Light Resistance:   100Ω - 1kΩ (low)
Response Time:      ~10ms (rising), ~20ms (falling)
Spectral Peak:      ~540nm (green-yellow light)
Operating Voltage:  Max 150V
Power Rating:       100-200mW
```

### LDR Working Principle:

```
Photoconductivity Effect:

In Darkness:
  • Fewer free charge carriers
  • High resistance (MΩ range)
  • Low current flow
  • Low voltage at Arduino pin

In Light:
  • More photons absorbed
  • More free charge carriers generated
  • Low resistance (kΩ range)
  • High current flow
  • High voltage at Arduino pin

Light ↑ → Resistance ↓ → Voltage ↑ → analogRead() value ↑
```

### Voltage Divider Circuit:

```
LDR Voltage Divider Configuration:

        VCC (+5V)
           │
          LDR (R_ldr)
           │
           ├───→ To Arduino Analog Pin (A0-A3)
           │
          10kΩ (R_fixed)
           │
          GND

Output Voltage:
  V_out = VCC × (R_fixed / (R_ldr + R_fixed))

Example Calculations:
  
  Bright Light (R_ldr = 500Ω):
    V_out = 5V × (10k / (500 + 10k))
    V_out ≈ 4.76V
    analogRead() ≈ 976 (out of 1023)
  
  Dim Light (R_ldr = 50kΩ):
    V_out = 5V × (10k / (50k + 10k))
    V_out ≈ 0.83V
    analogRead() ≈ 170
  
  Darkness (R_ldr = 1MΩ):
    V_out = 5V × (10k / (1M + 10k))
    V_out ≈ 0.05V
    analogRead() ≈ 10
```

### LDR Response Curve:

```
Resistance vs Light Intensity:

Resistance (Ω)
    1M │                 ●
       │                /
  100k │              ●
       │            /
   10k │          ●
       │        /
    1k │      ●
       │    /
   100 │  ●
       └─────────────────── Light Intensity (lux)
         0  10  100 1k 10k

Note: Logarithmic response (nonlinear!)
```

---

## 🔄 Dual-Axis Tracking

### Two Degrees of Freedom:

```
Dual-Axis Solar Tracking System:

1. HORIZONTAL AXIS (Azimuth):
   • Rotation: 0° to 180° (left to right)
   • Follows sun's east-to-west movement
   • Controlled by: Servo Motor H (Pin 9)
   • Sensors: Left LDRs vs Right LDRs

        ┌─────┐
    0° ←│Panel│→ 180°
        └─────┘
         (Top view)

2. VERTICAL AXIS (Elevation):
   • Rotation: 0° to 45° (down to up)
   • Follows sun's altitude change
   • Controlled by: Servo Motor V (Pin 10)
   • Sensors: Top LDRs vs Bottom LDRs

          45° ↑  ┌─────┐
                 │Panel│
           0° ←  └─────┘
         (Side view)
```

### 4-Quadrant LDR Configuration:

```
LDR Physical Layout (looking from back of panel):

          FRONT (facing sun)
        ┌─────────────────┐
        │  TL         TR  │  TL = Top-Left (A0)
        │   ●         ●   │  TR = Top-Right (A1)
        │                 │
        │      PANEL      │
        │                 │
        │   ●         ●   │  BL = Bottom-Left (A2)
        │  BL         BR  │  BR = Bottom-Right (A3)
        └─────────────────┘
             BACK

Light Detection Logic:
  • TL + TR > BL + BR → Tilt UP (increase elevation)
  • BL + BR > TL + TR → Tilt DOWN (decrease elevation)
  • TL + BL > TR + BR → Rotate LEFT (decrease azimuth)
  • TR + BR > TL + BL → Rotate RIGHT (increase azimuth)
```

### Tracking Axes Explained:

```
HORIZONTAL SERVO (Azimuth):
  ┌─────────────────────────────────────┐
  │  0°        45°       90°      180°  │
  │  East     SE        South     West  │
  │   ↑        ↑         ↑         ↑    │
  └─────────────────────────────────────┘
  Tracks sun from sunrise (east) to sunset (west)

VERTICAL SERVO (Elevation):
  ┌─────────────────────────────────────┐
  │  0°           15°        30°    45° │
  │ Horizon     Morning     Noon   Max  │
  │   ↑           ↑          ↑      ↑   │
  └─────────────────────────────────────┘
  Tracks sun altitude throughout the day

Combined Movement:
  Morning:   Horizontal = 0° (East), Vertical = 15°
  Noon:      Horizontal = 90° (South), Vertical = 45°
  Evening:   Horizontal = 180° (West), Vertical = 15°
```

---

## 🔌 Circuit Diagram

### Complete System Circuit:

```
Dual-Axis Solar Tracker Circuit:

┌────────────────────────────────────────────────────────────────┐
│                                                                │
│  ┌─────────────────────────────────────────────────────────┐  │
│  │                    ARDUINO UNO                          │  │
│  │                                                         │  │
│  │  [A0] ←─── LDR Top-Left ────┤  VCC                     │  │
│  │              │              │                           │  │
│  │             10kΩ            │                           │  │
│  │              │              │                           │  │
│  │             GND             │                           │  │
│  │                             │                           │  │
│  │  [A1] ←─── LDR Top-Right ───┤                           │  │
│  │              │              │                           │  │
│  │             10kΩ            │                           │  │
│  │              │              │                           │  │
│  │             GND             │                           │  │
│  │                             │                           │  │
│  │  [A2] ←─── LDR Bottom-Left ─┤                           │  │
│  │              │              │                           │  │
│  │             10kΩ            │                           │  │
│  │              │              │                           │  │
│  │             GND             │                           │  │
│  │                             │                           │  │
│  │  [A3] ←─── LDR Bottom-Right ┤                           │  │
│  │              │              │                           │  │
│  │             10kΩ            │                           │  │
│  │              │              │                           │  │
│  │             GND             │                           │  │
│  │                             │                           │  │
│  │  [A4] ←─── Potentiometer H ─┤ (Horizontal range)        │  │
│  │              (wiper)        │                           │  │
│  │         VCC ──┤  ├── GND    │                           │  │
│  │                             │                           │  │
│  │  [A5] ←─── Potentiometer V ─┤ (Vertical range)          │  │
│  │              (wiper)        │                           │  │
│  │         VCC ──┤  ├── GND    │                           │  │
│  │                             │                           │  │
│  │  [D9] ───→ Servo H (Signal) │ Horizontal Servo         │  │
│  │            │                │                           │  │
│  │         VCC│  │GND          │                           │  │
│  │            ↓  ↓             │                           │  │
│  │        External 5V          │                           │  │
│  │                             │                           │  │
│  │ [D10] ───→ Servo V (Signal) │ Vertical Servo           │  │
│  │            │                │                           │  │
│  │         VCC│  │GND          │                           │  │
│  │            ↓  ↓             │                           │  │
│  │        External 5V          │                           │  │
│  │                             │                           │  │
│  │  [5V]  ────→ Power Rails    │                           │  │
│  │  [GND] ────→ Ground Rails   │                           │  │
│  └─────────────────────────────────────────────────────────┘  │
│                                                                │
│  External Power Supply (5V 2A):                                │
│    ┌─────────────┐                                            │
│    │   +5V  GND  │                                            │
│    └───┬─────┬───┘                                            │
│        │     │                                                │
│        │     └────→ Arduino GND + Servo GND (common)          │
│        └──────────→ Arduino VIN + Servo VCC                   │
│                                                                │
│  Optional: 100µF capacitor across servo power rails           │
└────────────────────────────────────────────────────────────────┘

LDR Configuration (Each):
  VCC (+5V) → LDR → Analog Pin (A0-A3) → 10kΩ → GND

Potentiometer Configuration (Each):
  Pin 1: VCC (+5V)
  Pin 2: Wiper → Analog Pin (A4 or A5)
  Pin 3: GND

Servo Configuration (Each):
  Red/Brown: VCC (+5V) - External supply recommended
  Black/Brown: GND - Common ground with Arduino
  Orange/Yellow: Signal - PWM pin (D9 or D10)
```

### Breadboard Layout:

```
Breadboard Connections:

Power Rails:
  ═══════════════════════════════════════ (+5V)
  ─────────────────────────────────────── (GND)

Left Section (Sensors):
  [LDR TL] → A0, VCC
     ↓ 10kΩ
    GND
  
  [LDR TR] → A1, VCC
     ↓ 10kΩ
    GND
  
  [LDR BL] → A2, VCC
     ↓ 10kΩ
    GND
  
  [LDR BR] → A3, VCC
     ↓ 10kΩ
    GND

Center Section (Potentiometers):
  [Pot H] → A4 (wiper), VCC, GND
  [Pot V] → A5 (wiper), VCC, GND

Right Section (Servos):
  [Servo H] → D9 (signal), 5V, GND
  [Servo V] → D10 (signal), 5V, GND

Note: Keep servo power wires short and thick (avoid voltage drop)
```

---

## 📍 Pin Configuration

### Complete Pin Mapping:

| Arduino Pin | Component | Type | Function |
|-------------|-----------|------|----------|
| **A0** | LDR Top-Left | Analog Input | Light sensing (TL quadrant) |
| **A1** | LDR Top-Right | Analog Input | Light sensing (TR quadrant) |
| **A2** | LDR Bottom-Left | Analog Input | Light sensing (BL quadrant) |
| **A3** | LDR Bottom-Right | Analog Input | Light sensing (BR quadrant) |
| **A4** | Potentiometer H | Analog Input | Horizontal range control (0-180°) |
| **A5** | Potentiometer V | Analog Input | Vertical range control (0-90°) |
| **D9** | Servo Motor H | PWM Output | Horizontal axis control |
| **D10** | Servo Motor V | PWM Output | Vertical axis control |
| **5V** | Power Rail | Power | LDRs, potentiometers |
| **GND** | Ground Rail | Ground | Common ground |

### Code Pin Definitions:

```cpp
Pin Definitions in Code:

const int ldrTopLeft = A0;      // LDR sensor top-left
const int ldrTopRight = A1;     // LDR sensor top-right
const int ldrBottomLeft = A2;   // LDR sensor bottom-left
const int ldrBottomRight = A3;  // LDR sensor bottom-right
const int potH = A4;            // Potentiometer horizontal
const int potV = A5;            // Potentiometer vertical

Servo servoH;  // Attached to pin 9 (horizontal)
Servo servoV;  // Attached to pin 10 (vertical)
```

---

## ⚙️ Working Principle

### System Operation Flow:

```
┌────────────────────────────────────────────────┐
│        SOLAR TRACKING SYSTEM FLOW              │
└────────────────────────────────────────────────┘
                    │
              Power ON
                    │
                    ▼
         ┌──────────────────┐
         │ System Setup     │
         │ • Initialize pins│
         │ • Attach servos  │
         │ • Set initial    │
         │   position:      │
         │   H=90°, V=45°   │
         └─────────┬────────┘
                   │
                   ▼
         ┌──────────────────┐
         │ Read 4 LDR       │ ◄──────────────┐
         │ Values:          │                │
         │ • TL, TR         │                │
         │ • BL, BR         │                │
         └─────────┬────────┘                │
                   │                         │
                   ▼                         │
         ┌──────────────────┐                │
         │ Calculate        │                │
         │ Averages:        │                │
         │ • avgTop         │                │
         │ • avgBottom      │                │
         │ • avgLeft        │                │
         │ • avgRight       │                │
         └─────────┬────────┘                │
                   │                         │
                   ▼                         │
         ┌──────────────────┐                │
         │ Compare Top vs   │                │
         │ Bottom           │                │
         └─────────┬────────┘                │
                   │                         │
         ┌─────────┴─────────┐               │
         │                   │               │
    Top > Bottom      Bottom > Top           │
         │                   │               │
         ▼                   ▼               │
  ┌──────────┐        ┌──────────┐          │
  │ Tilt UP  │        │Tilt DOWN │          │
  │ V_angle++│        │V_angle-- │          │
  └──────────┘        └──────────┘          │
         │                   │               │
         └─────────┬─────────┘               │
                   │                         │
                   ▼                         │
         ┌──────────────────┐                │
         │ Compare Left vs  │                │
         │ Right            │                │
         └─────────┬────────┘                │
                   │                         │
         ┌─────────┴─────────┐               │
         │                   │               │
    Left > Right      Right > Left           │
         │                   │               │
         ▼                   ▼               │
  ┌──────────┐        ┌──────────┐          │
  │Rotate    │        │ Rotate   │          │
  │LEFT      │        │ RIGHT    │          │
  │H_angle-- │        │H_angle++ │          │
  └──────────┘        └──────────┘          │
         │                   │               │
         └─────────┬─────────┘               │
                   │                         │
                   ▼                         │
         ┌──────────────────┐                │
         │ Read             │                │
         │ Potentiometers   │                │
         │ • Limit H range  │                │
         │ • Limit V range  │                │
         └─────────┬────────┘                │
                   │                         │
                   ▼                         │
         ┌──────────────────┐                │
         │ Update Servo     │                │
         │ Positions        │                │
         │ • servoH.write() │                │
         │ • servoV.write() │                │
         └─────────┬────────┘                │
                   │                         │
                   ▼                         │
         ┌──────────────────┐                │
         │ delay(300ms)     │                │
         │ Wait for stable  │                │
         │ reading          │                │
         └─────────┬────────┘                │
                   │                         │
                   └─────────────────────────┘
                    Loop Back
```

---

## 💻 Code Explanation

### Complete Code:

```cpp
/*
 * Project 17: Dual-Axis Solar Tracking System
 * Arduino UNO + 4 LDR + 2 Servo Motors
 * Tracks sun position for maximum solar panel efficiency
 */

#include <Servo.h>

// LDR sensor pins (4-quadrant configuration)
const int ldrTopLeft = A0;
const int ldrTopRight = A1;
const int ldrBottomLeft = A2;
const int ldrBottomRight = A3;

// Potentiometer pins (range control)
const int potH = A4;  // Horizontal servo limit
const int potV = A5;  // Vertical servo limit

// Servo objects
Servo servoH;  // Horizontal axis (azimuth)
Servo servoV;  // Vertical axis (elevation)

// Initial servo positions
int horizontalAngle = 90;   // Start at center (0-180°)
int verticalAngle = 45;     // Start at mid-elevation (0-90°)

// Tracking sensitivity
const int tolerance = 15;   // Minimum difference to trigger movement

void setup() {
  // Attach servos to PWM pins
  servoH.attach(9);   // Horizontal servo on D9
  servoV.attach(10);  // Vertical servo on D10
  
  // Set initial positions
  servoH.write(horizontalAngle);
  servoV.write(verticalAngle);
  
  // Wait for servos to reach position
  delay(1000);
  
  // Optional: Serial debugging
  Serial.begin(9600);
  Serial.println("Solar Tracker Initialized");
  Serial.println("H: 90° | V: 45°");
}

void loop() {
  // Read all 4 LDR sensors
  int valTopLeft = analogRead(ldrTopLeft);
  int valTopRight = analogRead(ldrTopRight);
  int valBottomLeft = analogRead(ldrBottomLeft);
  int valBottomRight = analogRead(ldrBottomRight);
  
  // Calculate averages for each axis
  int avgTop = (valTopLeft + valTopRight) / 2;
  int avgBottom = (valBottomLeft + valBottomRight) / 2;
  int avgLeft = (valTopLeft + valBottomLeft) / 2;
  int avgRight = (valTopRight + valBottomRight) / 2;
  
  // VERTICAL AXIS CONTROL (Elevation)
  // Top sensors have more light → tilt UP
  if (avgTop - avgBottom > tolerance) {
    if (verticalAngle < 90) {  // Max elevation limit
      verticalAngle++;
    }
  }
  // Bottom sensors have more light → tilt DOWN
  else if (avgBottom - avgTop > tolerance) {
    if (verticalAngle > 0) {  // Min elevation limit
      verticalAngle--;
    }
  }
  
  // HORIZONTAL AXIS CONTROL (Azimuth)
  // Left sensors have more light → rotate LEFT
  if (avgLeft - avgRight > tolerance) {
    if (horizontalAngle > 0) {  // Min azimuth limit
      horizontalAngle--;
    }
  }
  // Right sensors have more light → rotate RIGHT
  else if (avgRight - avgLeft > tolerance) {
    if (horizontalAngle < 180) {  // Max azimuth limit
      horizontalAngle++;
    }
  }
  
  // Read potentiometers for dynamic range control
  int potHVal = analogRead(potH);
  int potVVal = analogRead(potV);
  
  // Map potentiometer values to servo range
  int maxHorizontal = map(potHVal, 0, 1023, 0, 180);
  int maxVertical = map(potVVal, 0, 1023, 0, 90);
  
  // Constrain angles within potentiometer limits
  horizontalAngle = constrain(horizontalAngle, 0, maxHorizontal);
  verticalAngle = constrain(verticalAngle, 0, maxVertical);
  
  // Update servo positions
  servoH.write(horizontalAngle);
  servoV.write(verticalAngle);
  
  // Debug output (optional)
  Serial.print("TL:");
  Serial.print(valTopLeft);
  Serial.print(" TR:");
  Serial.print(valTopRight);
  Serial.print(" BL:");
  Serial.print(valBottomLeft);
  Serial.print(" BR:");
  Serial.print(valBottomRight);
  Serial.print(" | H:");
  Serial.print(horizontalAngle);
  Serial.print("° V:");
  Serial.print(verticalAngle);
  Serial.println("°");
  
  // Wait before next reading (smooth tracking)
  delay(300);
}
```

---

### Code Breakdown:

#### **1. Library and Pin Definitions:**

```cpp
#include <Servo.h>

const int ldrTopLeft = A0;
const int ldrTopRight = A1;
const int ldrBottomLeft = A2;
const int ldrBottomRight = A3;
const int potH = A4;
const int potV = A5;
```

**Explanation:**
- `#include <Servo.h>`: Arduino Servo library for PWM control
- LDR pins (A0-A3): Analog inputs for light sensing
- Pot pins (A4-A5): Analog inputs for range control

#### **2. Servo Objects and Variables:**

```cpp
Servo servoH;  // Horizontal axis
Servo servoV;  // Vertical axis

int horizontalAngle = 90;   // Start center
int verticalAngle = 45;     // Start mid-elevation
const int tolerance = 15;   // Sensitivity threshold
```

**Variables:**
- `servoH`, `servoV`: Servo control objects
- `horizontalAngle`: Current azimuth (0-180°)
- `verticalAngle`: Current elevation (0-90°)
- `tolerance`: Minimum light difference to trigger movement

**Why tolerance?**
```
Without tolerance:
  • Servo jitters constantly
  • Unstable positioning
  • High power consumption
  
With tolerance (15):
  • Only moves when difference > 15
  • Smooth, stable tracking
  • Efficient operation
```

#### **3. Setup Function:**

```cpp
void setup() {
  servoH.attach(9);
  servoV.attach(10);
  
  servoH.write(horizontalAngle);
  servoV.write(verticalAngle);
  
  delay(1000);
  Serial.begin(9600);
}
```

**Initialization:**
1. Attach servos to PWM pins (9, 10)
2. Set initial positions (90°, 45°)
3. Wait 1 second for servos to reach position
4. Start serial communication (debugging)

#### **4. Reading LDR Sensors:**

```cpp
int valTopLeft = analogRead(ldrTopLeft);
int valTopRight = analogRead(ldrTopRight);
int valBottomLeft = analogRead(ldrBottomLeft);
int valBottomRight = analogRead(ldrBottomRight);
```

**ADC Conversion:**
```
analogRead() returns 0-1023 (10-bit ADC)
  • 0 = 0V (darkness)
  • 1023 = 5V (bright light)
  • Resolution: 5V / 1024 = 4.88mV per step

Example readings:
  Bright sunlight:  900-1000
  Indoor light:     300-500
  Dim light:        100-200
  Darkness:         0-50
```

#### **5. Calculate Averages:**

```cpp
int avgTop = (valTopLeft + valTopRight) / 2;
int avgBottom = (valBottomLeft + valBottomRight) / 2;
int avgLeft = (valTopLeft + valBottomLeft) / 2;
int avgRight = (valTopRight + valBottomRight) / 2;
```

**Why averaging?**
```
Reduces noise and improves accuracy!

Example:
  TL = 850, TR = 870
  avgTop = (850 + 870) / 2 = 860
  
  BL = 600, BR = 650
  avgBottom = (600 + 650) / 2 = 625
  
  Difference = 860 - 625 = 235 > tolerance (15)
  → Action: Tilt UP! ✅
```

#### **6. Vertical Axis Control:**

```cpp
if (avgTop - avgBottom > tolerance) {
  if (verticalAngle < 90) {
    verticalAngle++;
  }
}
else if (avgBottom - avgTop > tolerance) {
  if (verticalAngle > 0) {
    verticalAngle--;
  }
}
```

**Logic:**
```
Top brighter than bottom:
  avgTop > avgBottom + tolerance
  → Sun is higher up
  → Increase elevation (tilt UP)
  → verticalAngle++ (max 90°)

Bottom brighter than top:
  avgBottom > avgTop + tolerance
  → Sun is lower down
  → Decrease elevation (tilt DOWN)
  → verticalAngle-- (min 0°)

Within tolerance:
  |avgTop - avgBottom| ≤ tolerance
  → Balanced light
  → No movement (stable)
```

#### **7. Horizontal Axis Control:**

```cpp
if (avgLeft - avgRight > tolerance) {
  if (horizontalAngle > 0) {
    horizontalAngle--;
  }
}
else if (avgRight - avgLeft > tolerance) {
  if (horizontalAngle < 180) {
    horizontalAngle++;
  }
}
```

**Logic:**
```
Left brighter than right:
  avgLeft > avgRight + tolerance
  → Sun is on the left
  → Rotate LEFT (counter-clockwise)
  → horizontalAngle-- (min 0°)

Right brighter than left:
  avgRight > avgLeft + tolerance
  → Sun is on the right
  → Rotate RIGHT (clockwise)
  → horizontalAngle++ (max 180°)

Within tolerance:
  |avgLeft - avgRight| ≤ tolerance
  → Balanced light
  → No movement (stable)
```

#### **8. Potentiometer Range Control:**

```cpp
int potHVal = analogRead(potH);
int potVVal = analogRead(potV);

int maxHorizontal = map(potHVal, 0, 1023, 0, 180);
int maxVertical = map(potVVal, 0, 1023, 0, 90);

horizontalAngle = constrain(horizontalAngle, 0, maxHorizontal);
verticalAngle = constrain(verticalAngle, 0, maxVertical);
```

**Dynamic Range Limiting:**
```
map() function:
  map(value, fromLow, fromHigh, toLow, toHigh)
  
  Example (Horizontal):
    Pot at 0%:    map(0, 0, 1023, 0, 180) = 0°
    Pot at 50%:   map(512, 0, 1023, 0, 180) = 90°
    Pot at 100%:  map(1023, 0, 1023, 0, 180) = 180°

constrain() function:
  constrain(value, min, max)
  
  Example:
    horizontalAngle = 150°
    maxHorizontal = 120° (pot setting)
    Result: constrain(150, 0, 120) = 120° ✅
    
    (Limits servo within user-defined range)

Use cases:
  • Prevent collision with mounting structure
  • Limit tracking to specific sky region
  • Test system with restricted movement
```

#### **9. Update Servos:**

```cpp
servoH.write(horizontalAngle);
servoV.write(verticalAngle);
```

**Servo Control:**
```
servoH.write(90):
  • Sends PWM signal to horizontal servo
  • Pulse width: 1500µs (center position)
  • Servo rotates to 90°
  
servoV.write(45):
  • Sends PWM signal to vertical servo
  • Pulse width: 1250µs (mid-range)
  • Servo rotates to 45°

PWM Timing:
  0° = 1000µs (1ms pulse)
  90° = 1500µs (1.5ms pulse)
  180° = 2000µs (2ms pulse)
  PWM frequency: 50Hz (20ms period)
```

#### **10. Delay and Loop:**

```cpp
delay(300);
```

**Why 300ms delay?**
```
Too fast (< 100ms):
  • Servo jitters
  • Noisy readings
  • High power consumption
  • Unstable tracking

Too slow (> 1000ms):
  • Slow response
  • Sun moves ahead
  • Tracking lags behind

Optimal (300ms):
  • Smooth movement ✅
  • Stable readings ✅
  • Good response time ✅
  • Low jitter ✅
```

---

## 🎯 Tracking Algorithm

### Decision Tree:

```
┌─────────────────────────────────────────────────┐
│         SOLAR TRACKING DECISION LOGIC           │
└─────────────────────────────────────────────────┘

Step 1: Read 4 LDR Values
  ┌────┬────┬────┬────┐
  │ TL │ TR │ BL │ BR │
  └────┴────┴────┴────┘

Step 2: Calculate Averages
  avgTop    = (TL + TR) / 2
  avgBottom = (BL + BR) / 2
  avgLeft   = (TL + BL) / 2
  avgRight  = (TR + BR) / 2

Step 3: Vertical Axis Decision
  ┌─────────────────────────────────┐
  │ avgTop - avgBottom > tolerance? │
  └──────────┬──────────────────────┘
             │
       YES ──┴── NO
        │         │
        ▼         ▼
   Tilt UP    avgBottom - avgTop > tolerance?
   V_angle++      │
             YES ──┴── NO
              │         │
              ▼         ▼
         Tilt DOWN   No Change
         V_angle--

Step 4: Horizontal Axis Decision
  ┌─────────────────────────────────┐
  │ avgLeft - avgRight > tolerance? │
  └──────────┬────────────────────────┘
             │
       YES ──┴── NO
        │         │
        ▼         ▼
   Rotate LEFT  avgRight - avgLeft > tolerance?
   H_angle--      │
             YES ──┴── NO
              │         │
              ▼         ▼
         Rotate RIGHT  No Change
         H_angle++

Step 5: Apply Limits
  H_angle = constrain(H_angle, 0, maxH)
  V_angle = constrain(V_angle, 0, maxV)

Step 6: Update Servos
  servoH.write(H_angle)
  servoV.write(V_angle)
```

### Example Scenario:

```
Morning (9 AM):
  Sun position: East (low elevation)
  
  LDR readings:
    TL = 400, TR = 800  → avgTop = 600
    BL = 300, BR = 700  → avgBottom = 500
    avgLeft = 350, avgRight = 750
  
  Vertical decision:
    avgTop - avgBottom = 600 - 500 = 100 > 15
    → Tilt UP (V_angle++)
  
  Horizontal decision:
    avgRight - avgLeft = 750 - 350 = 400 > 15
    → Rotate RIGHT (H_angle++)
  
  Result: Panel moves up and to the right (towards sun) ☀️

Noon (12 PM):
  Sun position: South (high elevation)
  
  LDR readings:
    TL = 850, TR = 870  → avgTop = 860
    BL = 840, BR = 850  → avgBottom = 845
    avgLeft = 845, avgRight = 860
  
  Vertical decision:
    avgTop - avgBottom = 860 - 845 = 15 ≈ tolerance
    → No change (balanced)
  
  Horizontal decision:
    avgRight - avgLeft = 860 - 845 = 15 ≈ tolerance
    → No change (balanced)
  
  Result: Panel stays pointing at sun (optimal!) ✅

Evening (6 PM):
  Sun position: West (low elevation)
  
  LDR readings:
    TL = 700, TR = 300  → avgTop = 500
    BL = 650, BR = 250  → avgBottom = 450
    avgLeft = 675, avgRight = 275
  
  Vertical decision:
    avgTop - avgBottom = 500 - 450 = 50 > 15
    → Tilt UP slightly (V_angle++)
  
  Horizontal decision:
    avgLeft - avgRight = 675 - 275 = 400 > 15
    → Rotate LEFT (H_angle--)
  
  Result: Panel moves up and to the left (following sunset) 🌅
```

---

## 🔧 Calibration Guide

### Initial Setup:

```
Step 1: Mechanical Assembly
  ✓ Mount servos on base plate
  ✓ Attach horizontal servo to base
  ✓ Attach vertical servo to horizontal arm
  ✓ Mount solar panel to vertical arm
  ✓ Ensure smooth rotation (no binding)

Step 2: LDR Placement
  ┌─────────────────┐
  │  ●           ●  │  ← Mount LDRs at panel corners
  │                 │     (facing same direction as panel)
  │     PANEL       │
  │                 │     Use small tubes/straws to focus
  │  ●           ●  │     light direction (optional)
  └─────────────────┘

Step 3: Wiring Check
  ✓ All LDRs connected to correct pins
  ✓ Servo signal wires to D9, D10
  ✓ Common ground established
  ✓ External power connected (if used)

Step 4: Initial Position
  • Set H_angle = 90° (center)
  • Set V_angle = 45° (mid-elevation)
  • Verify panel faces forward
```

### Software Calibration:

```cpp
// Test LDR readings
void testLDRs() {
  Serial.println("=== LDR Calibration ===");
  Serial.print("TL: "); Serial.println(analogRead(A0));
  Serial.print("TR: "); Serial.println(analogRead(A1));
  Serial.print("BL: "); Serial.println(analogRead(A2));
  Serial.print("BR: "); Serial.println(analogRead(A3));
  delay(1000);
}

// Call in setup():
testLDRs();

Expected results:
  • All similar values under uniform light
  • All change together when light varies
  • No stuck at 0 or 1023
```

### Tolerance Adjustment:

```cpp
// Adjust sensitivity based on environment

// High sensitivity (indoor, artificial light):
const int tolerance = 5;   // Responds to small differences

// Medium sensitivity (outdoor, cloudy):
const int tolerance = 15;  // Default, good balance

// Low sensitivity (outdoor, direct sun):
const int tolerance = 30;  // Ignores minor fluctuations
```

### Servo Range Calibration:

```cpp
// Test full servo range
void testServos() {
  Serial.println("Testing Horizontal Servo...");
  for (int i = 0; i <= 180; i += 10) {
    servoH.write(i);
    Serial.println(i);
    delay(500);
  }
  
  Serial.println("Testing Vertical Servo...");
  for (int i = 0; i <= 90; i += 10) {
    servoV.write(i);
    Serial.println(i);
    delay(500);
  }
}

// Call in setup():
testServos();

Check for:
  ✓ Smooth movement across full range
  ✓ No mechanical binding or collisions
  ✓ Stable holding at each position
```

---

## 🐛 Troubleshooting

### Common Issues:

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| **Servos jitter constantly** | Tolerance too low | Increase tolerance to 20-30 |
| | Noisy LDR readings | Add 0.1µF capacitor across each LDR |
| | Insufficient power | Use external 5V 2A power supply |
| **Panel doesn't move** | Servo not attached | Check `servoH.attach(9)` in setup |
| | No power to servos | Verify servo VCC connections |
| | LDR readings identical | Check LDR wiring, test individually |
| **Moves in wrong direction** | LDR positions swapped | Verify TL=A0, TR=A1, BL=A2, BR=A3 |
| | Servo reversed | Swap increment/decrement logic |
| **Erratic movement** | Shadows on LDRs | Use tubes to focus light direction |
| | Reflections | Mount LDRs flush with panel |
| **Stops at limits** | Mechanical obstruction | Check servo range, add soft stops |
| | Software limits | Adjust `constrain()` values |
| **Slow response** | Delay too long | Reduce delay from 300ms to 200ms |
| | Tolerance too high | Decrease tolerance to 10-15 |
| **One axis not working** | Servo connection | Check D9/D10 wiring |
| | LDR pair failure | Test LDR readings individually |

### Diagnostic Code:

```cpp
// Comprehensive diagnostic
void runDiagnostics() {
  Serial.println("=== SYSTEM DIAGNOSTICS ===");
  
  // Test LDRs
  Serial.println("\n--- LDR Readings ---");
  Serial.print("TL (A0): "); Serial.println(analogRead(A0));
  Serial.print("TR (A1): "); Serial.println(analogRead(A1));
  Serial.print("BL (A2): "); Serial.println(analogRead(A2));
  Serial.print("BR (A3): "); Serial.println(analogRead(A3));
  
  // Test Potentiometers
  Serial.println("\n--- Potentiometer Readings ---");
  Serial.print("Pot H (A4): "); Serial.println(analogRead(A4));
  Serial.print("Pot V (A5): "); Serial.println(analogRead(A5));
  
  // Test Servos
  Serial.println("\n--- Servo Test ---");
  Serial.println("Moving to 0°...");
  servoH.write(0);
  servoV.write(0);
  delay(1000);
  
  Serial.println("Moving to 90°...");
  servoH.write(90);
  servoV.write(45);
  delay(1000);
  
  Serial.println("Moving to max...");
  servoH.write(180);
  servoV.write(90);
  delay(1000);
  
  Serial.println("\n=== DIAGNOSTICS COMPLETE ===");
}

// Call in setup():
runDiagnostics();
```

---

## 🚀 Applications

### 1. Solar Panel Efficiency Optimization

```
Residential rooftop solar:
  • Fixed panel: ~80% efficiency
  • Single-axis tracker: ~90% efficiency
  • Dual-axis tracker: ~95-98% efficiency
  
  Annual energy gain: 30-40% increase!
  ROI: 2-3 years (commercial systems)
```

### 2. Solar Water Heater

```
Integrate with solar thermal collector:
  • Track sun throughout day
  • Maximize heat absorption
  • Reduce heating time by 40%
  • Automatic seasonal adjustment
```

### 3. Solar Oven/Cooker

```
Parabolic solar cooker tracking:
  • Maintains focus on sun
  • Consistent cooking temperature
  • No manual adjustment needed
  • Efficient outdoor cooking
```

### 4. Heliostat (Solar Concentrator)

```
Focus sunlight to fixed point:
  • Solar power tower applications
  • Concentrated solar power (CSP)
  • Research and experiments
  • Melting/welding demonstrations
```

### 5. Educational Projects

```
STEM learning:
  • Renewable energy concepts
  • Sensor integration
  • Control systems
  • Real-world problem solving
  • Physics of solar angles
```

---

## 📚 Learning Outcomes

### Skills Gained:

```
✅ Analog sensor interfacing (LDR voltage dividers)
✅ Servo motor control (PWM signals)
✅ Multi-sensor data fusion (averaging, comparison)
✅ Control algorithms (threshold-based decision making)
✅ Real-time feedback systems
✅ Dynamic range limiting (potentiometer control)
✅ Mechanical system integration
✅ Renewable energy principles
✅ Serial debugging techniques
✅ System calibration and optimization
```

### Advanced Concepts:

- **Feedback Control**: Closed-loop system maintaining optimal angle
- **Dead Band**: Tolerance prevents oscillation (hysteresis)
- **Multi-Axis Coordination**: Independent but synchronized movement
- **Sensor Fusion**: Combining multiple sensors for better accuracy
- **Energy Optimization**: Maximizing power output through positioning

---

## 🎯 Project Enhancements

### Enhancement 1: Add LCD Display

```cpp
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void loop() {
  // ... tracking code ...
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("H:");
  lcd.print(horizontalAngle);
  lcd.print(" V:");
  lcd.print(verticalAngle);
  
  lcd.setCursor(0, 1);
  lcd.print("Avg:");
  lcd.print((valTopLeft + valTopRight + 
             valBottomLeft + valBottomRight) / 4);
}
```

### Enhancement 2: Store Daily Profile

```cpp
#include <EEPROM.h>

// Store optimal angles every hour
void storeProfile() {
  static unsigned long lastStore = 0;
  if (millis() - lastStore > 3600000) {  // 1 hour
    int hour = (millis() / 3600000) % 24;
    EEPROM.write(hour * 2, horizontalAngle);
    EEPROM.write(hour * 2 + 1, verticalAngle);
    lastStore = millis();
  }
}
```

### Enhancement 3: Weather Detection

```cpp
// Detect clouds and adjust tracking
int detectClouds() {
  int avgLight = (valTopLeft + valTopRight + 
                  valBottomLeft + valBottomRight) / 4;
  
  if (avgLight < 200) {
    // Very dim - heavy clouds or night
    return 2;
  }
  else if (avgLight < 500) {
    // Dim - light clouds
    return 1;
  }
  return 0;  // Clear skies
}
```

### Enhancement 4: Sleep Mode

```cpp
void checkNightMode() {
  int avgLight = (valTopLeft + valTopRight + 
                  valBottomLeft + valBottomRight) / 4;
  
  if (avgLight < 50) {  // Dark = night
    servoH.write(0);    // Reset to east
    servoV.write(0);    // Reset to horizon
    delay(60000);       // Sleep 1 minute
  }
}
```

### Enhancement 5: Maximum Power Point Tracking

```cpp
// Monitor actual solar panel output
const int solarVoltagePin = A6;
const int solarCurrentPin = A7;

float measurePower() {
  float voltage = analogRead(solarVoltagePin) * (5.0 / 1023.0);
  float current = analogRead(solarCurrentPin) * (5.0 / 1023.0);
  return voltage * current;  // Power in watts
}

// Compare positions and choose best
void optimizeForPower() {
  float currentPower = measurePower();
  
  // Try slight adjustment
  servoH.write(horizontalAngle + 1);
  delay(500);
  float newPower = measurePower();
  
  if (newPower < currentPower) {
    // Worse, go back
    servoH.write(horizontalAngle - 1);
  }
  else {
    // Better, keep new position
    horizontalAngle++;
  }
}
```

---

## 📖 References

- [Solar Position Algorithm (SPA)](https://www.nrel.gov/docs/fy08osti/34302.pdf)
- [Arduino Servo Library](https://www.arduino.cc/reference/en/libraries/servo/)
- [Photoresistor Theory](https://en.wikipedia.org/wiki/Photoresistor)
- [Solar Tracking Systems Review](https://www.sciencedirect.com/science/article/pii/S1364032117312364)

---

## 👨‍💻 Author

**Md. Akhinoor Islam**  
📚 Energy Science and Engineering (ESE)  
🏫 Khulna University of Engineering & Technology (KUET)

---

## 📄 License

MIT License - Free to use, modify, and distribute!

---

## 🎉 Success Tips

```
1. Start Simple
   → Test each LDR individually first
   → Verify servo movement separately
   → Then combine everything

2. Mechanical Stability
   → Secure mounting is crucial
   → No loose connections
   → Smooth servo rotation

3. Light Focusing
   → Use tubes/straws on LDRs
   → Prevents ambient light interference
   → Better directional sensing

4. Power Management
   → External 5V supply for servos
   → Capacitor across servo power
   → Avoid Arduino USB power

5. Calibration is Key
   → Adjust tolerance for environment
   → Test in actual sunlight
   → Fine-tune ranges

6. Debug with Serial
   → Monitor LDR values
   → Track servo angles
   → Identify issues quickly

7. Weatherproofing (outdoor use)
   → Protect electronics from rain
   → UV-resistant enclosure
   → Sealed cable entries
```

**Good luck building your solar tracking system! ☀️🌍⚡**
