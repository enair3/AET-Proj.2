/* AET319M&T Project 2: Hansel and Gretel
    Gretel pushes witch into oven > gets key > saves Hansel
*/
#include <Servos.h>;

//inst servos (2)
Servo ovenServo; 
Servo cageServo;

//designate pin numbers of inputs
const int witchPin = 3;
const int cagePin = 4;
const int hanselPin = 5;

//designate pin numbers of outputs
int ledPin = 6;
int ovenPiezoPin = 7;
int hanselPiezoPin = 8;

//keep track of states. start all off
int witchState = 0;
int cageState = 0;
int hanselState = 0;

void setup() {
  //designate I/O
  pinMode(witchPin, INPUT);
  pinMode(cagePin, INPUT);
  pinMode(hanselPin, INPUT);
  ovenServo.attach(witchPin);
  cageServo.attach(cageDoorPin);

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
  witchState = digitalRead(witchPin); //read if HIGH/LOW

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
  cageState = digitalRead(cagePin);
  hanselState = digitalRead(hanselPin);

  //key in cahe keyhole
  if (cageState == HIGH) {
    //GET AUDIO FOR CAGE OPENING
    digitalWrite(hanselPiezoPin, HIGH);
    hanselAudio(); //REVISIT

    cageServo.write(90); //open cage door
  }

  //hansel still in cage, switch is on
  if (hanselState == HIGH) {
    //switch is on, add hansel as a switch
    //AUDIO OF HELP ME GRETEL
    digitalWrite(hanselPiezoPin, HIGH);
  } else {
    digitalWrite(hanselPiezoPin, LOW);
  }

  //must put witch into oven AND take hansel out of cage to win
  if (hanselState == LOW && witchState == HIGH) {
    //AUDIO OF HOORAY
  }
}
