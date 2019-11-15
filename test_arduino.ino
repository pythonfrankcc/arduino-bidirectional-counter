#include "ultrasonic.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

//ultrasonic 1 pins
#define UltraEcho1 7
#define UltraTrigger1 8

#define UltraEcho2 12
#define UltraTrigger2 13
//led pins
#define AllClearLed 2
#define TrappedLed 9
//defining the buzzer pin
#define BuzzerTrigger 10
//defining the ultrasonic ranges
#define ultrasonic_sensor_one_range 10
#define ultrasonic_sensor_two_range 10
//defining the delay timers in between the display
#define delay_value 1000
#define lcd_dynamic 1000
#define lcd_starter_delay 5000
//defining the flame sensor pin
#define flame_sensor 4


Ultrasonic ultrasonic1(UltraTrigger1, UltraEcho1);
Ultrasonic ultrasonic2(UltraTrigger2, UltraEcho2);

bool ultrasonic_sensor_one_is_passed = false;
bool ultrasonic_sensor_two_is_passed = false;
int total_number_of_people = 0;
//storing the value by the flame sensor
int flame_detected;

void setup() {
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);//starts serial communication

  ultrasonic1.initialize();
  ultrasonic2.initialize();
  pinMode(flame_sensor, INPUT) ;
  pinMode(AllClearLed, OUTPUT);
  pinMode(TrappedLed, OUTPUT);
  pinMode(BuzzerTrigger, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("HELP SAVE");
  //delay(lcd_dynamic);
  lcd.setCursor(0, 1);
  lcd.print(" BY E.E.B.C");
  delay(lcd_starter_delay);

}
void loop() {

  int sensor_one_distance =  ultrasonic1.getDistance();
  int sensor_two_distance = ultrasonic2.getDistance();
  flame_detected = digitalRead(flame_sensor);


  Serial.print("Ultrasonic 1 => ");
  Serial.print(sensor_one_distance);
  Serial.print("  Ultrasonic 2 => ");
  Serial.println(sensor_two_distance);
  Serial.print("Total persons inside => ");
  Serial.println(total_number_of_people);


  if ((sensor_one_distance < ultrasonic_sensor_one_range) && (ultrasonic_sensor_two_is_passed == false)) {
    ultrasonic_sensor_one_is_passed = true;

    Serial.println("ultrasonic 1 passed first");
    delay(delay_value);
  }
  else if ((sensor_two_distance < ultrasonic_sensor_two_range) && (ultrasonic_sensor_one_is_passed == false)) {
    ultrasonic_sensor_two_is_passed = true;
    Serial.println("ultrasonic 2 passed first");
    delay(delay_value);

  }
  if (ultrasonic_sensor_one_is_passed) {
    if (sensor_two_distance < ultrasonic_sensor_two_range) {
      ultrasonic_sensor_one_is_passed = false;
      Serial.println("ultrasonic 2 passed last");
      total_number_of_people++;
      delay(delay_value);
    }
  }



  else if (ultrasonic_sensor_two_is_passed) {
    if (sensor_one_distance < ultrasonic_sensor_one_range) {
      ultrasonic_sensor_two_is_passed = false;
      Serial.println("ultrasonic 1 passed last");
      total_number_of_people--;
      delay(delay_value);

    }
  }

  if (total_number_of_people < 0) total_number_of_people = 0;


  delay(1000);

  if (total_number_of_people > 0 && flame_detected == 0) {
    digitalWrite(TrappedLed, HIGH);
    digitalWrite(BuzzerTrigger, HIGH);
    delay(200);
    digitalWrite(TrappedLed, LOW);;
    digitalWrite(BuzzerTrigger, LOW);
    delay(200);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(total_number_of_people);
    lcd.setCursor(0, 1);
    lcd.print("People trapped");
    delay(500);
  }
  else if (total_number_of_people > 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(total_number_of_people);
    lcd.setCursor(0, 1);
    lcd.print("People inside");
    delay(500);

  }
  if (total_number_of_people <= 0 && flame_detected  == 1) {
    digitalWrite(BuzzerTrigger, LOW);
    digitalWrite(AllClearLed, HIGH);
    delay(200);
    digitalWrite(AllClearLed, LOW);
    delay(200);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ALL CLEAR");
    lcd.setCursor(0, 1);
    lcd.print(total_number_of_people, ":INSIDE");
    delay(500);
  }
  else if (total_number_of_people <= 0) {
    digitalWrite(BuzzerTrigger, LOW);
    digitalWrite(AllClearLed, HIGH);
    delay(200);
    digitalWrite(AllClearLed, LOW);
    delay(200);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("NOBODY IS");
    lcd.setCursor(0, 1);
    lcd.print("INSIDE");
    delay(500);
  }
}
