#include "pitches.h"

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};


int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};


const int pushButton = 2;
int buttonState = 1;

const int activeBuzzerPin = 11;


const int passiveBuzzerPin = A0;
const int threshold = 1;
int passiveBuzzerValue = 0;
int varCheckKnock = 0;

unsigned long beginTime;
unsigned long currentTime;
unsigned long period = 5000;

void setup() {
  pinMode(pushButton, INPUT_PULLUP);
  pinMode(activeBuzzerPin, OUTPUT);
  pinMode(passiveBuzzerPin, INPUT);
  beginTime = millis();
}

void loop() {
  passiveBuzzerValue = analogRead(passiveBuzzerPin);
  currentTime = millis();
  if(passiveBuzzerValue >= threshold && varCheckKnock == 0){
    varCheckKnock = 1;
    currentTime = millis();
  }
  if(currentTime - beginTime >= period && varCheckKnock == 1){
      if(buttonState >= 1){
        for (int thisNote = 0; thisNote < 8; thisNote++) {

          buttonState = digitalRead(pushButton);
          if(buttonState == 0){
            break;
          }
          int noteDuration = 1000 / noteDurations[thisNote];
          tone(activeBuzzerPin, melody[thisNote], noteDuration);
      
          int pauseBetweenNotes = noteDuration * 1.30;
          delay(pauseBetweenNotes);
          //noTone(16);
          }
         beginTime = currentTime; 
      }
  }
}
