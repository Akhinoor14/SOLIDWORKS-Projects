# 🔢 ডিজিটাল ভোল্টমিটার - ATtiny85 ও 3-Digit 7-Segment Display

## 🌟 প্রজেক্ট পরিচিতি

এই প্রজেক্টে আমরা **ATtiny85** মাইক্রোকন্ট্রোলার দিয়ে একটি ডিজিটাল ভোল্টমিটার তৈরি করব যা **3-digit 7-segment display**-তে voltage প্রদর্শন করবে। এটি একটি advanced প্রজেক্ট যেখানে আমরা **74HC595 shift register**, **timer interrupt**, **display multiplexing**, এবং **ADC** ব্যবহার শিখব।

### 📚 এই প্রজেক্ট থেকে শিখব:

```
✅ ATtiny85 কী এবং কীভাবে প্রোগ্রাম করতে হয়
✅ 74HC595 shift register দিয়ে pin সংখ্যা কমানো
✅ 7-segment display কীভাবে কাজ করে
✅ Display multiplexing কী এবং কেন প্রয়োজন
✅ Timer interrupt দিয়ে background task চালানো
✅ ATtiny85-এ ADC configure করা
✅ Lookup table ব্যবহার করে digit display করা
✅ Current limiting এবং power management
✅ Register-level programming (bare-metal AVR)
✅ USB overcurrent থেকে সার্কিট রক্ষা করা
```

---

## 🛠️ প্রয়োজনীয় যন্ত্রপাতি

| যন্ত্র | সংখ্যা | বিস্তারিত | কাজ |
|-------|--------|----------|------|
| ATtiny85 | ১টি | 8-pin মাইক্রোকন্ট্রোলার | Main controller |
| 74HC595 Shift Register | ১টি | 16-pin IC | Segment driver |
| 3-Digit 7-Segment Display | ১টি | Common cathode, লাল LED | ভোল্টেজ প্রদর্শন |
| 10kΩ Potentiometer | ১টি | Linear taper | Variable voltage |
| 100Ω রেজিস্ট্যান্স | ৮টি | ¼W, ±5% | Segment current limit |
| 2kΩ রেজিস্ট্যান্স | ১টি | ¼W | Digit 1 current limit |
| 750Ω রেজিস্ট্যান্স | ১টি | ¼W | Digit 2 current limit |
| USB to Serial Adapter | ১টি | Programming জন্য | ATtiny85 program করা |
| 5V Power Supply | ১টি | Regulated, 500mA | External power |
| Breadboard | ১টি | 830 tie-points | সার্কিট তৈরি |
| Jumper Wires | ~৩০টি | Male-to-Male | সংযোগ |

### 💰 আনুমানিক খরচ: ৳৬০০-৮০০ টাকা

---

## 🔬 ATtiny85 কী?

### Pin Configuration:

```
ATtiny85 DIP-8 Package (উপর থেকে দেখলে):
        ┌─────┬─────┐
  RESET │1 ●  8│ VCC (5V)
     A3 │2    7│ A1 (PB2) - ADC Input
     A2 │3    6│ PB1 - Clock
    GND │4    5│ PB0 - Data
        └───────┘

আমাদের ব্যবহার:
  Pin 5 (PB0) = 74HC595-এ data পাঠাবে
  Pin 6 (PB1) = Clock signal
  Pin 7 (PB2) = Latch signal + ADC input (A1)
  Pin 2 (PB3) = Digit 1 enable
  Pin 3 (PB4) = Digit 2 enable
```

### বৈশিষ্ট্য:

```
ATtiny85 Specifications:
┌─────────────────────────────────────┐
│ Core: AVR 8-bit RISC                │
│ Flash Memory: 8 KB (program)        │
│ SRAM: 512 bytes (variables)         │
│ EEPROM: 512 bytes (data storage)    │
│ GPIO Pins: 6 (5টি usable)          │
│ ADC: 10-bit, 4 channels             │
│ Timers: 2টি (8-bit)                 │
│ Clock: 8 MHz internal               │
│ Operating Voltage: 2.7V - 5.5V      │
│ Current: ~15mA active, <1µA sleep   │
└─────────────────────────────────────┘
```

### কেন ATtiny85?

