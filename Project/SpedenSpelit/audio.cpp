#include "audio.h"

playAudio(int frequency, int timeInMilliseconds){
    tone(buzzerPin, frequency);
    delay(timeInMilliseconds);
    noTone(buzzerPin);
}
