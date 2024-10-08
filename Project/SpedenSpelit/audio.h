#ifndef AUDIO_H
#define AUDIO_H
#include <arduino.h>
#define NOTE_C5  523

const byte buzzerPin = A0;

/// @brief use playAudio to make sound effect shit
/// @param  
void playButtonPressAudio(void);
/// @brief use playAudio to make sound effect shit
/// @param  
void playLoseAudio(void);
/// @brief use playAudio to make sound effect shit
/// @param  
void playStartAudio(void);

/// @brief Play audio
/// @param frequency frequency
/// @param timeInMilliseconds time
void playAudio(int frequency, int timeInMilliseconds);

#endif