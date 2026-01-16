# 🔌 Circuit Connections – TMP36 + ATtiny85 + RGB LED (5-Color Logic)

| Component           | ATtiny85 Pin | Physical Pin | Notes                                  |
|---------------------|--------------|---------------|----------------------------------------|
| TMP36 Vout          | A1 (PB2)     | Pin 7         | Analog input (TMP36 middle leg)        |
| TMP36 GND           | —            | Pin 4         | TMP36 right leg, common ground      |
| TMP36 VCC (3V)      | —            | DIP Switch → Pin 8 | Battery (+) থেকে DIP হয়ে VCC |
| RGB RED             | PB0          | Pin 5         | With 220Ω resistor                     |
| RGB GREEN           | PB1          | Pin 6         | With 220Ω resistor                     |
| RGB BLUE            | PB4          | Pin 3         | With 220Ω resistor                     |
| Common GND          | —            | Pin 4         | সব ground এখানে যুক্ত              |

📌 DIP Switch: ব্যাটারি (+) থেকে VCC (Pin 8)-এ  
📌 Common cathode RGB LED ব্যবহার করো; প্রতিটি রঙের অ্যানোড একটি রেজিস্টরের মাধ্যমে সংযুক্ত করা হয়েছে  
📌 VCC ↔ GND-এ 0.1μF ক্যাপাসিটর voltage stability-র জন্য লাগাও

---

# 🧠 Code Breakdown

### TMP36 Voltage Mapping
- TMP36 gives **0.5V at 0°C**  
- Every +1°C adds ~10mV  
- So:  
  - -40°C = 0.1V  
  - +125°C = 1.75V  
- Formula: `temperature = (voltage - 0.5) * 100`

### Color Zones Mapped to Temperature

| Temperature Range     | Color   | RGB Value      |
|----------------------|---------|----------------|
| ≤ –20°C              | Blue    | (0, 0, 255)    |
| –20°C to 10°C        | Cyan    | (0, 255, 255)  |
| 10°C to 35°C         | Green   | (0, 255, 0)    |
| 35°C to 60°C         | Orange  | (255, 165, 0)  |
| > 60°C               | Red     | (255, 0, 0)    |

### PWM and Pin Constraints

| Function     | Pin Name | Physical Pin | PWM Supported |
|--------------|-----------|---------------|----------------|
| RED          | PB0       | Pin 5         | ✅             |
| GREEN        | PB1       | Pin 6         | ✅             |
| BLUE         | PB4       | Pin 3         | ✅             |
| TMP36 Analog | PB2       | Pin 7         | Analog Only    |

---

✅ This setup ensures 5 clear color indicators across wide temp range using battery + DIP control

---

✨ এই প্রজেক্টে কী হবে?
==========================
- ATtiny85 দিয়ে TMP36 temperature sensor-এর মান পড়বে
- Temperature অনুযায়ী RGB LED-তে ৫টি আলাদা রঙ দেখাবে (Blue, Cyan, Green, Orange, Red)
- সবকিছু ছোট সার্কিটে, ব্যাটারি ও DIP switch দিয়ে চালানো যাবে

🔌 সার্কিট কানেকশন (Circuit Connection)
==========================
**যা লাগবে:**
- ATtiny85
- TMP36 Temperature Sensor
- ১টি Common Cathode RGB LED
- ৩টি 220Ω resistor (প্রতিটি রঙের জন্য)
- DIP Switch (battery on/off)
- 0.1μF capacitor (VCC ↔ GND)
- Coin cell battery (3V)
- Jumper Wires

**কানেকশন টেবিল:**

| Component           | ATtiny85 Pin | Physical Pin | কাজ/ব্যাখ্যা                        |
|---------------------|--------------|-------------|-------------------------------------|
| TMP36 Vout          | A1 (PB2)     | Pin 7       | Analog input (TMP36 middle leg)     |
| TMP36 GND           | —            | Pin 4       | TMP36 right leg, common ground      |
| TMP36 VCC (3V)      | —            | DIP Switch → Pin 8 | Battery (+) থেকে DIP হয়ে VCC |
| RGB RED             | PB0          | Pin 5       | 220Ω resistor দিয়ে                 |
| RGB GREEN           | PB1          | Pin 6       | 220Ω resistor দিয়ে                 |
| RGB BLUE            | PB4          | Pin 3       | 220Ω resistor দিয়ে                 |
| Common GND          | —            | Pin 4       | সব ground এখানে যুক্ত              |

**নোট:**
- DIP Switch: ব্যাটারি (+) থেকে VCC (Pin 8)-এ
- Common cathode RGB LED ব্যবহার করো
- VCC ↔ GND-এ 0.1μF ক্যাপাসিটর voltage stability-র জন্য

💡 Temperature থেকে Color Mapping
==========================
- TMP36: 0°C-তে 0.5V, প্রতি 1°C-তে ~10mV বাড়ে
- Temperature বের করার ফর্মুলা:  
  `temperature = (voltage - 0.5) * 100`

| Temperature Range     | Color   | RGB Value      |
|----------------------|---------|----------------|
| ≤ –20°C              | Blue    | (0, 0, 255)    |
| –20°C to 10°C        | Cyan    | (0, 255, 255)  |
| 10°C to 35°C         | Green   | (0, 255, 0)    |
| 35°C to 60°C         | Orange  | (255, 165, 0)  |
| > 60°C               | Red     | (255, 0, 0)    |

📝 ধাপে ধাপে কী হচ্ছে (Step-by-Step)
==========================
1. TMP36-এর Vout → ATtiny85-এর A1 (PB2, Pin 7)-এ সংযুক্ত করো
2. TMP36-এর GND → Pin 4-এ, VCC → DIP Switch হয়ে Pin 8-এ
3. RGB LED-এর RED, GREEN, BLUE পা যথাক্রমে PB0 (Pin 5), PB1 (Pin 6), PB4 (Pin 3)-এ সংযুক্ত করো (প্রতিটিতে 220Ω resistor)
4. Common cathode (LED-এর বড় পা) ও সব ground Pin 4-এ সংযুক্ত করো
5. 0.1μF ক্যাপাসিটর VCC ↔ GND-এ লাগাও
6. analogRead() দিয়ে TMP36-এর মান পড়ো
7. মানকে voltage ও temperature-এ রূপান্তর করো
8. temperature অনুযায়ী RGB LED-তে নির্দিষ্ট রঙ দেখাও (digitalWrite/analogWrite)
9. DIP Switch দিয়ে সার্কিট অন/অফ করো

✅ এই প্রজেক্টে যা শিখবে
==========================
- ATtiny85-তে TMP36 temperature sensor ব্যবহার
- analogRead() ও temperature calculation
- RGB LED-তে বিভিন্ন রঙ দেখানো (PWM)
- DIP Switch ও ক্যাপাসিটর ব্যবহার
- Temperature অনুযায়ী রঙ পরিবর্তন

🚦 এখন নিজে চেষ্টা করো!
==========================
- সার্কিট বানাও
- কোড আপলোড করো
- Temperature বাড়লে/কমলে LED-র রঙ কিভাবে বদলায় দেখো!
