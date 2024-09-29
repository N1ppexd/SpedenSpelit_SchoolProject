#ifndef AUDIO_H
#define AUDIO_H
#include <arduino.h>

const byte buzzerPin = A0;

void playButtonPressAudio(void);
void playLoseAudio(void);
void playStartAudio(void);

void playAudio(int frequency, int timeInMilliseconds);

#endif