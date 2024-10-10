#include "leds.h"



// Initialize analog pins A2,A3,A4,A5 to be used as outputs
void initializeLeds()
{
  for (int i = 0; i < 4; i++)
  {
    pinMode(ledPins[i], OUTPUT); // Initialize the specified analog pins to be used as outputs
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

//  For testing the operation of subroutines void setLed(byte), void clearAllLeds(void) and void setAllLeds(void)
void testiOhjelma()
{
  setAllLeds();        // Turn on all leds
  delay(1000);         
  clearAllLeds();      // Turn off all leds
  delay(1000);         
  setLed(0);           // Turn on the led 0
  delay(1000);         
  setLed(1);           // Turn on the led 1
  delay(1000);         
  setLed(2);           // Turn on the led 2
  delay(1000);         
  setLed(3);           // Turn on the led 3
  delay(1000);         
  clearAllLeds();      // Turn off all leds
  delay(1000);         
}

// show1() subroutine shows numbers 0,1,...,15 as binary numbers, waits a bit and repeats number "show"
void show1()
{
  clearAllLeds(), delay(200); 
  digitalWrite(A5, HIGH), delay(200);
  digitalWrite(A5, LOW), digitalWrite(A4, HIGH), delay(200);
  digitalWrite(A5, HIGH), delay(200);
  digitalWrite(A3, HIGH), digitalWrite(A4, LOW), digitalWrite(A5, LOW), delay(200);
  digitalWrite(A5, HIGH), delay(200);
  digitalWrite(A5, LOW), digitalWrite(A4, HIGH), delay(200);
  digitalWrite(A5, HIGH), delay(200);
  digitalWrite(A2, HIGH), digitalWrite(A3, LOW), digitalWrite(A4, LOW), digitalWrite(A5, LOW), delay(200);
  digitalWrite(A5, HIGH), delay(200);
  digitalWrite(A5, LOW), digitalWrite(A4, HIGH), delay(200);
  digitalWrite(A5, HIGH), delay(200);
  digitalWrite(A3, HIGH), digitalWrite(A4, LOW), digitalWrite(A5, LOW), delay(200);
  digitalWrite(A5, HIGH), delay(200);
  digitalWrite(A5, LOW), digitalWrite(A4, HIGH), delay(200);
  digitalWrite(A5, HIGH), delay(200);
  clearAllLeds();
}

/* 
show2(int) subroutine shows leds 0, 0,1, 0,1,2, 0,1,2,3 with increasing changing rate per round. And when top change speed has been reached
-> int rounds: This parameter determines how many times 0,1,2,3 sequence is shown
*/
void show2(int rounds)
{
  int baseDelay = 400;  // Starting delay in milliseconds
  int minDelay = 50;   // Minimum delay (fastest speed)
  int decrement = 50;   // How much the delay decreases each round

  // Loop for the number of rounds specified
  for (int round = 0; round < rounds; round++)
   {
    // Light up LEDs in increasing order, with a delay between each step
    for (int i = 0; i < 4; i++)
     {
      for (int j = 0; j <= i; j++)
      {
        digitalWrite(ledPins[j], HIGH);  // Turn on LEDs from 0 to i
      }
      delay(baseDelay);  // Wait before turning on the next LED
    }
    clearAllLeds(); // Turn off all LEDs before starting the next round

    // Speed up the show by decreasing the delay after each round
    baseDelay -= decrement;
    if (baseDelay < minDelay)
    {
      baseDelay = minDelay;  // Ensure the delay doesn't go below the minimum
    }
  }
}