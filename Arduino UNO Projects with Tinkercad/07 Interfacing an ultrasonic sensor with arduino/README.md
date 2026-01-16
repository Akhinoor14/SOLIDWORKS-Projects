# 📏 Ultrasonic Sensor Interfacing with Arduino

Measure distance with sound! This project uses the **HC-SR04 ultrasonic sensor** to calculate how far an object is from your Arduino UNO using sound wave reflection.

## 👨‍🎓 Developed By
Md Akhinoor Islam  
ESE (Energy Science and Engineering), KUET

---

## 🛠️ Components Used

| Component             | Quantity |
|------------------------|----------|
| Arduino UNO             | 1        |
| Ultrasonic Sensor (HC-SR04) | 1     |
| Breadboard              | 1        |
| Jumper Wires            | as needed |

---

## 🔌 Circuit Connections

| HC-SR04 Pin | Arduino Pin | Function         |
|-------------|-------------|------------------|
| VCC         | 5V          | Power             |
| GND         | GND         | Ground            |
| Trig        | D9          | Trigger Signal    |
| Echo        | D10         | Echo Response     |

🖼️ **Circuit Diagram**  
![circuit](Circuit.png)

🔗 **Tinkercad Simulation**  
[🔗 Click to View](https://www.tinkercad.com/things/cCuOhTyFwlL-07-ultrasonic-sensor-interfacing)

---

## 💡 Learning Highlights

- 🧠 How HC-SR04 measures distance using ultrasonic waves
- 📏 Use of `pulseIn()` and time-to-distance conversion
- 🧪 Basic physics: speed of sound (~343 m/s)
- 🕹️ Reading and processing digital signals
- 🖥️ Using `Serial Monitor` for debugging and output display

---

## 📜 Code Summary

The sensor sends out a high-frequency sound wave via **Trig**, and listens for its echo via **Echo**. The time between send and receive is used to calculate the distance.

---

## 📂 Folder Contents

- `README.md` → Project documentation  
- `code/ultrasonic-distance.ino` → Arduino source code  
- `circuit.png` → Tinkercad screenshot  
- `Code & Circuit Explanation(for beginner).md` → Circuit explanation & code breakdown  
---

## ✅ Project Status

✔️ **Working successfully** on Tinkercad  
📏 Accurate distance measurement  
🧭 Part of Akhinoor’s 40 Arduino Project journey  
