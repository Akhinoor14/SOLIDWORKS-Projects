# 📟 ডিজিটাল পটেনশিওমিটার - ভোল্টেজ ডিভাইডার প্রজেক্ট

## 🌟 প্রজেক্ট পরিচিতি

এই প্রজেক্টে আমরা **Voltage Divider (ভোল্টেজ বিভাজক)** সার্কিট তৈরি করব যেটি Arduino দিয়ে ভোল্টেজ মাপার কাজ করবে। ১ MΩ এবং ১০ kΩ রেজিস্ট্যান্স ব্যবহার করে আমরা একটি voltage divider নেটওয়ার্ক তৈরি করব, Arduino এর ADC দিয়ে ভোল্টেজ পড়ব এবং formula ব্যবহার করে আসল input voltage বের করব।

### 📚 এই প্রজেক্ট থেকে শিখব:

```
✅ Voltage Divider কী এবং কীভাবে কাজ করে
✅ দুইটি রেজিস্ট্যান্স series-এ কানেক্ট করলে ভোল্টেজ কীভাবে ভাগ হয়
✅ Arduino ADC (Analog to Digital Converter) কীভাবে কাজ করে
✅ 0-1023 ADC ভ্যালু থেকে 0-5V voltage-এ convert করা
✅ Voltage divider formula ব্যবহার করে input voltage বের করা
✅ 16×2 LCD ডিসপ্লেতে real-time ভোল্টেজ দেখানো
✅ Floating-point arithmetic (দশমিক সংখ্যা গণনা)
✅ Resistor ratio এবং scaling factor বুঝা
```

---

## 🛠️ প্রয়োজনীয় যন্ত্রপাতি

| যন্ত্র | সংখ্যা | বিস্তারিত | কাজ |
|-------|--------|----------|------|
| Arduino UNO | ১টি | ATmega328P, 5V লজিক | মাইক্রোকন্ট্রোলার |
| 16×2 LCD Display | ১টি | HD44780, 4-bit mode | ভোল্টেজ প্রদর্শন |
| 1MΩ রেজিস্ট্যান্স | ১টি | Brown-Black-Green (±5%) | Upper resistor (R1) |
| 10kΩ রেজিস্ট্যান্স | ১টি | Brown-Black-Orange (±5%) | Lower resistor (R2) |
| 10kΩ Potentiometer | ১টি | LCD contrast adjust | কন্ট্রাস্ট নিয়ন্ত্রণ |
| 220Ω রেজিস্ট্যান্স | ১টি (optional) | LCD backlight | LED current limiting |
| Breadboard | ১টি | 830 tie-points | সার্কিট তৈরি |
| Jumper Wires | ~২০টি | Male-to-Male | সংযোগ |
| USB Cable | ১টি | Type A to Type B | Programming |

### 💰 আনুমানিক খরচ: ৳৩০০-৫০০ টাকা

---

## ⚡ Voltage Divider (ভোল্টেজ বিভাজক) কী?

### মূল ধারণা:

**Voltage Divider** হল একটি সার্কিট যেখানে দুইটি resistor series-এ (একের পর এক) connect করা থাকে। এই সার্কিট একটি বড় voltage কে ছোট voltage-এ convert করতে পারে।

### কীভাবে কাজ করে:

```
সহজ ব্যাখ্যা:
ধরি একটি পাইপে পানি প্রবাহিত হচ্ছে। পথে দুটি ভালভ আছে।
প্রথম ভালভ বড় (R1 = 1MΩ), অনেক বেশি বাধা দেয়।
দ্বিতীয় ভালভ ছোট (R2 = 10kΩ), কম বাধা দেয়।

জলচাপ (voltage) প্রথম ভালভে বেশি কমে, দ্বিতীয়টায় কম কমে।
দুই ভালভের মাঝখানের জলচাপ (Node A) Arduino পড়ে।
```

### Voltage Divider সার্কিট:

```
Voltage Divider Diagram:
         +5V (Arduino থেকে)
          │
          ├──── Input Voltage (Vin)
          │
         ╱╲
        │  │  R1 = 1MΩ (১০ লক্ষ ওহম)
        │  │  [Upper Resistor]
         ╲╱
          │
          ├──── Node A (Vout) → Arduino A0-তে যায়
          │
         ╱╲
        │  │  R2 = 10kΩ (১০ হাজার ওহম)
        │  │  [Lower Resistor]
         ╲╱
          │
         GND
         
ব্যাখ্যা:
• Vin = Input voltage (যা আমরা মাপতে চাই)
• Vout = Output voltage (Node A-তে, Arduino পড়ে)
• R1 = Upper resistor (উপরের প্রতিরোধ)
• R2 = Lower resistor (নিচের প্রতিরোধ)
```

