#include <LiquidCrystal_I2C.h>
#include <avdweb_AnalogReadFast.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
bool reset_flag = false; //測定判断用
unsigned long mrBegin, mrEnd= 0; //測定関係の保管用
unsigned int tries = 0; //測定回数保管用
float f_mrTotal, f_avgmrTotal; //測定数値のms表記

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("standby");
}

void loop() {
  while(analogReadFast(1) > 300);{
    }
    mrBegin = micros();
  while(analogReadFast(0) < 1000);{
  }
  mrEnd = micros();
  if(mrEnd > mrBegin){
    f_mrTotal = static_cast<float>(mrEnd - mrBegin)/1000;
    if(f_mrTotal < 60){
      f_avgmrTotal = static_cast<float>(((f_avgmrTotal * tries) +f_mrTotal)/(tries + 1));
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
      if(tries == 1){
        Serial.println("Try, Input lag[ms], average[ms]");
        Serial.print(tries);
        Serial.print(", ");
        Serial.print(String(f_mrTotal,3));
        Serial.println(", =AVERAGE(B:B)");
      } else {
        Serial.print(tries);
        Serial.print(", ");
        Serial.println(String(f_mrTotal,3));
      }
    } else {
      lcd.clear();
      lcd.print("Failed");
    }
  } else {
    lcd.clear();
    lcd.print("Failed");
  }
  delay(200);
}
