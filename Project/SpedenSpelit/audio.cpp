#include "audio.h"



void playButtonPressAudio(void){

}
void playLoseAudio(void){

}
void playStartAudio(void){
    
}

playAudio(int frequency, int timeInMilliseconds){
    tone(buzzerPin, frequency);
    delay(timeInMilliseconds);
    noTone(buzzerPin);
}
