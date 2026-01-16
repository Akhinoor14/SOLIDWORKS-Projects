/*
 * Project 21: Smart Parking System using Arduino, IR Sensors, LCD & Servo
 * Author: Md. Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: Detects vehicle entry/exit, monitors parking slots, 
 *              controls gate servos, and displays slot status on LCD.
 */

#include <Servo.h>
#include <LiquidCrystal.h>
Servo S1, S2;
#define IR_Slot1 7
#define IR_Slot2 8
#define IR_entry 6
#define IR_exit 13
int pos=0;
// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() {
    // Servo Pins
  S1.attach(9); // entryServoPin
  S2.attach(10); // exitServoPin

  S1.write(0);  // Closed
  S2.write(0);   // Closed

  // IR Sensor Pins
  pinMode(6, INPUT); // entryIR
  pinMode(13, INPUT); // exitIR
  pinMode(7, INPUT); // slot1IR
  pinMode(8, INPUT); // slot2IR


    // Initial LCD message
  lcd.begin(16, 2);
  lcd.print("Smart Parking");
lcd.setCursor(0, 1);
  lcd.print("System Ready");    
  delay(2000);
  lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Slot 1: Free");
    lcd.setCursor(0, 1);
    lcd.print("Slot 2: Free");
    delay(2000);
  lcd.clear();  
}

void loop() {
  if (digitalRead(IR_Slot1) ==HIGH)
  {
    lcd.setCursor(0, 0);
    lcd.print("Slot 1: Occupied");
    delay(3000); // Delay to allow reading
    S1.write(90);  // Open gate for Slot 1
    delay(2000);   // Keep gate open for 2 seconds 
    S1.write(0);   // Close gate

  }     
    else {
        lcd.setCursor(0, 0);
        lcd.print("Slot 1: Free   "); // Clear previous message
        lcd.clear();
    }
  if (digitalRead(IR_Slot2) == HIGH)
  {
    lcd.setCursor(0, 1);
    lcd.print("Slot 2: Occupied");
    delay(3000); // Delay to allow reading
    S2.write(90);  // Open gate for Slot 2
    delay(2000);   // Keep gate open for 2 seconds
    S2.write(0);   // Close gate

    } 
    
    else {
        lcd.setCursor(0, 1);
        lcd.print("Slot 2: Free   "); // Clear previous message
        lcd.clear();
    }   
  
  if (digitalRead(IR_entry) == HIGH) {
    lcd.setCursor(0, 0);
    lcd.print("Vehicle Entry");
    S1.write(90);  // Open entry gate
    delay(2000);   // Keep gate open for 2 seconds
    S1.write(0);   // Close gate
  }
  // Check Exit IR
  if (digitalRead(IR_exit) == HIGH) {
    lcd.setCursor(0, 1);
    lcd.print("Vehicle Exit");
    S2.write(90);  // Open exit gate
    delay(2000);   // Keep gate open for 2 seconds
    S2.write(0);   // Close gate
  }
  // Add a small delay to avoid flickering
  delay(1000); // Adjust as needed for readability
}