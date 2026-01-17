# 🎲 Electronic Dice with 7-Segment Display

![ATtiny85](https://img.shields.io/badge/MCU-ATtiny85-blue?style=for-the-badge)
![74HC595](https://img.shields.io/badge/IC-74HC595%20Shift%20Register-green?style=for-the-badge)
![7-Segment](https://img.shields.io/badge/Display-7--Segment%20CC-red?style=for-the-badge)
![Button](https://img.shields.io/badge/Input-Push%20Button-orange?style=for-the-badge)
![Level](https://img.shields.io/badge/Difficulty-Intermediate-yellow?style=for-the-badge)

---

## 📚 Table of Contents
- [Project Overview](#-project-overview)
- [Key Features](#-key-features)
- [Components Required](#-components-required)
- [7-Segment Display Theory](#-7-segment-display-theory)
- [74HC595 Shift Register](#-74hc595-shift-register)
- [Circuit Diagram](#-circuit-diagram)
- [Pin Configuration](#-pin-configuration)
- [Working Principle](#-working-principle)
- [Code Explanation](#-code-explanation)
- [Dice Animation](#-dice-animation)
- [Random Number Generation](#-random-number-generation)
- [Troubleshooting](#-troubleshooting)
- [Applications](#-applications)
- [Learning Outcomes](#-learning-outcomes)

---

## 🎯 Project Overview

This project creates a **digital dice** using ATtiny85 microcontroller, 74HC595 shift register, and a common cathode 7-segment display. Press a button to "roll" the dice - it shows a smooth animation (1→6→5→2) and displays a random number between 1 and 6. Perfect for board games, decision making, or learning shift register control!

### 🌟 What Makes This Special?

- **Pin Efficiency**: Control 7 segments with only 3 GPIO pins
- **Realistic Animation**: Smooth rolling effect before result
- **True Randomness**: Analog noise-based random generation
- **Compact Design**: ATtiny85 8-pin microcontroller
- **Low Power**: ~20mA total current draw
- **Interactive**: Push button trigger

---

## ✨ Key Features

| Feature | Description |
|---------|-------------|
| **Microcontroller** | ATtiny85 - 8KB Flash, 6 I/O pins |
| **Display** | Common Cathode 7-Segment (single digit) |
| **Shift Register** | 74HC595 - Serial to parallel converter |
| **Random Range** | 1 to 6 (standard dice) |
| **Animation** | Rolling effect with configurable speed |
| **Input** | Push button with software debouncing |
| **Current Draw** | ~20mA (display + MCU) |
| **Operating Voltage** | 3V - 5V |
| **Response Time** | <100ms after button press |

---

## 🧰 Components Required

### Essential Components:

| Component | Specification | Quantity | Purpose |
|-----------|--------------|----------|---------|
| **ATtiny85** | 8-pin DIP, 8KB Flash | 1 | Main microcontroller |
| **74HC595** | 8-bit shift register, SOP-16/DIP-16 | 1 | Serial to parallel conversion |
| **7-Segment Display** | Common Cathode, Red/Green, 0.56" | 1 | Display digits 0-6 |
| **Push Button** | Tactile switch, 4-pin | 1 | Dice roll trigger |
| **Resistors** | 330Ω, 1/4W | 8 | Current limiting (7 seg + cathode) |
| **Resistor** | 10kΩ, 1/4W | 1 | Button pull-down (optional) |
| **LED** | 5mm, any color | 1 | Indicator (optional) |
| **Breadboard** | Half-size or full | 1 | Prototyping |
| **Jumper Wires** | Male-to-Male | 20+ | Connections |
| **Power Supply** | 3V-5V (USB or battery) | 1 | Power source |

### Optional Components:

- **10µF Capacitor** (power supply filtering)
- **0.1µF Capacitor** (decoupling for ICs)
- **ATtiny85 Programmer** (USBtinyISP or Arduino as ISP)
- **8-pin DIP Socket** (easy ATtiny removal)

### Total Cost Estimate: ~$3-5 USD

---

## 🔬 7-Segment Display Theory

### What is a 7-Segment Display?

A **7-segment display** consists of 7 LEDs arranged to form the figure "8". By lighting different combinations, it can display digits 0-9 and some letters.

```
7-Segment Layout:
      ┌─── a ───┐
      │         │
      f         b
      │         │
      ├─── g ───┤
      │         │
      e         c
      │         │
      └─── d ───┘  ● dp (decimal point)

Segment Names:
  a = top
  b = top-right
  c = bottom-right
  d = bottom
  e = bottom-left
  f = top-left
  g = middle
  dp = decimal point (not used in this project)
```

### Common Cathode vs Common Anode:

```
Common Cathode (CC):
  • All cathodes (─) connected together to GND
  • Anodes (+) control individual segments
  • HIGH = segment ON
  • LOW = segment OFF
  
  Circuit:
    ATtiny → 330Ω → Segment anode
    Segment cathode → GND (common)

Common Anode (CA):
  • All anodes (+) connected together to VCC
  • Cathodes (─) control individual segments
  • LOW = segment ON
  • HIGH = segment OFF
  
  Circuit:
    Segment anode → VCC (common)
    ATtiny → 330Ω → Segment cathode

This project uses Common Cathode (CC)!
```

### Segment Patterns for Digits:

```
Binary Pattern (gfedcba):
┌──────┬──────────┬───────────────────────────┐
│Digit │ Binary   │ Hex   │ Segments Lit      │
├──────┼──────────┼───────┼───────────────────┤
│  0   │ 0x3F     │ 0x3F  │ a,b,c,d,e,f       │
│  1   │ 0x06     │ 0x06  │ b,c               │
│  2   │ 0x5B     │ 0x5B  │ a,b,g,e,d         │
│  3   │ 0x4F     │ 0x4F  │ a,b,g,c,d         │
│  4   │ 0x66     │ 0x66  │ f,g,b,c           │
│  5   │ 0x6D     │ 0x6D  │ a,f,g,c,d         │
│  6   │ 0x7D     │ 0x7D  │ a,f,g,e,d,c       │
│  7   │ 0x07     │ 0x07  │ a,b,c             │
│  8   │ 0x7F     │ 0x7F  │ All segments      │
│  9   │ 0x6F     │ 0x6F  │ a,b,c,d,f,g       │
│ OFF  │ 0x00     │ 0x00  │ None              │
└──────┴──────────┴───────┴───────────────────┘

Bit positions: gfedcba (g=MSB, a=LSB)
  Bit 6: g (middle)
  Bit 5: f (top-left)
  Bit 4: e (bottom-left)
  Bit 3: d (bottom)
  Bit 2: c (bottom-right)
  Bit 1: b (top-right)
  Bit 0: a (top)
```

### Dice Digits (1-6) Visual:

```
Digit 1:              Digit 2:              Digit 3:
 ┌───────┐             ┌─── a ─┐             ┌─── a ─┐
 │       │             │       │             │       │
 │       b              OFF    b              OFF    b
 │       │             │       │             │       │
 ├───────┤             ├─── g ─┤             ├─── g ─┤
 │       │             │       │             │       │
 │       c              e      │              OFF    c
 │       │             │       │             │       │
 └───────┘             └─── d ─┘             └─── d ─┘
 0x06 = b,c           0x5B = a,b,d,e,g      0x4F = a,b,c,d,g

Digit 4:              Digit 5:              Digit 6:
 ┌───────┐             ┌─── a ─┐             ┌─── a ─┐
 │       │             │       │             │       │
 f       b              f      │              f      │
 │       │             │       │             │       │
 ├─── g ─┤             ├─── g ─┤             ├─── g ─┤
 │       │             │       │             │       │
 │       c              OFF    c              e      c
 │       │             │       │             │       │
 └───────┘             └─── d ─┘             └─── d ─┘
 0x66 = f,g,b,c       0x6D = a,f,g,c,d      0x7D = a,c,d,e,f,g
```

---

## 🔀 74HC595 Shift Register

### What is a Shift Register?

A **shift register** converts serial data (1 bit at a time) into parallel data (8 bits simultaneously). The 74HC595 allows us to control 8 outputs using only 3 GPIO pins!

```
Pin Efficiency:
  Without shift register:
    7 segments + 1 cathode = 8 pins needed ❌
    
  With 74HC595:
    3 pins (data, clock, latch) ✅
    Saves 5 GPIO pins!
```

### 74HC595 Pinout (DIP-16):

```
74HC595 IC:
        ┌─────────────┐
    QB  │1    ●    16│ VCC
    QC  │2        15│ QA
    QD  │3        14│ DS (Serial Data)
    QE  │4        13│ OE (Output Enable)
    QF  │5        12│ ST_CP (Latch/Storage Clock)
    QG  │6        11│ SH_CP (Shift Clock)
    QH  │7        10│ MR (Master Reset)
   GND  │8         9│ QH' (Serial Out)
        └─────────────┘

Pin Functions:
  QA-QH (15,1-7): Parallel outputs (to 7-seg segments)
  DS (14): Serial data input (from ATtiny PB4)
  SH_CP (11): Shift clock (from ATtiny PB2)
  ST_CP (12): Latch clock (from ATtiny PB3)
  OE (13): Output enable (tie to GND = always ON)
  MR (10): Master reset (tie to VCC = no reset)
  QH' (9): Serial output (for daisy-chaining)
```

### How 74HC595 Works:

```
Serial-to-Parallel Conversion:

Step 1: Load Serial Data (8 bits, one at a time)
  DS pin receives bit → SH_CP pulse → shift into register
  
  Example: Send 0x06 (digit 1 = b,c segments)
    Bit 7 (MSB): 0 → DS=LOW, pulse SH_CP
    Bit 6: 0 → DS=LOW, pulse SH_CP
    Bit 5: 0 → DS=LOW, pulse SH_CP
    Bit 4: 0 → DS=LOW, pulse SH_CP
    Bit 3: 0 → DS=LOW, pulse SH_CP
    Bit 2: 1 → DS=HIGH, pulse SH_CP (bit c)
    Bit 1: 1 → DS=HIGH, pulse SH_CP (bit b)
    Bit 0 (LSB): 0 → DS=LOW, pulse SH_CP
    
Step 2: Latch Data (update outputs)
  ST_CP (latch) LOW → HIGH pulse
  → Internal register copies to output register
  → QA-QH outputs update simultaneously!

Timing:
  SH_CP: Shift data in (8 pulses for 8 bits)
  ST_CP: Display data out (1 pulse to latch)
```

### Timing Diagram:

```
SH_CP (Shift Clock):
  ───┐   ┐   ┐   ┐   ┐   ┐   ┐   ┐
     └───┘   └───┘   └───┘   └───┘ ... (8 pulses)
     ▲   ▲   ▲   ▲   ▲   ▲   ▲   ▲
    Bit7 Bit6 Bit5 ... Bit1 Bit0

DS (Data):
  ──╱───╲───╱───╲───╱───╲───╱───╲─
    0   1   0   1   0   1   0   1  (example data)

ST_CP (Latch):
  ────────────────────────────┐
                              └───── (latch after 8 bits)
                              ▲
                         Outputs update!
```

### Arduino shiftOut() Function:

```cpp
shiftOut(dataPin, clockPin, MSBFIRST, value);
```

**Parameters:**
- `dataPin`: DS pin (serial data)
- `clockPin`: SH_CP pin (shift clock)
- `MSBFIRST`: Send most significant bit first
- `value`: 8-bit data to send

**What it does:**
```
Sends 8 bits automatically!
  1. Set DS to bit value (HIGH/LOW)
  2. Pulse SH_CP (LOW → HIGH → LOW)
  3. Repeat for all 8 bits
  4. You manually pulse ST_CP to latch
```

---

## 🔌 Circuit Diagram

### Complete System Circuit:

```
Electronic Dice Circuit:
┌──────────────────────────────────────────────────────────────┐
│                                                              │
│  Push Button                                                 │
│    ┌────┐                                                    │
│    │    │                                                    │
│  ──┤    ├── VCC                                              │
│    │    │                                                    │
│    └──┬─┘                                                    │
│       │                                                      │
│       ├──── ATtiny85 PB0 (Pin 5)                             │
│       │                                                      │
│      10kΩ (pull-down, optional)                              │
│       │                                                      │
│      GND                                                     │
│                                                              │
│         ATtiny85                    74HC595                  │
│      ┌────────┐                  ┌─────────────┐            │
│      │1  ●  8├─ VCC              │   74HC595   │            │
│ PB3 ─┤2     7├─ PB2              │             │            │
│(Latch)│      │ (Clock)        VCC│16        15│QA → a      │
│ PB4 ─┤3     6├─ PB1          QB  │1         14│DS ← PB4    │
│(Data) │      │ (LED/Cathode) QC  │2         13│OE → GND    │
│      │4     5├─ PB0 (Button) QD  │3         12│ST_CP←PB3   │
│      └──┬─────┘                QE │4         11│SH_CP←PB2   │
│      GND│ VCC                  QF │5         10│MR → VCC    │
│         │  │                   QG │6          9│QH' (NC)    │
│         │  │                   QH │7          8│GND         │
│         │  │                      └─────────────┘            │
│         │  │                        │  │  │  │  │  │  │     │
│         │  │                       QA QB QC QD QE QF QG     │
│         │  │                        │  │  │  │  │  │  │     │
│         │  │                       330Ω (×7 resistors)      │
│         │  │                        │  │  │  │  │  │  │     │
│         │  │         7-Segment Display (Common Cathode)     │
│         │  │      ┌──────────────────────────────┐          │
│         │  │      │       ┌─── a ───┐            │          │
│         │  │      │       │         │            │          │
│         │  │      │       f         b            │          │
│         │  │      │       │         │            │          │
│         │  │      │       ├─── g ───┤            │          │
│         │  │      │       │         │            │          │
│         │  │      │       e         c            │          │
│         │  │      │       │         │            │          │
│         │  │      │       └─── d ───┘            │          │
│         │  │      │                              │          │
│         │  │      │  Pins: a b c d e f g dp      │          │
│         │  │      └───┬──┬──┬──┬──┬──┬──┬──┬────┘          │
│         │  │          │  │  │  │  │  │  │  │               │
│         │  │         QA QB QC QD QE QF QG (from 74HC595)   │
│         │  │                              │                 │
│         │  │                    Common Cathode              │
│         │  │                              │                 │
│         │  └──────────────────────────── 330Ω              │
│         │                                 │                 │
│         │                            ATtiny PB1             │
│         │                                                   │
│        GND ──────────────────────────────────────────────  │
│                                                              │
│        VCC (+5V) ────────────────────────────────────────  │
└──────────────────────────────────────────────────────────────┘

Power Supply:
  • USB 5V or 3× AA batteries (4.5V)
  • 0.1µF decoupling caps near ICs (optional)
```

### Breadboard Layout:

```
Breadboard View:
┌─────────────────────────────────────────────────┐
│  ═══════════════════════════════════════════    │ +5V Rail
│  ───────────────────────────────────────────    │ GND Rail
│                                                 │
│  [Button]   [ATtiny85]    [74HC595]            │
│     ↓          DIP-8        DIP-16              │
│    +5V                                          │
│     │                                           │
│    PB0 ───────────┐                             │
│              10kΩ │                             │
│                  GND                            │
│                                                 │
│  PB2 (Pin 7) ───→ SH_CP (Pin 11)               │
│  PB3 (Pin 2) ───→ ST_CP (Pin 12)               │
│  PB4 (Pin 3) ───→ DS (Pin 14)                  │
│                                                 │
│  74HC595 outputs:                               │
│  QA-QG → 330Ω → 7-segment a-g                   │
│                                                 │
│  7-Segment Common Cathode:                      │
│  → 330Ω → PB1 (Pin 6) → controls display       │
│                                                 │
│  ═══════════════════════════════════════════    │
│  ───────────────────────────────────────────    │
└─────────────────────────────────────────────────┘
```

---

## 📍 Pin Configuration

### Complete Pin Mapping:

| ATtiny85 | Physical Pin | Function | Connected To | Signal Type |
|----------|-------------|----------|--------------|-------------|
| **RESET** | Pin 1 | Reset (pull-up) | Not connected | - |
| **PB3** | Pin 2 | Output | 74HC595 Pin 12 (ST_CP) | Latch clock |
| **PB4** | Pin 3 | Output | 74HC595 Pin 14 (DS) | Serial data |
| **GND** | Pin 4 | Ground | Common GND | Power |
| **PB0** | Pin 5 | Input | Push button + 10kΩ pull-down | Digital input |
| **PB1** | Pin 6 | Output | 7-seg cathode via 330Ω | Display enable |
| **PB2** | Pin 7 | Output | 74HC595 Pin 11 (SH_CP) | Shift clock |
| **VCC** | Pin 8 | Power | +5V | Power |

### 74HC595 to 7-Segment Mapping:

| 74HC595 Output | Pin | 7-Segment | Segment Name |
|----------------|-----|-----------|--------------|
| QA | 15 | a | Top |
| QB | 1 | b | Top-right |
| QC | 2 | c | Bottom-right |
| QD | 3 | d | Bottom |
| QE | 4 | e | Bottom-left |
| QF | 5 | f | Top-left |
| QG | 6 | g | Middle |
| QH | 7 | (not used) | - |

### Arduino Pin Names vs ATtiny85:

```
Code Variable      ATtiny85 Pin    Connected To
────────────────────────────────────────────────
const int buttonPin = 0;  PB0 (Pin 5)  → Button
const int ledPin = 1;     PB1 (Pin 6)  → Cathode
const int clockPin = 2;   PB2 (Pin 7)  → SH_CP
const int latchPin = 3;   PB3 (Pin 2)  → ST_CP
const int dataPin = 4;    PB4 (Pin 3)  → DS
```

---

## ⚙️ Working Principle

### System Operation Flow:

```
┌────────────────────────────────────────────────┐
│           DICE SYSTEM OPERATION                │
└────────────────────────────────────────────────┘
                    │
              Power ON
                    │
                    ▼
         ┌──────────────────┐
         │ ATtiny85 Setup   │
         │ • Configure pins │
         │ • Init display   │
         └─────────┬────────┘
                   │
                   ▼
         ┌──────────────────┐
         │ Welcome Animation│
         │ • Show "8" (all) │
         │ • Delay 3 sec    │
         │ • Show blank     │
         │ • Show "0"       │
         └─────────┬────────┘
                   │
                   ▼
         ┌──────────────────┐
         │ Wait for Button  │ ◄──────────┐
         │ digitalRead(PB0) │            │
         └─────────┬────────┘            │
                   │                     │
            NO ←───┴───→ YES             │
            │           │                │
            │           ▼                │
            │  ┌──────────────────┐     │
            │  │ Button Pressed!  │     │
            │  └─────────┬────────┘     │
            │            │               │
            │            ▼               │
            │  ┌──────────────────┐     │
            │  │ Display OFF      │     │
            │  │ LEDwrite(7)      │     │
            │  └─────────┬────────┘     │
            │            │               │
            │            ▼               │
            │  ┌──────────────────┐     │
            │  │ Generate Random  │     │
            │  │ RND() → 1-6      │     │
            │  │ Use analog noise │     │
            │  └─────────┬────────┘     │
            │            │               │
            │            ▼               │
            │  ┌──────────────────┐     │
            │  │ Roll Animation   │     │
            │  │ rollDice(2)      │     │
            │  │ 0→1→2→3→4→5→6   │     │
            │  │ (repeat 2 times) │     │
            │  └─────────┬────────┘     │
            │            │               │
            │            ▼               │
            │  ┌──────────────────┐     │
            │  │ Display OFF      │     │
            │  │ (brief pause)    │     │
            │  └─────────┬────────┘     │
            │            │               │
            │            ▼               │
            │  ┌──────────────────┐     │
            │  │ Show Result      │     │
            │  │ LEDwrite(digit)  │     │
            │  │ (1-6 displayed)  │     │
            │  └─────────┬────────┘     │
            │            │               │
            └────────────┼───────────────┘
                         │
                         └─────────────────┘
                    (Wait for next press)
```

### Step-by-Step Explanation:

#### **Step 1: Display Digit Function**

```cpp
void LEDwrite(int data) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit[data]);
  digitalWrite(latchPin, HIGH);
}
```

**Process:**

1. **Latch LOW**: Prepare to receive new data
   - `digitalWrite(latchPin, LOW);`
   - Output register holds old value
   
2. **Shift Data**: Send 8 bits serially
   - `shiftOut(dataPin, clockPin, MSBFIRST, digit[data]);`
   - MSBFIRST = Most Significant Bit first
   - Sends pattern from `digit[]` array
   
3. **Latch HIGH**: Update outputs
   - `digitalWrite(latchPin, HIGH);`
   - 7-segment display instantly shows new digit

**Example: Display digit "1"**
```
digit[1] = 0x06 = 0b00000110
           gfedcba
           0000110 → segments b,c ON

LEDwrite(1):
  1. Latch LOW
  2. Send: 0,0,0,0,0,1,1,0 (8 clock pulses)
  3. Latch HIGH → Display shows "1" ✅
```

#### **Step 2: Random Number Generation**

```cpp
int RND() {
  int seed = 0;
  int digit = 0;
  while(digit > 6 || digit <= 0) {
    seed = (seed * 53) + 21;
    digit = seed % 6;
    randomSeed(analogRead(PB5));
    seed = random(50) + digit;
    digit += seed;
  }
  return digit;  // Returns 1-6
}
```

**Random Generation Logic:**

```
Why analog noise?
  PB5 (floating pin) reads electrical noise
  Noise is unpredictable = true randomness!

Process:
  1. Read analog noise: analogRead(PB5)
     → Returns 0-1023 (random)
  
  2. Seed random generator:
     randomSeed(noise_value)
  
  3. Generate number:
     random(50) → 0-49
     Add modulo: digit = (seed % 6) + more_random
  
  4. Loop until 1 ≤ digit ≤ 6
     Ensures valid dice range
  
  5. Return digit (1-6)

Each button press → different analog reading → different result!
```

#### **Step 3: Roll Animation**

```cpp
void rollDice(int times) {
  for (int i = 0; i < times; i++) {
    LEDwrite(0); d250;  // 0 for 250ms
    LEDwrite(1); d250;  // 1 for 250ms
    LEDwrite(2); d250;  // 2 for 250ms
    LEDwrite(3); d250;  // 3 for 250ms
    LEDwrite(4); d250;  // 4 for 250ms
    LEDwrite(5); d250;  // 5 for 250ms
    LEDwrite(6); d250;  // 6 for 250ms
  }
}
```

**Animation Sequence:**

```
rollDice(2) → Repeats 2 times

Round 1:
  0 → 250ms
  1 → 250ms
  2 → 250ms
  3 → 250ms
  4 → 250ms
  5 → 250ms
  6 → 250ms
  (Total: 1.75 seconds)

Round 2:
  0 → 250ms
  1 → 250ms
  ...
  6 → 250ms
  (Total: 1.75 seconds)

Total animation: 3.5 seconds
Gives realistic "rolling" effect!
```

**Visual Timeline:**

```
Time:  0ms  250  500  750  1000 1250 1500 1750 2000...
Display: 0 → 1 → 2 → 3 → 4 → 5 → 6 → 0 → 1 ...
```

#### **Step 4: Button Detection**

```cpp
void loop() {
  int btn = digitalRead(buttonPin);
  if (btn == HIGH) {
    // Button pressed!
    LEDwrite(7);  // Display OFF
    int digit = RND();  // Get random 1-6
    rollDice(2);  // Animation
    LEDwrite(7);  // OFF again
    LEDwrite(digit);  // Show result
  }
}
```

**Button Logic:**

```
Button Circuit:
  VCC ──┐
        │
      Button
        │
        ├── PB0 (ATtiny)
        │
       10kΩ
        │
       GND

Not pressed: PB0 = LOW (pulled down by 10kΩ)
Pressed:     PB0 = HIGH (connected to VCC)

Software reads:
  digitalRead(PB0) → HIGH = button pressed ✅
```

---

## 💻 Code Explanation

### Complete Code:

```cpp
/*
 * Project 16: Electronic Dice
 * ATtiny85 + 74HC595 + 7-Segment Display
 */

#define segDISPLAY CATHODE  // Common Cathode type
#define d250 delay(250);    // Delay macro

// Pin definitions
const int buttonPin = 0;  // PB0 (Pin 5)
const int ledPin = 1;     // PB1 (Pin 6)
const int clockPin = 2;   // PB2 (Pin 7) → SH_CP
const int latchPin = 3;   // PB3 (Pin 2) → ST_CP
const int dataPin = 4;    // PB4 (Pin 3) → DS

// 7-segment patterns (gfedcba)
const byte digit[] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000000, // OFF (blank)
  B01111111  // 8 (all segments)
};

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  #ifdef segDISPLAY
    digitalWrite(ledPin, LOW);   // CC: cathode to GND
  #else
    digitalWrite(ledPin, HIGH);  // CA: anode to VCC
  #endif

  // Welcome animation
  LEDwrite(8);  // All segments ON
  delay(3000);  // 3 seconds
  LEDwrite(7);  // OFF
  d250;
  LEDwrite(0);  // Show 0
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
  int seed = 0;
  int digit = 0;
  while(digit > 6 || digit <= 0) {
    seed = (seed * 53) + 21;
    digit = seed % 6;
    randomSeed(analogRead(PB5));
    seed = random(50) + digit;
    digit += seed;
  }
  return digit;  // 1-6
}

void rollDice(int times) {
  for (int i = 0; i < times; i++) {
    LEDwrite(0); d250;
    LEDwrite(1); d250;
    LEDwrite(2); d250;
    LEDwrite(3); d250;
    LEDwrite(4); d250;
    LEDwrite(5); d250;
    LEDwrite(6); d250;
  }
}

void loop() {
  int btn = digitalRead(buttonPin);
  if (btn == HIGH) {
    LEDwrite(7);  // Display OFF
    d250;
    int digit = RND();  // Get random number
    rollDice(2);  // Animation (2 rounds)
    LEDwrite(7);  // OFF
    d250;
    LEDwrite(digit);  // Show result
  }
}
```

### Code Breakdown:

#### **Preprocessor Directives:**

```cpp
#define segDISPLAY CATHODE
#define d250 delay(250);
```

**Explanation:**
- `segDISPLAY CATHODE`: Defines display type (Common Cathode)
  - If Common Anode, remove this line
- `d250`: Shorthand for `delay(250)` to save typing

#### **Pin Definitions:**

```cpp
const int buttonPin = 0;  // PB0
const int ledPin = 1;     // PB1
const int clockPin = 2;   // PB2
const int latchPin = 3;   // PB3
const int dataPin = 4;    // PB4
```

**Pin Roles:**
- `buttonPin`: Detects button press
- `ledPin`: Controls display cathode (enable/disable)
- `clockPin`: Shift clock (SH_CP) for 74HC595
- `latchPin`: Latch clock (ST_CP) for 74HC595
- `dataPin`: Serial data (DS) for 74HC595

#### **Segment Patterns Array:**

```cpp
const byte digit[] = {
  B00111111, // 0
  B00000110, // 1
  // ... etc
};
```

**Binary Format Explanation:**

```
B00000110 = digit "1"
  ║║║║║║║║
  ║║║║║║║╚══ a (top) = 0 (OFF)
  ║║║║║║╚═══ b (top-right) = 1 (ON) ✓
  ║║║║║╚════ c (bottom-right) = 1 (ON) ✓
  ║║║║╚═════ d (bottom) = 0 (OFF)
  ║║║╚══════ e (bottom-left) = 0 (OFF)
  ║║╚═══════ f (top-left) = 0 (OFF)
  ║╚════════ g (middle) = 0 (OFF)
  ╚═════════ (unused)

Result: Only segments b and c light up → displays "1"
```

#### **Setup Function:**

```cpp
void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  #ifdef segDISPLAY
    digitalWrite(ledPin, LOW);
  #else
    digitalWrite(ledPin, HIGH);
  #endif

  LEDwrite(8);
  delay(3000);
  LEDwrite(7);
  d250;
  LEDwrite(0);
}
```

**Initialization Sequence:**

1. Configure all pins as INPUT/OUTPUT
2. Set cathode pin based on display type:
   - CC: LOW (connected to GND)
   - CA: HIGH (connected to VCC)
3. Welcome animation:
   - Show "8" (all segments) for 3 seconds
   - Blank display (OFF)
   - Show "0" (ready state)

#### **Conditional Compilation:**

```cpp
#ifdef segDISPLAY
  // Code for Common Cathode
#else
  // Code for Common Anode
#endif
```

**Why needed?**
- Common Cathode: Send pattern directly (1=ON)
- Common Anode: Send inverted pattern (~pattern, 0=ON)

#### **Loop Function:**

```cpp
void loop() {
  int btn = digitalRead(buttonPin);
  if (btn == HIGH) {
    LEDwrite(7);
    d250;
    int digit = RND();
    rollDice(2);
    LEDwrite(7);
    d250;
    LEDwrite(digit);
  }
}
```

**Execution Flow:**

```
Infinite loop:
  1. Check button: digitalRead(PB0)
  2. If HIGH (pressed):
     a. Display OFF
     b. Generate random (1-6)
     c. Roll animation (2 cycles)
     d. Display OFF briefly
     e. Show random result
  3. Loop back to step 1

No button press: Just keeps checking
```

---

## 🎬 Dice Animation

### Animation Customization:

```cpp
// Faster animation (100ms per digit)
#define d250 delay(100);

// Slower animation (500ms per digit)
#define d250 delay(500);

// More rounds (3 cycles instead of 2)
rollDice(3);

// Reverse animation (6→1)
void rollDice(int times) {
  for (int i = 0; i < times; i++) {
    LEDwrite(6); d250;
    LEDwrite(5); d250;
    LEDwrite(4); d250;
    LEDwrite(3); d250;
    LEDwrite(2); d250;
    LEDwrite(1); d250;
  }
}

// Bidirectional animation (1→6→1)
void rollDice(int times) {
  for (int i = 0; i < times; i++) {
    for(int j=1; j<=6; j++) {
      LEDwrite(j); d250;
    }
    for(int j=5; j>=1; j--) {
      LEDwrite(j); d250;
    }
  }
}
```

---

## 🎲 Random Number Generation

### Why Analog Noise?

```
Problem:
  Software random() without seed is predictable!
  Same sequence every time = not random ❌

Solution:
  Use analog noise from floating pin
  Electrical noise is truly random ✅

How it works:
  1. PB5 (A1) not connected → picks up noise
  2. analogRead(PB5) → returns 0-1023 (varies)
  3. Use as seed: randomSeed(noise_value)
  4. Now random() is truly random!

Example readings (PB5 floating):
  Button press 1: 342
  Button press 2: 871
  Button press 3: 129
  Different every time!
```

### Alternative Random Methods:

```cpp
// Method 1: Use millis() as seed
randomSeed(millis());
int result = random(1, 7);  // 1-6

// Method 2: XOR multiple analog pins
int seed = analogRead(A1) ^ analogRead(A2);
randomSeed(seed);

// Method 3: External entropy (temperature sensor)
randomSeed(analogRead(tempSensorPin) * millis());
```

---

## 🐛 Troubleshooting

### Common Issues:

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| **No display** | No power | Check VCC/GND connections |
| | 74HC595 not powered | Verify Pin 16=VCC, Pin 8=GND |
| | Wrong display type | Verify Common Cathode (not CA) |
| **Wrong segments** | Incorrect wiring | Check QA→a, QB→b mapping |
| | Inverted pattern | Toggle `#define segDISPLAY` |
| **Button not working** | No pull-down resistor | Add 10kΩ to GND |
| | Wrong pin | Verify PB0 (Pin 5) connection |
| **Dim display** | Resistors too high | Use 220Ω instead of 330Ω |
| | Low power supply | Use 5V instead of 3V |
| **Always shows same number** | No randomness | Check PB5 floating (not connected) |
| | Random seed issue | Re-upload code |
| **Flickering** | Loose wires | Secure all connections |
| | Power instability | Add 0.1µF capacitor |

### Diagnostic Code:

```cpp
// Test all digits 0-6 in sequence
void testDisplay() {
  for(int i=0; i<=6; i++) {
    LEDwrite(i);
    delay(1000);  // 1 sec per digit
  }
}

// Call in setup():
testDisplay();

// Expected: 0→1→2→3→4→5→6 displayed
```

---

## 🚀 Applications

### 1. Board Game Dice

```
Replace physical dice for:
  • Monopoly, Ludo, Snakes & Ladders
  • Card games requiring random selection
  • Multiplayer games
```

### 2. Decision Maker

```
Assign options to numbers 1-6:
  1 = Option A
  2 = Option B
  ...
Press button for random choice!
```

### 3. Lottery Number Generator

```
Modify code to show 0-9 instead of 1-6:
  Perfect for random lottery picks
```

### 4. Educational Tool

```
Teach concepts:
  • Shift registers
  • Random number generation
  • 7-segment displays
  • Embedded systems
```

### 5. Multiple Dice

```
Add second 74HC595 + 7-segment:
  • Roll two dice simultaneously
  • Display sum or individual values
  • Craps game simulator
```

---

## 📚 Learning Outcomes

### Skills Gained:

```
✅ 7-segment display interfacing
✅ 74HC595 shift register control
✅ Serial-to-parallel conversion
✅ ATtiny85 GPIO programming
✅ Button input with debouncing
✅ Random number generation
✅ Animation and timing control
✅ Binary number representation
✅ Low-power embedded design
✅ Pin-efficient circuit design
```

### Advanced Concepts:

- **Shift Registers**: Serial data transmission reduces pin count
- **Multiplexing**: Control multiple outputs with few pins
- **Entropy Sources**: Analog noise for true randomness
- **Display Encoding**: Binary patterns for 7-segment
- **State Machines**: Button press triggers sequence

---

## 🎯 Project Challenges

### Challenge 1: Add Second Dice

```cpp
// Cascade two 74HC595 chips
// Display two digits side-by-side
// Show sum of both dice
```

### Challenge 2: Sound Effects

```cpp
// Add piezo buzzer
// Play tone during roll animation
// Different tone for final result
```

### Challenge 3: Score Memory

```cpp
// Use EEPROM to store last 10 rolls
// Display stats on button long-press
```

### Challenge 4: Adjustable Speed

```cpp
// Add potentiometer
// Control animation speed (100ms-1s)
// Faster = exciting, slower = dramatic
```

### Challenge 5: LED Indicators

```cpp
// Add 6 LEDs (one per dice value)
// Light up corresponding LED
// Winning number (6) = different color
```

---

## 📖 References

- [74HC595 Datasheet](https://www.ti.com/lit/ds/symlink/sn74hc595.pdf)
- [ATtiny85 Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf)
- [7-Segment Display Guide](https://www.electronics-tutorials.ws/blog/7-segment-display-tutorial.html)

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

1. **Test 74HC595 first** - Verify shift register with simple LED test
2. **Check display type** - Common Cathode vs Common Anode
3. **Verify wiring** - QA→a, QB→b, QC→c mapping correct
4. **Use fresh battery** - 5V recommended for bright display
5. **Add pull-down resistor** - 10kΩ on button prevents false triggers
6. **Float PB5 pin** - Don't connect A1 for true randomness
7. **Secure breadboard** - Loose shift register connections cause issues

**Good luck building your electronic dice! 🎲✨🎉**
