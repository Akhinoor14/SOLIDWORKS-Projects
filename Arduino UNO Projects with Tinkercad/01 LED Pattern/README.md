# 💡 LED Pattern Project with Potentiometer Control

![Arduino Project](https://img.shields.io/badge/Arduino-UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Beginner-green?style=for-the-badge)

## 📋 Table of Contents
- [Overview](#-overview)
- [Components Required](#-components-required)
- [Circuit Diagram](#-circuit-diagram)
- [How It Works](#-how-it-works)
- [Step-by-Step Guide](#-step-by-step-guide)
- [Code Explanation](#-code-explanation)
- [Simulation](#-simulation)
- [Troubleshooting](#-troubleshooting)
- [Learning Outcomes](#-learning-outcomes)
- [Project Files](#-project-files)
- [Author](#-author)

---

## 🎯 Overview

This project demonstrates how to control the blinking pattern of 5 LEDs using a potentiometer. As you rotate the potentiometer, different numbers of LEDs light up based on the analog voltage level detected by the Arduino. This is a perfect beginner project to learn about analog input, digital output, and conditional logic in Arduino programming.

### Key Features:
- ✅ Real-time analog to digital conversion (ADC)
- ✅ Dynamic LED control based on voltage thresholds
- ✅ Serial Monitor debugging support
- ✅ Visual feedback system with 5 distinct voltage zones
- ✅ Hands-on learning of potentiometer interfacing

---

## 🧰 Components Required

| Component | Quantity | Specification |
|-----------|----------|---------------|
| Arduino UNO | 1 | ATmega328P based |
| Breadboard | 1 | Full-size or half-size |
| LED (Any color) | 5 | 5mm standard |
| Resistor | 5 | 220Ω (Red-Red-Brown) |
| Potentiometer | 1 | 10kΩ (B10K) |
| Jumper Wires | 15-20 | Male-to-Male |

### 💰 Estimated Cost: $8-12 USD

---

## 🔌 Circuit Diagram

### Connection Table:

#### Potentiometer Connections:
| Potentiometer Pin | Arduino Pin | Description |
|-------------------|-------------|-------------|
| Terminal 1 | 5V | Power supply |
| Wiper (Middle) | A0 | Analog input |
| Terminal 2 | GND | Ground |

#### LED Connections:
| LED Number | Arduino Pin | Notes |
|------------|-------------|-------|
| LED 1 | D2 | Through 220Ω resistor |
| LED 2 | D3 | Through 220Ω resistor |
| LED 3 | D4 | Through 220Ω resistor |
| LED 4 | D5 | Through 220Ω resistor |
| LED 5 | D6 | Through 220Ω resistor |

**All LED cathodes (shorter leg) connect to GND rail on breadboard**

### 🖼️ Circuit Diagram:
![LED Pattern Circuit](circuit.png)

---

## ⚙️ How It Works

The project operates on a simple principle of **analog voltage division and threshold detection**:

1. **Potentiometer Function**: 
   - When you rotate the potentiometer, it acts as a variable voltage divider
   - Output voltage varies from 0V to 5V

2. **Analog Reading**:
   - Arduino's A0 pin reads this voltage
   - `analogRead()` converts it to a digital value (0-1023)
   - 0 = 0V, 1023 = 5V

3. **LED Control Logic**:
   - The code divides the 0-1023 range into 5 zones
   - Each zone activates a specific number of LEDs
   
### Voltage Zones:

| Potentiometer Value | Voltage Range | LEDs ON | Behavior |
|---------------------|---------------|---------|----------|
| 0 - 199 | 0V - 0.97V | 1 LED | Only LED 1 glows |
| 200 - 399 | 0.98V - 1.95V | 2 LEDs | LED 1 & 2 glow |
| 400 - 599 | 1.96V - 2.93V | 3 LEDs | LED 1, 2 & 3 glow |
| 600 - 799 | 2.94V - 3.91V | 4 LEDs | LED 1, 2, 3 & 4 glow |
| 800 - 1023 | 3.92V - 5V | 5 LEDs | All LEDs glow |

---

## 📝 Step-by-Step Guide

### 1. **Prepare the Breadboard**
   - Place Arduino UNO next to breadboard
   - Connect Arduino's 5V to breadboard's positive (+) rail
   - Connect Arduino's GND to breadboard's negative (-) rail

### 2. **Insert Potentiometer**
   - Place potentiometer in breadboard
   - Connect left pin to 5V rail
   - Connect right pin to GND rail
   - Connect middle pin (wiper) to Arduino A0 using jumper wire

### 3. **Place LEDs**
   - Insert 5 LEDs in breadboard with proper polarity
   - **Long leg (Anode)** → will connect to Arduino pins through resistors
   - **Short leg (Cathode)** → connect to GND rail

### 4. **Add Resistors**
   - Connect a 220Ω resistor from each LED's anode
   - Other end of resistors connect to Arduino pins D2, D3, D4, D5, D6

### 5. **Upload Code**
   - Open Arduino IDE
   - Copy the code from `Led-pattern.ino`
   - Select correct board: **Tools > Board > Arduino UNO**
   - Select correct port: **Tools > Port > COM X**
   - Click Upload button

### 6. **Test the Project**
   - Open Serial Monitor (Tools > Serial Monitor) or Ctrl+Shift+M
   - Set baud rate to 9600
   - Rotate potentiometer slowly
   - Observe LED patterns change
   - Watch analog values in Serial Monitor

---

## 💻 Code Explanation

### Full Code Structure:

```cpp
/*
 * Project: LED Pattern Project with Potentiometer
 * Author: Md. Akhinoor Islam
 * Description: Control 5 LEDs based on potentiometer voltage
 */

const int potPin = A0;              // Potentiometer connected to analog pin A0
const int leds[] = {2, 3, 4, 5, 6}; // Array holding LED pins

void setup() {
  // Initialize all LED pins as outputs
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT);
  }
  Serial.begin(9600); // Start serial communication for debugging
}

void loop() {
  int potValue = analogRead(potPin); // Read analog value (0-1023)
  Serial.println(potValue);          // Display value in Serial Monitor

  // Control LEDs based on voltage zones
  if (potValue < 200) {
    digitalWrite(leds[0], HIGH);
    for (int i = 1; i < 5; i++) digitalWrite(leds[i], LOW);
  } 
  else if (potValue < 400) {
    for (int i = 0; i < 2; i++) digitalWrite(leds[i], HIGH);
    for (int i = 2; i < 5; i++) digitalWrite(leds[i], LOW);
  } 
  else if (potValue < 600) {
    for (int i = 0; i < 3; i++) digitalWrite(leds[i], HIGH);
    for (int i = 3; i < 5; i++) digitalWrite(leds[i], LOW);
  } 
  else if (potValue < 800) {
    for (int i = 0; i < 4; i++) digitalWrite(leds[i], HIGH);
    digitalWrite(leds[4], LOW);
  } 
  else {
    for (int i = 0; i < 5; i++) digitalWrite(leds[i], HIGH);
  }

  delay(300); // Small delay for stability
}
```

### Key Functions Explained:

- **`analogRead(potPin)`**: Reads voltage from A0, returns 0-1023
- **`digitalWrite(pin, HIGH/LOW)`**: Turns LED on or off
- **`Serial.println()`**: Prints data to Serial Monitor for debugging
- **`pinMode(pin, OUTPUT)`**: Configures pin as output
- **`delay(300)`**: Waits 300 milliseconds

---

## 🌐 Simulation

### Try it Online:
🔗 **[View on Tinkercad](https://www.tinkercad.com/things/c3b3O8IGfQV-01-led-pattern)**

You can simulate this entire project online without any hardware! Click the link above to:
- Interact with the virtual circuit
- Modify the code
- See real-time results
- Learn at your own pace

---

## 🔧 Troubleshooting

### Common Issues and Solutions:

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| LEDs not lighting up | Incorrect polarity | Check LED orientation (long leg to resistor) |
| All LEDs always on | Potentiometer not connected | Verify A0 connection to middle pin |
| Erratic behavior | Loose connections | Press jumper wires firmly |
| No Serial Monitor output | Wrong baud rate | Set to 9600 in Serial Monitor |
| Random LED patterns | Floating pin | Check potentiometer connections to 5V and GND |
| Arduino not detected | Driver issue | Install CH340 or FTDI drivers |

### 📌 Pro Tips:
- Use different colored LEDs for better visual effect
- Keep wires organized and short
- Double-check polarity before powering up
- Use the Serial Monitor to debug voltage values
- Take a photo of your working circuit!

---

## 🎓 Learning Outcomes

After completing this project, you will understand:

### 📚 Concepts Covered:
- ✅ **Analog Input**: Reading variable voltage with `analogRead()`
- ✅ **Digital Output**: Controlling LEDs with `digitalWrite()`
- ✅ **Conditional Logic**: Using `if-else` statements for decision making
- ✅ **Arrays**: Storing multiple pin numbers efficiently
- ✅ **Loops**: Iterating through arrays with `for` loops
- ✅ **Serial Communication**: Debugging with Serial Monitor
- ✅ **Voltage Division**: How potentiometers work
- ✅ **Threshold Detection**: Dividing analog range into zones

### 🚀 Skills Gained:
- Reading datasheets for components
- Building circuits on breadboard
- Writing structured Arduino code
- Debugging hardware and software issues
- Understanding analog vs digital signals

---

## 📁 Project Files

This repository contains:

| File | Description |
|------|-------------|
| `README.md` | Complete project documentation (this file) |
| `Led-pattern.ino` | Arduino source code |
| `Code Explaination (for beginner).md` | Detailed Bengali tutorial for beginners |
| `circuit.png` | Circuit diagram screenshot |
| `LICENSE` | MIT License |

---

## 👨‍🎓 Author

**Md. Akhinoor Islam**  
📚 Energy Science and Engineering (ESE)  
🏫 Khulna University of Engineering & Technology (KUET)  
🌐 [GitHub Profile](https://github.com/Akhinoor14)

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 🤝 Contributing

Found an issue or want to improve this project? Feel free to:
- Open an issue
- Submit a pull request
- Share your modifications

---

## ⭐ Show Your Support

If this project helped you learn something new, please consider giving it a ⭐ on GitHub!

---

### 📌 Next Steps:
- Try adding more LEDs
- Create different blinking patterns
- Add an LCD display to show voltage values
- Control LED brightness using PWM

Happy Learning! 🎉
