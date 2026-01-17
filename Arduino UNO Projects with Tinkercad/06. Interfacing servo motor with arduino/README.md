# 🤖 Servo Motor Control with Arduino

![Arduino Project](https://img.shields.io/badge/Arduino-UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Beginner-green?style=for-the-badge)
![Concept](https://img.shields.io/badge/Servo-Motor-orange?style=for-the-badge)

## 📋 Table of Contents
- [Overview](#-overview)
- [Components Required](#-components-required)
- [Servo Motor Basics](#-servo-motor-basics)
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

This project demonstrates how to control a **servo motor** using Arduino UNO. The servo smoothly sweeps from 0° to 180° and back, teaching the fundamentals of precise angular motion control using PWM signals. This is essential knowledge for robotics, automation, and mechanical control systems.

### Key Features:
- ✅ Precise angle control (0° to 180°)
- ✅ Smooth sweeping motion
- ✅ Using Arduino Servo library
- ✅ PWM signal generation for servo control
- ✅ Foundation for robotic arm, pan-tilt mechanisms, etc.

---

## 🧰 Components Required

| Component | Quantity | Specification |
|-----------|----------|---------------|
| Arduino UNO | 1 | ATmega328P based |
| Servo Motor | 1 | SG90 or similar (180° rotation) |
| Breadboard | 1 | Optional (for organization) |
| Jumper Wires | 3 | Male-to-Male |

### 💰 Estimated Cost: $5-8 USD

---

## 🔬 Servo Motor Basics

### What is a Servo Motor?

A servo motor is a **rotary actuator** that allows precise control of angular position. Unlike regular DC motors that spin continuously, servos can be positioned to specific angles.

### Servo Motor Types:

| Type | Rotation Range | Use Case |
|------|----------------|----------|
| **Standard Servo** | 0° to 180° | Most common (SG90, MG90S) |
| **Continuous Rotation** | 360° continuous | Wheel drive systems |
| **Industrial Servo** | Multi-turn | High precision applications |

### How Servo Motors Work:

```
Internal Components:
┌─────────────────────────────┐
│  DC Motor                   │
│    ↓                        │
│  Gear System (Reduction)    │
│    ↓                        │
│  Output Shaft               │
│    ↓                        │
│  Potentiometer (Feedback)   │
│    ↓                        │
│  Control Circuit            │
└─────────────────────────────┘

Control Signal: PWM
  • Pulse width determines angle
  • 1ms pulse = 0°
  • 1.5ms pulse = 90°
  • 2ms pulse = 180°
```

### SG90 Servo Specifications:

| Parameter | Value |
|-----------|-------|
| Operating Voltage | 4.8V - 6V |
| Operating Current | ~100-250mA |
| Stall Current | ~650mA |
| Stall Torque | 1.8 kg·cm (at 4.8V) |
| Operating Speed | 0.1s/60° (at 4.8V) |
| Rotation Range | 0° - 180° |
| Dead Band | 10 μs |
| Control Signal | PWM (50 Hz) |

### Servo Wire Colors:

```
Standard Color Codes:
┌──────────────────────────┐
│  Wire    │  Color        │  Connection  │
│──────────┼───────────────┼──────────────│
│  Power   │  Red          │  5V          │
│  Ground  │  Brown/Black  │  GND         │
│  Signal  │  Orange/Yellow│  PWM Pin     │
└──────────────────────────┘

Note: Some servos may have white instead of orange
```

---

## 🔌 Circuit Diagram

### Connection Table:

| Servo Wire | Arduino Pin | Description |
|------------|-------------|-------------|
| Red | 5V | Power supply (4.8V-6V) |
| Brown/Black | GND | Ground |
| Orange/Yellow/White | D9 | PWM signal (control) |

### Circuit Wiring:

```
Arduino UNO                    Servo Motor (SG90)
┌─────────────┐               ┌────────────┐
│             │               │            │
│   5V  ●─────┼───────────────┤ Red        │
│             │               │            │
│  GND  ●─────┼───────────────┤ Brown      │
│             │               │            │
│   D9  ●─────┼───────────────┤ Orange     │
│             │               │  (Signal)  │
└─────────────┘               └────────────┘

PWM Pin (D9) sends control signal
Servo moves to commanded angle
```

### 🖼️ Circuit Diagram:
![Servo Motor Control Circuit](Circuit.png)

---

## ⚙️ How It Works

### PWM Signal and Angle Control:

Servo motors use **PWM (Pulse Width Modulation)** signals with a specific timing:

```
PWM Signal (50 Hz = 20ms period):

0° Position (1ms pulse):
|▄____________________| 20ms
 1ms HIGH, 19ms LOW

90° Position (1.5ms pulse):
|▄▄▄___________________| 20ms
 1.5ms HIGH, 18.5ms LOW

180° Position (2ms pulse):
|▄▄▄▄__________________| 20ms
 2ms HIGH, 18ms LOW

Pulse Width → Angle Mapping:
1.0ms → 0°
1.1ms → 18°
1.2ms → 36°
1.3ms → 54°
1.4ms → 72°
1.5ms → 90°
1.6ms → 108°
1.7ms → 126°
1.8ms → 144°
1.9ms → 162°
2.0ms → 180°
```

### Servo Control Loop:

```
Arduino sends PWM signal
         ↓
Servo's control circuit receives signal
         ↓
Compares with potentiometer position
         ↓
Calculates error (desired - actual)
         ↓
Drives motor to correct position
         ↓
Potentiometer confirms position
         ↓
Motor stops (position held)
```

### Motion Sequence:

```
Time:    0s      1.2s    2.4s    3.6s
Angle:   0° ───► 180° ───► 0° ───► 180°

Sweep Pattern:
180°├────────╮           ╭────────╮
    │        │           │        │
 90°│        │           │        │
    │        ╰───────────╯        ╰──►
  0°└─────────────────────────────────► Time
    Fwd Sweep  Rev Sweep  Fwd Sweep
```

---

## 📝 Step-by-Step Guide

### 1. **Identify Servo Wires**
   - **Red** = Power (5V)
   - **Brown/Black** = Ground (GND)
   - **Orange/Yellow/White** = Signal (PWM)
   - Check your servo's datasheet if colors differ

### 2. **Connect Power**
   ```
   Servo Red wire → Arduino 5V
   Servo Brown/Black wire → Arduino GND
   ```
   
   **Important:** For multiple servos or high-torque servos, use external 5V power supply!

### 3. **Connect Signal**
   ```
   Servo Orange/Yellow wire → Arduino D9
   ```
   - D9 is a PWM-capable pin
   - Can use other PWM pins (D3, D5, D6, D10, D11)

### 4. **Secure Connections**
   - Ensure wires are firmly connected
   - Use breadboard for stable connections
   - Double-check polarity (especially power!)

### 5. **Upload Code**
   - Open Arduino IDE
   - Copy code from `servo-control.ino`
   - Install Servo library if needed: **Sketch > Include Library > Servo**
   - Select: **Tools > Board > Arduino UNO**
   - Select: **Tools > Port > [Your COM Port]**
   - Click **Upload**

### 6. **Observe Motion**
   - Servo should sweep from 0° to 180°
   - Then sweep back from 180° to 0°
   - Motion should be smooth and continuous
   - If jerky, check power supply

---

## 💻 Code Explanation

### Full Code:

```cpp
/*
 * Project: Servo Motor Control
 * Author: Md. Akhinoor Islam
 * Description: Smooth servo sweep from 0° to 180°
 */

#include <Servo.h>  // Include Servo library

Servo myServo;      // Create servo object

void setup() {
  myServo.attach(9);  // Attach servo to pin 9
}

void loop() {
  // Sweep from 0° to 180°
  for (int angle = 0; angle <= 180; angle += 1) {
    myServo.write(angle);  // Move to angle
    delay(15);             // Wait for servo to reach position
  }

  // Sweep from 180° back to 0°
  for (int angle = 180; angle >= 0; angle -= 1) {
    myServo.write(angle);  // Move to angle
    delay(15);             // Wait for servo to reach position
  }
}
```

### Code Breakdown:

#### 1️⃣ **Include Servo Library**
```cpp
#include <Servo.h>
```
- Arduino's built-in library for servo control
- Handles PWM signal generation automatically
- Simplifies angle commands

#### 2️⃣ **Create Servo Object**
```cpp
Servo myServo;
```
- Creates a servo control object
- Can create multiple objects for multiple servos
- Each object controls one servo

#### 3️⃣ **Setup Function**
```cpp
void setup() {
  myServo.attach(9);
}
```

| Function | Purpose | Parameter |
|----------|---------|-----------|
| `attach(pin)` | Connects servo to pin | Pin number (9) |
| Initializes PWM | Sets up signal generation | 50 Hz frequency |

#### 4️⃣ **Forward Sweep (0° to 180°)**
```cpp
for (int angle = 0; angle <= 180; angle += 1) {
  myServo.write(angle);
  delay(15);
}
```

**Iteration Examples:**

| Iteration | angle | Action | Time |
|-----------|-------|--------|------|
| 1 | 0 | Move to 0° | 0ms |
| 30 | 29 | Move to 29° | 435ms |
| 90 | 89 | Move to 89° | 1335ms |
| 180 | 179 | Move to 179° | 2685ms |
| 181 | 180 | Move to 180° | 2700ms |

**Total sweep time:** 181 × 15ms = 2.715 seconds

#### 5️⃣ **Reverse Sweep (180° to 0°)**
```cpp
for (int angle = 180; angle >= 0; angle -= 1) {
  myServo.write(angle);
  delay(15);
}
```
- Same logic as forward sweep
- Decrements angle from 180 to 0
- Creates smooth return motion

### Key Functions:

| Function | Purpose | Parameters | Return |
|----------|---------|------------|--------|
| `attach(pin)` | Connect servo | pin: Digital pin number | void |
| `write(angle)` | Set angle | angle: 0-180 degrees | void |
| `read()` | Get current angle | none | int (0-180) |
| `detach()` | Disconnect servo | none | void |

### Timing Considerations:

```cpp
delay(15);  // Why 15ms?
```

| Delay | Effect |
|-------|--------|
| 0-5ms | Too fast, servo can't keep up |
| 10-20ms | Smooth motion, recommended |
| 50ms+ | Slow but stable |
| 100ms+ | Very slow, step-like motion |

---

## 🌐 Simulation

### Try it Online:
🔗 **[View on Tinkercad](https://www.tinkercad.com/things/0DGu9rY1BEx-06-interfacing-servo-motor-with-arduino)**

Features:
- Interactive servo visualization
- Real-time angle display
- Modify sweep range
- Adjust speed

---

## 🔧 Troubleshooting

### Common Issues:

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| Servo doesn't move | Wrong wire connection | Check: Red=5V, Brown=GND, Orange=D9 |
| Jittery motion | Insufficient power | Use external 5V power supply |
| Servo stuck at one position | Library not included | Add `#include <Servo.h>` |
| Random movements | Loose signal wire | Secure connection to D9 |
| Servo hums but doesn't move | Mechanical obstruction | Remove obstacles, check gears |
| Limited range (<180°) | Servo physically limited | Some servos have <180° range |
| Overheating | Stalled motor | Reduce load, check for binding |

### Power Issues:

**Symptoms of insufficient power:**
- Servo jitters or shakes
- Arduino resets randomly
- Brown-outs during servo movement

**Solutions:**
```
For 1 servo: Arduino 5V usually OK
For 2-3 servos: External 5V 1A power
For 4+ servos: External 5V 2A+ power

External Power Setup:
  5V Supply (+) → Servo Red wires
  5V Supply (-) → Servo Brown + Arduino GND (common ground!)
  Arduino D9 → Servo Orange (signal only)
```

### Advanced Debugging:

```cpp
#include <Servo.h>

Servo myServo;

void setup() {
  Serial.begin(9600);
  myServo.attach(9);
  Serial.println("Servo attached to pin 9");
}

void loop() {
  for (int angle = 0; angle <= 180; angle += 10) {
    myServo.write(angle);
    Serial.print("Angle: ");
    Serial.println(angle);
    delay(500);
  }
}
```

---

## 🎓 Learning Outcomes

### 📚 Concepts Covered:

| Concept | Description | Applications |
|---------|-------------|--------------|
| **Servo Motors** | Precise angular control | Robotics, RC vehicles, automation |
| **PWM Signals** | Pulse width modulation | Motor control, LED dimming |
| **Servo Library** | Arduino abstraction layer | Simplifies complex timing |
| **Mechanical Control** | Digital to physical motion | Actuators, robotic arms |
| **Feedback Systems** | Closed-loop control | Position sensing, stability |

### 🚀 Skills Gained:
- ✅ Understanding servo motor operation
- ✅ Using Arduino Servo library
- ✅ PWM signal generation concepts
- ✅ Power management for motors
- ✅ Smooth motion programming
- ✅ Foundation for robotics projects

### 🔄 Project Extensions:

1. **Potentiometer Control** - Manual angle adjustment
2. **Multi-Servo Coordination** - Robot arm with 4+ servos
3. **Servo with Sensors** - Ultrasonic-controlled pan-tilt
4. **Remote Control** - IR/Bluetooth servo control
5. **Pan-Tilt Camera Mount** - 2-axis camera positioning
6. **Robotic Gripper** - Open/close mechanism
7. **Servo Tester** - Variable speed and range control

---

## 📁 Project Files

| File | Description |
|------|-------------|
| `README.md` | Complete project documentation |
| `servo-control.ino` | Arduino source code |
| `Code & Circuit Explanation(for beginner).md` | Bengali tutorial |
| `Circuit.png` | Circuit diagram |
| `license` | MIT License |

---

## 👨‍🎓 Author

**Md. Akhinoor Islam**  
📚 Energy Science and Engineering (ESE)  
🏫 Khulna University of Engineering & Technology (KUET)  
🌐 [GitHub Profile](https://github.com/Akhinoor14)

---

## 📄 License

This project is licensed under the MIT License.

---

## 🤝 Contributing

Enhance this project:
- Add angle limits
- Implement smooth acceleration
- Add serial control interface
- Create pattern sequences
- Share your servo projects!

---

## ⭐ Show Your Support

If this helped you learn about servo motors, give it a ⭐!

---

### 📌 Real-World Applications:

- 🤖 **Robotic Arms** - Multi-axis manipulation
- 📷 **Camera Gimbals** - Stabilization systems
- 🚪 **Automated Doors** - Smart access control
- ✈️ **RC Aircraft** - Control surfaces
- 🚗 **RC Cars** - Steering mechanisms
- 🏭 **Industrial Automation** - Precise positioning

Happy Building! 🎉
