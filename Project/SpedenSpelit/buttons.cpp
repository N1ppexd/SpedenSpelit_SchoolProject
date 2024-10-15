#include "buttons.h"
#include "audio.h"

volatile byte lastButtonState = 0;               
volatile unsigned long lastDebounceTime = 0;   
const unsigned long debounceDelay = 50;            
const unsigned long pressThreshold = 3000;         

volatile bool buttonPressedFlag[4] = {false, false, false, false};         
volatile unsigned long buttonPressDuration[4] = {0, 0, 0, 0};

volatile unsigned long timePressed;

int getPressedButton(){
  for(int i = 0; i < 4; i++){
    if(buttonPressedFlag[i]){
      buttonPressedFlag[i] = false;
      playButtonPressAudio();
      return i;
    }
  }
  
  return -1;
}

ISR(PCINT2_vect) {
    unsigned long currentTime = millis();
    
    byte currentButtonState = PIND & 0b00111100;

    if ((currentTime - lastDebounceTime) > debounceDelay) {
        if (currentButtonState != lastButtonState) { 
            lastButtonState = currentButtonState; 

            for (byte pin = 2; pin <= 5; pin++) { 
                byte bitMask = (1 << pin); 

                if (!(currentButtonState & bitMask)) { 
                    Serial.print("Button ");
                    Serial.print(pin);
                    Serial.println(" pressed");
                    buttonPressedFlag[pin - 2] = true; 
                    buttonPressDuration[pin - 2] = 0;

                    timePressed = millis();

                } else {
                    if (lastButtonState & bitMask) { 
                        Serial.print("Button ");
                        Serial.print(pin);
                        Serial.println(" released");
                        buttonPressedFlag[pin - 2] = false; 

                        timePressed = 0;
                    }
                }
            }
        }
        lastDebounceTime = currentTime; 
    }
}

void initButtonsAndButtonInterrupts() {
    for (byte pin = 2; pin <= 5; pin++) {
        pinMode(pin, INPUT_PULLUP); 
    }

    PCICR |= B00000100; 
    PCMSK2 |= B00111100; 
    Serial.println("Started");
}

bool hasPressedLongEnough(int button, float time){
 bool result = ((float)(millis() - timePressed)) >= time * 1000 && buttonPressedFlag[button] == true;

  if(result){
    buttonPressedFlag[button] = false;
    timePressed = millis();
  }

 return result;
}
