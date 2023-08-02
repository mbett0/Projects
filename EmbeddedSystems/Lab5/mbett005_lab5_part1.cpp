enum States{INIT, S0, S1} SM1_state;
unsigned long lastRan;
int Song = 0;
int SoundPlay = 0;
//int Song = 0;
int SongTime = 0;
const unsigned long period = 500;
const unsigned long LightPeriod = 2500;

// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {8, 9, 10, 11};
int JoyStick = 2; // Recall that A0 is really a number under the hood.
const int light_pattern_size = 5;
const char light_pattern[light_pattern_size] = {0x00, 0x01, 0x03, 0x7, 0x0F};

const char sound_pattern_size = 5;
const double sound_pattern[sound_pattern_size] = { 230, 261.63, 293.66, 320, 335}; // C4, D4

const int buzzer = 3;

//const int xAxis_median = 100; // Adjust this if needed

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

int SM1_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case INIT:
         //State Transition
            state = S0;
        break;
      case S0:
          if (!digitalRead(JoyStick)){
            state = S1;
          }
          else{
            state = S0;
          }
         //State Transition
        break;
      case S1:
            if (!digitalRead(JoyStick)){
                state = S0;
            }
            else{
                state = S1;
            }
             //State Transition
        break;
    }
    switch(state){ // State Action
      case INIT:
         //State Action
        break;
      case S0:
            //State Action
//            resetBuffer();
//            writeBuffer(light_pattern[0]);
            
            if(Song < 4 && SoundPlay == 4){
              Song++;
              SoundPlay = 0;
            }else if(Song == 4 && SoundPlay == 4){
              Song = 0;
              SoundPlay = 0;
              resetBuffer();
            }else if(Song == 4 && SoundPlay ==3){
              writeBuffer(light_pattern[4]);
            }else if(Song == 3 && SoundPlay ==3){
              writeBuffer(light_pattern[3]);
            }else if(Song == 2 && SoundPlay ==2){
              writeBuffer(light_pattern[2]);
            }else if(Song == 1 && SoundPlay ==1){
              writeBuffer(light_pattern[1]);
            }
            else{
            }
            tone(buzzer, sound_pattern[Song]);
            SoundPlay++;
          
         //State Action
        break;
      case S1:
            //State Action
            //resetBuffer();
            //writeBuffer(light_pattern[1]);
            noTone(buzzer);
         //State Action
        break;
    }

    return state;
}


  
  
void setup() {
    // OUTPUT is a defined macro in Arduino!
    for(int i = 0; i < b_size; i++)
        {
            pinMode(b[i], OUTPUT);
        }
        pinMode(JoyStick, INPUT_PULLUP);
    // We will also read from the serial monitor
    Serial.begin(9600);
}

void loop() {
  
//    if(Song == 5){
//       resetBuffer();
//    }else if(Song == 4 &&(millis()-lastRan) > 375){
//        writeBuffer(light_pattern[4]);
//    }  else if(Song == 3 &&(millis()-lastRan) > 375){
//        writeBuffer(light_pattern[3]);
//    }else if(Song == 2 && (millis()-lastRan) > 250){
//        writeBuffer(light_pattern[2]);
//    }else if(Song == 1 &&(millis()-lastRan) > 125){
//        writeBuffer(light_pattern[1]);
//    }else{
//      writeBuffer(light_pattern[0]);
//    }
    if ((millis() - lastRan) > period) {     
      SM1_state = (States)SM1_Tick(SM1_state);        
      lastRan = millis();   
     }  
} 
