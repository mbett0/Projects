// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {8, 9, 10, 11};
const int xAxis = A0; // Recall that A0 is really a number under the hood.

const int yAxis = A1;
const int light_pattern_size = 2;
//const char light_pattern[light_pattern_size] = {0x00, 0x0F};

unsigned char sound_pattern_size = 0;
unsigned char index = 0;
unsigned char sound_pattern[6] = {0, 0, 0, 0, 0, 0}; // C4, D4
unsigned char sound0 = 91.63;
unsigned char sound1 = 225.30;
unsigned char sound2 = 149.23;
unsigned char sound3 = 393.88;
unsigned char stateCount = 0;
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
          if (jInput){
           
            state = SM1_S0;
          }
          else{
            state = SM1_S1;
          }
         //State Transition
        break;
      case SM1_S1:
            if (jInput){
              
                state = SM1_S1;
            }
            else{
                state = SM1_S2;
            }
        break;
       case SM1_S2:
             if(jInput){
               
                 state = SM1_S2;
             }else{
               state = SM1_S0;
             }
             //State Transition
        break;
    }
    switch(state){ // State Action
      case SM1_INIT:
         //State Action
         
        break;
      case SM1_S0:
      if(analogRead(xAxis) < xAxis_medianLeft){
           tone(buzzer, sound0);
         }else if(analogRead(xAxis) > xAxis_medianRight){
           tone(buzzer, sound1);
         }else if(analogRead(yAxis) < yAxis_medianDown){
           tone(buzzer, sound2);
         }else if(analogRead(yAxis) > yAxis_medianUp){
           tone(buzzer, sound3);
         }else{
           noTone(buzzer);
         } 
        stateCount = 0;
            //State Action
           // Serial.print("zero");
         
         //State Action
        break;
      case SM1_S1:
        stateCount = 1;
        if(analogRead(xAxis) < xAxis_medianLeft){
            sound_pattern[sound_pattern_size] = sound0;
            sound_pattern_size++;
           tone(buzzer, sound0);
         }else if(analogRead(xAxis) > xAxis_medianRight){
           sound_pattern[sound_pattern_size] = sound1;
            sound_pattern_size++;
           tone(buzzer, sound1);
         }else if(analogRead(yAxis) < yAxis_medianDown){
           sound_pattern[sound_pattern_size] = sound2;
            sound_pattern_size++;
           tone(buzzer, sound2);
         }else if(analogRead(yAxis) > yAxis_medianUp){
           sound_pattern[sound_pattern_size] = sound3;
            sound_pattern_size++;
           tone(buzzer, sound3);
         }else{
           noTone(buzzer);
         }
            //State Action
           //Serial.print("one");  
         //State Action
        break;
        
      case SM1_S2:
        stateCount = 2;
       //Serial.print("two");
          
        break;
    }

    return state;
}

enum SM2_States { SM2_INIT, SM2_S0, SM2_S1, SM2_S2};
int SM2_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case SM2_INIT:
         //State Transition
            state = SM2_S0;
        break;
      case SM2_S0:
          if (stateCount == 2){
            state = SM2_S1;
          }
          else{
            state = SM2_S0;
          }
         //State Transition
        break;
      case SM1_S1:
            if (stateCount == 2){
            state = SM2_S1;
          }
          else{
            state = SM2_S0;
          }
         break;
       
    }
    switch(state){ // State Action
      case SM2_INIT:
         //State Action
        break;
      case SM2_S0:
         Serial.print("zero");
          
         //State Action
        break;
      case SM2_S1:
       tone(buzzer, sound_pattern[index]);
       Serial.print(index);
            if(index < sound_pattern_size){
              index++;
            }else{
              index = 0;
            }
          Serial.print("one");
          
        break;
      
    }
    return state;
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
  tasks[i].period = 200;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM1_Tick;
  i++;
  tasks[i].state = SM2_INIT;
  tasks[i].period = 1000;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;

  delay_gcd = 200; // GCD

}


void loop() {
  // put your main code here, to run repeatedly:
  jInput = digitalRead(JoyStick);
  Serial.println(stateCount);
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
