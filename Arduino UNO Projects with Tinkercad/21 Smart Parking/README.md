# 🚗 Smart Parking System with Arduino

![Arduino](https://img.shields.io/badge/Arduino-UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Sensors](https://img.shields.io/badge/IR_Sensors-4x-red?style=for-the-badge)
![Servo](https://img.shields.io/badge/Servo-2x-blue?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Intermediate-orange?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Complete-success?style=for-the-badge)

A comprehensive **Smart Parking System** that uses IR sensors to detect vehicle entry/exit and parking slot occupancy, servo motors to control automated gates, and a 16×2 LCD display to show real-time parking availability. This project demonstrates automation, sensor integration, and multi-component coordination.

---

## 📑 Table of Contents

- [Overview](#-overview)
- [Learning Objectives](#-learning-objectives)
- [System Architecture](#-system-architecture)
- [Components Required](#-components-required)
- [IR Sensor Theory](#-ir-sensor-theory)
- [Servo Motor Control](#-servo-motor-control)
- [Circuit Diagram](#-circuit-diagram)
- [Circuit Connections](#-circuit-connections)
- [Code Explanation](#-code-explanation)
- [How It Works](#-how-it-works)
- [System States](#-system-states)
- [LCD Display Modes](#-lcd-display-modes)
- [Troubleshooting](#-troubleshooting)
- [Real-World Applications](#-real-world-applications)
- [Project Extensions](#-project-extensions)
- [Challenges](#-challenges)
- [Author](#-author)

---

## 🎯 Overview

This **Smart Parking System** automates parking lot management by:
- **Detecting vehicles** at entry and exit points using IR sensors
- **Monitoring parking slots** (2 slots) for occupancy status
- **Controlling automated gates** with servo motors
- **Displaying availability** on a 16×2 LCD in real-time
- **Providing debugging** through Serial Monitor

### Key Features:
- ✅ 4 IR sensors (entry, exit, slot 1, slot 2)
- ✅ 2 servo-controlled gates (entry & exit)
- ✅ Real-time LCD status display
- ✅ Automatic gate opening/closing
- ✅ Slot occupancy detection
- ✅ Serial Monitor debugging
- ✅ Foundation for IoT parking systems

---

## 🎓 Learning Objectives

By completing this project, you will learn:

| Concept | Description | Practical Application |
|---------|-------------|----------------------|
| **IR Sensor Logic** | Obstacle detection with digital output | Proximity sensing, automation |
| **Servo Control** | Precise angular positioning | Automated gates, robotic arms |
| **LCD Interfacing** | Character display in 4-bit mode | User interfaces, information panels |
| **Multi-Sensor Systems** | Coordinating multiple inputs | Complex automation projects |
| **State Management** | Tracking system conditions | FSM (Finite State Machines) |
| **Real-Time Display** | Updating user feedback continuously | Monitoring systems |

---

## 🏗️ System Architecture

### System Block Diagram:

```
┌─────────────────────────────────────────────────────┐
│                   SMART PARKING SYSTEM               │
└─────────────────────────────────────────────────────┘
                          │
        ┌─────────────────┼─────────────────┐
        │                 │                 │
        ▼                 ▼                 ▼
   ┌─────────┐      ┌─────────┐      ┌─────────┐
   │ SENSORS │      │ ARDUINO │      │ OUTPUTS │
   └─────────┘      │   UNO   │      └─────────┘
        │           └─────────┘            │
        │                 │                │
    ┌───┴────┐       ┌────┴────┐      ┌───┴────┐
    │ IR×4   │ ───→  │ Process │ ───→ │ Servo×2│
    │ Slot×2 │       │ Logic   │      │ LCD    │
    └────────┘       └─────────┘      └────────┘

Data Flow:
  IR Sensors → Arduino → Decision Logic → Servo + LCD
```

### Functional Components:

```
INPUT SENSORS:
┌──────────────────────────────────┐
│ • Entry IR (D6)                  │ → Detects arriving vehicles
│ • Exit IR (D13)                  │ → Detects departing vehicles
│ • Slot 1 IR (D7)                 │ → Monitors parking slot 1
│ • Slot 2 IR (D8)                 │ → Monitors parking slot 2
└──────────────────────────────────┘

PROCESSING:
┌──────────────────────────────────┐
│ • Arduino UNO                    │ → Central controller
│ • Logic algorithms               │ → Decision making
│ • State tracking                 │ → System status
└──────────────────────────────────┘

OUTPUTS:
┌──────────────────────────────────┐
│ • Entry Servo (D9)               │ → Entry gate control
│ • Exit Servo (D10)               │ → Exit gate control
│ • 16×2 LCD (D2-D12)              │ → Status display
│ • Serial Monitor                 │ → Debugging output
└──────────────────────────────────┘
```

---

## 🧰 Components Required

| Component | Quantity | Specifications | Purpose |
|-----------|----------|----------------|---------|
| Arduino UNO | 1 | ATmega328P, 5V logic | Microcontroller |
| IR Sensor Module | 4 | Digital output, adjustable sensitivity | Vehicle/slot detection |
| Servo Motor | 2 | SG90 or similar, 0-180° | Gate automation |
| 16×2 LCD Display | 1 | HD44780 compatible, 4-bit mode | Status display |
| 10kΩ Potentiometer | 1 | For LCD contrast | Display adjustment |
| Breadboard | 1-2 | 830 tie-points | Prototyping |
| Jumper Wires | ~40 | Male-to-Male | Connections |
| USB Cable | 1 | Type A to Type B | Programming & Power |
| 5V Power Supply | 1 (optional) | 2A minimum for servos | External power |

### 💰 Estimated Cost: ৳1500-2500 ($18-30 USD)

---

## 🔬 IR Sensor Theory

### What is an IR Sensor Module?

An **IR (Infrared) sensor module** consists of:
1. **IR LED (Transmitter)** - Emits infrared light
2. **Photodiode (Receiver)** - Detects reflected IR light
3. **Comparator Circuit** - Converts analog signal to digital output
4. **Potentiometer** - Adjusts detection sensitivity

### IR Sensor Working Principle:

```
IR Sensor Module Components:
┌─────────────────────────────────────┐
│                                     │
│   IR LED          Photodiode       │
│   (Emitter)       (Receiver)       │
│      │                │             │
│      └───→ IR Light ──┘            │
│             ↓ ↑ (Reflected)        │
│                                     │
│   [Comparator] → Digital OUT       │
│   [Potentiometer] (Sensitivity)    │
│                                     │
└─────────────────────────────────────┘

Operation:
  1. IR LED continuously emits infrared light
  2. When object present: Light reflects back
  3. Photodiode receives reflected light
  4. Comparator outputs:
     - HIGH (5V) = No object detected
     - LOW (0V) = Object detected
```

### IR Sensor Pinout:

```
IR Sensor Module (Top View):
┌─────────────────────────┐
│   [●] [●] [●]           │
│   VCC OUT GND           │
│                         │
│   (LED)    (Photodiode) │
│     ●          ●        │
│                         │
│  [Potentiometer]        │
│        ╰──╮             │
└───────────┴─────────────┘

Pin Connections:
  VCC → Arduino 5V
  OUT → Arduino Digital Pin (D6, D7, D8, D13)
  GND → Arduino GND
```

### IR Sensor Characteristics:

| Parameter | Value | Notes |
|-----------|-------|-------|
| Operating Voltage | 3.3V - 5V | Compatible with Arduino |
| Detection Range | 2-30 cm | Adjustable with potentiometer |
| Output Type | Digital (TTL) | HIGH/LOW only |
| Detection Logic | Active LOW | LOW = Object detected |
| Response Time | <1 ms | Very fast detection |
| Beam Angle | ~35° | Cone-shaped detection area |
| Current Draw | ~20 mA | Low power consumption |

### Detection Range Adjustment:

```
Potentiometer (Top View):
    ┌───────┐
    │   ↻   │ ← Turn clockwise: Increase range
    └───┬───┘   Turn counter-clockwise: Decrease range
        │
     Sensitivity

Testing Detection:
  1. Place object 5 cm away
  2. Adjust potentiometer slowly
  3. LED on module lights when detecting
  4. Verify digital output with multimeter
     - No object: ~5V (HIGH)
     - Object present: ~0V (LOW)
```

---

## ⚙️ Servo Motor Control

### SG90 Servo Motor Specifications:

| Parameter | Value | Description |
|-----------|-------|-------------|
| Operating Voltage | 4.8V - 6V | Powered by Arduino 5V |
| Rotation Range | 0° - 180° | Half rotation |
| Torque | 1.8 kg·cm @ 5V | Sufficient for lightweight gates |
| Speed | 0.1 s/60° @ 5V | Fast response |
| Control Type | PWM signal | 50 Hz, 1-2 ms pulse width |
| Current Draw | 100-250 mA | Peak during movement |
| Weight | 9 grams | Lightweight |

### Servo Control Theory:

```
PWM Signal for Servo Control:
┌────────────────────────────────────┐
│ Pulse Width → Angle Position      │
│                                    │
│ 1.0 ms pulse → 0° (closed gate)   │
│ 1.5 ms pulse → 90° (mid position) │
│ 2.0 ms pulse → 180° (open gate)   │
│                                    │
│ PWM Frequency: 50 Hz (20 ms period)│
└────────────────────────────────────┘

Servo.h Library Functions:
  servo.attach(pin)      → Initialize servo on pin
  servo.write(angle)     → Set position (0-180°)
  servo.read()           → Get current position
  servo.detach()         → Release servo pin
```

### Gate Position States:

```
Entry/Exit Gate Positions:
┌──────────────────────────────────────┐
│                                      │
│  Closed (0°):        Open (90°):    │
│                                      │
│      │                    ────       │
│      │                                │
│      │  Gate Arm          Gate Arm   │
│      │                    (Vertical  │
│      │ (Horizontal)        raised)   │
│    ──┴──                 ──┴──       │
│    Servo                 Servo       │
│                                      │
└──────────────────────────────────────┘

Arduino Code:
  servo.write(0);    // Close gate (horizontal)
  servo.write(90);   // Open gate (vertical)
```

---

## 📐 Circuit Diagram

### Complete System Schematic:

```
                        SMART PARKING SYSTEM
┌─────────────────────────────────────────────────────────────────┐
│                         Arduino UNO                              │
│  ┌──────────────────────────────────────────────┐               │
│  │                                              │               │
│  │  DIGITAL PINS:                               │               │
│  │    D2  ●────────────────────────────────────┼──→ LCD D7     │
│  │    D3  ●────────────────────────────────────┼──→ LCD D6     │
│  │    D4  ●────────────────────────────────────┼──→ LCD D5     │
│  │    D5  ●────────────────────────────────────┼──→ LCD D4     │
│  │    D6  ●──────────┐                         │               │
│  │    D7  ●──────┐   │                         │               │
│  │    D8  ●────┐ │   │                         │               │
│  │    D9  ●──┐ │ │   │                         │               │
│  │   D10  ●┐ │ │ │   │                         │               │
│  │   D11  ●┼─┼─┼─┼───┼─────────────────────────┼──→ LCD EN     │
│  │   D12  ●┼─┼─┼─┼───┼─────────────────────────┼──→ LCD RS     │
│  │   D13  ●┼─┼─┼─┼───┼──┐                      │               │
│  │        │ │ │ │ │   │  │                     │               │
│  │   5V   ●┼─┼─┼─┼───┼──┼───── Power Rails ────┤               │
│  │   GND  ●┼─┼─┼─┼───┼──┼───── Ground ─────────┤               │
│  └─────────┼─┼─┼─┼───┼──┼──────────────────────┘               │
└────────────┼─┼─┼─┼───┼──┼─────────────────────────────────────┘
             │ │ │ │   │  │
             ↓ ↓ ↓ ↓   ↓  ↓
      ┌──────┘ │ │ │   │  └──────┐
      │        │ │ │   │         │
   Exit      Entry│ │   │      Exit
   Servo     Servo│ │   │       IR
   (D10)     (D9) │ │   │      (D13)
                  │ │   │
           ┌──────┘ │   └──────┐
           │        │          │
         Slot2    Slot1      Entry
          IR       IR          IR
         (D8)     (D7)        (D6)


IR SENSORS (×4):
┌────────────────────────────────────┐
│ Entry IR (D6)                      │
│  VCC → 5V                          │
│  OUT → D6                          │
│  GND → GND                         │
├────────────────────────────────────┤
│ Slot 1 IR (D7)                     │
│  VCC → 5V                          │
│  OUT → D7                          │
│  GND → GND                         │
├────────────────────────────────────┤
│ Slot 2 IR (D8)                     │
│  VCC → 5V                          │
│  OUT → D8                          │
│  GND → GND                         │
├────────────────────────────────────┤
│ Exit IR (D13)                      │
│  VCC → 5V                          │
│  OUT → D13                         │
│  GND → GND                         │
└────────────────────────────────────┘

SERVO MOTORS (×2):
┌────────────────────────────────────┐
│ Entry Servo (D9)                   │
│  Brown  → GND                      │
│  Red    → 5V                       │
│  Orange → D9                       │
├────────────────────────────────────┤
│ Exit Servo (D10)                   │
│  Brown  → GND                      │
│  Red    → 5V                       │
│  Orange → D10                      │
└────────────────────────────────────┘

16×2 LCD DISPLAY:
┌────────────────────────────────────┐
│ VSS (1)  → GND                     │
│ VDD (2)  → 5V                      │
│ VO (3)   → Potentiometer (contrast)│
│ RS (4)   → D12                     │
│ RW (5)   → GND (write mode)        │
│ EN (6)   → D11                     │
│ D4 (11)  → D5                      │
│ D5 (12)  → D4                      │
│ D6 (13)  → D3                      │
│ D7 (14)  → D2                      │
│ LED+ (15)→ 5V (with 220Ω resistor) │
│ LED- (16)→ GND                     │
└────────────────────────────────────┘
```

### Physical Layout:

```
Breadboard View (Top):
┌───────────────────────────────────────────────────┐
│  Power Rails:                                     │
│  [+5V] ────────────────────────────────────       │
│  [GND] ────────────────────────────────────       │
│                                                   │
│  IR Sensors (4x):                                 │
│    [Entry]  [Exit]  [Slot1]  [Slot2]             │
│      D6      D13      D7       D8                 │
│                                                   │
│  Servos (2x):                                     │
│    Entry Gate ──→ D9                              │
│    Exit Gate  ──→ D10                             │
│                                                   │
│  LCD Display (16×2):                              │
│    RS→D12, EN→D11, D4-D7→D5-D2                    │
│    Contrast pot connected to VO                   │
│                                                   │
│  Arduino UNO mounted on breadboard                │
└───────────────────────────────────────────────────┘
```

---

## 🔌 Circuit Connections

### Detailed Pin Mapping Table:

**IR Sensors:**

| IR Sensor | Location | Arduino Pin | VCC | GND | Function |
|-----------|----------|-------------|-----|-----|----------|
| IR #1 | Entry Gate | D6 | 5V | GND | Detect arriving vehicles |
| IR #2 | Slot 1 | D7 | 5V | GND | Monitor slot 1 occupancy |
| IR #3 | Slot 2 | D8 | 5V | GND | Monitor slot 2 occupancy |
| IR #4 | Exit Gate | D13 | 5V | GND | Detect departing vehicles |

**Servo Motors:**

| Servo | Location | Signal Pin | Power | Ground | Angle Range |
|-------|----------|------------|-------|--------|-------------|
| Servo 1 | Entry Gate | D9 | 5V | GND | 0° (closed) - 90° (open) |
| Servo 2 | Exit Gate | D10 | 5V | GND | 0° (closed) - 90° (open) |

**16×2 LCD Display (4-bit mode):**

| LCD Pin | Pin # | Arduino Pin | Function |
|---------|-------|-------------|----------|
| VSS | 1 | GND | Ground |
| VDD | 2 | 5V | Power |
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
STEP 1: Power Distribution
  - Connect Arduino 5V to breadboard + rail
  - Connect Arduino GND to breadboard - rail

STEP 2: IR Sensors (×4)
  - Entry IR: VCC→+rail, GND→-rail, OUT→D6
  - Slot 1 IR: VCC→+rail, GND→-rail, OUT→D7
  - Slot 2 IR: VCC→+rail, GND→-rail, OUT→D8
  - Exit IR: VCC→+rail, GND→-rail, OUT→D13

STEP 3: Servo Motors (×2)
  - Entry Servo: Red→+rail, Brown→-rail, Orange→D9
  - Exit Servo: Red→+rail, Brown→-rail, Orange→D10

STEP 4: LCD Display
  - Power: VSS→GND, VDD→5V
  - Control: RS→D12, RW→GND, EN→D11
  - Data: D4→D5, D5→D4, D6→D3, D7→D2
  - Backlight: LED+→5V (via 220Ω), LED-→GND

STEP 5: Contrast Potentiometer
  - Left terminal → GND
  - Middle terminal → LCD VO (Pin 3)
  - Right terminal → 5V

STEP 6: Verify All Connections
  ✓ All IR sensors powered (5V, GND)
  ✓ All IR outputs connected to correct pins
  ✓ Both servos powered and signal connected
  ✓ LCD in 4-bit mode (D4-D7 only)
  ✓ Common ground for all components
```

---

### ⚠️ Important Notes:

1. **IR Sensor Logic**: Most IR modules output **LOW when object detected**, **HIGH when clear**
2. **Servo Power**: If servos draw too much current, use external 5V power supply (common ground with Arduino)
3. **LCD Contrast**: Adjust potentiometer until characters are clearly visible
4. **Pin Conflicts**: Ensure no pin is used for multiple purposes
5. **Servo Positioning**: Test servo range (0°-90°) before installing gate mechanism

---

## 💻 Code Explanation

### Complete Arduino Code:

```cpp
/*
 * Project 21: Smart Parking System
 * Author: Md. Akhinoor Islam
 * Department: ESE (Energy Science and Engineering), KUET
 * Description: Automated parking system with IR sensors, servo gates,
 *              and LCD display showing real-time slot availability.
 */

#include <Servo.h>
#include <LiquidCrystal.h>

// Servo objects for entry and exit gates
Servo entryServo;  // S1 in some versions
Servo exitServo;   // S2 in some versions

// IR Sensor pin definitions
#define IR_ENTRY 6    // Entry gate IR sensor
#define IR_SLOT1 7    // Parking slot 1 IR sensor
#define IR_SLOT2 8    // Parking slot 2 IR sensor
#define IR_EXIT 13    // Exit gate IR sensor

// Servo pin definitions
#define SERVO_ENTRY 9   // Entry gate servo
#define SERVO_EXIT 10   // Exit gate servo

// LCD initialization (RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Gate angle constants
const int GATE_CLOSED = 0;   // Horizontal position (closed)
const int GATE_OPEN = 90;    // Vertical position (open)
const int GATE_DELAY = 2000; // Time gate stays open (ms)

void setup() {
  // Initialize Serial for debugging
  Serial.begin(9600);
  Serial.println("Smart Parking System Initialized");
  
  // Attach servos to pins
  entryServo.attach(SERVO_ENTRY);
  exitServo.attach(SERVO_EXIT);
  
  // Set initial gate positions (closed)
  entryServo.write(GATE_CLOSED);
  exitServo.write(GATE_CLOSED);
  
  // Configure IR sensor pins as inputs
  pinMode(IR_ENTRY, INPUT);
  pinMode(IR_SLOT1, INPUT);
  pinMode(IR_SLOT2, INPUT);
  pinMode(IR_EXIT, INPUT);
  
  // Initialize LCD (16 columns, 2 rows)
  lcd.begin(16, 2);
  
  // Display startup message
  lcd.setCursor(0, 0);
  lcd.print("Smart Parking");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
  
  // Initial slot status display
  updateSlotDisplay();
}

void loop() {
  // Read all IR sensors
  bool entryDetected = (digitalRead(IR_ENTRY) == LOW);  // LOW = vehicle present
  bool exitDetected = (digitalRead(IR_EXIT) == LOW);
  bool slot1Occupied = (digitalRead(IR_SLOT1) == LOW);
  bool slot2Occupied = (digitalRead(IR_SLOT2) == LOW);
  
  // Handle entry gate
  if (entryDetected) {
    Serial.println("Vehicle at Entry - Opening Gate");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Vehicle Entry");
    entryServo.write(GATE_OPEN);
    delay(GATE_DELAY);
    entryServo.write(GATE_CLOSED);
    lcd.clear();
  }
  
  // Handle exit gate
  if (exitDetected) {
    Serial.println("Vehicle at Exit - Opening Gate");
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Vehicle Exit");
    exitServo.write(GATE_OPEN);
    delay(GATE_DELAY);
    exitServo.write(GATE_CLOSED);
    lcd.clear();
  }
  
  // Update slot status display
  updateSlotDisplay();
  
  // Debug output to Serial Monitor
  Serial.print("Slot1: ");
  Serial.print(slot1Occupied ? "Occupied" : "Free");
  Serial.print(" | Slot2: ");
  Serial.println(slot2Occupied ? "Occupied" : "Free");
  
  delay(500);  // Update interval
}

// Function to update LCD with current slot status
void updateSlotDisplay() {
  bool slot1Occupied = (digitalRead(IR_SLOT1) == LOW);
  bool slot2Occupied = (digitalRead(IR_SLOT2) == LOW);
  
  // Display Slot 1 status
  lcd.setCursor(0, 0);
  lcd.print("Slot 1: ");
  if (slot1Occupied) {
    lcd.print("Occupied");
  } else {
    lcd.print("Free    ");  // Extra spaces to clear previous text
  }
  
  // Display Slot 2 status
  lcd.setCursor(0, 1);
  lcd.print("Slot 2: ");
  if (slot2Occupied) {
    lcd.print("Occupied");
  } else {
    lcd.print("Free    ");
  }
}
```

---

### 📖 Code Breakdown:

#### 1. Library Includes

```cpp
#include <Servo.h>
#include <LiquidCrystal.h>
```

**Purpose:**
- `Servo.h` - Built-in Arduino library for servo motor control
- `LiquidCrystal.h` - Built-in library for LCD character displays

#### 2. Object Declarations

```cpp
Servo entryServo;
Servo exitServo;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
```

**Servo Objects:**
- `entryServo` - Controls entry gate servo motor
- `exitServo` - Controls exit gate servo motor

**LCD Object:**
```cpp
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
LiquidCrystal lcd(12, 11, 5,  4,  3,  2);
```

#### 3. Pin Definitions

```cpp
#define IR_ENTRY 6
#define IR_SLOT1 7
#define IR_SLOT2 8
#define IR_EXIT 13
#define SERVO_ENTRY 9
#define SERVO_EXIT 10
```

**Why `#define`?**
- Creates readable aliases for pin numbers
- Easy to modify if hardware changes
- No memory overhead (preprocessor macro)
- Convention: Use UPPERCASE for constants

#### 4. Constants

```cpp
const int GATE_CLOSED = 0;
const int GATE_OPEN = 90;
const int GATE_DELAY = 2000;
```

| Constant | Value | Purpose |
|----------|-------|---------|
| `GATE_CLOSED` | 0° | Horizontal gate position (blocking) |
| `GATE_OPEN` | 90° | Vertical gate position (allowing passage) |
| `GATE_DELAY` | 2000 ms | Duration gate stays open |

#### 5. Setup Function

```cpp
void setup() {
  Serial.begin(9600);
  entryServo.attach(SERVO_ENTRY);
  exitServo.attach(SERVO_EXIT);
  entryServo.write(GATE_CLOSED);
  exitServo.write(GATE_CLOSED);
  pinMode(IR_ENTRY, INPUT);
  pinMode(IR_SLOT1, INPUT);
  pinMode(IR_SLOT2, INPUT);
  pinMode(IR_EXIT, INPUT);
  lcd.begin(16, 2);
  // ... startup messages ...
}
```

**Step-by-Step:**

**a) Serial Communication:**
```cpp
Serial.begin(9600);
```
- Initialize Serial at 9600 baud for debugging
- Allows monitoring sensor states in real-time

**b) Servo Initialization:**
```cpp
entryServo.attach(SERVO_ENTRY);
exitServo.attach(SERVO_EXIT);
entryServo.write(GATE_CLOSED);
exitServo.write(GATE_CLOSED);
```
- `attach(pin)` - Associates servo object with physical pin
- `write(angle)` - Sets servo to initial closed position (0°)
- Ensures gates start in closed state on power-up

**c) IR Sensor Configuration:**
```cpp
pinMode(IR_ENTRY, INPUT);
pinMode(IR_SLOT1, INPUT);
pinMode(IR_SLOT2, INPUT);
pinMode(IR_EXIT, INPUT);
```
- Configures all IR sensor pins as inputs
- Arduino will read digital HIGH/LOW from these pins

**d) LCD Initialization:**
```cpp
lcd.begin(16, 2);
```
- Initializes 16×2 LCD (16 columns, 2 rows)
- Configures 4-bit communication mode
- Must be called before any LCD operations

#### 6. Main Loop

```cpp
void loop() {
  bool entryDetected = (digitalRead(IR_ENTRY) == LOW);
  bool exitDetected = (digitalRead(IR_EXIT) == LOW);
  bool slot1Occupied = (digitalRead(IR_SLOT1) == LOW);
  bool slot2Occupied = (digitalRead(IR_SLOT2) == LOW);
  
  // Gate control logic
  // Display updates
  // Serial debugging
  
  delay(500);
}
```

**IR Sensor Reading:**
```cpp
bool entryDetected = (digitalRead(IR_ENTRY) == LOW);
```

**Why `== LOW`?**
```
Standard IR Module Logic:
  digitalRead() returns HIGH (5V) → No object detected (beam intact)
  digitalRead() returns LOW (0V)  → Object detected (beam broken)

Boolean Conversion:
  LOW (0) == LOW → true  (vehicle present)
  HIGH (1) == LOW → false (no vehicle)
```

#### 7. Entry Gate Control

```cpp
if (entryDetected) {
  Serial.println("Vehicle at Entry - Opening Gate");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vehicle Entry");
  entryServo.write(GATE_OPEN);
  delay(GATE_DELAY);
  entryServo.write(GATE_CLOSED);
  lcd.clear();
}
```

**Flow:**
1. Check if vehicle at entry (`entryDetected == true`)
2. Print debug message to Serial Monitor
3. Clear LCD and display "Vehicle Entry"
4. Open gate (rotate servo to 90°)
5. Wait 2 seconds (allow vehicle to pass)
6. Close gate (rotate servo back to 0°)
7. Clear LCD for next status update

#### 8. Update Slot Display Function

```cpp
void updateSlotDisplay() {
  bool slot1Occupied = (digitalRead(IR_SLOT1) == LOW);
  bool slot2Occupied = (digitalRead(IR_SLOT2) == LOW);
  
  lcd.setCursor(0, 0);
  lcd.print("Slot 1: ");
  if (slot1Occupied) {
    lcd.print("Occupied");
  } else {
    lcd.print("Free    ");
  }
  
  lcd.setCursor(0, 1);
  lcd.print("Slot 2: ");
  if (slot2Occupied) {
    lcd.print("Occupied");
  } else {
    lcd.print("Free    ");
  }
}
```

**LCD Display Format:**
```
Row 0: |S|l|o|t| |1|:| |F|r|e|e| | | | |
       0 1 2 3 4 5 6 7 8 9 10... 15

Row 1: |S|l|o|t| |2|:| |O|c|c|u|p|i|e|d|
       0 1 2 3 4 5 6 7 8 9 10 11 12...

Note: Extra spaces after "Free" clear previous "Occupied" text
```

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
│  • Serial Monitor starts (9600 baud)    │
│  • Servos attach to pins D9, D10        │
│  • Gates close (0°)                     │
│  • IR sensors configured as inputs      │
│  • LCD initialized (16×2)               │
│  • Display "System Ready"               │
└──────────────┬──────────────────────────┘
               ↓
┌─────────────────────────────────────────┐
│  MAIN LOOP (Continuous)                 │
└──────────────┬──────────────────────────┘
               ↓
       ┌───────┴───────┐
       │               │
       ↓               ↓
┌─────────────┐ ┌─────────────┐
│ READ SENSORS│ │ CONTROL     │
│ • Entry IR  │ │ • Entry Gate│
│ • Exit IR   │ │ • Exit Gate │
│ • Slot 1 IR │ │ • LCD Update│
│ • Slot 2 IR │ │ • Serial Out│
└──────┬──────┘ └──────┬──────┘
       │               │
       └───────┬───────┘
               ↓
         Wait 500ms
               ↓
         Repeat Loop
```

### Detailed Operation Scenarios:

#### Scenario 1: Vehicle Enters Parking

```
Timeline:
  T=0s    : Vehicle approaches entry
  T=0.1s  : Entry IR detects vehicle (LOW signal)
  T=0.2s  : LCD displays "Vehicle Entry"
  T=0.3s  : Entry servo rotates to 90° (gate opens)
  T=2.3s  : Vehicle passes through
  T=2.4s  : Entry servo returns to 0° (gate closes)
  T=2.5s  : LCD clears, shows slot status
```

#### Scenario 2: Vehicle Parks in Slot 1

```
Timeline:
  T=0s    : Vehicle enters Slot 1
  T=0.1s  : Slot 1 IR detects vehicle (LOW)
  T=0.2s  : LCD updates: "Slot 1: Occupied"
  T=...   : Display continues showing occupied status
  T=Xmin  : Vehicle leaves Slot 1
  T=Xmin+0.1s : Slot 1 IR clears (HIGH)
  T=Xmin+0.2s : LCD updates: "Slot 1: Free    "
```

#### Scenario 3: Vehicle Exits Parking

```
Timeline:
  T=0s    : Vehicle approaches exit
  T=0.1s  : Exit IR detects vehicle (LOW signal)
  T=0.2s  : LCD displays "Vehicle Exit"
  T=0.3s  : Exit servo rotates to 90° (gate opens)
  T=2.3s  : Vehicle passes through
  T=2.4s  : Exit servo returns to 0° (gate closes)
  T=2.5s  : LCD clears, shows slot status
```

---

## 🎭 System States

### State Diagram:

```
┌──────────────────────────────────────────────────┐
│                   IDLE STATE                     │
│  • Both gates closed (0°)                        │
│  • LCD shows slot status                         │
│  • Waiting for IR trigger                        │
└─────────┬────────────────────────────────────────┘
          │
    ┌─────┴─────┐
    │           │
    ↓           ↓
┌─────────┐ ┌─────────┐
│ ENTRY   │ │ EXIT    │
│ DETECTED│ │ DETECTED│
└────┬────┘ └────┬────┘
     │           │
     ↓           ↓
┌─────────┐ ┌─────────┐
│ OPEN    │ │ OPEN    │
│ ENTRY   │ │ EXIT    │
│ GATE    │ │ GATE    │
└────┬────┘ └────┬────┘
     │           │
     ↓           ↓
┌─────────┐ ┌─────────┐
│ WAIT    │ │ WAIT    │
│ 2s      │ │ 2s      │
└────┬────┘ └────┬────┘
     │           │
     ↓           ↓
┌─────────┐ ┌─────────┐
│ CLOSE   │ │ CLOSE   │
│ ENTRY   │ │ EXIT    │
│ GATE    │ │ GATE    │
└────┬────┘ └────┬────┘
     │           │
     └─────┬─────┘
           ↓
    Return to IDLE
```

---

## 📺 LCD Display Modes

### Display States:

#### Mode 1: Normal Operation (Slot Status)
```
┌────────────────┐
│Slot 1: Free    │ Row 0
│Slot 2: Occupied│ Row 1
└────────────────┘
```

#### Mode 2: Vehicle Entry
```
┌────────────────┐
│Vehicle Entry   │ Row 0
│                │ Row 1
└────────────────┘
(Displays for 2 seconds)
```

#### Mode 3: Vehicle Exit
```
┌────────────────┐
│                │ Row 0
│Vehicle Exit    │ Row 1
└────────────────┘
(Displays for 2 seconds)
```

#### Mode 4: System Startup
```
┌────────────────┐
│Smart Parking   │ Row 0
│System Ready    │ Row 1
└────────────────┘
(Displays for 2 seconds on boot)
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
| **Servo doesn't move** | Not powered | Check red wire to 5V |
| | Signal disconnected | Verify orange wire to D9/D10 |
| | Insufficient current | Use external 5V supply |
| **Gate opens but doesn't close** | Software delay issue | Check `delay(GATE_DELAY)` |
| | Mechanical obstruction | Test servo manually |
| **IR always detects** | Sensitivity too high | Adjust IR potentiometer (CCW) |
| | Wiring reversed | Check OUT pin connection |
| **IR never detects** | No power | Verify VCC, GND connections |
| | Sensitivity too low | Adjust IR potentiometer (CW) |
| | Object too far | Move closer (2-10 cm range) |
| **Wrong slot shows occupied** | Pin swap | Verify D7=Slot1, D8=Slot2 |
| | IR logic inverted | Check `== LOW` in code |
| **Entry gate opens on exit** | Pin conflict | Verify D6=Entry, D13=Exit |
| **LCD text garbled** | Baud rate mismatch | Not applicable (LCD doesn't use serial) |
| | Poor connections | Reseat all LCD wires |
| **Serial Monitor empty** | Not opened | Tools → Serial Monitor |
| | Wrong baud rate | Set to 9600 |
| | USB cable issue | Try different cable/port |
| **System freezes** | Infinite delay | Check for `while(true)` loops |
| | Power brownout | Use adequate power supply |

---

### Advanced Debugging:

#### Test IR Sensors Individually:
```cpp
void loop() {
  Serial.print("Entry: ");
  Serial.print(digitalRead(IR_ENTRY));
  Serial.print(" | Slot1: ");
  Serial.print(digitalRead(IR_SLOT1));
  Serial.print(" | Slot2: ");
  Serial.print(digitalRead(IR_SLOT2));
  Serial.print(" | Exit: ");
  Serial.println(digitalRead(IR_EXIT));
  delay(500);
}
// Expected: 1 (HIGH) when clear, 0 (LOW) when blocked
```

#### Test Servos Independently:
```cpp
void loop() {
  entryServo.write(0);
  delay(1000);
  entryServo.write(90);
  delay(1000);
}
// Expected: Servo sweeps between 0° and 90° every second
```

#### Test LCD Display:
```cpp
void setup() {
  lcd.begin(16, 2);
  lcd.print("Test Line 1");
  lcd.setCursor(0, 1);
  lcd.print("Test Line 2");
}
void loop() {}
// Expected: Two lines of text displayed clearly
```

---

## 🌍 Real-World Applications

### Where This Technology is Used:

| Application | Description | Industry |
|-------------|-------------|----------|
| **Shopping Mall Parking** | Multi-level parking with slot indicators | Retail |
| **Airport Parking** | Long-term and short-term parking management | Transportation |
| **Hospital Parking** | Priority parking for emergency vehicles | Healthcare |
| **Office Buildings** | Employee and visitor parking allocation | Corporate |
| **Smart Cities** | Integrated parking guidance systems | Urban planning |
| **Residential Complexes** | Gated community parking | Real estate |
| **Pay-and-Park** | Automated ticketing and payment | Commercial |
| **EV Charging Stations** | Reserved slots for electric vehicles | Automotive |

---

### Industry Example: Smart City Parking

```
Enhanced Smart Parking System:
┌────────────────────────────────────────┐
│ Multiple Parking Lots                  │
│   ├─ Entry/Exit gates (Servo/Barrier) │
│   ├─ Slot detection (IR/Ultrasonic)   │
│   ├─ License plate recognition (Camera)│
│   └─ Payment terminals (RFID/NFC)     │
├────────────────────────────────────────┤
│ Central Controller (Arduino/Raspberry Pi)│
│   ├─ Real-time availability tracking  │
│   ├─ Database logging                 │
│   └─ Network communication            │
├────────────────────────────────────────┤
│ User Interfaces                        │
│   ├─ Mobile app (iOS/Android)         │
│   ├─ Web dashboard                    │
│   ├─ LED signage displays             │
│   └─ SMS/Email notifications          │
└────────────────────────────────────────┘
```

---

## 🚀 Project Extensions

### Beginner Level:

#### 1. **Add LED Indicators**
```cpp
#define LED_SLOT1 A0
#define LED_SLOT2 A1

void setup() {
  pinMode(LED_SLOT1, OUTPUT);
  pinMode(LED_SLOT2, OUTPUT);
}

void loop() {
  digitalWrite(LED_SLOT1, digitalRead(IR_SLOT1) == LOW ? HIGH : LOW);
  digitalWrite(LED_SLOT2, digitalRead(IR_SLOT2) == LOW ? HIGH : LOW);
}
// Red LED on = Slot occupied, Off = Slot free
```

#### 2. **Add Buzzer Alert**
```cpp
#define BUZZER A2

if (entryDetected) {
  tone(BUZZER, 1000, 200);  // Short beep on entry
}
```

#### 3. **Count Total Vehicles**
```cpp
int vehicleCount = 0;

if (entryDetected && !prevEntryState) {
  vehicleCount++;
}
if (exitDetected && !prevExitState) {
  vehicleCount--;
}
lcd.print("Total: ");
lcd.print(vehicleCount);
```

---

### Intermediate Level:

#### 4. **RFID Access Control**
```cpp
#include <MFRC522.h>
MFRC522 rfid(SS_PIN, RST_PIN);

void loop() {
  if (rfid.PICC_IsNewCardPresent()) {
    if (authorizedCard()) {
      entryServo.write(GATE_OPEN);
    } else {
      lcd.print("Access Denied");
    }
  }
}
```

#### 5. **SD Card Data Logging**
```cpp
#include <SD.h>
File logFile;

void logEntry(String timestamp, String event) {
  logFile = SD.open("parking.txt", FILE_WRITE);
  logFile.print(timestamp);
  logFile.print(",");
  logFile.println(event);
  logFile.close();
}
```

#### 6. **Ultrasonic Slot Detection** (More Accurate)
```cpp
#include <NewPing.h>
NewPing sonar1(TRIG1, ECHO1, MAX_DISTANCE);

void loop() {
  int distance = sonar1.ping_cm();
  bool occupied = (distance > 0 && distance < 50);  // Car within 50cm
}
```

---

### Advanced Level:

#### 7. **IoT Integration (WiFi)**
```cpp
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

void loop() {
  // Update cloud database
  ThingSpeak.setField(1, slot1Occupied);
  ThingSpeak.setField(2, slot2Occupied);
  ThingSpeak.writeFields(channelID, apiKey);
  
  // Mobile app can fetch data
}
```

#### 8. **License Plate Recognition**
```cpp
// Using ESP32-CAM or Raspberry Pi
#include <OpenCV.h>

void captureAndRecognize() {
  image = camera.capture();
  licensePlate = OCR(image);
  database.addEntry(licensePlate, timestamp);
}
```

#### 9. **Dynamic Pricing System**
```cpp
unsigned long entryTime = millis();

void calculateFee() {
  unsigned long duration = (millis() - entryTime) / 60000;  // minutes
  float fee = duration * 0.50;  // $0.50 per minute
  lcd.print("Fee: $");
  lcd.print(fee, 2);
}
```

---

## 🎯 Challenges

### 🟢 Beginner:
- [ ] Add a third parking slot with IR sensor
- [ ] Display available slot count on LCD
- [ ] Add button to manually open gates

### 🟡 Intermediate:
- [ ] Implement parking duration timer (entry to exit)
- [ ] Add RFID card authentication for entry
- [ ] Create web dashboard showing live status

### 🔴 Advanced:
- [ ] Build complete IoT parking system with mobile app
- [ ] Integrate payment gateway (cash/card/mobile)
- [ ] Add license plate recognition with camera
- [ ] Create multi-floor parking management system

---

## 📚 Technical Reference

### Arduino Functions Used:

| Function | Syntax | Purpose |
|----------|--------|---------|
| `servo.attach()` | `servo.attach(pin)` | Initialize servo on pin |
| `servo.write()` | `servo.write(angle)` | Set servo angle (0-180°) |
| `digitalRead()` | `digitalRead(pin)` | Read digital input (HIGH/LOW) |
| `pinMode()` | `pinMode(pin, mode)` | Configure pin direction |
| `lcd.begin()` | `lcd.begin(cols, rows)` | Initialize LCD |
| `lcd.setCursor()` | `lcd.setCursor(col, row)` | Set cursor position |
| `lcd.print()` | `lcd.print(text)` | Print text to LCD |
| `lcd.clear()` | `lcd.clear()` | Clear LCD display |
| `Serial.begin()` | `Serial.begin(baud)` | Initialize serial communication |
| `delay()` | `delay(ms)` | Pause execution |

---

## 👨‍🎓 Author

**Md. Akhinoor Islam**  
📚 Department: Energy Science and Engineering (ESE)  
🏫 Institution: Khulna University of Engineering & Technology (KUET)  
🌐 GitHub: [@Akhinoor14](https://github.com/Akhinoor14)  
📧 Contact: [GitHub Profile](https://github.com/Akhinoor14)

---

## 🔗 Related Projects

- [Project 07: Ultrasonic Distance Sensor](../07%20Interfacing%20an%20ultrasonic%20sensor%20with%20arduino/)
- [Project 06: Servo Motor Control](../06.%20Interfacing%20servo%20motor%20with%20arduino/)
- [Project 15: 16×2 LCD Display](../15%20Interfacing%2016-2%20Lcd%20display/)
- [Project 10: Photodiode (Alternative Sensor)](../10%20Interfacing%20Photodiode/)

---

## 📖 Learning Resources:

- [Arduino Servo Library](https://www.arduino.cc/reference/en/libraries/servo/)
- [LiquidCrystal Library](https://www.arduino.cc/en/Reference/LiquidCrystal)
- [IR Sensor Tutorial](https://www.electronicshub.org/ir-sensor/)
- [Smart Parking Systems Overview](https://en.wikipedia.org/wiki/Smart_parking)

---

## 📜 License

This project is part of the **40 Arduino Projects Series** by Akhinoor Islam.  
Licensed under MIT License - see [LICENSE](../LICENSE) file for details.

---

## ✅ Project Completion Checklist:

- [ ] All components gathered and tested
- [ ] Circuit wired according to diagram
- [ ] IR sensors adjusted for proper detection range
- [ ] Servos tested individually (0° and 90°)
- [ ] LCD contrast adjusted for clear display
- [ ] Code uploaded successfully
- [ ] Serial Monitor configured (9600 baud)
- [ ] Entry gate opens when vehicle detected
- [ ] Exit gate opens when vehicle detected
- [ ] Slot status updates correctly on LCD
- [ ] Gates close after 2-second delay
- [ ] All IR sensors respond accurately

---

**Happy Building! 🎉**  
**Create automated parking solutions and learn system integration! 🚗**

---

### 🌟 Key Takeaways:

1. **Multi-sensor coordination** - Managing 4 IR sensors simultaneously
2. **Actuator control** - Servo motors for physical automation
3. **User interface** - LCD display for real-time feedback
4. **Event-driven programming** - Responding to sensor triggers
5. **System integration** - Combining sensors, actuators, and displays

Master this project and you'll understand the fundamentals of automation systems used in smart buildings, industry 4.0, and IoT applications! 🚀