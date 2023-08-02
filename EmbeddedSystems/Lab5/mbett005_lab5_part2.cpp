enum States{INIT, S0, S1, S2, S3, S4} SM1_state;
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
const int xAxis = A0;
const int yAxis = A1;

const int light_pattern_size = 5;
const char light_pattern[light_pattern_size] = {0x00, 0x01, 0x03, 0x7, 0x0F};

const char sound_pattern_size = 5;
const double sound_pattern[sound_pattern_size] = { 230, 261.63, 293.66, 320, 335}; // C4, D4
const int xAxis_medianLeft = 80;
const int xAxis_medianRight = 120;
const int yAxis_medianDown = 80;
const int yAxis_medianUp = 120;
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
         
         //State Transition
        break;
      case S1:
            
             //State Transition
        break;
    }
    switch(state){ // State Action
      case INIT:
         //State Action
        break;
      case S0:
            writeBuffer(light_pattern[0]);
          
         //State Action
        break;
      case S1:
            writeBuffer(light_pattern[1]);
        break;
      case S2:
            writeBuffer(light_pattern[2]);
        break;
      case S3:
            writeBuffer(light_pattern[3]);
        break;
      case S4:
            writeBuffer(light_pattern[4]);
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
  

    if ((millis() - lastRan) > period) {     
      SM1_state = (States)SM1_Tick(SM1_state);        
      lastRan = millis();   
     }  
     //Serial.print(digitalRead(xAxis));
} 
