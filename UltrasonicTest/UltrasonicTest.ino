 

const int trigPin = 8;
const int echoPin = 7;
long duration;
int distanceCm, distanceInch;

void setup()
{
 Serial.begin(9600);//starts serial communication
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

}


void loop() 
{
  
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);
distanceCm= duration*0.034/2;
distanceInch = duration*0.0133/2;

Serial.print("Distance from ultrasonic1: ");
  Serial.println(distanceCm);

}
