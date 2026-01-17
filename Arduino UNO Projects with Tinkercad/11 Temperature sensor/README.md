# 🌡️ TMP36 Temperature Sensor with Arduino

![Arduino Project](https://img.shields.io/badge/Arduino-UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Beginner-green?style=for-the-badge)
![Sensor](https://img.shields.io/badge/TMP36-Temperature-red?style=for-the-badge)

## 📋 Table of Contents
- [Overview](#-overview)
- [Components Required](#-components-required)
- [TMP36 Sensor Basics](#-tmp36-sensor-basics)
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

This project demonstrates **ambient temperature measurement** using the **TMP36 analog temperature sensor** and Arduino UNO. The TMP36 outputs a voltage proportional to temperature, which Arduino reads via ADC and converts to Celsius, Fahrenheit, and Kelvin. This is essential for environmental monitoring, HVAC control, and temperature-sensitive applications.

### Key Features:
- ✅ Direct temperature-to-voltage conversion
- ✅ No external components required (standalone sensor)
- ✅ Wide temperature range (-40°C to +125°C)
- ✅ Linear output (10mV per °C)
- ✅ Multi-unit display (Celsius, Fahrenheit, Kelvin)
- ✅ Low power consumption (~50μA)

---

## 🧰 Components Required

| Component | Quantity | Specification |
|-----------|----------|---------------|
| Arduino UNO | 1 | ATmega328P based |
| TMP36 Sensor | 1 | Precision temperature sensor |
| Breadboard | 1 | For stable connections |
| Jumper Wires | 3 | Male-to-Male |
| USB Cable | 1 | For serial monitoring |

### 💰 Estimated Cost: $5-7 USD

---

## 🔬 TMP36 Sensor Basics

### What is TMP36?

The **TMP36** is a low-voltage, precision analog temperature sensor from Analog Devices. It directly converts temperature to a proportional voltage output without requiring external calibration or signal conditioning circuits.

### TMP36 Family Comparison:

| Model | Range | Accuracy | Output |
|-------|-------|----------|--------|
| **TMP35** | +10°C to +125°C | ±2°C | 10mV/°C, 250mV at 25°C |
| **TMP36** | -40°C to +125°C | ±2°C | 10mV/°C, 750mV at 25°C |
| **TMP37** | +5°C to +100°C | ±2°C | 20mV/°C, 500mV at 25°C |

**Why TMP36?**
- Extended low-temperature range (-40°C)
- Centered 0V output at 0°C makes calculations simple
- Most versatile for general applications

### TMP36 vs Other Sensors:

| Feature | TMP36 | DHT11 | DS18B20 | LM35 |
|---------|-------|-------|---------|------|
| **Interface** | Analog | Digital (1-Wire) | Digital (1-Wire) | Analog |
| **Accuracy** | ±2°C | ±2°C | ±0.5°C | ±0.5°C |
| **Range** | -40°C to +125°C | 0°C to 50°C | -55°C to +125°C | -55°C to +150°C |
| **Resolution** | Continuous (ADC limited) | 1°C | 0.0625°C | Continuous |
| **Wiring** | 3 pins (simple) | 3 pins (protocol) | 3 pins (protocol) | 3 pins (simple) |
| **Cost** | Low | Very low | Moderate | Low |
| **Humidity** | ❌ No | ✅ Yes | ❌ No | ❌ No |

### TMP36 Specifications:

| Parameter | Value |
|-----------|-------|
| Supply Voltage | 2.7V - 5.5V |
| Supply Current | < 50μA |
| Operating Range | -40°C to +125°C |
| Accuracy | ±1°C (typ), ±2°C (max) |
| Scale Factor | 10mV/°C |
| Offset Voltage | 500mV at 0°C |
| Output Impedance | 0.1Ω (typ) |
| Conversion Time | Instantaneous (analog) |

### TMP36 Pinout:

```
TMP36 Sensor (Front View - Flat Side Facing You)
┌─────────────────┐
│    T M P 3 6    │
│                 │
│  ┌───────────┐  │
│  │Temperature│  │
│  │  Sensing  │  │
│  │   Die     │  │
│  └───────────┘  │
│                 │
│   1    2    3   │
└───┼────┼────┼───┘
    │    │    │
   +Vs  Vout GND
   (5V) (A0) (-)

Pin 1: +Vs (Power Supply)
Pin 2: Vout (Signal Output)
Pin 3: GND (Ground)
```

### Pin Identification:

| Pin | Name | Function | Connection |
|-----|------|----------|------------|
| **1 (Left)** | +Vs | Power supply | Arduino 5V |
| **2 (Middle)** | Vout | Voltage output | Arduino A0 |
| **3 (Right)** | GND | Ground | Arduino GND |

**⚠️ CRITICAL:** Always view TMP36 with **flat side facing you**. Reversed connection can damage the sensor!

### Temperature-to-Voltage Transfer Function:

The TMP36 has a **linear transfer function**:

```
Vout = (Temperature °C × 10mV) + 500mV

Examples:
  -40°C → (-40 × 10mV) + 500mV = 100mV
    0°C → (0 × 10mV) + 500mV = 500mV (0.5V)
  +25°C → (25 × 10mV) + 500mV = 750mV (0.75V)
  +50°C → (50 × 10mV) + 500mV = 1000mV (1.0V)
 +100°C → (100 × 10mV) + 500mV = 1500mV (1.5V)
 +125°C → (125 × 10mV) + 500mV = 1750mV (1.75V)

Reverse Formula (Voltage → Temperature):
  Temperature °C = (Vout - 500mV) / 10mV
  Temperature °C = (Vout - 0.5V) × 100
```

### Output Voltage Curve:

```
Vout (V)
1.75├───────────────╱ (125°C)
    │              ╱
1.50│            ╱ (100°C)
    │          ╱
1.25│        ╱ (75°C)
    │      ╱
1.00│    ╱ (50°C)
    │  ╱
0.75│╱ (25°C)
0.50├ (0°C)
0.25│
0.10├ (-40°C)
    └────────────────────────► Temperature (°C)
   -40   0   25  50  75  100  125

Linear slope: 10mV per °C
Offset: 500mV at 0°C
```

### Why 500mV Offset?

```
Without offset:
  Negative temperatures would produce negative voltages
  Difficult to measure with single-supply ADC
  
With 500mV offset:
  -40°C → 100mV (positive!)
  0°C → 500mV
  Range: 100mV to 1750mV (all positive)
  
Benefit:
  Single-supply operation (no negative rail needed)
  Compatible with standard ADCs
```

---

## 🔌 Circuit Diagram

### Connection Table:

| TMP36 Pin | Arduino Pin | Description |
|-----------|-------------|-------------|
| 1 (+Vs) | 5V | Power supply (2.7V - 5.5V) |
| 2 (Vout) | A0 | Analog temperature signal |
| 3 (GND) | GND | Ground reference |

### Circuit Wiring:

```
Arduino UNO                    TMP36 Sensor
┌─────────────┐               ┌──────────────┐
│             │               │  T M P 3 6   │
│   5V  ●─────┼───────────────┤ Pin 1 (+Vs)  │
│             │               │              │
│  GND  ●─────┼───────────────┤ Pin 3 (GND)  │
│             │               │              │
│   A0  ●─────┼───────────────┤ Pin 2 (Vout) │
│             │               │              │
└─────────────┘               └──────────────┘

No external components required!
TMP36 connects directly to Arduino.
```

### Breadboard Layout:

```
Power Rails:
  Red (+)  → Arduino 5V → TMP36 Pin 1
  Blue (-) → Arduino GND → TMP36 Pin 3

Signal:
  TMP36 Pin 2 (Middle) → Arduino A0

Simple 3-wire connection:
  TMP36 Pin 1 (Left) → 5V
  TMP36 Pin 2 (Middle) → A0
  TMP36 Pin 3 (Right) → GND

⚠️ Verify flat side orientation!
```

### 🖼️ Circuit Diagram:
![TMP36 Circuit](Circuit.png)

---

## ⚙️ How It Works

### Temperature Sensing Process:

```
Step 1: Temperature Measurement
  Internal silicon bandgap senses temperature
  
Step 2: Voltage Generation
  On-chip amplifier converts to proportional voltage
  Output = (Temp × 10mV) + 500mV
  
Step 3: Arduino ADC Reading
  A0 pin samples voltage (0-5V range)
  10-bit ADC converts to 0-1023
  
Step 4: Voltage Calculation
  Convert ADC value back to voltage
  Voltage = (ADC / 1023) × 5V
  
Step 5: Temperature Calculation
  Apply inverse transfer function
  Temp °C = (Voltage - 0.5) × 100
  
Step 6: Unit Conversion
  Fahrenheit = (Celsius × 9/5) + 32
  Kelvin = Celsius + 273.15
  
Step 7: Serial Output
  Display all temperature units
```

### ADC (Analog-to-Digital Converter):

```
Arduino UNO ADC Specifications:
  • Resolution: 10-bit (0-1023)
  • Reference Voltage: 5V (AVCC)
  • Conversion Time: ~100μs
  • Input Range: 0V to 5V

ADC Formula:
  Digital Value = (Analog Voltage / 5V) × 1023
  
TMP36 Voltage Range Mapping:
  100mV (-40°C) → 20
  500mV (0°C) → 102
  750mV (25°C) → 153
  1000mV (50°C) → 205
  1750mV (125°C) → 358

Resolution Calculation:
  ADC step size = 5V / 1024 = 4.88mV
  Temperature resolution = 4.88mV / 10mV per °C = 0.488°C
  Practical resolution: ~0.5°C per ADC step
```

### Complete Conversion Chain:

```
Real Temperature → TMP36 Internal Circuit → Vout
        │                                      │
      25°C                                   750mV
        │                                      │
        ↓                                      ↓
Arduino A0 pin ← ← ← ← ← ← ← ← ← ← ← ← ← ← 750mV
        │
        ↓
    ADC Conversion
        │
        ↓
  Digital Value = (0.75V / 5V) × 1023 = 153
        │
        ↓
  Voltage Calculation
  Voltage = (153 / 1023) × 5V = 0.748V
        │
        ↓
  Temperature Calculation
  Temp = (0.748V - 0.5V) × 100 = 24.8°C
        │
        ↓
  Unit Conversions
  Fahrenheit = (24.8 × 9/5) + 32 = 76.64°F
  Kelvin = 24.8 + 273.15 = 297.95K
        │
        ↓
  Serial Monitor Display
```

### Mathematical Derivation:

```
Given TMP36 Transfer Function:
  Vout = (T × 0.01) + 0.5

Solve for Temperature:
  Vout = (T × 0.01) + 0.5
  Vout - 0.5 = T × 0.01
  T = (Vout - 0.5) / 0.01
  T = (Vout - 0.5) × 100

Example (25°C):
  Step 1: TMP36 outputs 750mV
  Step 2: ADC reads 153 (digital)
  Step 3: Convert to voltage: (153/1023)×5 = 0.748V
  Step 4: Calculate temp: (0.748 - 0.5) × 100 = 24.8°C
  Step 5: Convert units:
          F = (24.8 × 1.8) + 32 = 76.64°F
          K = 24.8 + 273.15 = 297.95K
```

---

## 📝 Step-by-Step Guide

### 1. **Identify TMP36 Orientation**
   ```
   Front View (Flat Side Facing You):
   ┌─────────────┐
   │  T M P 3 6  │
   │             │
   │  1   2   3  │
   └──┼───┼───┼──┘
      │   │   │
     +Vs Vout GND
   ```

### 2. **Verify Pinout**
   - **Pin 1 (Left)**: +Vs → 5V
   - **Pin 2 (Middle)**: Vout → A0
   - **Pin 3 (Right)**: GND → GND

### 3. **Connect to Arduino**
   ```
   TMP36 Pin 1 → Arduino 5V
   TMP36 Pin 2 → Arduino A0
   TMP36 Pin 3 → Arduino GND
   ```

### 4. **Safety Check**
   - Confirm flat side orientation
   - Verify no pins are shorted
   - Check 5V and GND not reversed

### 5. **Upload Code**
   - Open Arduino IDE
   - Copy code from `temperature_sensor.ino`
   - Select: **Tools > Board > Arduino UNO**
   - Select: **Tools > Port > [Your COM Port]**
   - Click **Upload**

### 6. **Open Serial Monitor**
   - Click **Tools > Serial Monitor**
   - Set baud rate to **9600**
   - Temperature readings should appear every 1 second

### 7. **Calibration Test**
   - Touch sensor gently → temperature should rise
   - Room temperature: ~20-25°C typical
   - Ice bath: ~0°C
   - Boiling water (careful!): ~100°C

---

## 💻 Code Explanation

### Full Code:

```cpp
/*
 * Project: TMP36 Temperature Sensor
 * Author: Md Akhinoor Islam
 * Description: Measure ambient temperature and convert to C, F, K
 */

const int sensorPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  
  // Convert ADC to voltage
  float voltage = sensorValue * (5.0 / 1023.0);
  
  // Convert voltage to Celsius
  float temperature = (voltage - 0.5) * 100.0;
  
  // Convert to Fahrenheit
  float fahrenheit = (temperature * 9.0 / 5.0) + 32.0;
  
  // Convert to Kelvin
  float kelvin = temperature + 273.15;
  
  // Display all units
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, ");
  Serial.print(fahrenheit);
  Serial.print(" F, ");
  Serial.print(kelvin);
  Serial.println(" K");
  
  delay(1000);
}
```

### Code Breakdown:

#### 1️⃣ **Pin Definition**
```cpp
const int sensorPin = A0;
```

| Constant | Value | Purpose |
|----------|-------|---------|
| `sensorPin` | A0 | Analog pin for TMP36 output |

#### 2️⃣ **Setup Function**
```cpp
void setup() {
  Serial.begin(9600);
}
```

**Initialization:**
- No pinMode needed (A0 is analog input by default)
- Serial communication at 9600 baud
- Runs once at startup

#### 3️⃣ **Read ADC Value**
```cpp
int sensorValue = analogRead(sensorPin);
```

**analogRead() Details:**

| Function | Returns | Range | Time |
|----------|---------|-------|------|
| `analogRead(A0)` | int | 0-1023 | ~100μs |

**Typical ADC Values:**

| Temperature | Voltage | ADC Value |
|-------------|---------|-----------|
| -40°C | 100mV | 20 |
| 0°C | 500mV | 102 |
| 25°C (room) | 750mV | 153 |
| 37°C (body) | 870mV | 178 |
| 50°C | 1000mV | 205 |
| 100°C | 1500mV | 307 |

#### 4️⃣ **Convert ADC to Voltage**
```cpp
float voltage = sensorValue * (5.0 / 1023.0);
```

**Conversion Formula:**

```
Voltage = (ADC Value / 1023) × Reference Voltage

With 5V reference:
  Voltage = (ADC / 1023) × 5.0

Example (ADC = 153):
  Voltage = (153 / 1023) × 5.0
  Voltage = 0.14955 × 5.0
  Voltage = 0.748V
```

**Why float?**
- Division produces decimal values
- Temperature requires precision
- `int` would truncate to whole numbers

#### 5️⃣ **Convert Voltage to Celsius**
```cpp
float temperature = (voltage - 0.5) * 100.0;
```

**Derivation:**

```
TMP36 Transfer Function:
  Vout = (T × 10mV) + 500mV
  Vout = (T × 0.01) + 0.5

Solve for T:
  T = (Vout - 0.5) / 0.01
  T = (Vout - 0.5) × 100

Example (Voltage = 0.748V):
  T = (0.748 - 0.5) × 100
  T = 0.248 × 100
  T = 24.8°C
```

**Step-by-Step Calculation:**

| Step | Calculation | Result |
|------|-------------|--------|
| 1 | voltage = 0.748V | |
| 2 | voltage - 0.5 = 0.248V | Remove offset |
| 3 | 0.248 × 100 = 24.8 | Scale to °C |
| 4 | temperature = 24.8°C | Final result |

#### 6️⃣ **Convert to Fahrenheit**
```cpp
float fahrenheit = (temperature * 9.0 / 5.0) + 32.0;
```

**Fahrenheit Formula:**

```
°F = (°C × 9/5) + 32
°F = (°C × 1.8) + 32

Example (25°C):
  °F = (25 × 9/5) + 32
  °F = (25 × 1.8) + 32
  °F = 45 + 32
  °F = 77°F

Common Conversions:
  0°C = 32°F (freezing)
  25°C = 77°F (room temperature)
  37°C = 98.6°F (body temperature)
  100°C = 212°F (boiling)
```

**Why 9.0 / 5.0 instead of 9/5?**
```cpp
int result1 = 9 / 5;      // Integer division → 1 (wrong!)
float result2 = 9.0 / 5.0; // Float division → 1.8 (correct!)
```

#### 7️⃣ **Convert to Kelvin**
```cpp
float kelvin = temperature + 273.15;
```

**Kelvin Formula:**

```
K = °C + 273.15

Example (25°C):
  K = 25 + 273.15
  K = 298.15K

Key Points:
  0°C = 273.15K (absolute zero at -273.15°C)
  Kelvin has no negative values
  1K = 1°C (same degree size)
```

#### 8️⃣ **Serial Output**
```cpp
Serial.print("Temperature: ");
Serial.print(temperature);
Serial.print(" C, ");
Serial.print(fahrenheit);
Serial.print(" F, ");
Serial.print(kelvin);
Serial.println(" K");
```

**Output Format:**
```
Temperature: 24.80 C, 76.64 F, 297.95 K
Temperature: 24.85 C, 76.73 F, 298.00 K
Temperature: 24.78 C, 76.60 F, 297.93 K
```

**Formatted Output (with precision control):**

```cpp
// Show 2 decimal places
Serial.print(temperature, 2);  // 24.80

// Show 1 decimal place
Serial.print(temperature, 1);  // 24.8

// Integer only
Serial.print((int)temperature);  // 24
```

#### 9️⃣ **Delay**
```cpp
delay(1000);
```

**Sampling Rate:**

| Delay (ms) | Samples/sec | Use Case |
|-----------|-------------|----------|
| 100 | 10 | Fast monitoring |
| 500 | 2 | Standard |
| 1000 | 1 | Slow changes (temperature) |
| 5000 | 0.2 | Data logging |

---

### Advanced Code Examples:

#### **Temperature Threshold Alert:**
```cpp
const float TEMP_THRESHOLD = 30.0;  // 30°C warning

void loop() {
  int sensorValue = analogRead(sensorPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100.0;
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C - ");
  
  if (temperature > TEMP_THRESHOLD) {
    Serial.println("⚠ HIGH TEMPERATURE WARNING!");
  } else {
    Serial.println("✓ Normal");
  }
  
  delay(1000);
}
```

#### **LED Indicator (Temperature Zones):**
```cpp
const int greenLED = 11;
const int yellowLED = 12;
const int redLED = 13;

void setup() {
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100.0;
  
  // Temperature zones
  if (temperature < 20) {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);  // Too cold
  } else if (temperature >= 20 && temperature <= 30) {
    digitalWrite(greenLED, HIGH);  // Comfortable
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
  } else {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);  // Too hot
    digitalWrite(redLED, LOW);
  }
  
  Serial.print(temperature);
  Serial.println(" C");
  delay(1000);
}
```

#### **Smoothed Reading (Noise Reduction):**
```cpp
const int numReadings = 10;
float readings[numReadings];
int readIndex = 0;
float total = 0;
float average = 0;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100.0;
  
  // Moving average
  total = total - readings[readIndex];
  readings[readIndex] = temperature;
  total = total + readings[readIndex];
  readIndex = (readIndex + 1) % numReadings;
  average = total / numReadings;
  
  Serial.print("Current: ");
  Serial.print(temperature);
  Serial.print(" C, Average: ");
  Serial.print(average);
  Serial.println(" C");
  
  delay(500);
}
```

---

## 🌐 Simulation

### Try it Online:
🔗 **[View on Tinkercad](https://www.tinkercad.com/things/8MxH29I8SaW-11-temperaturesensor)**

Features:
- Adjustable temperature slider
- Real-time conversion to C, F, K
- Voltage output visualization
- Test calculation formulas

---

## 🔧 Troubleshooting

### Common Issues:

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| Reading always -40°C | TMP36 reversed | Flip sensor 180° (flat side facing you) |
| Reading always 125°C | Power/GND shorted | Check connections, replace sensor |
| Unstable readings | Loose wires | Secure breadboard connections |
| Wrong temperature | Incorrect formula | Verify: `(voltage - 0.5) × 100` |
| No serial output | Baud rate mismatch | Set Serial Monitor to 9600 |
| Reading too high/low | Bad sensor | Test with known temperature (ice/boiling water) |

### Calibration Test:

```cpp
// Calibration verification
void calibrate() {
  Serial.println("Calibration Test:");
  Serial.println("Place sensor in ice water (0°C)...");
  delay(5000);
  
  int sensorValue = analogRead(sensorPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100.0;
  
  Serial.print("Ice water reading: ");
  Serial.print(temperature);
  Serial.println(" C (should be ~0°C)");
  
  Serial.println("\nPlace sensor in room temperature...");
  delay(5000);
  
  sensorValue = analogRead(sensorPin);
  voltage = sensorValue * (5.0 / 1023.0);
  temperature = (voltage - 0.5) * 100.0;
  
  Serial.print("Room temp reading: ");
  Serial.print(temperature);
  Serial.println(" C (should be ~20-25°C)");
}
```

### Accuracy Improvement:

```cpp
// Use internal 1.1V reference for better resolution
void setup() {
  analogReference(INTERNAL);  // 1.1V reference
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  // Recalculate with 1.1V reference
  float voltage = sensorValue * (1.1 / 1023.0);
  float temperature = (voltage - 0.5) * 100.0;
  
  Serial.print(temperature);
  Serial.println(" C");
  delay(1000);
}
```

---

## 🎓 Learning Outcomes

### 📚 Concepts Covered:

| Concept | Description | Applications |
|---------|-------------|--------------|
| **Analog Sensors** | Voltage-based measurement | All analog sensors |
| **ADC** | Digital conversion | Data acquisition |
| **Transfer Functions** | Sensor output equations | Calibration |
| **Unit Conversion** | Temperature scales | Scientific applications |
| **Floating Point** | Decimal precision | Accurate calculations |

### 🚀 Skills Gained:
- ✅ Understanding TMP36 operation
- ✅ ADC voltage calculation
- ✅ Mathematical conversions (C/F/K)
- ✅ Floating-point arithmetic
- ✅ Sensor calibration techniques
- ✅ Real-time environmental monitoring

### 🔄 Project Extensions:

1. **HVAC Controller** - Automatic fan control
2. **Data Logger** - SD card temperature recording
3. **LCD Display** - Show temperature on 16×2 LCD
4. **Temperature Alarm** - Buzzer at threshold
5. **Multi-sensor Network** - Compare multiple locations
6. **Web Server** - Send data to IoT platform
7. **PID Control** - Precision temperature regulation

---

## 📁 Project Files

| File | Description |
|------|-------------|
| `README.md` | Complete project documentation |
| `temperature_sensor.ino` | Arduino source code |
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
- Add multi-sensor averaging
- Implement data logging
- Create temperature alerts
- Add LCD/OLED display
- Share your temperature monitoring projects!

---

## ⭐ Show Your Support

If this helped you understand temperature sensors, give it a ⭐!

---

### 📌 Real-World Applications:

- 🌡️ **HVAC Systems** - Automatic climate control
- 🏭 **Industrial Monitoring** - Process temperature tracking
- 🔬 **Laboratory Equipment** - Incubators, freezers
- 🚗 **Automotive** - Engine temperature monitoring
- 🌾 **Agriculture** - Greenhouse automation
- 💻 **Computer Cooling** - Fan speed control
- 🏠 **Smart Home** - Thermostat control
- ⚗️ **Chemical Processes** - Reaction temperature

Happy Sensing! 🎉
