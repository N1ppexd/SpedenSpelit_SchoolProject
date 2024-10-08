#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

volatile bool newTimerInterrupt = false;  
volatile int interruptCount = 0;
byte gameNumbers[10];
byte playerButtonPushes[10];
int currentRound = 0; //this CAN BE MORE THAN 9
int roundRound = 0; //10 round rounds in one round and 10 normal rounds in one round too. Becomes 0 when it becomes 9
int ledNumber = 0;
bool gameContinues;
bool isPlaying;
bool gameLost;


unsigned long maxTime = 30;
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

  if (hasPressedLongEnough(3, 1)){
    startTheGame();
    isPlaying = true;
    gameLost = false;
  }

  if(isPlaying){
    int buttonPressed = getPressedButton();
  if (checkGame(buttonPressed)){
        int randomNumber = gameNumbers[roundRound];
     // and corresponding led must be activated
     clearAllLeds();
     delay(100);
    setLed(randomNumber);
    }
  }

  if(gameLost){
    setAllLeds();
    isPlaying = false;
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
  if(isPlaying){
  currentTime++;
    
    if (currentTime >= maxTime){
    timeHasPassed = true;
    currentTime = 0;
    }
  }
}


bool checkGame(int buttonNum)
{
  bool rightNumber = false;
  // checks if the right button was pressed.
  if (buttonNum == gameNumbers[roundRound]) {
    playerButtonPushes[roundRound] = gameNumbers[roundRound];
    currentRound++;
    roundRound++;
    interruptCount++;

    //check if button has been pressed 10 times
    if (interruptCount >= 9) {
      interruptCount = 0;
      initializeGame();
      maxTime = maxTime * 0.9;
    }

    Serial.println("");
    Serial.print("maxTime = ");
    Serial.println(maxTime);
    
    rightNumber = true;
    currentTime = 0;

  } else if (buttonNum >= 0) {
    rightNumber = false;
    gameLost = true;
  }

  //if no button is being pressed
  if(buttonNum == -1 && timeHasPassed){
    //check if time has passed
    gameLost = true;
  }

  //setLed(gameNumbers[currentRound]);
  showResult(currentRound);
  Serial.println("");
  Serial.print("currentRound = ");
  Serial.println(currentRound);

  return rightNumber;

	// see requirements for the function from SpedenSpelit.h
}


void initializeGame()
{
  roundRound = 0;
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
  roundRound = 0;
  timeHasPassed = false;
  initializeGame(); // initialize game settings
  int randomNumber = gameNumbers[currentRound];
  setLed(randomNumber);
  currentTime = 0;
}

