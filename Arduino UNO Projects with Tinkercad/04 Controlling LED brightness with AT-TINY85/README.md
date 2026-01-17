# 🌟 ATtiny85 LED Brightness Control with Potentiometer

![ATtiny85](https://img.shields.io/badge/ATtiny85-Microcontroller-red?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Intermediate-orange?style=for-the-badge)
![Power](https://img.shields.io/badge/Power-3V_Battery-blue?style=for-the-badge)

## 📋 Table of Contents
- [Overview](#-overview)
- [Components Required](#-components-required)
- [ATtiny85 Overview](#-attiny85-overview)
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

This project demonstrates how to use the **ATtiny85** microcontroller to control LED brightness with a potentiometer. The ATtiny85 is a compact, low-power alternative to Arduino UNO, perfect for embedded systems and portable projects powered by a simple 3V coin battery.

### Key Features:
- ✅ Compact microcontroller (8-pin IC)
- ✅ Low power consumption (3V battery operation)
- ✅ Analog input reading from potentiometer
- ✅ PWM output for LED brightness control
- ✅ Introduction to embedded system design
- ✅ Cost-effective alternative to Arduino for simple projects

---

## 🧰 Components Required

| Component | Quantity | Specification |
|-----------|----------|---------------|
| ATtiny85 Microcontroller | 1 | 8-pin DIP package |
| LED (Any color) | 1 | 5mm standard |
| Resistor | 1 | 220Ω (Red-Red-Brown) |
| Potentiometer | 1 | 10kΩ (B10K) |
| Coin Battery | 1 | 3V (CR2032 or similar) |
| Battery Holder | 1 | For CR2032 |
| Breadboard | 1 | For prototyping |
| Jumper Wires | 10-12 | Male-to-Male |

### 💰 Estimated Cost: $5-8 USD

---

## 🔬 ATtiny85 Overview

### What is ATtiny85?

The ATtiny85 is a low-power 8-bit microcontroller from Atmel's tinyAVR family.

### ATtiny85 vs Arduino UNO:

| Feature | ATtiny85 | Arduino UNO |
|---------|----------|-------------|
| **Size** | 8-pin IC | Full board with USB |
| **Digital I/O** | 6 pins | 14 pins |
| **Analog Input** | 4 pins (A0-A3) | 6 pins (A0-A5) |
| **PWM Pins** | 2 pins | 6 pins |
| **Flash Memory** | 8 KB | 32 KB |
| **RAM** | 512 bytes | 2 KB |
| **Power** | 1.8V - 5.5V | 5V (via USB/adapter) |
| **Cost** | ~$1-2 | ~$5-10 |
| **Best For** | Compact, battery projects | Learning, prototyping |

### ATtiny85 Pinout:

```
      ATtiny85 (DIP-8)
      ┌─────▪─────┐
 RST  │1   ⚫   8│ VCC (+3V)
(A3)  │2       7│ (A1/SCK)
(A2)  │3       6│ (PWM/MISO)
 GND  │4       5│ (PWM/MOSI) ← PB0 (LED)
      └───────────┘
      
Pin Functions:
• Pin 1: RESET (not used in this project)
• Pin 2: PB3/A3 (Analog Input) → Potentiometer
• Pin 3: PB4/A2 (Analog Input)
• Pin 4: GND → Ground
• Pin 5: PB0 (PWM) → LED
• Pin 6: PB1 (PWM)
• Pin 7: PB2/A1 (Analog/SCK)
• Pin 8: VCC → 3V Power
```

---

## 🔌 Circuit Diagram

### Connection Table:

#### Potentiometer Connections:
| Potentiometer Pin | ATtiny85 Pin | Description |
|-------------------|--------------|-------------|
| Terminal 1 | Pin 8 (VCC) | 3V power |
| Wiper (Middle) | Pin 2 (PB3/A3) | Analog input |
| Terminal 2 | Pin 4 (GND) | Ground |

#### LED Connections:
| LED Pin | Connection | Notes |
|---------|------------|-------|
| Anode (+) | Through 220Ω → Pin 5 (PB0) | PWM output |
| Cathode (-) | Pin 4 (GND) | Ground |

#### Power Supply:
| Battery | ATtiny85 Pin |
|---------|--------------|
| + (3V) | Pin 8 (VCC) |
| - (GND) | Pin 4 (GND) |

### Circuit Wiring:

```
     3V Coin Battery
         ┌─┴─┐
         │ + │
         └─┬─┘
           │
    ┌──────┴──────────────────────┐
    │                              │
    │        ATtiny85              │
    │      ┌─────▪─────┐           │
    │ RST  │1   ⚫   8│ VCC ←──────┤
    │  ┌───│2       7│             │
    │  │   │3       6│             │
    └──┼───│4       5│───[220Ω]───[LED]───┐
       │   └───────────┘                   │
       │              PB0 (PWM)            │
       │                                   │
  Potentiometer                           GND
   (10kΩ)                                  │
   ┌─┴─┐                                   │
   │▲  │ Wiper                            │
   └─┬─┘                                   │
     │                                     │
     └─────────────────────────────────────┘
          GND
```

### 🖼️ Circuit Diagram:
![ATtiny85 LED Control Circuit](Circuit.png)

---

## ⚙️ How It Works

### Working Principle:

1. **Power Supply:**
   - 3V coin battery powers the entire circuit
   - ATtiny85 operates efficiently at low voltage

2. **Analog Input:**
   - Potentiometer creates variable voltage (0V to 3V)
   - Connected to Pin 2 (PB3/A3) - analog input
   - `analogRead()` converts to digital value (0-1023)

3. **Value Mapping:**
   - Analog reading: 0-1023 (10-bit ADC)
   - PWM output: 0-255 (8-bit)
   - `map()` function converts between ranges

4. **PWM Output:**
   - Pin 5 (PB0) generates PWM signal
   - `analogWrite()` controls duty cycle
   - LED brightness changes accordingly

### Data Flow:

```
Potentiometer Rotation
         ↓
Voltage Change (0-3V)
         ↓
ATtiny85 A3 Pin Reads
         ↓
ADC Conversion (0-1023)
         ↓
map() Function
         ↓
PWM Value (0-255)
         ↓
PB0 Pin Output
         ↓
LED Brightness Changes
```

---

## 📝 Step-by-Step Guide

### 1. **Prepare ATtiny85**
   - If using Tinkercad: Simply add ATtiny85 from components
   - If using real hardware: May need to program via Arduino as ISP (see advanced section)

### 2. **Insert Components**
   - Place ATtiny85 in breadboard (notch at top)
   - Insert potentiometer
   - Insert LED with correct polarity

### 3. **Power Connections**
   ```
   Battery + → ATtiny85 Pin 8 (VCC)
   Battery - → ATtiny85 Pin 4 (GND)
   ```

### 4. **Potentiometer Wiring**
   ```
   Left pin → VCC (3V)
   Middle pin → ATtiny85 Pin 2 (PB3/A3)
   Right pin → GND
   ```

### 5. **LED Wiring**
   ```
   ATtiny85 Pin 5 (PB0) → 220Ω resistor → LED Anode
   LED Cathode → GND
   ```

### 6. **Upload Code**
   - In Tinkercad: Paste code directly into ATtiny85
   - Real hardware: Program using Arduino as ISP
   - Start simulation and test

### 7. **Test Operation**
   - Rotate potentiometer
   - Observe LED brightness changing
   - Full rotation should go from OFF to full brightness

---

## 💻 Code Explanation

### Full Code:

```cpp
/*
 * Project: LED Brightness Control with ATtiny85
 * Author: Md. Akhinoor Islam
 * Description: Control LED brightness using potentiometer
 */

const int potPin = A3;  // Potentiometer on analog pin A3 (Pin 2)
const int ledPin = 0;   // LED on PB0 (Pin 5)

void setup() {
  pinMode(ledPin, OUTPUT);  // Set PB0 as output
}

void loop() {
  int potValue = analogRead(potPin);              // Read pot (0-1023)
  int brightness = map(potValue, 0, 1023, 0, 255); // Map to PWM range
  analogWrite(ledPin, brightness);                // Set LED brightness
  delay(10);                                      // Smooth update
}
```

### Code Breakdown:

#### 1️⃣ **Pin Definitions**
```cpp
const int potPin = A3;
const int ledPin = 0;
```

| Pin | ATtiny85 Physical Pin | Function |
|-----|----------------------|----------|
| A3 | Pin 2 (PB3) | Analog input from potentiometer |
| 0 | Pin 5 (PB0) | PWM output to LED |

**Note:** On ATtiny85:
- Digital pin 0 = Physical pin 5 (PB0)
- Analog pin A3 = Physical pin 2 (PB3)

#### 2️⃣ **Setup Function**
```cpp
void setup() {
  pinMode(ledPin, OUTPUT);
}
```
- Configures PB0 (Pin 5) as output for LED control
- No need to set pinMode for analog input

#### 3️⃣ **Main Loop**

**Read Potentiometer:**
```cpp
int potValue = analogRead(potPin);
```
- Reads voltage from potentiometer
- Returns value 0-1023
- 0 = 0V, 1023 = 3V (or VCC)

**Map Values:**
```cpp
int brightness = map(potValue, 0, 1023, 0, 255);
```

| Function | Purpose |
|----------|---------|
| `map()` | Converts one range to another |
| Input range | 0-1023 (analog reading) |
| Output range | 0-255 (PWM values) |

**Example mapping:**
- potValue = 0 → brightness = 0
- potValue = 512 → brightness = 128
- potValue = 1023 → brightness = 255

**Set LED Brightness:**
```cpp
analogWrite(ledPin, brightness);
```
- Outputs PWM signal to PB0
- Duty cycle = brightness/255
- LED brightness corresponds to value

**Delay:**
```cpp
delay(10);
```
- Small delay for smooth transitions
- Prevents excessive CPU usage

---

## 🌐 Simulation

### Try it Online:
🔗 **[View on Tinkercad](https://www.tinkercad.com/things/jBYdqVo95Ea-04-controlling-led-brightness-with-at-tiny85)**

Features in simulation:
- Interactive potentiometer control
- Real-time brightness adjustment
- Battery-powered operation
- Perfect for learning before building

---

## 🔧 Troubleshooting

### Common Issues:

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| LED not responding | Wrong pin assignment | Use pin 0 for LED (maps to PB0/Pin 5) |
| Dim LED throughout | Low battery voltage | Check battery is 3V, replace if needed |
| Erratic brightness | Poor potentiometer connection | Check wiring to Pin 2 (A3) |
| LED always full bright | Potentiometer not connected | Verify pot wiper to A3 connection |
| No power | Battery polarity wrong | + to Pin 8, - to Pin 4 |
| Brightness not changing | Using digitalWrite() | Must use analogWrite() for PWM |

### 📌 Programming ATtiny85 (Real Hardware):

If you want to program a real ATtiny85:

1. **Using Arduino as ISP:**
   - Connect Arduino UNO to ATtiny85
   - Upload "ArduinoISP" sketch to UNO
   - Wire ATtiny85 to UNO as ISP
   - Install ATtiny board definitions in Arduino IDE
   - Select ATtiny85, 8MHz internal clock
   - Upload your sketch

2. **Wiring for Programming:**
   ```
   Arduino → ATtiny85
   Pin 10  → Pin 1 (RESET)
   Pin 11  → Pin 5 (MOSI)
   Pin 12  → Pin 6 (MISO)
   Pin 13  → Pin 7 (SCK)
   5V      → Pin 8 (VCC)
   GND     → Pin 4 (GND)
   ```

---

## 🎓 Learning Outcomes

### 📚 Concepts Covered:

| Concept | Description | Applications |
|---------|-------------|--------------|
| **ATtiny85** | Compact 8-pin microcontroller | Wearables, tiny robots, sensors |
| **Low Power Design** | Battery-operated circuits | IoT devices, remote sensors |
| **Analog Input** | Reading variable voltage | Sensor interfacing |
| **PWM on ATtiny** | Limited PWM pins (2) | LED control, motor speed |
| **map() Function** | Range conversion | Scaling sensor values |
| **Embedded Systems** | Complete system in small package | Product design, manufacturing |

### 🚀 Skills Gained:
- ✅ Understanding microcontroller alternatives to Arduino
- ✅ Low-power circuit design
- ✅ Working with limited resources (pins, memory)
- ✅ Battery-powered project design
- ✅ Cost optimization for production
- ✅ Introduction to embedded programming

### 🔄 Project Extensions:
1. **Temperature Sensor** - Read with A2, display with LED brightness
2. **Light Sensor** - LDR on A3, auto-adjust LED
3. **Multiple LEDs** - Use both PWM pins (PB0, PB1)
4. **Sleep Mode** - Add power-saving sleep modes
5. **Mini Robot** - Control 2 motors with PWM

---

## 📁 Project Files

| File | Description |
|------|-------------|
| `README.md` | Complete project documentation |
| `ATTINY85 Brightness.ino` | ATtiny85 source code |
| `Code & Circuit Explanation(for beginner).md` | Bengali tutorial |
| `Circuit.png` | Circuit diagram |
| `license` | MIT License |

---

## 👨‍🎓 Author

**Md. Akhinoor Islam**  
📚 Energy Science and Engineering (ESE)  
🏫 Khulna University of Engineering & Technology (KUET)  
🌐 [GitHub Profile](https://github.com/Akhinoor14)

---

## 📄 License

This project is licensed under the MIT License.

---

## 🤝 Contributing

Improve this project:
- Add sleep mode for power saving
- Create PCB design
- Add more sensors
- Share your ATtiny85 projects!

---

## ⭐ Show Your Support

If this helped you learn about ATtiny85, give it a ⭐!

---

### 📌 Why Use ATtiny85?

- **Cost:** 5-10x cheaper than Arduino UNO
- **Size:** Fits in tiny spaces
- **Power:** Battery lasts much longer
- **Production:** Perfect for final products
- **Learning:** Understand microcontroller basics

Happy Tinkering! 🎉
