# 🔌 Circuit Connections

| Component       | Arduino Pin | Description                         |
|------------------|-------------|-------------------------------------|
| PIR OUT          | D2          | Sensor digital output to Arduino    |
| PIR VCC          | 5V          | Power to sensor                     |
| PIR GND          | GND         | Common ground                       |
| LED (+)          | D13 or any PWM pin | Series 220Ω resistor → GND |
| Resistor (220Ω)  | In series with LED | Limits current through LED  |

📌 Note: If using an external LED, connect it via 220Ω resistor to any digital pin (like D9, D13). Built-in LED on pin 13 is optional for simulation.

---

# 🧠 Code Explanation (Line by Line)

- `const int pirPin = 2;`  
  ▸ PIR sensor-এর digital output Arduino-এর D2 পিনে নিয়েছি।

- `const int ledPin = 13;`  
  ▸ LED সংযুক্ত করা হয়েছে pin 13 এ (onboard বা external)।

- `pinMode(pirPin, INPUT);`  
  ▸ PIR sensor থেকে input নেওয়ার জন্য সেট করা হয়েছে।

- `digitalRead(pirPin);`  
  ▸ Motion আছে কিনা তা পড়া হচ্ছে (HIGH = motion detected)।

- `digitalWrite(ledPin, HIGH/LOW);`  
  ▸ Motion পেলে LED জ্বলে, না পেলে নিভে যায়।

- `Serial.println()`  
  ▸ Monitor-এ "Motion Detected!" বা "No Motion" দেখায়।

- `delay(500);`  
  ▸ প্রতি ০.৫ সেকেন্ডে আপডেট রিফ্রেশ হয়।

---
✨ এই প্রজেক্টে কী হবে?
==========================
- PIR sensor দিয়ে Arduino UNO-তে মুভমেন্ট (motion) ডিটেক্ট করা শিখবে
- মুভমেন্ট হলে LED জ্বলবে, না হলে নিভে যাবে

🔌 সার্কিট কানেকশন (Circuit Connection)
==========================
**যা লাগবে:**
- Arduino UNO
- ১টি PIR sensor
- ১টি LED (onboard D13 বা external)
- ১টি 220Ω resistor (external LED হলে)
- Jumper Wires

**কানেকশন টেবিল:**
| Component       | Arduino Pin         | কাজ/ব্যাখ্যা                          |
|-----------------|---------------------|---------------------------------------|
| PIR OUT         | D2                  | Sensor digital output to Arduino      |
| PIR VCC         | 5V                  | Power to sensor                       |
| PIR GND         | GND                 | Common ground                         |
| LED (+)         | D13 বা যেকোনো digital pin | Series 220Ω resistor → GND      |
| Resistor (220Ω) | In series with LED  | LED-তে current কমানোর জন্য            |

**নোট:**  
- External LED ব্যবহার করলে 220Ω resistor দিয়ে যেকোনো digital pin (যেমন D9, D13)-এ সংযুক্ত করো  
- Built-in LED (D13) simulation-এর জন্য সহজ

💡 কোড ব্যাখ্যা (Code Explanation)
==========================

| অংশ | কী বোঝায়? |
|------|-----------|
| `const int pirPin = 2;` | PIR sensor-এর digital output Arduino-এর D2 পিনে নেওয়া হয়েছে |
| `const int ledPin = 13;` | LED সংযুক্ত করা হয়েছে pin 13-এ (onboard বা external) |
| `pinMode(pirPin, INPUT);` | PIR sensor থেকে input নেওয়ার জন্য সেট করা হয়েছে |
| `digitalRead(pirPin);` | Motion আছে কিনা তা পড়া হচ্ছে (HIGH = motion detected) |
| `digitalWrite(ledPin, HIGH/LOW);` | Motion পেলে LED জ্বলে, না পেলে নিভে যায় |
| `Serial.println()` | Monitor-এ "Motion Detected!" বা "No Motion" দেখায় |
| `delay(500);` | প্রতি ০.৫ সেকেন্ডে আপডেট রিফ্রেশ হয় |

📝 ধাপে ধাপে কী হচ্ছে (Step-by-Step)
==========================
1. PIR sensor-এর OUT, VCC, GND যথাযথভাবে সংযুক্ত করো
2. LED (onboard/external) ও resistor সংযুক্ত করো
3. pinMode দিয়ে PIR ও LED-এর pin সেট করো
4. loop-এ digitalRead() দিয়ে motion ডিটেক্ট করো
5. motion থাকলে LED জ্বালাও, না থাকলে নিভিয়ে দাও
6. Serial Monitor-এ স্টেটাস দেখাও
7. delay() দিয়ে প্রতি ০.৫ সেকেন্ডে আপডেট করো

✅ এই প্রজেক্টে যা শিখবে
==========================
- PIR sensor দিয়ে motion detect করা
- digitalRead() ও digitalWrite() ব্যবহার
- Serial Monitor-এ স্টেটাস দেখা
- LED কন্ট্রোল

🚦 এখন নিজে চেষ্টা করো!
==========================
- সার্কিট বানাও
- কোড আপলোড করো
- দেখো কিভাবে মুভমেন্ট হলে LED জ্বলে!

