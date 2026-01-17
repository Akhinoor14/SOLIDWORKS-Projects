# 🧠 Code & Circuit Explanation (for beginner) – Project 23 (Optimized): Digital Voltmeter with ATtiny85

এই সংস্করণে আমরা ATtiny85 দিয়ে একটি ডিজিটাল ভোল্টমিটার তৈরি করব, যেখানে potentiometer দিয়ে voltage vary করা হবে, ADC দিয়ে তা পরিমাপ করা হবে, এবং 3-digit 7-segment display-এ তা দেখানো হবে। আমরা এমনভাবে সার্কিট ডিজাইন করব যাতে USB port-এ কোনো overcurrent না হয়।

---

## 1. 🎒 যা লাগবে (What You Need)

| Component               | Quantity | Description                                      |
|--------------------------|----------|--------------------------------------------------|
| ATtiny85 Microcontroller| 1        | Compact 8-pin MCU for ADC and control           |
| 74HC595 Shift Register  | 1        | Drives 7-segment display using serial data      |
| 3-Digit 7-Segment Display| 1        | Common cathode display for voltage output       |
| Potentiometer (10kΩ)    | 1        | Variable voltage source                         |
| 100 Ω Resistor          | 8        | Current limiting for each segment               |
| 2 kΩ Resistor           | 1        | Digit common line limiting                      |
| 750 Ω Resistor          | 1        | Optional: second digit line limiting            |
| USB to Serial Adapter   | 1        | For programming ATtiny85                        |
| 5V Regulated Power Supply| 1        | External power (e.g., AMS1117 or phone charger) |
| Breadboard + Jumper Wires| as needed | For prototyping                               |

---

## 2. 🔌 Circuit Connections (Pin-to-Pin Details)

### 🔹 ATtiny85 Pin Mapping

| ATtiny85 Pin | Function         | Connected To                     |
|--------------|------------------|----------------------------------|
| PB0 (D0)     | Data (DS)        | 74HC595 pin 14                   |
| PB1 (D1)     | Clock (SH_CP)    | 74HC595 pin 11                   |
| PB2 (D2)     | Latch (ST_CP)    | 74HC595 pin 12                   |
| PB3 (D3)     | Digit 1 Enable   | Digit 1 common cathode → GND via 2kΩ |
| PB4 (D4)     | Digit 2 Enable   | Digit 2 common cathode → GND via 750Ω |
| A1 (PB2)     | Analog Input     | Potentiometer middle pin         |
| VCC          | Power            | 5V regulated supply              |
| GND          | Ground           | Common ground                    |
| RESET        | Programming only | Not used in runtime              |

---

### 🔹 74HC595 to 7-Segment Display

| 74HC595 Pin | Connected To         | Through Resistor | Segment |
|-------------|----------------------|------------------|---------|
| Q0 (15)     | Segment A            | 100Ω             | A       |
| Q1 (1)      | Segment B            | 100Ω             | B       |
| Q2 (2)      | Segment C            | 100Ω             | C       |
| Q3 (3)      | Segment D            | 100Ω             | D       |
| Q4 (4)      | Segment E            | 100Ω             | E       |
| Q5 (5)      | Segment F            | 100Ω             | F       |
| Q6 (6)      | Segment G            | 100Ω             | G       |
| Q7 (7)      | Segment DP (optional)| 100Ω             | Decimal |

> All segment resistors must be 100Ω to limit current and prevent USB overload.

---

### 🔹 Potentiometer Wiring

| Potentiometer Pin | Connected To |
|-------------------|--------------|
| Left Pin          | GND          |
| Right Pin         | 5V           |
| Middle Pin        | A1 (PB2)     |

---

### 🔹 Power Supply

- Use a **regulated 5V adapter** (e.g., phone charger or AMS1117 module)
- Connect **GND of USB programmer and external supply together**
- Avoid powering display directly from USB port

---

## 3. 🧠 Reason Behind the Connection & How It Works

- **Potentiometer** acts as a variable voltage source (0–5V)
- **ATtiny85 ADC** reads voltage from A1 and converts it to a 10-bit value (0–1023)
- Voltage is scaled and split into 3 digits (e.g., 4.23V → 423 → 4, 2, 3)
- **74HC595** receives serial data from ATtiny85 and drives the 7-segment segments
- **Multiplexing** is done by enabling one digit at a time using PB3, PB4
- **100Ω resistors** limit current per segment (~15mA max)
- **2kΩ and 750Ω resistors** limit current through digit commons

---

## 4. 📝 ধাপে ধাপে কী হচ্ছে (Step-by-Step Workflow)

1. `analogRead(A1)` → potentiometer থেকে voltage রিড করা হয়  
2. ADC মানকে voltage এ রূপান্তর করা হয় (0–5V)  
3. voltage × 100 করে integer তে রূপান্তর (e.g., 4.23 → 423)  
4. 3-digit এ ভাগ করে shift register-এ পাঠানো হয়  
5. প্রতিটি digit ৫ms করে enable করা হয় → multiplexed display  
6. Display smooth দেখায় এবং USB port safe থাকে  

---

## 5. ✨ এই প্রজেক্টে কী হবে (Project Outcome)

- ATtiny85 দিয়ে ADC রিডিং ও voltage পরিমাপ শেখা যাবে  
- 74HC595 shift register দিয়ে 7-segment display কন্ট্রোল করা শিখবে  
- Multiplexing কিভাবে কাজ করে তা বোঝা যাবে  
- USB overcurrent সমস্যা ছাড়াই practical embedded system তৈরি করা যাবে  
- Power optimization, resistor sizing, এবং display timing সম্পর্কে ধারণা তৈরি হবে  

---

## 6. 🚦 এখন নিজে চেষ্টা করো! (Hands-On Challenge)

- Breadboard এ ATtiny85, 74HC595, এবং 3-digit display connect করো  
- প্রতিটি segment-এর সাথে 100Ω resistor বসাও  
- Digit common pin-এ 2kΩ ও 750Ω resistor বসাও  
- Potentiometer দিয়ে voltage vary করো  
- কোড আপলোড করে display তে voltage দেখো  
- USB port গরম হচ্ছে কিনা বা shutdown হচ্ছে কিনা তা পর্যবেক্ষণ করো  
- Optional: External 5V supply দিয়ে display আরও stable করো  

---
