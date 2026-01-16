# 🔌 Circuit Connections

| LCD Pin | Function      | ATtiny85 Pin         | Battery/Power Connection         |
|---------|---------------|----------------------|----------------------------------|
| 1       | GND           | GND                  | Battery (–), Step-Up GND         |
| 2       | VCC           | VCC                  | Step-Up Converter Output (5V) (+)|
| 3       | V0            | GND                  | Battery (–), Step-Up GND         |
| 4       | RS            | PB0                  | —                                |
| 5       | RW            | GND                  | Battery (–), Step-Up GND         |
| 6       | E             | PB1                  | —                                |
| 11      | D4            | PB2                  | —                                |
| 12      | D5            | PB3                  | —                                |
| 13      | D6            | PB4                  | —                                |
| 14      | D7            | PB5                  | —                                |
| 15      | LED Anode     | —                    | Step-Up Converter Output (5V) (+) via 220Ω resistor |
| 16      | LED Cathode   | —                    | Battery (–), Step-Up GND         |

📌 **Note:**  
- DIP switch is placed between battery (+) and step-up input for power control.
- Use a **step-up converter (MT3608)** to boost 1.5V from the battery to 5V for the ATtiny85 and LCD.  
- You can use an **LCD I2C backpack** to save pins (uses only two pins, e.g. A4/A5, if using software I2C).

📌 RW → GND করে দিলে কোডে `.begin()` ব্যাসেই LCD ready  
📌 Contrast ঠিক রাখতে VO (Pin 3) → সরাসরি GND দিলে কালো লেখা দেখা যাবে  
📌 LCD তে D7 ব্যবহার করিনি, কারণ আমরা 4-bit mode ব্যবহার করছি  
📌 Power Control: DIP switch → Battery থেকে Step-Up Converter-এ

---

# 🧠 Code Explanation (Line by Line)

- `#include <LiquidCrystal.h>`  
  ➤ LCD লাইব্রেরি ইমপোর্ট করে যেটা Arduino-তে চার পিনে ডাটা পাঠায়  

- `LiquidCrystal lcd(rs, en, d4, d5, d6);`  
  ➤ LCD এর RS, EN ও D4-D6 পিন declare করা হয়েছে  

- `lcd.begin(16, 2);`  
  ➤ LCD initialize করা হয়েছে 16 column, 2 row মোডে  

- `lcd.setCursor(0, 0); lcd.print("this is Akhinoor");`  
  ➤ প্রথম লাইনের শুরুর দিক থেকে নাম প্রিন্ট করে  

- `lcd.setCursor(0, 1); lcd.print("welcome    ");`  
  ➤ দ্বিতীয় লাইনের শুরুতে `welcome` শব্দ এবং শেষে সময়ের জন্য ফাঁকা রাখা  

- `millis()`  
  ➤ বিল্ট-ইন Arduino ফাংশন যা চালু হওয়ার পর কত ms পেরিয়েছে তা বলে  

- `if (currentMillis - previousMillis >= 1000)`  
  ➤ প্রতি ১ সেকেন্ড পর সময় আপডেট করে  

- `lcd.setCursor(11, 1); lcd.print(mm:ss);`  
  ➤ সময় কে সুন্দরভাবে ফরম্যাট করে দ্বিতীয় লাইনের শেষে দেখায়  

---

# ✨ এই প্রজেক্টে কী হবে?

- ATtiny85 + LCD দিয়ে তোমার নিজের নাম দেখাবে  
- দ্বিতীয় লাইনে welcome + live clock চলবে mm:ss ফরম্যাটে  
- DIP switch দিয়ে 1.5V ব্যাটারি থেকে power control করা যাবে  

---

# ✅ এই প্রজেক্টে যা শিখবে

- 16×2 LCD কে 4-bit মোডে drive করা  
- millis() দিয়ে সরল সফটওয়্যার timer তৈরি  
- pin mapping ও DIP-based power control  
- power-efficient ATtiny circuit designing

---

# 🚦 এখন নিজে চেষ্টা করো!

1. Circuit তৈরি করো Tinkercad বা real breadboard-এ  
2. ATtiny85 pin mapping দেখে wiring করো  
3. কোড আপলোড করো → LCD-তে বার্তা ও সময় দেখো  
4. Clock সেকেন্ডে সেকেন্ডে আপডেট হয় কিনা দেখো  
5. DIP switch দিয়ে power toggle করো  