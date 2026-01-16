# 🌈 RGB LED Control with PWM

Smoothly blend colors using **PWM signals** to control a common-cathode RGB LED with Arduino UNO. Watch the LED transition between red, green, blue, and mixed colors in a loop.

## 👨‍🎓 Developed By
Md Akhinoor Islam  
ESE (Energy Science and Engineering), KUET

---

## 🔧 Components Used

| Component       | Quantity |
|----------------|----------|
| Arduino UNO     | 1        |
| RGB LED (common cathode) | 1 |
| 220Ω Resistor   | 3        |
| Breadboard      | 1        |
| Jumper Wires    | as needed |

---

## 🔌 Circuit Overview

| LED Color | Arduino Pin | Notes                     |
|-----------|-------------|---------------------------|
| Red       | D9 (PWM)    | Through 220Ω resistor     |
| Green     | D10 (PWM)   | Through 220Ω resistor     |
| Blue      | D11 (PWM)   | Through 220Ω resistor     |
| Cathode   | GND         | Common cathode connection |

🖼️ **Circuit Diagram**  
![circuit](Circuit.png)

🔗 **Tinkercad Simulation:**  
[🔗 Click to View](https://www.tinkercad.com/things/kepNW7iwRmS-05-rgb-led-control-with-pwm)

---

## 💡 Learning Highlights

- 🎨 RGB LED পিন ফাংশন ও color-mixing idea
- 🎛️ PWM control using `analogWrite()`
- 🔁 Smooth color transitions using `for` loops
- 🧠 Common Cathode vs Common Anode difference
- 🔌 Importance of proper resistor values

---

## 📜 Code Summary

The Arduino cycles through red → green → blue by gradually fading one LED out and another in using PWM. This creates a soothing breathing-like color shift.

---

## 📂 Folder Contents

- `README.md` → This documentation  
- `code/rgb-led-pwm.ino` → Arduino code  
- `circuit.png` → Tinkercad screenshot  
- `Code & Circuit Explanation(for beginner).md` → Circuit explanation & code breakdown  
---

## ✅ Project Status

✔️ **Successfully Simulated**  
🎨 Visual and engaging color blending  
🧱 Part of Akhinoor’s 40 Arduino Project Journey!
