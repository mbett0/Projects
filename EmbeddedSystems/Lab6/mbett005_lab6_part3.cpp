// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {8, 9, 10, 11};
const int xAxis = A0; // Recall that A0 is really a number under the hood.
unsigned char ii = 0;
const int yAxis = A1;
unsigned int light_pattern_size = 0;
unsigned char light_pattern[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char lightTemp = 0;
unsigned char lightFlag = 0;
unsigned char errorCounter = 0;
unsigned char sound_pattern_size = 5;
unsigned char soundIndex = 0;
 // C4, D4
unsigned char sound0 = 91.63;
unsigned char sound1 = 225.30;
unsigned char sound2 = 149.23;
unsigned char sound3 = 393.88;
unsigned char stateCount = 0;
unsigned char sound_pattern[5] = {sound0, sound1, sound3, sound2, sound1};
const int JoyStick = 2;

unsigned char jInput;


const int xAxis_medianLeft = 450;
const int xAxis_medianRight = 650;
const int yAxis_medianDown = 425;
const int yAxis_medianUp = 650;
const int buzzer = 3;
// Reset the Output Buffer. 
void resetBuffer() {
    for(int i = 0; i < b_size; i++) {
        // Note this is an arduino function call to the pins
        digitalWrite(b[i], LOW);
    }
}
// Writes to the buffer. Note this function ORs the current value with the new value
// Note that size is an optional argument with default size the same as the buffer
void writeBuffer(unsigned char b_temp, int size = b_size)
{
    for (int i = (size - 1); i >= 0; i--) {
        if ((b_temp >> i) & 0x01) {
        digitalWrite(b[i], HIGH);
        }
    }

}


typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
    
} task;

int delay_gcd;
const unsigned short tasksNum = 2;
task tasks[tasksNum];

enum SM1_States { SM1_INIT, SM1_S0, SM1_S1, SM1_S2};
int SM1_Tick(int state){
  //Serial.print(jInput);
    //Read thing
    switch(state){ // State transitions
      case SM1_INIT:
         //State Transition
            state = SM1_S0;
        break;
      case SM1_S0:
          state = SM1_S0;
         //State Transition
        break;

    }
    switch(state){ // State Action
      case SM1_INIT:
         //State Action
         
        break;
      case SM1_S0:
      
         tone(buzzer, sound_pattern[soundIndex]);
         if(soundIndex > 4){
           soundIndex = 0;
         }else{
           soundIndex++;
         }
            //State Action
           // Serial.print("zero");
         
         //State Action
        break;

    }
    return state;
}

enum SM2_States { SM2_INIT, SM2_S0, SM2_S1, SM2_S2, SM2_S3};
int SM2_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case SM2_INIT:
         //State Transition
         Serial.print("INIT");
            state = SM2_S0;
        break;
      case SM2_S0:
      Serial.print("0");
          light_pattern_size = rand()%3 + 3;
          for(ii = 0; ii < light_pattern_size; ii++){
            lightTemp = rand()%4;
            if(lightTemp == 0){
              light_pattern[ii] = 0x01;
            }else if(lightTemp == 1){
              light_pattern[ii] = 0x02;
            }else if (lightTemp == 2){
              light_pattern[ii] = 0x04;
            }else{
              light_pattern[ii] = 0x08;
            }
            lightTemp = 0;
            state = SM2_S1;
         //State Transition
         resetBuffer();
         break;
      case SM2_S1:
      Serial.print("1");
           if (lightTemp == light_pattern_size*2){
             lightTemp = 0;
            state = SM2_S2;
          }
          else{
            //lightTemp == 0;
            state = SM2_S1;
          }
          resetBuffer();
          break;
       case SM2_S2:
       Serial.print("2");
         if(lightFlag){
           state = SM2_S0;
           lightFlag = 0;
         }else if(lightTemp == light_pattern_size){
           state = SM2_S3;
         }else{
           state = SM2_S2;
         }
         resetBuffer();
         break;
      case SM2_S3:
      Serial.print("3");
        if(errorCounter == 10){
          errorCounter = 0;
          state = SM2_S0;
        }else{
          state = SM2_S3;
        }
        resetBuffer();
        break;
       
    }
    switch(state){ // State Action
      case SM2_INIT:
         //State Action
        break;
      case SM2_S0:
          
          
          //lightTemp++;
         //State Action
        break;
      case SM2_S1:
        if(lightTemp%2 == 0){
          writeBuffer(light_pattern[lightTemp/2]);
        }else{
          //resetBuffer();
        }
          lightTemp++;
        break;
      case SM2_S2:
        
         if( analogRead(xAxis)< xAxis_medianLeft && light_pattern[lightTemp] != 0x08){
             lightFlag = 1;
         }
         if(analogRead(xAxis)< xAxis_medianLeft && light_pattern[lightTemp] == 0x08){
           lightTemp++;
         }
         if( analogRead(xAxis)< xAxis_medianRight && light_pattern[lightTemp] != 0x01){
             lightFlag = 1;
         }
         if(analogRead(xAxis)< xAxis_medianRight && light_pattern[lightTemp] == 0x01){
           lightTemp++;
         }
         if( analogRead(yAxis)< yAxis_medianUp && light_pattern[lightTemp] != 0x04){
             lightFlag = 1;
         }
         if(analogRead(yAxis)< yAxis_medianUp && light_pattern[lightTemp] == 0x04){
           lightTemp++;
         }
         if( analogRead(yAxis)< yAxis_medianDown && light_pattern[lightTemp] != 0x02){
             lightFlag = 1;
         }
         if(analogRead(yAxis)< yAxis_medianDown && light_pattern[lightTemp] == 0x02){
           lightTemp++;
         }
         
         
           
      break;
      case SM2_S3:
        if(errorCounter %2 == 0){
          writeBuffer(0x0F);
        }else{
            resetBuffer;
          }
          errorCounter++;
      break;
    }
    return state;
}
}






void setup() {
    //some set up (Default Arduino Function)

    // LEDs
    for(int i = 0; i < b_size; i++)
    {
        pinMode(b[i], OUTPUT);
    }
     pinMode(JoyStick, INPUT_PULLUP);
    Serial.begin(9600);


  unsigned char i = 0;
  tasks[i].state = SM1_INIT;
  tasks[i].period = 300;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM1_Tick;
  i++;
  tasks[i].state = SM2_INIT;
  tasks[i].period = 500;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;

  delay_gcd = 100; // GCD

}


void loop() {
  // put your main code here, to run repeatedly:
  //jInput = digitalRead(JoyStick);
 
 // Serial.print(analogRead(yAxis));
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
     if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
      
     }
   }
  delay(delay_gcd); // GCD.
  jInput = 0;
}
