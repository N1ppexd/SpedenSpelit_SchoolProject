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

const unsigned long maxMaxTime = 30;
unsigned long maxTime;
volatile long currentTime;
volatile bool timeHasPassed;


void setup()
{
  initButtonsAndButtonInterrupts();
  initializeDisplay();
  initializeLeds();
  initializeTimer();
  Serial.begin(9600);
}

void loop()
{ 

  if (hasPressedLongEnough(3, 1) && !isPlaying)
  {
    startTheGame();
    isPlaying = true;
    gameLost = false;
  }

  if(isPlaying)
  {
    int buttonPressed = getPressedButton();
    checkGame(buttonPressed);
  }

  if(gameLost && isPlaying)
  {
    loseTheGame();
  }
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
  if(isPlaying)
  {
    currentTime++;
    if (currentTime >= maxTime){
      timeHasPassed = true;
      currentTime = 0;
    }
  }
}


void checkGame(int buttonNum)
{
  // checks if the right button was pressed.
  if (buttonNum == gameNumbers[interruptCount])
  {
    playerButtonPushes[interruptCount] = gameNumbers[interruptCount];
    currentRound++;
    interruptCount++;

    int randomNumber = gameNumbers[interruptCount];

    //check if button has been pressed 10 times
    if (interruptCount >= 9) 
    {
      initializeGame();
      maxTime = maxTime * 0.9;
    }

    Serial.println("");
    Serial.print("maxTime = ");
    Serial.println(maxTime);
    
    currentTime = 0;

    clearAllLeds();
    delay(100);
    setLed(randomNumber);

  } 
  //if player DID press a button (meaning buttonNum is more or equal to 0), but it was the wrong one, game is lost
  else if (buttonNum >= 0) 
  {
    gameLost = true;
  }
  //if button was not pressed, and time has passed, player loses...
  if(buttonNum == -1 && timeHasPassed)
  {
    gameLost = true;
  }

  showResult(currentRound);
  Serial.println("");
  Serial.print("currentRound = ");
  Serial.println(currentRound);

  //return rightNumber;
}


void initializeGame()
{
  interruptCount = 0;
  for (int i = 0; i < 10; i++) {
    gameNumbers[i] = random(0,4);
  }

  for (int i = 0; i < 10; i++) {
    playerButtonPushes[i] = 0;
  }
}


void startTheGame()
{
  setAllLeds();
  delay(1000);
  show1();
  maxTime = maxMaxTime;
  currentRound = 0;
  interruptCount = 0;
  timeHasPassed = false;
  initializeGame(); // initialize game settings
  int randomNumber = gameNumbers[interruptCount];
  setLed(randomNumber);
  currentTime = 0;
}


void loseTheGame()
{
  isPlaying = false;
  setAllLeds();
  delay(1000);
  show2(12);
}

