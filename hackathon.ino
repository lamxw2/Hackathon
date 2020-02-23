#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

// Direction of the arm - left or right (0/180)
int dir = 0;
// The middle direction value
const int MID = 90;

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

void wave(int baseAng){
  // Set arm upright
  Braccio.ServoMovement(20,           baseAng,  90, 90, 90,  0,  73);  
  // Wave hand left and right
  for(int i=0; i <= 2; i++){
    Braccio.ServoMovement(10,           baseAng,  90, 90, 60,  0,  10);
    Braccio.ServoMovement(10,           baseAng,  90, 90, 120,  0,  10);    
  }
}

void surveillance(){
  // Rotate arm left and right
  for(int i=0; i <= 2; i++){
    Braccio.ServoMovement(30,           180,  45, 180, 40,  90,  73); 
    Braccio.ServoMovement(30,           0,  45, 180, 40,  90,  73);    
  }
}

void dance(){
  for(int i=0; i <= 5; i++){
    // Crazy movements
    Braccio.ServoMovement(10,           0,  15, 180, 170, 0,  73);  
    Braccio.ServoMovement(10,           180,  165, 0, 0, 180,  10);  
  }
}

/* Put the cup back down */
void putCupDown(int baseAng){
  // Starting position
  Braccio.ServoMovement(20,           baseAng,  45, 180, 40,  90,  73);

  // Reach down 
  Braccio.ServoMovement(10,           baseAng,  140, 180, 140,  90,  73);

  // Open grip 
  Braccio.ServoMovement(10,           baseAng,  140, 180, 140,  90,  10);

  // Move the wrist down so it lets go of the cup - narrow base
  Braccio.ServoMovement(20,           baseAng,  140, 180, 90,  90,  10);
  Braccio.ServoMovement(20,           baseAng,  100, 180, 0,  90,  10);
}

/* Pick up a cup */
void pickCupUp(int baseAng){
  // Starting position
  Braccio.ServoMovement(10,           baseAng,  45, 180, 40,  90,  73);

  // Reach down while opening grip
  Braccio.ServoMovement(20,           baseAng,  70, 180, 20,  90,  10);

  Braccio.ServoMovement(20,           baseAng,  140, 180, 90,  90,  10);

  Braccio.ServoMovement(20,           baseAng,  140, 180, 140,  90,  10);
  
  Braccio.ServoMovement(10,           baseAng,  140, 180, 140,  90,  73);
}

/* Pour into the middle cup */
void pour(){
  // Amount to angle the arm from the middle 
  int dec = 17;

  // Angle base to the right slightly to pour into middle cup
  Braccio.ServoMovement(20,           MID-dec,  110, 160, 100,  90,  73);
  
  // Tilt grip left to pour 
  Braccio.ServoMovement(20,           MID-dec,  110, 160, 100,  0,  73);
  
  //Braccio.ServoMovement(10,           MID,  60, 180, 20,  0,  73);
  
  // Wait 2 seconds
  delay(2000);
  
  // Tilt grip right again
  Braccio.ServoMovement(20,           MID-dec,  110, 160, 100,  90,  73);
 
}

void spin() {
  Braccio.ServoMovement(10,           100,  45, 180, 40,  60,  73);
  Braccio.ServoMovement(10,           50,  45, 180, 40,  120,  73);  
}

void loop() {
  /*
  Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
  M1=base degrees. Allowed values from 0 to 180 degrees
  M2=shoulder degrees. Allowed values from 15 to 165 degrees
  M3=elbow degrees. Allowed values from 0 to 180 degrees
  M4=wrist vertical degrees. Allowed values from 0 to 180 degrees
  M5=wrist rotation degrees. Allowed values from 0 to 180 degrees
  M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.
  */

  // Start perpendicular
  Braccio.ServoMovement(20,           MID,  90, 90, 90,  90,  73);

  // Wave
  wave(dir);

  // Pick up left cup and pour; right cup and pour
  for(int i=0; i <= 1; i++){

    if (i == 0){
      dir = 180; // left?
    } else {
      dir = 0; // right?
    } // mid = 90
     
    pickCupUp(dir);
  
    // Move upwards
    Braccio.ServoMovement(20,           dir,  45, 180, 40,  90,  73);
    // Turn base 90 degrees
    Braccio.ServoMovement(10,           MID,  45, 180, 40,  90,  73);

    pour();

    putCupDown(dir);
  }

  // After pouring in two cups, pick up the middle cup and spin it
  pickCupUp(MID);

  // Shake the cup
  for(int i=0; i <= 4; i++){
    spin();
  }

  // Put it down again
  putCupDown(MID);
  
  // Perpendicular position
  Braccio.ServoMovement(20,           MID,  90, 90, 90,  90,  73);
  
  // Wait 1 second
  delay(1000);
  
  // Starting position - collapse
 Braccio.ServoMovement(10,           MID,  45, 180, 40,  90,  73);

 // Wait 1 second
 delay(1000);

}
