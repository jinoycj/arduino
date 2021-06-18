/*
 * Bujji - Jagame Thandhiram
 * 
 * Connect a piezo buzzer or speaker to pin 6 or select a new pin.
 * for more arduino projects from me, plese visit https://github.com/jinoycj/
 * 
 * I have used some code snippets from https://github.com/robsoncouto/arduino-songs 
 * There you can find lots other songs.
 * 
 * Jinoy Johnson - 2021
 */


#include "melody.h"

// change this to whichever pin you want to use
int buzzer = 11;

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;
void setup() {
    // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = pgm_read_word_near(melody+thisNote + 1);
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, pgm_read_word_near(melody+thisNote), noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }

}

void loop() {
  // no need to repeat the melody.

}
