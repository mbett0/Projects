#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
 int selectButton = 8;
int switchButton = 9;

unsigned char heartrate = 1;
unsigned char prevBeat = 0;
unsigned char beats = 0;
unsigned char beatTime = 0;
unsigned char Threshold = 400; //edit when sensor connected;
int PulseSensorPurplePin = 0; //"    "

int TempSensor = 0;
unsigned char temp = 2;
unsigned char coolThresh = 350;
unsigned char warmThresh = 540;

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
    
} task;

enum SM4_States{SM4_INIT, SM4_Run};

int SM4_Tick(int state){
  switch(state){
    case SM4_INIT:
      state = SM4_Run;
      break;
    case SM4_Run:
      state = SM4_Run;
      break;
  }
  switch(state){
    case SM4_INIT:
      break;
    case SM4_Run:
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
       digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
       duration = pulseIn(echoPin, HIGH);
      // Calculating the distance
      distance = duration * 0.034 / 2;
      break;
  }
  return state; 
}

enum SM2_States {SM2_INIT, startGame, two1A, two1B, two2A1, two2A2, two2A3, two2B1, two2B2, two2B3, two3A, two3B, two4A1, two4B1, two4C, two3A1, two3A2, two3A3, LockedOut, LostD, LostB, death};
int SM2_Tick(int state){
  switch(state){
    case SM2_INIT:
      state = startGame;
      Serial.println("Welcome to my 120B Project");
      Serial.println("Press start to being");
      Serial.println();
      Serial.println();
//               Serial.println("You are in a ");
//      
//      Serial.println("dark room with");
//      
//      Serial.println("a big door");
//      
//      Serial.println(">Open the door?");
//      
//      Serial.println("Look around   ");
//      
//      Serial.println("the room?");

      Serial.println();
      Serial.println();
      break;
    case startGame:
//      delay(250);
      if(digitalRead(selectButton) == 1){
        state = two1A;
      Serial.println("You are in a ");
      
      Serial.println("dark room with");
      
      Serial.println("a big door");
      
      Serial.println(">Open the door?");
      
      Serial.println("Look around   ");
      
      Serial.println("the room?");

      Serial.println();
      Serial.println();
        
      }else{
        state = startGame;
      }
      break;
     case two1A:
       if(digitalRead(selectButton) == 1 && temp == 0){
        state = two2A1;
                Serial.println("You go outside ");
        
        Serial.println("Into a freezing");
        
        Serial.println("Snowy tundra");
        
        Serial.println(">Walk into the  ");
        
        Serial.println("wilderness");
        
        Serial.println("Return to hut "); 
        Serial.println();
        Serial.println();
        
       }else if(digitalRead(selectButton) == 1 && temp == 1){
        state = two2A2;
                Serial.println("You go outside ");
        
        Serial.println("Into a forest");
        
        Serial.println("With a river ");
        
        Serial.println(">Walk into the  ");
        
        Serial.println("wilderness");
        
        Serial.println("Return to hut ");
        Serial.println();
        Serial.println();
        
       }else if(digitalRead(selectButton) == 1 && temp == 2){
        state = two2A3;
                Serial.println("You go outside ");
        
        Serial.println("Into a boiling");
        
        Serial.println("Dry desert    ");
        
        Serial.println(">Walk into the  ");
        
        Serial.println("wilderness");
        
        Serial.println("Return to hut ");
        Serial.println();
        Serial.println(); 
        
       }else if(digitalRead(switchButton) == 1){
        state = two1B;
              Serial.println("You are in a");
      
      Serial.println("dark room with");
      
      Serial.println("a big door");
      
      Serial.println("Open the door?");
      
      Serial.println(">Look around");
      
      Serial.println("the room?");
      Serial.println();
      Serial.println();
       }else{
        state = two1A;
       }
       break;
     case two1B:
       if(digitalRead(selectButton) == 1 ){
        state = two3A;
                Serial.println("You find a box");
        
        Serial.println("with a logo on");
        
        Serial.println("it with the   ");
        
        Serial.println("letters TIL.  ");
        
        Serial.println(">Open the box ");
        
        Serial.println("Keep looking  ");
        Serial.println();
        Serial.println();
        
       }else if(digitalRead(switchButton) == 1){
        state = two1A;
              Serial.println("You are in a ");
      
      Serial.println("dark room with");
      
      Serial.println("a big door");
      
      Serial.println(">Open the door?");
      
      Serial.println("Look around   ");
      
      Serial.println("the room?");
      Serial.println();
      Serial.println();
       }else{
        state = two1B;
       }
       break;
     case two2A1:
        if(digitalRead(selectButton) == 1){
          state = LostB;
                  Serial.println("You quickly   ");
        
        Serial.println("Get lost in a  ");
        
        Serial.println("Blizzard and   ");
        
        Serial.println("Freeze to death");
        
        Serial.println(">Press select");
        Serial.println();
        Serial.println();
          
        }else if(digitalRead(switchButton) == 1){
          state = two2B1;
                  Serial.println("You go outside ");
        
        Serial.println("Into a freezing");
        
        Serial.println("Snowy tundra");
        
        Serial.println("Walk into the  ");
        
        Serial.println("wilderness");
        
        Serial.println(">Return to hut"); 
        Serial.println();
        Serial.println();
        }else{
          state = two2A1;
        }
        break;
     case two2B1:
        if(digitalRead(selectButton) == 1){
          state = LockedOut;
                  Serial.println("You reach for ");
        
        Serial.println("the door but  ");
        
        Serial.println("the hut you   ");
        
        Serial.println("came out of   ");
        
        Serial.println("dissapears");
        
        Serial.println(">Continue");
        Serial.println();
        Serial.println();
          
        }else if(digitalRead(switchButton) == 1){
          state = two2A1;
                  Serial.println("You go outside ");
        
        Serial.println("Into a freezing");
        
        Serial.println("Snowy tundra");
        
        Serial.println(">Walk into the  ");
        
        Serial.println("wilderness");
        
        Serial.println("Return to hut "); 
        Serial.println();
        Serial.println();
        }else{
          state = two2B1;
        }
        break;
     case two2A2:
        if(digitalRead(selectButton) == 1){
          state = two4A1;
          
        }else if(digitalRead(switchButton) == 1){
          state = two2B2;
                  Serial.println("You go outside ");
        
        Serial.println("Into a forest");
        
        Serial.println("With a river ");
        
        Serial.println("Walk into the  ");
        
        Serial.println("wilderness");
        
        Serial.println(">Return to hut ");
        Serial.println();
        Serial.println();
        }else{
          state = two2A2;
        }
        break;
     case two2B2:
        if(digitalRead(selectButton) == 1){
          state = two4C;
          
                  Serial.println("The door has  ");
        
        Serial.println("locked behind ");
        
        Serial.println("you and you  ");
        
        Serial.println("cant get in  ");
        
        Serial.println(">Explore the  ");
        
        Serial.println("forest");

        Serial.println();
        Serial.println();
          
        }else if(digitalRead(switchButton) == 1){
          state = two2A2;
                  Serial.println("You go outside ");
        
        Serial.println("Into a forest");
        
        Serial.println("With a river ");
        
        Serial.println(">Walk into the  ");
        
        Serial.println("wilderness");
        
        Serial.println("Return to hut ");
        Serial.println();
        Serial.println();
        }else{
          state = two2B2;
        }
        break;
     case two2A3:
        if(digitalRead(selectButton) == 1){
          state = LostD;
                  Serial.println("You walk for  ");
        
        Serial.println("A short while ");
        
        Serial.println("But cannot    ");
        
        Serial.println("Find water and");
        
        Serial.println("Die of thirst ");
        
        Serial.println(">Press select");
        Serial.println();
        Serial.println();
          
        }else if(digitalRead(switchButton) == 1){
          state = two2B3;
         Serial.println("You go outside ");
        
        Serial.println("Into a boiling");
        
        Serial.println("Dry desert    ");
        
        Serial.println("Walk into the  ");
        
        Serial.println("wilderness");
        
        Serial.println(">Return to hut "); 
        Serial.println();
        Serial.println();
          
        }else{
          state = two2A3;
        }
        break;
     case two2B3:
        if(digitalRead(selectButton) == 1){
          state = LockedOut;
                  Serial.println("You reach for ");
        
        Serial.println("the door but  ");
        
        Serial.println("the hut you   ");
        
        Serial.println("came out of   ");
        
        Serial.println("dissapears");
        
        Serial.println(">Continue");
        Serial.println();
        Serial.println();
          
        }else if(digitalRead(switchButton) == 1){
          state = two2A3;        
         Serial.println("You go outside ");
        
        Serial.println("Into a boiling");
        
        Serial.println("Dry desert    ");
        
        Serial.println(">Walk into the  ");
        
        Serial.println("wilderness");
        
        Serial.println("Return to hut "); 
        Serial.println();
        Serial.println();
        }else{
          state = two2B3;
        }
        break;
     case two3A:
        if(digitalRead(selectButton) == 1 && heartrate){
          state = two3A1;
           Serial.println("Your heart is ");
        
        Serial.println("Pounding hard.");
        
        Serial.println("You feel a    ");
        
        Serial.println("Pain in your  ");
        
        Serial.println("Chest. You can");
        
        Serial.println("Not breathe.  ");
        Serial.println();
        Serial.println();
        }else if(digitalRead(selectButton) == 1){
          state = two3A2;
                  Serial.println("The box is    ");
        
        Serial.println("empty         ");
        Serial.println();
        Serial.println();
        }else if(digitalRead(switchButton) == 1){
          state = two3B;
                  Serial.println("You find a box");
        
        Serial.println("with a logo on");
        
        Serial.println("it with the   ");
        
        Serial.println("letters TIL.  ");
        
        Serial.println("Open the box  ");
        
        Serial.println(">Keep looking ");
        Serial.println();
        Serial.println();
        }else{
          state = two3A;
        }
        break;
     case two3B:
        if(digitalRead(selectButton) == 1){
          state = two3A3;
        }else if(digitalRead(switchButton) == 1){
          state = two3A;
                  Serial.println("You find a box");
        
        Serial.println("with a logo on");
        
        Serial.println("it with the   ");
        
        Serial.println("letters TIL.  ");
        
        Serial.println(">Open the box ");
        
        Serial.println("Keep looking  ");
        Serial.println();
        Serial.println();
        }else{
          state = two3B;
        }
        break;
     case two3A1:

        break;
     case two3A2:

        break;
     case two3A3:

        break;
     case two4A1:
        if(distance < 30){
          Serial.println("A pack of rhinos crushed you");
          Serial.println("As they ran through the forrest");
          Serial.println();
          Serial.println();
          Serial.println("You have died");
          state = death;
        }else{
          state = two4B1;
          Serial.println("A pack of rhinos stampede");
          Serial.println("Directly in front of you");
          Serial.println("That was a close one");
          Serial.println("You mutter to yourself");
        }
        break;
     case two4B1:
        break;
     case two4C:

        if(digitalRead(selectButton) == 1){
          state = two4A1;
        }else{
          state = two4C;
        }
        break;

     case LockedOut:
        if(digitalRead(selectButton) == 1){
          state = death;
         Serial.println("You have died");
        
        Serial.println("Reset select to play again");
        }else{
          state = LockedOut;
        }
        break;
     case LostD:
        if(digitalRead(selectButton) == 1){
          state = death;
                  Serial.println("You have died");
        
        Serial.println("Reset select to play again");
        }else{
          state = LostD;
        }
        break;
     case LostB:
        if(digitalRead(selectButton) == 1){
          state = death;
                  Serial.println("You have died");
        
        Serial.println("Reset select to play again");
        }else{
          state = LostB;
        }
        break;
     case death:
        state = death;
        break;
  }
    
  return state;
}



