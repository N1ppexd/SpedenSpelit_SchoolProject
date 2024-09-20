#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile int buttonNumber = -1;           // for buttons interrupt handler
volatile bool newTimerInterrupt = false;  // for timer interrupt handler
volatile int interruptCount = 0;


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
  if (buttonNumber >= 0 && buttonNumber < 4) {
    checkGame(buttonNumber);
  }
     



  if(newTimerInterrupt == true)
  {
     // new random number must be generated
    int randomNumber = random(0,4);
     // and corresponding led must be activated
    digitalWrite(ledipinni[randomNumber], HIGH);

    newTimerInterrupt = false:
  }
}

void initializeTimer(void)
{
  int timerLimit = 6250;
  noInterrupts(); // disable interrupts while setting up the timer
  TCCR1A = 0; // clear timer1 control register A
  TCCR1B = 0; // clear timer1 control register B
  TCCR1B |= (1 << WGM12) | (1 << CS12);
  OCR1A = timerLimit; // ten times a second.
  TIMSK1 |= (1 << OCIE1A); 
  interrupts(); // Re-enable
	// see requirements for the function from SpedenSpelit.h
}

ISR(TIMER1_COMPA_vect)
{
newTimerInterrupt = true;
interruptCount++;

if (interruptCount >= 10) {
  cli(); // clear interrupts = disable interrupts
  OCR1A = OCR1A * 0.9; // Decreasing OCR1A by 10%
  interruptCount = 0; // reset the interrupt count
  sei(); // Re-enable interrupts
  }
  /*
  Communicate to loop() that it's time to make new random number.
  Increase timer interrupt rate after 10 interrupts.
  */
  
}


void checkGame(byte nbrOfButtonPush)
{

// checks if the right button was pressed.
if (nbrOfButtonPush == 0){

}
if (nbrOfButtonPush == 1){
  
}
if (nbrOfButtonPush == 2){
  
}
if (nbrOfButtonPush == 3){
  
}


	// see requirements for the function from SpedenSpelit.h
}


void initializeGame()
{
	// see requirements for the function from SpedenSpelit.h
}

void startTheGame()
{
  initializeGame(); // initialize game settings
  initializeTimer();
}

