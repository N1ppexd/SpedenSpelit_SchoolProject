#include "leds.h"

// Define pin numbers for the LEDs
const int ledPins[] = {A2, A3, A4, A5};

// Initialize analog pins A2,A3,A4,A5 to be used as outputs
void initializeLeds()
{
  for (int i = 0; i < 4; i++)
  {
      pinMode(ledPins[i], OUTPUT);
  }
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
  if (ledNumber >= 0 && ledNumber <= 3)
  {
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(ledPins[i], LOW);  // Clear all the LEDs first to ensure that only one LED can be turned on at a time
    }

  digitalWrite(ledPins[ledNumber], HIGH);  // Turn on the specified LED 
  }
}

// Clears all leds
void clearAllLeds()
{
  for (int i = 0; i < 4; i++) 
  {
    digitalWrite(ledPins[i], LOW);  // Turn off the specified leds (led 0, 1, 2 and 3)
  }
}

// Sets all leds
void setAllLeds()
{
  for (int i = 0; i < 4; i++) 
  {
    digitalWrite(ledPins[i], HIGH);  // Turn on the specified leds (led 0, 1, 2 and 3)
  }
    
}

void show1()
{
// see requirements for this function from leds.h
}

void show2(int rounds)
{
// see requirements for this function from leds.h  
}