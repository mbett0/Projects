#include <Servo.h>
#include <RTClib.h>
#include <Wire.h>
#include <LiquidCrystal.h>

RTC_DS3231 rtc;
char t[32];


/////Treat Servo Set-Up////////
const int trigPin = 11;
const int echoPin = 10;
float distance, duration;

bool sensorCheck = false;
int sensorTime = 0;

Servo myservoTreat;  
enum States1{INIT, Ready, Open, Wait} treatState;
unsigned long previousMillis;
unsigned long currentMillis;
const long openInt = 200;
const long waitInt = 10000;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservoTreat.attach(9);
}

int treatTick (int state){
  switch(state){
    case INIT:
      myservoTreat.write(90);
      break;
    case Ready:
      myservoTreat.write(90);
      break;
    case Open:
      myservoTreat.write(0);
      break;
    case Wait:
      myservoTreat.write(90);
      break;
  }

  switch(state){
    case INIT:
      state = Ready;
      break;
    case Ready:
      if(sensorCheck){
        previousMillis = currentMillis;
        state = Open;
      }
      break;
    case Open:
      if(currentMillis - previousMillis >= openInt){
        previousMillis = currentMillis;
        state = Wait;
      }
      break;
    case Wait:
      if(currentMillis - previousMillis >= waitInt){
        state = Ready;
      }
      break;
  }
  return state;
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  //Serial.println(distance);

  if(distance < 15){
    sensorTime++;
    if(sensorTime > 10){
      sensorCheck = true;
    }
  }else{
    sensorTime = 0;
    sensorCheck = false;
  }

  currentMillis = millis();
  treatState = (States1) treatTick(treatState);
  Serial.println(sensorCheck);
  Serial.println(distance);
}

  
