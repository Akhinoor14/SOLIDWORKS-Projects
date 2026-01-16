# 🔧 Code & Circuit Explanation (for beginner) — Project 17: Solar Tracking System

এই প্রজেক্টে Arduino UNO ব্যবহার করে ২টি servo ও ৪টি LDR দিয়ে সূর্য কোথায় আছে তা detect করে solar panel-কে ওই দিকে ঘোরানো হয় — horizontally (0–180°) এবং vertically (0–45°)। ২টি potentiometer ব্যবহার করে servo movement সীমাবদ্ধ করা যায়।

---

## 1. 🎒 যা লাগবে (Components Required)

| Component                   | Quantity | Use                         |
|------------------------------|----------|------------------------------|
| Arduino UNO                 | 1        | Microcontroller (brain)     |
| Servo Motor (SG90/MG995)    | 2        | Panel movement (H+V)        |
| LDR (Light Dependent Resistor)| 4      | Sunlight sensing            |
| 10kΩ Resistor               | 4        | LDR voltage divider         |
| Potentiometer (10kΩ)        | 2        | Servo limit control         |
| Jumper Wires + Breadboard   | as needed | Circuit building            |
| Power Supply (5V)           | 1        | Servo + Arduino power       |

---

## 2. 🔌 Circuit Connections (Easy Explanation)

### 🔶 ATmega328P (Arduino UNO) — কে কী কী নিয়ন্ত্রণ করছে

#### ☀️ Light Sensors (LDR) — সূর্যের আলো detect করতে

| Arduino Pin | Component         | Connection                          |
|--------------|-------------------|--------------------------------------|
| A0           | LDR Top-Left      | One leg → A0; Other leg → 5V  
                          ↳ 10kΩ resistor from A0 → GND |
| A1           | LDR Top-Right     | Same configuration as above         |
| A2           | LDR Bottom-Left   | Same                                |
| A3           | LDR Bottom-Right  | Same                                |

🧠 Note: প্রতিটি LDR একটি 10kΩ রেজিস্টর দিয়ে **voltage divider** করা হয়েছে  
⮕ LDR বেশি আলো পেলে তার রেজিস্ট্যান্স কমে যায় → analogRead() মান বাড়ে

---

#### 🎛️ Potentiometers — Servo movement সীমাবদ্ধ রাখতে

| Arduino Pin | Potentiometer       | Description                    |
|--------------|---------------------|--------------------------------|
| A4           | Pot H (Horizontal)  | map() করে max 0–180° set করে |
| A5           | Pot V (Vertical)    | map() করে max 0–90° set করে  |

সরাসরি pin A4/A5 → Pot wiper (middle pin)  
Pot এর দুই পাশ → GND & 5V

---

#### 🔁 Servo Motors — Panel Movement Control

| Servo        | Arduino Pin | Description                      |
|---------------|--------------|----------------------------------|
| Horizontal    | D9           | Azimuth (left-right) servo       |
| Vertical      | D10          | Elevation (up-down) servo        |
| Power (Both)  | 5V + GND     | Use external supply if needed    |

📝 External 5V power preferable  
📌 Servo signal wire → PWM pins (D9, D10)

---

## 3. 🧠 Reason Behind the Connection & How It Works

- **4টি LDR** ২x২ grid আকারে বসানো হয় → প্রত্যেক কোণে ১টি করে  
- LDR-গুলো detect করে কোন দিক থেকে আলো বেশি আসছে  
- `avgTop`, `avgBottom`, `avgLeft`, `avgRight` → average করে দেখানো হয় কোন দিক বেশি আলো  
- যদি পার্থক্য বেশি হয় (tolerance-এর চেয়ে), তাহলে servo ১° করে adjust হয়  
- `analogRead(pot)` দিয়ে servo movement limit dynamically সেট করা যায়

🎯 এইভাবে Arduino প্রতিবার loop-এ সূর্যর অবস্থান বুঝে servo-কে হালকা করে adjust করে

---

## 4. 📝 ধাপে ধাপে কী হচ্ছে

1. Arduino চালু হলে servo গুলো initial position (90°, 45°)-এ যায়  
2. প্রতি 0.3s-এ চারটি LDR থেকে মান নেয়া হয়  
3. উপর vs নিচ এবং বাম vs ডান দিকের আলো তুলনা করা হয়  
4. কোন দিক বেশি → সেইদিকে ১° করে servo ঘুরানো হয়  
5. Potentiometer অনুযায়ী servo এর ঘোরার range কন্ট্রোল হয়  
6. Panel সর্বোচ্চ সূর্যরশ্মির দিকে অটো-অ্যাডজাস্ট হয়

---

## 5. ✨ এই প্রজেক্টে কী হবে?

- Light tracking logic embedded করে servo-driven solar alignment হবে  
- শুধু ৪টি LDR দিয়েই panel-কে সূর্যের দিকে ঘোরানো  
- servo angles limit করা যাবে potentiometer দিয়ে — user programmable  
- smooth embedded control + renewable system simulation

---
# 🔍 Code Breakdown – Project 17: Solar Tracker (Dual Axis)

## 🧩 Libraries & Setup

- `#include <Servo.h>` → Servo motor control লাইব্রেরি ইনক্লুড করা হয়েছে  
- `Servo servoH, servoV;` → Horizontal এবং Vertical servo-এর জন্য object তৈরি

## 📌 Pin Assignments

| Variable        | Connected To   | Description                    |
|------------------|----------------|--------------------------------|
| ldrTopLeft       | A0             | সূর্যের উপরের-বামের দিকের আলো |
| ldrTopRight      | A1             | উপরের-ডানের আলো               |
| ldrBottomLeft    | A2             | নিচের-বামের আলো               |
| ldrBottomRight   | A3             | নিচের-ডানের আলো               |
| potH             | A4             | Horizontal movement limit      |
| potV             | A5             | Vertical movement limit        |

## ⚙️ Servo Initialization

- `servoH.attach(9);` → Horizontal servo → Pin 9  
- `servoV.attach(10);` → Vertical servo → Pin 10  
- `servo.write(pos);` → 90°, 45° → শুরুতেই মাঝখানে থাকে

## 🌞 Sensor Logic

- ৪টি LDR → সূর্যের অবস্থান detect করতে ৪ কোণ থেকে আলো পড়ে  
- average করে top vs bottom এবং left vs right compare করা হয়  
- যদি পার্থক্য `tolerance` এর বেশি হয়, তাহলে servo adjust হয়

## 🌀 Movement Control

- Horizontal servo → 0° থেকে potentiometer-controlled max পর্যন্ত ঘোরে (up to 180°)  
- Vertical servo → 0° থেকে 45° বা potentiometer অনুযায়ী  
- প্রতি loop-এ servo ১° করে adjust হয় smooth tracking-এর জন্য

## ⏱️ delay()

- `delay(300);` → প্রতি 0.3 সেকেন্ডে servo update করে, যাতে shake না হয়
---

## 6. 🚦 এখন নিজে চেষ্টা করো!

🔧 Breadboard এ circuit তৈরী করো  
🌞 ৪টি LDR একটি cardboard cruciform টেমপ্লেটে বসাও  
🔗 Arduino + Servo সঠিকভাবে সংযোগ দাও  
⚙️ potentiometer ঘোরালে servo কতটুকু ঘোরে test করো  
💡 একপাশে বেশি আলো দিলে servo ওই দিকে যাচ্ছে কিনা দেখে verify করো  

🎉 এবার তোমার নিজস্ব mini solar tracker চালু!

