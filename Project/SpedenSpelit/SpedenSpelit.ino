#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

volatile bool newTimerInterrupt = false;  
volatile int interruptCount = 0;
byte gameNumbers[10];
byte playerButtonPushes[10];
int currentRound = 0;
int ledNumber = 0;
bool gameContinues;
bool isPlaying;
bool gameLost;

void setup()
{
initButtonsAndButtonInterrupts();
initializeDisplay();
initializeLeds();
Serial.begin(9600);

}

void loop()
{ 

  if (hasPressedLongEnough(3, 1)){
    startTheGame();
    isPlaying = true;
    gameLost = false;
  } 
     // check the game if 0<=buttonNumber<4
  /*if (buttonNumber >= 0 && buttonNumber < 4) {

    checkGame(buttonNumber);
  }*/

  if(isPlaying){
    checkGame(getPressedButton());
  }

if(gameLost){
  setAllLeds();
  isPlaying = false;
}




  if(newTimerInterrupt == true)
  {
     // new random number must be generated
    int randomNumber = gameNumbers[currentRound];
     // and corresponding led must be activated
    digitalWrite(ledPins[randomNumber], HIGH);
    
    //currentRound++;

    newTimerInterrupt = false;
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

  /*
  Communicate to loop() that it's time to make new random number.
  Increase timer interrupt rate after 10 interrupts.
  */
  
}


bool checkGame(int buttonNum)
{
  bool rightNumber = false;
  // checks if the right button was pressed.
  if (buttonNum == gameNumbers[currentRound]) {
    playerButtonPushes[currentRound] = gameNumbers[currentRound];
    currentRound++;
    interruptCount++;
    if (interruptCount >= 10) {
      interruptCount = 0;
      initializeGame();
    }
    
    rightNumber = true;
  } else if (buttonNum >= 0) {
    rightNumber = false;
    gameLost = true;
  }

  setLed(gameNumbers[currentRound]);
  showResult(currentRound);
  Serial.println("");
  Serial.print("currentRound = ");
  Serial.println(currentRound);

  return rightNumber;

	// see requirements for the function from SpedenSpelit.h
}


void initializeGame()
{
for (int i = 0; i < 10; i++) {
  gameNumbers[i] = random(0,4);
}

for (int i = 0; i < 10; i++) {
  playerButtonPushes[i] = 0;
}

	// see requirements for the function from SpedenSpelit.h
}

void startTheGame()
{
  currentRound = 0;
  initializeGame(); // initialize game settings
  initializeTimer();
}

