# 🚶 PIR Motion Sensor - বিস্তারিত বাংলা টিউটোরিয়াল

![Motion Sensor](https://img.shields.io/badge/Sensor-PIR%20Motion-orange?style=for-the-badge)
![Language](https://img.shields.io/badge/ভাষা-বাংলা-success?style=for-the-badge)
![Level](https://img.shields.io/badge/লেভেল-শিক্ষানবিস-green?style=for-the-badge)

---

## 📚 সূচিপত্র
- [প্রজেক্ট পরিচিতি](#-প্রজেক্ট-পরিচিতি)
- [PIR Sensor কী?](#-pir-sensor-কী)
- [যন্ত্রপাতি পরিচিতি](#-যন্ত্রপাতি-পরিচিতি)
- [সার্কিট ডায়াগ্রাম](#-সার্কিট-ডায়াগ্রাম)
- [কাজের নীতি](#-কাজের-নীতি)
- [কোড ব্যাখ্যা](#-কোড-ব্যাখ্যা)
- [পদক্ষেপসমূহ](#-পদক্ষেপসমূহ)
- [সমস্যা সমাধান](#-সমস্যা-সমাধান)
- [শিক্ষণীয় বিষয়](#-শিক্ষণীয়-বিষয়)

---

## 🎯 প্রজেক্ট পরিচিতি

এই প্রজেক্টে আমরা **PIR (Passive Infrared) Motion Sensor** ব্যবহার করে **নড়াচড়া সনাক্ত** করব। যখন কোনো মানুষ বা প্রাণী sensor-এর সামনে দিয়ে যাবে, তখন LED জ্বলবে এবং Serial Monitor-এ message দেখা যাবে। এটি security system, automatic light, এবং smart home-এর মূল ভিত্তি!

### 🎓 এই প্রজেক্ট থেকে শিখব:
- ✅ PIR sensor কীভাবে কাজ করে
- ✅ Infrared radiation detection
- ✅ Digital signal পড়া (HIGH/LOW)
- ✅ Conditional logic (if-else)
- ✅ Motion-triggered automation
- ✅ Security system basics

---

## 💡 PIR Sensor কী?

### সহজ ভাষায়:

**PIR** মানে **Passive Infrared** (নিষ্ক্রিয় ইনফ্রারেড)। এই sensor কিছু পাঠায় না, শুধু **গরম জিনিস থেকে আসা infrared radiation** (তাপ) সনাক্ত করে। 

```
মানুষ এবং প্রাণীর দেহ = ~37°C
     ↓
Infrared radiation (তাপ) নির্গত করে
     ↓
PIR sensor এই তাপ সনাক্ত করে
     ↓
Signal পাঠায় Arduino-তে
```

**Key Point:**
```
স্থির বস্তু = কোনো detection নেই ❌
নড়াচড়া = Detection! ✅

কারণ: PIR শুধু তাপের পরিবর্তন সনাক্ত করে,
      স্থির তাপ নয়।
```

### PIR vs অন্যান্য Sensor:

| Sensor | পদ্ধতি | Range | দাম | ব্যবহার |
|--------|--------|-------|-----|---------|
| **PIR** | Infrared তাপ | 3-7m | সস্তা | Security, lighting |
| **Ultrasonic** | Sound echo | 2-400cm | সস্তা | Distance, parking |
| **Microwave** | Radio waves | 5-20m | ব্যয়বহুল | Outdoor security |
| **Camera** | Image analysis | Variable | মাঝারি | Smart surveillance |

### PIR-এর সুবিধা:

```
✅ খুব সস্তা ($1-2)
✅ কম বিদ্যুৎ খায় (<65mA)
✅ সহজ ব্যবহার (শুধু 3 wire)
✅ দীর্ঘ দূরত্ব (7m পর্যন্ত)
✅ প্রশস্ত coverage (110° angle)
✅ দিন-রাত কাজ করে
```

---

## 🧰 যন্ত্রপাতি পরিচিতি

### 1️⃣ **HC-SR501 PIR Sensor Module**

```
HC-SR501 Module (উপর থেকে দেখলে):
┌────────────────────────────────┐
│    ┌──────────────┐            │
│    │  White Dome  │◄─── Fresnel Lens
│    │  (Lens)      │    (সাদা গোলাকার)
│    └──────────────┘            │
│                                │
│  ┌──────┐  ┌──────┐           │
│  │ Sx   │  │ Tx   │◄───────── Adjustable knobs
│  │Sens. │  │Time  │           │
│  └──────┘  └──────┘           │
│                                │
│  ┌────┐                        │
│  │RTRG│◄────────────────────── Jumper
│  └────┘   (H/L)                │
│                                │
│  VCC  OUT  GND  ◄───────────── Pins
└────────────────────────────────┘
```

#### Pin বিবরণ:

| Pin | নাম | কাজ | সংযোগ |
|-----|-----|-----|--------|
| **Pin 1** | VCC | বিদ্যুৎ (4.5V-20V) | Arduino 5V |
| **Pin 2** | OUT | Signal output | Arduino D2 |
| **Pin 3** | GND | Ground | Arduino GND |

#### Fresnel Lens (সাদা গোলাকার):

```
Fresnel Lens-এর কাজ:
  • Infrared radiation focus করে
  • Detection range বাড়ায় (3m → 7m)
  • একাধিক zone তৈরি করে
  • Wide angle coverage (110°)

ছাড়া:  🌡️ ───────→ [PIR] (~3m)
সহ:     🌡️ ╲  │  ╱ [Lens+PIR] (~7m)
            ╲ │ ╱
```

#### Adjustable Settings:

##### 1️⃣ **Sensitivity (Sx) - সংবেদনশীলতা**

```
ঘড়ির কাঁটার বিপরীতে ঘুরালে:
  → কম range (~3m)
  → ছোট ঘরের জন্য
  
ঘড়ির কাঁটার দিকে ঘুরালে:
  → বেশি range (~7m)
  → বড় ঘর/করিডোরের জন্য
```

##### 2️⃣ **Time Delay (Tx) - সময় বিলম্ব**

```
ঘড়ির কাঁটার বিপরীতে ঘুরালে:
  → কম delay (~0.3 second)
  → দ্রুত response
  
ঘড়ির কাঁটার দিকে ঘুরালে:
  → বেশি delay (~200 second)
  → LED দীর্ঘক্ষণ জ্বলে
  
Delay = Motion detect হওয়ার পর 
        কতক্ষণ LED ON থাকবে
```

##### 3️⃣ **Trigger Mode Jumper**

```
H Position (Repeatable Mode):
  • নড়াচড়া চলতে থাকলে LED জ্বলতেই থাকে
  • প্রতিবার motion-এ timer reset হয়
  • Continuous monitoring-এর জন্য
  • LED = ON যতক্ষণ motion আছে
  
L Position (Non-repeatable Mode):
  • একবার detect হলে LED জ্বলে
  • Delay শেষে LED বন্ধ
  • পরবর্তী detection-এর জন্য 2.5s অপেক্ষা
  • LED = একবার blink per motion
```

### 2️⃣ **LED + 220Ω Resistor**

**কেন 220Ω Resistor দরকার?**

```
Without Resistor:
  Arduino D13 (5V) → LED → GND
  Current = 5V / 20Ω (LED resistance)
  Current = 250mA ❌ (Too much! LED burns!)

With 220Ω Resistor:
  Arduino D13 (5V) → 220Ω → LED → GND
  Current = 3V / 220Ω
  Current = 13.6mA ✅ (Safe!)
  
LED-এর জন্য ideal current: 10-20mA
```

**LED Pin চেনা:**

```
LED:
  ┌───┐
  │ ● │  ◄── Flat edge = Cathode (-)
  │   │
  │   │
  ├───┤  ◄── Longer lead = Anode (+)
  │   │
  └───┘

Anode (+) → D13
Cathode (-) → 220Ω → GND
```

### 3️⃣ **Arduino UNO**

এই প্রজেক্টে Arduino-র কাজ:
- PIR sensor-কে 5V বিদ্যুৎ দেওয়া
- D2 pin দিয়ে PIR signal পড়া (digitalRead)
- D13 pin দিয়ে LED নিয়ন্ত্রণ (digitalWrite)
- Serial Monitor-এ message পাঠানো

---

## 🔌 সার্কিট ডায়াগ্রাম

### সংযোগ তালিকা:

| Component | Arduino Pin | বিস্তারিত |
|-----------|-------------|-----------|
| PIR VCC | 5V | বিদ্যুৎ সরবরাহ |
| PIR OUT | D2 | Motion signal |
| PIR GND | GND | Ground |
| LED Anode (+) | D13 | LED control |
| LED Cathode (-) | GND (via 220Ω) | LED ground |

### Circuit Diagram (ASCII):

```
Arduino UNO       HC-SR501 PIR      LED Circuit
┌──────────┐      ┌──────────┐      ┌─────────┐
│          │      │ [Lens]   │      │   LED   │
│ 5V  ●────┼──────┤ VCC      │      │    │    │
│          │      │          │      │  Anode  │
│ GND ●────┼──┬───┤ GND      │      │    │    │
│          │  │   │          │      │    ↓    │
│ D2  ●────┼──┼───┤ OUT      │      │    │    │
│          │  │   └──────────┘      │  220Ω   │
│ D13 ●────┼──┼─────────────────────┤    │    │
│          │  │                     │ Cathode │
└──────────┘  │                     │    │    │
              └─────────────────────┴────┴────┘
                                         ↓
                                        GND
```

### Breadboard Layout:

```
Breadboard Setup:
┌─────────────────────────────────┐
│ + Rail (Red)                    │◄── Arduino 5V
│ - Rail (Blue)                   │◄── Arduino GND
│                                 │
│ PIR Module:                     │
│   Row 10: VCC → + Rail          │
│   Row 11: OUT → D2 (wire)       │
│   Row 12: GND → - Rail          │
│                                 │
│ LED Circuit:                    │
│   Row 20: LED Anode → D13       │
│   Row 21: LED Cathode → 220Ω   │
│   Row 22: 220Ω → - Rail         │
└─────────────────────────────────┘
```

### Wire Color Convention:

```
🔴 Red wire:    5V → PIR VCC
⚫ Black wire:  GND → PIR GND
🟡 Yellow wire: D2 → PIR OUT
🔵 Blue wire:   D13 → LED Anode
```

---

## ⚙️ কাজের নীতি

### ধাপে ধাপে কীভাবে কাজ করে:

```
ধাপ ১: PIR Sensor চালু হওয়া
  • Arduino 5V power দেয়
  • Warm-up time: 30-60 second
  • এই সময় LED flicker করতে পারে
  • Sensor পরিবেশের তাপ মাপে (calibration)
   ↓
ধাপ ২: Idle State (কোনো নড়াচড়া নেই)
  • PIR OUT pin = LOW (0V)
  • Arduino digitalRead(D2) = LOW
  • LED = OFF
  • Serial: "No Motion"
   ↓
ধাপ ৩: Motion Detection!
  • মানুষ সামনে দিয়ে যায়
  • Infrared radiation পরিবর্তন হয়
  • PIR OUT pin = HIGH (3.3V)
  • Arduino digitalRead(D2) = HIGH
   ↓
ধাপ ৪: Arduino Response
  • if (pirState == HIGH) condition true হয়
  • digitalWrite(D13, HIGH) → LED জ্বলে
  • Serial.println("Motion Detected!")
   ↓
ধাপ ৫: Delay Period
  • LED জ্বলে থাকে (Tx setting অনুযায়ী)
  • Repeatable mode: নতুন motion-এ timer reset
  • Non-repeatable mode: delay শেষে বন্ধ
   ↓
ধাপ ৬: No Motion (আবার স্থির)
  • PIR OUT = LOW
  • digitalRead(D2) = LOW
  • digitalWrite(D13, LOW) → LED বন্ধ
  • Serial: "No Motion"
```

### Digital Signal বোঝা:

PIR sensor একটি **digital sensor**, মানে output শুধু দুই রকম:

```
PIR Output:
  HIGH = Motion detected (3.3V)
  LOW = No motion (0V)

Arduino digitalRead():
  Voltage > 2.5V → HIGH (1)
  Voltage < 1.0V → LOW (0)

কোনো middle value নেই! শুধু ON/OFF
```

### Timing Diagram:

```
মানুষ:    হাঁটা শুরু   দাঁড়ানো  আবার হাঁটা
          ╔═══════╗     │     ╔══════╗
          ║       ║     │     ║      ║
   ───────╝       ╚─────┴─────╝      ╚────

PIR OUT:        ╔════════════╗  ╔═════════╗
   HIGH         ║            ║  ║         ║
                ║            ║  ║         ║
   LOW    ──────╝            ╚──╝         ╚───
                ▲   Delay    ▲  ▲
                │   (Tx)     │  │
            Detection      End  New
                              Motion

LED:            ████████████████  ███████████
   ON           ║            ║  ║         ║
                ║            ║  ║         ║
   OFF    ──────╝            ╚──╝         ╚───

Serial:    "Motion"      "No"    "Motion"
```

---

## 💻 কোড ব্যাখ্যা

### সম্পূর্ণ কোড:

```cpp
/*
 * Project: PIR Motion Sensor
 * নড়াচড়া সনাক্তকরণ প্রজেক্ট
 */

const int pirPin = 2;   // PIR sensor D2 pin-এ
const int ledPin = 13;  // LED D13 pin-এ

void setup() {
  pinMode(pirPin, INPUT);   // PIR input হিসেবে
  pinMode(ledPin, OUTPUT);  // LED output হিসেবে
  Serial.begin(9600);       // Serial communication
}

void loop() {
  int pirState = digitalRead(pirPin);  // PIR state পড়া
  
  if (pirState == HIGH) {              // Motion detected?
    digitalWrite(ledPin, HIGH);        // LED জ্বালানো
    Serial.println("Motion Detected!");
  } else {                             // No motion
    digitalWrite(ledPin, LOW);         // LED বন্ধ
    Serial.println("No Motion");
  }
  
  delay(500);  // 0.5 সেকেন্ড অপেক্ষা
}
```

---

### লাইন বাই লাইন ব্যাখ্যা:

#### 1️⃣ **Pin Declaration:**

```cpp
const int pirPin = 2;
const int ledPin = 13;
```

**ব্যাখ্যা:**
- `const int` = স্থির integer (পরিবর্তন হবে না)
- `pirPin = 2` = PIR-এর OUT pin D2-এ সংযুক্ত
- `ledPin = 13` = LED D13-এ সংযুক্ত (Arduino-তে built-in LED আছে D13-এ)

**কেন D2 এবং D13?**

| Pin | কারণ |
|-----|------|
| D2 | যেকোনো digital pin ব্যবহার করা যায় (D2-D12) |
| D13 | Built-in LED আছে, test করতে সুবিধা |

#### 2️⃣ **Setup Function:**

```cpp
void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}
```

**ব্যাখ্যা:**

##### pinMode(pirPin, INPUT):
```
INPUT mode মানে:
  • Arduino এই pin দিয়ে signal পড়বে
  • High impedance (কোনো voltage পাঠায় না)
  • External device (PIR) voltage দেবে
  • digitalRead() ব্যবহার করা যাবে
```

##### pinMode(ledPin, OUTPUT):
```
OUTPUT mode মানে:
  • Arduino এই pin দিয়ে signal পাঠাবে
  • Voltage control করতে পারবে (HIGH/LOW)
  • LED, motor, buzzer চালাতে পারবে
  • digitalWrite() ব্যবহার করা যাবে
```

##### Serial.begin(9600):
```
Serial communication চালু:
  • Computer-এর সাথে যোগাযোগ
  • Debugging-এর জন্য দরকারি
  • Baud rate: 9600 (standard)
```

#### 3️⃣ **Loop Function:**

```cpp
void loop() {
  // এই code বারবার চলতে থাকে (infinite loop)
}
```

**Loop-এর কাজ:**
1. PIR sensor পড়া
2. Motion check করা
3. LED নিয়ন্ত্রণ করা
4. Serial message পাঠানো
5. কিছুক্ষণ অপেক্ষা
6. আবার ধাপ 1 থেকে শুরু

#### 4️⃣ **Digital Read:**

```cpp
int pirState = digitalRead(pirPin);
```

**ব্যাখ্যা:**
- `digitalRead()` = Digital pin-এর voltage পড়ে
- Return করে: **HIGH (1)** বা **LOW (0)**
- `pirState` variable-এ সংরক্ষণ করা হয়

**digitalRead() কীভাবে কাজ করে:**

```
D2 pin-এ voltage measurement:
  • Voltage > 2.5V → HIGH (1)
  • Voltage < 1.0V → LOW (0)
  • Execution time: ~5 microseconds

PIR Output → D2 Voltage → digitalRead()
Motion:   3.3V      →  HIGH (1)
No Motion: 0V       →  LOW (0)
```

#### 5️⃣ **Conditional Logic:**

```cpp
if (pirState == HIGH) {
  // Motion detected
} else {
  // No motion
}
```

**ব্যাখ্যা:**

```
Decision Making:
┌─────────────────┐
│ pirState == HIGH?│
└────────┬─────────┘
    YES  │  NO
  ┌──────┴──────┐
  ↓             ↓
TRUE         FALSE
Motion       No Motion
```

**Comparison Operators:**

| Operator | অর্থ | উদাহরণ |
|----------|------|---------|
| `==` | সমান | `pirState == HIGH` |
| `!=` | সমান নয় | `pirState != LOW` |
| `>` | বড় | `x > 10` |
| `<` | ছোট | `x < 5` |

#### 6️⃣ **LED Control:**

```cpp
digitalWrite(ledPin, HIGH);  // LED জ্বালানো
digitalWrite(ledPin, LOW);   // LED বন্ধ
```

**ব্যাখ্যা:**

```
digitalWrite(pin, state):
  • pin: যে pin control করতে চাই (D13)
  • state: HIGH (5V) বা LOW (0V)

HIGH লিখলে:
  • D13 pin = 5V
  • Current flow: D13 → 220Ω → LED → GND
  • LED জ্বলে ✅

LOW লিখলে:
  • D13 pin = 0V
  • কোনো current flow নেই
  • LED বন্ধ ❌
```

**Current Calculation:**

```
Circuit: 5V → 220Ω → LED (2V drop) → GND

Ohm's Law: I = V / R
I = (5V - 2V) / 220Ω
I = 3V / 220Ω
I = 13.6mA (LED-এর জন্য safe!)
```

#### 7️⃣ **Serial Output:**

```cpp
Serial.println("Motion Detected!");
Serial.println("No Motion");
```

**ব্যাখ্যা:**
- `Serial.println()` = টেক্সট print + newline যোগ
- Serial Monitor-এ দেখা যায়

**Output দেখতে:**
```
No Motion
No Motion
Motion Detected!
Motion Detected!
Motion Detected!
No Motion
No Motion
```

**Serial Functions Comparison:**

| Function | Output | Newline? |
|----------|--------|----------|
| `Serial.print("Hi")` | Hi | ❌ No |
| `Serial.println("Hi")` | Hi | ✅ Yes |

#### 8️⃣ **Delay:**

```cpp
delay(500);
```

**ব্যাখ্যা:**
- `500` milliseconds = 0.5 second
- Program এই সময় থেমে থাকে
- পরবর্তী loop iteration শুরু করার আগে অপেক্ষা

**কেন Delay দরকার?**

```
Without delay (0ms):
  • প্রতি ~0.001s একটি reading
  • Serial Monitor spam (অপঠনীয়)
  • Unnecessary CPU usage

With delay (500ms):
  • প্রতি 0.5s একটি reading (2 readings/second)
  • Serial Monitor পড়া সহজ
  • Efficient CPU usage
```

**Delay Options:**

| Delay (ms) | সময় | Readings/sec | ব্যবহার |
|-----------|------|--------------|---------|
| 100 | 0.1s | 10 | দ্রুত response |
| 500 | 0.5s | 2 | Standard |
| 1000 | 1s | 1 | Slow monitoring |

---

### Code Flow Visualization:

```
        START
          │
          ↓
      ┌────────┐
      │ setup()│
      └────┬───┘
           │
    ┌──────┴──────────┐
    │ pinMode setup   │
    │ Serial start    │
    └──────┬──────────┘
           │
           ↓
    ┌──────────────┐
    │   loop()     │◄────────────┐
    └──────┬───────┘             │
           │                     │
           ↓                     │
    ┌──────────────┐             │
    │ digitalRead  │             │
    │   (pirPin)   │             │
    └──────┬───────┘             │
           │                     │
      ┌────┴────┐                │
      │ HIGH?   │                │
      └────┬────┘                │
       YES │ NO                  │
    ┌──────┴──────┐              │
    ↓             ↓              │
┌────────┐   ┌────────┐          │
│LED HIGH│   │LED LOW │          │
│"Motion"│   │"No M." │          │
└───┬────┘   └───┬────┘          │
    │            │               │
    └─────┬──────┘               │
          ↓                      │
    ┌──────────┐                 │
    │delay(500)│                 │
    └─────┬────┘                 │
          │                      │
          └──────────────────────┘
```

---

### Advanced Code Examples:

#### **Motion Counter (নড়াচড়া গণনা):**

```cpp
const int pirPin = 2;
const int ledPin = 13;
int motionCount = 0;
bool lastState = LOW;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Motion Counter Started!");
}

void loop() {
  int pirState = digitalRead(pirPin);
  
  // নতুন motion detect হলে count বাড়ানো
  if (pirState == HIGH && lastState == LOW) {
    motionCount++;
    Serial.print("Motion #");
    Serial.println(motionCount);
    digitalWrite(ledPin, HIGH);
  } else if (pirState == LOW) {
    digitalWrite(ledPin, LOW);
  }
  
  lastState = pirState;  // Save করা
  delay(100);
}
```

#### **Buzzer Alarm System:**

```cpp
const int pirPin = 2;
const int buzzerPin = 8;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  
  Serial.println("Alarm System");
  Serial.println("Waiting 60s for PIR warm-up...");
  delay(60000);  // 60 second warm-up
  Serial.println("Alarm ARMED!");
}

void loop() {
  if (digitalRead(pirPin) == HIGH) {
    Serial.println("⚠ INTRUDER ALERT!");
    
    // Alarm sound (10 beeps)
    for (int i = 0; i < 10; i++) {
      tone(buzzerPin, 1000, 200);  // 1kHz, 200ms
      delay(300);
    }
    
    delay(5000);  // 5 second pause
  }
  delay(100);
}
```

#### **Smart Light (Automatic Lighting):**

```cpp
const int pirPin = 2;
const int ledPin = 13;
unsigned long lastMotion = 0;
const unsigned long timeout = 10000;  // 10 seconds

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(pirPin) == HIGH) {
    lastMotion = millis();  // Time save করা
    digitalWrite(ledPin, HIGH);
    Serial.println("Motion - Light ON");
  }
  
  // 10 second পর light বন্ধ
  if (millis() - lastMotion > timeout && lastMotion != 0) {
    digitalWrite(ledPin, LOW);
    Serial.println("Timeout - Light OFF");
    lastMotion = 0;  // Reset
  }
  
  delay(100);
}
```

---

## 📋 পদক্ষেপসমূহ

### ধাপ ১: PIR Settings Adjust করা

```
Potentiometer Settings:
┌─────────────────────────────┐
│ Sx (Sensitivity):           │
│   • শুরুতে মাঝামাঝি রাখুন  │
│   • Test করে adjust করবেন  │
│                             │
│ Tx (Time Delay):            │
│   • শুরুতে minimum (কম delay)│
│   • Test করে বাড়াবেন       │
│                             │
│ Jumper:                     │
│   • H position (Repeatable) │
└─────────────────────────────┘
```

### ধাপ ২: Connection করা

**Checklist:**
```
✅ PIR VCC → Arduino 5V
✅ PIR OUT → Arduino D2
✅ PIR GND → Arduino GND
✅ LED Anode (+) → D13
✅ LED Cathode (-) → 220Ω → GND
✅ 220Ω resistor জরুরি!
```

### ধাপ ৩: Code Upload

1. Arduino IDE খুলুন
2. `Arduino C++ code.ino` file load করুন
3. **Tools → Board → Arduino UNO**
4. **Tools → Port → COM[X]**
5. **Upload** button (→) click করুন
6. "Done uploading" দেখা পর্যন্ত অপেক্ষা করুন

### ধাপ ৪: PIR Warm-up

```
⚠️ গুরুত্বপূর্ণ: PIR চালু হওয়ার পর 30-60 second অপেক্ষা করুন!

Warm-up সময়:
  • Sensor calibration চলে
  • LED flicker করতে পারে
  • এই সময় motion test করবেন না
  
Ready signal:
  • LED স্থির হয়ে OFF থাকবে
  • Serial Monitor: "No Motion"
```

### ধাপ ৫: Serial Monitor খোলা

```
Tools → Serial Monitor (বা Ctrl+Shift+M)
Baud rate: 9600 নির্বাচন করুন

Output দেখতে পাবেন:
"No Motion"
"No Motion"
"Motion Detected!"  ◄── হাত নাড়ালে
```

### ধাপ ৬: Test করা

**Test Procedures:**

```
Test 1: হাত নাড়ানো
  • PIR-এর সামনে (~1-2m) হাত নাড়ান
  • LED জ্বলবে ✅
  • Serial: "Motion Detected!"
  
Test 2: স্থির থাকা
  • একদম নড়বেন না
  • Delay শেষে LED বন্ধ হবে
  • Serial: "No Motion"
  
Test 3: হাঁটা
  • PIR-এর সামনে দিয়ে হাঁটুন
  • LED জ্বলবে
  • দূরে চলে যান → LED বন্ধ
  
Test 4: Range Test
  • দূরে সরে যান ধীরে ধীরে
  • কত দূর থেকে detect করে দেখুন
```

---

## 🔧 সমস্যা সমাধান

### সাধারণ সমস্যা:

| সমস্যা | কারণ | সমাধান |
|--------|------|--------|
| LED সবসময় জ্বলে | PIR calibration হয়নি | 60s warm-up দিন |
| কোনো detection নেই | ভুল pin connection | D2 connection চেক করুন |
| খুব বেশি sensitive | Sensitivity বেশি | Sx ঘড়ির কাঁটার বিপরীতে ঘুরান |
| LED দীর্ঘক্ষণ জ্বলে | Time delay বেশি | Tx ঘড়ির কাঁটার বিপরীতে ঘুরান |
| Erratic behavior | বাতাস/আলো | PIR ঢেকে রাখুন |
| Range কম | Sensitivity কম | Sx ঘড়ির কাঁটায় ঘুরান |

### PIR Calibration Test:

```cpp
// PIR ঠিক আছে কিনা test
void testPIR() {
  Serial.println("PIR Test শুরু...");
  Serial.println("60s warm-up - নড়বেন না!");
  
  // Warm-up countdown
  for (int i = 60; i > 0; i--) {
    Serial.print(i);
    Serial.println(" seconds...");
    delay(1000);
  }
  
  Serial.println("✓ Warm-up complete!");
  Serial.println("এখন হাত নাড়ান...");
  
  // Motion detection test
  unsigned long startTime = millis();
  bool detected = false;
  
  while (millis() - startTime < 10000) {  // 10s test
    if (digitalRead(pirPin) == HIGH) {
      Serial.println("✓ Motion detected! PIR ঠিক আছে!");
      detected = true;
      break;
    }
    delay(100);
  }
  
  if (!detected) {
    Serial.println("✗ Problem! Connection চেক করুন");
  }
}
```

### Range Adjustment Guide:

```
Range বাড়াতে:
  1. Sx knob ঘড়ির কাঁটায় ঘুরান
  2. Test করুন (দূরে সরে motion করুন)
  3. Desired range পাওয়া পর্যন্ত adjust
  
Range কমাতে:
  1. Sx knob ঘড়ির কাঁটার বিপরীতে ঘুরান
  2. খুব কাছে না আসলে detect হবে না
  3. False detection কমবে
```

---

## 🎓 শিক্ষণীয় বিষয়

### যা শিখলাম:

```
✅ PIR sensor-এর কাজের নীতি
✅ Infrared radiation detection
✅ Digital signal processing (HIGH/LOW)
✅ pinMode() - INPUT/OUTPUT configuration
✅ digitalRead() - Digital pin পড়া
✅ digitalWrite() - Digital pin নিয়ন্ত্রণ
✅ Conditional logic (if-else)
✅ LED circuit design (current limiting)
✅ Serial debugging
```

### Digital vs Analog:

| বৈশিষ্ট্য | Digital | Analog |
|----------|---------|--------|
| **Values** | শুধু 2টি (HIGH/LOW) | অনেক (0-1023) |
| **Reading** | digitalRead() | analogRead() |
| **Pins** | D0-D13 | A0-A5 |
| **Use** | Switch, button, PIR | Temperature, light |
| **Example** | PIR sensor | TMP36 sensor |

### পরবর্তী Project Ideas:

1. **Security Alarm** - Buzzer + PIR + SMS notification
2. **Automatic Door** - Servo motor with PIR
3. **Visitor Counter** - Count people entering room
4. **Smart Bathroom Light** - Auto on/off lighting
5. **Motion Logger** - SD card data logging
6. **Multi-zone Security** - Multiple PIR sensors
7. **Battery-powered** - Sleep mode for portability

---

## ❓ প্রশ্নোত্তর

**প্রশ্ন ১: PIR কেন 60s warm-up লাগে?**
- উত্তর: Pyroelectric sensor পরিবেশের তাপ মাপে এবং calibrate হয়। এই সময় ambient IR level balance করে।

**প্রশ্ন ২: 220Ω resistor ছাড়া LED লাগালে কী হবে?**
- উত্তর: LED-এ 250mA current flow হবে এবং burn out হবে! Resistor অবশ্যই দরকার।

**প্রশ্ন ৩: PIR কি অন্ধকারে কাজ করে?**
- উত্তর: হ্যাঁ! PIR দৃশ্যমান আলো নয়, infrared radiation (তাপ) সনাক্ত করে। দিন-রাত সমান কাজ করে।

**প্রশ্ন ৪: Repeatable vs Non-repeatable mode কোনটি ভালো?**
- উত্তর: 
  - **Repeatable (H)**: Automatic lighting, continuous monitoring
  - **Non-repeatable (L)**: Visitor counter, single-event detection

**প্রশ্ন ৫: কেন স্থির মানুষ detect করে না?**
- উত্তর: PIR শুধু তাপের **পরিবর্তন** সনাক্ত করে। স্থির মানুষ = কোনো IR পরিবর্তন নেই।

---

## 👨‍🎓 লেখক

**মো. আখিনুর ইসলাম**  
📚 Energy Science and Engineering (ESE)  
🏫 Khulna University of Engineering & Technology (KUET)

---

## 📄 License

MIT License - Free to use and modify!

---

### ✨ সফলতার Tips:

1. **60s warm-up দিন** - PIR calibration-এর জন্য অত্যাবশ্যক
2. **220Ω resistor ভুলবেন না** - LED protection
3. **Settings adjust করুন** - আপনার need অনুযায়ী
4. **Serial Monitor ব্যবহার করুন** - Debugging-এর জন্য
5. **Stable mounting** - PIR নড়াচড়া করলে false detection

**শুভকামনা! নিরাপত্তা ব্যবস্থা তৈরি করুন! 🚶🔒🎉**
