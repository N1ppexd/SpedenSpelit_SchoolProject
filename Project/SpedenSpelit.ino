#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile int buttonNumber = -1;           // for buttons interrupt handler
volatile bool newTimerInterrupt = false;  // for timer interrupt handler


void setup()
{
initButtonsAndButtonInterrupts();
initializeDisplay();
initializeLeds();
  /*
    Initialize here all modules
  */
}

void loop()
{ 
  // start the game if buttonNumber == 4
  if (buttonNumber == 4){
    startTheGame();
  } 
     // check the game if 0<=buttonNumber<4
  if (buttonNumber >= 0 & buttonNumber < 4) {

  }
     



  if(newTimerInterrupt == true)
  {
     // new random number must be generated
     // and corresponding let must be activated
  }
}

void initializeTimer(void)
{
	// see requirements for the function from SpedenSpelit.h
}
ISR(TIMER1_COMPA_vect)
{
  /*
  Communicate to loop() that it's time to make new random number.
  Increase timer interrupt rate after 10 interrupts.
  */
  
}


void checkGame(byte nbrOfButtonPush)
{
	// see requirements for the function from SpedenSpelit.h
}


void initializeGame()
{
	// see requirements for the function from SpedenSpelit.h
}

void startTheGame()
{
   // see requirements for the function from SpedenSpelit.h
}