```
Arduino UNO vs ATtiny85:
┌────────────────┬──────────┬───────────┐
│ বৈশিষ্ট্য      │ UNO      │ ATtiny85  │
├────────────────┼──────────┼───────────┤
│ Pins           │ 28       │ 8         │
│ Size           │ Large    │ Very small│
│ Cost           │ ৳400-500 │ ৳50-80    │
│ Power          │ ~50mA    │ ~15mA     │
│ Flash          │ 32KB     │ 8KB       │
│ GPIO           │ 20       │ 6         │
│ ADC            │ ✓        │ ✓         │
│ Timers         │ ✓        │ ✓         │
└────────────────┴──────────┴───────────┘

ATtiny85 সুবিধা:
  ✅ খুব ছোট (compact projects)
  ✅ কম দাম
  ✅ কম বিদ্যুৎ খরচ (battery projects)
  ✅ এই প্রজেক্টের জন্য যথেষ্ট
```

---

## 🔀 74HC595 Shift Register কী?

### মূল ধারণা:

**Shift Register** হল একটি IC যা **serial data** (এক bit একবারে) নিয়ে **parallel output** (8 bit একসাথে) দেয়। এতে অনেক কম pin ব্যবহার করে অনেক বেশি output control করা যায়!

### কীভাবে কাজ করে:

```
3-Pin Control (ATtiny85 থেকে):
┌──────────────────────────────────────┐
│ DS (Data Serial):                    │
│   • এক bit data পাঠাই (0 or 1)      │
│                                      │
│ SH_CP (Shift Clock):                 │
│   • Clock pulse দিয়ে data shift করি │
│   • প্রতি pulse-এ এক bit ঢুকে যায়   │
│                                      │
│ ST_CP (Latch Clock):                 │
│   • Output pins-এ data পাঠাই        │
│   • এক pulse-এ 8টি output update    │
└──────────────────────────────────────┘

Process (ধাপে ধাপে):
  1. DS pin-এ bit পাঠাই (HIGH/LOW)
  2. SH_CP pulse দিই (bit shift হয়)
  3. ৮ বার repeat করি (8 bits)
  4. ST_CP pulse দিই (output update)
  5. Q0-Q7 pins একসাথে update হয়

সুবিধা:
  ✅ 8টি output মাত্র 3টি pin দিয়ে
  ✅ আরো IC লাগিয়ে 16, 24, 32... output করা যায়
  ✅ প্রতিটি output 35mA পর্যন্ত দিতে পারে
```

---

## 🔢 7-Segment Display কীভাবে কাজ করে

### Segment Layout:

```
7-Segment Display Structure:
     A
    ───
   │   │
  F│ G │B
    ───
   │   │
  E│   │C
    ───
     D   ●DP

Segments:
  A = উপরের horizontal
  B = ডান উপরের vertical
  C = ডান নিচের vertical
  D = নিচের horizontal
  E = বাম নিচের vertical
  F = বাম উপরের vertical
  G = মাঝের horizontal
  DP = Decimal Point (দশমিক বিন্দু)
```

### Digit Pattern (Binary Encoding):

```
74HC595 Output Mapping:
  Bit:  7   6  5  4  3  2  1  0
       DP  G  F  E  D  C  B  A

Digit Patterns (DIGH[] array):
  '0': 0x3F = 0011 1111 = A,B,C,D,E,F জ্বলে
  '1': 0x06 = 0000 0110 = শুধু B,C জ্বলে
  '2': 0x5B = 0101 1011 = A,B,G,E,D জ্বলে
  '3': 0x4F = 0100 1111 = A,B,G,C,D জ্বলে
  '4': 0x66 = 0110 0110 = F,G,B,C জ্বলে
  '5': 0x6D = 0110 1101 = A,F,G,C,D জ্বলে
  '6': 0x7D = 0111 1101 = A,F,G,E,D,C জ্বলে
  '7': 0x07 = 0000 0111 = A,B,C জ্বলে
  '8': 0x7F = 0111 1111 = সব segment জ্বলে
  '9': 0x6F = 0110 1111 = A,B,C,D,F,G জ্বলে
  '-': 0x40 = 0100 0000 = শুধু G (error indicator)

Visual Examples:
  Digit '0':        Digit '1':        Digit '8':
     ───               │                 ───
    │   │              │                │   │
    │   │              │                │   │
                                         ───
    │   │              │                │   │
    │   │              │                │   │
     ───                                 ───
```

