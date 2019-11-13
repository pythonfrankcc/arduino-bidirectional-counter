//digital pin connected to flame_Sensor
#define flame_sensor 4
//storing the value by the flame sensor
int flame_detected;
void setup() {
  // put your setup code here, to run once:
  pinMode(flame_sensor, INPUT) ;

}

void loop() {
  // put your main code here, to run repeatedly:
  //read digital output and store it in variable
  flame_detected = digitalRead(flame_sensor);
  if (flame_detected == 1)
  {
    Serial.println("Flame detected...! take action immediately.");
    digitalWrite(buzzer, HIGH);
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(200);
  }
  else
  {
    Serial.println("No flame detected. stay cool");
    digitalWrite(buzzer, LOW);
    digitalWrite(LED, LOW);
  }

}
