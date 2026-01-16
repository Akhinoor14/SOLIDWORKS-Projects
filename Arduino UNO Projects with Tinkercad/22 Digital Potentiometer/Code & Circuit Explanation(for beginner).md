# 🧠 Code & Circuit Explanation (for beginner) – Project 22: Digital Potentiometer with Arduino

এই প্রজেক্টে আমরা একটি voltage divider তৈরি করব 1MΩ এবং 10kΩ রেজিস্টর দিয়ে। Arduino সেই divider-এর মাঝখান থেকে voltage পরিমাপ করবে, divider formula ব্যবহার করে মূল input voltage হিসাব করবে এবং LCD তে তা দেখাবে।

---

## 1. 🎒 যা লাগবে (What You Need)

| Component             | Quantity | Description                                 |
|------------------------|----------|---------------------------------------------|
| Arduino UNO           | 1        | Main controller board                       |
| 16x2 LCD (parallel)   | 1        | Display for voltage readout                 |
| 1 MΩ Resistor         | 1        | Upper resistor in voltage divider           |
| 10 kΩ Resistor        | 1        | Lower resistor in voltage divider           |
| 220 Ω Resistor        | 1        | Optional: LCD backlight current limiting    |
| Breadboard + Jumper Wires | as needed | For connections                        |
| USB Cable / 5V Supply | 1        | Power for Arduino                           |

---

## 2. 🔌 Circuit Connections (pin-to-pin details)

| Arduino Pin | Connected To                  | Description                                |
|-------------|-------------------------------|--------------------------------------------|
| A0          | Node between 1MΩ & 10kΩ       | Analog voltage input from divider          |
| 5V          | Top of 1MΩ resistor           | Voltage source for divider                 |
| GND         | Bottom of 10kΩ resistor       | Ground reference                           |
| D12–D2      | LCD RS, E, D4–D7              | Parallel LCD control pins                  |
| 5V / GND    | LCD VCC, GND                  | Power supply for LCD                       |
| Potentiometer (optional) | LCD contrast pin | Adjust LCD visibility                      |

> **Node A** = 1MΩ এবং 10kΩ রেজিস্টরের সংযোগস্থল → এখানেই voltage divider এর output পাওয়া যায়, যা A0 পিনে যায়।

---

## 3. 🧠 Reason Behind the Connection & How It Works

- **Voltage Divider Principle:**  
  1MΩ ও 10kΩ রেজিস্টর সিরিজে সংযুক্ত → মাঝখানের পয়েন্টে (Node A) ভোল্টেজ পাওয়া যায়  
  এই ভোল্টেজ নির্ভর করে রেজিস্টরের অনুপাতে:  
  

\[
  V_{out} = V_{in} \times \frac{R_2}{R_1 + R_2}
  \]

  
  যেখানে R₁ = 1MΩ, R₂ = 10kΩ

- **Analog Read & Conversion:**  
  A0 পিনে voltage measure করা হয় → analogRead() মান 0–1023 এর মধ্যে  
  তারপর সেই মানকে ভোল্টেজে রূপান্তর করা হয়:  
  `vout = (sensorValue × 5.0) / 1023.0`

- **Input Voltage Calculation:**  
  Divider formula ব্যবহার করে মূল input voltage হিসাব করা হয়:  
  `input_voltage = vout × ((r1 + r2) / r2)`

- **LCD Display:**  
  LCD তে প্রথম লাইনে “Digital Voltage” এবং দ্বিতীয় লাইনে রিয়েল-টাইম voltage দেখানো হয়

---

## 4. 📝 ধাপে ধাপে কী হচ্ছে (Step-by-Step Workflow)

1. `setup()` এ LCD initialize হয় এবং “Digital Voltage” লেখা দেখানো হয়  
2. `loop()` এ analogRead(A0) দিয়ে voltage divider এর output measure করা হয়  
3. ADC মানকে voltage এ রূপান্তর করা হয় (vout)  
4. Divider formula দিয়ে মূল input voltage হিসাব করা হয়  
5. LCD তে দ্বিতীয় লাইনে সেই voltage দেখানো হয় (দুই দশমিক ঘর সহ)  
6. Serial Monitor এ একই voltage print হয় debugging এর জন্য  
7. প্রতি ০.৫ সেকেন্ডে আপডেট হয়  

