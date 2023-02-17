#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
unsigned long mrBegin, mrEnd = 0;  //測定関係の保管用
unsigned int tries = 0;            //測定回数保管用
float f_mrTotal, f_avgmrTotal;     //測定数値のms表記

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("standby");
  pinMode(4, INPUT);
  pinMode(7, INPUT_PULLUP);
}

void loop() {
  while (digitalRead(7) != LOW){
  }
  mrBegin = micros();
  while (digitalRead(4) != HIGH){
  }
  mrEnd = micros();
  if (mrEnd > mrBegin) {
    f_mrTotal = static_cast<float>(mrEnd - mrBegin) / 1000;
    if (f_mrTotal < 100) {
      f_avgmrTotal = static_cast<float>(((f_avgmrTotal * tries) + f_mrTotal) / (tries + 1));
      tries += 1;
      lcd.clear();
      lcd.home();
      lcd.print("Try new");
      lcd.setCursor(8, 0);
      lcd.print(f_mrTotal);
      lcd.setCursor(14, 0);
      lcd.print("ms");
      lcd.setCursor(0, 1);
      lcd.print(tries);
      lcd.setCursor(4, 1);
      lcd.print("avg");
      lcd.setCursor(8, 1);
      lcd.print(f_avgmrTotal);
      lcd.setCursor(14, 1);
      lcd.print("ms");
      if (tries == 1) {
        Serial.println("Try, Input lag[ms], minimum[ms], average[ms], maximum[ms], Range, STDEV");
        Serial.print(tries);
        Serial.print(", ");
        Serial.print(String(f_mrTotal, 3));
        Serial.println(", =MIN(B:B), =AVERAGE(B:B), =MAX(B:B), =E2-C2, =STDEVP(B:B)");
      } else {
        Serial.print(tries);
        Serial.print(", ");
        Serial.println(String(f_mrTotal, 3));
      }
    } else {
      lcd.clear();
      lcd.print("Too Slow");
    }
  } else {
    lcd.clear();
    lcd.print("Too Fast");
  }
  delay(200);
}
