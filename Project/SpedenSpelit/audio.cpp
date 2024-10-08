#include "audio.h"



void playButtonPressAudio(void){
    playAudio(NOTE_C5, 100); 
}
void playLoseAudio(void){

}
void playStartAudio(void){
    
}

void playAudio(int frequency, int timeInMilliseconds){
    tone(buzzerPin, frequency);
    delay(timeInMilliseconds);
    noTone(buzzerPin);
}