//enum SM1_States { SM1_INIT, SM1_S0, SM1_S1};
//int SM1_Tick(int state){
//  
//    //Read thing
//    switch(state){ // State transitions
//      case SM1_INIT:
//         //State Transition
//            state = SM1_S0;
//        break;
//      case SM1_S0:
//          if (beats/beatTime * 1000 > 4){
//           
//            state = SM1_S1;
//          }
//          else{
//            state = SM1_S0;
//          }
//         //State Transition
//        break;
//      case SM1_S1:
//            if (beats/beatTime * 1000 > 4){
//                state = SM1_S1;
//            }else{ 
//              state = SM1_S0;
//            }
//        break;
//    }
//    switch(state){ // State Action
//      case SM1_INIT:
//         //State Action
//         
//        break;
//      case SM1_S0:
//         heartrate = 0;
//         if(beatTime == 10000){
//          beatTime = 0;
//          beats = 0;
//          prevBeat = 0;
//         }else if(analogRead(PulseSensorPurplePin) > Threshold && heartrate){
//           prevBeat = 1;
//           beatTime++;
//         }else if(analogRead(PulseSensorPurplePin) > Threshold){
//            beats++;
//            beatTime++;
//            prevBeat  = 1;
//         }else{
//          beatTime++; 
//          prevBeat = 0;
//         }
//        break;
//      case SM1_S1:
//        heartrate = 1;
//         if(beatTime == 10000){
//          beatTime = 0;
//          beats = 0;
//          prevBeat = 0;
//         }else if(analogRead(PulseSensorPurplePin) > Threshold && prevBeat){
//          beatTime++;
//          prevBeat = 1;
//         }else if(analogRead(PulseSensorPurplePin) > Threshold){
//            beats++;
//            beatTime++;
//            prevBeat = 1;
//         }else{
//          beatTime++; 
//          prevBeat = 0;
//         }
//        break;
//        
// 
//          
//       
//    }
//    return state;
//}

