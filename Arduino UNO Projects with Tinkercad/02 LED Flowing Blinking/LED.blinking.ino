/*
 * Project: LED Sequential Blink
 * Author: Md Akhinoor Islam
 * ESE (Energy Science and Engineering), KUET
 * Description: 5 LEDs blink one by one in a loop
 */

const int leds[] = {2, 3, 4, 5, 6}; // LED পিন নাম্বার array আকারে রাখা হয়েছে

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT); // প্রতিটি পিনকে Output mode এ সেট করছি
  }
}

void loop() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(leds[i], HIGH); // বর্তমান LED জ্বলছে
    delay(300);                  // ৩০০ মিলিসেকেন্ড অপেক্ষা
    digitalWrite(leds[i], LOW);  // LED বন্ধ
    delay(100);                  // সামান্য বিরতি
  }
}
