#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"
#include "audio.h"


int pressedCount = 0;
byte gameNumbers[10];
byte playerButtonPushes[10];
int currentRound = 0;
int ledNumber = 0;
bool isPlaying;
bool gameLost;

const unsigned long maxMaxTime = 25;
unsigned long maxTime;
volatile long currentTime;
volatile bool timeHasPassed;

int highScore = 0;


void setup()
{
  initButtonsAndButtonInterrupts();
  initializeDisplay();
  initializeLeds();
  initializeTimer();
  clearDisplay();
  Serial.begin(9600);
}

void loop()
{ 

  

  if (!isPlaying)
  {
    if (hasPressedLongEnough(3, 1))
    {
      startTheGame();
      
    }
    if(hasPressedLongEnough(2, 1))
    {
      Serial.print("highscore");
      clearDisplay();
      delay(100);
      showResult(highScore);
      delay(3000);
      clearDisplay();
    }

    if(hasPressedLongEnough(1,1)){
      show1();
    }
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
  if (buttonNum == gameNumbers[pressedCount])
  {
    playerButtonPushes[pressedCount] = gameNumbers[pressedCount];
    currentRound++;
    pressedCount++;

    

    //check if button has been pressed 10 times
    if (pressedCount > 9) 
    {
      initializeGame();
      maxTime = maxTime * 0.7;
    }

    Serial.println("");
    Serial.print("maxTime = ");
    Serial.println(maxTime);
    
    currentTime = 0;

    int randomNumber = gameNumbers[pressedCount];
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

  if(currentRound > highScore){
    highScore = currentRound;
  }

  showResult(currentRound);
  Serial.println("");
  Serial.print("currentRound = ");
  Serial.println(currentRound);
}


void initializeGame()
{
  pressedCount = 0;
  for (int i = 0; i < 10; i++) {
    gameNumbers[i] = random(0,4);
  }

  for (int i = 0; i < 10; i++) {
    playerButtonPushes[i] = 0;
  }
}


void startTheGame()
{
  clearDisplay();
  setAllLeds();
  playStartAudio();  //ÄLÄ POISTA
  delay(1000);
  //show1();  //ÄLÄ POISTA
  maxTime = maxMaxTime;
  currentRound = 0;
  pressedCount = 0;
  timeHasPassed = false;
  initializeGame(); // initialize game settings
  int randomNumber = gameNumbers[pressedCount];
  setLed(randomNumber);
  currentTime = 0;

  isPlaying = true;
  gameLost = false;
}


void loseTheGame()
{
  playLoseAudio();
  isPlaying = false;
  
  setAllLeds();
  delay(1000);
  show2(12);
  delay(1000);
  clearDisplay();
}

