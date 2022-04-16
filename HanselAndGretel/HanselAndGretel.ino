/* AET319M&T Project 2: Hansel and Gretel
    Gretel pushes witch into oven > gets key > saves Hansel
*/
#include <Servo.h>

//inst servos (2)
Servo ovenServo; 
Servo cageServo;

//designate pin numbers. switch = I, pin = O
const int witchSwitch = 1;
const int witchPin = 2;

const int cageSwitch = 3;
const int cagePin = 4;

const int hanselSwitch = 5;

int ledPin = 7;
int ovenPiezoPin = 8;
int hanselPiezoPin = 9;

//keep track of states. start all off
int witchState = 0;
int cageState = 0;
int hanselState = 0;

void setup() {
  //designate I/O
  pinMode(witchSwitch, INPUT);
  pinMode(cageSwitch, INPUT);
  pinMode(hanselSwitch, INPUT);
  
  ovenServo.attach(witchPin);
  cageServo.attach(cagePin);

  //inital states
  ovenServo.write(0);
  cageServo.write(0);
  
  digitalWrite(ledPin, LOW);
  digitalWrite(ovenPiezoPin, LOW);
  digitalWrite(hanselPiezoPin, LOW);

  //debug
  Serial.begin(9600);
}

void loop() {
  ovenBehavior();
  cageBehavior();
}

void ovenAudio() {
  //NEED AUDIO FOR BURNING, WITCH SCREAMING
}

//witch/oven interaction
//NEED TO INCORPORATE SWITCH STATE CHECK CODE
void ovenBehavior() {
  witchState = digitalRead(witchSwitch); //read if HIGH/LOW

  //witch in oven, switch is ON
  if (witchState == HIGH) {
    ovenServo.write(180); //spin witch 180, display burnt side with key
    digitalWrite(ledPin, HIGH);
    digitalWrite(ovenPiezoPin, HIGH);
    ovenAudio(); //IMPLEMENT
  }
}

//key/cage/hansel interaction
void cageBehavior() {
  cageState = digitalRead(cageSwitch);
  hanselState = digitalRead(hanselSwitch);

  //key in cahe keyhole
  if (cageState == HIGH) {
    //GET AUDIO FOR CAGE OPENING
    digitalWrite(hanselPiezoPin, HIGH);
    cageServo.write(90); //open cage door
  }
  
  if (hanselState == HIGH) {
    //hansel still in cage, hanselSwitch is on
    
    digitalWrite(hanselPiezoPin, HIGH);
    //AUDIO OF HELP ME GRETEL
  } else {
    //hansel out of cage, hanselSwitch is off
    
    digitalWrite(hanselPiezoPin, LOW);
  }

  //must put witch into oven AND take hansel out of cage to win
  if (hanselState == LOW && witchState == HIGH) {
    digitalWrite(hanselPiezoPin, HIGH);
    //AUDIO OF HOORAY
  }
}
