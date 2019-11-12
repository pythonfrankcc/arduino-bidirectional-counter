#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  //lcd.begin();
  //turning on the backlight
  lcd.backlight();
  //Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);
  lcd.print("HELP SAVE ");
  delay(1000);//for dynamic effect
  lcd.setCursor(0,1);//goes to the start of the second line
  lcd.print("IIVES BY E.E.B.C");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("THANKS");
  delay(2000);

}
