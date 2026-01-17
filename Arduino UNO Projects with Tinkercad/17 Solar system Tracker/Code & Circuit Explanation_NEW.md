# ☀️ সৌর শক্তি ট্র্যাকিং সিস্টেম - Dual-Axis

![Arduino](https://img.shields.io/badge/Arduino-UNO-00979D?style=for-the-badge&logo=arduino)
![Servo](https://img.shields.io/badge/Servo-২টি-orange?style=for-the-badge)
![LDR](https://img.shields.io/badge/Sensors-৪টি%20LDR-green?style=for-the-badge)
![বাংলা](https://img.shields.io/badge/ভাষা-বাংলা-red?style=for-the-badge)

---

## 📚 সূচিপত্র
- [প্রজেক্ট পরিচিতি](#-প্রজেক্ট-পরিচিতি)
- [যা যা লাগবে](#-যা-যা-লাগবে)
- [LDR সেন্সর কী](#-ldr-সেন্সর-কী)
- [Dual-Axis Tracking কী](#-dual-axis-tracking-কী)
- [সার্কিট সংযোগ](#-সার্কিট-সংযোগ)
- [পিন ম্যাপিং](#-পিন-ম্যাপিং)
- [কাজের নিয়ম](#-কাজের-নিয়ম)
- [কোড ব্যাখ্যা](#-কোড-ব্যাখ্যা)
- [সমস্যা সমাধান](#-সমস্যা-সমাধান)
- [নিজে চেষ্টা করো](#-নিজে-চেষ্টা-করো)

---

## 🎯 প্রজেক্ট পরিচিতি

এই প্রজেক্টে আমরা **Arduino UNO**, **৪টা LDR sensor**, এবং **২টা servo motor** ব্যবহার করে একটি **automatic solar tracking system** বানাবো। এই সিস্টেম চারদিক থেকে আলোর তীব্রতা মেপে solar panel কে সূর্যের দিকে ঘুরিয়ে দেয় - যার ফলে **সারাদিন সর্বোচ্চ সৌর শক্তি** সংগ্রহ করা যায়!

### 🌟 কেন এই প্রজেক্ট বিশেষ?

```
✅ দুটো axis এ ঘোরে (horizontal + vertical)
✅ ৪টা LDR দিয়ে সূর্যের অবস্থান detect করে
✅ Real-time position adjustment (১° করে)
✅ Potentiometer দিয়ে range control করা যায়
✅ Smooth servo movement (কোনো jitter নেই)
✅ Fixed panel এর চেয়ে ৪০% বেশি energy capture
✅ পুরোপুরি renewable energy application
✅ Tinkercad simulation available
```

### ☀️ Energy Efficiency তুলনা:

```
স্থির Solar Panel:         ████████░░ (৮০% গড় দক্ষতা)
Single-Axis Tracker:       ██████████░ (৯০% দক্ষতা)
Dual-Axis Tracker:         ████████████ (৯৫-৯৮% দক্ষতা) ⭐
```

---

## 🧰 যা যা লাগবে

### প্রয়োজনীয় যন্ত্রাংশ:

| যন্ত্রাংশ | স্পেসিফিকেশন | সংখ্যা | কাজ |
|-----------|--------------|--------|------|
| **Arduino UNO** | ATmega328P, 16MHz | ১টি | মূল controller |
| **Servo Motor** | SG90 (9g) অথবা MG995 (metal gear) | ২টি | Horizontal + Vertical movement |
| **LDR** | GL5528, 5-10kΩ @ 10 lux | ৪টি | আলোর তীব্রতা মাপে |
| **Resistor** | 10kΩ, 1/4W | ৪টি | LDR এর জন্য voltage divider |
| **Potentiometer** | 10kΩ, linear taper | ২টি | Servo range control |
| **Breadboard** | Half-size (400 points) | ১টি | Prototyping |
| **Jumper Wires** | Male-to-Male, বিভিন্ন length | ২০+ | সংযোগের জন্য |
| **Power Supply** | 5V 2A adapter অথবা USB | ১টি | Power source |

### Optional যন্ত্রাংশ:

- **Capacitor** (100µF, 16V) - Servo power filtering
- **Diode** (1N4007) - Reverse polarity protection
- **Switch** (SPST) - Power on/off control
- **Solar Panel** (ছোট 5V) - আসল tracking demonstration
- **Mounting Frame** - Cardboard/3D printed structure
- **External Power** (6V battery pack) - আলাদা servo power

### মোট খরচ: প্রায় ১২০০-২০০০ টাকা

---

## 🔬 LDR সেন্সর কী?

### LDR এর পরিচয়:

**LDR (Light Dependent Resistor)** বা **photoresistor** হলো একটা passive sensor যার resistance আলোর তীব্রতার সাথে পরিবর্তিত হয়। বেশি আলো = কম resistance!

```
LDR এর বৈশিষ্ট্য:

অন্ধকারে Resistance:  1MΩ - 10MΩ (অনেক বেশি)
আলোতে Resistance:     100Ω - 1kΩ (কম)
Response Time:        ~10ms (rising), ~20ms (falling)
Spectral Peak:        ~540nm (সবুজ-হলুদ আলো)
Operating Voltage:    Max 150V
Power Rating:         100-200mW
```

### LDR কীভাবে কাজ করে:

```
Photoconductivity Effect:

অন্ধকারে:
  • কম charge carrier
  • বেশি resistance (MΩ range)
  • কম current flow
  • Arduino pin এ কম voltage

আলোতে:
  • বেশি photon absorbed
  • বেশি charge carrier তৈরি হয়
  • কম resistance (kΩ range)
  • বেশি current flow
  • Arduino pin এ বেশি voltage

আলো ↑ → Resistance ↓ → Voltage ↑ → analogRead() value ↑
```

### Voltage Divider Circuit:

```
LDR Voltage Divider Configuration:

        VCC (+5V)
           │
          LDR (R_ldr)
           │
           ├───→ Arduino Analog Pin এ (A0-A3)
           │
          10kΩ (R_fixed)
           │
          GND

Output Voltage:
  V_out = VCC × (R_fixed / (R_ldr + R_fixed))

উদাহরণ হিসাব:
  
  উজ্জ্বল আলো (R_ldr = 500Ω):
    V_out = 5V × (10k / (500 + 10k))
    V_out ≈ 4.76V
    analogRead() ≈ 976 (out of 1023)
  
  ম্লান আলো (R_ldr = 50kΩ):
    V_out = 5V × (10k / (50k + 10k))
    V_out ≈ 0.83V
    analogRead() ≈ 170
  
  অন্ধকার (R_ldr = 1MΩ):
    V_out = 5V × (10k / (1M + 10k))
    V_out ≈ 0.05V
    analogRead() ≈ 10
```

### LDR Response Curve:

```
Resistance vs আলোর তীব্রতা:

Resistance (Ω)
    1M │                 ●
       │                /
  100k │              ●
       │            /
   10k │          ●
       │        /
    1k │      ●
       │    /
   100 │  ●
       └─────────────────── আলোর তীব্রতা (lux)
         0  10  100 1k 10k

নোট: Logarithmic response (nonlinear!)
```

---

## 🔄 Dual-Axis Tracking কী?

### দুটো Degree of Freedom:

```
Dual-Axis Solar Tracking System:

১. HORIZONTAL AXIS (Azimuth - দিক):
   • ঘূর্ণন: 0° থেকে 180° (বাম থেকে ডান)
   • সূর্যের পূর্ব-থেকে-পশ্চিম গতি follow করে
   • Control করে: Servo Motor H (Pin 9)
   • Sensors: বাম LDR vs ডান LDR

        ┌─────┐
    0° ←│Panel│→ 180°
        └─────┘
         (উপর থেকে দেখলে)

২. VERTICAL AXIS (Elevation - উচ্চতা):
   • ঘূর্ণন: 0° থেকে 45° (নিচ থেকে উপর)
   • সূর্যের altitude পরিবর্তন follow করে
   • Control করে: Servo Motor V (Pin 10)
   • Sensors: উপরের LDR vs নিচের LDR

          45° ↑  ┌─────┐
                 │Panel│
           0° ←  └─────┘
         (পাশ থেকে দেখলে)
```

### ৪-Quadrant LDR Configuration:

```
LDR Physical Layout (panel এর পিছন থেকে দেখলে):

          সামনে (সূর্যের দিকে)
        ┌─────────────────┐
        │  TL         TR  │  TL = Top-Left (A0)
        │   ●         ●   │  TR = Top-Right (A1)
        │                 │
        │      PANEL      │
        │                 │
        │   ●         ●   │  BL = Bottom-Left (A2)
        │  BL         BR  │  BR = Bottom-Right (A3)
        └─────────────────┘
             পিছনে

আলো Detection Logic:
  • TL + TR > BL + BR → উপরে Tilt করো (elevation বাড়াও)
  • BL + BR > TL + TR → নিচে Tilt করো (elevation কমাও)
  • TL + BL > TR + BR → বামে Rotate করো (azimuth কমাও)
  • TR + BR > TL + BL → ডানে Rotate করো (azimuth বাড়াও)
```

### Tracking Axes ব্যাখ্যা:

```
HORIZONTAL SERVO (Azimuth):
  ┌─────────────────────────────────────┐
  │  0°        45°       90°      180°  │
  │  পূর্ব      দ.পূ.    দক্ষিণ    পশ্চিম │
  │   ↑        ↑         ↑         ↑    │
  └─────────────────────────────────────┘
  সূর্যোদয় (পূর্ব) থেকে সূর্যাস্ত (পশ্চিম) track করে

VERTICAL SERVO (Elevation):
  ┌─────────────────────────────────────┐
  │  0°           15°        30°    45° │
  │ দিগন্ত     সকাল      দুপুর   Max  │
  │   ↑           ↑          ↑      ↑   │
  └─────────────────────────────────────┘
  সারাদিন সূর্যের altitude track করে

Combined Movement:
  সকাল:    Horizontal = 0° (পূর্ব), Vertical = 15°
  দুপুর:    Horizontal = 90° (দক্ষিণ), Vertical = 45°
  সন্ধ্যা:   Horizontal = 180° (পশ্চিম), Vertical = 15°
```

---

## 🔌 সার্কিট সংযোগ

### সম্পূর্ণ সিস্টেম সার্কিট:

```
Dual-Axis Solar Tracker Circuit:

┌────────────────────────────────────────────────────────────────┐
│                                                                │
│  ┌─────────────────────────────────────────────────────────┐  │
│  │                    ARDUINO UNO                          │  │
│  │                                                         │  │
│  │  [A0] ←─── LDR Top-Left ────┤  VCC                     │  │
│  │              │              │                           │  │
│  │             10kΩ            │                           │  │
│  │              │              │                           │  │
│  │             GND             │                           │  │
│  │                             │                           │  │
│  │  [A1] ←─── LDR Top-Right ───┤                           │  │
│  │              │              │                           │  │
│  │             10kΩ            │                           │  │
│  │              │              │                           │  │
│  │             GND             │                           │  │
│  │                             │                           │  │
│  │  [A2] ←─── LDR Bottom-Left ─┤                           │  │
│  │              │              │                           │  │
│  │             10kΩ            │                           │  │
│  │              │              │                           │  │
│  │             GND             │                           │  │
│  │                             │                           │  │
│  │  [A3] ←─── LDR Bottom-Right ┤                           │  │
│  │              │              │                           │  │
│  │             10kΩ            │                           │  │
│  │              │              │                           │  │
│  │             GND             │                           │  │
│  │                             │                           │  │
│  │  [A4] ←─── Potentiometer H ─┤ (Horizontal range)        │  │
│  │              (wiper)        │                           │  │
│  │         VCC ──┤  ├── GND    │                           │  │
│  │                             │                           │  │
│  │  [A5] ←─── Potentiometer V ─┤ (Vertical range)          │  │
│  │              (wiper)        │                           │  │
│  │         VCC ──┤  ├── GND    │                           │  │
│  │                             │                           │  │
│  │  [D9] ───→ Servo H (Signal) │ Horizontal Servo         │  │
│  │            │                │                           │  │
│  │         VCC│  │GND          │                           │  │
│  │            ↓  ↓             │                           │  │
│  │        External 5V          │                           │  │
│  │                             │                           │  │
│  │ [D10] ───→ Servo V (Signal) │ Vertical Servo           │  │
│  │            │                │                           │  │
│  │         VCC│  │GND          │                           │  │
│  │            ↓  ↓             │                           │  │
│  │        External 5V          │                           │  │
│  │                             │                           │  │
│  │  [5V]  ────→ Power Rails    │                           │  │
│  │  [GND] ────→ Ground Rails   │                           │  │
│  └─────────────────────────────────────────────────────────┘  │
│                                                                │
│  External Power Supply (5V 2A):                                │
│    ┌─────────────┐                                            │
│    │   +5V  GND  │                                            │
│    └───┬─────┬───┘                                            │
│        │     │                                                │
│        │     └────→ Arduino GND + Servo GND (common)          │
│        └──────────→ Arduino VIN + Servo VCC                   │
│                                                                │
│  Optional: 100µF capacitor servo power rails এ                │
└────────────────────────────────────────────────────────────────┘

প্রতিটা LDR Configuration:
  VCC (+5V) → LDR → Analog Pin (A0-A3) → 10kΩ → GND

প্রতিটা Potentiometer Configuration:
  Pin 1: VCC (+5V)
  Pin 2: Wiper → Analog Pin (A4 বা A5)
  Pin 3: GND

প্রতিটা Servo Configuration:
  লাল/বাদামী: VCC (+5V) - External supply recommended
  কালো/বাদামী: GND - Arduino এর সাথে common ground
  কমলা/হলুদ: Signal - PWM pin (D9 বা D10)
```

---

## 📍 পিন ম্যাপিং

### সম্পূর্ণ Pin Mapping:

| Arduino Pin | Component | Type | কাজ |
|-------------|-----------|------|-----|
| **A0** | LDR Top-Left | Analog Input | আলো sensing (TL quadrant) |
| **A1** | LDR Top-Right | Analog Input | আলো sensing (TR quadrant) |
| **A2** | LDR Bottom-Left | Analog Input | আলো sensing (BL quadrant) |
| **A3** | LDR Bottom-Right | Analog Input | আলো sensing (BR quadrant) |
| **A4** | Potentiometer H | Analog Input | Horizontal range control (0-180°) |
| **A5** | Potentiometer V | Analog Input | Vertical range control (0-90°) |
| **D9** | Servo Motor H | PWM Output | Horizontal axis control |
| **D10** | Servo Motor V | PWM Output | Vertical axis control |
| **5V** | Power Rail | Power | LDRs, potentiometers |
| **GND** | Ground Rail | Ground | Common ground |

### Code-এ Pin Definition:

```cpp
Pin Definitions:

const int ldrTopLeft = A0;      // LDR sensor উপর-বাম
const int ldrTopRight = A1;     // LDR sensor উপর-ডান
const int ldrBottomLeft = A2;   // LDR sensor নিচ-বাম
const int ldrBottomRight = A3;  // LDR sensor নিচ-ডান
const int potH = A4;            // Potentiometer horizontal
const int potV = A5;            // Potentiometer vertical

Servo servoH;  // Pin 9 এ attached (horizontal)
Servo servoV;  // Pin 10 এ attached (vertical)
```

---

## ⚙️ কাজের নিয়ম

### সিস্টেম কীভাবে চলে:

```
┌────────────────────────────────────────────────┐
│     SOLAR TRACKING SYSTEM OPERATION            │
└────────────────────────────────────────────────┘
                    │
              Power ON
                    │
                    ▼
         ┌──────────────────┐
         │ System Setup     │
         │ • Pin initialize │
         │ • Servo attach   │
         │ • Initial pos:   │
         │   H=90°, V=45°   │
         └─────────┬────────┘
                   │
                   ▼
         ┌──────────────────┐
         │ ৪টা LDR পড়ো     │ ◄──────────────┐
         │ Values:          │                │
         │ • TL, TR         │                │
         │ • BL, BR         │                │
         └─────────┬────────┘                │
                   │                         │
                   ▼                         │
         ┌──────────────────┐                │
         │ Average হিসাব    │                │
         │ করো:             │                │
         │ • avgTop         │                │
         │ • avgBottom      │                │
         │ • avgLeft        │                │
         │ • avgRight       │                │
         └─────────┬────────┘                │
                   │                         │
                   ▼                         │
         ┌──────────────────┐                │
         │ উপর vs নিচ       │                │
         │ তুলনা করো        │                │
         └─────────┬────────┘                │
                   │                         │
         ┌─────────┴─────────┐               │
         │                   │               │
    উপর > নিচ           নিচ > উপর          │
         │                   │               │
         ▼                   ▼               │
  ┌──────────┐        ┌──────────┐          │
  │ উপরে     │        │ নিচে     │          │
  │ Tilt     │        │ Tilt     │          │
  │ V_angle++│        │V_angle-- │          │
  └──────────┘        └──────────┘          │
         │                   │               │
         └─────────┬─────────┘               │
                   │                         │
                   ▼                         │
         ┌──────────────────┐                │
         │ বাম vs ডান       │                │
         │ তুলনা করো        │                │
         └─────────┬────────┘                │
                   │                         │
         ┌─────────┴─────────┐               │
         │                   │               │
    বাম > ডান           ডান > বাম            │
         │                   │               │
         ▼                   ▼               │
  ┌──────────┐        ┌──────────┐          │
  │ বামে      │        │ ডানে      │          │
  │ Rotate   │        │ Rotate   │          │
  │H_angle-- │        │H_angle++ │          │
  └──────────┘        └──────────┘          │
         │                   │               │
         └─────────┬─────────┘               │
                   │                         │
                   ▼                         │
         ┌──────────────────┐                │
         │ Potentiometer    │                │
         │ পড়ো              │                │
         │ • H range limit  │                │
         │ • V range limit  │                │
         └─────────┬────────┘                │
                   │                         │
                   ▼                         │
         ┌──────────────────┐                │
         │ Servo Position   │                │
         │ Update করো       │                │
         │ • servoH.write() │                │
         │ • servoV.write() │                │
         └─────────┬────────┘                │
                   │                         │
                   ▼                         │
         ┌──────────────────┐                │
         │ delay(300ms)     │                │
         │ stable reading   │                │
         │ এর জন্য wait     │                │
         └─────────┬────────┘                │
                   │                         │
                   └─────────────────────────┘
                    Loop Back
```

---

## 💻 কোড ব্যাখ্যা

### সম্পূর্ণ কোড:

```cpp
/*
 * Project 17: Dual-Axis Solar Tracking System
 * Arduino UNO + 4 LDR + 2 Servo Motors
 * সূর্যের অবস্থান track করে maximum solar efficiency
 */

#include <Servo.h>

// LDR sensor pins (4-quadrant configuration)
const int ldrTopLeft = A0;      // উপর-বাম
const int ldrTopRight = A1;     // উপর-ডান
const int ldrBottomLeft = A2;   // নিচ-বাম
const int ldrBottomRight = A3;  // নিচ-ডান

// Potentiometer pins (range control)
const int potH = A4;  // Horizontal servo limit
const int potV = A5;  // Vertical servo limit

// Servo objects
Servo servoH;  // Horizontal axis (azimuth)
Servo servoV;  // Vertical axis (elevation)

// Initial servo positions
int horizontalAngle = 90;   // মাঝখানে শুরু (0-180°)
int verticalAngle = 45;     // মাঝ-উচ্চতায় শুরু (0-90°)

// Tracking sensitivity
const int tolerance = 15;   // Movement trigger করার জন্য minimum difference

void setup() {
  // Servo attach করো PWM pins এ
  servoH.attach(9);   // Horizontal servo D9 এ
  servoV.attach(10);  // Vertical servo D10 এ
  
  // Initial position set করো
  servoH.write(horizontalAngle);
  servoV.write(verticalAngle);
  
  // Servo position এ পৌঁছানোর জন্য wait করো
  delay(1000);
  
  // Optional: Serial debugging
  Serial.begin(9600);
  Serial.println("Solar Tracker চালু হয়েছে");
  Serial.println("H: 90° | V: 45°");
}

void loop() {
  // ৪টা LDR sensor পড়ো
  int valTopLeft = analogRead(ldrTopLeft);
  int valTopRight = analogRead(ldrTopRight);
  int valBottomLeft = analogRead(ldrBottomLeft);
  int valBottomRight = analogRead(ldrBottomRight);
  
  // প্রতিটা axis এর জন্য average হিসাব করো
  int avgTop = (valTopLeft + valTopRight) / 2;
  int avgBottom = (valBottomLeft + valBottomRight) / 2;
  int avgLeft = (valTopLeft + valBottomLeft) / 2;
  int avgRight = (valTopRight + valBottomRight) / 2;
  
  // VERTICAL AXIS CONTROL (Elevation)
  // উপরের sensor বেশি আলো পাচ্ছে → উপরে tilt করো
  if (avgTop - avgBottom > tolerance) {
    if (verticalAngle < 90) {  // Max elevation limit
      verticalAngle++;
    }
  }
  // নিচের sensor বেশি আলো পাচ্ছে → নিচে tilt করো
  else if (avgBottom - avgTop > tolerance) {
    if (verticalAngle > 0) {  // Min elevation limit
      verticalAngle--;
    }
  }
  
  // HORIZONTAL AXIS CONTROL (Azimuth)
  // বাম sensor বেশি আলো পাচ্ছে → বামে rotate করো
  if (avgLeft - avgRight > tolerance) {
    if (horizontalAngle > 0) {  // Min azimuth limit
      horizontalAngle--;
    }
  }
  // ডান sensor বেশি আলো পাচ্ছে → ডানে rotate করো
  else if (avgRight - avgLeft > tolerance) {
    if (horizontalAngle < 180) {  // Max azimuth limit
      horizontalAngle++;
    }
  }
  
  // Dynamic range control এর জন্য potentiometer পড়ো
  int potHVal = analogRead(potH);
  int potVVal = analogRead(potV);
  
  // Potentiometer value কে servo range এ map করো
  int maxHorizontal = map(potHVal, 0, 1023, 0, 180);
  int maxVertical = map(potVVal, 0, 1023, 0, 90);
  
  // Potentiometer limit এর মধ্যে angle রাখো
  horizontalAngle = constrain(horizontalAngle, 0, maxHorizontal);
  verticalAngle = constrain(verticalAngle, 0, maxVertical);
  
  // Servo position update করো
  servoH.write(horizontalAngle);
  servoV.write(verticalAngle);
  
  // Debug output (optional)
  Serial.print("TL:");
  Serial.print(valTopLeft);
  Serial.print(" TR:");
  Serial.print(valTopRight);
  Serial.print(" BL:");
  Serial.print(valBottomLeft);
  Serial.print(" BR:");
  Serial.print(valBottomRight);
  Serial.print(" | H:");
  Serial.print(horizontalAngle);
  Serial.print("° V:");
  Serial.print(verticalAngle);
  Serial.println("°");
  
  // পরের reading এর আগে wait করো (smooth tracking)
  delay(300);
}
```

---

### ধাপে ধাপে কোড বিশ্লেষণ:

#### **১. Library এবং Pin Definitions:**

```cpp
#include <Servo.h>

const int ldrTopLeft = A0;
const int ldrTopRight = A1;
const int ldrBottomLeft = A2;
const int ldrBottomRight = A3;
const int potH = A4;
const int potV = A5;
```

**ব্যাখ্যা:**
- `#include <Servo.h>`: Arduino Servo library PWM control এর জন্য
- LDR pins (A0-A3): Analog inputs আলো sensing এর জন্য
- Pot pins (A4-A5): Analog inputs range control এর জন্য

#### **২. Servo Objects এবং Variables:**

```cpp
Servo servoH;  // Horizontal axis
Servo servoV;  // Vertical axis

int horizontalAngle = 90;   // মাঝখানে শুরু
int verticalAngle = 45;     // মাঝ-উচ্চতায় শুরু
const int tolerance = 15;   // Sensitivity threshold
```

**Variables:**
- `servoH`, `servoV`: Servo control objects
- `horizontalAngle`: বর্তমান azimuth (0-180°)
- `verticalAngle`: বর্তমান elevation (0-90°)
- `tolerance`: Movement trigger করার জন্য minimum light difference

**Tolerance কেন দরকার?**
```
Tolerance ছাড়া:
  • Servo ক্রমাগত jitter করবে
  • অস্থির positioning
  • বেশি power consumption
  
Tolerance (15) সহ:
  • শুধু difference > 15 হলে move করবে
  • Smooth, stable tracking
  • Efficient operation
```

#### **৩. Setup Function:**

```cpp
void setup() {
  servoH.attach(9);
  servoV.attach(10);
  
  servoH.write(horizontalAngle);
  servoV.write(verticalAngle);
  
  delay(1000);
  Serial.begin(9600);
}
```

**Initialization:**
1. PWM pins (9, 10) এ servo attach করো
2. Initial position set করো (90°, 45°)
3. Servo position এ পৌঁছানোর জন্য ১ second wait করো
4. Serial communication শুরু করো (debugging)

#### **৪. LDR Sensor Reading:**

```cpp
int valTopLeft = analogRead(ldrTopLeft);
int valTopRight = analogRead(ldrTopRight);
int valBottomLeft = analogRead(ldrBottomLeft);
int valBottomRight = analogRead(ldrBottomRight);
```

**ADC Conversion:**
```
analogRead() returns 0-1023 (10-bit ADC)
  • 0 = 0V (অন্ধকার)
  • 1023 = 5V (উজ্জ্বল আলো)
  • Resolution: 5V / 1024 = 4.88mV per step

উদাহরণ readings:
  উজ্জ্বল সূর্যের আলো:  900-1000
  ঘরের আলো:             300-500
  ম্লান আলো:            100-200
  অন্ধকার:              0-50
```

#### **৫. Average হিসাব:**

```cpp
int avgTop = (valTopLeft + valTopRight) / 2;
int avgBottom = (valBottomLeft + valBottomRight) / 2;
int avgLeft = (valTopLeft + valBottomLeft) / 2;
int avgRight = (valTopRight + valBottomRight) / 2;
```

**কেন averaging?**
```
Noise কমায় এবং accuracy বাড়ায়!

উদাহরণ:
  TL = 850, TR = 870
  avgTop = (850 + 870) / 2 = 860
  
  BL = 600, BR = 650
  avgBottom = (600 + 650) / 2 = 625
  
  Difference = 860 - 625 = 235 > tolerance (15)
  → Action: উপরে Tilt করো! ✅
```

#### **৬. Vertical Axis Control:**

```cpp
if (avgTop - avgBottom > tolerance) {
  if (verticalAngle < 90) {
    verticalAngle++;
  }
}
else if (avgBottom - avgTop > tolerance) {
  if (verticalAngle > 0) {
    verticalAngle--;
  }
}
```

**Logic:**
```
উপর নিচের চেয়ে উজ্জ্বল:
  avgTop > avgBottom + tolerance
  → সূর্য উপরে আছে
  → Elevation বাড়াও (উপরে tilt)
  → verticalAngle++ (max 90°)

নিচ উপরের চেয়ে উজ্জ্বল:
  avgBottom > avgTop + tolerance
  → সূর্য নিচে আছে
  → Elevation কমাও (নিচে tilt)
  → verticalAngle-- (min 0°)

Tolerance এর মধ্যে:
  |avgTop - avgBottom| ≤ tolerance
  → Balanced আলো
  → কোনো movement নেই (stable)
```

#### **৭. Horizontal Axis Control:**

```cpp
if (avgLeft - avgRight > tolerance) {
  if (horizontalAngle > 0) {
    horizontalAngle--;
  }
}
else if (avgRight - avgLeft > tolerance) {
  if (horizontalAngle < 180) {
    horizontalAngle++;
  }
}
```

**Logic:**
```
বাম ডানের চেয়ে উজ্জ্বল:
  avgLeft > avgRight + tolerance
  → সূর্য বামে আছে
  → বামে Rotate করো (counter-clockwise)
  → horizontalAngle-- (min 0°)

ডান বামের চেয়ে উজ্জ্বল:
  avgRight > avgLeft + tolerance
  → সূর্য ডানে আছে
  → ডানে Rotate করো (clockwise)
  → horizontalAngle++ (max 180°)

Tolerance এর মধ্যে:
  |avgLeft - avgRight| ≤ tolerance
  → Balanced আলো
  → কোনো movement নেই (stable)
```

#### **৮. Potentiometer Range Control:**

```cpp
int potHVal = analogRead(potH);
int potVVal = analogRead(potV);

int maxHorizontal = map(potHVal, 0, 1023, 0, 180);
int maxVertical = map(potVVal, 0, 1023, 0, 90);

horizontalAngle = constrain(horizontalAngle, 0, maxHorizontal);
verticalAngle = constrain(verticalAngle, 0, maxVertical);
```

**Dynamic Range Limiting:**
```
map() function:
  map(value, fromLow, fromHigh, toLow, toHigh)
  
  উদাহরণ (Horizontal):
    Pot 0% এ:     map(0, 0, 1023, 0, 180) = 0°
    Pot 50% এ:    map(512, 0, 1023, 0, 180) = 90°
    Pot 100% এ:   map(1023, 0, 1023, 0, 180) = 180°

constrain() function:
  constrain(value, min, max)
  
  উদাহরণ:
    horizontalAngle = 150°
    maxHorizontal = 120° (pot setting)
    Result: constrain(150, 0, 120) = 120° ✅
    
    (User-defined range এর মধ্যে servo limit করে)

ব্যবহার:
  • Mounting structure এর সাথে collision আটকাতে
  • নির্দিষ্ট sky region এ tracking limit করতে
  • Restricted movement দিয়ে test করতে
```

#### **৯. Servo Update:**

```cpp
servoH.write(horizontalAngle);
servoV.write(verticalAngle);
```

**Servo Control:**
```
servoH.write(90):
  • Horizontal servo তে PWM signal পাঠায়
  • Pulse width: 1500µs (center position)
  • Servo 90° তে rotate করে
  
servoV.write(45):
  • Vertical servo তে PWM signal পাঠায়
  • Pulse width: 1250µs (mid-range)
  • Servo 45° তে rotate করে

PWM Timing:
  0° = 1000µs (1ms pulse)
  90° = 1500µs (1.5ms pulse)
  180° = 2000µs (2ms pulse)
  PWM frequency: 50Hz (20ms period)
```

#### **১০. Delay এবং Loop:**

```cpp
delay(300);
```

**কেন 300ms delay?**
```
খুব দ্রুত (< 100ms):
  • Servo jitter করবে
  • Noisy reading
  • বেশি power consumption
  • Unstable tracking

খুব ধীর (> 1000ms):
  • Slow response
  • সূর্য এগিয়ে যাবে
  • Tracking lag করবে

Optimal (300ms):
  • Smooth movement ✅
  • Stable reading ✅
  • Good response time ✅
  • Low jitter ✅
```

---

## 🐛 সমস্যা সমাধান

### সাধারণ সমস্যা:

| সমস্যা | সম্ভাব্য কারণ | সমাধান |
|--------|--------------|---------|
| **Servo ক্রমাগত jitter করছে** | Tolerance খুব কম | Tolerance 20-30 এ বাড়াও |
| | Noisy LDR reading | প্রতিটা LDR এ 0.1µF capacitor যোগ করো |
| | যথেষ্ট power নেই | External 5V 2A power supply ব্যবহার করো |
| **Panel move করছে না** | Servo attach হয়নি | `servoH.attach(9)` setup এ আছে কিনা check করো |
| | Servo power নেই | Servo VCC সংযোগ verify করো |
| | LDR reading একই | LDR wiring check করো, individually test করো |
| **ভুল দিকে move করছে** | LDR position ভুল | TL=A0, TR=A1, BL=A2, BR=A3 verify করো |
| | Servo reversed | Increment/decrement logic swap করো |
| **Erratic movement** | LDR এ shadow পড়ছে | Tube ব্যবহার করো light direction focus করতে |
| | Reflection | LDR panel এর সাথে flush mount করো |
| **Limit এ থেমে যায়** | Mechanical obstruction | Servo range check করো, soft stop যোগ করো |
| | Software limit | `constrain()` value adjust করো |
| **Slow response** | Delay খুব বেশি | Delay 300ms থেকে 200ms কমাও |
| | Tolerance খুব বেশি | Tolerance 10-15 এ কমাও |
| **এক axis কাজ করছে না** | Servo সংযোগ | D9/D10 wiring check করো |
| | LDR pair failure | LDR reading individually test করো |

### Diagnostic Code:

```cpp
// সম্পূর্ণ diagnostic
void runDiagnostics() {
  Serial.println("=== সিস্টেম DIAGNOSTICS ===");
  
  // LDR test
  Serial.println("\n--- LDR Readings ---");
  Serial.print("TL (A0): "); Serial.println(analogRead(A0));
  Serial.print("TR (A1): "); Serial.println(analogRead(A1));
  Serial.print("BL (A2): "); Serial.println(analogRead(A2));
  Serial.print("BR (A3): "); Serial.println(analogRead(A3));
  
  // Potentiometer test
  Serial.println("\n--- Potentiometer Readings ---");
  Serial.print("Pot H (A4): "); Serial.println(analogRead(A4));
  Serial.print("Pot V (A5): "); Serial.println(analogRead(A5));
  
  // Servo test
  Serial.println("\n--- Servo Test ---");
  Serial.println("0° তে যাচ্ছে...");
  servoH.write(0);
  servoV.write(0);
  delay(1000);
  
  Serial.println("90° তে যাচ্ছে...");
  servoH.write(90);
  servoV.write(45);
  delay(1000);
  
  Serial.println("Max এ যাচ্ছে...");
  servoH.write(180);
  servoV.write(90);
  delay(1000);
  
  Serial.println("\n=== DIAGNOSTICS সম্পূর্ণ ===");
}

// setup() এ call করো:
runDiagnostics();
```

---

## 📚 নিজে চেষ্টা করো

### প্রজেক্ট সম্পূর্ণ করার ধাপ:

#### ধাপ ১: Mechanical Assembly

```
✓ Base plate এ servo mount করো
✓ Horizontal servo base এ attach করো
✓ Vertical servo horizontal arm এ attach করো
✓ Solar panel vertical arm এ mount করো
✓ Smooth rotation ensure করো (কোনো binding নেই)
```

#### ধাপ ২: LDR Placement

```
  ┌─────────────────┐
  │  ●           ●  │  ← Panel corner এ LDR mount করো
  │                 │     (panel এর সাথে same direction এ)
  │     PANEL       │
  │                 │     Small tube/straw ব্যবহার করো
  │  ●           ●  │     light direction focus করতে
  └─────────────────┘
```

#### ধাপ ৩: Wiring Check

```
✓ সব LDR সঠিক pin এ connected
✓ Servo signal wire D9, D10 এ
✓ Common ground established
✓ External power connected (যদি ব্যবহার করো)
```

#### ধাপ ৪: Initial Position

```
• H_angle = 90° set করো (center)
• V_angle = 45° set করো (mid-elevation)
• Panel সামনে face করছে কিনা verify করো
```

#### ধাপ ৫: Calibration

```
১. LDR reading test করো:
   - Uniform light এ সব similar value
   - Light vary করলে সবগুলো together change করে
   - কোনোটা 0 বা 1023 এ stuck নেই

২. Servo range test করো:
   - Full range এ smooth movement
   - কোনো mechanical binding নেই
   - প্রতিটা position এ stable holding

৩. Tolerance adjust করো:
   - Indoor: 5 (high sensitivity)
   - Default: 15 (balanced)
   - Outdoor: 30 (low sensitivity)
```

#### ধাপ ৬: Final Testing

```
১. সকালে test করো:
   - Panel পূর্ব দিকে যায় কিনা

২. দুপুরে test করো:
   - Panel দক্ষিণ দিকে থাকে কিনা

৩. সন্ধ্যায় test করো:
   - Panel পশ্চিম দিকে যায় কিনা

৪. Potentiometer test করো:
   - Range limit কাজ করছে কিনা
```

---

## 🚀 প্রয়োগক্ষেত্র (Applications)

### ১. Solar Panel Efficiency বাড়ানো

```
বাসার ছাদে solar panel:
  • Fixed panel: ~80% দক্ষতা
  • Single-axis tracker: ~90% দক্ষতা
  • Dual-axis tracker: ~95-98% দক্ষতা
  
  বার্ষিক energy gain: 30-40% বৃদ্ধি!
  ROI: 2-3 বছর (commercial system)
```

### ২. Solar Water Heater

```
Solar thermal collector এর সাথে:
  • সারাদিন সূর্য track করে
  • Maximum heat absorption
  • Heating time 40% কমে
  • Automatic seasonal adjustment
```

### ৩. Solar Oven/Cooker

```
Parabolic solar cooker tracking:
  • সূর্যের উপর focus maintain করে
  • Consistent cooking temperature
  • Manual adjustment লাগে না
  • Efficient outdoor cooking
```

### ৪. Educational Project

```
STEM শেখার জন্য:
  • Renewable energy ধারণা
  • Sensor integration
  • Control system
  • Real-world problem solving
  • Solar angle এর physics
```

---

## ✨ শিক্ষা (Learning Outcomes)

### যা শিখবে:

```
✅ Analog sensor interfacing (LDR voltage divider)
✅ Servo motor control (PWM signal)
✅ Multi-sensor data fusion (averaging, comparison)
✅ Control algorithm (threshold-based decision)
✅ Real-time feedback system
✅ Dynamic range limiting (potentiometer control)
✅ Mechanical system integration
✅ Renewable energy principle
✅ Serial debugging technique
✅ System calibration এবং optimization
```

### Advanced Concepts:

- **Feedback Control**: Closed-loop system optimal angle maintain করে
- **Dead Band**: Tolerance oscillation আটকায় (hysteresis)
- **Multi-Axis Coordination**: Independent কিন্তু synchronized movement
- **Sensor Fusion**: Multiple sensor combine করে better accuracy
- **Energy Optimization**: Positioning দিয়ে power output maximize করা

---

## 🎉 Success Tips (সফলতার টিপস)

```
১. সহজ থেকে শুরু করো
   → প্রথমে প্রতিটা LDR individually test করো
   → Servo movement আলাদা verify করো
   → তারপর সব একসাথে combine করো

২. Mechanical Stability
   → Secure mounting অত্যন্ত গুরুত্বপূর্ণ
   → কোনো loose connection না
   → Smooth servo rotation

৩. Light Focusing
   → LDR এ tube/straw ব্যবহার করো
   → Ambient light interference আটকায়
   → Better directional sensing

৪. Power Management
   → Servo এর জন্য external 5V supply
   → Servo power এ capacitor
   → Arduino USB power avoid করো

৫. Calibration is Key
   → Environment অনুযায়ী tolerance adjust করো
   → Actual sunlight এ test করো
   → Range fine-tune করো

৬. Serial দিয়ে Debug করো
   → LDR value monitor করো
   → Servo angle track করো
   → Issue quickly identify করো

৭. Weatherproofing (বাইরে ব্যবহারের জন্য)
   → Electronics বৃষ্টি থেকে protect করো
   → UV-resistant enclosure
   → Sealed cable entry
```

**শুভকামনা তোমার solar tracking system বানানোর জন্য! ☀️🌍⚡**

---

## 👨‍💻 Author

**Md. Akhinoor Islam**  
📚 Energy Science and Engineering (ESE)  
🏫 Khulna University of Engineering & Technology (KUET)

---

## 📄 License

MIT License - Free to use, modify, and distribute!

---

**Happy Making! ☀️🔥**
