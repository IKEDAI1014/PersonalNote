#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int PULSE_START_PIN = 7;
const int PULSE_END_PIN = 4;
const float MAX_PULSE_DURATION = 100.0;
const float MIN_PULSE_DURATION = 1.1;

unsigned long previousMillis = 0;
const long interval = 200;
unsigned long pulseStart, pulseEnd = 0;
unsigned int numTries = 0;
float pulseDuration, averagePulseDuration = 0.0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(PULSE_START_PIN, INPUT);
  pinMode(PULSE_END_PIN, INPUT);
}

void loop() {
  if (millis() - previousMillis >= interval) {
    while (digitalRead(PULSE_START_PIN) != LOW){
    }
    delay(1);
    pulseStart = micros();
    while (digitalRead(PULSE_END_PIN) != HIGH){
    }
    pulseEnd = micros();
    previousMillis = millis();
    pulseDuration = ((pulseEnd > pulseStart) ? ((pulseEnd - pulseStart - 4) / 1000.0): 0.0);
    if (pulseDuration < MAX_PULSE_DURATION && pulseDuration > MIN_PULSE_DURATION) {
      averagePulseDuration = ((averagePulseDuration * numTries) + pulseDuration) / (numTries + 1);
      numTries += 1;
      if (numTries == 1) {
        lcd.home();
        lcd.print("Try new");
        lcd.setCursor(8, 0);
        lcd.print(pulseDuration);
        lcd.setCursor(14, 0);
        lcd.print("ms");
        lcd.setCursor(0, 1);
        lcd.print(numTries);
        lcd.setCursor(4, 1);
        lcd.print("average");
        lcd.setCursor(8, 1);
        lcd.print(averagePulseDuration);
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
        lcd.print(numTries);
        lcd.setCursor(8, 1);
        lcd.print("      ");
        lcd.setCursor(8, 1);
        lcd.print(averagePulseDuration);
        char buf[7];
        dtostrf(pulseDuration, 5, 3, buf);
        Serial.println(buf);
      }
    }
  }
}