//enum SM3_States{SM3_INIT, SM3_0, SM3_1, SM3_2};
//int SM3_Tick(int state){
//  switch(state){
//    case SM3_INIT:
//      state = SM3_1;
//      break;
//    case SM3_0:
//      if(analogRead(TempSensor) < coolThresh){
//        state = SM3_0;
//      }else if(analogRead(TempSensor) > warmThresh){
//        state = SM3_1;
//      }else{
//        state = SM3_2;
//      }
//      break;
//    case SM3_1:
//      if(analogRead(TempSensor) < coolThresh){
//        state = SM3_0;
//      }else if(analogRead(TempSensor) > warmThresh){
//        state = SM3_1;
//      }else{
//        state = SM3_2;
//      }break;
//    case SM3_2:
//      if(analogRead(TempSensor) < coolThresh){
//        state = SM3_0;
//      }else if(analogRead(TempSensor) > warmThresh){
//        state = SM3_1;
//      }else{
//        state = SM3_2;
//      }
//      break;
//  }
//  switch (state){
//    case SM3_INIT:
//      break;
//     case SM3_0:
//       temp = 0;
//      break;
//      case SM3_1:
//        temp = 2;
//        break;
//      case SM3_2:
//        temp = 1;
//        break;
//      
//  }
//  return state;
//}
const unsigned short tasksNum = 2;
task tasks[tasksNum];
// The SetUp Function:
void setup() {
  pinMode(selectButton == 1, INPUT);
  pinMode(switchButton == 1, INPUT);
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  unsigned char i = 0;
//  tasks[i].state = SM1_INIT;
//  tasks[i].period = 50;
//  tasks[i].elapsedTime = 0;
//  tasks[i].TickFct = &SM1_Tick;
//  i++;
  tasks[i].state = SM2_INIT;
  tasks[i].period = 300;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;
//  i++;
//  tasks[i].state = SM3_INIT;
//  tasks[i].period = 200;
//  tasks[i].elapsedTime = 0;
//  tasks[i].TickFct = &SM3_Tick;
  i++;
  tasks[i].state = SM4_INIT;
  tasks[i].period = 1000;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM4_Tick;
   Serial.begin(9600);         // Set's up Serial Communication at certain speed.

}

// The Main Loop Function
void loop() {

  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
     if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
      
     }
  }
}
