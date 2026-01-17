# 🚗 স্মার্ট পার্কিং সিস্টেম - Arduino (বিস্তারিত ব্যাখ্যা)

![Arduino Bangla Tutorial](https://img.shields.io/badge/ভাষা-বাংলা-green?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/লেভেল-মধ্যম-orange?style=for-the-badge)
![Smart Parking](https://img.shields.io/badge/Automation-Parking-blue?style=for-the-badge)

---

## 📚 সূচিপত্র
- [প্রজেক্ট পরিচিতি](#-প্রজেক্ট-পরিচিতি)
- [IR সেন্সর কী?](#-ir-সেন্সর-কী)
- [Servo Motor কীভাবে কাজ করে](#-servo-motor-কীভাবে-কাজ-করে)
- [প্রয়োজনীয় যন্ত্রপাতি](#-প্রয়োজনীয়-যন্ত্রপাতি)
- [সার্কিট সংযোগ](#-সার্কিট-সংযোগ)
- [কোড ব্যাখ্যা](#-কোড-ব্যাখ্যা)
- [কীভাবে কাজ করে](#-কীভাবে-কাজ-করে)
- [System States](#-system-states)
- [সমস্যা ও সমাধান](#-সমস্যা-ও-সমাধান)
- [শিক্ষণীয় বিষয়](#-শিক্ষণীয়-বিষয়)

---

## 🎯 প্রজেক্ট পরিচিতি

এই প্রজেক্টে আমরা একটি **স্মার্ট পার্কিং সিস্টেম** তৈরি করব যেখানে:
- **IR সেন্সর** দিয়ে গাড়ি entry/exit এবং parking slot detect করা হবে
- **Servo motor** দিয়ে gate স্বয়ংক্রিয়ভাবে খোলা-বন্ধ করা হবে
- **16×2 LCD** তে real-time slot availability দেখানো হবে
- **Serial Monitor** দিয়ে debugging করা যাবে

### এই প্রজেক্ট থেকে শিখবেন:
- ✅ IR sensor দিয়ে obstacle detection
- ✅ Servo motor control (0°-90° positioning)
- ✅ LCD display interfacing (4-bit mode)
- ✅ Multi-sensor system coordination
- ✅ State management programming
- ✅ Automation system basics

---

## 🔬 IR সেন্সর কী?

### সহজ ভাষায়:

**IR (Infrared) sensor** হলো একটি module যা সামনে কোনো বস্তু আছে কিনা detect করে। এতে IR LED (transmitter) আলো পাঠায় এবং photodiode (receiver) reflected আলো receive করে।

### IR Sensor এর গঠন:

```
IR Sensor Module (উপর থেকে দেখা):
┌─────────────────────────────┐
│   [●] [●] [●]               │
│   VCC OUT GND               │
│                             │
│   ┌───┐      ┌───┐          │
│   │LED│      │PD │          │ ← IR LED ও Photodiode
│   └───┘      └───┘          │
│                             │
│  [Potentiometer]            │ ← Sensitivity adjust
│       ╰──╮                  │
└──────────┴──────────────────┘

Pin সংযোগ:
  VCC → Arduino 5V
  OUT → Arduino Digital Pin (D6, D7, D8, D13)
  GND → Arduino GND
```

### IR Sensor কীভাবে কাজ করে:

```
কাজের পদ্ধতি:
┌────────────────────────────────────┐
│ ১. IR LED (Emitter):               │
│    → Infrared আলো নিঃসরণ করে     │
│                                    │
│ ২. কোনো বস্তু সামনে থাকলে:       │
│    → আলো reflect হয়ে ফিরে আসে    │
│                                    │
│ ৩. Photodiode (Receiver):          │
│    → Reflected আলো receive করে     │
│                                    │
│ ৪. Comparator Circuit:             │
│    → Analog signal কে digital-এ    │
│      রূপান্তর করে                 │
│                                    │
│ ৫. Digital Output:                 │
│    → HIGH (5V) = কোনো বস্তু নেই   │
│    → LOW (0V) = বস্তু সনাক্ত      │
└────────────────────────────────────┘

Logic:
  বস্তু নেই → IR beam intact → Photodiode কম signal → OUT = HIGH
  বস্তু আছে → IR beam blocked → Photodiode বেশি signal → OUT = LOW
```

### IR Sensor Characteristics:

| বৈশিষ্ট্য | মান | ব্যাখ্যা |
|----------|-----|---------|
| Operating Voltage | 3.3V - 5V | Arduino compatible |
| Detection Range | 2-30 cm | Potentiometer দিয়ে adjust |
| Output Type | Digital (TTL) | শুধু HIGH/LOW |
| Detection Logic | Active LOW | LOW = বস্তু detected |
| Response Time | <1 ms | খুব দ্রুত |
| Beam Angle | ~35° | Cone-shaped detection |
| Current Draw | ~20 mA | কম power |

### Detection Range Adjustment:

```
Potentiometer (উপর থেকে দেখা):
    ┌───────┐
    │   ↻   │ ← Clockwise ঘুরান: Range বাড়বে
    └───┬───┘   Counter-clockwise: Range কমবে
        │
     Sensitivity

Testing:
  1. বস্তু 5 cm দূরে রাখুন
  2. Potentiometer ধীরে ধীরে ঘুরান
  3. Module-এ LED জ্বলবে যখন detect করবে
  4. Multimeter দিয়ে output verify করুন:
     - বস্তু নেই: ~5V (HIGH)
     - বস্তু আছে: ~0V (LOW)
```

---

## ⚙️ Servo Motor কীভাবে কাজ করে

### SG90 Servo Motor বৈশিষ্ট্য:

| Parameter | Value | বিবরণ |
|-----------|-------|-------|
| Operating Voltage | 4.8V - 6V | Arduino 5V থেকে powered |
| Rotation Range | 0° - 180° | অর্ধেক rotation |
| Torque | 1.8 kg·cm @ 5V | হালকা gate এর জন্য যথেষ্ট |
| Speed | 0.1 s/60° @ 5V | দ্রুত response |
| Control Type | PWM signal | 50 Hz, 1-2 ms pulse width |
| Current Draw | 100-250 mA | Movement-এ peak |
| Weight | 9 grams | হালকা |

### Servo Wire Color Code:

```
SG90 Servo Wires:
┌─────────────────────────┐
│ Brown  → GND (Ground)   │
│ Red    → VCC (5V Power) │
│ Orange → Signal (PWM)   │
└─────────────────────────┘

Arduino Connection:
  Entry Servo:
    Brown → GND
    Red → 5V
    Orange → D9
  
  Exit Servo:
    Brown → GND
    Red → 5V
    Orange → D10
```

### PWM Control Theory:

```
PWM Signal দিয়ে Servo Control:
┌────────────────────────────────────┐
│ Pulse Width → Angle Position      │
│                                    │
│ 1.0 ms pulse → 0° (gate বন্ধ)     │
│ 1.5 ms pulse → 90° (mid position) │
│ 2.0 ms pulse → 180° (সম্পূর্ণ খোলা)│
│                                    │
│ PWM Frequency: 50 Hz (20 ms period)│
└────────────────────────────────────┘

Arduino Servo Library Functions:
  servo.attach(pin)      → Servo initialize
  servo.write(angle)     → Position set (0-180°)
  servo.read()           → Current position পড়া
  servo.detach()         → Servo pin release
```

### Gate Position States:

```
Entry/Exit Gate অবস্থা:
┌──────────────────────────────────────┐
│                                      │
│  বন্ধ (0°):           খোলা (90°):   │
│                                      │
│      │                    ────       │
│      │                                │
│      │  Gate Arm          Gate Arm   │
│      │                    (Vertical  │
│      │ (Horizontal)        উপরে)    │
│    ──┴──                 ──┴──       │
│    Servo                 Servo       │
│                                      │
└──────────────────────────────────────┘

Arduino Code:
  servo.write(0);    // Gate বন্ধ (horizontal)
  servo.write(90);   // Gate খোলা (vertical)
```

---

## 🧰 প্রয়োজনীয় যন্ত্রপাতি

| যন্ত্রের নাম | সংখ্যা | বিবরণ | উদ্দেশ্য |
|-------------|--------|-------|---------|
| Arduino UNO | ১টি | ATmega328P, 5V logic | Microcontroller |
| IR Sensor Module | ৪টি | Digital output, adjustable | Vehicle/slot detection |
| Servo Motor | ২টি | SG90, 0-180° | Gate automation |
| 16×2 LCD Display | ১টি | HD44780 compatible | Status display |
| 10kΩ Potentiometer | ১টি | LCD contrast এর জন্য | Display adjustment |
| ব্রেডবোর্ড | ১-২টি | 830 tie-points | সার্কিট তৈরির জন্য |
| জাম্পার তার | ~৪০টি | Male-to-Male | সংযোগ |
| USB Cable | ১টি | Type A to Type B | Programming ও power |
| 5V Power Supply | ১টি (ঐচ্ছিক) | 2A minimum | Servo এর জন্য |

### 💰 আনুমানিক খরচ: ১৫০০-২৫০০ টাকা

### Component চেনার উপায়:

**IR Sensor Module:**
```
সামনে থেকে:
  - দুটি গোল জিনিস: IR LED ও Photodiode
  - নীল/সাদা চাকা: Potentiometer (sensitivity adjust)
  - 3টি pin: VCC, OUT, GND
```

**SG90 Servo:**
```
চেনার উপায়:
  - ছোট প্লাস্টিক box
  - 3টি তার: Brown, Red, Orange
  - উপরে সাদা প্লাস্টিক arm (ঘুরে)
```

---

## 🔌 সার্কিট সংযোগ

### সম্পূর্ণ সংযোগ টেবিল:

**IR Sensors (৪টি):**

| IR Sensor | অবস্থান | Arduino Pin | VCC | GND | কাজ |
|-----------|---------|-------------|-----|-----|-----|
| IR #1 | Entry Gate | D6 | 5V | GND | আগমন vehicle detect |
| IR #2 | Parking Slot 1 | D7 | 5V | GND | Slot 1 occupancy |
| IR #3 | Parking Slot 2 | D8 | 5V | GND | Slot 2 occupancy |
| IR #4 | Exit Gate | D13 | 5V | GND | প্রস্থান vehicle detect |

**Servo Motors (২টি):**

| Servo | অবস্থান | Signal Pin | Power | Ground | Angle |
|-------|---------|-----------|-------|--------|-------|
| Servo 1 | Entry Gate | D9 | 5V | GND | 0° (বন্ধ) - 90° (খোলা) |
| Servo 2 | Exit Gate | D10 | 5V | GND | 0° (বন্ধ) - 90° (খোলা) |

**16×2 LCD Display (4-bit mode):**

| LCD Pin | Pin # | Arduino Pin | কাজ |
|---------|-------|-------------|-----|
| VSS | 1 | GND | Ground |
| VDD | 2 | 5V | Power |
| VO | 3 | Pot মাঝ | Contrast |
| RS | 4 | D12 | Register Select |
| RW | 5 | GND | Write mode |
| EN | 6 | D11 | Enable |
| D4 | 11 | D5 | Data bit 4 |
| D5 | 12 | D4 | Data bit 5 |
| D6 | 13 | D3 | Data bit 6 |
| D7 | 14 | D2 | Data bit 7 |
| LED+ | 15 | 5V (220Ω দিয়ে) | Backlight + |
| LED- | 16 | GND | Backlight - |

### সার্কিট ডায়াগ্রাম:

```
                    SMART PARKING SYSTEM
┌──────────────────────────────────────────────────┐
│                   Arduino UNO                    │
│  ┌────────────────────────────────────┐          │
│  │ DIGITAL PINS:                      │          │
│  │   D2  ●───→ LCD D7                 │          │
│  │   D3  ●───→ LCD D6                 │          │
│  │   D4  ●───→ LCD D5                 │          │
│  │   D5  ●───→ LCD D4                 │          │
│  │   D6  ●───→ Entry IR OUT           │          │
│  │   D7  ●───→ Slot 1 IR OUT          │          │
│  │   D8  ●───→ Slot 2 IR OUT          │          │
│  │   D9  ●───→ Entry Servo (Orange)   │          │
│  │   D10 ●───→ Exit Servo (Orange)    │          │
│  │   D11 ●───→ LCD EN                 │          │
│  │   D12 ●───→ LCD RS                 │          │
│  │   D13 ●───→ Exit IR OUT            │          │
│  │                                    │          │
│  │   5V  ●───→ Power Rails            │          │
│  │   GND ●───→ Ground Rails           │          │
│  └────────────────────────────────────┘          │
└──────────────────────────────────────────────────┘

IR SENSORS (৪টি):
┌────────────────────────────────────┐
│ Entry IR (D6):                     │
│   VCC → 5V                         │
│   OUT → D6                         │
│   GND → GND                        │
├────────────────────────────────────┤
│ Slot 1 IR (D7):                    │
│   VCC → 5V                         │
│   OUT → D7                         │
│   GND → GND                        │
├────────────────────────────────────┤
│ Slot 2 IR (D8):                    │
│   VCC → 5V                         │
│   OUT → D8                         │
│   GND → GND                        │
├────────────────────────────────────┤
│ Exit IR (D13):                     │
│   VCC → 5V                         │
│   OUT → D13                        │
│   GND → GND                        │
└────────────────────────────────────┘

SERVO MOTORS (২টি):
┌────────────────────────────────────┐
│ Entry Servo (D9):                  │
│   Brown  → GND                     │
│   Red    → 5V                      │
│   Orange → D9                      │
├────────────────────────────────────┤
│ Exit Servo (D10):                  │
│   Brown  → GND                     │
│   Red    → 5V                      │
│   Orange → D10                     │
└────────────────────────────────────┘
```

### ধাপে ধাপে সংযোগ:

```
ধাপ ১: Power Distribution
  - Arduino 5V → Breadboard + rail
  - Arduino GND → Breadboard - rail

ধাপ ২: IR Sensors সংযোগ (৪টি)
  - Entry IR: VCC→+, GND→-, OUT→D6
  - Slot 1 IR: VCC→+, GND→-, OUT→D7
  - Slot 2 IR: VCC→+, GND→-, OUT→D8
  - Exit IR: VCC→+, GND→-, OUT→D13

ধাপ ৩: Servo Motors সংযোগ (২টি)
  - Entry Servo: Red→+, Brown→-, Orange→D9
  - Exit Servo: Red→+, Brown→-, Orange→D10

ধাপ ৪: LCD Display সংযোগ
  - Power: VSS→GND, VDD→5V
  - Control: RS→D12, RW→GND, EN→D11
  - Data: D4→D5, D5→D4, D6→D3, D7→D2
  - Backlight: LED+→5V (220Ω দিয়ে), LED-→GND

ধাপ ৫: Potentiometer (LCD Contrast)
  - বাম terminal → GND
  - মাঝ terminal → LCD VO (Pin 3)
  - ডান terminal → 5V

ধাপ ৬: সংযোগ যাচাই করুন
  ✓ সব IR sensor powered (5V, GND)
  ✓ সব IR output সঠিক pin-এ
  ✓ দুটো servo powered ও signal সংযুক্ত
  ✓ LCD 4-bit mode (D4-D7 only)
  ✓ সব component এর common ground
```

---

## 💻 কোড ব্যাখ্যা

### সম্পূর্ণ কোড:

```cpp
/*
 * প্রজেক্ট 21: স্মার্ট পার্কিং সিস্টেম
 * লেখক: Md. Akhinoor Islam
 * বিভাগ: ESE, KUET
 * বিবরণ: IR sensor দিয়ে vehicle detect, servo gate control,
 *        এবং LCD-তে real-time slot status display
 */

#include <Servo.h>
#include <LiquidCrystal.h>

// Servo objects (entry এবং exit gate এর জন্য)
Servo entryServo;
Servo exitServo;

// IR Sensor pin definitions
#define IR_ENTRY 6    // Entry gate IR sensor
#define IR_SLOT1 7    // Parking slot 1 IR sensor
#define IR_SLOT2 8    // Parking slot 2 IR sensor
#define IR_EXIT 13    // Exit gate IR sensor

// Servo pin definitions
#define SERVO_ENTRY 9   // Entry gate servo
#define SERVO_EXIT 10   // Exit gate servo

// LCD initialization (RS, EN, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Gate angle constants
const int GATE_CLOSED = 0;   // Horizontal (বন্ধ)
const int GATE_OPEN = 90;    // Vertical (খোলা)
const int GATE_DELAY = 2000; // Gate খোলা থাকবে (ms)

void setup() {
  // Serial debugging এর জন্য
  Serial.begin(9600);
  Serial.println("Smart Parking System শুরু হয়েছে");
  
  // Servo attach করা
  entryServo.attach(SERVO_ENTRY);
  exitServo.attach(SERVO_EXIT);
  
  // Gate শুরুতে বন্ধ রাখা
  entryServo.write(GATE_CLOSED);
  exitServo.write(GATE_CLOSED);
  
  // IR sensor pins configure করা
  pinMode(IR_ENTRY, INPUT);
  pinMode(IR_SLOT1, INPUT);
  pinMode(IR_SLOT2, INPUT);
  pinMode(IR_EXIT, INPUT);
  
  // LCD initialize করা (16 columns, 2 rows)
  lcd.begin(16, 2);
  
  // Startup message
  lcd.setCursor(0, 0);
  lcd.print("Smart Parking");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
  
  // Initial slot status
  updateSlotDisplay();
}

void loop() {
  // সব IR sensor পড়া
  bool entryDetected = (digitalRead(IR_ENTRY) == LOW);  // LOW = vehicle আছে
  bool exitDetected = (digitalRead(IR_EXIT) == LOW);
  bool slot1Occupied = (digitalRead(IR_SLOT1) == LOW);
  bool slot2Occupied = (digitalRead(IR_SLOT2) == LOW);
  
  // Entry gate handle করা
  if (entryDetected) {
    Serial.println("Entry-তে Vehicle - Gate খোলা হচ্ছে");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Vehicle Entry");
    entryServo.write(GATE_OPEN);
    delay(GATE_DELAY);
    entryServo.write(GATE_CLOSED);
    lcd.clear();
  }
  
  // Exit gate handle করা
  if (exitDetected) {
    Serial.println("Exit-এ Vehicle - Gate খোলা হচ্ছে");
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Vehicle Exit");
    exitServo.write(GATE_OPEN);
    delay(GATE_DELAY);
    exitServo.write(GATE_CLOSED);
    lcd.clear();
  }
  
  // Slot status update করা
  updateSlotDisplay();
  
  // Serial Monitor-এ debug output
  Serial.print("Slot1: ");
  Serial.print(slot1Occupied ? "Occupied" : "Free");
  Serial.print(" | Slot2: ");
  Serial.println(slot2Occupied ? "Occupied" : "Free");
  
  delay(500);  // Update interval
}

// LCD তে slot status update করার function
void updateSlotDisplay() {
  bool slot1Occupied = (digitalRead(IR_SLOT1) == LOW);
  bool slot2Occupied = (digitalRead(IR_SLOT2) == LOW);
  
  // Slot 1 status
  lcd.setCursor(0, 0);
  lcd.print("Slot 1: ");
  if (slot1Occupied) {
    lcd.print("Occupied");
  } else {
    lcd.print("Free    ");  // Extra space = আগের text clear করা
  }
  
  // Slot 2 status
  lcd.setCursor(0, 1);
  lcd.print("Slot 2: ");
  if (slot2Occupied) {
    lcd.print("Occupied");
  } else {
    lcd.print("Free    ");
  }
}
```

---

### 📖 লাইন-বাই-লাইন ব্যাখ্যা:

#### ১. Library Include

```cpp
#include <Servo.h>
#include <LiquidCrystal.h>
```

**কী করে?**
- `Servo.h` - Arduino built-in servo motor control library
- `LiquidCrystal.h` - LCD character display control library
- এগুলো ছাড়া servo ও LCD function পাবেন না

---

#### ২. Object Declarations

```cpp
Servo entryServo;
Servo exitServo;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
```

**Servo Objects:**
- `entryServo` - Entry gate control করবে
- `exitServo` - Exit gate control করবে

**LCD Object:**
```cpp
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
                 (12, 11, 5,  4,  3,  2);
```
- RS (Register Select) = D12
- EN (Enable) = D11
- Data pins (D4-D7) = D5, D4, D3, D2

---

#### ৩. Pin Definitions

```cpp
#define IR_ENTRY 6
#define IR_SLOT1 7
#define IR_SLOT2 8
#define IR_EXIT 13
#define SERVO_ENTRY 9
#define SERVO_EXIT 10
```

**কেন `#define`?**
- Pin number এর পরিবর্তে readable name
- Hardware পরিবর্তন হলে শুধু এখানে edit করলেই হবে
- Memory overhead নেই (preprocessor macro)
- Convention: UPPERCASE ব্যবহার করা হয়

---

#### ৪. Constants

```cpp
const int GATE_CLOSED = 0;
const int GATE_OPEN = 90;
const int GATE_DELAY = 2000;
```

| Constant | মান | উদ্দেশ্য |
|----------|-----|---------|
| `GATE_CLOSED` | 0° | Horizontal position (blocking) |
| `GATE_OPEN` | 90° | Vertical position (allowing) |
| `GATE_DELAY` | 2000 ms | Gate কতক্ষণ খোলা থাকবে |

---

#### ৫. Setup Function

```cpp
void setup() {
  Serial.begin(9600);
  entryServo.attach(SERVO_ENTRY);
  exitServo.attach(SERVO_EXIT);
  entryServo.write(GATE_CLOSED);
  exitServo.write(GATE_CLOSED);
  pinMode(IR_ENTRY, INPUT);
  pinMode(IR_SLOT1, INPUT);
  pinMode(IR_SLOT2, INPUT);
  pinMode(IR_EXIT, INPUT);
  lcd.begin(16, 2);
  // ... startup messages ...
}
```

**ধাপে ধাপে:**

**a) Serial Communication:**
```cpp
Serial.begin(9600);
```
- 9600 baud rate-এ Serial শুরু
- Debugging এর জন্য sensor state monitor করা

**b) Servo Initialization:**
```cpp
entryServo.attach(SERVO_ENTRY);
exitServo.attach(SERVO_EXIT);
entryServo.write(GATE_CLOSED);
exitServo.write(GATE_CLOSED);
```
- `attach(pin)` - Servo object কে physical pin-এর সাথে যুক্ত করা
- `write(angle)` - Initial position set করা (0° = বন্ধ)
- Power-up-এ gate বন্ধ অবস্থায় শুরু হয়

**c) IR Sensor Configuration:**
```cpp
pinMode(IR_ENTRY, INPUT);
pinMode(IR_SLOT1, INPUT);
pinMode(IR_SLOT2, INPUT);
pinMode(IR_EXIT, INPUT);
```
- সব IR sensor pin কে INPUT mode-এ configure করা
- Arduino এই pin থেকে digital HIGH/LOW পড়বে

**d) LCD Initialization:**
```cpp
lcd.begin(16, 2);
```
- 16×2 LCD initialize করা (16 columns, 2 rows)
- 4-bit communication mode configure করা
- LCD operation এর আগে অবশ্যই call করতে হবে

---

#### ৬. Main Loop

```cpp
void loop() {
  bool entryDetected = (digitalRead(IR_ENTRY) == LOW);
  bool exitDetected = (digitalRead(IR_EXIT) == LOW);
  bool slot1Occupied = (digitalRead(IR_SLOT1) == LOW);
  bool slot2Occupied = (digitalRead(IR_SLOT2) == LOW);
  
  // Gate control
  // Display update
  // Serial debugging
  
  delay(500);
}
```

**IR Sensor Reading:**
```cpp
bool entryDetected = (digitalRead(IR_ENTRY) == LOW);
```

**কেন `== LOW`?**
```
Standard IR Module Logic:
  digitalRead() = HIGH (5V) → কোনো বস্তু নেই (beam clear)
  digitalRead() = LOW (0V)  → বস্তু detected (beam blocked)

Boolean Conversion:
  LOW (0) == LOW → true  (vehicle আছে)
  HIGH (1) == LOW → false (vehicle নেই)
```

---

#### ৭. Entry Gate Control

```cpp
if (entryDetected) {
  Serial.println("Entry-তে Vehicle - Gate খোলা হচ্ছে");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vehicle Entry");
  entryServo.write(GATE_OPEN);
  delay(GATE_DELAY);
  entryServo.write(GATE_CLOSED);
  lcd.clear();
}
```

**প্রবাহ:**
1. Check করা: vehicle at entry? (`entryDetected == true`)
2. Serial Monitor-এ debug message
3. LCD clear করে "Vehicle Entry" display করা
4. Gate খোলা (servo 90° ঘুরানো)
5. 2 সেকেন্ড অপেক্ষা (vehicle pass করার জন্য)
6. Gate বন্ধ (servo 0° ফিরিয়ে আনা)
7. LCD clear করা পরবর্তী status এর জন্য

---

#### ৮. Update Slot Display Function

```cpp
void updateSlotDisplay() {
  bool slot1Occupied = (digitalRead(IR_SLOT1) == LOW);
  bool slot2Occupied = (digitalRead(IR_SLOT2) == LOW);
  
  lcd.setCursor(0, 0);
  lcd.print("Slot 1: ");
  if (slot1Occupied) {
    lcd.print("Occupied");
  } else {
    lcd.print("Free    ");
  }
  
  lcd.setCursor(0, 1);
  lcd.print("Slot 2: ");
  if (slot2Occupied) {
    lcd.print("Occupied");
  } else {
    lcd.print("Free    ");
  }
}
```

**LCD Display Format:**
```
Row 0: |S|l|o|t| |1|:| |F|r|e|e| | | | |
       0 1 2 3 4 5 6 7 8 9 10... 15

Row 1: |S|l|o|t| |2|:| |O|c|c|u|p|i|e|d|
       0 1 2 3 4 5 6 7 8 9 10 11 12...

নোট: "Free" এর পরে extra space আগের "Occupied" text মুছে দেয়
```

---

## ⚙️ কীভাবে কাজ করে

### সিস্টেম Operation Flow:

```
┌─────────────────────────────────────────┐
│  POWER ON                               │
└──────────────┬──────────────────────────┘
               ↓
┌─────────────────────────────────────────┐
│  INITIALIZATION                         │
│  • Serial Monitor (9600 baud)           │
│  • Servo attach (D9, D10)               │
│  • Gates বন্ধ (0°)                      │
│  • IR sensors INPUT mode                │
│  • LCD initialize (16×2)                │
│  • "System Ready" display               │
└──────────────┬──────────────────────────┘
               ↓
┌─────────────────────────────────────────┐
│  MAIN LOOP (Continuous)                 │
└──────────────┬──────────────────────────┘
               ↓
       ┌───────┴───────┐
       │               │
       ↓               ↓
┌─────────────┐ ┌─────────────┐
│ SENSORS     │ │ CONTROL     │
│ • Entry IR  │ │ • Entry Gate│
│ • Exit IR   │ │ • Exit Gate │
│ • Slot 1    │ │ • LCD       │
│ • Slot 2    │ │ • Serial    │
└──────┬──────┘ └──────┬──────┘
       │               │
       └───────┬───────┘
               ↓
         500ms Wait
               ↓
         Loop Repeat
```

### বিস্তারিত Operation Scenarios:

#### Scenario 1: গাড়ি প্রবেশ করছে

```
Timeline:
  T=0s    : গাড়ি entry-র কাছে আসে
  T=0.1s  : Entry IR detect করে (LOW signal)
  T=0.2s  : LCD দেখায় "Vehicle Entry"
  T=0.3s  : Entry servo 90° ঘুরে (gate খোলে)
  T=2.3s  : গাড়ি pass করে
  T=2.4s  : Entry servo 0° ফিরে (gate বন্ধ)
  T=2.5s  : LCD clear, slot status দেখায়
```

#### Scenario 2: গাড়ি Slot 1-এ পার্ক করছে

```
Timeline:
  T=0s    : গাড়ি Slot 1-এ প্রবেশ করে
  T=0.1s  : Slot 1 IR detect করে (LOW)
  T=0.2s  : LCD update: "Slot 1: Occupied"
  T=...   : Display occupied দেখাতে থাকে
  T=Xmin  : গাড়ি Slot 1 ছেড়ে যায়
  T=Xmin+0.1s : Slot 1 IR clear (HIGH)
  T=Xmin+0.2s : LCD update: "Slot 1: Free    "
```

#### Scenario 3: গাড়ি বের হচ্ছে

```
Timeline:
  T=0s    : গাড়ি exit-এর কাছে আসে
  T=0.1s  : Exit IR detect করে (LOW signal)
  T=0.2s  : LCD দেখায় "Vehicle Exit"
  T=0.3s  : Exit servo 90° ঘুরে (gate খোলে)
  T=2.3s  : গাড়ি বেরিয়ে যায়
  T=2.4s  : Exit servo 0° ফিরে (gate বন্ধ)
  T=2.5s  : LCD clear, slot status দেখায়
```

---

## 🎭 System States

### State Diagram:

```
┌──────────────────────────────────────────────────┐
│                   IDLE STATE                     │
│  • দুটো gate বন্ধ (0°)                           │
│  • LCD তে slot status                            │
│  • IR trigger এর অপেক্ষায়                       │
└─────────┬────────────────────────────────────────┘
          │
    ┌─────┴─────┐
    │           │
    ↓           ↓
┌─────────┐ ┌─────────┐
│ ENTRY   │ │ EXIT    │
│ DETECTED│ │ DETECTED│
└────┬────┘ └────┬────┘
     │           │
     ↓           ↓
┌─────────┐ ┌─────────┐
│ OPEN    │ │ OPEN    │
│ ENTRY   │ │ EXIT    │
│ GATE    │ │ GATE    │
└────┬────┘ └────┬────┘
     │           │
     ↓           ↓
┌─────────┐ ┌─────────┐
│ WAIT    │ │ WAIT    │
│ 2s      │ │ 2s      │
└────┬────┘ └────┬────┘
     │           │
     ↓           ↓
┌─────────┐ ┌─────────┐
│ CLOSE   │ │ CLOSE   │
│ ENTRY   │ │ EXIT    │
│ GATE    │ │ GATE    │
└────┬────┘ └────┬────┘
     │           │
     └─────┬─────┘
           ↓
    IDLE-এ ফিরে যাও
```

---

## 📺 LCD Display Modes

### Display States:

#### Mode 1: স্বাভাবিক Operation (Slot Status)
```
┌────────────────┐
│Slot 1: Free    │ Row 0
│Slot 2: Occupied│ Row 1
└────────────────┘
```

#### Mode 2: গাড়ি প্রবেশ
```
┌────────────────┐
│Vehicle Entry   │ Row 0
│                │ Row 1
└────────────────┘
(2 সেকেন্ড দেখাবে)
```

#### Mode 3: গাড়ি প্রস্থান
```
┌────────────────┐
│                │ Row 0
│Vehicle Exit    │ Row 1
└────────────────┘
(2 সেকেন্ড দেখাবে)
```

#### Mode 4: System Startup
```
┌────────────────┐
│Smart Parking   │ Row 0
│System Ready    │ Row 1
└────────────────┘
(Boot-এ 2 সেকেন্ড)
```

---

## 🔧 সমস্যা ও সমাধান

### সাধারণ সমস্যা এবং সমাধান:

| সমস্যা | সম্ভাব্য কারণ | সমাধান |
|--------|--------------|---------|
| **LCD blank** | Power নেই | VDD (pin 2) থেকে 5V check করুন |
| | Contrast adjust হয়নি | Potentiometer ধীরে ঘুরান |
| **LCD তে boxes** | Contrast খুব বেশি | Potentiometer adjust করুন |
| | ভুল pin সংযোগ | D2-D5, D11-D12 verify করুন |
| **Servo নড়ে না** | Powered নয় | Red wire 5V check করুন |
| | Signal disconnect | Orange wire D9/D10 verify |
| | Current insufficient | External 5V supply ব্যবহার করুন |
| **Gate খোলে কিন্তু বন্ধ হয় না** | Software delay issue | `delay(GATE_DELAY)` check |
| | Mechanical block | Servo manually test করুন |
| **IR সবসময় detect করে** | Sensitivity বেশি | IR pot CCW ঘুরান |
| | Wiring reverse | OUT pin connection check |
| **IR কখনো detect করে না** | Power নেই | VCC, GND verify করুন |
| | Sensitivity কম | IR pot CW ঘুরান |
| | বস্তু দূরে | 2-10 cm range-এ আনুন |
| **ভুল slot occupied দেখায়** | Pin swap | D7=Slot1, D8=Slot2 verify |
| | IR logic inverted | `== LOW` code-এ check |
| **Entry gate exit-এ খোলে** | Pin conflict | D6=Entry, D13=Exit verify |
| **LCD text garbled** | সংযোগ loose | সব LCD wire reseat করুন |
| **Serial Monitor empty** | খোলা নেই | Tools → Serial Monitor |
| | ভুল baud rate | 9600 set করুন |

---

### Advanced Debugging:

#### IR Sensors আলাদা করে Test:
```cpp
void loop() {
  Serial.print("Entry: ");
  Serial.print(digitalRead(IR_ENTRY));
  Serial.print(" | Slot1: ");
  Serial.print(digitalRead(IR_SLOT1));
  Serial.print(" | Slot2: ");
  Serial.print(digitalRead(IR_SLOT2));
  Serial.print(" | Exit: ");
  Serial.println(digitalRead(IR_EXIT));
  delay(500);
}
// প্রত্যাশা: 1 (HIGH) clear, 0 (LOW) blocked
```

#### Servos স্বতন্ত্রভাবে Test:
```cpp
void loop() {
  entryServo.write(0);
  delay(1000);
  entryServo.write(90);
  delay(1000);
}
// প্রত্যাশা: Servo 0° ও 90° এর মধ্যে sweep করবে
```

---

## 🎓 শিক্ষণীয় বিষয়

### এই প্রজেক্ট থেকে যা শিখলাম:

| ধারণা | ব্যাখ্যা | বাস্তব ব্যবহার |
|------|---------|----------------|
| **IR Sensor Logic** | Obstacle detection digital output | Automation, robotics |
| **Servo Control** | Precise angular positioning | Gates, robotic arms |
| **LCD Interfacing** | Character display (4-bit) | User interfaces |
| **Multi-Sensor System** | একসাথে একাধিক input coordinate | Complex automation |
| **State Management** | System condition tracking | FSM programming |
| **Real-Time Display** | Continuous user feedback | Monitoring systems |

---

## 🚀 প্রজেক্ট বাড়ানোর আইডিয়া

### 🟢 Beginner Level:

#### ১. **LED Indicators যোগ করুন**
```cpp
#define LED_SLOT1 A0
#define LED_SLOT2 A1

void setup() {
  pinMode(LED_SLOT1, OUTPUT);
  pinMode(LED_SLOT2, OUTPUT);
}

void loop() {
  digitalWrite(LED_SLOT1, digitalRead(IR_SLOT1) == LOW ? HIGH : LOW);
  digitalWrite(LED_SLOT2, digitalRead(IR_SLOT2) == LOW ? HIGH : LOW);
}
// Red LED on = Slot occupied, Off = Free
```

#### ২. **Buzzer Alert**
```cpp
#define BUZZER A2

if (entryDetected) {
  tone(BUZZER, 1000, 200);  // Entry-তে short beep
}
```

### 🟡 Intermediate Level:

#### ৩. **RFID Access Control**
```cpp
#include <MFRC522.h>
MFRC522 rfid(SS_PIN, RST_PIN);

void loop() {
  if (rfid.PICC_IsNewCardPresent()) {
    if (authorizedCard()) {
      entryServo.write(GATE_OPEN);
    } else {
      lcd.print("Access Denied");
    }
  }
}
```

#### ৪. **SD Card Data Logging**
```cpp
#include <SD.h>
File logFile;

void logEntry(String timestamp, String event) {
  logFile = SD.open("parking.txt", FILE_WRITE);
  logFile.print(timestamp);
  logFile.print(",");
  logFile.println(event);
  logFile.close();
}
```

---

## 🌍 বাস্তব জীবনে ব্যবহার

### এই প্রযুক্তি কোথায় ব্যবহৃত হয়:

| Application | বিবরণ | শিল্প |
|-------------|-------|------|
| **Shopping Mall Parking** | Multi-level parking management | Retail |
| **Airport Parking** | Long-term parking | Transportation |
| **Hospital Parking** | Priority parking | Healthcare |
| **Office Buildings** | Employee parking | Corporate |
| **Smart Cities** | Integrated parking guidance | Urban planning |
| **Residential** | Gated community | Real estate |

---

## 👨‍🎓 লেখক

**Md. Akhinoor Islam**  
📚 Energy Science and Engineering (ESE)  
🏫 Khulna University of Engineering & Technology (KUET)  
🌐 [GitHub Profile](https://github.com/Akhinoor14)

---

## 🔗 সম্পর্কিত প্রজেক্ট:

1. [Ultrasonic Sensor](../07%20Interfacing%20an%20ultrasonic%20sensor%20with%20arduino/)
2. [Servo Motor](../06.%20Interfacing%20servo%20motor%20with%20arduino/)
3. [16×2 LCD Display](../15%20Interfacing%2016-2%20Lcd%20display/)
4. [Photodiode](../10%20Interfacing%20Photodiode/)

---

## ✅ Checklist

### প্রজেক্ট শুরুর আগে:

- [ ] সব component সংগ্রহ করেছি
- [ ] IR sensor এবং servo চিহ্নিত করেছি
- [ ] Circuit diagram বুঝেছি
- [ ] Pin mapping clear

### সংযোগের সময়:

- [ ] 4টি IR sensor: VCC, GND, OUT সঠিক
- [ ] 2টি servo: Red, Brown, Orange সঠিক
- [ ] LCD: 4-bit mode (D2-D5)
- [ ] Potentiometer LCD contrast-এ

### Code upload এর পর:

- [ ] Serial Monitor (9600 baud)
- [ ] LCD "System Ready" দেখাচ্ছে
- [ ] Entry gate vehicle detect করে খোলে
- [ ] Exit gate vehicle detect করে খোলে
- [ ] Slot status correctly update হয়
- [ ] Gates 2 সেকেন্ড পর বন্ধ হয়

---

**শুভ কোডিং! 🎉**  
**Automated parking solution তৈরি করুন এবং system integration শিখুন! 🚗**
