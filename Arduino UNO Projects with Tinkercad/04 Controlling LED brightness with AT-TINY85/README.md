# 🌟 ATtiny85 LED Brightness Controller

Control the brightness of an LED using a potentiometer with a compact **ATtiny85 microcontroller**, powered by just a 3V battery.

## 👨‍🎓 Developed By
Md Akhinoor Islam  
ESE (Energy Science and Engineering), KUET

---

## 🛠️ Components Used

| Component      | Quantity |
|----------------|----------|
| ATtiny85        | 1        |
| LED             | 1        |
| 220Ω Resistor   | 1        |
| Potentiometer   | 1        |
| 3V Coin Battery | 1        |
| Breadboard      | 1        |
| Jumper Wires    | as needed |

---

## 🔌 Circuit Connections

- **LED**:  
  – Anode (+) → 220Ω resistor → **Pin 5 (PB0)**  
  – Cathode (–) → GND

- **Potentiometer**:  
  – Middle Pin → **Pin 2 (PB3/A3)**  
  – One Side → GND  
  – Other Side → 3V

- **Power Supply**:  
  – 3V Battery → VCC & GND pins of ATtiny85

🖼️ **Circuit Diagram:**  
![circuit](Circuit.png)

🔗 **Tinkercad Simulation:**  
[🔗 Click to View](https://www.tinkercad.com/things/jBYdqVo95Ea-04-controlling-led-brightness-with-at-tiny85)

---

## 💡 Learning Highlights

- 🎛️ Reading analog input from a potentiometer (`analogRead()`)
- 💡 Outputting PWM signals with `analogWrite()` using ATtiny85
- 📉 Mapping one range to another using `map()` function
- 🎯 Low-power microcontroller programming
- 🧠 Understanding compact circuit design

---

## 🔍 How It Works

The potentiometer sends analog voltage to the ATtiny85's pin A3 (PB3). This value (0–1023) is mapped to a PWM range (0–255), then sent to PB0 (Pin 5) using `analogWrite()` to adjust the LED's brightness.

---

## 📂 Folder Contents

- `README.md` → Project documentation  
- `circuit.png` → Circuit image from Tinkercad  
- `code/attiny-led.ino` → Arduino code for ATtiny85  
- `Code & Circuit Explanation(for beginner).md` → Circuit explanation & code breakdown  
---

## ✅ Project Status

⚡ **Working Successfully on Tinkercad**  
📦 Compact embedded system demo  
🌱 Part of Akhinoor’s 40 Arduino project journey  
