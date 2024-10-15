#include "audio.h"

void playButtonPressAudio(void)
{
  playAudio(NOTE_C5, 100); 
}

void playStartAudio(void){
  Serial.print("playStartAudio");

  // Lyhyt start-ääni
  int startTones[] = {523, 587, 659}; // C4, D4, E4
  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, startTones[i], 1000); // Soita kukin äänimerkki 1 sekunti
    delay(100); // 100 ms tauko äänten välillä
  }
  noTone(buzzerPin);
}

void playLoseAudio(void){
  Serial.print("playLoseAudio");

  // Lyhyt game over -ääni
  int gameOverTones[] = {659, 587, 523}; // E4, D4, C4
  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, gameOverTones[i], 1000); // Soita kukin äänimerkki 1 sekunti
    delay(100); // 100 ms tauko äänten välillä
  }
  noTone(buzzerPin);
}

void playAudio(int frequency, int timeInMilliseconds){
    tone(buzzerPin, frequency, timeInMilliseconds);
}
