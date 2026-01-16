# 📘 Code Breakdown — dice-7segment-shift-v1.ino

এই কোডে আমরা ATtiny85 ব্যবহার করে ৭-সেগমেন্ট ডিসপ্লেতে একরকম ডিস রোলিং সিমুলেট করছি। 74HC595 shift register-এর মাধ্যমে মাত্র ৩টি পিন ব্যবহার করে ৭টি সেগমেন্ট নিয়ন্ত্রণ করছি। নিচে প্রতিটি লাইন ও ফাংশনের ব্যাখ্যা দেওয়া হলো:

---

## 📌 Macro & Constants

- `#define segDISPLAY CATHODE`  
  ➤ Common Cathode টাইপ ডিসপ্লের জন্য লজিক ঠিক রাখতে ব্যবহৃত  
- `#define d250 delay(100);`  
  ➤ একটি shortcut macro, যাতে delay সহজে ব্যবহৃত হয়

---

## 🔌 Pin Declarations

| নাম | সংযুক্ত পিন | কাজ |
|-----|--------------|-----|
| buttonPin | PB0 (Pin 5) | বোতাম ইনপুট, চাপলে ডিস ঘোরে |
| ledPin    | PB1 (Pin 6) | Indicator LED (ঐচ্ছিক) |
| clockPin  | PB2 (Pin 7) | 74HC595 এর clock (SH_CP) |
| latchPin  | PB3 (Pin 2) | 74HC595 এর latch (ST_CP) |
| dataPin   | PB4 (Pin 3) | 74HC595 এর data line (DS) |

---

## 🔢 Segment Patterns

- `digit[]` → প্রতিটি নাম্বারের জন্য ৭-সেগমেন্ট ডিসপ্লের বাইনারি প্যাটার্ন রাখা হয়েছে  
- Index 7 → সব segment OFF  
- Index 8 → সব segment ON (welcome animation)

---

## ⚙️ setup()

- `pinMode()` দিয়ে সকল পিন set করা হয়েছে  
- LED-এর অবস্থা নির্ধারণ করা হয়েছে CC বা CA অনুযায়ী  
- তারপরে:
  - `LEDwrite(8);` → সব segment ON করে animation দেখানো হয়
  - `LEDwrite(7);` → OFF করে reset
  - `LEDwrite(0);` → ০ দিয়ে শুরু

---

## 🔁 loop()

- `digitalRead(buttonPin)` দিয়ে বোতাম চাপা হয়েছে কিনা চেক  
- যদি চাপা হয়:
  - ডিসপ্লে OFF  
  - `RND()` দিয়ে ১–৬ এর মধ্যে একটি সংখ্যা তৈরি  
  - `rollDice(2)` দিয়ে ঘূর্ণন animation  
  - শেষে random সংখ্যাটি দেখানো হয়

---

## 💡 LEDwrite(index)

- latchPin LOW করে ডেটা পাঠানো শুরু  
- `shiftOut()` দিয়ে digit array থেকে ডেটা পাঠানো হয়  
- latchPin HIGH করে display update করা হয়  
- CA হলে ~digit ব্যবহার হবে (inverted), CC হলে সরাসরি pattern যাবে

---

## 🎲 RND()

- `analogRead(A1)` → analog noise ব্যবহার করে randomness তৈরি  
- `randomSeed()` দিয়ে সেই value ইউজ করে  
- `random(1,7)` → ১ থেকে ৬ এর মধ্যে random নাম্বার ফেরত দেয়

---

## 🎞️ rollDice(times)

- loop এর মাধ্যমে ১ থেকে ৬ পর্যন্ত, আবার ৫ থেকে ২ পর্যন্ত প্যাটার্ন একটার পর একটা দেখা যায়  
- এটা করতে `LEDwrite()` এবং `d250` delay ব্যবহার করা হয়েছে  
- শেষে ১ দেখা যায় → এইভাবে একটা rolling effect তৈরি হয়
```

```

# 📘 Code Breakdown — dice-7segment-shift-v2.ino

এই কোডটি dice-7segment-shift-v1 এর মতোই ৭-সেগমেন্ট ডিসপ্লেতে র‌্যান্ডম dice সংখ্যা দেখায়। তবে এখানে RND() ফাংশনের logic ভিন্ন, এবং কিছু structure আর variable নামেও variation আছে। নিচে প্রতিটি অংশের বিস্তারিত ব্যাখ্যা দেওয়া হলো।

---

## 📌 Macro & Constants

- `#define segDISPLAY CATHODE`  
  ➤ ডিসপ্লের ধরন define করা হয় (Common Cathode হলে সরাসরি ব্যবহার হবে)  
- `#define d250 delay(100);`  
  ➤ Delay macro, একই সময় delay বারবার ইউজ করতে সহজ করে

---

## 🔌 Pin Declarations

| নাম | সংযুক্ত পিন | কাজ |
|-----|--------------|-----|
| buttonPin | PB0 (Pin 5) | বোতাম ইনপুট |
| ledPin    | PB1 (Pin 6) | Indicator LED |
| clockPin  | PB2 (Pin 7) | SH_CP (Clock) |
| latchPin  | PB3 (Pin 2) | ST_CP (Latch) |
| dataPin   | PB4 (Pin 3) | DS (Serial Data Input) |