---

## 🎬 Display Multiplexing কী?

### মূল সমস্যা:

```
3-Digit Display এর সমস্যা:
  • প্রতিটি digit-এ 8টি segment (A-G + DP)
  • 3টি digit = 3 × 8 = 24টি pin লাগত!
  • 74HC595 দিয়ে 8টি segment control করি
  • কিন্তু 3টি digit আলাদা আলাদা কীভাবে দেখাব?

Multiplexing সমাধান:
  • 8টি segment সব digit-এর জন্য common
  • একসময় একটি digit enable করব
  • খুব দ্রুত পরিবর্তন করব (70Hz+)
  • চোখ continuous মনে করবে!
```

### কীভাবে কাজ করে:

```
Time-Division Multiplexing:
┌────────────────────────────────────────┐
│ Time Slot 1 (5ms):                     │
│   • সব digit off করি                  │
│   • DISP[2] থেকে pattern পাঠাই (4)    │
│   • Digit 1 enable করি                │
│   • Display দেখায়: "4__"              │
│                                        │
│ Time Slot 2 (5ms):                     │
│   • সব digit off করি                  │
│   • DISP[1] থেকে pattern পাঠাই (2)    │
│   • Digit 2 enable করি                │
│   • Display দেখায়: "_2_"              │
│                                        │
│ Time Slot 3 (5ms):                     │
│   • সব digit off করি                  │
│   • DISP[0] থেকে pattern পাঠাই (3)    │
│   • Digit 3 enable করি                │
│   • Display দেখায়: "__3"              │
│                                        │
│ পুনরাবৃত্তি (15ms cycle = 66.7Hz)     │
│ চোখে দেখবে: "4.23V" continuously!     │
└────────────────────────────────────────┘

Duty Cycle:
  • প্রতিটি digit 33% সময় জ্বলে (5ms out of 15ms)
  • কিন্তু চোখ continuous ভাবে
  • Refresh rate 66.7Hz (flicker-free)

Persistence of Vision:
  • মানুষের চোখ >50Hz পর্যন্ত merge করে
  • Cinema: 24fps (frames per second)
  • আমাদের: 66.7fps → very smooth!
```

---

## 🔌 সার্কিট সংযোগ (Circuit Connections)

### ATtiny85 Pin Connections:

| ATtiny85 Pin | Pin # | কাজ | সংযুক্ত | তারের রং |
|--------------|-------|-----|---------|----------|
| PB0 | 5 | Serial Data | 74HC595 pin 14 | হলুদ |
| PB1 | 6 | Shift Clock | 74HC595 pin 11 | সবুজ |
| PB2 | 7 | Latch Clock | 74HC595 pin 12 | নীল |
| PB2/A1 | 7 | ADC Input | Pot মাঝখান | কমলা |
| PB3 | 2 | Digit 1 Enable | [2kΩ] → COM1 | সাদা |
| PB4 | 3 | Digit 2 Enable | [750Ω] → COM2 | ধূসর |
| VCC | 8 | Power | 5V | লাল |
| GND | 4 | Ground | GND | কালো |

### 74HC595 Shift Register:

| 74HC595 Pin | Pin # | কাজ | সংযুক্ত |
|-------------|-------|-----|---------|
| DS | 14 | Data input | ATtiny PB0 |
| SH_CP | 11 | Shift clock | ATtiny PB1 |
| ST_CP | 12 | Latch clock | ATtiny PB2 |
| Q0 | 15 | Output 0 | [100Ω] → Seg A |
| Q1 | 1 | Output 1 | [100Ω] → Seg B |
| Q2 | 2 | Output 2 | [100Ω] → Seg C |
| Q3 | 3 | Output 3 | [100Ω] → Seg D |
| Q4 | 4 | Output 4 | [100Ω] → Seg E |
| Q5 | 5 | Output 5 | [100Ω] → Seg F |
| Q6 | 6 | Output 6 | [100Ω] → Seg G |
| Q7 | 7 | Output 7 | [100Ω] → Seg DP |
| VCC | 16 | Power | 5V |
| GND | 8 | Ground | GND |
| OE | 13 | Output Enable | GND (always on) |
| SRCLR | 10 | Clear | 5V (never clear) |