---

## 📐 Voltage Divider সূত্র (Formula)

### Output Voltage বের করার সূত্র:

```
Vout = Vin × (R2 / (R1 + R2))

যেখানে:
  Vout = Output voltage (যা Arduino পড়ে)
  Vin  = Input voltage (যা আমরা জানতে চাই)
  R1   = Upper resistor (1MΩ)
  R2   = Lower resistor (10kΩ)
```

### Input Voltage বের করার সূত্র (Reverse):

```
Vin = Vout × ((R1 + R2) / R2)

এটি উল্টো হিসাব:
  Arduino Vout পড়ে → Formula দিয়ে Vin বের করে
```

---

## 🧮 গাণিতিক উদাহরণ

### আমাদের প্রজেক্টে:

**দেওয়া আছে:**
- Vin = 5V (Arduino এর supply voltage)
- R1 = 1,000,000 Ω (১০ লক্ষ ওহম = ১ MΩ)
- R2 = 10,000 Ω (১০ হাজার ওহম = ১০ kΩ)

### ধাপ ১: Output Voltage (Vout) বের করি

```
Formula: Vout = Vin × (R2 / (R1 + R2))

হিসাব:
Vout = 5V × (10,000 / (1,000,000 + 10,000))
     = 5V × (10,000 / 1,010,000)
     = 5V × 0.00990099
     = 0.0495V
     ≈ 49.5 mV (মিলিভোল্ট)

ব্যাখ্যা: 5V input voltage-এ Node A-তে প্রায় 0.05V আসবে।
```

### ধাপ ২: Arduino ADC Reading

```
Arduino ADC (Analog to Digital Converter):
  • Range: 0-1023 (10-bit resolution)
  • 0 = 0V, 1023 = 5V
  • প্রতি step = 5V / 1023 = 4.89 mV

Vout = 0.0495V থেকে ADC value:
ADC = (Vout / 5V) × 1023
    = (0.0495 / 5.0) × 1023
    = 0.0099 × 1023
    = 10.13
    ≈ 10

Arduino পড়বে: সেন্সর ভ্যালু = 10
```

### ধাপ ৩: ADC থেকে Voltage-এ Convert

```
Code-এ যেভাবে হিসাব হয়:
vout = (sensorValue × 5.0) / 1023.0
     = (10 × 5.0) / 1023.0
     = 50.0 / 1023.0
     = 0.0489V

প্রায় 0.05V পড়ছে (যা আশা করেছিলাম)
```

### ধাপ ৪: Input Voltage (Vin) বের করি

```
Formula: Vin = Vout × ((R1 + R2) / R2)

হিসাব:
Vin = 0.0489V × ((1,000,000 + 10,000) / 10,000)
    = 0.0489V × (1,010,000 / 10,000)
    = 0.0489V × 101
    = 4.94V

আসল voltage ছিল 5V, Arduino calculate করেছে 4.94V
Error = (5.00 - 4.94) / 5.00 × 100% = 1.2%
```

---

## 🔢 Divider Ratio (বিভাজন অনুপাত)

### Scaling Factor:

```
Divider Ratio = (R1 + R2) / R2
              = (1,000,000 + 10,000) / 10,000
              = 1,010,000 / 10,000
              = 101

এর মানে:
  ✅ Output voltage, input voltage-এর ১০১ গুণ ছোট
  ✅ Input বের করতে: Output × 101
  ✅ এই ratio দিয়ে theoretically 505V পর্যন্ত মাপা যায়
     (কিন্তু Arduino শুধু 5V পর্যন্ত নিরাপদ!)

উদাহরণ:
  Vin = 5V    → Vout = 5/101 = 0.0495V
  Vin = 10V   → Vout = 10/101 = 0.099V
  Vin = 50V   → Vout = 50/101 = 0.495V
  Vin = 505V  → Vout = 505/101 = 5.00V (Arduino limit)
```

---

## 🔌 সার্কিট সংযোগ (Circuit Connections)

