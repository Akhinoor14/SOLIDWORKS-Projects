# 🔁 LED Sequential Blinking Pattern

![Arduino Project](https://img.shields.io/badge/Arduino-UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Beginner-green?style=for-the-badge)

## 📋 Table of Contents
- [Overview](#-overview)
- [Components Required](#-components-required)
- [Circuit Diagram](#-circuit-diagram)
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

This project demonstrates a simple yet visually appealing **sequential LED blinking pattern**. Five LEDs blink one by one in a continuous loop, creating a flowing light effect. This is an excellent beginner project to understand arrays, loops, and timing control in Arduino programming.

### Key Features:
- ✅ Sequential LED blinking pattern
- ✅ Array-based pin management
- ✅ For loop implementation for efficiency
- ✅ Customizable timing and speed
- ✅ Easy to expand with more LEDs

---

## 🧰 Components Required

| Component | Quantity | Specification |
|-----------|----------|---------------|
| Arduino UNO | 1 | ATmega328P based |
| Breadboard | 1 | Full-size or half-size |
| LED (Any color) | 5 | 5mm standard |
| Resistor | 5 | 220Ω (Red-Red-Brown) |
| Jumper Wires | 15-20 | Male-to-Male |

### 💰 Estimated Cost: $5-8 USD

---

## 🔌 Circuit Diagram

### Connection Table:

#### LED Connections:
| LED Number | Arduino Pin | Connection Path |
|------------|-------------|-----------------|
| LED 1 | D2 | D2 → 220Ω resistor → LED Anode (+) |
| LED 2 | D3 | D3 → 220Ω resistor → LED Anode (+) |
| LED 3 | D4 | D4 → 220Ω resistor → LED Anode (+) |
| LED 4 | D5 | D5 → 220Ω resistor → LED Anode (+) |
| LED 5 | D6 | D6 → 220Ω resistor → LED Anode (+) |

**All LED cathodes (shorter leg) connect to GND rail on breadboard**

### Circuit Wiring:
```
Arduino UNO
┌─────────────┐
│             │
│  D2 ●───[220Ω]───[LED1]───┐
│  D3 ●───[220Ω]───[LED2]───┤
│  D4 ●───[220Ω]───[LED3]───┼──► GND
│  D5 ●───[220Ω]───[LED4]───┤
│  D6 ●───[220Ω]───[LED5]───┘
│             │
│  GND ●──────┴──► Breadboard GND Rail
└─────────────┘
```

### 🖼️ Circuit Diagram:
![LED Sequential Blink Circuit](Circuit.png)

---

## ⚙️ How It Works

The project uses a **sequential control algorithm** to create a flowing light pattern:

1. **Array Storage**: 
   - All 5 LED pin numbers are stored in an array: `{2, 3, 4, 5, 6}`
   - This makes it easy to control multiple LEDs with a loop

2. **For Loop Iteration**:
   - The loop runs from 0 to 4 (5 times)
   - Each iteration controls one LED

3. **Blinking Sequence**:
   - Turn LED ON (`HIGH`)
   - Wait 300ms (LED stays lit)
   - Turn LED OFF (`LOW`)
   - Wait 100ms (brief gap before next LED)
   - Move to next LED

4. **Continuous Loop**:
   - After LED 5, the sequence automatically starts from LED 1 again
   - Creates an endless flowing pattern

### Timing Diagram:

```
LED 1: █░░░░░░░░░░░░░░░░░░░█░░░░░░░░
LED 2: ░░░░█░░░░░░░░░░░░░░░░░░░█░░░░
LED 3: ░░░░░░░░█░░░░░░░░░░░░░░░░░░█░
LED 4: ░░░░░░░░░░░░█░░░░░░░░░░░░░░░░
LED 5: ░░░░░░░░░░░░░░░░█░░░░░░░░░░░░
       ↑                ↑
     300ms ON         100ms OFF
```

---

## 📝 Step-by-Step Guide

### 1. **Prepare the Breadboard**
   - Connect Arduino's GND to breadboard's negative (-) rail
   - This will be the common ground for all LEDs

### 2. **Insert LEDs**
   - Place 5 LEDs in breadboard with proper polarity
   - **Long leg (Anode)** → will connect to resistors
   - **Short leg (Cathode)** → connect to GND rail
   - Space them evenly for better visual effect

### 3. **Add Current-Limiting Resistors**
   - Connect a 220Ω resistor to each LED's anode (long leg)
   - Other end of resistors connect to Arduino pins D2-D6
   - **Why 220Ω?** Limits current to ~20mA, safe for both LED and Arduino

### 4. **Wire to Arduino Pins**
   ```
   Resistor → D2 (for LED 1)
   Resistor → D3 (for LED 2)
   Resistor → D4 (for LED 3)
   Resistor → D5 (for LED 4)
   Resistor → D6 (for LED 5)
   ```

### 5. **Upload Code**
   - Open Arduino IDE
   - Copy code from `LED.blinking.ino`
   - Select: **Tools > Board > Arduino UNO**
   - Select: **Tools > Port > [Your COM Port]**
   - Click **Upload** (→ button)

### 6. **Test and Observe**
   - Watch the LEDs blink one by one
   - The pattern should flow smoothly from LED 1 to LED 5
   - Then repeat continuously

---

## 💻 Code Explanation

### Full Code:

```cpp
/*
 * Project: LED Sequential Blink
 * Author: Md. Akhinoor Islam
 * Description: 5 LEDs blink one by one in a loop
 */

const int leds[] = {2, 3, 4, 5, 6}; // LED pin numbers in array

void setup() {
  // Initialize all LED pins as outputs
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  // Light up each LED one by one
  for (int i = 0; i < 5; i++) {
    digitalWrite(leds[i], HIGH);  // Turn LED ON
    delay(300);                   // Keep lit for 300ms
    digitalWrite(leds[i], LOW);   // Turn LED OFF
    delay(100);                   // Brief gap before next LED
  }
}
```

### Code Breakdown:

#### 1️⃣ **Array Declaration**
```cpp
const int leds[] = {2, 3, 4, 5, 6};
```
| Concept | Explanation |
|---------|-------------|
| **Array** | Stores multiple pin numbers in one variable |
| **const** | Value cannot be changed during program execution |
| **leds[0]** = 2 | First LED on pin 2 |
| **leds[4]** = 6 | Fifth LED on pin 6 |

#### 2️⃣ **Setup Function**
```cpp
void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT);
  }
}
```
- Runs **once** when Arduino powers on
- **For loop** iterates 5 times (i = 0 to 4)
- Sets each pin as **OUTPUT** to send signals to LEDs

#### 3️⃣ **Loop Function**
```cpp
void loop() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(leds[i], HIGH);  // LED ON
    delay(300);                   // Wait
    digitalWrite(leds[i], LOW);   // LED OFF
    delay(100);                   // Short gap
  }
}
```

**Execution Flow:**

| Step | Action | Duration |
|------|--------|----------|
| 1 | LED 1 ON | 300ms |
| 2 | LED 1 OFF | - |
| 3 | Wait | 100ms |
| 4 | LED 2 ON | 300ms |
| 5 | LED 2 OFF | - |
| ... | Pattern continues | ... |
| Loop back | Repeat from LED 1 | Infinite |

### Key Functions:

- **`pinMode(pin, OUTPUT)`**: Configures pin to send signals
- **`digitalWrite(pin, HIGH)`**: Sends 5V to LED (turns ON)
- **`digitalWrite(pin, LOW)`**: Sends 0V to LED (turns OFF)
- **`delay(ms)`**: Pauses program for specified milliseconds

---

## 🌐 Simulation

### Try it Online:
🔗 **[View on Tinkercad](https://www.tinkercad.com/things/6ulx8HV3fon-02-led-blinking)**

You can simulate this project online:
- Interact with the circuit
- Modify timing values
- Add more LEDs
- Experiment without hardware

---

## 🔧 Troubleshooting

### Common Issues and Solutions:

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| No LEDs lighting up | Power not connected | Check GND connection from Arduino to breadboard |
| LEDs stay dim | Wrong resistor value | Use 220Ω resistors (Red-Red-Brown) |
| Random blinking | Loose wires | Firmly insert all jumper wires |
| Only some LEDs work | Incorrect pin connections | Verify D2-D6 connections match code |
| All LEDs blink together | Code issue | Re-upload the correct code |
| LEDs too bright/burn out | No resistor | ALWAYS use 220Ω resistors |

### 📌 Pro Tips:
- Use LEDs of different colors for better visual effect
- Try changing `delay(300)` to speed up or slow down
- Keep wires short and organized
- Mark each LED number with tape for easy identification
- Take a video of the working pattern!

### 🎨 Customization Ideas:
```cpp
// Faster blinking
delay(150);  // Instead of 300

// Reverse direction
for (int i = 4; i >= 0; i--)

// Bounce effect
// First loop: 0→4, Second loop: 4→0
```

---

## 🎓 Learning Outcomes

After completing this project, you will understand:

### 📚 Concepts Covered:

| Concept | Description | Real-world Use |
|---------|-------------|----------------|
| **Arrays** | Storing multiple values efficiently | Managing sensor data, pin lists |
| **For Loops** | Repeating actions without code duplication | Scanning inputs, patterns |
| **Digital Output** | Controlling HIGH/LOW states | LED control, motor direction |
| **Timing Control** | Using delays for synchronization | Debouncing, animations |
| **Pin Management** | Organizing multiple I/O pins | Multi-LED displays, keypads |

### 🚀 Skills Gained:
- ✅ Writing efficient code with loops and arrays
- ✅ Understanding program flow and iteration
- ✅ Managing multiple outputs simultaneously
- ✅ Creating timing-based animations
- ✅ Debugging sequential logic

### 🔄 Pattern Variations to Try:
1. **Ping-Pong**: Light flows left to right, then right to left
2. **Expanding**: Start from middle, expand outward
3. **Random**: LEDs light up in random order
4. **Brightness Fade**: Use PWM to fade each LED in/out

---

## 📁 Project Files

This repository contains:

| File | Description |
|------|-------------|
| `README.md` | Complete project documentation (this file) |
| `LED.blinking.ino` | Arduino source code |
| `Code Explanation (for beginner).md` | Detailed Bengali tutorial |
| `Circuit.png` | Circuit diagram screenshot |
| `LICENSE` | MIT License |

---

## 👨‍🎓 Author

**Md Akhinoor Islam**  
📚 Energy Science and Engineering (ESE)  
🏫 Khulna University of Engineering & Technology (KUET)  
🌐 [GitHub Profile](https://github.com/Akhinoor14)

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 🤝 Contributing

Want to improve this project?
- Add more LED patterns
- Optimize the code
- Create variations
- Share your improvements!

---

## ⭐ Show Your Support

If this project helped you learn, give it a ⭐ on GitHub!

---

### 📌 Next Steps:
- Try Project 03: Breathing LED (PWM control)
- Create a reverse blinking pattern
- Add a button to control speed
- Connect 10 LEDs for a longer sequence

Happy Making! 🎉
