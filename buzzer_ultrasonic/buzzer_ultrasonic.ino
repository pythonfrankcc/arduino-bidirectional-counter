//ultrasonic 1 pins
int UltraEcho1=7;
int UltraTrigger1=8;
//ultrasonic 2 pins
int UltraEcho2=12;
int UltraTrigger2=13;
//digital led pins
int AllClearLed=2;
int TrappedLed=9;
//buzzer trigger
int BuzzerTrigger=10;
//defining variables used in ultrasonic
long duration1;//ultrasonic 1 travel time  
int distance1;//ultrasonic 1 distance
long duration2;//ultrasonic 2 travel time 
int distance2;//ultrasonic 2 distance
//delay for clearing trigger pin
int TriggerDelay=2;
//delay for pulse generation
int TriggerPulse=2;
//defining initial no of people as zero
int NoOfPeople = 0;
//define alarm delay one minute
uint64_t AlarmDelay=4000000;
//define the longs that you use with millis
unsigned long i;
unsigned long j;
void setup() {
  Serial.begin(9600);//starts serial communication
  pinMode(UltraTrigger1,OUTPUT);//sets trigger pin as Output
  pinMode(UltraEcho1,INPUT);//sets ech pin as Input
  pinMode(UltraTrigger2,OUTPUT);
  pinMode(UltraEcho2,INPUT);
  pinMode(AllClearLed,OUTPUT);
  pinMode(TrappedLed,OUTPUT);
  pinMode(BuzzerTrigger,OUTPUT);
  // put your setup code here, to run once:

}
//function  for UltraSonic1 distance
int UltraSonic1(){

  digitalWrite(UltraTrigger1, LOW);
delayMicroseconds(2);
digitalWrite(UltraTrigger1, HIGH);
delayMicroseconds(10);
digitalWrite(UltraTrigger1, LOW);

 //   digitalWrite(UltraTrigger1,HIGH);
 //   delay(TriggerPulse);
//    digitalWrite(UltraTrigger1,LOW);
 //   delay(TriggerPulse);
    duration1=pulseIn(UltraEcho1,HIGH);//reads the echopin on UlstraSonic2 and returns the sound wave travel in microseconds
    distance1 = duration1*0.034/2;
    return distance1;
    } 
//function for UltraSonic2 distance
int UltraSonic2(){
    digitalWrite(UltraTrigger2,HIGH);
    delay(TriggerPulse);
    digitalWrite(UltraTrigger2,LOW);
    delay(TriggerPulse);
    duration2=pulseIn(UltraEcho2,HIGH);//reads the echopin on UlstraSonic2 and returns the sound wave travel in microseconds
    distance2 = duration2*0.034/2;
    return distance2;
    }

void loop() {
  //clearing Triggerpins
  //digitalWrite(UltraTrigger1,LOW);
  //delay(TriggerDelay);
  //digitalWrite(UltraTrigger2,LOW);
  //delay(TriggerDelay);
  UltraSonic1();
  UltraSonic2();
  //print distance on Serial Monitor
  Serial.print("Distance from ultrasonic1: ");
  Serial.println(UltraSonic1());
  Serial.print("Distance from ultrasonic2: ");
  Serial.println(UltraSonic2());
  if (distance1 < 15){
    i = millis();
    while ((millis() - i) <= 3000){
      UltraSonic2();
      Serial.print("Distance from ultrasonic2: ");
      Serial.println(UltraSonic2());
      if (distance2 < 15){
        NoOfPeople++;
        break;
        }
      }
    } 
  Serial.print("The number of people: ");
  Serial.println(NoOfPeople);
  if (distance2 < 15){
    j = millis();
    while ((millis()-j) <= 3000){
      UltraSonic1();
      Serial.print("Distance from ultrasonic1: ");
      Serial.println(UltraSonic1());
      if (distance1<15){
        NoOfPeople--;
        break;
        }
      }
    }
  Serial.print("The number of people: ");
  Serial.println(NoOfPeople);
  //delay before alarm starts,1 minute
  delay(AlarmDelay);
  
  if (NoOfPeople > 0){
    digitalWrite(TrappedLed,HIGH);
    delay(300);
    digitalWrite(TrappedLed,LOW);;
    delay(300);
    }
  if(NoOfPeople > 0){
   digitalWrite(BuzzerTrigger,HIGH); 
    }
  if (NoOfPeople == 0){
    digitalWrite(BuzzerTrigger,LOW);
    }
  if (NoOfPeople >0){
    digitalWrite(AllClearLed,HIGH);
    delay(300);
    digitalWrite(AllClearLed,LOW);
    delay(300);
    }

}
