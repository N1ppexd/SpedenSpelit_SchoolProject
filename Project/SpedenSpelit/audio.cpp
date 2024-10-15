#include "audio.h"

int numTones = 62;
int tones[] = {587, 784, 880, 988, 988, 988, 988, 988, 988, 988, 932, 988, 784, 784, 784, 784, 784, 784, 784, 880, 988, 1047, 1047, 1319, 1319, 1319, 1319, 1175, 1047, 988, 988, 988, 784, 880, 988, 1047, 1047, 1319, 1319, 1319, 1319, 1175, 1047, 988, 988, 784, 784, 784, 784, 880, 988, 988, 988, 1047, 880, 880, 880, 988, 784, 784, 784, 784};

void playButtonPressAudio(void)
{
  playAudio(NOTE_C5, 100); 
}

void playStartAudio(void){
  Serial.print("playStartAudio");

  // short start sound
  int startTones[] = {523, 587, 659}; // C4, D4, E4
  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, startTones[i], 1000); // play every note for 1 second
    delay(100); // 100 ms break between notes
  }
  noTone(buzzerPin);
}

void playLoseAudio(void){
  Serial.print("playLoseAudio");

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