### Voltage Divider Network:

| যন্ত্র | Terminal | Arduino Pin | তারের রং | কাজ |
|-------|----------|-------------|----------|------|
| 1MΩ (R1) | Leg 1 | 5V | লাল | Input voltage |
| 1MΩ (R1) | Leg 2 | Node A → A0 | হলুদ | Divider output |
| 10kΩ (R2) | Leg 1 | Node A (R1-এর সাথে) | - | Junction point |
| 10kΩ (R2) | Leg 2 | GND | কালো | Ground |

### 16×2 LCD Display (4-bit mode):

| LCD Pin | Pin # | Arduino Pin | কাজ |
|---------|-------|-------------|------|
| VSS | 1 | GND | Ground |
| VDD | 2 | 5V | Power |
| VO | 3 | Pot মাঝখান | Contrast |
| RS | 4 | D12 | Register Select |
| RW | 5 | GND | Read/Write |
| EN | 6 | D11 | Enable |
| D4 | 11 | D5 | Data bit 4 |
| D5 | 12 | D4 | Data bit 5 |
| D6 | 13 | D3 | Data bit 6 |
| D7 | 14 | D2 | Data bit 7 |
| LED+ | 15 | 5V (220Ω দিয়ে) | Backlight + |
| LED- | 16 | GND | Backlight - |

### সংযোগ ডায়াগ্রাম:

```
Arduino UNO                    Voltage Divider
┌─────────────────┐           ┌──────────────────┐
│                 │   +5V     │                  │
│   5V  ●─────────┼───────────┤●─────┐           │
│                 │           │      │           │
│                 │           │     [1MΩ]        │
│                 │           │      │           │
│                 │  Node A   │      │           │
│   A0  ●─────────┼───────────┤──────┴───────┐   │
│                 │           │              │   │
│                 │           │            [10kΩ]│
│                 │           │              │   │
│  GND  ●─────────┼───────────┤──────────────┴───┤
│                 │           └──────────────────┘
│                 │
│  D12  ●─────────┼─────────── LCD RS (4)
│  D11  ●─────────┼─────────── LCD EN (6)
│   D5  ●─────────┼─────────── LCD D4 (11)
│   D4  ●─────────┼─────────── LCD D5 (12)
│   D3  ●─────────┼─────────── LCD D6 (13)
│   D2  ●─────────┼─────────── LCD D7 (14)
│                 │
│   5V  ●─────────┼─────────── LCD VDD (2)
│  GND  ●─────────┼─────────── LCD VSS (1)
│  GND  ●─────────┼─────────── LCD RW (5)
└─────────────────┘
```

---

## 💻 কোড ব্যাখ্যা

### সম্পূর্ণ Code:

```cpp
#include <LiquidCrystal.h>

// LCD initialization (RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Voltage divider resistor values
const float R1 = 1000000.0;  // 1 MΩ
const float R2 = 10000.0;    // 10 kΩ

// Analog input pin
const int analogPin = A0;

// Variables
float inputVoltage = 0.0;
float vout = 0.0;

void setup() {
  Serial.begin(9600);
  Serial.println("Digital Potentiometer - Voltage Divider");
  
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Digital Voltage");
  
  delay(1000);
}

void loop() {
  // Read analog value (0-1023)
  int sensorValue = analogRead(analogPin);
  
  // Convert to voltage (0-5V)
  vout = (sensorValue * 5.0) / 1023.0;
  
  // Calculate input voltage
  inputVoltage = vout * ((R1 + R2) / R2);
  
  // Display on LCD
  lcd.setCursor(0, 1);
  lcd.print("V: ");
  lcd.print(inputVoltage, 2);
  lcd.print(" V   ");
  
  // Serial debug
  Serial.print("ADC: ");
  Serial.print(sensorValue);
  Serial.print(" | Vout: ");
  Serial.print(vout, 4);
  Serial.print("V | Vin: ");
  Serial.print(inputVoltage, 2);
  Serial.println("V");
  
  delay(500);
}
```

---

## 📖 Code Line-by-Line ব্যাখ্যা

### ১. Library Include

```cpp
#include <LiquidCrystal.h>
```

**কাজ:**
- Arduino এর built-in LCD library include করা
- LCD control করার জন্য function পাওয়া: `begin()`, `print()`, `setCursor()`

---

### ২. LCD Object তৈরি

