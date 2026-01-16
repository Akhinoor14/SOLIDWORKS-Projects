# 🔢 4×4 Matrix Keypad Interfacing with Arduino UNO

Read key presses from a 4×4 matrix keypad and display them on the Serial Monitor using the Keypad library. This project introduces matrix scanning and user input handling in embedded systems.

## 👨‍🎓 Developed By  
Md Akhinoor Islam  
ESE (Energy Science and Engineering), KUET

---

## 🔧 Components Used

| Component       | Quantity |
|------------------|----------|
| Arduino UNO       | 1        |
| 4×4 Matrix Keypad | 1        |
| Breadboard        | 1        |
| Jumper Wires      | as needed |

---

## 🔌 Circuit Overview

| Keypad Pin | Arduino Pin | Description         |
|------------|--------------|---------------------|
| ROW0       | D9           | Top row             |
| ROW1       | D8           |                     |
| ROW2       | D7           |                     |
| ROW3       | D6           | Bottom row          |
| COL0       | D5           | Leftmost column     |
| COL1       | D4           |                     |
| COL2       | D3           |                     |
| COL3       | D2           | Rightmost column    |

🖼️ **Circuit Diagram**  
![circuit](circuit.png)

🔗 **Tinkercad Simulation**  
[🔗 Click to View](https://www.tinkercad.com/things/i3NQmpJS77a-13-keypad-4x4)

---

## 💡 Learning Highlights

- 🔢 Matrix keypad scanning using Keypad library  
- 🧠 Mapping physical keys to characters  
- 💬 Displaying keypresses on Serial Monitor  
- 🧰 Library usage: `makeKeymap()`, `getKey()`  
- 🔁 Real-time user input handling

---

## 📂 Folder Contents

- `README.md` → Project overview  
- `Code & Circuit Explanation (for beginner).md` → Circuit + code explanation  
- `code/keypad-4x4.ino` → Arduino sketch  
- `circuit.png` → Tinkercad screenshot

---

## ✅ Project Status

✔️ Simulated successfully on Tinkercad  
🔘 Key presses detected and displayed  
📦 Part of Akhinoor’s 40 Arduino Project Series
