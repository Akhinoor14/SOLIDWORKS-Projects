# 🌈 NeoPixel Strip Control with Arduino (4 LEDs)

![Arduino Project](https://img.shields.io/badge/Arduino-UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Intermediate-yellow?style=for-the-badge)
![NeoPixel](https://img.shields.io/badge/NeoPixel-WS2812B-purple?style=for-the-badge)

## 📋 Table of Contents
- [Overview](#-overview)
- [Components Required](#-components-required)
- [NeoPixel Technology](#-neopixel-technology)
- [Circuit Diagram](#-circuit-diagram)
- [How It Works](#-how-it-works)
- [Step-by-Step Guide](#-step-by-step-guide)
- [Code Explanation](#-code-explanation)
- [Simulation](#-simulation)
- [Troubleshooting](#-troubleshooting)
- [Learning Outcomes](#-learning-outcomes)
- [Author](#-author)

---

## 🎯 Overview

This project demonstrates how to control **individually addressable RGB LEDs** (NeoPixels) using Arduino UNO. The 4-LED strip displays smooth color animations cycling through red, green, and blue using the Adafruit NeoPixel library. This technology is essential for LED displays, mood lighting, wearables, and visual effects.

### Key Features:
- ✅ Individual LED control (4 addressable pixels)
- ✅ 16.7 million colors per LED (24-bit RGB)
- ✅ Single-wire communication protocol
- ✅ Smooth color animations
- ✅ Low-latency pixel updates
- ✅ Chainable/expandable design

---

## 🧰 Components Required

| Component | Quantity | Specification |
|-----------|----------|---------------|
| Arduino UNO | 1 | ATmega328P based |
| NeoPixel Strip | 1 | 4 LEDs (WS2812B or compatible) |
| Breadboard | 1 | For stable connections |
| Jumper Wires | 3 | Male-to-Male |
| External Power Supply | 1 (optional) | 5V 1A+ (for >10 LEDs) |
| 1000μF Capacitor | 1 (optional) | Power supply smoothing |
| 470Ω Resistor | 1 (optional) | Data line protection |

### 💰 Estimated Cost: $8-12 USD

---

## 🔬 NeoPixel Technology

### What are NeoPixels?

**NeoPixels** are Adafruit's brand of **WS2812B** addressable RGB LEDs. Each pixel contains:
- Red, Green, Blue LED dies
- WS2812B control chip
- Single-wire communication interface

### WS2812B Chip Specifications:

| Parameter | Value |
|-----------|-------|
| Operating Voltage | 5V DC (4-7V) |
| Current per LED (max) | 60mA (20mA × 3 colors) |
| Current per LED (typical) | ~40mA (white at full brightness) |
| Data Protocol | 800 kHz one-wire |
| Color Depth | 24-bit (8-bit per channel) |
| Colors Available | 16,777,216 (256³) |
| PWM Frequency | 400 Hz |
| Refresh Rate | 400 Hz |
| Cascade Limit | Theoretically unlimited |

### NeoPixel Pinout:

```
WS2812B LED (Single Pixel)
┌─────────────────────────┐
│   ┌───────────────┐     │
│   │  WS2812B IC   │     │
│   │    + RGB LEDs │     │
│   └───────────────┘     │
│                         │
│  5V   DIN   GND   DOUT  │
│   │    │     │     │    │
└───┼────┼─────┼─────┼────┘
    │    │     │     │
   5V   Data  GND   Next LED
```

### Pin Functions:

| Pin | Function | Description |
|-----|----------|-------------|
| **5V** | Power | 5V supply (DO NOT use 3.3V) |
| **GND** | Ground | 0V reference |
| **DIN** | Data Input | Receives control signal from Arduino/previous LED |
| **DOUT** | Data Output | Sends signal to next LED in chain |

### How Data Flows:

```
Data Chain (Daisy-Chaining):

Arduino D6 ──→ [LED 0] ──→ [LED 1] ──→ [LED 2] ──→ [LED 3]
                DIN DOUT   DIN DOUT   DIN DOUT   DIN DOUT

Each LED:
  1. Reads first 24 bits (its RGB data)
  2. Passes remaining bits to next LED
  3. Updates its own color
  4. Repeats
```

### RGB Color Model:

```
24-bit Color (8 bits per channel):

RED   (8-bit): 0-255 intensity
GREEN (8-bit): 0-255 intensity  
BLUE  (8-bit): 0-255 intensity

Total Colors = 256 × 256 × 256 = 16,777,216

Examples:
  strip.Color(255, 0, 0)   → Pure Red
  strip.Color(0, 255, 0)   → Pure Green
  strip.Color(0, 0, 255)   → Pure Blue
  strip.Color(255, 255, 0) → Yellow (Red + Green)
  strip.Color(255, 0, 255) → Magenta (Red + Blue)
  strip.Color(0, 255, 255) → Cyan (Green + Blue)
  strip.Color(255, 255, 255) → White (all colors)
  strip.Color(128, 128, 128) → Gray (50% brightness)
  strip.Color(0, 0, 0)     → Black (OFF)
```

### WS2812B Timing Protocol:

```
One-Wire 800 kHz Protocol:

Bit 0:
  HIGH: 0.4μs, LOW: 0.85μs
  ▄▄▄▄________ (total 1.25μs)

Bit 1:
  HIGH: 0.8μs, LOW: 0.45μs
  ▄▄▄▄▄▄▄▄____ (total 1.25μs)

Reset (latch):
  LOW for >50μs
  ________________ (signals data complete)

24-bit color transmission:
  [G7 G6 G5 G4 G3 G2 G1 G0] Green byte first
  [R7 R6 R5 R4 R3 R2 R1 R0] Red byte
  [B7 B6 B5 B4 B3 B2 B1 B0] Blue byte

Note: GRB order, not RGB!
```

### Power Consumption:

```
Current Draw Calculation:

Single LED:
  Red only:   ~20mA @ 255
  Green only: ~20mA @ 255
  Blue only:  ~20mA @ 255
  White max:  ~60mA @ (255,255,255)
  White avg:  ~40mA (typical)

4-LED Strip:
  All white (max): 4 × 60mA = 240mA
  All white (avg): 4 × 40mA = 160mA
  
Arduino 5V pin: Can supply ~400mA
→ Safe for 4 LEDs at full brightness
→ Use external power for 10+ LEDs

Power Budget:
  1-10 LEDs: Arduino 5V OK
  10-30 LEDs: 5V 1A supply
  30-100 LEDs: 5V 2A supply
  100+ LEDs: 5V 4A+ supply
```

---

## 🔌 Circuit Diagram

### Connection Table:

| NeoPixel Strip | Arduino Pin | Description |
|----------------|-------------|-------------|
| DIN (Data In) | D6 | Control signal input |
| 5V / VCC | 5V | Power supply |
| GND | GND | Ground |

### Circuit Wiring:

```
Arduino UNO                    NeoPixel Strip (4 LEDs)
┌─────────────┐               ┌────────────────────────┐
│             │               │ [0] [1] [2] [3]        │
│   5V  ●─────┼───────────────┤ 5V  5V  5V  5V         │
│             │               │                        │
│  GND  ●─────┼───────────────┤ GND GND GND GND        │
│             │               │                        │
│   D6  ●─────┼───────────────┤ DIN → → → →            │
│             │               │ (data flows through)   │
└─────────────┘               └────────────────────────┘

D6 sends digital signal
Each LED reads its color, passes rest to next
```

### Enhanced Circuit (Recommended for Production):

```
Arduino D6 ──┬── 470Ω ──→ DIN (NeoPixel)
             │
         [Optional data line protection resistor]

5V Supply ──┬── 1000μF Capacitor ──→ NeoPixel 5V
            │
           GND (common)

Benefits:
  • 470Ω resistor: Protects data line from voltage spikes
  • 1000μF capacitor: Smooths power supply, prevents brownouts
```

### 🖼️ Circuit Diagram:
![NeoPixel Strip Circuit](Circuit.png)

### Breadboard Layout:

```
Power Rails:
  Red (+) → Arduino 5V → NeoPixel 5V
  Blue (-) → Arduino GND → NeoPixel GND

Signal:
  Arduino D6 → Breadboard → NeoPixel DIN

Important:
  ⚠️ Connect GND FIRST before data line
  ⚠️ Keep wires short (<6 inches for data)
  ⚠️ Common ground is CRITICAL
```

---

## ⚙️ How It Works

### Data Transmission Process:

```
Arduino sends 24-bit color data per LED:

Step 1: Arduino prepares data
  LED[0] = RED   (255, 0, 0)
  LED[1] = GREEN (0, 255, 0)
  LED[2] = BLUE  (0, 0, 255)
  LED[3] = OFF   (0, 0, 0)

Step 2: Convert to GRB format
  LED[0]: G=0, R=255, B=0 → 24 bits
  LED[1]: G=255, R=0, B=0 → 24 bits
  LED[2]: G=0, R=0, B=255 → 24 bits
  LED[3]: G=0, R=0, B=0   → 24 bits

Step 3: Serial transmission via D6
  96 bits total sent at 800 kHz

Step 4: Each LED processes
  First LED takes first 24 bits
  Passes remaining 72 bits to next LED
  Second LED takes next 24 bits, etc.

Step 5: Latch (>50μs LOW)
  All LEDs update simultaneously
```

### Animation Sequence (Loop):

```
Time:   0s      0.8s    1.6s    2.4s    Loop
Color:  RED  →  GREEN → BLUE  → RED  →  ...

LED Animation Pattern:
LED 0: █____  ____█  ____█
LED 1: _█___  ____█  ____█
LED 2: __█__  ____█  ____█
LED 3: ___█_  ____█  ____█
       RED    GREEN  BLUE

Each LED lights up sequentially (0→1→2→3)
Then turns off and next color starts
```

### Memory Map:

```
Arduino Memory:
  Adafruit_NeoPixel object stores:
    • Pin number (D6)
    • Pixel count (4)
    • Pixel buffer: 4 × 3 bytes = 12 bytes
    • Color format (NEO_GRB)

Pixel Buffer (RAM):
  [LED0_G] [LED0_R] [LED0_B]
  [LED1_G] [LED1_R] [LED1_B]
  [LED2_G] [LED2_R] [LED2_B]
  [LED3_G] [LED3_R] [LED3_B]

strip.show() transmits entire buffer
```

---

## 📝 Step-by-Step Guide

### 1. **Install Adafruit NeoPixel Library**
   - Open Arduino IDE
   - Go to **Sketch > Include Library > Manage Libraries**
   - Search: **Adafruit NeoPixel**
   - Click **Install** (by Adafruit)
   - Wait for installation to complete

### 2. **Identify NeoPixel Connections**
   - **3 wires** on strip: 5V, GND, DIN
   - Some strips have 4th wire (DOUT for chaining)
   - Check strip datasheet for pinout
   - Look for arrows indicating data direction (→)

### 3. **Connect Power FIRST**
   ```
   NeoPixel 5V → Arduino 5V
   NeoPixel GND → Arduino GND
   ```
   - Always connect GND before signal
   - Prevents static damage

### 4. **Connect Data Line**
   ```
   NeoPixel DIN → Arduino D6
   ```
   - Can use any digital pin (update code accordingly)
   - Keep wire short and direct

### 5. **Upload Code**
   - Copy code from `neopixel-strip.ino`
   - Verify library is included
   - Select: **Tools > Board > Arduino UNO**
   - Select: **Tools > Port > [Your COM Port]**
   - Click **Upload**

### 6. **Observe Animation**
   - LEDs should light up sequentially
   - Red → Green → Blue cycle
   - Smooth transitions with delays
   - If no light: check power and connections

---

## 💻 Code Explanation

### Full Code:

```cpp
/*
 * Project: NeoPixel Strip Control (4 LEDs)
 * Author: Md Akhinoor Islam
 * Description: Sequential RGB animation on 4-LED NeoPixel strip
 */

#include <Adafruit_NeoPixel.h>

#define PIN 6           // Data pin
#define NUMPIXELS 4     // Total number of NeoPixels

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();       // Initialize the strip
  strip.show();        // Turn OFF all pixels initially
}

void loop() {
  // RED cycle
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0)); // RED
    strip.show();
    delay(200);
    strip.setPixelColor(i, strip.Color(0, 0, 0)); // OFF
  }

  // GREEN cycle
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(0, 255, 0)); // GREEN
    strip.show();
    delay(200);
    strip.setPixelColor(i, strip.Color(0, 0, 0)); // OFF
  }

  // BLUE cycle
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 255)); // BLUE
    strip.show();
    delay(200);
    strip.setPixelColor(i, strip.Color(0, 0, 0)); // OFF
  }
}
```

### Code Breakdown:

#### 1️⃣ **Include Library**
```cpp
#include <Adafruit_NeoPixel.h>
```
- Adafruit's library for WS2812B control
- Handles complex timing automatically
- Download: Library Manager → "Adafruit NeoPixel"

#### 2️⃣ **Define Constants**
```cpp
#define PIN 6
#define NUMPIXELS 4
```

| Constant | Value | Purpose |
|----------|-------|---------|
| `PIN` | 6 | Data output pin (D6) |
| `NUMPIXELS` | 4 | Number of LEDs in strip |

#### 3️⃣ **Create NeoPixel Object**
```cpp
Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
```

**Constructor Parameters:**

| Parameter | Value | Meaning |
|-----------|-------|---------|
| `NUMPIXELS` | 4 | LED count |
| `PIN` | 6 | Data pin |
| `NEO_GRB` | Color order | Green-Red-Blue byte order |
| `NEO_KHZ800` | 800 kHz | WS2812B protocol speed |

**Color Order Options:**

| Flag | Byte Order | Use For |
|------|------------|---------|
| `NEO_RGB` | Red-Green-Blue | Some older strips |
| `NEO_GRB` | Green-Red-Blue | WS2812B (most common) |
| `NEO_RGBW` | + White channel | SK6812 RGBW strips |

#### 4️⃣ **Setup Function**
```cpp
void setup() {
  strip.begin();
  strip.show();
}
```

**Initialization Steps:**

| Function | Purpose |
|----------|---------|
| `strip.begin()` | Initializes pin, allocates memory buffer |
| `strip.show()` | Sends data (all pixels OFF initially) |

**Why `show()` in setup?**
- Ensures all LEDs start in known OFF state
- Clears any residual colors from previous runs

#### 5️⃣ **RED Cycle**
```cpp
for (int i = 0; i < NUMPIXELS; i++) {
  strip.setPixelColor(i, strip.Color(255, 0, 0));
  strip.show();
  delay(200);
  strip.setPixelColor(i, strip.Color(0, 0, 0));
}
```

**Iteration Table:**

| i | LED | Action | Time (ms) |
|---|-----|--------|-----------|
| 0 | 0 | RED ON | 0 |
| 0 | 0 | RED OFF | 200 |
| 1 | 1 | RED ON | 200 |
| 1 | 1 | RED OFF | 400 |
| 2 | 2 | RED ON | 400 |
| 2 | 2 | RED OFF | 600 |
| 3 | 3 | RED ON | 600 |
| 3 | 3 | RED OFF | 800 |

**Total RED cycle time:** 800ms

#### 6️⃣ **setPixelColor() Function**
```cpp
strip.setPixelColor(i, strip.Color(255, 0, 0));
```

**Function Signature:**
```cpp
void setPixelColor(uint16_t n, uint32_t color);
```

| Parameter | Type | Range | Purpose |
|-----------|------|-------|---------|
| `n` | uint16_t | 0 to (NUMPIXELS-1) | LED index |
| `color` | uint32_t | 24-bit RGB | Packed color value |

**Important:** This only updates the memory buffer, NOT the LEDs!

#### 7️⃣ **Color() Function**
```cpp
strip.Color(red, green, blue);
```

**Returns packed 32-bit color:**
```
24-bit RGB packed into uint32_t:

Input:  R=255, G=0, B=0
Binary: 0x00 FF 00 00
        └─┘ └┘ └┘ └┘
        Unused R G  B
```

**Color Examples:**

| Color | R | G | B | Hex |
|-------|---|---|---|-----|
| Red | 255 | 0 | 0 | 0xFF0000 |
| Green | 0 | 255 | 0 | 0x00FF00 |
| Blue | 0 | 0 | 255 | 0x0000FF |
| Yellow | 255 | 255 | 0 | 0xFFFF00 |
| Cyan | 0 | 255 | 255 | 0x00FFFF |
| Magenta | 255 | 0 | 255 | 0xFF00FF |
| White | 255 | 255 | 255 | 0xFFFFFF |
| Orange | 255 | 165 | 0 | 0xFFA500 |
| Purple | 128 | 0 | 128 | 0x800080 |

#### 8️⃣ **show() Function**
```cpp
strip.show();
```

**What it does:**
- Transmits entire pixel buffer to strip
- Uses precise timing (800 kHz)
- Updates all LEDs simultaneously
- Takes ~30μs per pixel (120μs for 4 pixels)

**Critical:** Always call after `setPixelColor()` to see changes!

#### 9️⃣ **Delay for Animation**
```cpp
delay(200);
```

**Animation Speed:**

| Delay (ms) | LEDs/sec | Effect |
|-----------|----------|--------|
| 50 | 20 | Very fast, hard to see |
| 100 | 10 | Fast, smooth |
| 200 | 5 | Medium (default) |
| 500 | 2 | Slow, clear |
| 1000 | 1 | Very slow |

#### 🔟 **Turn OFF Pixel**
```cpp
strip.setPixelColor(i, strip.Color(0, 0, 0));
```

**Note:** This sets buffer to black but doesn't transmit yet!
- LED stays ON until next `show()` in loop
- Creates "trail" effect

---

### Advanced Functions:

```cpp
// Set brightness (0-255)
strip.setBrightness(128);  // 50% brightness globally

// Get pixel color
uint32_t color = strip.getPixelColor(0);

// Clear all pixels
strip.clear();  // Sets all to black
strip.show();   // Must call show() to update

// Number of pixels
uint16_t count = strip.numPixels();  // Returns 4

// Alternative color setting (separate R,G,B)
strip.setPixelColor(0, 255, 0, 0);  // No need for Color()
```

---

## 🌐 Simulation

### Try it Online:
🔗 **[View on Tinkercad](https://www.tinkercad.com/things/14mb9UB3gDW-neopixel-strip)**

Features:
- Interactive NeoPixel simulation
- Real-time color changes
- Test different patterns
- Experiment with delays

---

## 🔧 Troubleshooting

### Common Issues:

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| No LEDs light up | Wrong wiring | Check: DIN=D6, 5V=5V, GND=GND |
| First LED works, rest don't | Data chain broken | Check DOUT connection between LEDs |
| Random colors/flickering | Loose data wire | Secure DIN connection, use 470Ω resistor |
| Dim/wrong colors | Insufficient power | Use external 5V supply for 5+ LEDs |
| Library error | Not installed | Install "Adafruit NeoPixel" from Library Manager |
| White LEDs instead of colors | Wrong color order | Try NEO_RGB instead of NEO_GRB |
| Stuck on one color | Code not uploading | Re-upload, check serial monitor |

### Power Issues:

**Symptoms of insufficient power:**
- LEDs dim progressively down the strip
- Colors look washed out (white tinted)
- Arduino resets randomly
- Only first few LEDs work

**Solutions:**
```
For 1-10 LEDs:
  → Arduino 5V usually sufficient

For 10-30 LEDs:
  → External 5V 1A supply
  → Connect supply GND to Arduino GND
  → Power NeoPixels from external supply
  → Data from Arduino D6

For 30+ LEDs:
  → 5V 2A+ supply
  → Add 1000μF capacitor across power
  → Inject power at multiple points
```

### Data Line Issues:

```cpp
// Add data line protection:
Arduino D6 → 470Ω resistor → NeoPixel DIN

// Test with simple code:
void loop() {
  strip.setPixelColor(0, strip.Color(255, 0, 0));
  strip.show();
  delay(1000);
  strip.setPixelColor(0, strip.Color(0, 0, 0));
  strip.show();
  delay(1000);
}
```

### Debugging Code:

```cpp
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 4

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(50);  // Reduce power consumption
  strip.show();
  Serial.println("NeoPixel initialized");
}

void loop() {
  for (int i = 0; i < NUMPIXELS; i++) {
    Serial.print("LED ");
    Serial.print(i);
    Serial.println(" RED");
    
    strip.setPixelColor(i, strip.Color(255, 0, 0));
    strip.show();
    delay(500);
    
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.show();
    delay(100);
  }
}
```

---

## 🎓 Learning Outcomes

### 📚 Concepts Covered:

| Concept | Description | Applications |
|---------|-------------|--------------|
| **Addressable LEDs** | Individual LED control via single wire | LED displays, lighting effects |
| **Serial Data Protocol** | 800 kHz one-wire communication | WS2812B, APA102, SK6812 |
| **RGB Color Mixing** | 24-bit color depth (16M colors) | Display technology, mood lighting |
| **Digital Signal Processing** | Precise timing for data transmission | All digital protocols |
| **Power Management** | Current calculation, supply sizing | Any multi-LED project |

### 🚀 Skills Gained:
- ✅ Using Adafruit NeoPixel library
- ✅ Understanding addressable LED protocols
- ✅ RGB color theory and mixing
- ✅ Power consumption calculations
- ✅ Sequential animation programming
- ✅ Debugging data transmission issues

### 🔄 Project Extensions:

1. **Rainbow Effect** - Cycle through full color spectrum
2. **Color Fading** - Smooth transitions between colors
3. **Music Reactive** - LEDs respond to sound sensor
4. **Fire Effect** - Flickering red/orange/yellow
5. **Running Lights** - Knight Rider scanner effect
6. **Multiple Patterns** - Button selects different animations
7. **Brightness Control** - Potentiometer adjusts brightness

---

## 📁 Project Files

| File | Description |
|------|-------------|
| `README.md` | Complete project documentation |
| `neopixel-strip.ino` | Arduino source code |
| `Code & Circuit Explanation(for beginner).md` | Bengali tutorial |
| `Circuit.png` | Circuit diagram |
| `license` | MIT License |

---

## 👨‍🎓 Author

**Md Akhinoor Islam**  
📚 Energy Science and Engineering (ESE)  
🏫 Khulna University of Engineering & Technology (KUET)  
🌐 [GitHub Profile](https://github.com/Akhinoor14)

---

## 📄 License

This project is licensed under the MIT License.

---

## 🤝 Contributing

Enhance this project:
- Create new animation patterns
- Add sensor integration
- Implement color palettes
- Optimize power consumption
- Share your NeoPixel projects!

---

## ⭐ Show Your Support

If this helped you learn about NeoPixels, give it a ⭐!

---

### 📌 Real-World Applications:

- 💡 **Smart Lighting** - Home automation and mood lighting
- 🎮 **Gaming Peripherals** - RGB keyboards, mice, headsets
- 🎭 **Stage Effects** - Concert lighting and displays
- 👕 **Wearable Tech** - LED clothing and accessories
- 🚗 **Automotive** - Underglow, interior accent lighting
- 🏢 **Signage** - Dynamic LED signs and displays
- 🎄 **Holiday Decorations** - Animated Christmas lights

Happy Coding! 🎉
