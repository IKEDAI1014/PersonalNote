#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int PULSE_START_PIN = 7;
const int PULSE_END_PIN = 4;
const float MAX_PULSE_DURATION = 100.0;
const float MIN_PULSE_DURATION = 1.1;

unsigned long pulseStart, pulseEnd = 0;
unsigned int numtries = 0;
float pulseDuration, avgPulseDuration = 0.0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(PULSE_START_PIN, INPUT);
  pinMode(PULSE_END_PIN, INPUT);
}

void loop() {
  while (digitalRead(PULSE_START_PIN) != LOW){
  }
  pulseStart = micros();
  delay(1);
  while (digitalRead(PULSE_END_PIN) != HIGH){
  }
  pulseEnd = micros();
  pulseDuration = (pulseEnd > pulseStart) ? (pulseEnd - pulseStart - 4) / 1000.0 : 0.0;
  if (pulseDuration < MAX_PULSE_DURATION && pulseDuration > MIN_PULSE_DURATION) {
    avgPulseDuration = ((avgPulseDuration * numtries) + pulseDuration) / (numtries + 1);
    numtries += 1;
    if (numtries == 1) {
      lcd.home();
      lcd.print("Try new");
      lcd.setCursor(8, 0);
      lcd.print(pulseDuration);
      lcd.setCursor(14, 0);
      lcd.print("ms");
      lcd.setCursor(0, 1);
      lcd.print(numtries);
      lcd.setCursor(4, 1);
      lcd.print("avg");
      lcd.setCursor(8, 1);
      lcd.print(avgPulseDuration);
      lcd.setCursor(14, 1);
      lcd.print("ms");
      char buf[7];
      dtostrf(pulseDuration, 5, 3, buf);
      Serial.println(buf);
    } else {
      lcd.setCursor(8, 0);
      lcd.print("      ");
      lcd.setCursor(8, 0);
      lcd.print(pulseDuration);
      lcd.setCursor(0, 1);
      lcd.print("    ");
      lcd.setCursor(0, 1);
      lcd.print(numtries);
      lcd.setCursor(8, 1);
      lcd.print("      ");
      lcd.setCursor(8, 1);
      lcd.print(avgPulseDuration);
      char buf[7];
      dtostrf(pulseDuration, 5, 3, buf);
      Serial.println(buf);
    }
  }
  delay(200);
}