---

## 🔢 Segment Patterns

- `digit[]` → g-f-e-d-c-b-a ফরম্যাটে বাইনারি সেগমেন্ট মান  
- Index 7 → All segments OFF  
- Index 8 → All segments ON (Animation)

---

## ⚙️ setup()

- সব pins initialize করা হয়েছে (INPUT / OUTPUT)  
- `segDISPLAY` macro অনুযায়ী LED অন করা হয়েছে  
- তারপর:
  - `LEDwrite(8);` → welcome animation  
  - `LEDwrite(7);` → clear  
  - `LEDwrite(0);` → শুরুর স্ক্রিন

---

## 🔁 loop()

- বোতাম HIGH হলে:
  1. display clear
  2. `RND()` দিয়ে র‌্যান্ডম নাম্বার তৈরি
  3. dice animation (`rollDice(2)`)
  4. আবার clear
  5. তারপর একটি একটি করে manual `if (digit == X)` condition দিয়ে number দেখানো হয়

---

## 💡 LEDwrite(data)

- latchPin LOW → shiftOut → latchPin HIGH  
- `digit[]` array থেকে binary pattern 74HC595-এ পাঠানো হয়  
- segDISPLAY macro অনুযায়ী pattern সরাসরি বা invert করে পাঠানো হয়

---

## 🎲 RND()

- এখানকার RND() function একটু complex logic use করে:  
  - seed = seed×53 + 21  
  - তারপর analogRead(PB5) ব্যবহার করে seed পরিবর্তন  
  - তারপর আবার random(50) + digit যোগ করে  
  - loop চলে যতক্ষণ না digit হয় ১–৬  
  ➤ এইভাবে random কিন্তু নিয়ন্ত্রিত একটি সংখ্যা পাওয়া যায়

---

## 🎞️ rollDice(times)

- Loop করে: 1→2→3→4→5→6 → তারপর 5→4→3→2  
- সবগুলোতে `LEDwrite()` এবং `d250` delay দেওয়া আছে  
- শেষবার `LEDwrite(1)` দিয়ে animation শেষ হয়

---

## 🔍 Extra Observation

- Code structure আরও modular করা যেতো, যেমনঃ digit==1, digit==2 এমন না করে সরাসরি `LEDwrite(digit);`  
- তবে logic flow clear এবং animation ঠিকভাবে চলে
- `const int dataPin = 0;`  
  → Data line for serial bit transfer

- `random(1, 7);`  
  → Generate random number between 1–6 for dice

- `displayDigit(roll - 1);`  
  → Calls segment pattern from digit array

- `shiftOut()`  
  → Sends 8-bit pattern to 74HC595 one bit at a time

- `digitalWrite(latchPin, HIGH);`  
  → Updates outputs on 7-segment display

- `INPUT_PULLUP`  
  → No external resistor needed; button reads LOW when pressed

- `delay(500);`  
  → Adds visual hold for display and debounce

---

```

```
# 🧠 Code & Circuit Explanation (for beginner)

প্রজেক্টঃ Dice with 7-Segment Display using ATtiny85, 74HC595, and Push Button  
ভিতরে থাকবেঃ full hardware connection, logic reasoning, ধাপে ধাপে walkthrough এবং নিজের জন্য চেষ্টা করার গাইড।

---

## 1. 🔧 **যা লাগবে (What You Need):**

| Component             | Quantity |
|------------------------|----------|
| ATtiny85 Microcontroller | 1        |
| 74HC595 Shift Register   | 1        |
| 7-Segment Display                      (**Common Cathode** type) | 1     |
| Push Button              | 1        |
| LED (Optional)           | 1        |
| 330Ω Resistor            | 1        |
| 10kΩ Resistor (Optional) | 1        |
| Breadboard + Jumper Wires | as needed |
| Power Supply (3–5V)      | 1 (battery or USB + step-up) |

---

## 2. 🔌 Circuit Connections (Easy Format)

### 🔲 **Main Component Connections — এক নজরে**

🟦 ATtiny85 → 🟥 74HC595 → 🟨 7-Segment Display  
🟩 Push Button → ATtiny85  
🔌 Power → All components

---

## 🧠 ATtiny85 to 74HC595 Shift Register

| ATtiny85 Pin | TO | 74HC595 Pin | Function      |
|--------------|------|-------------|---------------|
| PB4 (Pin 3)  | Input  | Pin 14 (DS)   | Serial Data In |
| PB2 (Pin 7)  | Shift Register clock | Pin 11 (SH_CP)| Shift Clock    |
| PB3 (Pin 2)  | Output Register Clock | Pin 12 (ST_CP)| Latch Clock    |
| GND (Pin 4)  | GND(-)        | |  Ground         |
| VCC (Pin 8)  | Power (+)       |         | Power +5V      |
---
---
### 🧠 ATtiny85 to 7-Segment Display (Common Cathode)
```
ATtiny85 Pin 
PB1 (Pin 6) →Resistor(330Ω) → Common cathode  (7-Segment Display)
```

