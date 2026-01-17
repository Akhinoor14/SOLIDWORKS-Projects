# 📺 16×2 LCD Display with ATtiny85 (Real-Time Clock)

![ATtiny85](https://img.shields.io/badge/MCU-ATtiny85-blue?style=for-the-badge)
![LCD](https://img.shields.io/badge/Display-16×2%20LCD-green?style=for-the-badge)
![Mode](https://img.shields.io/badge/Mode-4--bit-orange?style=for-the-badge)
![Power](https://img.shields.io/badge/Battery-1.5V%20+%20Boost-red?style=for-the-badge)
![Level](https://img.shields.io/badge/Difficulty-Advanced-red?style=for-the-badge)

---

## 📚 Table of Contents
- [Project Overview](#-project-overview)
- [Key Features](#-key-features)
- [Components Required](#-components-required)
- [16×2 LCD Display Architecture](#-162-lcd-display-architecture)
- [4-Bit vs 8-Bit Mode](#-4-bit-vs-8-bit-mode)
- [Step-Up Converter Theory](#-step-up-converter-theory)
- [Circuit Diagram](#-circuit-diagram)
- [Pin Configuration](#-pin-configuration)
- [Working Principle](#-working-principle)
- [Code Explanation](#-code-explanation)
- [Display Output](#-display-output)
- [Power Management](#-power-management)
- [Troubleshooting](#-troubleshooting)
- [Applications](#-applications)
- [Learning Outcomes](#-learning-outcomes)

---

## 🎯 Project Overview

This advanced project demonstrates **16×2 LCD interfacing with ATtiny85** microcontroller running on a **1.5V battery with step-up converter**. The system displays a **static message** on Line 1 and a **real-time clock (mm:ss)** on Line 2, all controlled via a DIP switch. This project combines low-power design, voltage boosting, and LCD control in 4-bit mode.

### 🌟 What Makes This Special?

- **Minimal Pin Usage**: 4-bit mode saves 4 I/O pins
- **Battery Powered**: 1.5V AA battery with boost converter
- **ATtiny85**: Compact 8-pin microcontroller driving LCD
- **Real-Time Clock**: Software-based minute:second counter
- **Power Control**: DIP switch for on/off
- **Low Cost**: ~$5-8 total components

---

## ✨ Key Features

| Feature | Description |
|---------|-------------|
| **Microcontroller** | ATtiny85 - 8KB Flash, 6 I/O pins |
| **Display** | 16×2 LCD - 2 lines × 16 characters |
| **Communication** | 4-bit parallel mode (6 pins) |
| **Power Source** | 1.5V AA battery + MT3608 boost converter |
| **Output Voltage** | 5V regulated (from 1.5V input) |
| **Current Draw** | ~30-50mA (LCD backlight ON) |
| **Clock Mode** | Software timer using millis() |
| **Update Rate** | 1 second per increment |
| **Display Format** | Line 1: Static message, Line 2: "welcome MM:SS" |

---

## 🧰 Components Required

### Essential Components:

| Component | Specification | Quantity | Purpose |
|-----------|--------------|----------|---------|
| **ATtiny85** | 8-pin DIP, 8KB Flash | 1 | Main microcontroller |
| **16×2 LCD Display** | HD44780 compatible | 1 | Character display output |
| **Step-Up Converter** | MT3608, 1.5V→5V boost | 1 | Voltage regulation |
| **AA Battery** | 1.5V Alkaline | 1 | Power source |
| **Battery Holder** | Single AA holder | 1 | Battery mounting |
| **DIP Switch** | SPST, 2-position | 1 | Power on/off control |
| **Resistor** | 220Ω, 1/4W | 1 | LCD backlight limiting |
| **Potentiometer** | 10kΩ trimpot | 1 | LCD contrast adjust (optional) |
| **Breadboard** | Full-size | 1 | Prototyping |
| **Jumper Wires** | Male-to-Male | 20+ | Connections |

### Optional Components:

- **LCD I2C Backpack** (saves 4 pins, uses SoftwareI2C)
- **0.1µF Capacitor** (power filtering)
- **100µF Capacitor** (boost converter output smoothing)
- **ATtiny85 Programmer** (USBtinyISP or Arduino as ISP)
- **8-pin DIP Socket** (easy ATtiny removal)

### Total Cost Estimate: ~$5-8 USD

---

## 🔬 16×2 LCD Display Architecture

### What is a 16×2 LCD?

A **16×2 LCD** is a character-based liquid crystal display capable of showing **2 lines** of text with **16 characters** per line.

```
16×2 LCD Display:
┌────────────────────────────────────────┐
│ ┌────────────────────────────────────┐ │
│ │ T H I S   I S   A K H I N O O R  │ │ ← Line 1 (Row 0)
│ ├────────────────────────────────────┤ │
│ │ W E L C O M E       0 0 : 0 0    │ │ ← Line 2 (Row 1)
│ └────────────────────────────────────┘ │
└────────────────────────────────────────┘
   ▲                                    ▲
Position (0,0)                   Position (15,1)

Total: 32 characters (16 × 2)
Each character: 5×8 dot matrix
```

### HD44780 Controller:

Most 16×2 LCDs use the **HD44780** or compatible controller chip.

```
HD44780 Features:
┌──────────────────────────────────────┐
│ • Built-in character ROM (192 chars) │
│ • 5×8 or 5×10 dot matrix             │
│ • 8-bit or 4-bit parallel interface  │
│ • Built-in LCD driver                │
│ • Contrast control via V0 pin        │
│ • Integrated backlight LEDs          │
│ • Operating voltage: 5V typical      │
│ • Instruction set for control        │
└──────────────────────────────────────┘
```

### LCD Pin Description:

```
16-pin LCD Pinout:
┌────┬─────────┬──────────────────────────────┐
│Pin │ Name    │ Function                     │
├────┼─────────┼──────────────────────────────┤
│ 1  │ VSS     │ Ground (GND)                 │
│ 2  │ VDD     │ Power +5V                    │
│ 3  │ V0      │ Contrast (0-5V via pot)      │
│ 4  │ RS      │ Register Select (CMD/DATA)   │
│ 5  │ R/W     │ Read/Write (GND = Write)     │
│ 6  │ E       │ Enable (falling edge clock)  │
│ 7  │ D0      │ Data bit 0 (8-bit mode)      │
│ 8  │ D1      │ Data bit 1 (8-bit mode)      │
│ 9  │ D2      │ Data bit 2 (8-bit mode)      │
│ 10 │ D3      │ Data bit 3 (8-bit mode)      │
│ 11 │ D4      │ Data bit 4 (4-bit & 8-bit)   │
│ 12 │ D5      │ Data bit 5 (4-bit & 8-bit)   │
│ 13 │ D6      │ Data bit 6 (4-bit & 8-bit)   │
│ 14 │ D7      │ Data bit 7 (4-bit & 8-bit)   │
│ 15 │ LED+    │ Backlight anode (+5V)        │
│ 16 │ LED-    │ Backlight cathode (GND)      │
└────┴─────────┴──────────────────────────────┘
```

### Control Pins Explained:

#### **RS (Register Select):**

```
RS Pin Function:
  RS = 0 → Command Mode (instructions to LCD)
  RS = 1 → Data Mode (characters to display)

Examples:
  RS=0: Clear display, set cursor position
  RS=1: Send character 'A', 'B', etc.
```

#### **R/W (Read/Write):**

```
R/W Pin Function:
  R/W = 0 → Write Mode (MCU → LCD)
  R/W = 1 → Read Mode (LCD → MCU)

In this project:
  R/W = GND (always write mode)
  We never read from LCD (saves 1 pin)
```

#### **E (Enable):**

```
Enable Pin Function:
  • Acts as clock signal
  • Data latched on falling edge (HIGH→LOW)
  • Must pulse HIGH then LOW to send data

Timing:
  ───┐     ┌───
     └─────┘
     ▲     ▲
   Enable  Latch data
```

---

## 🔀 4-Bit vs 8-Bit Mode

### Communication Mode Comparison:

| Feature | 8-Bit Mode | 4-Bit Mode |
|---------|-----------|------------|
| **Data Pins** | D0-D7 (8 pins) | D4-D7 (4 pins) |
| **Total Control Pins** | 11 pins (RS, E, 8 data) | 6 pins (RS, E, 4 data) |
| **Speed** | Faster (1 cycle) | Slower (2 cycles) |
| **Pin Efficiency** | Low | High ✅ |
| **Suitable For** | Pin-rich MCUs | ATtiny, pin-limited MCUs |
| **Complexity** | Simple | Moderate |

### Why 4-Bit Mode for ATtiny85?

```
ATtiny85 has only 6 I/O pins!
┌────────────────────────────────┐
│ Pin 1: RESET (can't use)       │
│ Pin 2: PB3 → LCD D5            │
│ Pin 3: PB4 → LCD D6            │
│ Pin 4: GND (power)             │
│ Pin 5: PB0 → LCD RS            │
│ Pin 6: PB1 → LCD E             │
│ Pin 7: PB2 → LCD D4            │
│ Pin 8: VCC (power)             │
└────────────────────────────────┘
   All 6 pins used! No room for 8-bit.

4-bit mode uses exactly 6 pins:
  RS, E, D4, D5, D6, D7 ✅
```

### 4-Bit Communication Process:

```
Sending 8-bit data in 4-bit mode:
┌────────────────────────────────────┐
│ Step 1: Send HIGH nibble (D7-D4)  │
│         8-bit: 1 0 1 1 0 1 0 0    │
│         Send: 1 0 1 1 first       │
│         Pulse E pin               │
├────────────────────────────────────┤
│ Step 2: Send LOW nibble (D3-D0)   │
│         Send: 0 1 0 0 second      │
│         Pulse E pin               │
└────────────────────────────────────┘

Result: LCD receives full 8-bit: 10110100

Two E pulses needed per byte!
```

---

## ⚡ Step-Up Converter Theory

### What is a Boost Converter?

A **boost converter** (step-up converter) increases DC voltage from a lower level to a higher level.

```
Boost Converter Principle:
   1.5V Input → [MT3608] → 5V Output

Working:
  1. Inductor stores energy (switch ON)
  2. Inductor releases energy (switch OFF)
  3. Diode prevents backflow
  4. Capacitor smooths output
  5. Feedback loop regulates voltage
```

### MT3608 Boost Converter Module:

```
MT3608 Module:
┌─────────────────────────────┐
│     [Trimmer Pot]           │
│        (Adjust)             │
│                             │
│  IN+  IN-  OUT+  OUT-       │
│   ●    ●    ●    ●          │
└───┼────┼────┼────┼──────────┘
    │    │    │    │
   1.5V GND  5V  GND
   (AA)     (to ATtiny & LCD)

Features:
  • Input: 2-24V DC (works with 1.5V!)
  • Output: 5-28V DC (adjustable)
  • Max Current: 2A
  • Efficiency: ~90%
  • Size: 17×11mm
  • Cost: ~$1
```

### Voltage Adjustment:

```
Adjusting Output Voltage:
1. Connect input (1.5V battery)
2. Connect multimeter to output
3. Turn trimmer pot clockwise → increase voltage
4. Turn counterclockwise → decrease voltage
5. Set to exactly 5.0V
6. Lock pot with glue/nail polish

⚠️ Don't exceed 5.5V (ATtiny85 max = 5.5V)
```

### Power Calculations:

```
Power Budget:
  ATtiny85: ~8mA
  LCD (no backlight): ~2mA
  LCD backlight: ~20-40mA
  Total: ~50mA @ 5V

Input power:
  5V × 0.05A = 0.25W

With 90% efficiency:
  Input = 0.25W / 0.9 = 0.278W
  Current @ 1.5V: 0.278W / 1.5V = 185mA

Battery capacity:
  AA Alkaline: ~2500mAh
  Runtime: 2500mAh / 185mA ≈ 13.5 hours ✅
```

---

## 🔌 Circuit Diagram

### Complete System Circuit:

```
1.5V Battery-Powered LCD System:
┌────────────────────────────────────────────────────────────┐
│                                                            │
│  ┌──────┐  DIP Switch                                     │
│  │  AA  │    ┌────┐                                       │
│  │ 1.5V │────┤ SW ├───┐                                   │
│  │2500mAh    └────┘   │                                   │
│  └──────┘             │                                   │
│  Battery              │                                   │
│                       │                                   │
│                  ┌────┴────┐                              │
│                  │ MT3608  │                              │
│                  │  Boost  │                              │
│                  │ Module  │                              │
│              IN+ │         │ OUT+ (+5V)                   │
│   ┌──────────────┤         ├──────────┬──────────────┐   │
│   │              │         │          │              │   │
│   │          IN- │         │ OUT-     │              │   │
│   │   ┌──────────┤         ├──────────┼──────────────┼───┤
│   │   │          └─────────┘          │              │   │
│   │   │        Step-Up 1.5V→5V        │              │   │
│   │   │                               │              │   │
│  1.5V GND                            +5V            GND  │
│   │   │                               │              │   │
│   │   │         ATtiny85              │              │   │
│   │   │      ┌────────┐               │              │   │
│   │   │      │1  ●  8├───────────────┘              │   │
│   │   │ PB3 ─┤2     7├─ PB2 (D4)                    │   │
│   │   │ PB4 ─┤3     6├─ PB1 (E)                     │   │
│   │   │      │4     5├─ PB0 (RS)                    │   │
│   │   │      └──┬─────┘                             │   │
│   │   │      GND│ VCC                               │   │
│   │   ├─────────┘  │                                │   │
│   │   │            └────────────────────────────────┼───┤
│   │   │                                             │   │
│   │   │                                            +5V GND
│   │   │                                             │   │
│   │   │         16×2 LCD Display                    │   │
│   │   │      ┌─────────────────────────┐            │   │
│   │   │      │ ┌─────────────────────┐ │            │   │
│   │   │      │ │ THIS IS AKHINOOR    │ │            │   │
│   │   │      │ ├─────────────────────┤ │            │   │
│   │   │      │ │ WELCOME    00:00    │ │            │   │
│   │   │      │ └─────────────────────┘ │            │   │
│   │   │      │                         │            │   │
│   │   │      │  Pin Configuration      │            │   │
│   │   │      │  ┌──┬──┬──┬──┬──┬──┬──┬┤            │   │
│   │   │      │  │1 │2 │3 │4 │5 │6...16│            │   │
│   │   │      └──┴──┴──┴──┴──┴──┴──┴──┴┘            │   │
│   │   │         │  │  │  │  │  │      │            │   │
│   │   ├─────────┘  │  │  │  │  │      │            │   │
│   │   │      ┌─────┘  │  │  │  │      │            │   │
│   │   │      │    ┌───┘  │  │  │      │            │   │
│   │   ├──────┼────┼──────┘  │  │      │            │   │
│   │   │      │    │   ┌─────┘  │      │            │   │
│   │   │      │    │   │   ┌────┘      │            │   │
│   │   │      │    │   │   │  ┌────────┘            │   │
│   │   │      │    │   │   │  │  ┌──────────────────┼───┤
│   │   │      │    │   │   │  │  │    ┌─────────────┘   │
│   └───┼──────┼────┼───┼───┼──┼──┼────┘                 │
│       │      │    │   │   │  │  │                      │
│      GND    VCC  V0  RS R/W E  D4...D7                 │
│      Pin1   Pin2 Pin3 Pin4 Pin5 Pin6 Pin11-14          │
│                   │                                     │
│              ┌────┴────┐                                │
│              │  10kΩ   │  (Optional: Contrast Control) │
│              │ Trimmer │                                │
│              └────┬────┘                                │
│                  GND                                    │
│                                                         │
│      LCD Backlight (Optional):                          │
│      Pin 15 (LED+) → +5V via 220Ω resistor              │
│      Pin 16 (LED-) → GND                                │
└─────────────────────────────────────────────────────────┘
```

### Simplified Breadboard Layout:

```
Breadboard View:
┌──────────────────────────────────────────────────┐
│  [AA Battery] → [DIP SW] → [MT3608 Module]      │
│      1.5V          ON/OFF     1.5V→5V            │
│                                  │               │
│                                 5V               │
│                                  │               │
│  ═══════════════════════════════╬═══════════════ │ +5V Rail
│  ───────────────────────────────┼─────────────── │ GND Rail
│                                 GND              │
│                                                  │
│    [ATtiny85]        [16×2 LCD Display]          │
│     8-pin DIP         16-pin Interface           │
│                                                  │
│  Pin Connections:                                │
│  ATtiny PB0 → LCD RS (Pin 4)                     │
│  ATtiny PB1 → LCD E (Pin 6)                      │
│  ATtiny PB2 → LCD D4 (Pin 11)                    │
│  ATtiny PB3 → LCD D5 (Pin 12)                    │
│  ATtiny PB4 → LCD D6 (Pin 13)                    │
│  ATtiny PB5 → LCD D7 (Pin 14)                    │
│                                                  │
│  LCD Power & Control:                            │
│  LCD Pin 1 (VSS) → GND                           │
│  LCD Pin 2 (VDD) → +5V                           │
│  LCD Pin 3 (V0) → GND (or 10kΩ pot)              │
│  LCD Pin 5 (R/W) → GND                           │
│                                                  │
│  ═══════════════════════════════════════════════ │
│  ─────────────────────────────────────────────── │
└──────────────────────────────────────────────────┘
```

---

## 📍 Pin Configuration

### Complete Pin Mapping:

| ATtiny85 | Physical Pin | Function | LCD Pin | LCD Function |
|----------|-------------|----------|---------|--------------|
| **RESET** | Pin 1 | Reset (pull-up) | - | Not connected |
| **PB3** | Pin 2 | Data Output | Pin 12 | D5 (Data bit 5) |
| **PB4** | Pin 3 | Data Output | Pin 13 | D6 (Data bit 6) |
| **GND** | Pin 4 | Ground | Pin 1, 5, 16 | VSS, R/W, LED- |
| **PB0** | Pin 5 | Control Output | Pin 4 | RS (Register Select) |
| **PB1** | Pin 6 | Control Output | Pin 6 | E (Enable) |
| **PB2** | Pin 7 | Data Output | Pin 11 | D4 (Data bit 4) |
| **VCC** | Pin 8 | Power +5V | Pin 2, 15 | VDD, LED+ |

### LCD Pin Connections:

```
LCD 16-Pin Detailed Mapping:
┌──────┬─────────┬─────────────────┬──────────────┐
│ Pin  │ Symbol  │ Connection      │ Purpose      │
├──────┼─────────┼─────────────────┼──────────────┤
│  1   │ VSS     │ GND             │ Ground       │
│  2   │ VDD     │ +5V (MT3608)    │ Power        │
│  3   │ V0      │ GND or 10kΩ pot │ Contrast     │
│  4   │ RS      │ ATtiny PB0      │ Reg Select   │
│  5   │ R/W     │ GND             │ Write mode   │
│  6   │ E       │ ATtiny PB1      │ Enable       │
│  7   │ D0      │ Not connected   │ (4-bit mode) │
│  8   │ D1      │ Not connected   │ (4-bit mode) │
│  9   │ D2      │ Not connected   │ (4-bit mode) │
│ 10   │ D3      │ Not connected   │ (4-bit mode) │
│ 11   │ D4      │ ATtiny PB2      │ Data bit 4   │
│ 12   │ D5      │ ATtiny PB3      │ Data bit 5   │
│ 13   │ D6      │ ATtiny PB4      │ Data bit 6   │
│ 14   │ D7      │ ATtiny PB5      │ Data bit 7   │
│ 15   │ LED+    │ +5V via 220Ω    │ Backlight +  │
│ 16   │ LED-    │ GND             │ Backlight -  │
└──────┴─────────┴─────────────────┴──────────────┘
```

### Arduino Pin Names vs ATtiny85:

```
In Code            ATtiny85 Physical    LCD Connection
──────────────────────────────────────────────────────
const int rs = 0;  → Pin 5 (PB0)     → LCD Pin 4 (RS)
const int en = 1;  → Pin 6 (PB1)     → LCD Pin 6 (E)
const int d4 = 2;  → Pin 7 (PB2)     → LCD Pin 11 (D4)
const int d5 = 3;  → Pin 2 (PB3)     → LCD Pin 12 (D5)
const int d6 = 4;  → Pin 3 (PB4)     → LCD Pin 13 (D6)
const int d7 = 5;  → Pin 1 (PB5)     → LCD Pin 14 (D7)
                                     ⚠️ Wait, PB5 is RESET!
```

**⚠️ Important Note on PB5:**

```
Problem:
  ATtiny85 Pin 1 is RESET by default!
  Using it as I/O requires disabling RESET fuse.

Solution 1: Use 5-data-pin mode (D4-D7 only, 5 pins)
Solution 2: Disable RESET fuse (risky, need HV programmer to recover)
Solution 3: Use I2C LCD backpack (only 2 pins!)

This project uses all 6 pins including PB5 as D7.
Must disable RESET fuse for PB5 to work as GPIO!
```

---

## ⚙️ Working Principle

### System Operation Flow:

```
┌──────────────────────────────────────────────────┐
│            SYSTEM OPERATION FLOW                 │
└──────────────────────────────────────────────────┘
                    │
              Power ON (DIP Switch)
                    │
                    ▼
         ┌──────────────────┐
         │ MT3608 Converts  │
         │ 1.5V → 5V        │
         └─────────┬────────┘
                   │
                   ▼
         ┌──────────────────┐
         │ ATtiny85 Boots   │
         │ • Setup pins     │
         │ • Init LCD       │
         └─────────┬────────┘
                   │
                   ▼
         ┌──────────────────┐
         │ LCD Initialize   │
         │ • 4-bit mode     │
         │ • 2 lines, 16 col│
         │ • Cursor off     │
         └─────────┬────────┘
                   │
                   ▼
         ┌──────────────────┐
         │ Display Line 1   │
         │ "THIS IS AKHINOOR"│
         │ (Static, setup)  │
         └─────────┬────────┘
                   │
                   ▼
         ┌──────────────────┐
         │ Main Loop Start  │ ◄──────────┐
         └─────────┬────────┘            │
                   │                     │
                   ▼                     │
         ┌──────────────────┐            │
         │ Check Timer      │            │
         │ millis() - prev  │            │
         │ >= 1000ms?       │            │
         └─────────┬────────┘            │
                   │                     │
            NO ←───┴───→ YES             │
            │           │                │
            │           ▼                │
            │  ┌──────────────────┐     │
            │  │ Increment Seconds│     │
            │  │ seconds++        │     │
            │  └─────────┬────────┘     │
            │            │               │
            │            ▼               │
            │  ┌──────────────────┐     │
            │  │ Check 60 seconds │     │
            │  │ seconds == 60?   │     │
            │  └─────────┬────────┘     │
            │            │               │
            │     NO ←───┴───→ YES      │
            │     │           │          │
            │     │           ▼          │
            │     │  ┌──────────────┐   │
            │     │  │ Reset seconds│   │
            │     │  │ minutes++    │   │
            │     │  └──────┬───────┘   │
            │     │         │            │
            │     │         ▼            │
            │     │  ┌──────────────┐   │
            │     │  │ Check 100 min│   │
            │     │  │ minutes==100?│   │
            │     │  └──────┬───────┘   │
            │     │         │            │
            │     │  NO ←───┴───→ YES   │
            │     │  │           │       │
            │     │  │           ▼       │
            │     │  │    ┌──────────┐  │
            │     │  │    │Reset min │  │
            │     │  │    └────┬─────┘  │
            │     └──┼─────────┘        │
            │        │                  │
            │        ▼                  │
            │  ┌──────────────────┐    │
            │  │ Display Line 2   │    │
            │  │ "WELCOME    "    │    │
            │  └─────────┬────────┘    │
            │            │              │
            │            ▼              │
            │  ┌──────────────────┐    │
            │  │ Display Time     │    │
            │  │ "MM:SS" format   │    │
            │  │ setCursor(11,1)  │    │
            │  └─────────┬────────┘    │
            │            │              │
            └────────────┼──────────────┘
                         │
                         └─────────────────┘
                       (Continue Loop)
```

### Step-by-Step Explanation:

#### **Step 1: Power Conversion**

```
Battery → Boost Converter → 5V Output

AA Battery: 1.5V (nominal)
  ↓
MT3608 Boost Converter:
  • Switching frequency: ~1 MHz
  • PWM duty cycle adjustment
  • Inductor energy storage
  ↓
Output: 5.0V ± 0.1V (regulated)
  ↓
Powers: ATtiny85 + LCD
```

#### **Step 2: LCD Initialization**

```cpp
lcd.begin(16, 2);
```

```
LiquidCrystal library sends init sequence:
  1. Wait 50ms after power-up
  2. Set 4-bit mode (special sequence)
  3. Set 2 lines, 5×8 font
  4. Display ON, cursor OFF
  5. Clear display
  6. Set entry mode (left-to-right)

Total init time: ~100ms
```

#### **Step 3: Display Static Message**

```cpp
lcd.setCursor(0, 0);
lcd.print("this is Akhinoor");
```

```
Line 1 Display:
  setCursor(0, 0) → Row 0, Column 0 (top-left)
  print() → Send characters one by one
  
  Position:  0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
            ┌──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┐
  Row 0:    │t │h │i │s │  │i │s │  │A │k │h │i │n │o │o │r │
            └──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┘

This line never changes (static in setup())!
```

#### **Step 4: Software Timer**

```cpp
unsigned long currentMillis = millis();
if (currentMillis - previousMillis >= 1000) {
  // 1 second elapsed
}
```

```
millis() Function:
  • Built-in Arduino function
  • Returns milliseconds since power-on
  • Overflows after ~49 days
  • Non-blocking (doesn't stop code)

Timer Logic:
  currentMillis: 5000ms
  previousMillis: 4000ms
  Difference: 1000ms → 1 second! ✅
  
  Update previousMillis = currentMillis
  Increment seconds
```

#### **Step 5: Time Increment**

```cpp
seconds++;
if (seconds == 60) {
  seconds = 0;
  minutes++;
  if (minutes == 100) minutes = 0;
}
```

```
Time Counter:
  seconds: 0 → 1 → 2 → ... → 59 → 0 (rollover)
  minutes: 0 → 1 → 2 → ... → 99 → 0 (rollover)

Example Timeline:
  00:00 (start)
  00:01 (1 sec)
  00:59 (59 sec)
  01:00 (1 min)
  01:30 (1 min 30 sec)
  99:59 (max)
  00:00 (reset)
```

#### **Step 6: Display Update**

```cpp
lcd.setCursor(0, 1);
lcd.print("welcome    ");

lcd.setCursor(11, 1);
if (minutes < 10) lcd.print('0');
lcd.print(minutes);
lcd.print(':');
if (seconds < 10) lcd.print('0');
lcd.print(seconds);
```

```
Line 2 Display:
  Position:  0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
            ┌──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┐
  Row 1:    │w │e │l │c │o │m │e │  │  │  │  │0 │3 │: │4 │5 │
            └──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┘
             ↑                               ↑           ↑
          "welcome"                    Time starts    "03:45"
                                       at column 11

Leading zeros for format:
  minutes = 3 → print "03" (not "3")
  seconds = 5 → print "05" (not "5")
```

---

## 💻 Code Explanation

### Complete Code:

```cpp
/*
 * Project 15: 16×2 LCD with ATtiny85 Real-Time Clock
 * Display static message and mm:ss timer
 */

#include <LiquidCrystal.h>

// LCD pins in 4-bit mode
const int rs = 0;  // PB0 (Pin 5) → LCD RS
const int en = 1;  // PB1 (Pin 6) → LCD E
const int d4 = 2;  // PB2 (Pin 7) → LCD D4
const int d5 = 3;  // PB3 (Pin 2) → LCD D5
const int d6 = 4;  // PB4 (Pin 3) → LCD D6
const int d7 = 5;  // PB5 (Pin 1) → LCD D7 (RESET disabled!)

// Create LCD object
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Timer variables
unsigned long previousMillis = 0;
int seconds = 0;
int minutes = 0;

void setup() {
  // Initialize LCD: 16 columns, 2 rows
  lcd.begin(16, 2);
  
  // Display static message on Line 1
  lcd.setCursor(0, 0);
  lcd.print("this is Akhinoor");
}

void loop() {
  // Get current time
  unsigned long currentMillis = millis();

  // Check if 1 second has passed
  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;

    // Increment seconds
    seconds++;
    
    // Handle 60-second rollover
    if (seconds == 60) {
      seconds = 0;
      minutes++;
      
      // Handle 100-minute rollover
      if (minutes == 100) {
        minutes = 0;
      }
    }

    // Display "welcome" on Line 2
    lcd.setCursor(0, 1);
    lcd.print("welcome    ");  // Spaces clear old time

    // Display time at end of Line 2 (column 11)
    lcd.setCursor(11, 1);
    
    // Print minutes with leading zero
    if (minutes < 10) lcd.print('0');
    lcd.print(minutes);
    
    // Print colon separator
    lcd.print(':');
    
    // Print seconds with leading zero
    if (seconds < 10) lcd.print('0');
    lcd.print(seconds);
  }
}
```

### Code Breakdown:

#### **Library Include:**

```cpp
#include <LiquidCrystal.h>
```

**Explanation:**
- Standard Arduino LCD library
- Supports HD44780-compatible displays
- Handles 4-bit and 8-bit communication
- Provides easy functions: `print()`, `setCursor()`, `clear()`

#### **Pin Definitions:**

```cpp
const int rs = 0;
const int en = 1;
const int d4 = 2;
const int d5 = 3;
const int d6 = 4;
const int d7 = 5;
```

**Explanation:**

```
Arduino pin numbers map to ATtiny85 physical pins:
  0 → PB0 (Physical Pin 5)
  1 → PB1 (Physical Pin 6)
  2 → PB2 (Physical Pin 7)
  3 → PB3 (Physical Pin 2)
  4 → PB4 (Physical Pin 3)
  5 → PB5 (Physical Pin 1) ⚠️ Requires RESET fuse disabled!

These 6 pins control all LCD operations!
```

#### **LCD Object Creation:**

```cpp
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
```

**Explanation:**

```
Constructor format (4-bit mode):
  LiquidCrystal(rs, enable, d4, d5, d6, d7)

This creates an "lcd" object with:
  • RS on pin 0
  • E on pin 1
  • Data on pins 2-5
  • R/W hardwired to GND (write-only)

Alternative (8-bit mode):
  LiquidCrystal(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7)
  (Not used here due to pin limitations)
```

#### **Timer Variables:**

```cpp
unsigned long previousMillis = 0;
int seconds = 0;
int minutes = 0;
```

**Explanation:**

```
unsigned long:
  • Range: 0 to 4,294,967,295 (32-bit)
  • Perfect for millis() (overflows after 49 days)
  • previousMillis stores last update time

int:
  • Range: -32,768 to 32,767 (16-bit)
  • seconds: 0-59
  • minutes: 0-99
```

#### **LCD Initialization:**

```cpp
lcd.begin(16, 2);
```

**Explanation:**

```
lcd.begin(columns, rows):
  • columns: 16 characters per line
  • rows: 2 lines total

Behind the scenes:
  1. Sends initialization sequence to LCD
  2. Sets 4-bit mode
  3. Configures display (2 lines, 5×8 font)
  4. Clears screen
  5. Sets cursor to home (0, 0)

Must be called in setup()!
```

#### **Cursor Positioning:**

```cpp
lcd.setCursor(0, 0);
```

**Explanation:**

```
lcd.setCursor(column, row):
  • column: 0-15 (left to right)
  • row: 0-1 (top to bottom)

Examples:
  setCursor(0, 0) → Top-left corner
  setCursor(15, 0) → Top-right corner
  setCursor(0, 1) → Bottom-left corner
  setCursor(11, 1) → Column 11, Row 1 (time position)

After setCursor(), next print() starts there!
```

#### **Printing Text:**

```cpp
lcd.print("this is Akhinoor");
```

**Explanation:**

```
lcd.print(data):
  • Converts data to characters
  • Sends to LCD starting at cursor position
  • Cursor auto-advances after each character

Types supported:
  print("text")  → String
  print('A')     → Single character
  print(123)     → Integer (converts to "123")
  print(3.14)    → Float (converts to "3.14")
```

#### **millis() Timer:**

```cpp
unsigned long currentMillis = millis();
```

**Explanation:**

```
millis() Function:
  • Returns milliseconds since Arduino powered on
  • Updates every 1ms (accurate to ~1ms)
  • Type: unsigned long (32-bit)
  • Overflows after: 2^32 ms ≈ 49.7 days

Usage:
  currentMillis: Current time snapshot
  Compare with previousMillis to find elapsed time

Why not delay()?
  delay() blocks all code (bad!)
  millis() is non-blocking (good!) ✅
```

#### **Time Check Logic:**

```cpp
if (currentMillis - previousMillis >= 1000) {
  previousMillis = currentMillis;
  // Update time
}
```

**Explanation:**

```
Non-Blocking Timer Pattern:

Time (ms):  0    500   1000  1500  2000
            │     │     │     │     │
currentMillis     │     │     │     │
previousMillis ───┴─────┼─────┼─────┘
                        │     │
Difference:       500ms 1000ms (trigger!)

When difference >= 1000ms:
  1. Update previousMillis (reset timer)
  2. Execute time update code
  3. Continue loop without blocking

This runs every 1 second precisely!
```

#### **Seconds Increment:**

```cpp
seconds++;
if (seconds == 60) {
  seconds = 0;
  minutes++;
  if (minutes == 100) minutes = 0;
}
```

**Explanation:**

```
Time Increment Logic:

Step 1: Increment seconds (0 → 59)
  seconds++ means seconds = seconds + 1

Step 2: Check for 60 seconds
  if (seconds == 60) → 1 minute passed!
  
Step 3: Reset seconds, increment minutes
  seconds = 0 (start new minute)
  minutes++ (add 1 minute)

Step 4: Check for 100 minutes (rollover)
  if (minutes == 100) → Reset to 00:00
  
Why 100 minutes?
  Display only has space for 2 digits (00-99)
  Could make it 60 for real hours, but code uses 99 max
```

#### **Display Formatting:**

```cpp
lcd.setCursor(0, 1);
lcd.print("welcome    ");
```

**Explanation:**

```
Why spaces after "welcome"?
  "welcome    " (11 characters total)
  ↑           ↑
  Text     Spaces clear old digits!

Without spaces:
  First display: "welcome    00:00"
  After 1 sec:   "welcome    00:01"
  After 10 sec:  "welcome    00:10" ✅
  
With old data not cleared:
  "welcome    0010" ❌ (old '0' remains!)

Spaces ensure clean display!
```

#### **Leading Zero Formatting:**

```cpp
if (minutes < 10) lcd.print('0');
lcd.print(minutes);
lcd.print(':');
if (seconds < 10) lcd.print('0');
lcd.print(seconds);
```

**Explanation:**

```
Time Format: MM:SS (always 5 characters)

Without leading zeros:
  minutes = 3, seconds = 5
  Display: "3:5" ❌ (looks wrong)

With leading zeros:
  if (minutes < 10) print '0' first
  then print minutes → "03"
  print ':'
  if (seconds < 10) print '0' first
  then print seconds → "05"
  Result: "03:05" ✅

Examples:
  00:00 (start)
  00:09 (9 seconds)
  00:10 (10 seconds)
  01:00 (1 minute)
  99:59 (max display)
```

---

## 📺 Display Output

### Expected LCD Display:

```
Line 1 (Static):
┌────────────────────────────────────┐
│ THIS IS AKHINOOR                   │
└────────────────────────────────────┘
  ↑                              ↑
Position (0,0)              Always same

Line 2 (Dynamic):
┌────────────────────────────────────┐
│ WELCOME       MM:SS                │
└────────────────────────────────────┘
  ↑             ↑
"welcome"    Time updates every second

Full Display:
┌────────────────────────────────────┐
│ THIS IS AKHINOOR                   │
│ WELCOME       00:45                │
└────────────────────────────────────┘
```

### Time Progression Examples:

```
After power-on:
┌────────────────────────────────────┐
│ THIS IS AKHINOOR                   │
│ WELCOME       00:00                │
└────────────────────────────────────┘

After 30 seconds:
┌────────────────────────────────────┐
│ THIS IS AKHINOOR                   │
│ WELCOME       00:30                │
└────────────────────────────────────┘

After 1 minute 15 seconds:
┌────────────────────────────────────┐
│ THIS IS AKHINOOR                   │
│ WELCOME       01:15                │
└────────────────────────────────────┘

After 99 minutes 59 seconds:
┌────────────────────────────────────┐
│ THIS IS AKHINOOR                   │
│ WELCOME       99:59                │
└────────────────────────────────────┘

After rollover (100 minutes):
┌────────────────────────────────────┐
│ THIS IS AKHINOOR                   │
│ WELCOME       00:00                │
└────────────────────────────────────┘
```

---

## 🔋 Power Management

### Power Consumption Analysis:

| Component | Current Draw | Voltage | Power |
|-----------|-------------|---------|-------|
| ATtiny85 (active) | ~8 mA | 5V | 40 mW |
| LCD (no backlight) | ~2 mA | 5V | 10 mW |
| LCD backlight | ~20-40 mA | 5V | 100-200 mW |
| **Total (backlight ON)** | **~50 mA** | **5V** | **250 mW** |
| **Total (backlight OFF)** | **~10 mA** | **5V** | **50 mW** |

### Battery Life Calculation:

```
AA Alkaline Battery:
  Voltage: 1.5V (nominal)
  Capacity: ~2500 mAh (typical)

With Backlight ON:
  Power: 250 mW
  Efficiency: 90% (MT3608)
  Input power: 250mW / 0.9 = 278 mW
  Current @ 1.5V: 278mW / 1.5V = 185 mA
  Runtime: 2500mAh / 185mA ≈ 13.5 hours ✅

With Backlight OFF:
  Power: 50 mW
  Input current: 50mW / (0.9 × 1.5V) = 37 mA
  Runtime: 2500mAh / 37mA ≈ 67 hours! 🎉

Recommendation: Turn off backlight for long runtime!
```

### Power Optimization Tips:

1. **Disable LCD Backlight:**
```
Remove/disconnect Pin 15 (LED+) → Pin 16 (LED-)
LCD still readable in good light!
10x longer battery life!
```

2. **Reduce Refresh Rate:**
```cpp
// Update every 2 seconds instead of 1
if (currentMillis - previousMillis >= 2000) {
  // Halves power consumption
}
```

3. **Sleep Mode (Advanced):**
```cpp
#include <avr/sleep.h>
#include <avr/power.h>

// Put ATtiny to sleep between updates
// Wake with timer interrupt
// ~100x power savings!
```

---

## 🐛 Troubleshooting

### Common Issues:

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| **No display** | No power | Check battery, DIP switch, MT3608 output |
| | Wrong wiring | Verify all 16 LCD pins |
| | No contrast | Adjust V0 pot or connect Pin 3 to GND |
| **Blank boxes** | Contrast too high | Connect V0 to GND directly |
| **Random characters** | Bad connection | Re-check D4-D7, RS, E pins |
| | Power instability | Add 100µF cap to MT3608 output |
| **No time update** | Code not uploaded | Re-upload with correct board settings |
| | millis() overflow | Rare, resets after 49 days |
| **Incorrect pins** | Wrong ATtiny fuse | Check RESET fuse for PB5 usage |
| **Backlight dim** | Resistor too high | Use 220Ω or lower (check LED rating) |
| **MT3608 not working** | Input voltage low | Battery <0.9V, replace |
| | Trimmer pot wrong | Adjust pot, check output with multimeter |

### Diagnostic Steps:

#### **Step 1: Check Power**

```
Multimeter Tests:
  1. Battery voltage: Should be >1.2V
  2. MT3608 input: Should match battery
  3. MT3608 output: Should be 5.0V ± 0.2V
  4. ATtiny VCC (Pin 8): Should be 5V
  5. LCD VDD (Pin 2): Should be 5V

If any voltage wrong → Fix power circuit first!
```

#### **Step 2: Test LCD Contrast**

```
V0 Pin Test:
  1. Power ON the system
  2. Connect V0 (Pin 3) directly to GND
  3. Should see dark boxes on LCD
  4. If no boxes → LCD may be damaged

For adjustable contrast:
  1. Use 10kΩ potentiometer
  2. Connect: +5V → Pot → Pin 3 → GND
  3. Turn pot to adjust contrast
```

#### **Step 3: Verify Pin Connections**

```
Use multimeter continuity mode:
  1. Power OFF
  2. Check ATtiny PB0 → LCD Pin 4 (RS)
  3. Check ATtiny PB1 → LCD Pin 6 (E)
  4. Check ATtiny PB2 → LCD Pin 11 (D4)
  5. Check ATtiny PB3 → LCD Pin 12 (D5)
  6. Check ATtiny PB4 → LCD Pin 13 (D6)
  7. Check ATtiny PB5 → LCD Pin 14 (D7)

Beep = connection OK ✅
No beep = loose wire ❌
```

#### **Step 4: Test with Simple Code**

```cpp
// Upload minimal test code
#include <LiquidCrystal.h>
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

void setup() {
  lcd.begin(16, 2);
  lcd.print("TEST");
}

void loop() {}

If "TEST" appears → LCD working! ✅
If not → Hardware issue
```

### PB5 RESET Fuse Issue:

```
Problem:
  ATtiny85 Pin 1 (PB5) is RESET by default
  Can't use as GPIO without disabling RESET fuse

Solutions:

Option 1: Don't use PB5, sacrifice D7
  • Use 5 data pins (D4-D6 + dummy D7)
  • LCD still works (4-bit needs min 4 pins)
  • Easiest solution!

Option 2: Disable RESET fuse
  • Requires ISP programmer (USBtinyISP, Arduino as ISP)
  • Command: avrdude -c usbtiny -p attiny85 -U lfuse:w:0x62:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m
  • ⚠️ After this, need HV programmer to re-enable RESET!
  • Risky for beginners

Recommendation: Use Option 1 (skip PB5/D7) for safety!
```

---

## 🚀 Applications

### 1. Portable Clock

```
Features:
  • Battery-powered digital clock
  • Minute:second display
  • Small form factor
  • Low power (<50mA)
```

### 2. Timer/Stopwatch

```cpp
// Modify code for stopwatch:
// Add button on free pin to start/stop
// Reset on button long-press
```

### 3. Temperature Display

```cpp
// Add TMP36 sensor on free pin
// Display: "Temp: 25.5°C"
// Real-time temperature monitor
```

### 4. Custom Message Board

```cpp
// Upload custom messages:
lcd.print("Happy Birthday!");
lcd.setCursor(0, 1);
lcd.print("John :)");
// Personalized LED sign
```

### 5. Data Logger Display

```cpp
// Read sensor every minute
// Display latest reading on LCD
// Store in EEPROM for history
```

### 6. Countdown Timer

```cpp
// Start from 99:59 and count down
// Alarm when reaches 00:00
// Kitchen timer, exam timer
```

---

## 📚 Learning Outcomes

### Skills Gained:

```
✅ 16×2 LCD interfacing in 4-bit mode
✅ ATtiny85 advanced pin usage
✅ Step-up boost converter theory
✅ Battery-powered system design
✅ LiquidCrystal library usage
✅ Non-blocking timers with millis()
✅ LCD cursor control and formatting
✅ Leading zero formatting
✅ Power management and efficiency
✅ Low-voltage circuit design
✅ Fuse bit configuration (PB5 RESET)
```

### Advanced Concepts:

- **4-bit vs 8-bit Communication**: Pin efficiency trade-offs
- **Boost Converter**: Voltage step-up using switching regulators
- **Non-Blocking Code**: millis() vs delay() programming
- **LCD HD44780 Protocol**: Command vs data modes, enable pulses
- **Power Budgeting**: Current draw analysis and battery life
- **Contrast Control**: LCD visibility optimization

---

## 🎯 Project Challenges

### Challenge 1: Add Button Control

```cpp
// Add button to start/stop clock
// Pin 2 (ATtiny) as button input
// Use internal pull-up resistor
```

### Challenge 2: Real-Time Clock (RTC)

```cpp
// Add DS1307 RTC module (I2C)
// Display real time (hours:minutes)
// Date on Line 1, Time on Line 2
```

### Challenge 3: Scrolling Text

```cpp
// Make Line 1 text scroll left-to-right
// Use lcd.scrollDisplayLeft()
// Loop continuously
```

### Challenge 4: Alarm Function

```cpp
// Set alarm time in code
// When time matches, blink backlight
// Or trigger buzzer on free pin
```

### Challenge 5: Temperature + Clock

```cpp
// Add TMP36 sensor
// Line 1: "Temp: 25.5C"
// Line 2: "Time: 12:34"
// Dual display!
```

---

## 📖 References

- [LiquidCrystal Library Documentation](https://www.arduino.cc/reference/en/libraries/liquidcrystal/)
- [HD44780 LCD Controller Datasheet](https://www.sparkfun.com/datasheets/LCD/HD44780.pdf)
- [ATtiny85 Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf)
- [MT3608 Boost Converter Datasheet](https://www.olimex.com/Products/Breadboarding/BB-PWR-3608/resources/MT3608.pdf)

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

1. **Test boost converter first** - Verify 5.0V output before connecting MCU
2. **Check LCD contrast** - Connect V0 to GND for full contrast
3. **Verify pin connections** - Use multimeter continuity mode
4. **Start without backlight** - Test display visibility, add backlight later
5. **PB5 RESET fuse** - Either skip D7 pin or carefully disable RESET
6. **Use fresh battery** - Old batteries <1.2V won't work
7. **Secure breadboard** - Loose wires cause intermittent issues

**Good luck building your ATtiny85 LCD clock! 📺⏰🎉**
