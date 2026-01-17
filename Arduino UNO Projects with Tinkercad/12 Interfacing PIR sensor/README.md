# 🚶 PIR Motion Sensor with Arduino

![Arduino Project](https://img.shields.io/badge/Arduino-UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Beginner-green?style=for-the-badge)
![Sensor](https://img.shields.io/badge/PIR-Motion%20Sensor-orange?style=for-the-badge)

## 📋 Table of Contents
- [Overview](#-overview)
- [Components Required](#-components-required)
- [PIR Sensor Basics](#-pir-sensor-basics)
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

This project demonstrates **motion detection** using a **PIR (Passive Infrared) sensor** and Arduino UNO. The PIR sensor detects infrared radiation emitted by warm bodies (humans, animals) and triggers a digital output when motion is detected, which Arduino reads to control an LED indicator. This is fundamental for security systems, automatic lighting, and presence detection applications.

### Key Features:
- ✅ Automatic motion detection (up to 7 meters)
- ✅ Digital output (HIGH/LOW) - simple interface
- ✅ Adjustable sensitivity and delay time
- ✅ Wide detection angle (110° cone)
- ✅ Low power consumption (~65mA)
- ✅ No contact required (passive detection)

---

## 🧰 Components Required

| Component | Quantity | Specification |
|-----------|----------|---------------|
| Arduino UNO | 1 | ATmega328P based |
| PIR Sensor | 1 | HC-SR501 module |
| LED | 1 | 5mm (any color) |
| 220Ω Resistor | 1 | For LED current limiting |
| Breadboard | 1 | For stable connections |
| Jumper Wires | 5 | Male-to-Male |
| USB Cable | 1 | For serial monitoring |

### 💰 Estimated Cost: $5-8 USD

---

## 🔬 PIR Sensor Basics

### What is a PIR Sensor?

**PIR** stands for **Passive Infrared**. Unlike active sensors that emit signals, PIR sensors passively detect infrared radiation (heat) emitted by objects. Every living creature with a temperature above absolute zero emits infrared radiation, making PIR sensors ideal for detecting human/animal movement.

### How PIR Sensors Work:

```
Physical Principle:
  All objects emit infrared radiation
  Warmer objects (37°C humans) emit more IR
  PIR sensor has pyroelectric material that generates
  voltage when exposed to IR radiation changes
  
Detection Process:
  1. Two IR-sensitive elements monitor field of view
  2. When stationary, both elements see same IR level
  3. Moving object causes differential IR change
  4. Voltage spike triggers digital output HIGH
  5. After delay, output returns to LOW
```

### PIR vs Other Motion Sensors:

| Sensor Type | Detection Method | Range | Power | Cost | Applications |
|-------------|-----------------|-------|-------|------|--------------|
| **PIR** | Infrared heat | 3-7m | Low | Low | Indoor security, lighting |
| **Ultrasonic** | Sound echo | 2-400cm | Moderate | Low | Parking sensors, robotics |
| **Microwave** | Radio waves | 5-20m | High | High | Outdoor security, traffic |
| **Laser/LIDAR** | Light reflection | 0-100m | High | Very High | Autonomous vehicles |
| **Camera** | Image analysis | Variable | High | Moderate | Smart surveillance |

### HC-SR501 PIR Module Specifications:

| Parameter | Value |
|-----------|-------|
| Operating Voltage | 4.5V - 20V (5V Arduino compatible) |
| Current Consumption | < 65mA |
| Output Type | Digital (3.3V HIGH / 0V LOW) |
| Detection Range | 3m - 7m (adjustable) |
| Detection Angle | 110° cone |
| Trigger Modes | Repeatable / Non-repeatable |
| Output Delay | 0.3s - 200s (adjustable) |
| Block Time | 2.5s (fixed) |
| Operating Temperature | -15°C to +70°C |
| Sensor Element | Dual pyroelectric sensors |

### HC-SR501 Module Components:

```
HC-SR501 PIR Module (Top View)
┌────────────────────────────────┐
│    ┌──────────────┐            │
│    │  Fresnel     │            │
│    │  Lens        │◄─── White dome lens
│    │  (Dome)      │            │
│    └──────────────┘            │
│                                │
│  ┌──────┐  ┌──────┐           │
│  │ Sx   │  │ Tx   │◄───────── Potentiometers
│  │Sens. │  │Time  │           │
│  └──────┘  └──────┘           │
│                                │
│  ┌────┐                        │
│  │RTRG│◄────────────────────── Trigger mode jumper
│  └────┘                        │
│   H  L                         │
│                                │
│  VCC  OUT  GND  ◄───────────── Pin header
└────────────────────────────────┘
```

### Pin Configuration:

| Pin | Function | Connection |
|-----|----------|------------|
| **VCC** | Power supply | Arduino 5V |
| **OUT** | Digital signal output | Arduino D2 (or any digital pin) |
| **GND** | Ground | Arduino GND |

### Fresnel Lens:

The white dome on the PIR module is a **Fresnel lens** that:
- Focuses infrared radiation onto the sensor
- Divides field of view into multiple zones
- Creates sensitivity patterns for motion detection
- Extends detection range from ~3m to ~7m

```
Fresnel Lens Effect:
┌─────────────────────────────────┐
│     Without Lens                │
│  Detection: ~3m, narrow angle   │
│                                 │
│   🌡️ ───────→ [PIR]            │
│         Single zone             │
└─────────────────────────────────┘

┌─────────────────────────────────┐
│     With Fresnel Lens           │
│  Detection: 3-7m, 110° wide     │
│                                 │
│      🌡️  🌡️  🌡️                │
│       ╲  │  ╱                   │
│        ╲ │ ╱                    │
│    [Lens+PIR]                   │
│    Multiple zones               │
└─────────────────────────────────┘
```

### Adjustable Settings:

#### 1️⃣ **Sensitivity (Sx) Potentiometer:**
```
Counter-clockwise: Minimum range (~3m)
Clockwise: Maximum range (~7m)

Use cases:
  Min (3m): Small rooms, precise detection
  Max (7m): Large rooms, corridors
```

#### 2️⃣ **Time Delay (Tx) Potentiometer:**
```
Counter-clockwise: Short delay (~0.3s)
Clockwise: Long delay (~200s)

Delay = How long output stays HIGH after detection

Use cases:
  Short (0.3s): Quick response, LED blink
  Medium (5-10s): Automatic lighting
  Long (200s): Energy-saving applications
```

#### 3️⃣ **Trigger Mode Jumper:**
```
H (Repeatable Mode):
  • Output stays HIGH while motion continues
  • Resets timer with each new motion
  • Ideal for continuous monitoring
  • LED stays on during activity

L (Non-repeatable Mode):
  • Output pulse ends after time delay
  • Ignores motion during block time (2.5s)
  • Single trigger per motion event
  • LED blinks once per detection
```

### Detection Pattern:

```
Field of View (110° cone):

Top View:
              7m
         ╱─────────╲
       ╱             ╲
     ╱                 ╲
   ╱                     ╲
  │                       │
  │      [PIR]            │
  │                       │
   ╲                     ╱
     ╲                 ╱
       ╲             ╱
         ╲─────────╱
            110°

Side View (mounting):
     ↑ Ceiling mount
     │
   [PIR] ← Wall mount (typical)
   ╱ │ ╲
  ╱  │  ╲  Coverage area
 ╱   │   ╲
───────────── Floor

Optimal Height: 2-2.5m from ground
```

### Motion Detection Zones:

The Fresnel lens creates multiple sensitivity zones:

```
Lens Zone Pattern:
┌───┬───┬───┬───┬───┐
│ 1 │ 2 │ 3 │ 4 │ 5 │ Zone 1 (Top)
├───┼───┼───┼───┼───┤
│ 6 │ 7 │ 8 │ 9 │10 │ Zone 2
├───┼───┼───┼───┼───┤
│11 │12 │13 │14 │15 │ Zone 3
├───┼───┼───┼───┼───┤
│16 │17 │18 │19 │20 │ Zone 4 (Bottom)
└───┴───┴───┴───┴───┘

Motion detected when object moves
between zones (differential change).

Stationary objects: No detection
Moving objects: Triggers HIGH
```

---

## 🔌 Circuit Diagram

### Connection Table:

| Component | Arduino Pin | Description |
|-----------|-------------|-------------|
| PIR VCC | 5V | Power supply (4.5V-20V) |
| PIR OUT | D2 | Digital motion signal |
| PIR GND | GND | Ground |
| LED Anode (+) | D13 | LED control (via 220Ω) |
| LED Cathode (-) | GND | LED ground (via resistor) |

### Circuit Wiring:

```
Arduino UNO               HC-SR501 PIR          LED Circuit
┌─────────────┐          ┌─────────────┐       ┌─────────┐
│             │          │  [Fresnel]  │       │         │
│   5V  ●─────┼──────────┤ VCC         │       │  LED    │
│             │          │             │       │   │     │
│  GND  ●─────┼────┬─────┤ GND         │       │  Anode  │
│             │    │     │             │       │   │     │
│   D2  ●─────┼────┼─────┤ OUT         │       │   ↓     │
│             │    │     └─────────────┘       │   │     │
│  D13  ●─────┼────┼─────────────┬─────────────┤ 220Ω    │
│             │    │             │             │   │     │
└─────────────┘    └─────────────┼─────────────┤ Cathode │
                                 └─────────────┴─────────┘
                                                     ↓
                                                    GND
```

### Detailed Connection Steps:

```
Power Connections:
  Arduino 5V → PIR VCC (red wire)
  Arduino GND → PIR GND (black wire)
  Arduino GND → LED cathode (via 220Ω resistor)

Signal Connections:
  Arduino D2 → PIR OUT (yellow wire)
  Arduino D13 → LED anode (longer lead)

Important:
  • 220Ω resistor prevents LED burnout
  • PIR can work with 4.5V-20V (5V is standard)
  • Output is 3.3V HIGH (Arduino reads as HIGH)
```

### Breadboard Layout:

```
Breadboard Setup:
┌─────────────────────────────────┐
│ + Rail (Red)                    │◄── Arduino 5V
│ - Rail (Blue)                   │◄── Arduino GND
│                                 │
│ Row 10: PIR VCC → + Rail        │
│ Row 11: PIR OUT → D2 (direct)   │
│ Row 12: PIR GND → - Rail        │
│                                 │
│ Row 20: LED Anode → D13         │
│ Row 21: LED Cathode → 220Ω → -Rail│
└─────────────────────────────────┘
```

### 🖼️ Circuit Diagram:
![PIR Motion Sensor Circuit](Circuit.png)

---

## ⚙️ How It Works

### Motion Detection Process:

```
Step 1: PIR Initialization
  • Module powers up
  • Warm-up time: ~60 seconds (stabilization)
  • Sensor calibrates to ambient IR levels
  
Step 2: Idle State (No Motion)
  • Two pyroelectric sensors see balanced IR
  • Output = LOW (0V)
  • LED = OFF
  
Step 3: Motion Detected
  • Person enters detection zone
  • IR radiation pattern changes
  • Differential voltage spike generated
  • Comparator triggers output HIGH
  
Step 4: Arduino Response
  • digitalRead(D2) returns HIGH
  • digitalWrite(D13, HIGH) turns on LED
  • Serial Monitor prints "Motion Detected!"
  
Step 5: Delay Period
  • Output stays HIGH for time delay (Tx setting)
  • If repeatable mode: timer resets with new motion
  • If non-repeatable: waits for delay + block time
  
Step 6: Return to Idle
  • No motion for delay period
  • Output = LOW
  • LED = OFF
  • Serial Monitor prints "No Motion"
```

### Digital Signal Characteristics:

```
PIR Output Signal:
  HIGH = Motion detected (3.3V)
  LOW = No motion (0V)

Arduino digitalRead():
  Returns HIGH (1) when PIR OUT > 2.5V
  Returns LOW (0) when PIR OUT < 1.0V

Timing Diagram:

Motion:  ╔═══╗     ╔══╗       ╔════╗
         ║   ║     ║  ║       ║    ║
         ║   ║     ║  ║       ║    ║
   ──────╝   ╚─────╝  ╚───────╝    ╚────

PIR OUT:      ╔══════════╗  ╔════════╗
   HIGH       ║          ║  ║        ║
              ║          ║  ║        ║
   LOW  ──────╝          ╚──╝        ╚───
              ▲          ▲  ▲
              │   Delay  │  │
          Detection    End  New
                            Motion

LED:          ████████████  ██████████
   ON         ║          ║  ║        ║
              ║          ║  ║        ║
   OFF  ──────╝          ╚──╝        ╚───
```

### Arduino Digital I/O:

```
digitalRead(pin):
  • Samples voltage at digital pin
  • Threshold: ~2.5V
  • Returns HIGH (1) or LOW (0)
  • Execution time: ~5μs
  
digitalWrite(pin, state):
  • Sets pin voltage
  • HIGH = 5V (source current)
  • LOW = 0V (sink current)
  • Execution time: ~5μs

pinMode(pin, mode):
  • INPUT: High impedance (reads signal)
  • OUTPUT: Can drive current (controls LED)
  • INPUT_PULLUP: Internal 20kΩ pull-up
```

### Code Flow Diagram:

```
┌──────────────────────────────┐
│      setup()                 │
│  • pinMode(pirPin, INPUT)    │
│  • pinMode(ledPin, OUTPUT)   │
│  • Serial.begin(9600)        │
└──────────────┬───────────────┘
               │
               ↓
┌──────────────┴───────────────┐
│      loop() - Continuous     │
└──────────────┬───────────────┘
               │
               ↓
       ┌───────────────┐
       │ digitalRead(  │
       │   pirPin)     │
       └───────┬───────┘
               │
         ┌─────┴─────┐
         │   HIGH?   │
         └─────┬─────┘
          YES  │  NO
     ┌─────────┴─────────┐
     ↓                    ↓
┌─────────┐         ┌─────────┐
│ Motion  │         │ No      │
│ Detected│         │ Motion  │
└────┬────┘         └────┬────┘
     │                   │
     ↓                   ↓
┌─────────┐         ┌─────────┐
│LED HIGH │         │LED LOW  │
│Serial   │         │Serial   │
│Message  │         │Message  │
└────┬────┘         └────┬────┘
     │                   │
     └─────────┬─────────┘
               ↓
         ┌─────────┐
         │delay(500)│
         └─────┬────┘
               │
               ↓
        Back to loop()
```

---

## 📝 Step-by-Step Guide

### 1. **Understand PIR Settings**
   - **Sensitivity (Sx)**: Start mid-position (5m range)
   - **Time Delay (Tx)**: Start at minimum (short delay)
   - **Trigger Mode**: Set jumper to H (repeatable)

### 2. **Connect PIR Module**
   ```
   PIR VCC → Arduino 5V
   PIR OUT → Arduino D2
   PIR GND → Arduino GND
   ```

### 3. **Connect LED Indicator**
   ```
   LED Anode (+) → D13
   LED Cathode (-) → 220Ω → GND
   ```

### 4. **Verify Connections**
   - Check all wires secure
   - Confirm LED polarity (longer lead = +)
   - Ensure no short circuits

### 5. **Upload Code**
   - Open Arduino IDE
   - Copy code from `Arduino C++ code.ino`
   - Select: **Tools > Board > Arduino UNO**
   - Select: **Tools > Port > [Your COM Port]**
   - Click **Upload**

### 6. **Wait for Warm-up**
   - PIR needs 30-60 seconds to stabilize
   - LED may flicker during initialization
   - Avoid motion near sensor during warm-up

### 7. **Open Serial Monitor**
   - Click **Tools > Serial Monitor**
   - Set baud rate to **9600**
   - Should display "No Motion" initially

### 8. **Test Motion Detection**
   - Wave hand in front of PIR (~1-2 meters)
   - LED should turn on
   - Serial Monitor: "Motion Detected!"
   - Stay still: LED turns off after delay

### 9. **Adjust Settings**
   - **Too sensitive?** Turn Sx counter-clockwise
   - **Not sensitive?** Turn Sx clockwise
   - **LED stays on too long?** Turn Tx counter-clockwise
   - **LED blinks too fast?** Turn Tx clockwise

---

## 💻 Code Explanation

### Full Code:

```cpp
/*
 * Project: PIR Motion Sensor with LED Indicator
 * Author: Md Akhinoor Islam
 * Description: Detect motion and trigger LED + Serial alert
 */

const int pirPin = 2;   // PIR sensor OUT pin
const int ledPin = 13;  // LED pin

void setup() {
  pinMode(pirPin, INPUT);   // PIR as input
  pinMode(ledPin, OUTPUT);  // LED as output
  Serial.begin(9600);       // Serial communication
}

void loop() {
  int pirState = digitalRead(pirPin);  // Read PIR state
  
  if (pirState == HIGH) {
    digitalWrite(ledPin, HIGH);        // Turn on LED
    Serial.println("Motion Detected!");
  } else {
    digitalWrite(ledPin, LOW);         // Turn off LED
    Serial.println("No Motion");
  }
  
  delay(500);  // Check every 0.5 seconds
}
```

### Code Breakdown:

#### 1️⃣ **Pin Definitions**
```cpp
const int pirPin = 2;
const int ledPin = 13;
```

| Constant | Value | Purpose |
|----------|-------|---------|
| `pirPin` | 2 | Digital pin D2 for PIR output |
| `ledPin` | 13 | Digital pin D13 for LED (built-in LED) |

**Why D2 and D13?**
- D2: Any digital pin works (D2-D12 available)
- D13: Built-in LED on Arduino UNO (convenient for testing)

#### 2️⃣ **Setup Function**
```cpp
void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}
```

**pinMode() Configuration:**

| Pin | Mode | Purpose |
|-----|------|---------|
| `pirPin` | INPUT | Read digital signal from PIR |
| `ledPin` | OUTPUT | Control LED (source current) |

**Serial Communication:**
- `Serial.begin(9600)`: Initialize UART at 9600 baud
- Enables debugging and real-time monitoring

#### 3️⃣ **Read PIR State**
```cpp
int pirState = digitalRead(pirPin);
```

**digitalRead() Function:**

| Function | Returns | Values |
|----------|---------|--------|
| `digitalRead(pin)` | int | HIGH (1) or LOW (0) |

**PIR Output Interpretation:**

| PIR State | Voltage | digitalRead() | Meaning |
|-----------|---------|---------------|---------|
| Motion | 3.3V | HIGH (1) | Object detected |
| No Motion | 0V | LOW (0) | No detection |

#### 4️⃣ **Conditional Logic**
```cpp
if (pirState == HIGH) {
  // Motion detected
} else {
  // No motion
}
```

**Logic Flow:**

```
pirState == HIGH?
├── TRUE → Motion detected
│   ├── Turn on LED (D13 = HIGH)
│   └── Print "Motion Detected!"
│
└── FALSE → No motion
    ├── Turn off LED (D13 = LOW)
    └── Print "No Motion"
```

#### 5️⃣ **LED Control**
```cpp
digitalWrite(ledPin, HIGH);  // Turn on LED
digitalWrite(ledPin, LOW);   // Turn off LED
```

**digitalWrite() Function:**

| State | Voltage | LED | Current |
|-------|---------|-----|---------|
| HIGH | 5V | ON | ~20mA (with 220Ω) |
| LOW | 0V | OFF | 0mA |

**Current Calculation:**

```
Ohm's Law: I = V / R

With 220Ω resistor:
  I = (5V - 2V LED drop) / 220Ω
  I = 3V / 220Ω
  I = 13.6mA (safe for LED)

Without resistor:
  I = 5V / 20Ω (LED resistance)
  I = 250mA (BURNOUT! ❌)
```

#### 6️⃣ **Serial Output**
```cpp
Serial.println("Motion Detected!");
Serial.println("No Motion");
```

**Output Format:**
```
No Motion
No Motion
Motion Detected!
Motion Detected!
Motion Detected!
No Motion
No Motion
```

#### 7️⃣ **Delay**
```cpp
delay(500);
```

**Sampling Rate:**

| Delay (ms) | Samples/sec | Use Case |
|-----------|-------------|----------|
| 100 | 10 | Fast response |
| 500 | 2 | Standard monitoring |
| 1000 | 1 | Low-power mode |

**Why 500ms?**
- Fast enough to catch motion
- Reduces serial spam
- Balances responsiveness and efficiency

---

### Advanced Code Examples:

#### **Motion Counter:**
```cpp
const int pirPin = 2;
const int ledPin = 13;
int motionCount = 0;
bool lastState = LOW;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int pirState = digitalRead(pirPin);
  
  if (pirState == HIGH && lastState == LOW) {
    motionCount++;
    Serial.print("Motion #");
    Serial.println(motionCount);
    digitalWrite(ledPin, HIGH);
  } else if (pirState == LOW) {
    digitalWrite(ledPin, LOW);
  }
  
  lastState = pirState;
  delay(100);
}
```

#### **Buzzer Alarm:**
```cpp
const int pirPin = 2;
const int buzzerPin = 8;
const int alarmDelay = 5000;  // 5 seconds

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Alarm Armed! Waiting 60s...");
  delay(60000);  // Warm-up + arming delay
  Serial.println("Alarm Active!");
}

void loop() {
  if (digitalRead(pirPin) == HIGH) {
    Serial.println("⚠ INTRUDER DETECTED!");
    
    // Alarm sound
    for (int i = 0; i < 10; i++) {
      tone(buzzerPin, 1000, 200);  // 1kHz beep
      delay(300);
    }
    
    delay(alarmDelay);
  }
  delay(100);
}
```

#### **Smart Lighting (Time-based):**
```cpp
const int pirPin = 2;
const int ledPin = 13;
unsigned long lastMotion = 0;
const unsigned long timeout = 10000;  // 10 seconds

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(pirPin) == HIGH) {
    lastMotion = millis();
    digitalWrite(ledPin, HIGH);
    Serial.println("Motion - LED ON");
  }
  
  // Turn off after timeout
  if (millis() - lastMotion > timeout && lastMotion != 0) {
    digitalWrite(ledPin, LOW);
    Serial.println("Timeout - LED OFF");
    lastMotion = 0;  // Reset
  }
  
  delay(100);
}
```

#### **Multi-zone Detection:**
```cpp
const int pirPin1 = 2;   // Zone 1
const int pirPin2 = 3;   // Zone 2
const int led1 = 12;
const int led2 = 13;

void setup() {
  pinMode(pirPin1, INPUT);
  pinMode(pirPin2, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  bool zone1 = digitalRead(pirPin1);
  bool zone2 = digitalRead(pirPin2);
  
  digitalWrite(led1, zone1 ? HIGH : LOW);
  digitalWrite(led2, zone2 ? HIGH : LOW);
  
  if (zone1 && zone2) {
    Serial.println("Both zones active!");
  } else if (zone1) {
    Serial.println("Zone 1 motion");
  } else if (zone2) {
    Serial.println("Zone 2 motion");
  }
  
  delay(500);
}
```

---

## 🌐 Simulation

### Try it Online:
🔗 **[View on Tinkercad](https://www.tinkercad.com/things/2H3kPD0kJMx-12-interfacingpirsensor)**

Features:
- Interactive motion simulation
- Adjustable PIR settings
- Real-time LED response
- Serial Monitor output

---

## 🔧 Troubleshooting

### Common Issues:

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| LED always ON | PIR not calibrated | Wait 60s warm-up time |
| No detection | Wrong pin connection | Verify D2 connection |
| Erratic behavior | Sensitivity too high | Turn Sx counter-clockwise |
| LED stays ON too long | Time delay too high | Turn Tx counter-clockwise |
| No serial output | Wrong baud rate | Set Serial Monitor to 9600 |
| Random triggers | Air currents, sunlight | Shield PIR from drafts/light |
| Short range | Sensitivity too low | Turn Sx clockwise |

### PIR Calibration Procedure:

```cpp
// Calibration helper
void calibratePIR() {
  Serial.println("PIR Calibration Mode");
  Serial.println("Avoid motion for 60 seconds...");
  
  for (int i = 60; i > 0; i--) {
    Serial.print(i);
    Serial.println(" seconds remaining");
    delay(1000);
  }
  
  Serial.println("Calibration complete!");
  Serial.println("Test motion detection now:");
  
  while (true) {
    if (digitalRead(pirPin) == HIGH) {
      Serial.println("✓ Motion detected successfully!");
      break;
    }
    delay(100);
  }
}
```

### Testing Detection Range:

```cpp
void testRange() {
  Serial.println("Range Test:");
  Serial.println("Walk away from sensor slowly...");
  
  int detections = 0;
  unsigned long startTime = millis();
  
  while (millis() - startTime < 30000) {  // 30s test
    if (digitalRead(pirPin) == HIGH) {
      detections++;
      Serial.print("Detection at: ");
      Serial.print((millis() - startTime) / 1000.0);
      Serial.println(" seconds");
      delay(1000);
    }
    delay(100);
  }
  
  Serial.print("Total detections: ");
  Serial.println(detections);
}
```

---

## 🎓 Learning Outcomes

### 📚 Concepts Covered:

| Concept | Description | Applications |
|---------|-------------|--------------|
| **PIR Technology** | Passive infrared detection | Security, automation |
| **Digital I/O** | Reading and writing digital signals | All sensors/actuators |
| **Conditional Logic** | if-else decision making | Control systems |
| **pinMode()** | Configuring pin directions | Hardware interfacing |
| **Serial Debugging** | Real-time monitoring | Troubleshooting |

### 🚀 Skills Gained:
- ✅ Understanding PIR sensor physics
- ✅ Digital signal processing
- ✅ Conditional control flow
- ✅ LED circuit design (current limiting)
- ✅ Serial communication for debugging
- ✅ Motion-triggered applications

### 🔄 Project Extensions:

1. **Security Alarm System** - Add buzzer and SMS notification
2. **Automatic Lighting** - Turn on lights when motion detected
3. **Visitor Counter** - Log timestamps of motion events
4. **Data Logger** - Save motion data to SD card
5. **Multi-sensor Network** - Combine multiple PIRs for zones
6. **Smart Home Integration** - Connect to home automation
7. **Battery-powered** - Use sleep modes for portable operation

---

## 📁 Project Files

| File | Description |
|------|-------------|
| `README.md` | Complete project documentation |
| `Arduino C++ code.ino` | Arduino source code |
| `Code & Circuit Explanation(for beginner).md` | Bengali tutorial |
| `Circuit.png` | Circuit diagram |
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
- Add multi-zone detection
- Implement motion logging
- Create alarm system
- Add LCD/OLED display
- Share your motion detection projects!

---

## ⭐ Show Your Support

If this helped you understand PIR sensors, give it a ⭐!

---

### 📌 Real-World Applications:

- 🔒 **Security Systems** - Intrusion detection
- 💡 **Automatic Lighting** - Energy-saving lights
- 🚪 **Smart Doors** - Auto-open/close
- 🏠 **Home Automation** - Presence detection
- 🏢 **Building Management** - Occupancy sensing
- 🚽 **Smart Restrooms** - Automatic flushing
- 🌳 **Wildlife Monitoring** - Animal detection
- 🚗 **Parking Systems** - Vehicle detection

Happy Detecting! 🎉
