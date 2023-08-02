#include <Servo.h>
#include <RTClib.h>
#include <Wire.h>
#include <LiquidCrystal.h>

/////////Real Time Clock Set-Up//////////
RTC_DS3231 rtc;
char t[32];
DateTime now;
int Contrast=75;
LiquidCrystal lcd(12, 13, 5, 4, 3, 2);  

/////////Schedule Setter Set-Up/////////
enum States2{INIT_sched, displayTime, setMeals, setSchedule} scheduleState;
unsigned int numMeals = 0;
unsigned int arrHours[10];
unsigned int arrMinutes[10];
unsigned long previousMillisSched;
const long schedMillis = 200;
const int buttonPinRight = 7;
int buttonStateRight = 0;
const int buttonPinLeft = A3;
int buttonStateLeft = 0;
int ss, mm, hh;

typedef struct{
  int mins;
  int hrs;
} feedTime;

feedTime times[10];
int tempMin = 0;
int tempHr = 0;
int mealIndex = 0;
int timeIndex = 0;

////////Food Servo Set-Up///////////////
Servo myservoFood;
enum States{INIT_FOOD, Wait_FOOD, Dispense} foodState;
unsigned long previousMillisFood;
const long openIntFood = 3000;
unsigned int i = 0;

/////Treat Servo Set-Up////////////////
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
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  analogWrite(6,Contrast);
  lcd.begin(16, 2);
  pinMode(buttonPinRight, INPUT);
  //rtc.adjust(DateTime(2023, 4, 6, 15, 46, 0)); //For adjustments to time on RTC
  myservoFood.attach(8);
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

int foodTick (int state){
  switch(state){
    case INIT_FOOD:
      myservoFood.write(90);
      break;
    case Wait_FOOD:
      myservoFood.write(90);
      break;
    case Dispense:
      myservoFood.write(180);
      break;
  }

  switch(state){
    case INIT_FOOD:
      state = Wait_FOOD;
      break;
    case Wait_FOOD:
      for(i = 0; i < numMeals; i++){
        if(mm == times[i].mins && hh == times[i].hrs && ss == 0){
          previousMillisFood = currentMillis;
          state = Dispense;
        }
      }
      break;
    case Dispense:
      if(currentMillis - previousMillisFood >= openIntFood/numMeals){
        previousMillisFood = currentMillis;
        state = Wait_FOOD;
      }
      break;
  }
  return state;
}

int scheduleTick (int state){
  switch(state){
    case INIT_sched:
      lcd.clear();
      break;
    case displayTime:
      lcd.setCursor(0, 0);
      lcd.print("Time: ");
      if (hh < 10) lcd.print("0");
      lcd.print(hh);
      lcd.print(':');
      if (mm < 10) lcd.print("0");
      lcd.print(mm);
      lcd.print(':');
      if (ss < 10) lcd.print("0");
      lcd.print(ss);
      lcd.setCursor(0,1);
      lcd.print("Right to Set");
      break;
    case setMeals:
      lcd.setCursor(0,0);
      lcd.print(" Right to cont.");
      if(buttonStateLeft == HIGH){
        if(numMeals == 9){
          numMeals = 0;
        }else{
          numMeals++;
        }
      }
      lcd.setCursor(0,1);
      lcd.print(" # of Meals: ");
      lcd.print(numMeals);
      
      
      break;
    case setSchedule:
      if(buttonStateRight == HIGH){
        timeIndex++;
        if(timeIndex > 1){
          timeIndex = 0;
          tempHr = 0;
          tempMin = 0;
          mealIndex++;
        }
      }
      if(buttonStateLeft == HIGH){
        if(timeIndex == 0){
          if(tempHr > 22){
            tempHr = 0;
          }else{
            tempHr++;
          }
        }else if(timeIndex == 1){
          if(tempMin > 58){
            tempMin = 0;
          }else{
            tempMin++;
          }
        }
      }
      lcd.setCursor(0,0);
      lcd.print("Setting ");
      if(timeIndex == 0){
        lcd.print("Hours");
      }else if(timeIndex == 1){
        lcd.print("Minutes");
      }
      lcd.setCursor(0,1);
      lcd.print("  Time: ");
      if (tempHr < 10) lcd.print("0");
      lcd.print(tempHr);
      lcd.print(':');
      if (tempMin < 10) lcd.print("0");
      lcd.print(tempMin);
      break;
  }

  switch(state){
    case INIT_sched:
      state = displayTime;
      break;
    case displayTime:
      if(buttonStateRight == HIGH){
        numMeals = 0;
        state = setMeals;
      }
      break;
    case setMeals:
      if(buttonStateRight == HIGH && numMeals != 0){
        state = setSchedule;
      }
      break;
    case setSchedule:
      if(mealIndex >= numMeals){
        state = displayTime;
        mealIndex = 0;
      }else{
        times[mealIndex].mins = tempMin;
        times[mealIndex].hrs = tempHr;
      }
      break;
  }
  return state;
}

void loop() {
  //////////Treat State Machine Prep/////////////
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;

  if(distance < 15 && distance > 1){
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

  ///////////Schedule & Food State Machine Prep///////////////
  now = rtc.now();
  ss = now.second();
  mm = now.minute();
  hh = now.hour();
  foodState = (States) foodTick(foodState);

  if(currentMillis - previousMillisSched >= schedMillis){
    lcd.clear();
    buttonStateRight = digitalRead(buttonPinRight);
    buttonStateLeft = digitalRead(buttonPinLeft);
    previousMillisSched = currentMillis;
    scheduleState = (States2) scheduleTick(scheduleState);
  }
}

  