### 7-Segment Display Common Pins:

| Digit | Common Pin | Resistor | সংযুক্ত |
|-------|------------|----------|---------|
| Digit 1 | COM1 | 2kΩ | ATtiny PB3 |
| Digit 2 | COM2 | 750Ω | ATtiny PB4 |
| Digit 3 | COM3 | Direct | GND |

---

## 💻 কোড ব্যাখ্যা

### Global Variables:

```cpp
#define NOP() asm ("nop")
```
**কাজ:**
- এক CPU cycle delay দেয়
- Timing control জন্য (shift register communication)

```cpp
long V = 0;
```
**কাজ:**
- Voltage store করে **centivolts**-এ
- Example: 423 = 4.23V

```cpp
const unsigned char DIGH[] = {
    0x3F,  // 0
    0x06,  // 1
    0x5B,  // 2
    // ... etc
    0x40   // - (error)
};
```
**কাজ:**
- **Lookup table** - digit pattern রাখে
- Index 0-9 = digit '0'-'9'
- Index 10 = dash '-' (error দেখাতে)

```cpp
unsigned char DISP[3] = {0, 0, 0};
```
**কাজ:**
- Display buffer - 3টি digit রাখে
- DISP[2] = শতক (ones place)
- DISP[1] = দশক (tenths place)
- DISP[0] = একক (hundredths place)
- Example: 4.23V → DISP = {4, 2, 3}

```cpp
boolean flag = 0;
unsigned char period = 0;
```
**কাজ:**
- `flag`: কখন ADC পড়তে হবে signal করে
- `period`: Timer interrupt counter

---

### Setup Function - GPIO Configure:

```cpp
DDRB = 0x1F;  // 0001 1111
```
**Data Direction Register:**
```
Bit অনুযায়ী:
  Bit 7 6 5 4 3 2 1 0
  Val 0 0 0 1 1 1 1 1
          │ │ │ │ │ └─ PB0: OUTPUT
          │ │ │ │ └─── PB1: OUTPUT
          │ │ │ └───── PB2: OUTPUT
          │ │ └─────── PB3: OUTPUT
          │ └───────── PB4: OUTPUT
          └─────────── PB5: INPUT (ADC)

0x1F = PB0-PB4 কে OUTPUT বানায়
```

```cpp
PORTB = 0x1C;  // 0001 1100
```
**Initial Pin States:**
```
Bit 7 6 5 4 3 2 1 0
Val 0 0 0 1 1 1 0 0
          │ │ │ └─ PB0: LOW (data idle)
          │ │ └─── PB1: LOW (clock idle)
          │ └───── PB2: HIGH (digit off)
          └─────── PB3,PB4: HIGH (digits off)

Common cathode display:
  HIGH = digit off
  LOW = digit on
```

---

### Setup Function - Timer0 Configure:

```cpp
TCCR0A = (1 << WGM01);
```
**Timer Control Register A:**
- `WGM01` bit set করলে **CTC mode** চালু হয়
- CTC = Clear Timer on Compare Match
- Timer TCNT0 == OCR0A হলে reset হয়

```cpp
TCCR0B = (1 << CS02);
```
**Timer Control Register B:**
- `CS02` bit set করলে **prescaler = 256**
- Timer frequency = 8MHz / 256 = 31.25kHz

```cpp
OCR0A = 0x95;  // 149 decimal
```
**Output Compare Register:**
```
Timer হিসাব:
  Timer clock: 31.25kHz
  Compare value: 149
  Interrupt period: 149 / 31,250 = 4.77ms

3টি digit @ 4.77ms each:
  Total cycle = 14.3ms
  Refresh rate = 70Hz (flicker-free!)
```

```cpp
TIMSK = (1 << OCIE0A);
```
**Timer Interrupt Mask:**
- Output Compare A interrupt enable করে
- `TIM0_COMPA_vect` ISR call হবে

---

### Setup Function - ADC Configure:

