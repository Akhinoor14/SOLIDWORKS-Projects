# 🌈 RGB LED Color Control with PWM

![Arduino Project](https://img.shields.io/badge/Arduino-UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Beginner-green?style=for-the-badge)
![Concept](https://img.shields.io/badge/Concept-RGB_PWM-purple?style=for-the-badge)

## 📋 Table of Contents
- [Overview](#-overview)
- [Components Required](#-components-required)
- [RGB LED Basics](#-rgb-led-basics)
- [Circuit Diagram](#-circuit-diagram)
- [How It Works](#-how-it-works)
- [Step-by-Step Guide](#-step-by-step-guide)
- [Code Explanation](#-code-explanation)
- [Color Mixing Theory](#-color-mixing-theory)
- [Simulation](#-simulation)
- [Troubleshooting](#-troubleshooting)
- [Learning Outcomes](#-learning-outcomes)
- [Author](#-author)

---

## 🎯 Overview

This project demonstrates **RGB LED color mixing** using PWM (Pulse Width Modulation). An RGB LED contains three separate LEDs (Red, Green, Blue) in one package. By controlling the brightness of each color independently, you can create millions of color combinations!

### Key Features:
- ✅ Smooth color transitions between red, green, and blue
- ✅ Three independent PWM channels
- ✅ Additive color mixing demonstration
- ✅ Breathing effect applied to colors
- ✅ Foundation for full-color LED displays and lighting

---

## 🧰 Components Required

| Component | Quantity | Specification |
|-----------|----------|---------------|
| Arduino UNO | 1 | ATmega328P based |
| RGB LED (Common Cathode) | 1 | 5mm, 4-pin |
| Resistor | 3 | 220Ω (Red-Red-Brown) |
| Breadboard | 1 | Full-size or half-size |
| Jumper Wires | 10-12 | Male-to-Male |

### 💰 Estimated Cost: $4-6 USD

---

## 🎨 RGB LED Basics

### What is an RGB LED?

An RGB LED is essentially **three LEDs in one package**:
- 🔴 **Red LED**
- 🟢 **Green LED**
- 🔵 **Blue LED**

### Common Cathode vs Common Anode:

```
Common Cathode (this project):        Common Anode:
┌─────────────┐                       ┌─────────────┐
│    RED   ●──┤─► to Arduino PWM      │    RED   ●──┤─► to Arduino PWM
│   GREEN  ●──┤─► to Arduino PWM      │   GREEN  ●──┤─► to Arduino PWM
│    BLUE  ●──┤─► to Arduino PWM      │    BLUE  ●──┤─► to Arduino PWM
│  CATHODE ●──┤─► to GND (-)          │   ANODE  ●──┤─► to VCC (+)
└─────────────┘                       └─────────────┘

We're using Common Cathode!
```

### RGB LED Pinout:

```
Looking at LED from front:
┌───────────┐
│    ___    │
│   (●●●)   │  ← Three LED chips inside
│   ||||    │
│   ||||    │
└───┬┴┬┴────┘
    R C G B
    
R = Red
C = Common Cathode (longest pin)
G = Green
B = Blue
```

---

## 🔌 Circuit Diagram

### Connection Table:

| RGB LED Pin | Resistor | Arduino Pin | Notes |
|-------------|----------|-------------|-------|
| Red | 220Ω | D9 (PWM) | Controls red intensity |
| Green | 220Ω | D10 (PWM) | Controls green intensity |
| Blue | 220Ω | D11 (PWM) | Controls blue intensity |
| Cathode (longest) | None | GND | Common ground |

### Why 3 Resistors?

Each color LED has different forward voltage:
- Red LED: ~2.0V
- Green LED: ~3.2V
- Blue LED: ~3.2V

Using 220Ω resistor for all provides adequate protection.

### Circuit Wiring:

```
Arduino UNO
┌─────────────┐
│             │                RGB LED
│  D9  ●──────┼──[220Ω]──────● Red
│             │
│  D10 ●──────┼──[220Ω]──────● Green
│             │
│  D11 ●──────┼──[220Ω]──────● Blue
│             │
│  GND ●──────┼──────────────● Cathode (longest)
│             │
└─────────────┘

Note: Each color through its own resistor!
```

### 🖼️ Circuit Diagram:
![RGB LED PWM Control](Circuit.png)

---

## ⚙️ How It Works

### Color Mixing Principle:

RGB LEDs use **additive color mixing** - combining light to create colors.

```
Primary Colors (Maximum Intensity):
🔴 Red (255, 0, 0)
🟢 Green (0, 255, 0)
🔵 Blue (0, 0, 255)

Secondary Colors (Mix two):
🟡 Yellow = Red + Green (255, 255, 0)
🔵 Cyan = Green + Blue (0, 255, 255)
🟣 Magenta = Red + Blue (255, 0, 255)

White:
⚪ White = Red + Green + Blue (255, 255, 255)

Black (Off):
⚫ Black = No light (0, 0, 0)
```

### PWM Control:

Each color channel is controlled independently:
- PWM value 0 = Color OFF
- PWM value 128 = 50% brightness
- PWM value 255 = Full brightness

### Animation Logic:

The code creates smooth transitions:
1. **Red to Green:** Red fades out while green fades in
2. **Green to Blue:** Green fades out while blue fades in
3. **Blue to Red:** Blue fades out while red fades in
4. Loop repeats infinitely

```
Color Transition Timeline:
Time:    0s      2.5s     5s      7.5s     10s
        ┌────────┬────────┬────────┬────────┐
Red:    █████████░░░░░░░░░░░░░░░░░░░░█████████
Green:  ░░░░░░░░░█████████░░░░░░░░░░░░░░░░░░░░
Blue:   ░░░░░░░░░░░░░░░░░░█████████░░░░░░░░░░░
        └────────┴────────┴────────┴────────┘
        Red→Grn  Grn→Blue Blue→Red  Loop...
```

---

## 📝 Step-by-Step Guide

### 1. **Identify RGB LED Type**
   - Check if it's **Common Cathode** or **Common Anode**
   - This project uses **Common Cathode**
   - Common pin is the **longest** pin

### 2. **Insert RGB LED**
   - Place LED in breadboard
   - Note pin positions (usually R-C-G-B or similar)
   - Longest pin = Cathode = to GND

### 3. **Add Resistors**
   - Connect 220Ω resistor to Red pin
   - Connect 220Ω resistor to Green pin
   - Connect 220Ω resistor to Blue pin
   - **Important:** Each color needs its own resistor!

### 4. **Wire to Arduino**
   ```
   Red resistor → D9
   Green resistor → D10
   Blue resistor → D11
   Cathode (longest pin) → GND
   ```

### 5. **Verify Connections**
   - Double-check each color is on correct PWM pin
   - Ensure common cathode is connected to GND
   - Resistors are in series with each color

### 6. **Upload Code**
   - Open Arduino IDE
   - Copy code from `rgb-pwm.ino`
   - Select: **Tools > Board > Arduino UNO**
   - Select: **Tools > Port > [Your COM Port]**
   - Click **Upload**

### 7. **Observe Color Transitions**
   - LED should smoothly transition through colors
   - Red → Yellow → Green → Cyan → Blue → Magenta → Red
   - If colors are wrong, check pin connections

---

## 💻 Code Explanation

### Full Code:

```cpp
/*
 * Project: RGB LED Control with PWM
 * Author: Md. Akhinoor Islam
 * Description: Smoothly transition between RGB colors
 */

const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Phase 1: Red to Green
  for (int i = 0; i <= 255; i++) {
    analogWrite(redPin, 255 - i);    // Red fades out
    analogWrite(greenPin, i);        // Green fades in
    analogWrite(bluePin, 0);         // Blue stays off
    delay(10);
  }

  // Phase 2: Green to Blue
  for (int i = 0; i <= 255; i++) {
    analogWrite(redPin, 0);          // Red stays off
    analogWrite(greenPin, 255 - i);  // Green fades out
    analogWrite(bluePin, i);         // Blue fades in
    delay(10);
  }

  // Phase 3: Blue to Red
  for (int i = 0; i <= 255; i++) {
    analogWrite(redPin, i);          // Red fades in
    analogWrite(greenPin, 0);        // Green stays off
    analogWrite(bluePin, 255 - i);   // Blue fades out
    delay(10);
  }
}
```

### Code Breakdown:

#### 1️⃣ **Pin Definitions**
```cpp
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
```
- All three pins are PWM-capable (marked with ~)
- Each controls one color channel independently

#### 2️⃣ **Setup Function**
```cpp
void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}
```
- Configures all three pins as outputs
- Allows PWM signals to be sent

#### 3️⃣ **Color Transition Loops**

**Red to Green Transition:**
```cpp
for (int i = 0; i <= 255; i++) {
  analogWrite(redPin, 255 - i);    // Decreases from 255 to 0
  analogWrite(greenPin, i);        // Increases from 0 to 255
  analogWrite(bluePin, 0);         // Stays off
  delay(10);
}
```

**Iteration Examples:**

| i | Red | Green | Blue | Resulting Color |
|---|-----|-------|------|-----------------|
| 0 | 255 | 0 | 0 | Pure Red |
| 64 | 191 | 64 | 0 | Orange-Red |
| 128 | 127 | 128 | 0 | Yellow-Orange |
| 191 | 64 | 191 | 0 | Yellow-Green |
| 255 | 0 | 255 | 0 | Pure Green |

**Total transition time:** 255 × 10ms = 2.55 seconds

### Key Functions:

| Function | Purpose | Parameters |
|----------|---------|------------|
| `analogWrite(pin, value)` | Set PWM duty cycle | pin: 9, 10, 11<br>value: 0-255 |
| `pinMode(pin, OUTPUT)` | Configure pin | Sets as output |
| `delay(ms)` | Pause execution | Time in milliseconds |

---

## 🎨 Color Mixing Theory

### RGB Color Model:

```
RGB Cube Representation:
        White (255,255,255)
            ●
           /|\
          / | \
         /  |  \
    Yellow  |  Cyan
       ●    |    ●
       |    |   /
       |    |  /
       |    | /
       |    |/
   Red ●────●───● Blue
        \   |
         \  |
          \ |
           \|
            ●
          Green

Mixing Rules:
Red + Green = Yellow
Green + Blue = Cyan
Blue + Red = Magenta
All three = White
```

### Common Colors (R, G, B):

| Color | Red | Green | Blue | Hex Code |
|-------|-----|-------|------|----------|
| 🔴 Red | 255 | 0 | 0 | #FF0000 |
| 🟢 Green | 0 | 255 | 0 | #00FF00 |
| 🔵 Blue | 0 | 0 | 255 | #0000FF |
| 🟡 Yellow | 255 | 255 | 0 | #FFFF00 |
| 🔵 Cyan | 0 | 255 | 255 | #00FFFF |
| 🟣 Magenta | 255 | 0 | 255 | #FF00FF |
| ⚪ White | 255 | 255 | 255 | #FFFFFF |
| ⚫ Black | 0 | 0 | 0 | #000000 |
| 🟠 Orange | 255 | 165 | 0 | #FFA500 |
| 🟣 Purple | 128 | 0 | 128 | #800080 |
| 🩷 Pink | 255 | 192 | 203 | #FFC0CB |

---

## 🌐 Simulation

### Try it Online:
🔗 **[View on Tinkercad](https://www.tinkercad.com/things/kepNW7iwRmS-05-rgb-led-control-with-pwm)**

Simulation features:
- Interactive RGB LED visualization
- Real-time color mixing
- Modify code to create custom patterns
- Learn color theory hands-on

---

## 🔧 Troubleshooting

### Common Issues:

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| Only one color works | Wrong pin connections | Verify D9=Red, D10=Green, D11=Blue |
| Wrong colors showing | Pins mixed up | Check RGB LED datasheet for pin order |
| Very dim LED | High resistor values | Use 220Ω, not 1kΩ |
| LED not working | Common Anode LED used | Code is for Common Cathode |
| Colors not mixing | One color not working | Check that color's resistor and connection |
| Flickering | Loose wires | Secure all connections |

### Testing Individual Colors:

```cpp
// Test Red
analogWrite(redPin, 255);
analogWrite(greenPin, 0);
analogWrite(bluePin, 0);
delay(1000);

// Test Green
analogWrite(redPin, 0);
analogWrite(greenPin, 255);
analogWrite(bluePin, 0);
delay(1000);

// Test Blue
analogWrite(redPin, 0);
analogWrite(greenPin, 0);
analogWrite(bluePin, 255);
delay(1000);
```

### For Common Anode LED:

If you have a Common Anode RGB LED, invert all values:
```cpp
analogWrite(redPin, 255 - value);  // Invert
// Connect common pin to 5V instead of GND
```

---

## 🎓 Learning Outcomes

### 📚 Concepts Covered:

| Concept | Description | Applications |
|---------|-------------|--------------|
| **RGB Color Model** | Additive color mixing | Displays, lighting, graphics |
| **Multi-channel PWM** | Controlling multiple outputs | Motor control, LED arrays |
| **Color Theory** | Primary, secondary colors | Design, art, visualization |
| **Simultaneous Control** | Managing parallel signals | Robotics, automation |
| **Fading Algorithms** | Smooth transitions | Animation, UI effects |

### 🚀 Skills Gained:
- ✅ Understanding RGB color representation
- ✅ Multi-channel PWM control
- ✅ Creating smooth animations
- ✅ Color mixing and theory
- ✅ Foundation for addressable LED strips (WS2812B, NeoPixels)

### 🔄 Project Extensions:

1. **Mood Light** - Slow, relaxing color changes
2. **Music Reactive** - Colors change with sound
3. **Potentiometer Control** - Manually select colors
4. **Temperature Display** - Color indicates temperature
5. **RGB Strip** - Control multiple RGB LEDs
6. **HSV Color Space** - Use Hue-Saturation-Value model
7. **Sunrise/Sunset** - Natural light simulation

---

## 📁 Project Files

| File | Description |
|------|-------------|
| `README.md` | Complete project documentation |
| `rgb-pwm.ino` | Arduino source code |
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
- Add color patterns (rainbow, strobe, etc.)
- Implement HSV color space
- Add button control for modes
- Create color wheel interface
- Share your creative patterns!

---

## ⭐ Show Your Support

If this helped you understand RGB LEDs, give it a ⭐!

---

### 📌 Next Steps:
- Build an RGB mood lamp
- Control WS2812B LED strips
- Create a color-changing nightlight
- Design RGB notification system
- Build ambient lighting for monitor

Happy Creating! 🎉
