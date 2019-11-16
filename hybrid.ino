#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int ldr = A0;
const int dynamo = A1;
const int solar = A2;
const int relay = 7;
const int opto = 2;
int volt2 = 0;
int volt1 = 0;
int volt3 = 0;
int volt4 = 0;
void setup() {
  //lcd.init();// initialize the lcd
  //lcd.init();
  //lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Made by:");
  lcd.setCursor(0, 1);
  lcd.print("Millicent Maina");
  //Serial.begin(9600);
  pinMode(ldr, INPUT);
  pinMode(dynamo, INPUT);
  pinMode(solar, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(opto, OUTPUT);

  digitalWrite(relay, LOW); // Initialise the relay on dynamo usage

  delay(3000);
}

void loop() {
  lcd.clear();
  int Value1 = analogRead(dynamo);

  delay(100);
  int Value2 = analogRead(solar);
  delay(100);
  volt1 = map(Value1, 1023, 0, 5, 0);//dynamo value
  volt2 = map(Value2, 1023, 0, 5, 0);//solar value
  volt3 = volt1 - 4;//dynamo value without error
  volt4 = volt2 - 4;//solar value without error
  lcd.setCursor(0,0);
  lcd.print("dynamo");
  lcd.setCursor(8, 0);
  lcd.print(volt3);

  lcd.setCursor(0, 1);
  lcd.print("solar");
  lcd.setCursor(7,1);
  lcd.print(volt4);

  if (volt3 <= 11) {
    digitalWrite(relay, HIGH);
  }
  else {
    digitalWrite(relay, LOW);
  }
  int Value = analogRead(ldr);
  delay(10);
  if (Value <= 100) {
    digitalWrite(opto, HIGH);
    lcd.setCursor(9, 1);
    lcd.print("led ON");
  }
  else {
    digitalWrite(opto, LOW);
    lcd.setCursor(9, 1);
    lcd.print("led OFF");
  }
  delay(100);
}