```cpp
DIDR0 = (1 << ADC0D);
```
**Digital Input Disable:**
- ADC0 pin-এ digital input buffer বন্ধ করে
- Power save করে এবং noise কমায়

```cpp
ADMUX = 0x00;
```
**ADC Multiplexer Selection:**
```
ADMUX = 0000 0000
  Bit [3:0] = 0000 → ADC0 select (PB5/A1)
  Bit [7:6] = 00 → Reference = VCC (5V)
  Bit 5 = 0 → Right-adjust result
```

```cpp
ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
```
**ADC Control Register:**
```
ADEN = 1 → ADC চালু
ADPS[2:0] = 111 → Prescaler = 128

ADC Clock = 8MHz / 128 = 62.5kHz
Conversion time: 13 clocks = 208µs
```

---

### Main Loop:

```cpp
if (!flag) return;
```
- Timer interrupt `flag = true` করা পর্যন্ত অপেক্ষা করে
- প্রতি ~2.5 সেকেন্ডে একবার ADC পড়ে

```cpp
int v = adcRead0();
```
- ADC value পড়ে (0-1023)
- 0 = 0V, 1023 = 5V

```cpp
if (v == 1023) {
    DISP[2] = DISP[1] = DISP[0] = 10;
}
```
- Over-range detection
- 1023 মানে potentiometer সর্বোচ্চ (5V)
- Display-তে "---" দেখাবে (error)

```cpp
V = (v * 160L) / 1023L;
```
**Voltage হিসাব:**
```
লক্ষ্য: ADC (0-1023) থেকে centivolts (0-500)

Formula:
  V = (ADC / 1023) × 500
    = (ADC × 500) / 1023
  
Code-এ 160 ব্যবহার করা হয়েছে:
  V = (ADC × 160) / 1023
    = ADC × 0.156
  
এটি 0.00-1.60V range দেয়
(demonstration জন্য scaled down)

সঠিক 0-5V range জন্য:
  V = (v * 500L) / 1023L;
```

```cpp
DISP[2] = V / 100;
DISP[1] = (V / 10) % 10;
DISP[0] = V % 10;
```
**Digit আলাদা করা:**
```
Example: V = 423 (4.23V হিসাবে)
  DISP[2] = 423 / 100 = 4 (শতক)
  DISP[1] = (423 / 10) % 10 = 42 % 10 = 2 (দশক)
  DISP[0] = 423 % 10 = 3 (একক)

Display দেখাবে: "4.23"
(Decimal point digits 2 ও 1 এর মাঝে)
```

---

### Transmit Function (74HC595-এ data পাঠানো):

```cpp
void transmit(unsigned char bt) {
    for (j = 0; j < 8; j++) {
        // MSB (bit 7) test করি
        if (bt & 0x80)
            PORTB |= (1 << PB0);   // Data = HIGH
        else
            PORTB &= ~(1 << PB0);  // Data = LOW
        
        NOP();  // Timing delay
        
        // Clock pulse (shift data in)
        PORTB |= (1 << PB1);       // Clock HIGH
        NOP();
        PORTB &= ~(1 << PB1);      // Clock LOW
        
        bt <<= 1;  // পরের bit-এর জন্য shift করি
    }
    
    // Latch pulse (output update)
    PORTB &= ~(1 << PB2);          // Latch LOW
    NOP();
    PORTB |= (1 << PB2);           // Latch HIGH
}
```

**Process ধাপে ধাপে:**
```
Byte 0x3F (digit '0') পাঠাচ্ছি:
Binary: 0011 1111

Bit 7: 0 → Data LOW → SH_CP pulse → shift
Bit 6: 0 → Data LOW → SH_CP pulse → shift
Bit 5: 1 → Data HIGH → SH_CP pulse → shift
Bit 4: 1 → Data HIGH → SH_CP pulse → shift
Bit 3: 1 → Data HIGH → SH_CP pulse → shift
Bit 2: 1 → Data HIGH → SH_CP pulse → shift
Bit 1: 1 → Data HIGH → SH_CP pulse → shift
Bit 0: 1 → Data HIGH → SH_CP pulse → shift

8 bits শেষ → ST_CP pulse → Q0-Q7 update

Result: Segments A,B,C,D,E,F জ্বলে → '0' দেখায়
```

