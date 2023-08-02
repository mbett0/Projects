#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;

#include <LiquidCrystal.h> 
int Contrast=75;
 LiquidCrystal lcd(13, 12, 5, 4, 3, 2);  
 
int status = 0;
int stateHr = 0;
int stateMin = 0;
int limHr = 0;
int limMin = 1;

int checkLim = 0;

const int buttonHr = 9;
//const int buttonMin = 10;

int spotSelect = 0;
int statusSpot = 0;
int buttonState = 0;

unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 100;


void setup(){
    rf_driver.init();
    analogWrite(6,Contrast);
     lcd.begin(16, 2);
     pinMode(buttonHr, INPUT);
     //pinMode(buttonMin, INPUT);
     startMillis = millis();
     Serial.begin(9600);
} 

void loop(){ 
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    // Check if received packet is correct size
    if (rf_driver.recv(buf, &buflen)){
      // Message received with valid checksum
      Serial.print("Message Received: ");
      Serial.println((char*)buf);
      //Serial.println(buf[1]);      
    }
    currentMillis= millis();
    if(currentMillis - startMillis >= period){ 
     buttonState = digitalRead(buttonHr);
     if(buttonState == HIGH){
      statusSpot++;
     }
     if(statusSpot % 2 == 1){
      spotSelect = 6;
     }else{
      spotSelect = 0;
     }
     
     lcd.clear();
     lcd.setCursor(0, 0);
     if(spotSelect == 6){
         lcd.print("Spot2:");
     }else{
      lcd.print("Spot1:");
     }


    //get status
    static char* time = (char*) buf;
    String temp = static_cast<String>(time[1+spotSelect]);
    stateHr = temp.toInt();
    temp = static_cast<String>(time[3+spotSelect]);
    stateMin = temp.toInt();
    if(stateHr > limHr){
      status = 2;
    }else if(stateHr == limHr && stateMin >= limMin){
      status = 2;
    }else if(time[5+spotSelect]!= '0' || time[4+spotSelect] != '0' || time[3+spotSelect] != '0'){
      status = 1;
    }else{
      status = 0;
    }

     if(status == 0){
      lcd.setCursor(6,0);
      lcd.print("Available");
     }else if(status == 1){
      lcd.setCursor(6, 0);
      lcd.print("Taken");
     }else if(status == 2){
      lcd.setCursor(6,0);
      lcd.print("Over Limit");
     }else{
      lcd.setCursor(0,0);
      lcd.print("Error");
     }

    
    lcd.setCursor(0,1);
    lcd.print("Time: ");
    lcd.setCursor(6, 1);
    lcd.print(time[0+spotSelect]);
    lcd.setCursor(7,1);
    lcd.print(time[1+spotSelect]);
    lcd.setCursor(8,1);
    lcd.print("h");
    lcd.setCursor(9,1);
    lcd.print(time[2+spotSelect]);
    lcd.setCursor(10,1);
    lcd.print(time[3+spotSelect]);
    lcd.setCursor(11,1);
    lcd.print("m");
    lcd.setCursor(12,1);
    lcd.print(time[4+spotSelect]);
    lcd.setCursor(13,1);
    lcd.print(time[5+spotSelect]);
    lcd.setCursor(14,1);
    lcd.print("s");
    startMillis = currentMillis;
    }
    

}
