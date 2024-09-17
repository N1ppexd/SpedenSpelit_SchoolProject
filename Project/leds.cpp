#include "leds.h"

// Define pin numbers for the LEDs
const int ledPins[] = {A2, A3, A4, A5};

// Initialize analog pins A2,A3,A4,A5 to be used as outputs
void initializeLeds()
{
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
}

/*
  Sets correct led number given as 0,1,2 or 3 
  led number 0 corresponds to led connected at Arduino pin A2
  led number 1 => Arduino pin A3
  led number 2 => Arduino pin A4
  led number 3 => Arduino pin A5
*/
void setLed(byte ledNumber)
{
  setLed(0);
  setLed(1);
  setLed(2);
  setLed(3);
}

// Clears all leds
void clearAllLeds()
{
  for (int i = 0; i < 4; i++) 
  {
    digitalWrite(ledPins[i], LOW);
  }
}

void setAllLeds()
{
// see requirements for this function from leds.h
}


void show1()
{
// see requirements for this function from leds.h
}

void show2(int rounds)
{
// see requirements for this function from leds.h  
}