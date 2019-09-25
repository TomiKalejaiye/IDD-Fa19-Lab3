/*
Force Sensor Datalogger

 Uses a rotary encoder to set "recording" and "playing" states for an Arduino, so that analog voltages 
 from a force sensor can be written(recorded) to and read(played) from an EEPROM. I use the terms "recorded"
 and "played" because this is intended to ultimately use a speaker to play the saved analog voltages.
 For now it simply displays them on the serial monitor.

 Created by Tomi Kalejaiye

 25 Sep. 2019
 
 */



#include <EEPROM.h>
#define PUSH 9

const int EEPROMSIZE=1024;
int buttonPos = HIGH;
int prev_buttonPos = HIGH;
bool switched = false;

int state = 1;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PUSH, INPUT_PULLUP);
  for (int i = 0; i < EEPROMSIZE; i++) {
    EEPROM.write(i, 0);
  }
  playSetup();
}

void loop() {
  switched = switchState(checkButton());
  switch (state) {
    case 2:
      record();
      break;
    case 1:
      play();
      break;
  }
  
}

int checkButton(){
  /*Returns HIGH if button has been pushed and LOW if not.*/
  buttonPos = digitalRead(PUSH);
  int pushed = LOW;
  /*Checks if there has been a change in the position of the button*/
  if (buttonPos != prev_buttonPos) {
    /*Only consider button pushed after button has been released.
    Since we use a pullup resistor, buttonPos will be HIGH when the button is released.*/
    if (buttonPos == HIGH) {
      //note that button has been pressed
      pushed = HIGH;
    } 
  }
  //update button position
  prev_buttonPos = buttonPos;
  return pushed;
}

bool switchState(int pushed){
  //switch state depending not on the state of the button, but only on whether it was just pushed or not.
  if (pushed == HIGH && state == 1){
    state = 2;
    return true;
  }
  if (pushed == HIGH && state == 2){
    state = 1;
    return true;
  }
  return false;
}