```cpp
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
```

**কনস্ট্রাক্টর প্যারামিটার:**
```cpp
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
                 (12, 11, 5,  4,  3,  2);
```

| প্যারামিটার | Arduino Pin | LCD Pin | কাজ |
|-------------|-------------|---------|------|
| RS | D12 | 4 | Register Select |
| EN | D11 | 6 | Enable |
| D4 | D5 | 11 | Data bit 4 |
| D5 | D4 | 12 | Data bit 5 |
| D6 | D3 | 13 | Data bit 6 |
| D7 | D2 | 14 | Data bit 7 |

---

### ৩. Resistor মান Define করা

```cpp
const float R1 = 1000000.0;  // 1 MΩ (১০ লক্ষ ওহম)
const float R2 = 10000.0;    // 10 kΩ (১০ হাজার ওহম)
```

**কেন `const float`?**
```
const = মান পরিবর্তন হবে না (safety)
float = দশমিক সংখ্যা (decimal precision)
.0   = floating-point arithmetic নিশ্চিত করা
```

**Divider Ratio:**
```
(R1 + R2) / R2 = (1,000,000 + 10,000) / 10,000 = 101
```

---

### ৪. Analog Pin Define

```cpp
const int analogPin = A0;
```

- A0 pin দিয়ে voltage divider এর output পড়া হবে
- Arduino এর 10-bit ADC (0-1023 range)

---

### ৫. Variable Declare

```cpp
float inputVoltage = 0.0;  // Calculated Vin
float vout = 0.0;          // Measured Vout at Node A
```

- `inputVoltage` = আমরা যে voltage খুঁজছি (Vin)
- `vout` = Node A-তে যে voltage Arduino পড়ে

---

### ৬. Setup Function

```cpp
void setup() {
  Serial.begin(9600);
  Serial.println("Digital Potentiometer - Voltage Divider");
  
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Digital Voltage");
  
  delay(1000);
}
```

**ধাপে ধাপে:**

**ক) Serial Communication শুরু:**
```cpp
Serial.begin(9600);
Serial.println("...");
```
- Serial Monitor খোলা (9600 baud rate)
- Debugging এর জন্য header print করা

**খ) LCD Initialize:**
```cpp
lcd.begin(16, 2);
```
- 16 column × 2 row LCD configure করা
- 4-bit communication mode activate

**গ) Title প্রদর্শন:**
```cpp
lcd.setCursor(0, 0);    // প্রথম লাইন, প্রথম কলাম
lcd.print("Digital Voltage");
```
- LCD এর প্রথম লাইনে স্থায়ী title

**ঘ) Startup Delay:**
```cpp
delay(1000);  // ১ সেকেন্ড অপেক্ষা
```

---

### ৭. Loop Function - Analog পড়া

```cpp
int sensorValue = analogRead(analogPin);
```

**`analogRead()` Function:**

| বৈশিষ্ট্য | বিস্তারিত |
|---------|----------|
| কাজ | A0 pin-এ voltage পড়া |
| Return | Integer (0-1023) |
| Range | 0 = 0V, 1023 = 5V |
| Resolution | 5V / 1023 = 4.89 mV প্রতি step |
| Conversion Time | ~100 microseconds |

**উদাহরণ:**
```
যদি Node A-তে 0.0495V থাকে:
  ADC = (0.0495 / 5.0) × 1023
      = 0.0099 × 1023
      = 10.13 ≈ 10
  
Arduino পড়বে: sensorValue = 10
```

---

### ৮. ADC থেকে Voltage Convert

```cpp
vout = (sensorValue * 5.0) / 1023.0;
```

**সূত্র ব্যাখ্যা:**

```
লক্ষ্য: ADC value (0-1023) থেকে আসল voltage (0-5V) বের করা

Formula:
  Vout = (ADC / 1023) × Vref
  যেখানে Vref = 5.0V

Simplified:
  Vout = ADC × (5.0 / 1023.0)

কেন 1023, 1024 নয়?
  • ADC range: 0 থেকে 1023 (মোট 1024 টি মান)
  • কিন্তু: 0 মানে 0V, 1023 মানে 5V
  • তাই ভাগ করতে হবে 1023 দিয়ে

উদাহরণ:
  sensorValue = 0
    vout = 0 × (5.0/1023) = 0.000V
  
  sensorValue = 10
    vout = 10 × (5.0/1023) = 0.0489V
  
  sensorValue = 1023
    vout = 1023 × (5.0/1023) = 5.000V
```

