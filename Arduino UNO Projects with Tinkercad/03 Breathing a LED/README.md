# 🌬️ Breathing LED Effect with PWM

![Arduino Project](https://img.shields.io/badge/Arduino-UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Beginner-green?style=for-the-badge)
![PWM](https://img.shields.io/badge/Concept-PWM-blue?style=for-the-badge)

## 📋 Table of Contents
- [Overview](#-overview)
- [Components Required](#-components-required)
- [Circuit Diagram](#-circuit-diagram)
- [PWM Concept](#-pwm-concept-explained)
- [How It Works](#-how-it-works)
- [Step-by-Step Guide](#-step-by-step-guide)
- [Code Explanation](#-code-explanation)
- [Simulation](#-simulation)
- [Troubleshooting](#-troubleshooting)
- [Learning Outcomes](#-learning-outcomes)
- [Project Files](#-project-files)
- [Author](#-author)

---

## 🎯 Overview

This project creates a mesmerizing **breathing LED effect** where a single LED smoothly fades in and out, mimicking natural breathing. This is achieved using **PWM (Pulse Width Modulation)**, a fundamental technique in electronics for controlling analog-like outputs with digital signals.

### Key Features:
- ✅ Smooth LED brightness transitions (0% to 100%)
- ✅ PWM control using `analogWrite()`
- ✅ Breathing effect simulation
- ✅ Understanding duty cycle and analog simulation
- ✅ Foundation for advanced projects (motor speed, RGB colors, etc.)

---

## 🧰 Components Required

| Component | Quantity | Specification |
|-----------|----------|---------------|
| Arduino UNO | 1 | ATmega328P based |
| Breadboard | 1 | Full-size or half-size |
| LED (Any color) | 1 | 5mm standard |
| Resistor | 1 | 220Ω (Red-Red-Brown) |
| Jumper Wires | 5-6 | Male-to-Male |

### 💰 Estimated Cost: $3-5 USD

---

## 🔌 Circuit Diagram

### Connection Table:

| Component Pin | Arduino Pin | Description |
|---------------|-------------|-------------|
| LED Anode (+) | Through 220Ω resistor | Long leg of LED |
| Resistor | D9 (PWM Pin) | PWM-capable pin |
| LED Cathode (-) | GND | Short leg of LED |

### PWM-Capable Pins on Arduino UNO:
| Pin | PWM Support | Frequency |
|-----|-------------|-----------|
| D3 | ✅ Yes | ~490 Hz |
| D5 | ✅ Yes | ~980 Hz |
| D6 | ✅ Yes | ~980 Hz |
| **D9** | ✅ Yes | ~490 Hz |
| D10 | ✅ Yes | ~490 Hz |
| D11 | ✅ Yes | ~490 Hz |

*Look for the **~** symbol next to the pin on your Arduino board*

### Circuit Wiring:

```
Arduino UNO
┌─────────────┐
│             │
│   D9 ●──────┼──[220Ω]──┬──[LED]──┬──┐
│             │           │    (+)  │  │
│  GND ●──────┼───────────┴─────────┴──┘
│             │          (-)
└─────────────┘

Components:
  ● = Arduino Pin
  [] = Component
  ── = Wire
```

### 🖼️ Circuit Diagram:
![Breathing LED Circuit](Circuit.png)

---

## 📊 PWM Concept Explained

### What is PWM?

**PWM (Pulse Width Modulation)** is a technique to simulate analog output using digital signals by rapidly switching between HIGH and LOW states.

### How PWM Creates "Analog" Brightness:

```
Duty Cycle = (ON Time / Total Time) × 100%

0% Duty Cycle (OFF):
|___|___|___|___|     → LED appears OFF (0/255)

25% Duty Cycle (DIM):
|▄___|▄___|▄___|     → LED appears 25% bright (64/255)

50% Duty Cycle (MEDIUM):
|▄▄__|▄▄__|▄▄__|     → LED appears 50% bright (128/255)

75% Duty Cycle (BRIGHT):
|▄▄▄_|▄▄▄_|▄▄▄_|     → LED appears 75% bright (191/255)

100% Duty Cycle (FULL):
|▄▄▄▄|▄▄▄▄|▄▄▄▄|     → LED appears fully ON (255/255)

Key: ▄ = ON (5V), _ = OFF (0V)
Switching happens ~490 times per second (490 Hz)
```

### analogWrite() Value Range:

| Value | Duty Cycle | LED Brightness | Voltage (Avg) |
|-------|------------|----------------|---------------|
| 0 | 0% | OFF | 0V |
| 64 | 25% | Dim | 1.25V |
| 128 | 50% | Medium | 2.5V |
| 191 | 75% | Bright | 3.75V |
| 255 | 100% | Full | 5V |

---

## ⚙️ How It Works

The breathing effect is created by continuously changing the LED brightness in two phases:

### Phase 1: Fade In (Inhale)
- Brightness increases from 0 to 255
- Each step increases by 1
- Small delay (10ms) between steps creates smooth transition
- Total time: 255 × 10ms = 2.55 seconds

### Phase 2: Fade Out (Exhale)
- Brightness decreases from 255 to 0
- Each step decreases by 1
- Small delay (10ms) for smoothness
- Total time: 255 × 10ms = 2.55 seconds

### Complete Cycle:
```
Brightness
255 ├─────╮           ╭─────╮
    │     │           │     │
    │     │           │     │
128 │     │           │     │
    │     │           │     │
    │     ╰───────────╯     ╰────►
  0 └─────────────────────────────► Time
    Fade In  Fade Out Fade In  Fade Out
    (2.55s)  (2.55s)  (2.55s)  (2.55s)
    
    One complete breath ≈ 5.1 seconds
```

---

## 📝 Step-by-Step Guide

### 1. **Understand PWM Pins**
   - Locate PWM pins on Arduino (marked with **~** symbol)
   - We're using **D9** for this project
   - Only PWM pins support `analogWrite()`

### 2. **Insert LED**
   - Place LED in breadboard
   - **Identify polarity carefully:**
     - Long leg = Anode (+) = Connect to resistor
     - Short leg = Cathode (-) = Connect to GND
     - Flat edge on LED = Cathode side

### 3. **Add Resistor**
   - Connect 220Ω resistor to LED's anode (long leg)
   - **Why 220Ω?** 
     - Limits current to safe level (~20mA)
     - Formula: R = (Vsupply - VLED) / ILED = (5V - 2V) / 0.02A = 150Ω minimum
     - 220Ω provides safety margin

### 4. **Wire to Arduino**
   ```
   Arduino D9 → Resistor → LED Anode
   LED Cathode → Arduino GND
   ```

### 5. **Upload Code**
   - Open Arduino IDE
   - Copy code from `LED Breathing.ino`
   - Select: **Tools > Board > Arduino UNO**
   - Select: **Tools > Port > [Your COM Port]**
   - Click **Upload**

### 6. **Observe the Effect**
   - LED should smoothly brighten and dim
   - Each cycle takes about 5 seconds
   - If it looks choppy, increase delay value

---

## 💻 Code Explanation

### Full Code:

```cpp
/*
 * Project: Breathing LED
 * Author: Md. Akhinoor Islam
 * Description: LED gradually brightens and dims using PWM
 */

const int ledPin = 9; // PWM-capable pin

void setup() {
  pinMode(ledPin, OUTPUT); // Set D9 as output
}

void loop() {
  // Phase 1: Fade In (Brighten)
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(ledPin, brightness); // Set LED brightness
    delay(10);                       // Small delay for smooth transition
  }

  // Phase 2: Fade Out (Dim)
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(ledPin, brightness); // Decrease brightness
    delay(10);                       // Smooth transition
  }
}
```

### Code Breakdown:

#### 1️⃣ **Pin Declaration**
```cpp
const int ledPin = 9;
```
| Concept | Explanation |
|---------|-------------|
| **const** | Value won't change during execution |
| **Pin 9** | PWM-capable pin (marked with ~ on board) |
| **Why 9?** | Any PWM pin works (3, 5, 6, 9, 10, 11) |

#### 2️⃣ **Setup Function**
```cpp
void setup() {
  pinMode(ledPin, OUTPUT);
}
```
- Runs once when Arduino powers on
- Configures D9 as OUTPUT to send PWM signals

#### 3️⃣ **Fade In Loop**
```cpp
for (int brightness = 0; brightness <= 255; brightness++) {
  analogWrite(ledPin, brightness);
  delay(10);
}
```

**Step-by-Step Execution:**

| Iteration | brightness | Duty Cycle | LED State |
|-----------|------------|------------|-----------|
| 1 | 0 | 0% | OFF |
| 26 | 25 | ~10% | Very Dim |
| 51 | 50 | ~20% | Dim |
| 128 | 127 | 50% | Medium |
| 191 | 190 | ~75% | Bright |
| 256 | 255 | 100% | Full Bright |

#### 4️⃣ **Fade Out Loop**
```cpp
for (int brightness = 255; brightness >= 0; brightness--) {
  analogWrite(ledPin, brightness);
  delay(10);
}
```
- Exact opposite of fade in
- Decrements brightness from 255 to 0
- `brightness--` means subtract 1 each loop

### Key Functions:

| Function | Purpose | Parameters |
|----------|---------|------------|
| `analogWrite(pin, value)` | Set PWM duty cycle | pin: 3,5,6,9,10,11<br>value: 0-255 |
| `delay(ms)` | Pause execution | Time in milliseconds |
| `pinMode(pin, OUTPUT)` | Configure pin mode | Sets pin as output |

---

## 🌐 Simulation

### Try it Online:
🔗 **[View on Tinkercad](https://www.tinkercad.com/things/aBBDE8W7Qpl-03-breathing-led)**

Simulate this project online:
- Visualize PWM signals
- Adjust delay values
- Try different PWM pins
- Learn without hardware

---

## 🔧 Troubleshooting

### Common Issues and Solutions:

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| LED not lighting at all | Wrong polarity | Flip the LED (swap anode/cathode) |
| LED flickers/choppy | Non-PWM pin used | Use pins 3, 5, 6, 9, 10, or 11 |
| LED always full brightness | No PWM code | Check `analogWrite()` is used, not `digitalWrite()` |
| LED too dim throughout | Wrong resistor | Use 220Ω (Red-Red-Brown), not 1kΩ |
| Effect too fast | Short delay | Increase `delay(10)` to `delay(20)` |
| Effect too slow | Long delay | Decrease delay value |
| LED burns out | No resistor | **ALWAYS** use current-limiting resistor |

### 📌 Pro Tips:
- Try different delay values for different breathing speeds
- Use brighter LEDs (super-bright/clear LEDs) for better effect
- Experiment with different colors - blue/white look best
- Try non-linear fading (exponential curve) for more realistic breathing
- Add Serial.println() to debug brightness values

### 🎨 Advanced Modifications:

**1. Non-linear Breathing (More Natural):**
```cpp
// Use exponential fade
int brightness = pow(2, (i / 32.0)) - 1; // Range: 0-255
```

**2. Variable Speed:**
```cpp
// Fast inhale, slow exhale
delay(5);  // In fade-in loop
delay(15); // In fade-out loop
```

**3. Heartbeat Pattern:**
```cpp
// Two quick pulses, then pause
// Fade in-out (pulse 1)
// Fade in-out (pulse 2)
// Long delay (rest)
```

---

## 🎓 Learning Outcomes

After completing this project, you will understand:

### 📚 Core Concepts:

| Concept | What You Learned | Real-World Applications |
|---------|------------------|------------------------|
| **PWM** | Digital signals simulate analog | Motor speed control, LED dimming, audio |
| **Duty Cycle** | Ratio of ON time to total time | Power control, efficiency |
| **analogWrite()** | Arduino's PWM function | Brightness, speed, volume control |
| **Smooth Transitions** | Small increments + delays | Animations, UI effects |
| **For Loop Variants** | Increment and decrement loops | Counting up/down, ranges |

### 🚀 Skills Gained:
- ✅ Understanding PWM and duty cycles
- ✅ Using analog output with digital Arduino
- ✅ Creating smooth animations
- ✅ Working with PWM-capable pins
- ✅ Foundation for advanced projects:
  - RGB LED color mixing
  - DC motor speed control
  - Servo motor position
  - Audio tone generation

### 🔄 What You Can Build Next:
1. **RGB Breathing** - All three colors breathe independently
2. **Motor Speed Ramp** - Gradually increase/decrease speed
3. **Audio Fade** - Fade in/out a tone or melody
4. **Multiple LEDs** - Different breathing phases
5. **Light Sensor** - Auto-adjust brightness based on ambient light

---

## 📁 Project Files

This repository contains:

| File | Description |
|------|-------------|
| `README.md` | Complete project documentation (this file) |
| `LED Breathing.ino` | Arduino source code |
| `Code & CIRCUIT Explanation (for beginner).md` | Detailed Bengali tutorial |
| `Circuit.png` | Circuit diagram screenshot |
| `LICENSE` | MIT License |

---

## 👨‍🎓 Author

**Md. Akhinoor Islam**  
📚 Energy Science and Engineering (ESE)  
🏫 Khulna University of Engineering & Technology (KUET)  
🌐 [GitHub Profile](https://github.com/Akhinoor14)

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 🤝 Contributing

Enhance this project:
- Add non-linear fading curves
- Create different breathing patterns
- Add potentiometer for speed control
- Share your improvements!

---

## ⭐ Show Your Support

If this project helped you understand PWM, give it a ⭐ on GitHub!

---

### 📌 Next Steps:
- Try Project 04: ATtiny85 LED Control
- Create RGB breathing with 3 PWM pins
- Add a potentiometer to control breathing speed
- Build a light therapy lamp

Happy Learning! 🎉
