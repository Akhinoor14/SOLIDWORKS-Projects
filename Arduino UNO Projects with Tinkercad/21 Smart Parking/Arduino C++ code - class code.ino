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

  S1.write(pos);  // Closed
  S2.write(pos);   // Closed

  // IR Sensor Pins
  pinMode(IR_entry, INPUT); // entryIR
  pinMode(IR_exit, INPUT); // exitIR
  pinMode(IR_Slot1, INPUT); // slot1IR
  pinMode(IR_Slot2, INPUT); // slot2IR
    // Initial LCD message
  lcd.begin(16, 2);
  lcd.print("Smart Parking");
lcd.setCursor(0, 1);
  lcd.print("System Ready");    
  delay(2000);
  lcd.clear();
  lcd.print("Waiting for IR");
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
  
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Slot 1: Free "); 
  }
  if (digitalRead(IR_Slot2) == HIGH)
  {
    lcd.setCursor(0, 1);
    lcd.print("Slot 2: Occupied");
   
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Slot 2: Free ");
  }
if (digitalRead(IR_entry) == HIGH) {
    S1.write(90); // Open entry gate
  }
else {
    S1.write(pos); // Close entry gate
  } 
if (digitalRead(IR_exit) == HIGH) {
    S2.write(pos+90); // Open exit gate
  }
else {
    S2.write(0); // Close exit gate
  }
  delay(100); // Short delay for stability
}