---

### ৯. Input Voltage হিসাব

```cpp
inputVoltage = vout * ((R1 + R2) / R2);
```

**Voltage Divider Formula উল্টো:**

```
Standard Divider Formula:
  Vout = Vin × (R2 / (R1 + R2))

Rearrange করে Vin বের করি:
  Vin = Vout × ((R1 + R2) / R2)

আমাদের মান বসিয়ে:
  Vin = Vout × ((1,000,000 + 10,000) / 10,000)
      = Vout × (1,010,000 / 10,000)
      = Vout × 101

উদাহরণ:
  vout = 0.0489V (Node A-তে মাপা)
  inputVoltage = 0.0489 × 101
               = 4.94V
  
আসল voltage ছিল 5V, খুব কাছাকাছি পেয়েছি! ✓
```

**কেন 101 দিয়ে গুণ?**
```
Divider voltage কে 101 ভাগ করে ছোট করেছে
আবার বড় করতে 101 দিয়ে গুণ দিতে হবে
```

---

### ১০. LCD তে Display

```cpp
lcd.setCursor(0, 1);
lcd.print("V: ");
lcd.print(inputVoltage, 2);
lcd.print(" V   ");
```

**ধাপে ধাপে:**

**ক) Cursor স্থাপন:**
```cpp
lcd.setCursor(0, 1);
```
- Column 0, Row 1 (দ্বিতীয় লাইন, বাম দিক)

**খ) Label Print:**
```cpp
lcd.print("V: ");
```
- "V: " লেখা দেখাবে

**গ) Voltage Print:**
```cpp
lcd.print(inputVoltage, 2);
```
- দ্বিতীয় parameter `2` = দুই দশমিক স্থান
- যদি `inputVoltage = 5.00` হয়, display হবে "5.00"

**ঘ) পুরাতন Text মুছে ফেলা:**
```cpp
lcd.print(" V   ");
```
- " V" unit লেখা
- Extra space গুলো আগের লম্বা text মুছে দেয়

**LCD Display Format:**
```
Row 0: |D|i|g|i|t|a|l| |V|o|l|t|a|g|e| |
       0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

Row 1: |V|:| |5|.|0|0| |V| | | | | | | |
       0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
```

---

### ১১. Serial Monitor Debug

```cpp
Serial.print("ADC: ");
Serial.print(sensorValue);
Serial.print(" | Vout: ");
Serial.print(vout, 4);
Serial.print("V | Vin: ");
Serial.print(inputVoltage, 2);
Serial.println("V");
```

**Serial Output উদাহরণ:**
```
Digital Potentiometer - Voltage Divider
========================================
ADC: 10 | Vout: 0.0489V | Vin: 4.94V
ADC: 10 | Vout: 0.0489V | Vin: 4.94V
ADC: 11 | Vout: 0.0538V | Vin: 5.43V
```

**Debug তথ্য:**
- `ADC` = Raw sensor reading (0-1023)
- `Vout` = Node A voltage (৪ দশমিক)
- `Vin` = Calculated input voltage (২ দশমিক)

---

### ১২. Loop Delay

```cpp
delay(500);
```

- ৫০০ মিলিসেকেন্ড (০.৫ সেকেন্ড) অপেক্ষা
- সেকেন্ডে দুইবার update হবে
- LCD flicker রোধ করে
- Serial Monitor spam কমায়

---

## 🔄 কীভাবে কাজ করে (System Workflow)

### সম্পূর্ণ প্রক্রিয়া:

