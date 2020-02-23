#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

void surveillance(){
  for(int i=0; i <= 1; i++){
    Braccio.ServoMovement(30,           150,  45, 180, 40,  90,  73); 
    Braccio.ServoMovement(30,           30,  45, 180, 40,  90,  73);    
  }
}

void dance(){
  for(int i=0; i <= 5; i++){
    Braccio.ServoMovement(10,           0,  15, 180, 170, 0,  73);  
     Braccio.ServoMovement(10,           180,  15, 180, 0, 180,  73);  
     Braccio.ServoMovement(10,           0,  165, 0, 170, 0,  10);  
     Braccio.ServoMovement(10,           180,  165, 0, 0, 180,  10);  

  }
}

void setup() {
  //Initialization functions and set up the initial position for Braccio
  //All the servo motors will be positioned in the "safety" position:
  //Base (M1):90 degrees
  //Shoulder (M2): 45 degrees
  //Elbow (M3): 180 degrees
  //Wrist vertical (M4): 180 degrees
  //Wrist rotation (M5): 90 degrees
  //gripper (M6): 10 degrees
  Braccio.begin();
}

void loop() {
 surveillance();
 dance();
}