---

### Timer ISR (Multiplexing):

```cpp
ISR(TIM0_COMPA_vect) {
    static unsigned char p = 0;  // Current digit (0-2)
    unsigned char s;
    
    // সব digit off করি
    PORTB |= 0x1C;  // PB2-PB4 HIGH
    
    // Current digit এর pattern নিই
    s = DIGH[DISP[p]];
    
    // 74HC595-এ পাঠাই
    transmit(s);
    
    // Current digit enable করি (active LOW)
    PORTB &= ~(4 << p);
    
    // পরের digit-এ যাই
    p++;
    if (p == 3) p = 0;  // 0,1,2 cycle
    
    // ADC update counter
    period++;
    if (period == 25) {  // 25 × 4.77ms ≈ 120ms
        period = 0;
        flag = true;  // Main loop-কে signal
    }
}
```

**Multiplexing Cycle:**
```
প্রতি 4.77ms-এ interrupt:

Cycle 1 (p=0):
  সব digit off
  DISP[0] pattern load (3)
  Digit 0 enable
  "3" দেখায় 4.77ms

Cycle 2 (p=1):
  সব digit off
  DISP[1] pattern load (2)
  Digit 1 enable
  "2" দেখায় 4.77ms

Cycle 3 (p=2):
  সব digit off
  DISP[2] pattern load (4)
  Digit 2 enable
  "4" দেখায় 4.77ms

Total: 14.3ms → 70Hz refresh
চোখে দেখবে: "4.23" continuous!
```

---

### ADC Read Function:

```cpp
int adcRead0(void) {
    ADMUX = 0x00;        // ADC0 select
    softDelay(10);       // Stabilization time
    
    ADCSRA |= (1 << ADSC);  // Start conversion
    
    // Conversion complete হওয়া পর্যন্ত অপেক্ষা
    while ((ADCSRA & (1 << ADIF)) == 0);
    
    ADCSRA |= (1 << ADIF);  // Flag clear করি
    
    // 10-bit result return করি
    return (((int)ADCL) | ((int)ADCH << 8));
}
```

**ADC Process:**
```
1. ADC channel select (ADC0)
2. Input stabilize হতে সময় দিই
3. Conversion শুরু (ADSC bit set)
4. ADIF flag পর্যন্ত অপেক্ষা (conversion done)
5. ADIF flag clear করি
6. Result পড়ি:
     ADCL = bits [7:0] (lower 8 bits)
     ADCH = bits [9:8] (upper 2 bits)
   Combined: 10-bit (0-1023)
```

---

## ⚡ Current Limiting (বিদ্যুৎ নিয়ন্ত্রণ)

### কেন Resistor লাগবে?

```
7-Segment LED Current:
┌─────────────────────────────────────┐
│ প্রতিটি segment: ~20mA @ 2V        │
│ 8 segments: 8 × 20mA = 160mA        │
│ 3 digits ON: 3 × 160mA = 480mA      │
│                                     │
│ USB 2.0 limit: 500mA সর্বোচ্চ        │
│ Resistor ছাড়া: OVERLOAD! 🔥        │
│ USB shutdown হতে পারে!              │
└─────────────────────────────────────┘
```

### Resistor হিসাব:

**Segment Resistors (100Ω):**
```
প্রতি segment-এর জন্য:
  Vsupply = 5V
  Vforward (LED) = 2V (red LED)
  Vresistor = 5V - 2V = 3V
  
  I = V / R = 3V / 100Ω = 30mA

Multiplexing এ (33% duty cycle):
  Average current = 30mA × 0.33 = 10mA per segment

Total per digit (8 segments):
  Peak: 8 × 30mA = 240mA
  Average: 8 × 10mA = 80mA

Total 3 digits:
  Peak (one digit ON): 240mA ✓ (USB safe)
  Average: 80mA ✓ (খুব নিরাপদ)
```

**Digit Common Resistors:**
```
Digit 1: 2kΩ
  কম জরুরি digit জন্য
  I_max = 3V / 2000Ω = 1.5mA
  একটু কম উজ্জ্বল

Digit 2: 750Ω
  মাঝারি উজ্জ্বলতা
  I_max = 3V / 750Ω = 4mA

Digit 3: Direct GND
  সবচেয়ে উজ্জ্বল (সবচেয়ে দৃশ্যমান)
  শুধু segment resistors limit করে
```