```
┌─────────────────────────────────────────┐
│  POWER ON (Arduino চালু)                │
└──────────────┬──────────────────────────┘
               ↓
┌─────────────────────────────────────────┐
│  INITIALIZATION (শুরুতে একবার)         │
│  • Serial 9600 baud-এ শুরু             │
│  • LCD 16×2 initialize                  │
│  • "Digital Voltage" title দেখান      │
│  • R1=1MΩ, R2=10kΩ মান set             │
└──────────────┬──────────────────────────┘
               ↓
┌─────────────────────────────────────────┐
│  MAIN LOOP (বারবার চলতে থাকে)         │
└──────────────┬──────────────────────────┘
               ↓
       ┌───────┴───────┐
       │               │
       ↓               ↓
┌──────────────┐ ┌─────────────┐
│ পদক্ষেপ ১:   │ │ পদক্ষেপ ২:  │
│ A0 পড়া      │ │ হিসাব করা   │
│ (0-1023)     │ │ • ADC→Vout  │
│              │ │ • Vout×101  │
└──────┬───────┘ └──────┬──────┘
       │                │
       └────────┬───────┘
                ↓
      ┌───────────────────┐
      │ পদক্ষেপ ৩:        │
      │ ফলাফল দেখান      │
      │ • LCD: "V: X.XXV" │
      │ • Serial: Debug   │
      └─────────┬─────────┘
                ↓
          ৫০০ms অপেক্ষা
                ↓
          আবার Loop শুরু
```

---

### Physical Process (ভৌত প্রক্রিয়া):

```
Input Voltage (5V)
        ↓
   R1 (1MΩ) - বেশি voltage drop হয়
        ↓
    Node A - Arduino A0 পড়ে
        ↓
   R2 (10kΩ) - কম voltage drop
        ↓
      GND (0V)

Electrical Flow:
  1. Arduino 5V supply → R1 দিয়ে current প্রবাহ
  2. R1-এ বেশি voltage drop (প্রায় 4.95V)
  3. Node A-তে কম voltage (0.05V)
  4. R2-এ সামান্য drop (0.05V)
  5. Current খুব কম: I = 5V / 1.01MΩ ≈ 5µA

Arduino Processing:
  1. A0 pin-এ voltage sense করে
  2. ADC convert করে digital value-তে (0-1023)
  3. Formula দিয়ে voltage-এ convert করে
  4. Divider formula দিয়ে input calculate করে
  5. LCD ও Serial-এ display করে
```

---

## 🎯 ব্যবহারিক প্রয়োগ (Real-World Applications)

### কোথায় ব্যবহার হয়:

| প্রয়োগ | বর্ণনা | ক্ষেত্র |
|--------|-------|---------|
| **ব্যাটারি মনিটরিং** | 12V ব্যাটারির voltage মাপা | Automotive, solar |
| **Sensor Conditioning** | Sensor signal Arduino range-এ আনা | Industrial |
| **Multimeter** | High voltage নিরাপদে মাপা | Instrumentation |
| **Power Supply** | Voltage regulation ও sensing | Electronics |
| **Solar Systems** | Solar panel voltage monitor | Renewable energy |
| **Motor Controllers** | Voltage feedback | Robotics |

---

### উদাহরণ: 12V ব্যাটারি মনিটর

```
12V Lead-Acid Battery
        │
        ├───[220kΩ]─── R1
        │
    Node A ───────────→ Arduino A0
        │
        ├───[100kΩ]─── R2
        │
       GND

Divider Ratio = (220k + 100k) / 100k = 3.2

12V battery:
  Vout at Node A = 12V / 3.2 = 3.75V (Arduino safe!)
  Arduino reads: 3.75V
  Calculates: 3.75V × 3.2 = 12V ✓

যদি ব্যাটারি 10.5V-এ নামে (low):
  Vout = 10.5 / 3.2 = 3.28V
  Arduino পড়বে: 3.28V
  Calculate: 3.28 × 3.2 = 10.5V
  LCD দেখাবে: "Low Battery!" warning
```

---

## 🔧 Troubleshooting (সমস্যা সমাধান)

### সাধারণ সমস্যা:

| সমস্যা | কারণ | সমাধান |
|--------|------|--------|
| **LCD খালি** | Power নেই | VDD (pin 2) 5V-এ আছে কিনা check করুন |
| | Contrast adjust হয়নি | Potentiometer ঘুরান |
| **LCD-তে বক্স দেখা যাচ্ছে** | Contrast বেশি | Pot আস্তে আস্তে adjust করুন |
| | Pin সংযোগ ভুল | D2-D5, D11-D12 verify করুন |
| **Voltage সবসময় 0V** | Node A disconnect | A0 সংযোগ check করুন |
| | Resistor খারাপ | Multimeter দিয়ে test করুন |
| **Voltage সবসময় 5V** | Short circuit | Resistor connection দেখুন |
| | A0 floating | A0 wire properly লাগানো আছে কিনা |
| **অস্থির voltage** | Connection loose | সব wire ভালো করে লাগান |
| | Noise/interference | Wire ছোট রাখুন |
| **ভুল voltage reading** | Resistor ভুল | R1=1MΩ, R2=10kΩ verify করুন |
| | Code formula ভুল | 101 দিয়ে multiply হচ্ছে কিনা |
| **LCD text garbled** | Pin ভুল | D2-D5 to LCD D7-D4 check |
| **Serial Monitor খালি** | খোলা হয়নি | Tools → Serial Monitor |
| | Baud rate ভুল | 9600 set করুন |

