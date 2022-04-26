/* AET319M&T Project 2: Hansel and Gretel
    Gretel pushes witch into oven > gets key > saves Hansel
*/

#include <Servo.h>
#include "pitches.h"

//inst servos (2)
Servo ovenServo;
Servo cageServo;

//CONSTANTS. designate pin numbers. switch = I, pin = O
const int witchSwitch = 2;
const int cageSwitch = 3;

const int witchServoPin = 10;
const int cageServoPin = 4;
const int ledPin = 7;
const int piezoPin = 8;

//VARIABLES. keep track of states
int witchState = 0;
int cageState = 0;

void setup() {
  //designate I/O
  pinMode(witchSwitch, INPUT);
  pinMode(cageSwitch, INPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(piezoPin, OUTPUT);

  ovenServo.attach(witchServoPin);
  cageServo.attach(cageServoPin);

  //inital states
  ovenServo.write(0);
  cageServo.write(90);

  digitalWrite(ledPin, LOW);
  digitalWrite(piezoPin, LOW);

  //debug
  Serial.begin(9600);
}

void loop() {
  ovenBehavior();
  cageBehavior();
}

//witch/oven interaction
void ovenBehavior() {
  witchState = digitalRead(witchSwitch); //read if HIGH/LOW, assign

  //witch in oven, witchWwitch is ON but cage not opened yet. stays burnt
  if (witchState == HIGH && cageState == LOW) {
    ovenServo.write(180); //spin witch 180, show burnt side with key
    digitalWrite(ledPin, HIGH);
    tone(8, 2000); //CHANGE TONE TO WITCH SOUNDS
    //might need inOven var (inst 0, dead 1) based on playtesting
    //Q if players will close oven again after getting key...
  }
  //without else component, have to reupload to arduino to reset ovenServo
  //  } else {
  //    ovenServo.write(0);
  //    digitalWrite(ledPin, LOW); //turn off witch sounds
  //  }
}

//key/cage/hansel interaction
void cageBehavior() {
  cageState = digitalRead(cageSwitch);

  //key in cage keyhole AND witch in oven to free hansel
  if (cageState == HIGH && witchState == HIGH) {
    //  if (cageState == HIGH) {
    noTone(8); //turn off Hansel crying
    cageServo.write(0); //open door

  } else { //no key, witch is out, still trapped
    tone(8, 200); //CHANGE TONE FOR CRYING
    cageServo.write(90); //closed door
  }
}
