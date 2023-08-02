enum States{INIT, LightShow1, LightShow2} SM1_state = INIT;
int X_button = 8;
int Y_button = 9;
unsigned long lastRan;
unsigned long period;

// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {2, 3, 4, 5};
// Output Buffer
int b_buf = 0x00;
// Input Variables
int LightShowCount = 0;
// Serial Monitor Buffer
int s_buf = 0x00; 

/* 's' is an array of integers of size 8. Note that arrays start at 0
 We will use this to be able to see the individual bit values of the s_buf

 */
const int s_size = 8;
int s[s_size];

// We can also define our own helper functions. It is a good idea to use helper functions whenever they make sense.
// Normally we also define the return type (void for none)

// Read from the serial monitor into s_buf and the s[] array for individual bits
void readData()
{
    if(Serial.available())
        s_buf = Serial.parseInt();

    for(int i = (s_size - 1); i>=0; i--)  { 
        s[i] = (s_buf >> i) & 0x01; // What's going on here?
        // ">>" bit shifting 
        // "&" bit masking
    }

}
// Reset the Output Buffer. 
void resetBuffer() {
    for(int i = 0; i < b_size; i++) {
        // Note this is an arduino function call to the pins
        digitalWrite(b[i], LOW);
    }
}
// Writes to the buffer. Note this function ORs the current value with the new value
// Note that size is an optional argument with default size the same as the buffer
void writeShow1()
{
    if(LightShowCount == 0){
      digitalWrite(b[0],HIGH);
      digitalWrite(b[1],HIGH);
      digitalWrite(b[2],HIGH);
      digitalWrite(b[3],HIGH);
    }
    else if(LightShowCount == 1){
      digitalWrite(b[0],LOW);
      digitalWrite(b[1],HIGH);
      digitalWrite(b[2],LOW);
      digitalWrite(b[3],HIGH);
    }
    else{
      digitalWrite(b[0],HIGH);
      digitalWrite(b[1],LOW);
      digitalWrite(b[2],HIGH);
      digitalWrite(b[3],HIGH);
    }
    //resetBuffer();
    

}

void writeShow2()
{
   if(LightShowCount == 0){
      digitalWrite(b[0],HIGH);
      digitalWrite(b[1],HIGH);
      digitalWrite(b[2],HIGH);
      digitalWrite(b[3],LOW);
    }
    else if(LightShowCount == 1){
      digitalWrite(b[0],LOW);
      digitalWrite(b[1],HIGH);
      digitalWrite(b[2],LOW);
      digitalWrite(b[3],LOW);
    }
    else{
      digitalWrite(b[0],HIGH);
      digitalWrite(b[1],LOW);
      digitalWrite(b[2],HIGH);
      digitalWrite(b[3],LOW);
    }

}


void setup(){
  //some set up (Default Arduino Function)
    pinMode(X_button, INPUT);
    pinMode(Y_button, INPUT);
    // LEDs
    for(int i = 0; i < b_size; i++)
    {
        pinMode(b[i], OUTPUT);
    }
    Serial.begin(9600);
    period = 1000;
    lastRan = 0;
}
// This function takes in the state as an argument & returns the current state
int SM1_Tick(int state, int b_buf){
    //Read thing
    switch(state){ // State transitions
      case INIT:
         //State Transition
         state = LightShow1;
        break;

      case LightShow1:
         if (b_buf < 3) {
           
           //resetBuffer();
            state = LightShow2;
         }
         else {
            state = LightShow1;
         }
        break;
      case LightShow2:
        if(b_buf > 3){
          
          //resetBuffer();
          state = LightShow1;
          
        }else{
          state = LightShow2;
        }
         //State Transition
        break;
    }
    switch(state){ // State Action
      case INIT:
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
      case LightShow2:
         if(LightShowCount < 2){
            LightShowCount++;
         }else{
           LightShowCount = 0;
         }
         writeShow2();
        break;
    }

    return state;
}

void loop(){ 
    ///Default arduino function
    // We have to cast the return value of the tick function to type States
     b_buf = analogRead(A1);
    b_buf = map(b_buf, 0, 1023, 0, 16);
    if ((millis() - lastRan) > period) {  
      SM1_state = (States)SM1_Tick(SM1_state, b_buf);
     lastRan = millis();
    }
    //delay(250);
    //resetBuffer();
}
