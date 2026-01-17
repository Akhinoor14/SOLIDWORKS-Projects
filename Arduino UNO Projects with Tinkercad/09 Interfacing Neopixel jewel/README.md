# 💎 NeoPixel Jewel Control with Arduino (7 LEDs)

![Arduino Project](https://img.shields.io/badge/Arduino-UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Intermediate-yellow?style=for-the-badge)
![NeoPixel](https://img.shields.io/badge/NeoPixel-Jewel-purple?style=for-the-badge)

## 📋 Table of Contents
- [Overview](#-overview)
- [Components Required](#-components-required)
- [NeoPixel Jewel](#-neopixel-jewel)
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

This project demonstrates controlling a **7-pixel NeoPixel Jewel** using Arduino UNO. The jewel creates beautiful circular RGB animations with sequential color patterns (red, green, blue). The compact circular design makes it perfect for decorative projects, wearables, and artistic installations.

### Key Features:
- ✅ 7 individually addressable RGB LEDs (6 outer + 1 center)
- ✅ Circular/hexagonal layout for symmetric animations
- ✅ 16.7 million colors per LED (24-bit RGB)
- ✅ Single-wire WS2812B protocol
- ✅ Compact design (23.2mm diameter)
- ✅ Chainable with other NeoPixel products

---

## 🧰 Components Required

| Component | Quantity | Specification |
|-----------|----------|---------------|
| Arduino UNO | 1 | ATmega328P based |
| NeoPixel Jewel | 1 | 7 LEDs (WS2812B) - Adafruit #2226 |
| Breadboard | 1 | For connections |
| Jumper Wires | 3 | Male-to-Male |
| External Power Supply | 1 (optional) | 5V 1A (for brightness >50%) |
| 1000μF Capacitor | 1 (optional) | Power smoothing |
| 470Ω Resistor | 1 (optional) | Data line protection |

### 💰 Estimated Cost: $10-15 USD

---

## 🔬 NeoPixel Jewel

### What is a NeoPixel Jewel?

The **NeoPixel Jewel** is Adafruit's 7-LED circular module featuring WS2812B addressable RGB LEDs arranged in a jewel pattern:
- **1 center LED** (index 0)
- **6 outer LEDs** (indices 1-6) arranged hexagonally

### NeoPixel Jewel vs Strip:

| Feature | NeoPixel Strip | NeoPixel Jewel |
|---------|---------------|----------------|
| Layout | Linear | Circular (hexagonal) |
| LED Count | Varies (4, 8, 30, 60, 144) | 7 (fixed) |
| Size | Length varies | 23.2mm diameter |
| Mounting | Adhesive back | 4 mounting holes |
| Use Case | Linear effects | Radial/circular effects |

### WS2812B Specifications (per LED):

| Parameter | Value |
|-----------|-------|
| Operating Voltage | 5V DC (4-7V) |
| Current per LED (max) | 60mA (white at 255) |
| Current per LED (typical) | ~40mA (white typical) |
| Data Protocol | 800 kHz one-wire |
| Color Depth | 24-bit RGB (8-bit per channel) |
| Total Colors | 16,777,216 |
| PWM Resolution | 8-bit (256 levels per channel) |
| Refresh Rate | 400 Hz |

### Jewel Pinout:

```
NeoPixel Jewel (Top View)
┌──────────────────────────┐
│        ○  LED 1          │
│    ○         ○           │
│ LED 6  ●   LED 2         │  ● = Center LED (0)
│    ○   0    ○            │  ○ = Outer LEDs (1-6)
│ LED 5     LED 3          │
│        ○  LED 4          │
│                          │
│ IN  5V  GND  OUT         │
│  │   │   │   │           │
└──┼───┼───┼───┼───────────┘
   │   │   │   │
  DIN 5V GND DOUT
```

### Pin Configuration:

| Pin | Function | Description |
|-----|----------|-------------|
| **IN (DIN)** | Data Input | Receives control signal from Arduino |
| **5V** | Power | 5V supply (DO NOT use 3.3V) |
| **GND** | Ground | 0V reference |
| **OUT (DOUT)** | Data Output | Chains to next NeoPixel device |

### LED Indexing:

```
LED Index Map (viewed from front):

        1
    6       2
       0
    5       3
        4

Addressing:
  ring.setPixelColor(0, color);  // Center LED
  ring.setPixelColor(1, color);  // Top LED
  ring.setPixelColor(2, color);  // Top-right
  ring.setPixelColor(3, color);  // Bottom-right
  ring.setPixelColor(4, color);  // Bottom
  ring.setPixelColor(5, color);  // Bottom-left
  ring.setPixelColor(6, color);  // Top-left
```

### Physical Dimensions:

```
NeoPixel Jewel Measurements:
  Diameter: 23.2mm (0.91 inches)
  LED spacing: 60° apart (hexagonal)
  Mounting holes: 4 × Ø2mm
  PCB thickness: 1.2mm
  Weight: ~1.5g
```

### Power Consumption:

```
7-LED Jewel Power Budget:

Single LED:
  Red only:   ~20mA @ 255
  Green only: ~20mA @ 255
  Blue only:  ~20mA @ 255
  White (max): ~60mA @ (255,255,255)
  White (avg): ~40mA (typical usage)

Full Jewel (7 LEDs):
  All white (max): 7 × 60mA = 420mA
  All white (avg): 7 × 40mA = 280mA
  Mixed colors: 150-250mA (typical)

Arduino 5V Pin Limit: ~400-500mA
→ Safe for jewel at <80% brightness
→ Use external power for full brightness

Recommended Power:
  Low brightness (<50%): Arduino 5V OK
  High brightness (>50%): External 5V 1A
  Multiple jewels: 5V 2A+ supply
```

---

## 🔌 Circuit Diagram

### Connection Table:

| NeoPixel Jewel | Arduino Pin | Description |
|----------------|-------------|-------------|
| IN (DIN) | D6 | Control signal input |
| 5V | 5V | Power supply |
| GND | GND | Ground |
| OUT (DOUT) | Not connected | For chaining to next device |

### Circuit Wiring:

```
Arduino UNO                    NeoPixel Jewel (7 LEDs)
┌─────────────┐               ┌────────────────────┐
│             │               │      1             │
│   5V  ●─────┼───────────────┤   6   0   2        │
│             │               │      5   3         │
│  GND  ●─────┼───────────────┤        4           │
│             │               │                    │
│   D6  ●─────┼───────────────┤ IN 5V GND OUT      │
│             │               │  │  │  │           │
└─────────────┘               └──┼──┼──┼───────────┘
                                DIN 5V GND

D6 sends sequential color data
Center LED (0) + 6 outer LEDs (1-6)
```

### Enhanced Circuit (Recommended):

```
Data Line Protection:
  Arduino D6 → 470Ω resistor → Jewel IN
  (Protects against voltage spikes)

Power Smoothing:
  5V Supply ─┬─ 1000μF capacitor ─→ Jewel 5V
             │
            GND (common)
  (Prevents brownouts during LED changes)

Multi-Jewel Chaining:
  Jewel 1 OUT → Jewel 2 IN → Jewel 3 IN → ...
  (All share common 5V and GND)
```

### 🖼️ Circuit Diagram:
![NeoPixel Jewel Circuit](Circuit.png)

### Breadboard Layout:

```
Power Rails:
  Red (+)  → Arduino 5V → Jewel 5V
  Blue (-) → Arduino GND → Jewel GND

Signal:
  Arduino D6 → Breadboard → Jewel IN

Mounting:
  • Use 4 mounting holes for stability
  • Keep wires short (<6 inches)
  • Solder connections for permanent projects
  • Use header pins for breadboard prototyping
```

---

## ⚙️ How It Works

### Data Flow:

```
Arduino D6 sends 24-bit RGB data for each LED:

Step 1: Prepare color data
  LED[0] = RED   (255, 0, 0)  Center
  LED[1] = RED   (255, 0, 0)  Top
  LED[2] = RED   (255, 0, 0)  Top-right
  LED[3] = RED   (255, 0, 0)  Bottom-right
  LED[4] = RED   (255, 0, 0)  Bottom
  LED[5] = RED   (255, 0, 0)  Bottom-left
  LED[6] = RED   (255, 0, 0)  Top-left

Step 2: Convert to GRB byte order
  Each LED: 24 bits (G-R-B)
  Total: 7 × 24 = 168 bits

Step 3: Transmit at 800 kHz
  Entire jewel updates in ~210μs

Step 4: Latch (>50μs LOW)
  All LEDs update simultaneously
```

### Animation Sequence (Project Code):

```
Time:      0s      1.05s   2.1s    Loop
Cycle:     RED  →  GREEN → BLUE  → RED...

LED Animation Pattern (Sequential):

Iteration 0: LED 0 RED ON  → OFF
Iteration 1: LED 1 RED ON  → OFF
Iteration 2: LED 2 RED ON  → OFF
...
Iteration 6: LED 6 RED ON  → OFF

Total RED cycle: 7 × 150ms = 1050ms
Total GREEN cycle: 1050ms
Total BLUE cycle: 1050ms
Complete loop: 3150ms (3.15 seconds)

Visual Pattern:
         1           1           1
     6       2   6   ●   2   6       2
        0           0           0
     5       3   5       3   5       3
         4           4           4
       RED         GREEN        BLUE
```

### Circular Animation Possibilities:

```
Chase Effect (Clockwise):
  LED 1 → 2 → 3 → 4 → 5 → 6 → repeat

Radial Burst:
  Center (0) ON
  All outer (1-6) ON simultaneously
  Center OFF, outer OFF

Opposite Pair:
  LED 1 & 4 (opposite sides)
  LED 2 & 5
  LED 3 & 6
```

---

## 📝 Step-by-Step Guide

### 1. **Install Adafruit NeoPixel Library**
   - Open Arduino IDE
   - Go to **Sketch > Include Library > Manage Libraries**
   - Search: **Adafruit NeoPixel**
   - Click **Install** (by Adafruit)
   - Close Library Manager

### 2. **Identify Jewel Pinout**
   - **IN** = Data input (usually marked with arrow →)
   - **5V** = Power (often labeled VCC or +)
   - **GND** = Ground (often labeled - or G)
   - **OUT** = Data output (for chaining, not used here)

### 3. **Connect Power (GND First!)**
   ```
   Jewel GND → Arduino GND
   Jewel 5V → Arduino 5V
   ```
   - Always connect ground before power
   - Prevents static discharge damage

### 4. **Connect Data Line**
   ```
   Jewel IN → Arduino D6
   ```
   - Can use any digital pin (update code accordingly)
   - Keep wire short and direct

### 5. **Upload Code**
   - Copy code from `neopixel-jewel.ino`
   - Verify library is included: `#include <Adafruit_NeoPixel.h>`
   - Select: **Tools > Board > Arduino UNO**
   - Select: **Tools > Port > [Your COM Port]**
   - Click **Upload** (→)

### 6. **Observe Animation**
   - LEDs should light up sequentially (0→1→2→3→4→5→6)
   - Red → Green → Blue color cycles
   - Center LED lights first in each cycle
   - Smooth transitions with 150ms delays

---

## 💻 Code Explanation

### Full Code:

```cpp
/*
 * Project: NeoPixel Jewel (7 LEDs) Control
 * Author: Md Akhinoor Islam
 * Description: Sequential RGB animation on 7-LED NeoPixel Jewel
 */

#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 7

Adafruit_NeoPixel ring(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  ring.begin();
  ring.show(); // All off initially
}

void loop() {
  // RED cycle
  for (int i = 0; i < NUMPIXELS; i++) {
    ring.setPixelColor(i, ring.Color(255, 0, 0));
    ring.show();
    delay(150);
    ring.setPixelColor(i, 0);
  }

  // GREEN cycle
  for (int i = 0; i < NUMPIXELS; i++) {
    ring.setPixelColor(i, ring.Color(0, 255, 0));
    ring.show();
    delay(150);
    ring.setPixelColor(i, 0);
  }

  // BLUE cycle
  for (int i = 0; i < NUMPIXELS; i++) {
    ring.setPixelColor(i, ring.Color(0, 0, 255));
    ring.show();
    delay(150);
    ring.setPixelColor(i, 0);
  }
}
```

### Code Breakdown:

#### 1️⃣ **Include Library**
```cpp
#include <Adafruit_NeoPixel.h>
```
- Includes Adafruit's NeoPixel control library
- Manages precise 800 kHz timing
- Provides high-level functions for color control

#### 2️⃣ **Define Constants**
```cpp
#define PIN 6
#define NUMPIXELS 7
```

| Constant | Value | Purpose |
|----------|-------|---------|
| `PIN` | 6 | Data pin (D6) |
| `NUMPIXELS` | 7 | NeoPixel Jewel has 7 LEDs (1 center + 6 outer) |

#### 3️⃣ **Create Ring Object**
```cpp
Adafruit_NeoPixel ring(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
```

**Constructor Parameters:**

| Parameter | Value | Meaning |
|-----------|-------|---------|
| `NUMPIXELS` | 7 | Total LED count |
| `PIN` | 6 | Data output pin |
| `NEO_GRB` | Byte order | Green-Red-Blue (WS2812B standard) |
| `NEO_KHZ800` | 800 kHz | WS2812B protocol speed |

**Why "ring"?**
- Variable name reflects circular layout
- Could be named "jewel", "circle", "pixels", etc.
- Naming convention for clarity

#### 4️⃣ **Setup Function**
```cpp
void setup() {
  ring.begin();
  ring.show();
}
```

**Initialization:**

| Function | Action |
|----------|--------|
| `ring.begin()` | Configures pin, allocates memory buffer |
| `ring.show()` | Clears all LEDs (sets to black/OFF) |

#### 5️⃣ **RED Cycle**
```cpp
for (int i = 0; i < NUMPIXELS; i++) {
  ring.setPixelColor(i, ring.Color(255, 0, 0));
  ring.show();
  delay(150);
  ring.setPixelColor(i, 0);
}
```

**Iteration Details:**

| i | LED Position | Time (ms) | Color |
|---|-------------|-----------|-------|
| 0 | Center | 0 | RED |
| 1 | Top | 150 | RED |
| 2 | Top-right | 300 | RED |
| 3 | Bottom-right | 450 | RED |
| 4 | Bottom | 600 | RED |
| 5 | Bottom-left | 750 | RED |
| 6 | Top-left | 900 | RED |

**Total RED cycle:** 1050ms

#### 6️⃣ **setPixelColor() Function**
```cpp
ring.setPixelColor(i, ring.Color(255, 0, 0));
```

**Two Forms:**

```cpp
// Form 1: Packed color
ring.setPixelColor(index, 32-bit_color);

// Form 2: Separate R,G,B
ring.setPixelColor(index, red, green, blue);
```

**Important:** Only updates memory buffer, not LEDs!

#### 7️⃣ **Color() Function**
```cpp
ring.Color(red, green, blue);
```

**Common Colors:**

| Color | R | G | B | Visual |
|-------|---|---|---|--------|
| Red | 255 | 0 | 0 | 🔴 |
| Green | 0 | 255 | 0 | 🟢 |
| Blue | 0 | 0 | 255 | 🔵 |
| Yellow | 255 | 255 | 0 | 🟡 |
| Cyan | 0 | 255 | 255 | 🩵 |
| Magenta | 255 | 0 | 255 | 🟣 |
| White | 255 | 255 | 255 | ⚪ |
| Orange | 255 | 165 | 0 | 🟠 |
| Purple | 128 | 0 | 128 | 🟣 |
| Pink | 255 | 192 | 203 | 🩷 |

#### 8️⃣ **show() Function**
```cpp
ring.show();
```

**Critical Function:**
- Transmits buffer to LEDs
- Takes ~210μs for 7 LEDs
- All LEDs update simultaneously
- Must call after `setPixelColor()` to see changes

#### 9️⃣ **Animation Delay**
```cpp
delay(150);
```

**Timing Options:**

| Delay (ms) | Effect | Speed |
|-----------|--------|-------|
| 50 | Very fast, hard to follow | Rapid |
| 100 | Fast, smooth | Quick |
| 150 | Medium (default) | Balanced |
| 300 | Slow, clear | Leisurely |
| 500 | Very slow, deliberate | Slow-mo |

#### 🔟 **Turn OFF LED**
```cpp
ring.setPixelColor(i, 0);
```

**Alternative ways to turn OFF:**
```cpp
ring.setPixelColor(i, 0);                    // Shorthand
ring.setPixelColor(i, ring.Color(0, 0, 0));  // Explicit
ring.setPixelColor(i, 0, 0, 0);              // Separate R,G,B
```

---

### Advanced Functions:

```cpp
// Global brightness (0-255)
ring.setBrightness(100);  // ~39% brightness

// Read pixel color
uint32_t color = ring.getPixelColor(0);

// Clear all pixels
ring.clear();  // Sets all to black
ring.show();   // Must transmit changes

// Get LED count
uint16_t count = ring.numPixels();  // Returns 7

// Fill all with one color
ring.fill(ring.Color(255, 0, 0), 0, 7);  // All red
ring.show();

// Rainbow effect (advanced)
void rainbow(uint8_t wait) {
  for(long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
    for(int i=0; i<ring.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / ring.numPixels());
      ring.setPixelColor(i, ring.gamma32(ring.ColorHSV(pixelHue)));
    }
    ring.show();
    delay(wait);
  }
}
```

---

## 🌐 Simulation

### Try it Online:
🔗 **[View on Tinkercad](https://www.tinkercad.com/things/8oz9T9aag1W-09-neopixel-jewel)**

Features:
- Interactive jewel visualization
- Real-time color changes
- Test circular patterns
- Experiment with different animations

---

## 🔧 Troubleshooting

### Common Issues:

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| No LEDs light up | Wrong wiring | Check: IN=D6, 5V=5V, GND=GND |
| Only center LED works | Damaged outer LEDs | Test each LED individually |
| Random flickering | Loose IN connection | Secure data wire, add 470Ω resistor |
| Dim/wrong colors | Insufficient power | Use external 5V supply |
| Library not found | Not installed | Install "Adafruit NeoPixel" from Library Manager |
| Wrong color order | Incorrect flag | Try NEO_RGB instead of NEO_GRB |
| One LED stuck | Failed LED in chain | Replace jewel or skip that LED in code |

### Pattern-Specific Issues:

```cpp
// Test individual LEDs:
void testLEDs() {
  for (int i = 0; i < 7; i++) {
    ring.clear();
    ring.setPixelColor(i, ring.Color(255, 255, 255));  // White
    ring.show();
    Serial.print("LED ");
    Serial.print(i);
    Serial.println(" ON");
    delay(1000);
  }
}
```

### Debugging Code:

```cpp
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 7

Adafruit_NeoPixel ring(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  ring.begin();
  ring.setBrightness(50);  // Lower power consumption
  ring.show();
  Serial.println("NeoPixel Jewel initialized");
  Serial.println("LED positions:");
  Serial.println("  0 = Center");
  Serial.println("  1-6 = Outer (clockwise from top)");
}

void loop() {
  for (int i = 0; i < NUMPIXELS; i++) {
    Serial.print("LED ");
    Serial.print(i);
    Serial.print(" (");
    Serial.print(i == 0 ? "Center" : "Outer");
    Serial.println(") RED");
    
    ring.setPixelColor(i, ring.Color(255, 0, 0));
    ring.show();
    delay(500);
    
    ring.setPixelColor(i, ring.Color(0, 0, 0));
    ring.show();
    delay(100);
  }
}
```

---

## 🎓 Learning Outcomes

### 📚 Concepts Covered:

| Concept | Description | Applications |
|---------|-------------|--------------|
| **Circular LED Arrays** | Radial/symmetric light patterns | Wearables, decorations, indicators |
| **Addressable RGB** | Individual LED control | Any multi-LED display |
| **Sequential Animation** | Loop-based pattern generation | Visual effects, status indicators |
| **WS2812B Protocol** | 800 kHz one-wire communication | NeoPixel, addressable LED strips |
| **Power Budgeting** | Current calculation for LED arrays | Any power-sensitive project |

### 🚀 Skills Gained:
- ✅ Using Adafruit NeoPixel library
- ✅ Creating circular/radial animations
- ✅ Understanding LED indexing in non-linear layouts
- ✅ RGB color mixing and control
- ✅ Power management for LED arrays
- ✅ Debugging addressable LED issues

### 🔄 Project Extensions:

1. **Radial Burst Effect** - Center OUT expansion
2. **Color Wheel** - Continuous rainbow rotation
3. **Breathing Effect** - Fade in/out smoothly
4. **Opposite Pairs** - Mirror effects across center
5. **Music Reactive** - Beat-synchronized pulses
6. **Temperature Indicator** - Color changes with sensor
7. **Multiple Jewels** - Chain 2-3 jewels for patterns

---

## 📁 Project Files

| File | Description |
|------|-------------|
| `README.md` | Complete project documentation |
| `neopixel-jewel.ino` | Arduino source code |
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
- Create new circular animations
- Implement radial patterns
- Add sensor integration
- Develop multi-jewel synchronization
- Share your jewel projects!

---

## ⭐ Show Your Support

If this helped you learn about NeoPixel Jewels, give it a ⭐!

---

### 📌 Real-World Applications:

- 💍 **Wearable Jewelry** - LED earrings, pendants, bracelets
- 🎨 **Art Installations** - Interactive light sculptures
- 🎮 **Gaming Props** - Glowing power-ups, status indicators
- 🤖 **Robot Eyes** - Animated robot facial expressions
- 📱 **Smart Accessories** - Notification indicators
- 🎄 **Holiday Ornaments** - Animated Christmas decorations
- 🏆 **Award Trophies** - Dynamic LED centers

Happy Creating! 🎉