---

## 5. ✨ এই প্রজেক্টে কী হবে (Project Outcome)

- Voltage divider কিভাবে কাজ করে তা বোঝা যাবে  
- Analog input থেকে voltage কিভাবে পরিমাপ করতে হয় তা শেখা যাবে  
- Divider formula ব্যবহার করে মূল input voltage নির্ণয় করা যাবে  
- LCD তে রিয়েল-টাইম ডেটা দেখানোর অভ্যাস হবে  
- ADC, voltage scaling, এবং display formatting সম্পর্কে ধারণা তৈরি হবে  

---
# 🔍 Code Breakdown 

এই কোডে আমরা একটি voltage divider থেকে ভোল্টেজ রিড করব, divider-এর রেজিস্টর অনুপাতে মূল input voltage হিসাব করব, এবং তা LCD তে দেখাবো।

---

## 📌 Pin Declarations

| Name           | Pin   | Description                              |
|----------------|--------|------------------------------------------|
| `analogPin`    | A0     | Voltage divider output → analog input    |
| `lcd`          | D12–D2 | LCD control pins (RS, E, D4–D7)          |

---

## ⚙️ Variable Declarations

- `float r1 = 1000000.0;`  
  ➤ Upper resistor (1MΩ) — divider এর উপরের অংশ

- `float r2 = 10000.0;`  
  ➤ Lower resistor (10kΩ) — divider এর নিচের অংশ

- `float input_voltage = 0.0;`  
  ➤ মূল input voltage হিসাব করার জন্য ভেরিয়েবল

---

## ⚙️ setup()

- `lcd.begin(16, 2);`  
  ➤ 16x2 LCD initialize করা হয়

- `lcd.print("Digital Voltage");`  
  ➤ প্রথম লাইনে টাইটেল দেখানো হয়

- `Serial.begin(9600);`  
  ➤ Serial Monitor debugging এর জন্য চালু করা হয়

---

## 🔁 loop()

1. `analogRead(analogPin);`  
   ➤ A0 পিন থেকে ADC মান (0–1023) রিড করা হয়

2. `vout = (sensorValue * 5.0) / 1023.0;`  
   ➤ ADC মানকে ভোল্টেজে রূপান্তর করা হয় (assuming 5V reference)

3. `input_voltage = vout * ((r1 + r2) / r2);`  
   ➤ Voltage divider formula ব্যবহার করে মূল input voltage হিসাব করা হয়  
   ➤ Formula:  
   

\[
   V_{in} = V_{out} \times \left( \frac{R_1 + R_2}{R_2} \right)
   \]



4. `lcd.setCursor(0, 1);`  
   ➤ দ্বিতীয় লাইনে কার্সর সেট করা হয়

5. `lcd.print(input_voltage, 2);`  
   ➤ ভোল্টেজ ২ দশমিক ঘর পর্যন্ত দেখানো হয়

6. `Serial.println(input_voltage);`  
   ➤ Serial Monitor-এ debugging এর জন্য voltage print করা হয়

7. `delay(500);`  
   ➤ প্রতি ০.৫ সেকেন্ডে আপডেট হয়

---

## 🎯 Logic Summary

- 1MΩ ও 10kΩ রেজিস্টর দিয়ে voltage divider তৈরি  
- A0 পিনে সেই voltage measure করা হয়  
- Divider formula দিয়ে মূল input voltage হিসাব করা হয়  
- LCD তে real-time voltage দেখানো হয়  
- Serial Monitor দিয়ে debugging সহজ হয়  

## 6. 🚦 এখন নিজে চেষ্টা করো! (Hands-On Challenge)

- Breadboard এ 1MΩ ও 10kΩ রেজিস্টর দিয়ে voltage divider তৈরি করো  
- Node A কে A0 পিনে connect করো  
- LCD ঠিকভাবে parallel mode এ connect করো (RS, E, D4–D7)  
- কোড আপলোড করে LCD তে voltage দেখো  
- 5V supply এর পরিবর্তে অন্য voltage source দিয়ে divider test করো  
- রেজিস্টরের মান পরিবর্তন করে voltage scaling কিভাবে বদলায় তা পর্যবেক্ষণ করো  
- Serial Monitor খুলে voltage রিডিং যাচাই করো  

---