---

### Debug Tips:

#### ADC Reading Test:
```cpp
void loop() {
  int adc = analogRead(analogPin);
  Serial.print("Raw ADC: ");
  Serial.println(adc);
  delay(500);
}
// Expected: ~10 যদি 5V input হয়
// যদি 0: A0 সংযোগ ভুল
// যদি 1023: possible short to 5V
```

#### Voltage Conversion Test:
```cpp
void loop() {
  int adc = analogRead(analogPin);
  float v = (adc * 5.0) / 1023.0;
  Serial.print("ADC: ");
  Serial.print(adc);
  Serial.print(" → Voltage: ");
  Serial.print(v, 4);
  Serial.println("V");
  delay(500);
}
// Expected: ~0.0489V যদি 5V input
```

---

## 📊 Accuracy Analysis (নির্ভুলতা বিশ্লেষণ)

### Error Sources (ভুলের উৎস):

```
১. ADC Quantization Error:
   • 10-bit ADC: 5V / 1023 = 4.89 mV resolution
   • ±1 ADC step error সম্ভব
   • ±4.89 mV = ±0.5V after ×101 scaling
   
২. Resistor Tolerance:
   • ±5% tolerance (standard resistors)
   • R1 = 1MΩ ±5% → 950kΩ থেকে 1.05MΩ
   • R2 = 10kΩ ±5% → 9.5kΩ থেকে 10.5kΩ
   • Divider ratio: 96 থেকে 106 (instead of 101)
   
৩. Arduino Voltage Reference:
   • Vref nominally 5V কিন্তু ±5% variation সম্ভব
   • 4.75V থেকে 5.25V হতে পারে
   
৪. Floating-Point Rounding:
   • Computer arithmetic rounding errors
   • Usually negligible (<0.01%)

Expected Total Error: ±5-10%
```

### Accuracy উন্নতির উপায়:

```
১. Precision Resistors ব্যবহার (±1% tolerance)
২. Multimeter দিয়ে actual resistor values মাপুন
৩. Code-এ actual measured values ব্যবহার করুন
৪. External voltage reference ব্যবহার (precise 5V)
৫. Multiple readings average করুন
৬. Calibration mode implement করুন
```

---

## 🎓 শিক্ষণীয় বিষয়

### এই প্রজেক্ট থেকে আমরা শিখেছি:

```
✅ Voltage Divider কীভাবে কাজ করে
   → Series resistors voltage ভাগ করে নেয়
   → Ratio দিয়ে output voltage নির্ধারণ হয়

✅ ADC (Analog to Digital Converter)
   → Analog voltage কে digital number-এ convert করে
   → Arduino: 10-bit, 0-1023 range

✅ Mathematical Formula Implementation
   → Electronics formula কে code-এ লেখা
   → Vout = Vin × (R2/(R1+R2))
   → Vin = Vout × ((R1+R2)/R2)

✅ Scaling Factor
   → 101:1 ratio মানে 101 গুণ ছোট/বড়
   → High voltage নিরাপদে মাপার উপায়

✅ Real-time Display
   → LCD-তে live data দেখানো
   → User interface তৈরি করা

✅ Floating-Point Arithmetic
   → দশমিক সংখ্যা গণনা
   → Precision এবং accuracy
```

---

## 🚀 উন্নতির সুযোগ

### Beginner Level:

#### ১. LED Voltage Indicator যোগ করুন
```cpp
#define LED_LOW A1
#define LED_MED A2
#define LED_HIGH A3

if (inputVoltage < 3.0) {
  digitalWrite(LED_LOW, HIGH);
} else if (inputVoltage < 4.0) {
  digitalWrite(LED_MED, HIGH);
} else {
  digitalWrite(LED_HIGH, HIGH);
}
```