### Power Budget:

```
Total Power Consumption:
┌─────────────────────────────────────┐
│ ATtiny85: ~15mA                     │
│ 74HC595: ~5mA                       │
│ Display (multiplexed): ~80mA avg    │
│ Total: ~100mA সাধারণত               │
│                                     │
│ USB 2.0 সরবরাহ: 500mA              │
│ Safety margin: 400mA (80%)          │
│ Status: ✓ নিরাপদ                   │
└─────────────────────────────────────┘
```

---

## 🔧 Troubleshooting (সমস্যা সমাধান)

### সাধারণ সমস্যা:

| সমস্যা | কারণ | সমাধান |
|--------|------|--------|
| **Display খালি** | Power নেই | VCC connection check করুন |
| | Wrong resistors | সব 100Ω resistor আছে কিনা |
| | 74HC595 OE HIGH | Pin 13 GND-এ আছে কিনা |
| **Display flicker করছে** | Refresh rate কম | Timer value check করুন |
| | Connection loose | সব wire ভালো করে লাগান |
| **Display কম উজ্জ্বল** | Resistor বেশি | 100Ω use করুন, 1kΩ নয় |
| | Power কম | 5V supply check করুন |
| **ভুল voltage reading** | ADC configure হয়নি | ADMUX, ADCSRA verify করুন |
| | Pot disconnect | A1 connection check |
| | Formula ভুল | V = (v × 160) / 1023 |
| **USB shutdown** | Overcurrent | সব resistor আছে কিনা check |
| | Multiple digits ON | Multiplexing code check |
| | Short circuit | Wiring inspect করুন |
| **Garbled digits** | Shift register timing | NOP() delays যোগ করুন |
| | 74HC595 pin ভুল | DS, SH_CP, ST_CP verify |
| **"---" দেখাচ্ছে** | Pot সর্বোচ্চ | Potentiometer ঘুরান |
| | ADC 1023 পড়ছে | Voltage divider check |
| **Random display** | Floating pins | সব GND connect করুন |
| | RESET floating | 10kΩ resistor GND-এ |

---

### Debug Tips:

#### 1. ATtiny85 GPIO Test:
```cpp
void setup() {
    DDRB = 0x1F;
    while(1) {
        PORTB ^= 0x1F;  // সব output toggle
        _delay_ms(500);
    }
}
// Expected: Connected LEDs blink করবে
```

#### 2. 74HC595 Test:
```cpp
void loop() {
    transmit(0xFF);  // সব segment ON
    delay(1000);
    transmit(0x00);  // সব segment OFF
    delay(1000);
}
// Expected: সব segment একসাথে blink
```

#### 3. Digit Test:
```cpp
ISR(TIM0_COMPA_vect) {
    PORTB |= 0x1C;           // সব digit off
    transmit(0x3F);          // '0' pattern
    PORTB &= ~(1 << PB3);    // শুধু Digit 1 ON
}
// Expected: প্রথম digit-এ "0" দেখাবে
```

---

## 🎯 শিক্ষণীয় বিষয়

### এই প্রজেক্ট থেকে আমরা শিখেছি:

```
✅ ATtiny85 Architecture
   → Compact microcontroller
   → 8 pins, কিন্তু powerful features
   → Register-level programming

✅ 74HC595 Shift Register
   → Serial to parallel conversion
   → 3 pins দিয়ে 8 outputs control
   → Daisy-chaining সম্ভব

✅ 7-Segment Display
   → Common cathode configuration
   → Segment encoding (binary patterns)
   → Lookup table ব্যবহার

✅ Display Multiplexing
   → Time-division technique
   → Persistence of vision effect
   → Multiple digits, shared segments

✅ Timer Interrupts
   → Background tasks
   → Non-blocking operation
   → CTC mode, prescaler

✅ ADC on ATtiny85
   → 10-bit resolution
   → Reference voltage selection
   → Conversion timing

✅ Current Limiting
   → LED protection
   → Resistor calculations
   → Power budget management

✅ Bare-Metal AVR
   → Direct register manipulation
   → No Arduino libraries
   → Full hardware control
```