---

---

### 🟥 74HC595 to 7-Segment Display (Common Cathode)

| 74HC595 pin| Output No. | Connects To | Segment |
|------------|----|-------------|---------|
| Q0 (Pin 15) | 1  | pin a       | A       |
| Q1 (Pin 1)  | 2  | pin b       | B       | 
| Q2 (Pin 2)  |  3 | pin c       | C       | 
| Q3 (Pin 3)  |  4 | pin d       | D       | 
| Q4 (Pin 4)  |  5 | pin e       | E       |
| Q5 (Pin 5)  |  6 | pin f       | F       | 
| Q6 (Pin 6)  | 7  | pin g       | G       | 

📌 7-Segment-এর Common Cathode (CC) পিন → Resistor(330Ω) → PB1 (Pin 6)

---


### 🟩 Push Button to ATtiny85

| Button Terminal | Connected To | Purpose             |
|------------------|--------------|----------------------|
|  2a        | PB0 (Pin 5)  | buttonPin (input)    |
| 1b       | Power          |  |
| 2b         | →10kΩ pull-down resistor | → GND |

---

### 🔌 Power Supply

| Device     | Pin    | Connected To |
|------------|-------|--------------|
| ATtiny85   | VCC (8)  | +5V          |
| ATtiny85   | GND (4)  | GND          |
| 74HC595    | VCC (16) | +5V          |
| 74HC595    | GND (8)  | GND          |
| 74HC595    |Pin 13 - Output Enable  | GND          |
| 74HC595    | Pin 10 Shift Register Clear  | +5V     |

🔋 Power Source: 3V battery with step-up converter to 5V, or USB breakout

---

## 3. 🧠 Reason Behind the Connection & How It Works

- **ATtiny85 has limited pins**, তাই আমরা 74HC595 ব্যবহার করে **serial → parallel** ডেটা পাঠিয়ে ৭টা সেগমেন্ট কন্ট্রোল করছি মাত্র ৩টা পিন দিয়ে।
- 74HC595 এর **DS, SH_CP, ST_CP** পিন একসাথে `shiftOut()` function ব্যবহার করে bitwise data পাঠানো হয়।
- 7-Segment এ ৭টি segment active হয় যখন 595 এর output HIGH হয় (কারণ CC display → active HIGH)
- Push Button GND করে দিলে PB0 → HIGH হয়, তখন `loop()` ফাংশন dice রোল করে
- analogRead(A1) → analog noise → randomSeed তৈরি করে unpredictable number (1–6)
- **Why shift register (74HC595)?**  
  ➤ ATtiny85 has limited I/O pins. The 74HC595 allows us to control 7 segments with just 3 wires using serial-to-parallel output.

- **Why push button on PB3 (with pull-up)?**  
  ➤ Saves one resistor and simplifies code. The button connects to GND and triggers when pressed.

- **Why random(1, 7)?**  
  ➤ To simulate a six-sided dice roll. Subtracting 1 aligns array index (0 to 5).

- **Why latch and clock pins?**  
  ➤ Clock synchronizes data shifts; latch pushes the shifted bits to output at once.

- **Why 330Ω resistor?**  
  ➤ Limits current through each segment (~10mA–15mA max safe draw per pin)

- **Why common cathode?**  
  ➤ Active-HIGH outputs from 74HC595 require segments to sink current to GND

---

---

## 4. 📝 ধাপে ধাপে কী হচ্ছে

1. power ON → সব segment একবার ON হয়  
2. button চাপলে → display clear হয়  
3. একটা random নাম্বার তৈরি হয়  
4. rollDice() → animation দেখায় (1→6→1 type)  
5. শেষে সেই নাম্বার display-এ দেখানো হয়

---

## 5. ✨ এই প্রজেক্টে কী হবে?

1. Power ON হলে ATtiny85 ready হয়  
2. Button চাপলে random নাম্বার আসে (1–6)  
3. সেই নাম্বার অনুযায়ী pattern shift করা হয়  
4. latch active হয় → 7-segment-এ number display হয়  
5. delay() দিয়ে result hold করা হয়

---

# ✅ এই প্রজেক্টে যা শিখবে

- 7-segment display চালানো shift register দিয়ে  
- digital pin সাশ্রয় করে multiple output চালানো  
- Button trigger → real-time embedded interaction  
- Segment control pattern তৈরি  
- millis()/delay() দিয়ে timing sync করা
---

## 6. 🚦 এখন নিজে চেষ্টা করো!

✅ Step-by-step implement করো:  
- Breadboard layout করো  
- jumper wire দিয়ে ঠিক মতো connections দাও  
- বোতামে press দিলে display-এ সংখ্যাগুলো ঘোরে কিনা চেক করো  
- বুঝে ফেলো কে কার সাথে কীভাবে কথা বলছে 😄  

🔋 Bonus: চাইলে তুমি ২টা 595 use করে double-digit dice বানাতে পারো!


---

