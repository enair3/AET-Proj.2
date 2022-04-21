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
  cageServo.write(0);

  digitalWrite(ledPin, LOW);
  digitalWrite(piezoPin, LOW);

  //debug
  Serial.begin(9600);
}

void loop() {
//  ovenBehavior();
  cageBehavior();
}

//witch/oven interaction
void ovenBehavior() {
  witchState = digitalRead(witchSwitch); //read if HIGH/LOW, assign
  
  //witch in oven, switch is ON
  if (witchState == HIGH) {
    ovenServo.write(180); //spin witch 180, show burnt side with key
    digitalWrite(ledPin, HIGH);
    Serial.write("HIGH" );
    
    tone(x,y,z);//audio of burning, witch screaming
    digitalWrite(piezoPin, HIGH);
    
  } else {
    ovenServo.write(0);
    digitalWrite(ledPin, LOW);
    Serial.write("LOW ");
    digitalWrite(piezoPin, LOW);
  }
}

//key/cage/hansel interaction: stretch
void cageBehavior() {
  cageState = digitalRead(cageSwitch);

  //key in cage keyhole AND witch in oven to win
  if (cageState == HIGH && witchState == HIGH) {
    digitalWrite(piezoPin, LOW); //turn off Hansel crying
    cageServo.write(90); //open door
    
  } else { //no key, witch is out, still trapped
    
   tone(x,y,z); //Hansel crying
   cageServo.write(0); //closed door
  }

}
