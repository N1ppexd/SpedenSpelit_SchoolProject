#include "audio.h"

void playButtonPressAudio(void)
{
  playAudio(NOTE_C5, 100); 
}

void playStartAudio(void){
  // short start sound
  int startTones[] = {523, 587, 659}; // C4, D4, E4
  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, startTones[i], 1000); // play every note for 1 second
    delay(100); // 100 ms break between notes
  }
  noTone(buzzerPin);
}

void playLoseAudio(void){
  // short game over sound
  int gameOverTones[] = {659, 587, 523}; // E4, D4, C4
  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, gameOverTones[i], 1000); // play every note for 1 second
    delay(100); // 100 ms break between notes
  }
  noTone(buzzerPin);
}

void playAudio(int frequency, int timeInMilliseconds){
    tone(buzzerPin, frequency, timeInMilliseconds);
}
