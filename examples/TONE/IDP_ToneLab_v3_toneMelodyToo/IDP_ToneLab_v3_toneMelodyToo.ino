#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);       // initialize serial communications
pinMode (8, OUTPUT);
pinMode (12, OUTPUT);

 digitalWrite(12, HIGH);
//copied code from toneMelody
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
   digitalWrite(12, LOW);
}


void loop() {
  // put your main code here, to run repeatedly:

   // get a sensor reading:
   int sensorReading = analogRead(A0);

   //if the sensor is in full light -play nothing!
   if (sensorReading <= 650){
    digitalWrite(12, HIGH);
   // map the results from the sensor reading's range
   // to the desired pitch range:
   float frequency = map(sensorReading, 10, 700, 50, 1000);
   // change the pitch, play for 10 ms:
   tone(8, frequency, 30);
   } else {
    digitalWrite(12, LOW);
   }
   
}
