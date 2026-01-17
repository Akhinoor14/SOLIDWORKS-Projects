# 📷 Photodiode Light Sensor with Arduino

![Arduino Project](https://img.shields.io/badge/Arduino-UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Beginner-green?style=for-the-badge)
![Sensor](https://img.shields.io/badge/Photodiode-Light%20Sensor-yellow?style=for-the-badge)

## 📋 Table of Contents
- [Overview](#-overview)
- [Components Required](#-components-required)
- [Photodiode Basics](#-photodiode-basics)
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

This project demonstrates **light intensity measurement** using a **photodiode** and Arduino UNO. The photodiode operates in reverse-bias mode with a voltage divider circuit, converting light levels into analog voltage that Arduino reads via its ADC. This is fundamental for ambient light sensing, optical communication, and automatic lighting systems.

### Key Features:
- ✅ Analog light intensity measurement (0-1023)
- ✅ Voltage divider circuit with 10kΩ resistor
- ✅ Real-time Serial Monitor output
- ✅ Fast response to light changes
- ✅ Foundation for light-activated projects
- ✅ Low power consumption

---

## 🧰 Components Required

| Component | Quantity | Specification |
|-----------|----------|---------------|
| Arduino UNO | 1 | ATmega328P based |
| Photodiode | 1 | BPW34 or similar (reverse-bias mode) |
| 10kΩ Resistor | 1 | ±5% tolerance |
| Breadboard | 1 | For stable connections |
| Jumper Wires | 3 | Male-to-Male |
| USB Cable | 1 | For serial monitoring |

### 💰 Estimated Cost: $5-8 USD

---

## 🔬 Photodiode Basics

### What is a Photodiode?

A **photodiode** is a semiconductor device that converts light into electrical current. Unlike LEDs that emit light, photodiodes detect light.

### Photodiode vs LDR (Light Dependent Resistor):

| Feature | Photodiode | LDR (Photoresistor) |
|---------|-----------|---------------------|
| **Response Time** | Very fast (~μs) | Slow (~ms to s) |
| **Linearity** | Excellent | Poor |
| **Spectral Range** | Specific (UV, visible, IR) | Broad visible light |
| **Mode** | Current source | Resistance change |
| **Applications** | High-speed optical, precise | General ambient sensing |
| **Cost** | Moderate | Very cheap |

### Photodiode Operating Modes:

```
1. Photovoltaic Mode (0V bias):
   • Generates voltage from light
   • Solar cells use this mode
   • Lower sensitivity

2. Photoconductive Mode (Reverse-bias):
   • Higher sensitivity
   • Faster response
   • Used in this project
   • Requires voltage divider
```

### BPW34 Photodiode Specifications:

| Parameter | Value |
|-----------|-------|
| Type | Silicon PIN photodiode |
| Spectral Range | 430nm - 1100nm |
| Peak Sensitivity | 850nm (near-infrared) |
| Dark Current | < 2nA (at -5V) |
| Photo Current | ~60μA (at 1000 lux, 950nm) |
| Response Time | < 100ns |
| Operating Voltage | -5V to +5V |
| Viewing Angle | ±65° |

### Photodiode Pinout:

```
Photodiode (BPW34)
┌────────────────┐
│    ┌─────┐     │
│    │Light│     │  Larger window = photosensitive area
│    │Sensor│    │
│    └─────┘     │
│                │
│   Anode Cathode│
│    (+)   (-)   │
│     │     │    │
└─────┼─────┼────┘
      │     │
    Longer Shorter (flat edge)
     Lead   Lead
```

### Pin Identification:

| Pin | Identification | Connection |
|-----|---------------|------------|
| **Anode (+)** | Longer lead | 5V (reverse-bias) |
| **Cathode (-)** | Shorter lead, flat edge | A0 via 10kΩ → GND |

### How Photodiodes Work:

```
Physics of Light Detection:

1. Light photons hit photodiode
   ↓
2. Photons create electron-hole pairs
   ↓
3. Reverse bias sweeps carriers apart
   ↓
4. Photo current flows (proportional to light)
   ↓
5. Voltage divider converts current to voltage
   ↓
6. Arduino ADC reads voltage

Light Intensity ↑ → Photo Current ↑ → Voltage ↓ (at cathode)
```

### Voltage Divider Circuit:

```
+5V ────┬─── Anode (+)
        │
   Photodiode (acts as variable current source)
        │
        ├─── Cathode (-) ──┬─── to A0 (voltage reading)
        │                  │
        │              10kΩ Resistor
        │                  │
       GND ────────────────┴─────────

Voltage at A0:
  Bright light → Low resistance → Low voltage (~0-1V)
  Dim light → High resistance → High voltage (~2-4V)

ADC Reading:
  Bright: 0-200
  Normal: 200-500
  Dim: 500-800
  Dark: 800-1023
```

---

## 🔌 Circuit Diagram

### Connection Table:

| Component | Arduino Pin | Description |
|-----------|-------------|-------------|
| Photodiode Anode (+) | 5V | Reverse-bias voltage supply |
| Photodiode Cathode (-) | A0 | Analog signal (via voltage divider) |
| 10kΩ Resistor | Between A0 and GND | Pull-down resistor |

### Circuit Wiring:

```
Arduino UNO                    Photodiode Circuit
┌─────────────┐               ┌──────────────────┐
│             │               │                  │
│   5V  ●─────┼───────────────┤ Anode (+)        │
│             │               │   Photodiode     │
│  GND  ●─────┼────┬──────────┤ Cathode (-)──┬───┤
│             │    │          │              │   │
│   A0  ●─────┼────┴──────────┤◄─── Voltage  │   │
│             │               │     Divider  │   │
│             │               │   10kΩ ────┘   │
└─────────────┘               └──────────────────┘

Voltage divider creates variable voltage
Light ↑ → Current ↑ → A0 voltage ↓
Arduino ADC converts voltage to 0-1023
```

### Breadboard Layout:

```
Power Rails:
  Red (+)  → Arduino 5V → Photodiode Anode
  Blue (-) → Arduino GND

Signal:
  Photodiode Cathode → Breadboard row X
  Row X → Arduino A0
  Row X → 10kΩ resistor → GND

Important:
  • Photodiode polarity matters!
  • Longer lead = Anode (+) to 5V
  • Shorter lead = Cathode (-) to A0
  • 10kΩ resistor required for voltage divider
```

### 🖼️ Circuit Diagram:
![Photodiode Circuit](Circuit.png)

---

## ⚙️ How It Works

### Light-to-Voltage Conversion:

```
Step 1: Light Detection
  Photons → Photodiode → Photo current

Step 2: Reverse Bias Operation
  5V applied to anode
  Cathode connected to voltage divider
  
Step 3: Voltage Divider
  Photo current flows through 10kΩ resistor
  Creates voltage drop: V = I × R
  
Step 4: ADC Conversion
  Arduino reads voltage at A0
  10-bit ADC: 0V = 0, 5V = 1023

Step 5: Serial Output
  Display light intensity value
  Higher number = darker environment
```

### ADC (Analog-to-Digital Converter):

```
Arduino UNO ADC Specifications:
  • Resolution: 10-bit (0-1023)
  • Reference Voltage: 5V (default)
  • Conversion Time: ~100μs
  • Input Impedance: 100MΩ

Voltage to Digital:
  Digital Value = (Analog Voltage / 5V) × 1023
  
  Examples:
    0V → 0
    1V → 205
    2.5V → 512
    5V → 1023

Light Intensity Mapping:
  Bright sunlight:    0-200
  Indoor bright:      200-400
  Normal room:        400-600
  Dim light:          600-800
  Dark:               800-1023
```

### Response Characteristics:

```
Light Level vs ADC Reading:

ADC
1023├─────────╮         (Very Dark)
    │         │
 800│         ╰──╮
    │            │      (Dim)
 600│            ╰──╮
    │               │   (Normal)
 400│               ╰──╮
    │                  │(Bright)
 200│                  ╰──╮
    │                     │
   0│                     ╰─────► (Very Bright)
    └──────────────────────────────► Light Intensity

Photodiode in reverse-bias:
  More light → More current → Lower voltage at A0 → Lower ADC
```

---

## 📝 Step-by-Step Guide

### 1. **Identify Photodiode Polarity**
   - **Anode (+)**: Longer lead
   - **Cathode (-)**: Shorter lead, flat edge on package
   - **Important**: Reverse connection will not work!

### 2. **Build Voltage Divider**
   ```
   5V → Photodiode Anode
   Photodiode Cathode → A0 AND 10kΩ resistor
   10kΩ resistor → GND
   ```

### 3. **Connect to Arduino**
   ```
   Photodiode Anode (+) → Arduino 5V
   Photodiode Cathode (-) → Arduino A0
   10kΩ Resistor → Between A0 and GND
   ```

### 4. **Verify Connections**
   - Check polarity with multimeter if unsure
   - Ensure 10kΩ resistor is present
   - Confirm no short circuits

### 5. **Upload Code**
   - Open Arduino IDE
   - Copy code from `photo-diode.ino`
   - Select: **Tools > Board > Arduino UNO**
   - Select: **Tools > Port > [Your COM Port]**
   - Click **Upload**

### 6. **Open Serial Monitor**
   - Click **Tools > Serial Monitor**
   - Set baud rate to **9600**
   - Light intensity values should appear every 0.5s

### 7. **Test Light Response**
   - Cover photodiode → value increases (darker)
   - Shine flashlight → value decreases (brighter)
   - Observe real-time changes

---

## 💻 Code Explanation

### Full Code:

```cpp
/*
 * Project: Interfacing Photodiode with Arduino
 * Author: Md Akhinoor Islam
 * Description: Measure light intensity using photodiode as analog sensor
 */

const int sensorPin = A0;  // Photodiode connected to analog pin A0
int lightValue = 0;

void setup() {
  Serial.begin(9600);      // Start serial communication
}

void loop() {
  lightValue = analogRead(sensorPin);   // Read value from photodiode
  Serial.print("Light Intensity: ");
  Serial.println(lightValue);           // Print value to Serial Monitor
  delay(500);                           // Wait for 0.5 seconds
}
```

### Code Breakdown:

#### 1️⃣ **Pin Definition**
```cpp
const int sensorPin = A0;
```

| Constant | Value | Purpose |
|----------|-------|---------|
| `sensorPin` | A0 | Analog pin connected to photodiode cathode |

**Why A0?**
- Can use any analog pin (A0-A5)
- A0 is convention for first sensor

#### 2️⃣ **Variable Declaration**
```cpp
int lightValue = 0;
```

| Variable | Type | Range | Purpose |
|----------|------|-------|---------|
| `lightValue` | int | 0-1023 | Stores ADC reading |

**Data Type Choice:**
- `int` sufficient for 0-1023 range
- Could use `uint16_t` for clarity

#### 3️⃣ **Setup Function**
```cpp
void setup() {
  Serial.begin(9600);
}
```

**Serial Communication:**

| Function | Parameter | Purpose |
|----------|-----------|---------|
| `Serial.begin()` | 9600 | Initializes serial at 9600 baud |

**Baud Rate Options:**

| Baud | Use Case |
|------|----------|
| 9600 | Standard, reliable |
| 19200 | Faster data |
| 115200 | High-speed applications |

#### 4️⃣ **Read Analog Value**
```cpp
lightValue = analogRead(sensorPin);
```

**analogRead() Function:**

| Function | Returns | Range | Time |
|----------|---------|-------|------|
| `analogRead(pin)` | int | 0-1023 | ~100μs |

**How it Works:**
```
analogRead(A0):
  1. Sample voltage at A0
  2. Convert to 10-bit value
  3. Return digital value (0-1023)

Voltage Mapping:
  0V → 0
  0.5V → 102
  1.0V → 205
  2.5V → 512
  5.0V → 1023
```

#### 5️⃣ **Serial Output**
```cpp
Serial.print("Light Intensity: ");
Serial.println(lightValue);
```

**Output Format:**
```
Light Intensity: 345
Light Intensity: 342
Light Intensity: 338
```

**Print Functions:**

| Function | Action |
|----------|--------|
| `Serial.print()` | Print without newline |
| `Serial.println()` | Print with newline |

**Alternative Outputs:**

```cpp
// Option 1: Simple value
Serial.println(lightValue);

// Option 2: CSV format (for plotting)
Serial.println(lightValue);

// Option 3: Voltage display
float voltage = lightValue * (5.0 / 1023.0);
Serial.print(voltage);
Serial.println(" V");

// Option 4: Percentage
int percentage = map(lightValue, 0, 1023, 100, 0);
Serial.print(percentage);
Serial.println(" %");
```

#### 6️⃣ **Delay**
```cpp
delay(500);
```

**Sampling Rate:**

| Delay (ms) | Samples/sec | Use Case |
|-----------|-------------|----------|
| 50 | 20 | Fast tracking |
| 100 | 10 | Standard monitoring |
| 500 | 2 | Slow changes |
| 1000 | 1 | Visual display |

---

### Advanced Code Examples:

#### **Threshold Detection:**
```cpp
const int threshold = 500;

void loop() {
  lightValue = analogRead(sensorPin);
  
  if (lightValue > threshold) {
    Serial.println("Dark - Light needed");
  } else {
    Serial.println("Bright - Sufficient light");
  }
  
  delay(500);
}
```

#### **LED Control Based on Light:**
```cpp
const int ledPin = 13;
const int threshold = 500;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  lightValue = analogRead(sensorPin);
  
  if (lightValue > threshold) {
    digitalWrite(ledPin, HIGH);  // Turn on LED when dark
  } else {
    digitalWrite(ledPin, LOW);   // Turn off LED when bright
  }
  
  Serial.println(lightValue);
  delay(100);
}
```

#### **Smoothed Reading (Moving Average):**
```cpp
const int numReadings = 10;
int readings[numReadings];
int readIndex = 0;
int total = 0;
int average = 0;

void loop() {
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(sensorPin);
  total = total + readings[readIndex];
  readIndex = (readIndex + 1) % numReadings;
  average = total / numReadings;
  
  Serial.print("Smoothed: ");
  Serial.println(average);
  delay(100);
}
```

---

## 🌐 Simulation

### Try it Online:
🔗 **[View on Tinkercad](https://www.tinkercad.com/things/5uG3RNVzWWe-10-interfacingphotodiode)**

Features:
- Interactive light slider
- Real-time ADC reading
- Test voltage divider circuit
- Observe light response

---

## 🔧 Troubleshooting

### Common Issues:

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| Reading always 0 | Wrong polarity | Reverse photodiode connections |
| Reading always 1023 | No pull-down resistor | Add 10kΩ resistor between A0-GND |
| Erratic readings | Loose connections | Secure all wires on breadboard |
| No serial output | Wrong baud rate | Set Serial Monitor to 9600 |
| Slow response | Wrong photodiode mode | Ensure reverse-bias (anode to 5V) |
| Reading doesn't change | Photodiode damaged | Test with known good photodiode |
| Constant mid-value | Ambient light interference | Test in controlled lighting |

### Calibration:

```cpp
// Find min/max values for your setup
void calibrate() {
  int minValue = 1023;
  int maxValue = 0;
  
  Serial.println("Calibrating... Cover and uncover photodiode");
  
  for (int i = 0; i < 100; i++) {
    int reading = analogRead(sensorPin);
    if (reading < minValue) minValue = reading;
    if (reading > maxValue) maxValue = reading;
    delay(100);
  }
  
  Serial.print("Min: ");
  Serial.print(minValue);
  Serial.print(" Max: ");
  Serial.println(maxValue);
}
```

### Testing Photodiode:

```cpp
// Test photodiode functionality
void testPhotodiode() {
  Serial.println("Photodiode Test:");
  Serial.println("1. Cover photodiode completely");
  delay(2000);
  int darkReading = analogRead(sensorPin);
  Serial.print("Dark reading: ");
  Serial.println(darkReading);
  
  Serial.println("2. Shine bright light on photodiode");
  delay(2000);
  int brightReading = analogRead(sensorPin);
  Serial.print("Bright reading: ");
  Serial.println(brightReading);
  
  if (abs(darkReading - brightReading) > 200) {
    Serial.println("✓ Photodiode working correctly");
  } else {
    Serial.println("✗ Check connections and resistor");
  }
}
```

---

## 🎓 Learning Outcomes

### 📚 Concepts Covered:

| Concept | Description | Applications |
|---------|-------------|--------------|
| **Photodiodes** | Light-to-current conversion | Optical sensors, communication |
| **ADC** | Analog-to-digital conversion | All analog sensors |
| **Voltage Divider** | Resistive signal conditioning | Sensor interfacing |
| **Reverse Bias** | Photoconductive mode operation | High-speed detection |
| **Serial Communication** | Arduino-to-PC data transfer | Debugging, logging |

### 🚀 Skills Gained:
- ✅ Understanding photodiode operation
- ✅ Building voltage divider circuits
- ✅ Using analogRead() for sensor input
- ✅ Serial Monitor data visualization
- ✅ Threshold-based decision making
- ✅ Foundation for optical projects

### 🔄 Project Extensions:

1. **Automatic Night Light** - Turn on LED when dark
2. **Light Level Logger** - Save readings to SD card
3. **Solar Tracker** - Compare multiple photodiodes
4. **Optical Communication** - Send data via light pulses
5. **LCD Display** - Show light percentage
6. **RGB LED Control** - Brightness matches ambient light
7. **Light Alarm** - Alert when light level changes

---

## 📁 Project Files

| File | Description |
|------|-------------|
| `README.md` | Complete project documentation |
| `photo-diode.ino` | Arduino source code |
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
- Add calibration routine
- Implement data logging
- Create threshold alerts
- Add LCD/OLED display
- Share your light-sensing projects!

---

## ⭐ Show Your Support

If this helped you understand photodiodes, give it a ⭐!

---

### 📌 Real-World Applications:

- 🌙 **Automatic Lighting** - Street lights, garden lights
- ☀️ **Solar Tracking** - Maximum energy capture
- 📷 **Camera Metering** - Exposure control
- 🏭 **Industrial Automation** - Object detection
- 📡 **Optical Communication** - Data transmission
- 🔒 **Security Systems** - Intrusion detection
- 🌡️ **Environmental Monitoring** - Light level logging

Happy Sensing! 🎉
