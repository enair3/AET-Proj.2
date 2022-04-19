/* AET319M&T Project 2: Hansel and Gretel
    Gretel pushes witch into oven > gets key > saves Hansel
*/

#include <Servo.h>

//inst servos (2)
Servo ovenServo;
Servo cageServo;

//CONSTANTS. designate pin numbers. switch = I, pin = O
const int witchSwitch = 2;
const int cageSwitch = 3;
const int hanselSwitch = 5;

const int witchServoPin = 10;
const int cageServoPin = 4;
const int ledPin = 7;
const int ovenPiezoPin = 8;
const int hanselPiezoPin = 9;

//VARIABLES. keep track of states
int witchState = 0;
int cageState = 0;
int hanselState = 0;

void setup() {
  //designate I/O
  pinMode(witchSwitch, INPUT);
  pinMode(cageSwitch, INPUT);
  pinMode(hanselSwitch, INPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(ovenPiezoPin, OUTPUT);
  pinMode(hanselPiezoPin, OUTPUT);

  ovenServo.attach(witchServoPin);
  cageServo.attach(cageServoPin);

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
//  cageBehavior();
}

//witch/oven interaction
//INCORPORATE STATE CHANGE DETECTION CODE?
void ovenBehavior() {
  witchState = digitalRead(witchSwitch); //read if HIGH/LOW, assign
  
  //witch in oven, switch is ON
  if (witchState == HIGH) {
    ovenServo.write(180); //spin witch 180, show burnt side with key
    digitalWrite(ledPin, HIGH);
//    digitalWrite(ovenPiezoPin, HIGH);

    //audio of burning, witch screaming
  } else {
    digitalWrite(ledPin, LOW);
  }
}

//key/cage/hansel interaction
//void cageBehavior() {
//  cageState = digitalRead(cageSwitch);
//  hanselState = digitalRead(hanselSwitch);
//
//  //key in cahe keyhole
//  if (cageState == HIGH) {
//    //GET AUDIO FOR CAGE OPENING
//    digitalWrite(hanselPiezoPin, HIGH);
//    cageServo.write(90); //open cage door
//  }
//
//  if (hanselState == HIGH) {
//    //hansel still in cage, hanselSwitch is on
//    digitalWrite(hanselPiezoPin, HIGH);
//    //AUDIO OF HELP ME GRETEL
//  } else {
//    //hansel out of cage, hanselSwitch is off
//    digitalWrite(hanselPiezoPin, LOW);
//  }
//
//  //must put witch into oven AND take hansel out of cage to win
//  if (hanselState == LOW && witchState == HIGH) {
//    digitalWrite(hanselPiezoPin, HIGH);
//    //AUDIO OF HOORAY
//  }
//}
