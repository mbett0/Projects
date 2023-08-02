enum States{INIT, Active, Reset} SM1_state = INIT;
int X_button = 8;
int Y_button = 9;

// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {2, 3, 4, 5};
// Output Buffer
int b_buf = 0x00;
// Input Variables
int LEDCount = 0;
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
void writeActive()
{
    if(LEDCount > 0){
      digitalWrite(b[0],HIGH);
    }
    if(LEDCount > 1){
      digitalWrite(b[1],HIGH);
    }
    if(LEDCount > 2){
      digitalWrite(b[2],HIGH);
    }
    if(LEDCount > 3){
      digitalWrite(b[3],HIGH);
    }
    //resetBuffer();
    

}

void writeReset()
{
   for (int i = 3; i >= 0; i--) {
        digitalWrite(b[i], LOW);
    }
    LEDCount = 0;

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
}
// This function takes in the state as an argument & returns the current state
int SM1_Tick(int state, int b_buf){
    //Read thing
    switch(state){ // State transitions
      case INIT:
         //State Transition
         state = Active;
        break;

      case Active:
         if (b_buf > 3) {
            state = Reset;
         }
         else {
            state = Active;
         }
        break;
      case Reset:
        if(b_buf < 3){
          state = Active;
          
        }else{
          state = Reset;
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
      case Reset:
        writeReset();
         //State Action
        break;
      case Active:
         if(digitalRead(X_button)== HIGH && LEDCount < 4){
            LEDCount++;
         }else if(digitalRead(X_button)== HIGH && LEDCount > 3){
           LEDCount = 0;
         }else if(digitalRead(Y_button)== HIGH && LEDCount > 0){
           LEDCount--;
         }else if(digitalRead(Y_button) == HIGH && LEDCount == 0){
           LEDCount = 4;
         }else{
           LEDCount = LEDCount;
         }
         writeActive();
        break;
    }

    return state;
}

void loop(){ 
    ///Default arduino function
    // We have to cast the return value of the tick function to type States
     b_buf = analogRead(A1);
    b_buf = map(b_buf, 0, 1023, 0, 16);
    SM1_state = (States)SM1_Tick(SM1_state, b_buf);
    delay(200);
    resetBuffer();
}
