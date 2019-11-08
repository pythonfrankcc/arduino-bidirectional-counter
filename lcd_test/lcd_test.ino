#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  //turning on the backlight
  lcd.backlight();
  //Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.print("Shout Out!");
  lcd.setCursor(0,1);//goes to the start of the second line
  lcd.print("254");
  delay(500);

}
