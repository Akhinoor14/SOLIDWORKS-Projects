# ⌨️ 4×4 Matrix Keypad with Arduino

![Arduino Project](https://img.shields.io/badge/Arduino-UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Status](https://img.shields.io/badge/Status-Completed-success?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Intermediate-yellow?style=for-the-badge)
![Input](https://img.shields.io/badge/Input-4×4%20Keypad-blue?style=for-the-badge)

## 📋 Table of Contents
- [Overview](#-overview)
- [Components Required](#-components-required)
- [Matrix Keypad Basics](#-matrix-keypad-basics)
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

This project demonstrates **user input handling** using a **4×4 matrix keypad** and Arduino UNO. The keypad provides 16 buttons (0-9, A-D, *, #) through matrix scanning, which Arduino reads and displays via Serial Monitor. This is fundamental for password entry, calculators, menu navigation, and interactive embedded systems.

### Key Features:
- ✅ 16-button input with only 8 pins (matrix scanning)
- ✅ Keypad library for simplified operation
- ✅ Real-time key detection and display
- ✅ Debouncing built into library
- ✅ Customizable key mapping
- ✅ Foundation for security systems and HMI

---

## 🧰 Components Required

| Component | Quantity | Specification |
|-----------|----------|---------------|
| Arduino UNO | 1 | ATmega328P based |
| 4×4 Matrix Keypad | 1 | 16 buttons (membrane type) |
| Breadboard | 1 | For connections |
| Jumper Wires | 8 | Male-to-Male |
| USB Cable | 1 | For serial communication |

### 💰 Estimated Cost: $5-8 USD

---

## 🔬 Matrix Keypad Basics

### What is a Matrix Keypad?

A **matrix keypad** is an array of pushbuttons arranged in rows and columns. Instead of requiring one wire per button (16 wires for 16 buttons), the matrix configuration needs only **rows + columns** wires (4 + 4 = 8 wires for 4×4).

### Matrix vs Individual Buttons:

| Feature | Matrix Keypad (4×4) | Individual Buttons |
|---------|--------------------|--------------------|
| **Buttons** | 16 | 16 |
| **Pins Required** | 8 (4 rows + 4 cols) | 16 |
| **Pin Savings** | 50% reduction | None |
| **Complexity** | Matrix scanning | Simple digitalRead |
| **Cost** | Low | Higher (more wiring) |
| **Debouncing** | Library handles | Manual code |

### 4×4 Keypad Layout:

```
Physical Button Layout:
┌────┬────┬────┬────┐
│ 1  │ 2  │ 3  │ A  │  Row 0
├────┼────┼────┼────┤
│ 4  │ 5  │ 6  │ B  │  Row 1
├────┼────┼────┼────┤
│ 7  │ 8  │ 9  │ C  │  Row 2
├────┼────┼────┼────┤
│ *  │ 0  │ #  │ D  │  Row 3
└────┴────┴────┴────┘
Col0 Col1 Col2 Col3

Total: 16 buttons
Keys: 0-9 (10 digits)
      A-D (4 letters)
      *, # (2 symbols)
```

### Keypad Pinout:

```
Typical 4×4 Membrane Keypad:
┌─────────────────────────┐
│  ┌────┬────┬────┬────┐  │
│  │ 1  │ 2  │ 3  │ A  │  │
│  ├────┼────┼────┼────┤  │
│  │ 4  │ 5  │ 6  │ B  │  │
│  ├────┼────┼────┼────┤  │
│  │ 7  │ 8  │ 9  │ C  │  │
│  ├────┼────┼────┼────┤  │
│  │ *  │ 0  │ #  │ D  │  │
│  └────┴────┴────┴────┘  │
│                         │
│  Ribbon Cable (8-pin)   │
│  ↓↓↓↓↓↓↓↓                │
└─────────────────────────┘
   1 2 3 4 5 6 7 8

Pin Mapping (Standard):
  Pins 1-4: Row 0, Row 1, Row 2, Row 3
  Pins 5-8: Col 0, Col 1, Col 2, Col 3
```

**⚠️ Note:** Pin numbering may vary by manufacturer. Always check the datasheet or test with a multimeter.

### Matrix Scanning Principle:

The keypad is a grid of switches:

```
Internal Structure:
        COL0   COL1   COL2   COL3
         │      │      │      │
ROW0 ────●──────●──────●──────●──── D9
         │      │      │      │
ROW1 ────●──────●──────●──────●──── D8
         │      │      │      │
ROW2 ────●──────●──────●──────●──── D7
         │      │      │      │
ROW3 ────●──────●──────●──────●──── D6
         │      │      │      │
         D5     D4     D3     D2

Each ● = Switch (button)
When pressed: Connects row to column
```

### How Scanning Works:

```
Step-by-Step Scanning Process:

1. Arduino sets all ROW pins HIGH
2. Arduino sets all COL pins as INPUT_PULLUP
3. To scan:
   a. Set ROW0 LOW, others HIGH
   b. Read all columns
   c. If COL1 is LOW → Button (ROW0, COL1) pressed = '2'
   d. Set ROW0 HIGH again
   e. Repeat for ROW1, ROW2, ROW3

Example: Pressing '5' button
  • '5' is at (ROW1, COL1)
  • When ROW1 = LOW and button pressed
  • COL1 goes LOW (connected through switch)
  • Arduino detects: ROW1 + COL1 = Key '5'

Scanning Speed: ~100Hz (10ms per scan)
Library handles all timing automatically!
```

### Key Mapping Array:

```cpp
char keys[4][4] = {
  {'1', '2', '3', 'A'},  // Row 0
  {'4', '5', '6', 'B'},  // Row 1
  {'7', '8', '9', 'C'},  // Row 2
  {'*', '0', '#', 'D'}   // Row 3
//Col0  Col1  Col2  Col3
};

This 2D array maps physical button positions
to character values that your program uses.

You can customize:
  - Change '1' to 'X'
  - Change 'A' to '+'
  - Use for calculator, lock, menu, etc.
```

### Keypad Library Features:

The Arduino **Keypad library** by Mark Stanley and Alexander Brevig provides:

| Feature | Description | Benefit |
|---------|-------------|---------|
| **Automatic Scanning** | Continuously polls matrix | No manual timing code |
| **Debouncing** | Filters contact bounce | Clean key detection |
| **getKey()** | Returns pressed key | Simple function call |
| **State Tracking** | IDLE, PRESSED, HOLD, RELEASED | Advanced applications |
| **Customizable** | Change pins, mapping, timing | Flexible design |

---

## 🔌 Circuit Diagram

### Connection Table:

| Keypad Pin | Function | Arduino Pin | Description |
|-----------|----------|-------------|-------------|
| Pin 1 | ROW0 | D9 | Top row |
| Pin 2 | ROW1 | D8 | Second row |
| Pin 3 | ROW2 | D7 | Third row |
| Pin 4 | ROW3 | D6 | Bottom row |
| Pin 5 | COL0 | D5 | Leftmost column |
| Pin 6 | COL1 | D4 | Second column |
| Pin 7 | COL2 | D3 | Third column |
| Pin 8 | COL3 | D2 | Rightmost column |

### Circuit Wiring:

```
Arduino UNO                    4×4 Matrix Keypad
┌─────────────┐               ┌──────────────────┐
│             │               │  ┌────┬────┬────┬────┐
│   D9  ●─────┼───────────────┤  │ 1  │ 2  │ 3  │ A  │
│             │               │  ├────┼────┼────┼────┤
│   D8  ●─────┼───────────────┤  │ 4  │ 5  │ 6  │ B  │
│             │               │  ├────┼────┼────┼────┤
│   D7  ●─────┼───────────────┤  │ 7  │ 8  │ 9  │ C  │
│             │               │  ├────┼────┼────┼────┤
│   D6  ●─────┼───────────────┤  │ *  │ 0  │ #  │ D  │
│             │               │  └────┴────┴────┴────┘
│   D5  ●─────┼───────────────┤                      │
│             │               │  Ribbon Cable        │
│   D4  ●─────┼───────────────┤  (8 wires)           │
│             │               │                      │
│   D3  ●─────┼───────────────┤  Pin 1-4: Rows       │
│             │               │  Pin 5-8: Columns    │
│   D2  ●─────┼───────────────┤                      │
│             │               │                      │
└─────────────┘               └──────────────────────┘

No external components needed!
Keypad connects directly to Arduino.
```

### Breadboard Layout:

```
Direct Connection (No Breadboard Required):
┌──────────────────────────────────────┐
│ Keypad has 8-pin ribbon cable        │
│ Use female-to-male jumpers           │
│                                      │
│ Keypad Pin 1 → Arduino D9 (Red)      │
│ Keypad Pin 2 → Arduino D8 (Orange)   │
│ Keypad Pin 3 → Arduino D7 (Yellow)   │
│ Keypad Pin 4 → Arduino D6 (Green)    │
│ Keypad Pin 5 → Arduino D5 (Blue)     │
│ Keypad Pin 6 → Arduino D4 (Purple)   │
│ Keypad Pin 7 → Arduino D3 (Gray)     │
│ Keypad Pin 8 → Arduino D2 (White)    │
└──────────────────────────────────────┘

Optional: Use breadboard for organized wiring
```

### 🖼️ Circuit Diagram:
![4×4 Keypad Circuit](circuit.png)

---

## ⚙️ How It Works

### Matrix Scanning Process:

```
Continuous Scanning Loop:

Step 1: Initialize
  • Set all ROW pins as OUTPUT
  • Set all COL pins as INPUT_PULLUP
  • All columns read HIGH by default
  
Step 2: Scan Rows Sequentially
  For each row (0-3):
    a. Set current ROW LOW
    b. Read all column pins
    c. If any column is LOW:
       → Button at (row, col) is pressed
       → Return mapped character from keys[][]
    d. Set current ROW HIGH again
    e. Move to next row
  
Step 3: Debounce
  • Wait for stable reading (library handles)
  • Ignore contact bounce (<10ms)
  
Step 4: Return Key
  • If button pressed: Return character ('1'-'D')
  • If no button: Return NO_KEY (null)
  
Repeat: Every 10ms (100Hz scan rate)
```

### Example: Detecting '5' Press

```
Physical Button: Row 1, Column 1

Scanning Sequence:
┌──────────────────────────────┐
│ Scan ROW0 (LOW)              │
│ Read COL0,1,2,3 → All HIGH   │
│ No button pressed            │
└──────────────────────────────┘
         ↓
┌──────────────────────────────┐
│ Scan ROW1 (LOW)              │
│ Read COL0 → HIGH             │
│ Read COL1 → LOW ✅           │
│ Button detected!             │
│ Position: ROW1, COL1         │
│ keys[1][1] = '5'             │
│ Return '5'                   │
└──────────────────────────────┘
         ↓
┌──────────────────────────────┐
│ Arduino receives '5'         │
│ Serial.println("5")          │
│ User sees "Key Pressed: 5"   │
└──────────────────────────────┘
```

### Debouncing:

Physical switches have contact bounce:

```
Mechanical Switch Bounce:
┌──────────────────────────────┐
│ Ideal:                       │
│   OFF ────┐                  │
│           │                  │
│           └────── ON         │
│                              │
│ Reality:                     │
│   OFF ────┐╱╲╱╲╱╲            │
│           │╲╱╲╱╲╱│           │
│           └───────── ON      │
│           ▲       ▲          │
│        Bounce   Stable       │
│        (5-10ms) (>10ms)      │
└──────────────────────────────┘

Without debouncing: Multiple key detections
With debouncing: Single clean detection

Keypad library debouncing:
  • Default hold time: 50ms
  • Ignores bounces < 10ms
  • Customizable: keypad.setHoldTime(100)
```

### Code Flow:

```
        START
          │
          ↓
      ┌────────┐
      │ setup()│
      └────┬───┘
           │
    ┌──────┴──────────┐
    │ Serial.begin()  │
    │ Keypad object   │
    │ initialized     │
    └──────┬──────────┘
           │
           ↓
    ┌──────────────┐
    │   loop()     │◄────────────┐
    └──────┬───────┘             │
           │                     │
           ↓                     │
    ┌──────────────┐             │
    │keypad.getKey()│            │
    └──────┬───────┘             │
           │                     │
      ┌────┴────┐                │
      │Key != 0?│                │
      └────┬────┘                │
       YES │ NO                  │
    ┌──────┴──────┐              │
    ↓             ↓              │
┌────────┐   ┌────────┐          │
│ Print  │   │ Skip   │          │
│  Key   │   │        │          │
└───┬────┘   └───┬────┘          │
    │            │               │
    └─────┬──────┘               │
          │                      │
          └──────────────────────┘
```

---

## 📝 Step-by-Step Guide

### 1. **Install Keypad Library**
   ```
   Arduino IDE:
   1. Sketch → Include Library → Manage Libraries
   2. Search: "Keypad"
   3. Find: "Keypad" by Mark Stanley
   4. Click "Install"
   5. Wait for installation complete
   ```

### 2. **Identify Keypad Pins**
   - Most keypads have pin labels (1-8)
   - If unlabeled, use multimeter continuity test
   - Press button, test which pins connect

### 3. **Connect Keypad**
   ```
   Keypad → Arduino
   Pin 1 → D9
   Pin 2 → D8
   Pin 3 → D7
   Pin 4 → D6
   Pin 5 → D5
   Pin 6 → D4
   Pin 7 → D3
   Pin 8 → D2
   ```

### 4. **Upload Code**
   - Open Arduino IDE
   - Copy code from `keypad-4x4.ino`
   - Select: **Tools > Board > Arduino UNO**
   - Select: **Tools > Port > [Your COM Port]**
   - Click **Upload**

### 5. **Open Serial Monitor**
   - Click **Tools > Serial Monitor**
   - Set baud rate to **9600**
   - Should display initial startup message

### 6. **Test Keys**
   - Press each button (0-9, A-D, *, #)
   - Serial Monitor should show: "Key Pressed: [X]"
   - Test all 16 buttons systematically

### 7. **Verify Key Mapping**
   - Ensure displayed character matches button pressed
   - If mismatch, check pin connections or adjust mapping

---

## 💻 Code Explanation

### Full Code:

```cpp
/*
 * Project: 4x4 Matrix Keypad Interfacing
 * Author: Md Akhinoor Islam
 * Description: Read key presses from 4×4 keypad and display on Serial Monitor
 */

#include <Keypad.h>

// Define rows and columns
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Connect keypad ROW0, ROW1, ROW2, ROW3 to these Arduino pins
byte rowPins[ROWS] = {9, 8, 7, 6};

// Connect keypad COL0, COL1, COL2, COL3 to these Arduino pins
byte colPins[COLS] = {5, 4, 3, 2};

// Create the Keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();

  if (key) { // if a key is pressed
    Serial.print("Key Pressed: ");
    Serial.println(key);
  }
}
```

### Code Breakdown:

#### 1️⃣ **Include Library**
```cpp
#include <Keypad.h>
```

**Purpose:**
- Imports Keypad library functions
- Provides `Keypad` class and methods
- Required for matrix scanning

#### 2️⃣ **Define Matrix Size**
```cpp
const byte ROWS = 4;
const byte COLS = 4;
```

| Constant | Value | Purpose |
|----------|-------|---------|
| `ROWS` | 4 | Number of rows in matrix |
| `COLS` | 4 | Number of columns in matrix |

**Why `byte`?**
- Values 0-255 (unsigned 8-bit)
- Smaller than `int` (saves memory)
- Sufficient for keypad size

#### 3️⃣ **Key Mapping Array**
```cpp
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
```

**2D Array Visualization:**

```
       Col0  Col1  Col2  Col3
       ┌────┬────┬────┬────┐
Row0   │ '1'│ '2'│ '3'│ 'A'│
       ├────┼────┼────┼────┤
Row1   │ '4'│ '5'│ '6'│ 'B'│
       ├────┼────┼────┼────┤
Row2   │ '7'│ '8'│ '9'│ 'C'│
       ├────┼────┼────┼────┤
Row3   │ '*'│ '0'│ '#'│ 'D'│
       └────┴────┴────┴────┘

Accessing: keys[row][col]
Example: keys[1][2] = '6'
```

**Customization Examples:**

```cpp
// Calculator keypad
char keys[4][4] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'C', '0', '=', '/'}
};

// Phone keypad
char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Custom menu
char keys[4][4] = {
  {'U', 'D', 'L', 'R'},  // Up, Down, Left, Right
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'S', 'E', 'C', 'X'}   // Start, Enter, Cancel, Exit
};
```

#### 4️⃣ **Pin Assignment**
```cpp
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
```

**Pin Mapping:**

| Array Index | Row/Col | Arduino Pin |
|-------------|---------|-------------|
| rowPins[0] | ROW0 | D9 |
| rowPins[1] | ROW1 | D8 |
| rowPins[2] | ROW2 | D7 |
| rowPins[3] | ROW3 | D6 |
| colPins[0] | COL0 | D5 |
| colPins[1] | COL1 | D4 |
| colPins[2] | COL2 | D3 |
| colPins[3] | COL3 | D2 |

**Why These Pins?**
- Digital pins D2-D9 are available
- Avoids D0/D1 (Serial communication)
- Avoids D13 (built-in LED)
- Can be changed to any digital pins

#### 5️⃣ **Create Keypad Object**
```cpp
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
```

**Constructor Parameters:**

| Parameter | Value | Purpose |
|-----------|-------|---------|
| `makeKeymap(keys)` | Pointer to keys array | Character mapping |
| `rowPins` | Row pin array | Row connections |
| `colPins` | Column pin array | Column connections |
| `ROWS` | 4 | Number of rows |
| `COLS` | 4 | Number of columns |

**makeKeymap() Function:**
- Converts 2D array to format library expects
- Returns pointer to array
- Required by Keypad constructor

#### 6️⃣ **Setup Function**
```cpp
void setup() {
  Serial.begin(9600);
}
```

**Setup Actions:**
- Initialize serial communication
- Keypad object auto-configures pins
- No pinMode needed (library handles)

#### 7️⃣ **Get Key Press**
```cpp
char key = keypad.getKey();
```

**getKey() Function:**

| Returns | Meaning |
|---------|---------|
| Character ('1'-'D') | Button pressed |
| NO_KEY (0) | No button pressed |

**How It Works:**
```cpp
// Inside library:
char getKey() {
  if (scanMatrix()) {
    // Button detected
    return keys[detectedRow][detectedCol];
  } else {
    // No button
    return NO_KEY;
  }
}
```

**Alternative Functions:**

```cpp
// Get key state (IDLE, PRESSED, HOLD, RELEASED)
KeyState state = keypad.getState();

// Wait for key (blocking)
char key = keypad.waitForKey();

// Check specific key
bool pressed = keypad.isPressed('5');

// Set scan rate
keypad.setDebounceTime(50);  // 50ms debounce
keypad.setHoldTime(1000);    // 1s hold time
```

#### 8️⃣ **Conditional Check**
```cpp
if (key) {
  // Key pressed
}
```

**Why `if (key)`?**
```cpp
// Equivalent to:
if (key != NO_KEY)
if (key != 0)
if (key != '\0')

When NO_KEY (0), if condition is false
When any character, if condition is true
```

#### 9️⃣ **Serial Output**
```cpp
Serial.print("Key Pressed: ");
Serial.println(key);
```

**Output Format:**
```
Key Pressed: 1
Key Pressed: 5
Key Pressed: A
Key Pressed: #
```

---

### Advanced Code Examples:

#### **Password Entry System:**
```cpp
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3,2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const String password = "1234";
String enteredPassword = "";

void setup() {
  Serial.begin(9600);
  Serial.println("Enter 4-digit password:");
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    if (key == '#') {
      // Check password
      if (enteredPassword == password) {
        Serial.println("✓ ACCESS GRANTED!");
      } else {
        Serial.println("✗ ACCESS DENIED!");
      }
      enteredPassword = "";  // Reset
    }
    else if (key == '*') {
      // Clear entry
      enteredPassword = "";
      Serial.println("Cleared");
    }
    else if (key >= '0' && key <= '9') {
      // Add digit
      enteredPassword += key;
      Serial.print("*");  // Show asterisk for security
    }
  }
}
```

#### **Calculator:**
```cpp
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','=','/'}
};
byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3,2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

float num1 = 0, num2 = 0, result = 0;
char operation = ' ';
bool enteringNum2 = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Simple Calculator");
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    if (key >= '0' && key <= '9') {
      if (!enteringNum2) {
        num1 = num1 * 10 + (key - '0');
        Serial.println(num1);
      } else {
        num2 = num2 * 10 + (key - '0');
        Serial.println(num2);
      }
    }
    else if (key == '+' || key == '-' || key == '*' || key == '/') {
      operation = key;
      enteringNum2 = true;
      Serial.print(num1);
      Serial.print(" ");
      Serial.print(operation);
      Serial.println(" ");
    }
    else if (key == '=') {
      switch(operation) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/': result = num1 / num2; break;
      }
      Serial.print("= ");
      Serial.println(result);
      num1 = result;
      num2 = 0;
      enteringNum2 = false;
    }
    else if (key == 'C') {
      num1 = num2 = result = 0;
      operation = ' ';
      enteringNum2 = false;
      Serial.println("Cleared");
    }
  }
}
```

---

## 🌐 Simulation

### Try it Online:
🔗 **[View on Tinkercad](https://www.tinkercad.com/things/i3NQmpJS77a-13-keypad-4x4)**

Features:
- Interactive 4×4 keypad
- Click buttons to test
- Real-time Serial Monitor
- Verify key mapping

---

## 🔧 Troubleshooting

### Common Issues:

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| No key detection | Library not installed | Install Keypad library |
| Wrong key displayed | Incorrect pin mapping | Verify rowPins[] and colPins[] |
| Multiple keys at once | Ghosting/key rollover | Normal for cheap keypads |
| Erratic readings | Loose connections | Secure all wires |
| No serial output | Wrong baud rate | Set Serial Monitor to 9600 |
| Some keys don't work | Damaged keypad | Test with multimeter |

### Pin Testing Procedure:

```cpp
// Test which pins are rows vs columns
void testKeypadPins() {
  Serial.println("Keypad Pin Test:");
  
  // Set all as INPUT_PULLUP
  for (int i = 2; i <= 9; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  
  while (true) {
    Serial.println("\nPress a button...");
    delay(2000);
    
    for (int i = 2; i <= 9; i++) {
      if (digitalRead(i) == LOW) {
        Serial.print("Pin D");
        Serial.print(i);
        Serial.println(" is active (LOW)");
      }
    }
  }
}
```

### Key Mapping Verification:

```cpp
// Display pressed key position
void debugKeypad() {
  char key = keypad.getKey();
  
  if (key) {
    Serial.print("Key: ");
    Serial.print(key);
    Serial.print(" at position ");
    
    // Find position in array
    for (byte r = 0; r < ROWS; r++) {
      for (byte c = 0; c < COLS; c++) {
        if (keys[r][c] == key) {
          Serial.print("(Row ");
          Serial.print(r);
          Serial.print(", Col ");
          Serial.print(c);
          Serial.println(")");
        }
      }
    }
  }
}
```

---

## 🎓 Learning Outcomes

### 📚 Concepts Covered:

| Concept | Description | Applications |
|---------|-------------|--------------|
| **Matrix Scanning** | Row-column multiplexing | LED matrices, touchscreens |
| **2D Arrays** | Multi-dimensional data | Game boards, displays |
| **External Libraries** | Code reusability | All Arduino projects |
| **Debouncing** | Contact bounce filtering | All switch inputs |
| **Input Handling** | User interaction | HMI, control panels |

### 🚀 Skills Gained:
- ✅ Understanding matrix keypad operation
- ✅ Library installation and usage
- ✅ 2D array manipulation
- ✅ Character-based user input
- ✅ Serial debugging techniques
- ✅ Foundation for access control systems

### 🔄 Project Extensions:

1. **Door Lock System** - Password + servo unlock
2. **Calculator** - Full arithmetic operations
3. **Menu Navigation** - LCD + keypad menu
4. **Phone Dialer** - GSM module integration
5. **Game Controller** - Directional input
6. **Data Logger** - Keypad entry + SD card
7. **RFID + Keypad** - Multi-factor authentication

---

## 📁 Project Files

| File | Description |
|------|-------------|
| `README.md` | Complete project documentation |
| `keypad-4x4.ino` | Arduino source code |
| `Code & Circuit Explanation(for beginner).md` | Bengali tutorial |
| `circuit.png` | Circuit diagram |
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
- Add LCD display
- Implement password system
- Create custom key mappings
- Build calculator functions
- Share your keypad applications!

---

## ⭐ Show Your Support

If this helped you understand matrix keypads, give it a ⭐!

---

### 📌 Real-World Applications:

- 🔐 **Access Control** - Door locks, safes
- 📱 **Phone Systems** - Dialers, PBX
- 🧮 **Calculators** - Basic arithmetic
- 🏧 **ATM Machines** - PIN entry
- 🏭 **Industrial HMI** - Control panels
- 🎮 **Gaming** - Custom controllers
- 🚪 **Intercoms** - Building entry
- 🔢 **Data Entry** - Inventory systems

Happy Coding! 🎉
