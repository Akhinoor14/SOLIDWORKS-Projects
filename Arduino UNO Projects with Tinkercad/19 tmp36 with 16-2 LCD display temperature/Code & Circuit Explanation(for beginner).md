
# 🌡️ Code & Circuit Explanation (for beginner) – Project 19: Temperature Sensor + LCD

এই প্রজেক্টে TMP36 সেন্সর দিয়ে প্রকৃত তাপমাত্রা (°C) মাপা হয় এবং 16×2 LCD ডিসপ্লেতে তা দেখানো হয়। TMP36 একটি analog voltage output দেয়, আর Arduino UNO সেটাকে voltage থেকে temperature-এ রূপান্তর করে live display করে।  

---

## 1. 🎒 যা লাগবে (Required Components)

| Component           | Quantity | Description                              |
|----------------------|----------|------------------------------------------|
| Arduino UNO          | 1        | Microcontroller board                    |
| TMP36 Temp Sensor    | 1        | Analog temperature sensor                |
| LCD 16×2 (parallel)  | 1        | Text output display                      |
| 10kΩ Potentiometer   | 1        | LCD contrast control                     |
| 220Ω Resistor (Optional) | 1    | LCD backlight current limiting           |
| Breadboard + Wires   | as needed| Circuit connections                      |
| Power Supply (USB/5V)| 1        | Arduino power                            |

---

## 2. 🔌 Circuit Connections (Detailed & Easy)

### 🟢 TMP36 to Arduino (Temperature Sensor)

| TMP36 Pin | Connected To | Description                        |
|------------|--------------|------------------------------------|
| Left pin   | +5V          | Power supply                      |
| Middle pin | A0           | Analog output → reads voltage     |
| Right pin  | GND          | Common ground                     |

🧠 TMP36 output voltage = 0.5V at 0°C  
⮕ প্রতি 10mV = 1°C → Formula used: `(voltage - 0.5) × 100`

---

### 📺 LCD 16×2 to Arduino UNO (4-Bit Mode)

| LCD Pin | Arduino Pin | Description               |
|----------|-------------|---------------------------|
| 1 (VSS)  | GND         | Ground                    |
| 2 (VDD)  | +5V         | Power supply              |
| 3 (VO)   | Middle of Pot | Contrast control         |
| 4 (RS)   | D7          | Register Select           |
| 5 (RW)   | GND         | Write mode                |
| 6 (EN)   | D8          | Enable signal             |
| 11 (D4)  | D9          | Data line 4               |
| 12 (D5)  | D10         | Data line 5               |
| 13 (D6)  | D11         | Data line 6               |
| 14 (D7)  | D12         | Data line 7               |
| 15 (A/LED+) | 5V via 220Ω | Backlight (Optional)    |
| 16 (K/LED–)| GND       | Backlight ground          |

🔄 Potentiometer 3 pin → [Left → GND, Middle → LCD VO, Right → +5V]  
📌 LCD operates in 4-bit mode (saves Arduino pins)

---

## 3. 🧠 Reason Behind the Connections & How It Works

- **TMP36** continuously gives analog voltage based on temperature  
- **Arduino reads analog input** (0–1023) and converts it into voltage  
- Formula:  
  - `voltage = (analogValue × 5.0) / 1023.0`  
  - `tempC = (voltage - 0.5) × 100`  
- **LCD 16×2** is initialized using 4-bit communication to reduce pin use  
- LCD shows “Temp: XX.XX C” and updates every second  
- Potentiometer adjusts **contrast** — যতোই value adjust করো, ততটা contrast বাড়বে / কমবে

---

## 4. 📝 ধাপে ধাপে কী হচ্ছে

1. Arduino চালু হলে LCD তে “Temp Sensor Ready” লেখা আসে  
2. TMP36 থেকে analog voltage পড়া হয়  
3. Analog value → voltage → temperature (°C) তে রূপান্তর হয়  
4. LCD display তে live তাপমাত্রা দেখা যায়  
5. প্রতি 1 সেকেন্ড পর display update হয়

---

# 📗 Code Breakdown – Project 19: Display Temperature with TMP36 & LCD

---

## 📌 Library

- `#include <LiquidCrystal.h>`  
  ➤ 16×2 LCD ব্যবহারের জন্য Arduino এর ইনবিল্ট লাইব্রেরি

## 🔌 LCD Initialization

- `LiquidCrystal lcd(7,8,9,10,11,12);`  
  ➤ RS → 7, EN → 8, D4–D7 → 9–12 পিনের সাথে LCD যুক্ত

## 🌡️ TMP36 Temperature Sensor

- `const int tempPin = A0;`  
  ➤ TMP36 সেন্সরের analog output A0 পিনে নেয়া হয়েছে

---

## ⚙️ setup()

- `lcd.begin(16, 2);` → LCD initialize (16 columns × 2 rows)  
- প্রথমে display করে: “Temp Sensor Ready” → ২ সেকেন্ড পর clear হয়

---

## 🔁 loop()

- `analogRead(tempPin)` → TMP36 সেন্সরের raw voltage পড়া হয়  
- `voltage = analogValue * (5.0 / 1023.0)`  
  ➤ Analog value কে ভোল্টেজে রূপান্তর (Arduino 10-bit ADC)

- `tempC = (voltage - 0.5) * 100.0`  
  ➤ TMP36 থেকে °C ক্যালকুলেট করা হয়  
  ➤ 0.5V মানে 0°C, প্রতি 10mV মানে 1°C rise

---

## 🖥️ LCD Display

- প্রথম লাইন: "Now Temp:"
- দ্বিতীয় লাইন: "[value] C"
- এখানে ,  
- `lcd.setCursor(a,b)` → temperature value `a+1` column থেকে print হওয়া শুরু হয় `b+1` নং লাইনে. 
#### Example
   1. `lcd.setCursor(3,0)` → temperature value LCD তে `4` column থেকে print হওয়া শুরু হয় `1` নং লাইনে। 
2. `lcd.setCursor(0,1)` → temperature value LCD তে `1` column থেকে print হওয়া শুরু হয় `2` নং লাইনে। 
```
-  `delay(1000);` → প্রতি সেকেন্ডে display update হয়
```
---

## 🎯 Highlights

- TMP36 analog sensor → accurate temp read  
- Simple conversion: voltage to °C  
- 16×2 LCD তে live temperature দেখানো হয়  
- Clean display update (no flicker)


## 5. ✨ এই প্রজেক্টে কী হবে?

- Analog temperature sensing শিখবে  
- LCD display ব্যবহারে অভ্যস্ত হবে  
- voltage → temperature conversion logic বোঝা যাবে  
- 4-bit LCD interfacing + contrast control + display formatting শেখা যাবে  
- Embedded real-time sensor reading project complete হবে

---

## 6. 🚦 এখন নিজে চেষ্টা করো!

1. TMP36 ঠিকভাবে A0, GND, 5V এ connect করো  
2. Potentiometer → LCD contrast ঠিক মতো set করো  
3. LCD 4-bit mode অনুযায়ী পিনগুলো connect করো  
4. Code upload করো এবং সিরিয়াল মনিটরের মতো LCD display observe করো  
5. হাত দিয়ে TMP36 স্পর্শ করো — temp rise হচ্ছে কিনা দেখো 🔥  
6. Thermometer দিয়ে cross-check করে accuracy test করো

🧪 Bonus: ADC bits ও resolution নিয়ে experiment করো!  
🌡️ Temperature range: –40°C to +125°C supported by TMP36  

```
