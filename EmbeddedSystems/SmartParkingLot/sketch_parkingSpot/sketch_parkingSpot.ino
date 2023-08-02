#include <RH_ASK.h>
#include <SPI.h>



RH_ASK rf_driver;

const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 8;
const int greenLED = 7;
const int yellowLED = 11;
const int redLED = 13;

const int trigPin1 = 3;
const int echoPin1 = 2;
const int buzzer1 = 4;
const int greenLED1 = 1;
const int yellowLED1 = 6;
const int redLED1 = 5;

float duration, distance;
int buzzerTime = 0;
float buzzerBuffer = 0;
float parkingLimit = 600;

float duration1, distance1;
int buzzerTime2 = 0;
float buzzerBuffer1 = 0;



//const char* msg[6];

void setup() {
  rf_driver.init();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(buzzer1,OUTPUT);
  pinMode(greenLED1, OUTPUT);
  pinMode(yellowLED1, OUTPUT);
  pinMode(redLED1, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;

  
      if(distance < 8 && buzzerTime < 50){
        buzzerTime++;
        if(buzzerBuffer > 0){
          buzzerBuffer--;
        }
        int volume = distance/8 * 150 + 50;
        volume = 255 - volume;
        analogWrite(buzzer, volume);
      }else if(distance < 8){
        buzzerTime++;
        if(buzzerBuffer > 0){
          buzzerBuffer--;
        }
        analogWrite(buzzer, 0);
      }else{
        buzzerBuffer++;
        analogWrite(buzzer, 0);
      }
    
      if(buzzerTime < parkingLimit / 2){
        digitalWrite(greenLED, HIGH);
        digitalWrite(yellowLED, LOW);
        digitalWrite(redLED, LOW);
      }else if(buzzerTime < parkingLimit){
        digitalWrite(yellowLED, HIGH);
        digitalWrite(greenLED, LOW);
        digitalWrite(redLED, LOW);
      }else{
        digitalWrite(greenLED, LOW);
        digitalWrite(yellowLED, LOW);
        digitalWrite(redLED, HIGH);
      }
      

  if(buzzerBuffer > 20){
    buzzerBuffer = 0;
    buzzerTime = 0; 
  }


  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1*.0343)/2;
  //Serial.println(distance1);


      if(distance1 < 8 && buzzerTime2 < 50){
        buzzerTime2++;
        if(buzzerBuffer1 > 0){
          buzzerBuffer1--;
        }
        int volume1 = distance1/8 * 150 + 50;
        volume1 = 255 - volume1;
        analogWrite(buzzer1, volume1);
      }else if(distance1 < 8){
        buzzerTime2++;
        if(buzzerBuffer1 > 0){
          buzzerBuffer1--;
        }
        analogWrite(buzzer1, 0);
      }else{
        buzzerBuffer1++;
        analogWrite(buzzer1, 0);
      }
    
      if(buzzerTime2 < parkingLimit / 2){
        digitalWrite(greenLED1, HIGH);
        digitalWrite(yellowLED1, LOW);
        digitalWrite(redLED1, LOW);
      }else if(buzzerTime2 < parkingLimit){
        digitalWrite(yellowLED1, HIGH);
        digitalWrite(greenLED1, LOW);
        digitalWrite(redLED1, LOW);
      }else{
        digitalWrite(greenLED1, LOW);
        digitalWrite(yellowLED1, LOW);
        digitalWrite(redLED1, HIGH);
      }
  //}   
  if(buzzerBuffer1 > 20){
    buzzerBuffer1 = 0;
    buzzerTime2 = 0; 
  }


  
  String msg = "000000000000";
  
  int buzzerTime1 = buzzerTime/10;
  if(buzzerTime1 >= 36000){
    int h_temp = buzzerTime1/36000;
    if(h_temp > 9){
      msg[0] = 9;
    }else{
      msg[0] = String(h_temp)[0];
    }  
    while(buzzerTime1 >= 36000){
      buzzerTime1 = buzzerTime1 - 36000;
    }
  }
  
  if(buzzerTime1 >= 3600){
    int h_temp = buzzerTime1/3600;
    if(h_temp > 9){
      msg[1] = 9;
    }else{
      msg[1] = String(h_temp)[0];
    }  
    while(buzzerTime1 >= 3600){
      buzzerTime1 = buzzerTime1 - 3600;
    }
  }

  if(buzzerTime1 >= 600){
    int h_temp = buzzerTime1/600;
    if(h_temp > 9){
      msg[2] = 9;
    }else{
      msg[2] = String(h_temp)[0];
    }  
    while(buzzerTime1 >= 600){
      buzzerTime1 = buzzerTime1 - 600;
    }
  }

  if(buzzerTime1 >= 60){
    int h_temp = buzzerTime1/60;
    if(h_temp > 9){
      msg[3] = 9;
    }else{
      msg[3] = String(h_temp)[0];
    }  
    while(buzzerTime1 >= 60){
      buzzerTime1 = buzzerTime1 - 60;
    }
  }

  if(buzzerTime1 >= 10){
    int h_temp = buzzerTime1/10;
    if(h_temp > 9){
      msg[4] = 9;
    }else{
      msg[4] = String(h_temp)[0];
    }  
    while(buzzerTime1 >= 10){
      buzzerTime1 = buzzerTime1 - 10;
    }
  }

    int h_temp = buzzerTime1;
    msg[5] = '0';
    if(h_temp > 9){
      msg[5] = 9;
    }else if(h_temp){
      msg[5] = String(h_temp)[0];
    }else{
      msg[5] = '0';
    }






  int buzzerTime3 = buzzerTime2/10;
  if(buzzerTime3 >= 36000){
    int h_temp = buzzerTime3/36000;
    if(h_temp > 9){
      msg[6] = 9;
    }else{
      msg[6] = String(h_temp)[0];
    }  
    while(buzzerTime3 >= 36000){
      buzzerTime3 = buzzerTime3 - 36000;
    }
  }
  
  if(buzzerTime3 >= 3600){
    int h_temp = buzzerTime3/3600;
    if(h_temp > 9){
      msg[7] = 9;
    }else{
      msg[7] = String(h_temp)[0];
    }  
    while(buzzerTime3 >= 3600){
      buzzerTime3 = buzzerTime3 - 3600;
    }
  }

  if(buzzerTime3 >= 600){
    int h_temp = buzzerTime3/600;
    if(h_temp > 9){
      msg[8] = 9;
    }else{
      msg[8] = String(h_temp)[0];
    }  
    while(buzzerTime3 >= 600){
      buzzerTime3 = buzzerTime3 - 600;
    }
  }

  if(buzzerTime3 >= 60){
    int h_temp = buzzerTime3/60;
    if(h_temp > 9){
      msg[9] = 9;
    }else{
      msg[9] = String(h_temp)[0];
    }  
    while(buzzerTime3 >= 60){
      buzzerTime3 = buzzerTime3 - 60;
    }
  }

  if(buzzerTime3 >= 10){
    int h_temp = buzzerTime3/10;
    if(h_temp > 9){
      msg[10] = 9;
    }else{
      msg[10] = String(h_temp)[0];
    }  
    while(buzzerTime3 >= 10){
      buzzerTime3 = buzzerTime3 - 10;
    }
  }

    h_temp = buzzerTime3;
    msg[11] = '0';
    if(h_temp > 9){
      msg[11] = 9;
    }else if(h_temp){
      msg[11] = String(h_temp)[0];
    }else{
      msg[11] = '0';
    }    
  
  
  //Serial.println(buzzerTime);
  //String out = String(buzzerTime);
  //msg = out.c_str();
  Serial.println(msg);
  //Serial.println(buzzerTime2);
  static char* msg1 = const_cast<char*>(msg.c_str());
  //Serial.println(msg1);
  rf_driver.send((uint8_t *)msg1, strlen(msg1));
  rf_driver.waitPacketSent();
  //delay(100);
}
