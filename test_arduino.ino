#include "ultrasonic.h"

//ultrasonic 1 pins
#define UltraEcho1 7
#define UltraTrigger1 8

#define UltraEcho2 12
#define UltraTrigger2 13

#define AllClearLed 2
#define TrappedLed 9

#define BuzzerTrigger 10

#define ultrasonic_sensor_one_range 10
#define ultrasonic_sensor_two_range 10

#define delay_value 3000



Ultrasonic ultrasonic1(UltraTrigger1, UltraEcho1);
Ultrasonic ultrasonic2(UltraTrigger2, UltraEcho2);

bool ultrasonic_sensor_one_is_passed = false;
bool ultrasonic_sensor_two_is_passed = false;
int total_number_of_people = 0;

void setup() {
  Serial.begin(9600);//starts serial communication

  ultrasonic1.initialize();
  ultrasonic2.initialize();
  pinMode(AllClearLed,OUTPUT);
  pinMode(TrappedLed,OUTPUT);
  pinMode(BuzzerTrigger,OUTPUT);

}
void loop() {

  int sensor_one_distance =  ultrasonic1.getDistance();
  int sensor_two_distance = ultrasonic2.getDistance();

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

  if (total_number_of_people > 0){
    digitalWrite(TrappedLed,HIGH);
    digitalWrite(BuzzerTrigger,HIGH);
    delay(300);
    digitalWrite(TrappedLed,LOW);;
    digitalWrite(BuzzerTrigger,LOW);
    delay(300);
    }
  if (total_number_of_people <= 0){
    digitalWrite(BuzzerTrigger,LOW);
    digitalWrite(AllClearLed,HIGH);
    delay(300);
    digitalWrite(AllClearLed,LOW);
    delay(300);
    }
}