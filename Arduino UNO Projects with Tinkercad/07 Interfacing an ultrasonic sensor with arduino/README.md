# 📡 Ultrasonic Distance Sensor with Arduino

![Arduino Project](https://img.shields.io/badge/Arduino-UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Beginner-green?style=for-the-badge)
![Sensor](https://img.shields.io/badge/HC--SR04-Ultrasonic-blue?style=for-the-badge)

## 📋 Table of Contents
- [Overview](#-overview)
- [Components Required](#-components-required)
- [HC-SR04 Sensor Basics](#-hc-sr04-sensor-basics)
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

This project demonstrates **distance measurement** using the **HC-SR04 ultrasonic sensor** with Arduino UNO. The sensor uses sound waves to calculate the distance to an object, displaying results via Serial Monitor. This is fundamental for robotics obstacle avoidance, parking sensors, liquid level detection, and automation systems.

### Key Features:
- ✅ Non-contact distance measurement (2cm - 400cm)
- ✅ Uses ultrasonic sound waves (40 kHz)
- ✅ Time-of-flight calculation
- ✅ Accurate to ±3mm
- ✅ Real-time serial output
- ✅ Foundation for autonomous robots and smart systems

---

## 🧰 Components Required

| Component | Quantity | Specification |
|-----------|----------|---------------|
| Arduino UNO | 1 | ATmega328P based |
| HC-SR04 Ultrasonic Sensor | 1 | 2cm - 400cm range |
| Breadboard | 1 | For stable connections |
| Jumper Wires | 4 | Male-to-Male |
| USB Cable | 1 | For programming & serial monitor |

### 💰 Estimated Cost: $5-8 USD

---

## 🔬 HC-SR04 Sensor Basics

### What is an Ultrasonic Sensor?

An **ultrasonic sensor** measures distance by emitting **high-frequency sound waves** (above human hearing range) and measuring the time it takes for the echo to return.

### HC-SR04 Specifications:

| Parameter | Value |
|-----------|-------|
| Operating Voltage | 5V DC |
| Operating Current | 15mA |
| Operating Frequency | 40 kHz |
| Measuring Range | 2cm - 400cm (0.8in - 157in) |
| Accuracy | ±3mm |
| Measuring Angle | 15° cone |
| Trigger Input | 10μs TTL pulse |
| Echo Output | TTL pulse proportional to distance |
| Dimensions | 45mm × 20mm × 15mm |

### Sensor Pinout:

```
HC-SR04 Ultrasonic Sensor
┌─────────────────────────────┐
│   ┌───┐           ┌───┐     │
│   │ T │           │ R │     │  T = Transmitter (Speaker)
│   └───┘           └───┘     │  R = Receiver (Microphone)
│                              │
│  VCC  TRIG  ECHO  GND       │
│   │    │     │     │        │
└───┼────┼─────┼─────┼────────┘
    │    │     │     │
    5V   D9   D10   GND
```

### Pin Functions:

| Pin | Function | Description |
|-----|----------|-------------|
| **VCC** | Power | 5V supply |
| **GND** | Ground | 0V reference |
| **TRIG** | Trigger Input | Receives 10μs pulse to start measurement |
| **ECHO** | Echo Output | Sends HIGH pulse with duration = 2 × distance/speed |

### How Ultrasonic Ranging Works:

```
Physics of Sound:
┌──────────────────────────────────┐
│ Speed of Sound (20°C):           │
│   343 m/s = 34300 cm/s           │
│   = 0.0343 cm/μs                 │
│   = 0.034 cm/μs (rounded)        │
└──────────────────────────────────┘

Time-of-Flight Measurement:
  Sensor → Sound Wave → Object → Echo → Sensor
  |←─────── Distance ─────→|←──── Distance ────→|
            (forward)              (return)
  
  Total Time = 2 × Distance / Speed of Sound
  
  Distance = (Total Time × Speed of Sound) / 2
  Distance (cm) = (Duration in μs × 0.034) / 2
```

### Measurement Process:

```
Step 1: Trigger Pulse
Arduino sends 10μs HIGH pulse to TRIG pin

Step 2: Sensor Emits Ultrasound
HC-SR04 sends 8 burst pulses at 40 kHz
┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐ ┌─┐
│ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
└─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘ └─┘
 1  2  3  4  5  6  7  8  (bursts)

Step 3: Sound Travels to Object
40 kHz ultrasonic waves travel at 343 m/s

Step 4: Echo Returns
Sound reflects off object and returns

Step 5: Echo Pulse
ECHO pin goes HIGH for duration proportional to distance

Step 6: Arduino Measures Duration
pulseIn() measures how long ECHO stays HIGH

Step 7: Calculate Distance
Distance = Duration × 0.034 / 2
```

---

## 🔌 Circuit Diagram

### Connection Table:

| HC-SR04 Pin | Arduino Pin | Description |
|-------------|-------------|-------------|
| VCC | 5V | Power supply |
| TRIG | D9 | Trigger input (send 10μs pulse) |
| ECHO | D10 | Echo output (receive timing pulse) |
| GND | GND | Ground |

### Circuit Wiring:

```
Arduino UNO                    HC-SR04 Sensor
┌─────────────┐               ┌──────────────┐
│             │               │  ┌───┐ ┌───┐ │
│   5V  ●─────┼───────────────┤  │ T │ │ R │ │
│             │               │  └───┘ └───┘ │
│  GND  ●─────┼───────────────┤              │
│             │               │ VCC TRIG ECHO│
│   D9  ●─────┼───────────────┤  │   │   │  │
│             │               │  5V  D9  D10 │
│  D10  ●─────┼───────────────┤     GND      │
│             │               └──────────────┘
└─────────────┘

Trigger: D9 sends 10μs pulse
Echo: D10 receives timing pulse
```

### 🖼️ Circuit Diagram:
![Ultrasonic Distance Sensor Circuit](Circuit.png)

### Breadboard Layout:

```
Power Rails:
  Red (+) → Arduino 5V
  Blue (-) → Arduino GND

HC-SR04 Connections:
  Pin 1 (VCC)  → Red rail (+5V)
  Pin 2 (TRIG) → Arduino D9
  Pin 3 (ECHO) → Arduino D10
  Pin 4 (GND)  → Blue rail (GND)
```

---

## ⚙️ How It Works

### Distance Calculation Math:

```
Given:
  Speed of Sound = 343 m/s (at 20°C)
  = 34300 cm/s
  = 0.0343 cm/μs
  ≈ 0.034 cm/μs (simplified)

Formula Derivation:
  Distance = Speed × Time
  
  But sound travels TO object and BACK:
  Total Distance = Speed × Total Time
  Actual Distance = (Speed × Total Time) / 2
  
  Distance (cm) = (0.034 cm/μs × Duration μs) / 2
  Distance (cm) = Duration × 0.034 / 2
  Distance (cm) = Duration × 0.017

  Or keeping clarity:
  Distance (cm) = (Duration × 0.034) / 2
```

### Example Calculation:

```
Scenario: Object at 30 cm distance

Sound Travel:
  Forward:  30 cm ÷ 0.034 cm/μs = 882 μs
  Return:   30 cm ÷ 0.034 cm/μs = 882 μs
  Total:    1764 μs

Arduino Measurement:
  pulseIn() reads: 1764 μs
  
  Distance = 1764 × 0.034 / 2
           = 59.976 / 2
           = 29.988 cm
           ≈ 30 cm ✓
```

### Timing Diagram:

```
TRIG Pin (Arduino D9):
     10μs
  ┌──────┐
  │      │
──┘      └─────────────────────────────────────

ECHO Pin (HC-SR04):
                Proportional to Distance
          ┌───────────────────────┐
          │    pulseIn() reads    │
──────────┘                       └────────────

Time:  0μs   10μs              Variable

Process:
  t=0:    Arduino sends TRIG pulse
  t=10:   TRIG pulse ends
  t=~200: Sensor emits 8 ultrasonic bursts
  t=~200: ECHO pin goes HIGH
  t=~200+X: Sound returns, ECHO goes LOW
  X = time proportional to distance
```

### Distance vs Time Table:

| Distance (cm) | Round Trip Time (μs) | ECHO Pulse Width (μs) |
|--------------|----------------------|-----------------------|
| 5 | 294 | 294 |
| 10 | 588 | 588 |
| 20 | 1,176 | 1,176 |
| 50 | 2,941 | 2,941 |
| 100 | 5,882 | 5,882 |
| 200 | 11,765 | 11,765 |
| 400 | 23,529 | 23,529 |

### Temperature Effect:

Speed of sound varies with temperature:

| Temperature (°C) | Speed of Sound (m/s) | Correction Factor |
|------------------|---------------------|-------------------|
| 0°C | 331 | 0.0331 |
| 10°C | 337 | 0.0337 |
| 20°C | 343 | 0.0343 |
| 30°C | 349 | 0.0349 |
| 40°C | 355 | 0.0355 |

For higher accuracy, measure temperature and adjust calculation.

---

## 📝 Step-by-Step Guide

### 1. **Identify Sensor Pins**
   - Look at the HC-SR04 front
   - **VCC** = Leftmost pin (power)
   - **TRIG** = Second pin (trigger input)
   - **ECHO** = Third pin (echo output)
   - **GND** = Rightmost pin (ground)

### 2. **Connect Power**
   ```
   HC-SR04 VCC → Arduino 5V
   HC-SR04 GND → Arduino GND
   ```
   - Sensor requires stable 5V supply
   - Check voltage with multimeter if available

### 3. **Connect Signal Pins**
   ```
   HC-SR04 TRIG → Arduino D9
   HC-SR04 ECHO → Arduino D10
   ```
   - Can use other digital pins if needed
   - Update pin numbers in code accordingly

### 4. **Secure Connections**
   - Use breadboard for stable wiring
   - Ensure no loose connections
   - Keep wires short to reduce noise

### 5. **Upload Code**
   - Open Arduino IDE
   - Copy code from `ultrasonic-distance.ino`
   - Select: **Tools > Board > Arduino UNO**
   - Select: **Tools > Port > [Your COM Port]**
   - Click **Upload**

### 6. **Open Serial Monitor**
   - Click **Tools > Serial Monitor**
   - Set baud rate to **9600**
   - Distance readings should appear every 500ms

### 7. **Test Measurements**
   - Place hand in front of sensor
   - Move closer/farther
   - Observe distance changes in Serial Monitor

---

## 💻 Code Explanation

### Full Code:

```cpp
/*
 * Project: Ultrasonic Distance Measurement
 * Author: Md. Akhinoor Islam
 * Description: HC-SR04 sensor measures distance and displays via serial
 */

// Pin Definitions
const int trigPin = 9;   // Trigger pin connected to D9
const int echoPin = 10;  // Echo pin connected to D10

// Variables
long duration;     // Time for echo pulse
int distance;      // Calculated distance in cm

void setup() {
  pinMode(trigPin, OUTPUT);  // Set trigger pin as output
  pinMode(echoPin, INPUT);   // Set echo pin as input
  Serial.begin(9600);        // Initialize serial communication
}

void loop() {
  // Clear trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Send 10μs trigger pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read echo pulse duration
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance
  distance = duration * 0.034 / 2;
  
  // Display results
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(500);  // Wait 500ms before next measurement
}
```

### Code Breakdown:

#### 1️⃣ **Pin Definitions**
```cpp
const int trigPin = 9;
const int echoPin = 10;
```

| Variable | Purpose | Pin |
|----------|---------|-----|
| `trigPin` | Send trigger pulse | D9 |
| `echoPin` | Receive echo pulse | D10 |
| `const int` | Cannot be changed | Safety |

#### 2️⃣ **Variable Declarations**
```cpp
long duration;
int distance;
```

| Variable | Type | Purpose | Range |
|----------|------|---------|-------|
| `duration` | long | Stores pulse duration in μs | 0 - 38,000 |
| `distance` | int | Calculated distance in cm | 0 - 400 |

**Why `long` for duration?**
- Maximum measurable time: ~23,529 μs (for 400cm)
- `int` can only hold up to 32,767 (sufficient)
- But `long` is safer for longer ranges

#### 3️⃣ **Setup Function**
```cpp
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}
```

**Pin Mode Configuration:**

| Pin | Mode | Reason |
|-----|------|--------|
| trigPin (D9) | OUTPUT | Arduino sends pulse to sensor |
| echoPin (D10) | INPUT | Arduino receives pulse from sensor |

**Serial Communication:**
```cpp
Serial.begin(9600);
```
- Initializes serial communication at 9600 baud
- Allows data transfer to computer
- View data in Serial Monitor

#### 4️⃣ **Clear Trigger Pin**
```cpp
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
```

**Purpose:**
- Ensures trigger pin starts LOW
- Provides clean transition before pulse
- Prevents false triggers

**Timing:**
```
Before:  ─────── (may be HIGH or LOW)
After:   ──────┘ (guaranteed LOW)
Wait 2μs for stability
```

#### 5️⃣ **Send Trigger Pulse**
```cpp
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
```

**Creates 10μs pulse:**
```
TRIG Pin:
           10μs
      ┌──────────┐
──────┘          └────────
      ↑          ↑
    HIGH        LOW
```

**Why exactly 10μs?**
- HC-SR04 datasheet requirement
- Less than 10μs: May not trigger
- More than 10μs: Works but wastes time

#### 6️⃣ **Read Echo Pulse**
```cpp
duration = pulseIn(echoPin, HIGH);
```

**`pulseIn()` Function:**

| Parameter | Value | Purpose |
|-----------|-------|---------|
| Pin | echoPin (D10) | Which pin to monitor |
| State | HIGH | Wait for HIGH pulse |
| Timeout | 1 second (default) | Prevent infinite wait |
| Return | Pulse width in μs | Duration measurement |

**How pulseIn() Works:**
```
ECHO Pin:
          ┌─────────────────┐
──────────┘                 └──────
          ↑                 ↑
        Starts              Stops
        Timer               Timer
        
pulseIn() measures this duration
```

**Return Values:**

| Scenario | Duration (μs) | Distance (cm) |
|----------|---------------|---------------|
| No object / too far | 0 (timeout) | 0 |
| Object at 5cm | ~294 | 5 |
| Object at 100cm | ~5,882 | 100 |
| Object at 400cm | ~23,529 | 400 |

#### 7️⃣ **Calculate Distance**
```cpp
distance = duration * 0.034 / 2;
```

**Formula Breakdown:**

```
Step 1: Speed of sound conversion
  343 m/s = 34300 cm/s = 0.0343 cm/μs ≈ 0.034 cm/μs

Step 2: Distance = Speed × Time
  Distance = 0.034 cm/μs × duration μs
  Distance = 0.034 × duration cm

Step 3: Divide by 2 (round trip)
  Actual Distance = (0.034 × duration) / 2
```

**Example Calculations:**

| Duration (μs) | Calculation | Distance (cm) |
|--------------|-------------|---------------|
| 294 | 294 × 0.034 / 2 | 5 |
| 588 | 588 × 0.034 / 2 | 10 |
| 1,176 | 1,176 × 0.034 / 2 | 20 |
| 2,941 | 2,941 × 0.034 / 2 | 50 |
| 5,882 | 5,882 × 0.034 / 2 | 100 |

**Alternative Formula (inches):**
```cpp
distance_inch = duration * 0.0133 / 2;
// 343 m/s = 13503 in/s = 0.0133 in/μs
```

#### 8️⃣ **Display Results**
```cpp
Serial.print("Distance: ");
Serial.print(distance);
Serial.println(" cm");
```

**Serial Output Format:**
```
Distance: 5 cm
Distance: 10 cm
Distance: 23 cm
Distance: 47 cm
```

**Different Display Options:**

```cpp
// Option 1: Basic
Serial.println(distance);

// Option 2: With label
Serial.print("Distance: ");
Serial.println(distance);

// Option 3: Formatted (like in code)
Serial.print("Distance: ");
Serial.print(distance);
Serial.println(" cm");

// Option 4: Multiple units
Serial.print(distance);
Serial.print(" cm = ");
Serial.print(distance / 2.54);
Serial.println(" inches");

// Option 5: CSV format (for plotting)
Serial.println(distance);
```

#### 9️⃣ **Measurement Delay**
```cpp
delay(500);
```

**Why 500ms delay?**
- Gives readable serial output
- Prevents sensor overheating
- Reduces serial buffer overflow

**Different Delays:**

| Delay (ms) | Measurements/sec | Use Case |
|-----------|------------------|----------|
| 50 | 20 | Fast tracking |
| 100 | 10 | Standard robotics |
| 500 | 2 | Human-readable display |
| 1000 | 1 | Slow monitoring |

---

## 🌐 Simulation

### Try it Online:
🔗 **[View on Tinkercad](https://www.tinkercad.com/things/8ovpJIUXiQG-07-interfacing-an-ultrasonic-sensor-with-arduino)**

Features:
- Interactive distance slider
- Real-time serial output
- Visualize echo timing
- Test different distances

---

## 🔧 Troubleshooting

### Common Issues:

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| Always shows 0 cm | Wiring error | Check: VCC=5V, GND=GND, TRIG=D9, ECHO=D10 |
| Erratic readings | Loose connections | Secure all wires, use breadboard |
| Constant maximum value | No echo received | Check sensor orientation, remove obstacles |
| No serial output | Wrong baud rate | Set Serial Monitor to 9600 |
| Readings jump randomly | Electrical noise | Add 0.1μF capacitor across VCC-GND |
| Short range only | Weak ultrasound | Check if sensor is blocked/damaged |
| Won't measure close objects | < 2cm limitation | HC-SR04 minimum range is 2cm |

### Accuracy Issues:

**Factors Affecting Accuracy:**

| Factor | Effect | Solution |
|--------|--------|----------|
| **Temperature** | Speed of sound varies | Measure temp, adjust calculation |
| **Humidity** | Slight speed change | Usually negligible (<1%) |
| **Air pressure** | Minor effect | Ignore for most applications |
| **Soft surfaces** | Weak echo | Use hard, flat reflective surfaces |
| **Angled surfaces** | Echo deflects away | Keep sensor perpendicular |
| **Small objects** | Miss detection | Object must be larger than cone |

### Advanced Debugging Code:

```cpp
const int trigPin = 9;
const int echoPin = 10;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  Serial.println("Ultrasonic Sensor Debug");
  Serial.println("Duration(μs) | Distance(cm)");
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, 30000);  // 30ms timeout
  
  if (duration == 0) {
    Serial.println("Timeout - No echo received");
  } else {
    int distance = duration * 0.034 / 2;
    
    Serial.print(duration);
    Serial.print("μs | ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  
  delay(500);
}
```

### Filtering Noisy Readings:

```cpp
// Moving Average Filter
const int numReadings = 10;
int readings[numReadings];
int readIndex = 0;
int total = 0;

int getFilteredDistance() {
  total = total - readings[readIndex];
  readings[readIndex] = measureDistance();
  total = total + readings[readIndex];
  readIndex = (readIndex + 1) % numReadings;
  return total / numReadings;
}
```

---

## 🎓 Learning Outcomes

### 📚 Concepts Covered:

| Concept | Description | Applications |
|---------|-------------|--------------|
| **Ultrasonic Sensors** | Sound-based distance measurement | Robotics, automation, level sensing |
| **Time-of-Flight** | Measuring time for signal return | Radar, lidar, distance sensors |
| **pulseIn() Function** | Measuring pulse duration | Any timing measurement |
| **Serial Communication** | Arduino to computer data transfer | Debugging, data logging |
| **Unit Conversion** | Time to distance calculation | Physics applications |

### 🚀 Skills Gained:
- ✅ Understanding ultrasonic sensing principles
- ✅ Time-of-flight distance calculation
- ✅ Using pulseIn() for precise timing
- ✅ Serial Monitor for data visualization
- ✅ Sensor interfacing and debugging
- ✅ Foundation for autonomous systems

### 🔄 Project Extensions:

1. **Parking Sensor** - LED/buzzer alerts for proximity
2. **Obstacle Avoidance Robot** - Navigate around objects
3. **Water Level Monitor** - Tank level measurement
4. **Automatic Door** - Open when person approaches
5. **Distance-Based LED Bar** - Visual distance indicator
6. **Multiple Sensors** - 360° detection array
7. **Data Logging** - SD card storage of measurements

---

## 📁 Project Files

| File | Description |
|------|-------------|
| `README.md` | Complete project documentation |
| `ultrasonic-distance.ino` | Arduino source code |
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

Enhance this project:
- Add temperature compensation
- Implement median filtering
- Create LCD display version
- Add multiple sensor support
- Share your distance measurement projects!

---

## ⭐ Show Your Support

If this helped you understand ultrasonic sensors, give it a ⭐!

---

### 📌 Real-World Applications:

- 🤖 **Autonomous Robots** - Obstacle detection and avoidance
- 🚗 **Parking Sensors** - Vehicle proximity warnings
- 🏭 **Industrial Automation** - Object detection on conveyors
- 💧 **Level Sensing** - Tank and silo monitoring
- 🚪 **Automatic Doors** - Presence detection
- 📏 **Measurement Tools** - Digital tape measure
- 🔒 **Security Systems** - Perimeter monitoring

Happy Sensing! 🎉
