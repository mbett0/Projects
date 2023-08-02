// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {8, 9, 10, 11};
const int xAxis = A0; // Recall that A0 is really a number under the hood.

const int yAxis = A1;
const int light_pattern_size = 3;
const char light_pattern[light_pattern_size] = {0x01, 0x03, 0x05};
unsigned char LightShowCount = 0;
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
void writeShow1()
{
    if(LightShowCount == 0){
      digitalWrite(b[0],HIGH);
      digitalWrite(b[1],LOW);
      digitalWrite(b[2],LOW);
    }
    else if(LightShowCount == 1){
      digitalWrite(b[0],HIGH);
      digitalWrite(b[1],HIGH);
      digitalWrite(b[2],LOW);
    }
    else{
      digitalWrite(b[0],HIGH);
      digitalWrite(b[1],HIGH);
      digitalWrite(b[2],HIGH);
    }
    //resetBuffer();
    

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
            }else{ 
              state = SM1_S0;
            }
        break;
    }
    switch(state){ // State Action
      case SM1_INIT:
         //State Action
         
        break;
      case SM1_S0:
         digitalWrite(b[3],LOW);
        break;
      case SM1_S1:
        digitalWrite(b[3],HIGH);
            //State Action
           //Serial.print("one");  
         //State Action
        break;
        
 
          
       
    }

    return state;
}

enum SM2_States { SM2_INIT, LightShow1};
int SM2_Tick(int state){
    //Read thing
    
   
      switch(state){ // State transitions
      case SM2_INIT:
         //State Transition
         state = LightShow1;
        break;

      case LightShow1:
          state = LightShow1;
        break;
    }
    switch(state){ // State Action
      case SM2_INIT:
         //State Action
        break;
//      case S1Press:
//        break;
//      case S0Press:
//        break;
      case LightShow1:
        if(LightShowCount < 2){
            LightShowCount++;
         }else{
           LightShowCount = 0;
         }
        writeShow1();
         //State Action
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
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM1_Tick;
  i++;
  tasks[i].state = SM2_INIT;
  tasks[i].period = 1000;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;

  delay_gcd = 100; // GCD

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
