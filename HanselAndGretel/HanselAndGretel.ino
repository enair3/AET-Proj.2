/* AET319M&T Project 2: Hansel and Gretel
    Gretel pushes witch into oven > gets key > saves Hansel
    need to reupload to reset everything
    NOTE: servos only turn after the song is finished
    arduino song credits to https://github.com/robsoncouto/arduino-songs
*/

#include <Servo.h>
#include "pitches.h"
#include "songThemes.h"

//inst servos (2)
Servo ovenServo;
Servo cageServo;

//CONSTANTS. designate pin numbers. switch = I, pin = O
const int witchSwitch = 3;
const int cageSwitch = 2;

const int witchServoPin = 10;
const int cageServoPin = 12;
const int piezoPin = 8;

//VARIABLES. keep track of states
int witchState = 0;
int cageState = 0;

void setup() {
  //designate I/O
  pinMode(witchSwitch, INPUT);
  pinMode(cageSwitch, INPUT);

  pinMode(piezoPin, OUTPUT);

  ovenServo.attach(witchServoPin);
  cageServo.attach(cageServoPin);

  //inital states
  ovenServo.write(0);
  cageServo.write(90);

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

  //init states, start with witch out, hansel trapped in cage
  if (witchState == LOW && cageState == LOW) {
    witchTheme();
    
  //witch in oven, witchSwitch is ON but cage not opened yet. stays burnt
  } if (witchState == HIGH && cageState == LOW) {
    ovenServo.write(180);//spin witch 180, show burnt side with key
    hanselCrying();
  }
}

//key/cage/hansel interaction
void cageBehavior() {
  cageState = digitalRead(cageSwitch);

  //key in cage keyhole AND witch in oven to free hansel
  if (cageState == HIGH) {
    victoryTheme();
    cageServo.write(0); //open door
  }
}

//SONGTHEME FUNCTIONS
//WITCH SONG
void witchTheme() {
  //FIX into here and check in ovenBehavior()

  int notes = sizeof(witchMelody) / sizeof(witchMelody[0]) / 2;
  int wholenote = (60000 * 4) / witchTempo;
  int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody.
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    divider = pgm_read_word_near(witchMelody + thisNote + 1);
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }
    tone(piezoPin, pgm_read_word_near(witchMelody + thisNote), noteDuration * 0.9);
    delay(noteDuration);
    noTone(piezoPin);
  }
}

//HANSEL SONG
void hanselCrying() {
  //FIX into here and check in cageBehavior()
  int notes = sizeof(hanselMelody) / sizeof(hanselMelody[0]) / 2;
  int wholenote = (60000 * 4) / hanselTempo;
  int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody.
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    divider = pgm_read_word_near(hanselMelody + thisNote + 1);
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }
    tone(piezoPin, pgm_read_word_near(hanselMelody + thisNote ), noteDuration * 0.9);
    delay(noteDuration);
    noTone(piezoPin);
  }
}

//VICTORY SONG
void victoryTheme() {
  //FIX into here and check in cageBehavior()
  int notes = sizeof(victoryMelody) / sizeof(victoryMelody[0]) / 2;
  int wholenote = (60000 * 4) / victoryTempo;
  int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody.
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    divider = victoryMelody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }
    tone(piezoPin, victoryMelody[thisNote], noteDuration * 0.9);
    delay(noteDuration);
    noTone(piezoPin);
  }
}