#### ২. Min/Max Voltage Tracking
```cpp
float minVoltage = 100.0;
float maxVoltage = 0.0;

void loop() {
  // ... voltage calculation ...
  
  if (inputVoltage < minVoltage) minVoltage = inputVoltage;
  if (inputVoltage > maxVoltage) maxVoltage = inputVoltage;
  
  lcd.print("L:");
  lcd.print(minVoltage, 1);
  lcd.print(" H:");
  lcd.print(maxVoltage, 1);
}
```

#### ৩. Voltage Alarm
```cpp
#define BUZZER 8
#define THRESHOLD 3.5

if (inputVoltage < THRESHOLD) {
  tone(BUZZER, 1000, 200);  // Warning beep
}
```

---

### Intermediate Level:

#### ৪. Multi-Range Voltmeter (৫V/১২V/২৪V)
```cpp
int range = RANGE_5V;
float dividerRatio;

switch(range) {
  case RANGE_5V:  dividerRatio = 1.0; break;
  case RANGE_12V: dividerRatio = 3.2; break;
  case RANGE_24V: dividerRatio = 6.0; break;
}
```

#### ৫. Averaging Filter (Noise কমানো)
```cpp
const int numReadings = 10;
int readings[numReadings];
int total = 0;

// Average 10 readings
for (int i = 0; i < numReadings; i++) {
  total += analogRead(analogPin);
}
int average = total / numReadings;
```

---

## 🔬 Resistor Color Code (রং কোড)

### 1MΩ Resistor:
```
┌──[Brown][Black][Green][Gold]──┐
│    1      0      ×100k  ±5%   │
│  = 1 × 10 × 100,000            │
│  = 1,000,000 Ω                 │
│  = 1 MΩ                        │
└───────────────────────────────┘
```

### 10kΩ Resistor:
```
┌──[Brown][Black][Orange][Gold]──┐
│    1      0      ×1000   ±5%   │
│  = 1 × 10 × 1,000              │
│  = 10,000 Ω                    │
│  = 10 kΩ                       │
└────────────────────────────────┘
```

---

## ✅ প্রজেক্ট Checklist

- [ ] সব যন্ত্রপাতি সংগ্রহ করা হয়েছে
- [ ] Resistor verify করা (1MΩ এবং 10kΩ)
- [ ] Voltage divider সঠিকভাবে তৈরি
- [ ] Node A সঠিক জায়গায় A0-তে connected
- [ ] LCD 4-bit mode-এ wired করা
- [ ] LCD contrast adjust করা
- [ ] Code upload সফল
- [ ] Serial Monitor 9600 baud-এ খোলা
- [ ] LCD voltage দেখাচ্ছে (~5V)
- [ ] Serial Monitor-এ ADC, Vout, Vin দেখা যাচ্ছে
- [ ] Voltage reading stable (±0.1V)
- [ ] Formula manually verify করা

---

## 👨‍🎓 লেখক

**মোঃ আখিনূর ইসলাম**  
📚 বিভাগ: Energy Science and Engineering (ESE)  
🏫 প্রতিষ্ঠান: Khulna University of Engineering & Technology (KUET)  
🌐 GitHub: [@Akhinoor14](https://github.com/Akhinoor14)  

---

## 🎯 মূল শিক্ষা:

```
১. Voltage Divider - Fundamental circuit যা voltage scale করে
২. ADC Operation - Analog signal কে digital-এ convert
৩. Resistor Ratios - অনুপাত দিয়ে voltage নির্ধারণ
৪. Formula Implementation - Math কে code-এ রূপান্তর
৫. Real-time Monitoring - Live data display করা
৬. Precision Arithmetic - Floating-point calculations
```

**এই প্রজেক্ট শিখলে voltage measurement, multimeter principle, sensor interfacing-এর foundation পাবেন! 🚀**

---

## 📖 সংশ্লিষ্ট প্রজেক্ট:

- [Project 20: LDR Light Sensor](../20%20Light%20intensity%20Measurement%20using%20LDR%20sensor/)
- [Project 19: TMP36 Temperature + LCD](../19%20tmp36%20with%2016-2%20LCD%20display%20temperature/)
- [Project 15: 16×2 LCD Display](../15%20Interfacing%2016-2%20Lcd%20display/)

---

**শুভ প্রোগ্রামিং! 🎉**  
**Voltage divider আয়ত্ত করুন এবং electronics-এর মূল ভিত্তি শিখুন! 📟⚡**