# 📷 Interfacing Photodiode with Arduino UNO

Use a photodiode to detect light intensity and monitor changes through Arduino’s analog input. The setup demonstrates how a basic voltage divider enables analog light sensing.

## 👨‍🎓 Developed By
Md Akhinoor Islam  
ESE (Energy Science and Engineering), KUET

---

## 🔧 Components Used

| Component        | Quantity |
|------------------|----------|
| Arduino UNO       | 1        |
| Photodiode        | 1        |
| 10kΩ Resistor     | 1        |
| Breadboard        | 1        |
| Jumper Wires      | as needed |

---

## 🔌 Circuit Overview

| Connection Point | Arduino Pin | Description                        |
|------------------|-------------|------------------------------------|
| Photodiode +     | +5V         | Power supply (if needed)           |
| Photodiode –     | A0 via resistor → GND | Voltage divider setup    |

🖼️ **Circuit Diagram**  
![circuit](Circuit.png)

🔗 **Tinkercad Simulation**  
[🔗 Click to View](https://www.tinkercad.com/things/5uG3RNVzWWe-10-interfacingphotodiode)

---

## 💡 Learning Highlights

- 🌞 Light-sensing using analog voltage changes  
- 🧪 Working principle of reverse-biased photodiodes  
- 🔁 Voltage divider usage with analogRead()  
- 💬 Serial Monitor-based real-time feedback

---

## 📂 Folder Contents

- `README.md` → Project description  
- `Code & Circuit Explanation(for beginner).md` → Circuit + line-by-line explanation  
- `code/photo-diode.ino` → Arduino sketch  
- `circuit.png` → Simulation screenshot  

---

## ✅ Project Status

✔️ Verified in Tinkercad  
📷 Photodiode response is analog and stable  
📦 Part of Akhinoor’s 40 Project Arduino Series  
