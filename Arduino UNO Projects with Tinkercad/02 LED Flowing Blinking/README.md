# 🔁 LED Sequential Blink

This Arduino project blinks **five LEDs one by one in a loop**, creating a simple yet rhythmic visual effect.

## 👨‍🎓 Developed By
Md Akhinoor Islam  
ESE (Energy Science and Engineering), KUET

---

## ⚙️ Components Used

| Component       | Quantity |
|----------------|----------|
| Arduino UNO     | 1        |
| LED             | 5        |
| 220Ω Resistor   | 5        |
| Breadboard      | 1        |
| Jumper Wires    | as needed |

---

## 🔌 Circuit Connection

- LED 1 → D2 pin  
- LED 2 → D3 pin  
- LED 3 → D4 pin  
- LED 4 → D5 pin  
- LED 5 → D6 pin  
Each LED is connected in series with a 220Ω resistor and goes to GND.

🖼️ **Circuit Diagram:**  
![Circuit](Circuit.png)

🔗 **Tinkercad Simulation:**  
[🔗 View Live](https://www.tinkercad.com/things/6ulx8HV3fon-02-led-blinking)

---

## 💡 Learning Highlights

- `for loop` for repeating actions  
- `array` to handle multiple pins  
- `digitalWrite()` to control LEDs  
- `delay()` for timed blinking  
- Basic understanding of **Arduino pin mapping** and breadboard wiring

---

## 🧠 Code Summary

Each LED is turned on, waits 300ms, turns off, waits 100ms, then moves to the next. The sequence continues in a loop.

---

## 📂 Folder Contents

- `README.md` → This file  
- `circuit.png` → Your Tinkercad screenshot  
- `code/led-sequential.ino` → Arduino source code
- `Code & Circuit Explanation(for beginner).md` → Circuit explanation & code breakdown  
---

## ✅ Status

🚧 **Completed**  
📌 Uploaded on GitHub  
🧱 Part of Akhinoor’s 40-project journey  
