#ifndef AUDIO_H
#define AUDIO_H
#include <arduino.h>

const byte buzzerPin = A0;

void playAudio(int frequency, int timeInMilliseconds);

#endif