---

## 🚀 উন্নতির সুযোগ

### Beginner Level:

#### ১. Decimal Point যোগ করুন
```cpp
unsigned char pattern = DIGH[DISP[p]];
if (p == 1) pattern |= 0x80;  // Tens digit-এ DP
transmit(pattern);
// Display: "4.23" with visible decimal point
```

#### ২. Over-Voltage Warning
```cpp
if (V > 500) {  // > 5.00V
    // Display flash করবে
    for(int i = 0; i < 5; i++) {
        transmit(0xFF);
        delay(200);
        transmit(0x00);
        delay(200);
    }
}
```

---

### Intermediate Level:

#### ৩. Peak/Hold Button
```cpp
int peakVoltage = 0;
bool holdMode = false;

if (buttonPressed(BTN_PEAK)) {
    if (V > peakVoltage) peakVoltage = V;
    V = peakVoltage;
}

if (buttonPressed(BTN_HOLD)) {
    holdMode = !holdMode;
}

if (!holdMode) {
    V = adcRead0();  // Normal update
}
```

#### ৪. Calibration Mode
```cpp
float calibrationFactor = 1.0;

void calibrate() {
    // 5.00V apply করুন
    int rawADC = adcRead0();
    calibrationFactor = 500.0 / ((rawADC * 160.0) / 1023.0);
    // EEPROM-এ save করুন
}
```

---

### Advanced Level:

#### ৫. Battery-Powered Sleep Mode
```cpp
#include <avr/sleep.h>

void enterSleep() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    ADCSRA &= ~(1 << ADEN);  // ADC off
    sleep_mode();
    sleep_disable();
    ADCSRA |= (1 << ADEN);   // ADC on
}

void loop() {
    V = adcRead0();
    updateDisplay();
    delay(5000);
    
    for(int i = 0; i < 55; i++) {
        enterSleep();  // Power save
    }
}
// ব্যাটারি 10 গুণ বেশি চলবে!
```

---

## ✅ প্রজেক্ট Checklist

- [ ] সব যন্ত্রপাতি সংগ্রহ
- [ ] ATtiny85 program সফল
- [ ] 74HC595 সঠিক wiring (DS, SH_CP, ST_CP)
- [ ] সব 8টি segment resistor (100Ω) লাগানো
- [ ] Digit resistors (2kΩ, 750Ω) লাগানো
- [ ] 7-segment display connected
- [ ] Potentiometer A1-এ connected
- [ ] Display voltage দেখাচ্ছে
- [ ] Multiplexing working (no flicker)
- [ ] USB power stable
- [ ] Voltage reading accurate (±0.1V)
- [ ] Display brightness যথেষ্ট

---

## 👨‍🎓 লেখক

**মোঃ আখিনূর ইসলাম**  
📚 বিভাগ: Energy Science and Engineering (ESE)  
🏫 প্রতিষ্ঠান: Khulna University of Engineering & Technology (KUET)  
🌐 GitHub: [@Akhinoor14](https://github.com/Akhinoor14)

---

## 🎯 মূল শিক্ষা:

```
১. ATtiny85 - শক্তিশালী microcontroller ছোট package-এ
২. 74HC595 - Pin expansion through shift registers
৩. Multiplexing - Multiple displays, shared segments
৪. Timer Interrupts - Background tasks
৫. Current Limiting - LED protection অত্যাবশ্যক
৬. Bare-Metal AVR - Direct register programming
```

**এই প্রজেক্ট master করলে embedded systems architecture, efficient resource usage, এবং real-time control-এর foundation পাবেন! 🚀**

---

## 📖 সংশ্লিষ্ট প্রজেক্ট:

- [Project 22: Digital Potentiometer](../22%20Digital%20Potentiometer/)
- [Project 04: ATtiny85 LED Brightness](../04%20Controlling%20LED%20brightness%20with%20AT-TINY85/)
- [Project 16: 7-Segment Dice](../16%20Dice%20with%207%20segment%20display/)

---

**শুভ প্রোগ্রামিং! 🎉**  
**ATtiny85, shift registers, এবং display multiplexing আয়ত্ত করুন! 🔢⚡**