#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int PULSE_START_PIN = 7;
const int PULSE_END_PIN = 4;
const float MAX_PULSE_DURATION = 100.0;
const float MIN_PULSE_DURATION = 1.1;

unsigned long previousMillis = 0;
const long interval = 200;
unsigned long pulseStart, pulseEnd = 0;
unsigned int measurementCount = 0;
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
    pulseStart = micros();
    delay(1);
    while (digitalRead(PULSE_END_PIN) != HIGH){
    }
    pulseEnd = micros();
    previousMillis = millis();
    pulseDuration = ((pulseEnd > pulseStart) ? ((pulseEnd - pulseStart - 4) / 1000.0): 0.0);
    if (pulseDuration < MAX_PULSE_DURATION && pulseDuration > MIN_PULSE_DURATION) {
      averagePulseDuration = ((averagePulseDuration * measurementCount) + pulseDuration) / (measurementCount + 1);
      measurementCount ++;
      if (measurementCount == 1) {
        char buf[7];
        dtostrf(pulseDuration, 5, 3, buf);
        lcd.setCursor(1, 0);
        lcd.print("Samples : ");
        lcd.print(measurementCount);
        lcd.setCursor(1, 1);
        lcd.print(buf);
        lcd.setCursor(10, 1);
        lcd.print(averagePulseDuration);
        Serial.println(buf);
      } else {
        char buf[7];
        dtostrf(pulseDuration, 5, 3, buf);
        lcd.setCursor(11, 0);
        lcd.print(measurementCount);
        lcd.setCursor(0, 1);
        lcd.print("                ");
        lcd.setCursor(1, 1);
        lcd.print(buf);
        lcd.setCursor(10, 1);
        lcd.print(averagePulseDuration);
        Serial.println(buf);
      }
    }
  }
}
